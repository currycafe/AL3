#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include"PlayerBullet.h"
#include<list>
#include"Enemy.h"
#include"Sprite.h"



class Player
{
public:
	~Player();
	void Initialize(Model* model, uint32_t textureHundle, const Vector3& position);
	void Updete(ViewProjection& viewProjection);
	void Draw(ViewProjection& viewProjection);
	void Attack();
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	void OnCollision();
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }
	float GetRadius() { return radius_; }
	void SetParent(const WorldTransform* parent);
	Vector3 GetWorldTransform3DReticle();
	void DrawUI();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;

	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;

	std::list<PlayerBullet*>bullets_;
	float radius_ = 1.0f;
	WorldTransform worldTransform3DReticle_;
	Sprite* sprite2DReticle_ = nullptr;
	

};

