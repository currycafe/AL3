#pragma once
#include"Model.h"
#include"Vector3.h"
#include"ViewProjection.h"
#include"WorldTransform.h"

class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(ViewProjection& viewProjection);
	
	bool IsDead()const { return isDead_; }
private:

	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	//速度
	Vector3 velocity_;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスflag
	bool isDead_ = false;
};