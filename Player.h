#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include"PlayerBullet.h"
#include<list>



class Player
{
public:
	void Initialize(Model* model, uint32_t textureHundle);
	void Updete();
	void Draw(ViewProjection& viewProjection);
	void Attack();
	//~Player();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;

	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;

	std::list<PlayerBullet*>bullets_;


};

