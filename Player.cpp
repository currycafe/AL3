#include "Player.h"
#include "Input.h"
#include <cassert>


void Player::Initialize(Model* model, uint32_t textureHundle)
{
	//assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = textureHundle;
	input_ = Input::GetInstance();
}

void Player::Updete()
{
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection)
{
	
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}
