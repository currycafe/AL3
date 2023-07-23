#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "EnemyBullet.h"
#include <list>

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

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;
	Input* input_ = nullptr;
	EnemyBullet* bullet_ = nullptr;

	std::list<EnemyBullet*>bullets_;

	Phase phase_ = Phase::Approach;
	int32_t fireTimer = 0;
};

