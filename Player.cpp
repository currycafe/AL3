#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHundle)
{
	//NULLのポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	//ワールド変換の初期化
	worldTransform_.Initialize();
	textureHundle_ = textureHundle;
}

void Player::Updete()
{
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection)
{
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}
