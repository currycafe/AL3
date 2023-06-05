#include "Skydome.h"

void Skydome::Initialize(Model* model)
{
	model_ = model;
	worldTransform_.Initialize();
}

void Skydome::Update()
{
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
