#include "Player.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"


Player::~Player()
{
	//データ解放
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}


void Player::Initialize(Model* model, uint32_t textureHundle)
{
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = textureHundle;
	input_ = Input::GetInstance();
}

void Player::Updete()
{
	//キャラの移動ベクトル
	Vector3 move = { 0,0,0 };
	//キャラの移動の速さ
	const float kCharacterSpeed = 0.2f;
	//押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	//押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	//回転の速さ
	const float kRotSpeed = 0.2f;
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
	//座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
	//ワールド行列=スケーリング行列*回転行列*平行移動行列
	//行列更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//行列転送
	worldTransform_.TransferMatrix();
	//移動制限座標
	const float kMoveLimitX = 10.0f;
	const float kMoveLimitY = 10.0f;
	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	//キャラクター攻撃処理
	Attack();
	//弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	//デバッグ表示
	ImGui::Begin("player");
	float sliderValue[3] = { worldTransform_.translation_.x,worldTransform_.translation_.y, worldTransform_.translation_.z };
	ImGui::SliderFloat3("position", sliderValue, -20.0f, 20.0f);
	worldTransform_.translation_ = { sliderValue[0],sliderValue[1],sliderValue[2] };
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
	//弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		bullet_ = newBullet;
		//弾を登録する
		bullets_.push_back(newBullet);
	}
}


