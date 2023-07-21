#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "EnemyBullet.h"
#include <list>
#include "Player.h"
#include "Collider.h"


class Player;

class Enemy :public Collider
{
public:
	enum class Phase {
		Approach,
		Leave,
	};


	~Enemy();
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Fire();
	static const int kFireinterval = 30;
	void ApproachFire();

	void SetPlayer(Player* player) { player_ = player; }
	void OnCollision()override;
	Vector3 GetWorldPosition()override;
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; }
	float GetRadius() { return radius_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;
	Input* input_ = nullptr;
	EnemyBullet* bullet_ = nullptr;

	std::list<EnemyBullet*>bullets_;

	Enemy::Phase phase_ = Enemy::Phase::Approach;
	int32_t fireTimer = 0;

	//自キャラ
	//Enemy* enemy_ = nullptr;
	Player* player_ = nullptr;

	float radius_ = 1.0f;
};

