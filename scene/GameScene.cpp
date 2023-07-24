#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <list>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;
}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("sample.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	player_ = new Player();
	player_->Initialize(model_, textureHandle_);

	enemy_ = new Enemy();
	enemy_->Initialize(model_, { 0.0f,0.0f,50.0f });

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	enemy_->SetPlayer(player_);
}

void GameScene::Update() {
	player_->Updete();
	enemy_->Update();
	CheckAllCollisions();


#ifdef  _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}



#endif //  _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
	else {
		viewProjection_.UpdateMatrix();
	}


}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	const std::list<PlayerBullet*> playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*> enemyBullets = enemy_->GetBullets();



	std::list<Collider*>colliders_;
	colliders_.push_back(player_);
	colliders_.push_back(enemy_);
	for (PlayerBullet* bullets : player_->GetBullets()) {
		colliders_.push_back(bullets);
	}
	for (EnemyBullet* bullets : enemy_->GetBullets()) {
		colliders_.push_back(bullets);
	}

	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (;itrA != colliders_.end();++itrA) {
		//イテレーターAからコライダーAを取得する
		Collider* colliderA = *itrA;


		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (;itrB != colliders_.end();++itrB) {
			Collider* colliderB = *itrB;
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB)
{
	if (colliderA->GetCollisionAttribute() != colliderB->GetCollisionMask() ||
		colliderB->GetCollisionAttribute() != colliderA->GetCollisionMask()) {
		return;
	}
	Vector3 posA;
	Vector3 posB;
	posA = colliderA->GetWorldPosition();
	posB = colliderB->GetWorldPosition();
	float distance = (posB.x - posA.x) * (posB.x - posA.x) +
		(posB.y - posA.y) * (posB.y - posA.y) +
		(posB.z - posA.z) * (posB.z - posA.z);
	if (distance <= colliderA->GetRadius() + colliderB->GetRadius()) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}