#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include"PlayerBullet.h"
#include<list>
#include"Enemy.h"

class Player
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHundle"></param>
	/// <param name="position"></param>
	void Initialize(Model* model, uint32_t textureHundle, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Updete();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// ヒットしたらどうするか
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 自弾リスト化
	/// </summary>
	/// <returns></returns>
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	/// <summary>
	/// 半径
	/// </summary>
	/// <returns></returns>
	float GetRadius() { return radius_; }

	/// <summary>
	/// 親子関係
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent);

private:
	/// <summary>
	/// ワールド変換データ
	/// </summary>
	WorldTransform worldTransform_;

	/// <summary>
	/// モデル
	/// </summary>
	Model* model_ = nullptr;

	/// <summary>
	/// テクスチャハンドル
	/// </summary>
	uint32_t textureHundle_ = 0u;

	/// <summary>
	/// キーボード入力
	/// </summary>
	Input* input_ = nullptr;

	/// <summary>
	/// 主人公の弾
	/// </summary>
	PlayerBullet* bullet_ = nullptr;

	/// <summary>
	/// 主人公の弾のリスト化
	/// </summary>
	std::list<PlayerBullet*>bullets_;

	/// <summary>
	/// 主人公の半径
	/// </summary>
	float radius_ = 1.0f;


};

