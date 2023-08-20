#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
class RailCamera
{
public:
	void Initialize(Vector3 translation, Vector3 rotation);
	void Update();

	WorldTransform& GetWorldTransformProjection() { return worldTransform_; }
	ViewProjection& GetViewProjection() { return viewProjection_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

};

