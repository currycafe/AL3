#include "Enemy.h"
#include "Input.h"
#include <cassert>
#include "ImGuiManager.h"
#include "MathUtility.h"
#include "Player.h"
#include <cmath>
#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="model"></param>
/// <param name="position"></param>
void Enemy::Initialize(Model* model, const Vector3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = TextureManager::Load("sample.png");
	worldTransform_.translation_ = position;
	ApproachFire();
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		//今、止めてます。0.0です
		worldTransform_.translation_.z -= 0.2f;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Enemy::Phase::Leave;
		}
		--fireTimer;
		if (fireTimer <= 0) {
			Fire();
			fireTimer = kFireinterval;
		}
		break;

	case Enemy::Phase::Leave:
		worldTransform_.translation_.y -= 0.2f;
		break;
	}

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}


void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}


void Enemy::Fire() {
	const float kBulletSpeed = 1.0f;
	Vector3 a = GetWorldPosition();
	Vector3 b = player_->GetWorldPosition();
	Vector3 c = {};
	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;

	float length = sqrtf(c.x * c.x + c.y * c.y + c.z * c.z);
	Vector3 dir = { c.x / length, c.y / length, c.z / length };

	Vector3 velocity(kBulletSpeed * dir.x, kBulletSpeed * dir.y, kBulletSpeed * dir.z);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachFire() {
	fireTimer = kFireinterval;
}

void Enemy::OnCollision() {
	isDead_ = true;
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

