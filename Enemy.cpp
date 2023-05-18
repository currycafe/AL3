#include "Enemy.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"

void Enemy::Initialize(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = TextureManager::Load("sample.png");
	worldTransform_.translation_ = position;
}

void Enemy::Updete()
{
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_.z -= 0.2f;
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}

