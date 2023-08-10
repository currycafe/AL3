#include"PlayerBullet.h"
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
/// <param name="model"></param>
/// <param name="position"></param>
/// <param name="velocity"></param>
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("sample.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerBullet::Update() {
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
	worldTransform_.UpdateMatrix();
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection"></param>
void PlayerBullet::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}

/// <summary>
/// 当たったらデスフラグtrue
/// </summary>
void PlayerBullet::OnCollision() {
	isDead_ = true;
}

/// <summary>
/// ワールド変換データ
/// </summary>
Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}


