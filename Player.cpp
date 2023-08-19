#include "Player.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="model"></param>
/// <param name="textureHundle"></param>
/// <param name="position"></param>
void Player::Initialize(Model* model, uint32_t textureHundle, const Vector3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = textureHundle;
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Updete() {
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	if (isDead_ == true) {
		return;
	}

	Vector3 move = { 0,0,0 };

	//主人公の移動処理
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

	////主人公の回転
	//const float kRotSpeed = 0.2f;
	//if (input_->PushKey(DIK_A)) {
	//	worldTransform_.rotation_.y -= kRotSpeed;
	//}
	//else if (input_->PushKey(DIK_D)) {
	//	worldTransform_.rotation_.y += kRotSpeed;
	//}

	//主人公の移動制限
	const float kMoveLimitX = 15.0f;
	const float kMoveLimitY = 15.0f;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	//行列転送
	worldTransform_.UpdateMatrix();

	//攻撃処理
	Attack();

	//自弾更新
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

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection"></param>
void Player::Draw(ViewProjection& viewProjection) {
	if (isDead_ == true) {
		return;
	}

	model_->Draw(worldTransform_, viewProjection, textureHundle_);
	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

/// <summary>
/// 攻撃処理
/// </summary>
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = TransformNomal(velocity, worldTransform_.matWorld_);
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);
		bullet_ = newBullet;
		bullets_.push_back(newBullet);
	}
}

/// <summary>
/// ヒットしたらどうするか
/// </summary>
void Player::OnCollision() {
	isDead_ = true;
	//bullets_.clear();
}

/// <summary>
/// 親子関係
/// </summary>
/// <param name="parent"></param>
void Player::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
}

/// <summary>
/// 主人公の座標
/// </summary>
/// <returns></returns>
Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}