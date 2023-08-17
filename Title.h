#pragma once
#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Title {
private:
	/// <summary>
	/// テクスチャハンドル
	/// </summary>
	uint32_t textureHundle_ = 0u;

	/// <summary>
	/// キーボード入力
	/// </summary>
	Input* input_ = nullptr;


	/// <summary>
	/// ワールド変換データ
	/// </summary>
	WorldTransform worldTransform_;
public:
	void Initialize(uint32_t textureHundle, const Vector3& position);
	void Update();
	void Draw();
	
};

