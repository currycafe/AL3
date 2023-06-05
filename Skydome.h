#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

class Skydome
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& viewProjection);





private:
	WorldTransform worldTransform_;
	Model*model_=nullptr;
};

