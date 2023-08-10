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
	/// <param name="model"></param>
	/// <param name="position"></param>
	/// <param name="velocity"></param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// ヒットしたらどうするか
	/// </summary>
	void OnCollision();

	bool IsDead()const { return isDead_; }

	/// <summary>
	/// 自弾の半径
	/// </summary>
	/// <returns></returns>
	float GetRadius() { return radius_; }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

private:
	/// <summary>
	/// ワールド変換データ
	/// </summary>
	WorldTransform worldTransform_;

	/// <summary>
	/// モデル
	/// </summary>
	Model* model_;

	/// <summary>
	/// テクスチャハンドル
	/// </summary>
	uint32_t texturehandle_;

	/// <summary>
	/// 弾の速度
	/// </summary>
	Vector3 velocity_;

	/// <summary>
	/// 寿命
	/// </summary>
	static const int32_t kLifeTime = 60 * 5;

	/// <summary>
	/// デスタイマー
	/// </summary>
	int32_t deathTimer_ = kLifeTime;

	/// <summary>
	/// デスフラグ
	/// </summary>
	bool isDead_ = false;

	/// <summary>
	/// 自弾の半径
	/// </summary>
	float radius_ = 1.0f;
};