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


}


void Player::Initialize(Model* model, uint32_t textureHundle, const Vector3& position){
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = textureHundle;
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
}

void Player::Updete()
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

}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
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
	}
}

void Player::OnCollision() {
	//何もしない
}

void Player::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


