#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"



class Player
{
public:
	void Initialize(Model*model,uint32_t textureHundle);
	void Updete();
	void Draw(ViewProjection&viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;

	Input* input_ = nullptr;
	
	void Initialize();

};

