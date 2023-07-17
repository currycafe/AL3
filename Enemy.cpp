#include "Enemy.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"

Enemy::~Enemy()
{
	/*for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}*/
	if (bullet_) {
		delete bullet_;
	}
	timedCalls_.remove_if([](TimedCall* timedCall) {
		delete timedCall;
		return true;
		});
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
	FireReset();
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
	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
		});

	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}


	switch (phase_) {
	case Enemy::Phase::Approach:
	default:

		worldTransform_.translation_.z -= 0.0f;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Enemy::Phase::Leave;
		}

		/*--fireTimer;
		if (fireTimer <= 0) {
			Fire();
			fireTimer = kFireinterval;
		}*/
		
		
		break;

	case Enemy::Phase::Leave:
		worldTransform_.translation_.y -= 0.2f;
		timedCalls_.clear();
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

	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, -kBulletSpeed, kBulletSpeed);
	velocity = TransformNomal(velocity, worldTransform_.matWorld_);
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//bullet_ = newBullet;
	bullets_.push_back(newBullet);
}

void Enemy::ApproachFire() {
	fireTimer = kFireinterval;

}

void Enemy::FireReset() {
	Fire();
	timedCalls_.push_back(new TimedCall(std::bind(&Enemy::FireReset, this), kFireinterval));
}
