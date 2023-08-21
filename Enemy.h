#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "EnemyBullet.h"
#include <list>
#include "Player.h"

/// <summary>
/// 前方宣言の方々
/// </summary>
class Player;
class GameScene;

class Enemy
{
public:
	/// <summary>
	/// フェイズ
	/// </summary>
	enum class Phase {
		Approach,
		Leave,
	};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="position"></param>
	void Initialize(Model* model, const Vector3& position);

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
	/// 敵の攻撃
	/// </summary>
	void Fire();

	/// <summary>
	/// インターバル
	/// </summary>
	static const int kFireinterval = 30;
	void ApproachFire();

	void SetPlayer(Player* player) { player_ = player; }
	void OnCollision();
	Vector3 GetWorldPosition();

	float GetRadius() { return radius_; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	bool IsDead() { return isDead_; };


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


	EnemyBullet* bullet_ = nullptr;
	GameScene* gameScene_ = nullptr;

	/// <summary>
	/// 初期フェーズ::Approach
	/// </summary>
	Enemy::Phase phase_ = Enemy::Phase::Approach;

	/// <summary>
	/// タイマー
	/// </summary>
	int32_t fireTimer = 0;

	//自キャラ
	Player* player_ = nullptr;

	/// <summary>
	/// 敵の半径
	/// </summary>
	float radius_ = 1.0f;

	/// <summary>
	/// 敵の寿命
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


};
