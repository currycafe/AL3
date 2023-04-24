#include "Player.h"
#include "Input.h"
#include <cassert>


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
	Vector3 move = { 0,0,0 };

	const float kCharacterSpeed = 0.2f;



	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y += kCharacterSpeed;
	}


	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;


	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);



	//行列転送
	worldTransform_.TransferMatrix();



}

void Player::Draw(ViewProjection& viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}
