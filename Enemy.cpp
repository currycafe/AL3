#include "Enemy.h"
#include "Input.h"
#include <cassert>
#include "ImGuiManager.h"
#include "MathUtility.h"
#include "Player.h"
#include <cmath>

Enemy::~Enemy()
{
	/*for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}*/
	if (bullet_) {
		delete bullet_;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHundle_ = TextureManager::Load("sample.png");
	worldTransform_.translation_ = position;
	//Fire();
	ApproachFire();
}



void Enemy::Update()
{
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});
	worldTransform_.UpdateMatrix();
	//worldTransform_.translation_.z -= 0.2f;

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		//今、止めてます。0.0です
		worldTransform_.translation_.z -= 0.0f;
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
	//Fire();
	/*if (bullet_) {
		bullet_->Draw(viewProjection);*/
		/*for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
		}*/
		//Fire();
	/*if (bullet_) {
		bullet_->Update();
	}*/
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
}

void Enemy::Fire()
{
	//if (input_->TriggerKey(DIK_Q)) {
	//	const float kBulletSpeed = -4.0f;
	//	Vector3 velocity(0, 0, kBulletSpeed);
	//	velocity = TransformNomal(velocity, worldTransform_.matWorld_);
	//	EnemyBullet* newBullet = new EnemyBullet();
	//	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//	bullet_ = newBullet;
	//	//bullets_.push_back(newBullet);
	//}

	const float kBulletSpeed = 1.0f;
	Vector3 a = GetWorldPosition();
	Vector3 b = player_->GetWorldPosition();
	Vector3 c = {};
	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;

	//c.x /= 100.0f;
	//c.y /= 100.0f;
	//c.z /= 100.0f;


	float length = sqrtf(c.x * c.x + c.y * c.y + c.z * c.z);
	Vector3 dir = { c.x / length, c.y / length, c.z / length };

	Vector3 velocity(kBulletSpeed* dir.x, kBulletSpeed*dir.y, kBulletSpeed* dir.z);
	//velocity = TransformNomal(velocity, worldTransform_.matWorld_);


	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	newBullet->SetPlayer(player_);
	//bullet_ = newBullet;
	bullets_.push_back(newBullet);

}

void Enemy::ApproachFire() {
	fireTimer = kFireinterval;
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

