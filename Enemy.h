#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "EnemyBullet.h"
#include <list>
#include "Player.h"


class Player;

class Enemy
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
	static const int kFireinterval = 10;
	void ApproachFire();

	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();



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
	Player* player_ = nullptr;
};

