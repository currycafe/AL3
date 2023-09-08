#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	int number_ = 54825;
	int eachNumber[5] = {};
	int flag_ = 1;

	uint32_t Handle0_ = 0;
	uint32_t Handle1_ = 0;
	uint32_t Handle2_ = 0;
	uint32_t Handle3_ = 0;
	uint32_t Handle4_ = 0;
	uint32_t Handle5_ = 0;
	uint32_t Handle6_ = 0;
	uint32_t Handle7_ = 0;
	uint32_t Handle8_ = 0;
	uint32_t Handle9_ = 0;

	/*uint32_t numberHandle_ = {


	};*/
	Sprite* TextureHandle0_ = nullptr;
	Sprite* TextureHandle1_ = nullptr;
	Sprite* TextureHandle2_ = nullptr;
	Sprite* TextureHandle3_ = nullptr;
	Sprite* TextureHandle4_ = nullptr;
	Sprite* TextureHandle5_ = nullptr;
	Sprite* TextureHandle6_ = nullptr;
	Sprite* TextureHandle7_ = nullptr;
	Sprite* TextureHandle8_ = nullptr;
	Sprite* TextureHandle9_ = nullptr;


};
