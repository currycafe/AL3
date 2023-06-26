#include "Player.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"





Player::~Player()
{
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	/*if (bullet_) {
		delete bullet_;
	}*/
	delete sprite2DReticle_;

}


void Player::Initialize(Model* model, uint32_t textureHundle, const Vector3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = textureHundle;
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
	worldTransform3DReticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("target.png");
	sprite2DReticle_ = Sprite::Create(textureReticle, { 640,360 }, { 1,1,1,1 }, { 0.5f,0.5f });
}

void Player::Updete(ViewProjection& viewProjection)
{
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	Vector3 move = { 0,0,0 };

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	const float kRotSpeed = 0.2f;
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}


	const float kMoveLimitX = 300.0f;
	const float kMoveLimitY = 300.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);


	//行列転送
	worldTransform_.UpdateMatrix();
	/*worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();*/

	ImGui::Begin("player");
	float sliderValue[3] = { worldTransform_.translation_.x,worldTransform_.translation_.y, worldTransform_.translation_.z };
	ImGui::SliderFloat3("position", sliderValue, -20.0f, 20.0f);
	worldTransform_.translation_ = { sliderValue[0],sliderValue[1],sliderValue[2] };
	ImGui::End();
	Attack();

	/*if (bullet_) {
		bullet_->Update();
	}*/
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	const float kDistancePlayerTo3DReticle = 10.0f;
	Vector3 offset = { 0.0f,0.0f,1.0f };
	offset = TransformNomal(offset, worldTransform_.matWorld_);
	offset = Normalize(offset) * kDistancePlayerTo3DReticle;
	worldTransform3DReticle_.translation_ = GetWorldPosition() + offset;
	worldTransform3DReticle_.UpdateMatrix();

	Vector3 positionReticle = {
		worldTransform3DReticle_.matWorld_.m[3][0],
		worldTransform3DReticle_.matWorld_.m[3][1],
		worldTransform3DReticle_.matWorld_.m[3][2]
	};

	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matViewProjectionViewport = viewProjection.matView * viewProjection.matProjection * matViewport;
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));


	POINT mousePosition;
	//マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	sprite2DReticle_=Get

	//ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV = viewProjection.matView * viewProjection.matProjection * matViewport;
	//合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	//スクリーン座標系からワールド座標系へ
	Vector3 posNear=Vector3()





}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	model_->Draw(worldTransform3DReticle_, viewProjection);
}


void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = TransformNomal(velocity, worldTransform_.matWorld_);
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);
		bullet_ = newBullet;
		bullets_.push_back(newBullet);
		velocity = GetWorldTransform3DReticle() - GetWorldPosition();
		velocity = Normalize(velocity) * kBulletSpeed;
	}
}

void Player::OnCollision() {
	//何もしない
}

void Player::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
}

Vector3 Player::GetWorldTransform3DReticle() {
	Vector3 worldPos;
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}

void Player::DrawUI() {
	sprite2DReticle_->Draw();
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


