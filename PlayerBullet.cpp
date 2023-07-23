#include"PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& pos) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	//テクスチャハンドル読み込み
	texturehandle_ = TextureManager::Load("sample.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = pos;
}

void PlayerBullet::Update() {
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}
