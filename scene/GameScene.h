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
	/// シーン名
	/// </summary>
	enum class Scene {
		Title,
		Operation,
		Supplement,
		GamePlay,
		GameClear,
		GameOver
	};
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


	void SceneCange(Scene scene);



private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	RailCamera* railCamera_ = nullptr;
	Skydome* skydome_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;


	Scene scene_ = Scene::Title;


	bool isDebugCameraActive_ = false;

	std::list<EnemyBullet*>enemyBullets_;
	std::list<Enemy*>enemies_;
	std::stringstream enemyPopComands;

	int32_t waitTimer_ = 120;
	bool waitFlag_ = false;

	Sprite* sprite_ = nullptr;

	//シーンチェンジのフラグたち
	bool IsSceneCangeFlag_ = false;
	bool IsSceneCangeFlagUp_ = false;
	bool IsSceneCangeFlagDown_ = false;
	float alpha_ = 0;
	int levelFlag_ = 1;






	//画像の読み込みとモデルの方々
	uint32_t textureHandle_ = 0;
	uint32_t titleTexture_ = 0;
	uint32_t operationTexture_ = 0;
	uint32_t supplementTexture_ = 0;
	uint32_t gameClearTexture_ = 0;
	uint32_t gameOverTexture_ = 0;
	uint32_t sceneCangeTexture_ = 0;
	uint32_t level1Texture_ = 0;
	uint32_t level2Texture_ = 0;
	uint32_t level3Texture_ = 0;
	uint32_t level4Texture_ = 0;
	uint32_t level5Texture_ = 0;

	Sprite* titleTextureHandle_ = nullptr;
	Sprite* operationTextureHandle_ = nullptr;
	Sprite* supplementTextureHandle_ = nullptr;
	Sprite* gameClearTextureHandle_ = nullptr;
	Sprite* gameOverTextureHandle_ = nullptr;
	Sprite* sceneCangeHandle_ = nullptr;
	Sprite* level1TextureHandle_ = nullptr;
	Sprite* level2TextureHandle_ = nullptr;
	Sprite* level3TextureHandle_ = nullptr;
	Sprite* level4TextureHandle_ = nullptr;
	Sprite* level5TextureHandle_ = nullptr;


	Model* model_ = nullptr;
	Model* playerModel_ = nullptr;
	Model* playerBulletModel_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* modelSkydome_ = nullptr;


	uint32_t soundHandle_ = 0;
	uint32_t shotHandle_ = 0;
	uint32_t clearHandle_ = 0;
	uint32_t selectHandle_ = 0;
	uint32_t gameOverHandle_ = 0;
};
