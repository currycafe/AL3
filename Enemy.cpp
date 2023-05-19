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
	//worldTransform_.translation_.z -= 0.2f;
	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		worldTransform_.translation_.z -= 0.2f;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Enemy::Phase::Leave;
		}
		break;

	case Enemy::Phase::Leave:
		worldTransform_.translation_.y -= 0.2f;
		break;
	}
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}

