#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player
{
public:
	/// <summary>
	/// 
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

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHundle_ = 0u;
};

