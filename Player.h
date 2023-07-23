#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>

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
	/// <param name="model">モデル</param>
	/// <param name="textureHundle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHundle);
	/// <summary>
	/// 更新
	/// </summary>
	void Updete();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	void Draw(ViewProjection& viewProjection);
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHundle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
	//主人公の弾(単発)
	PlayerBullet* bullet_ = nullptr;
	//主人公の弾(複数)
	std::list<PlayerBullet*>bullets_;


};

