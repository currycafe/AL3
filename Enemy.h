#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"




class Enemy
{
public:
	void Initialize(Model* model, const Vector3& position);
	void Updete();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;

	//enum class Phase {
	//	Approach,
	//	Leave,
	//};
	//Phase phase_ = Phase::Approach;

};

