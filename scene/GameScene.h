#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>
#include <stdint.h>

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

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();


	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	void AddEnemyBullet(EnemyBullet* enemyBullet);
	const std::list<EnemyBullet*>& GetBullets() { return enemyBullets_; }


	void AddEnemy(Vector3 pos);
	void LoadEnemyPopData();
	void UpdateEnemyPopCommands();

	enum class Scene {
		title,
		GamePlay
	};

	void SceneCange(Scene scene);



private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Sprite* titleTextureHandle_ = nullptr;
	Sprite* sceneCangeHandle_ = nullptr;

	uint32_t textureHandle_ = 0;
	uint32_t titleTexture_ = 0;
	uint32_t sceneCangeTexture_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;


	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	RailCamera* railCamera_ = nullptr;
	//float imputFloat3[3] = { 0,0,0 };

	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	std::list<EnemyBullet*>enemyBullets_;
	std::list<Enemy*>enemies_;
	std::stringstream enemyPopComands;

	bool waitFlag_ = false;
	int32_t waitTimer_ = 120;

	//Sprite* sprite_ = nullptr;

	Scene scene_ = Scene::title;

	uint32_t gameTimer_ = 3000;

	bool IsSceneCangeFlag_ = false;
	bool IsSceneCangeFlagUp_ = false;
	bool IsSceneCangeFlagDown_ = false;

	float alpha = 0;

};
