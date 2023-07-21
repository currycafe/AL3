#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
class Collider
{
public:
	virtual void OnCollision();
	virtual Vector3 GetWorldPosition();
	float GetRadius() { return radius_; }
	void SetRadius(float radius) {
		radius_ = radius;
	}



private:
	float radius_ = 1.0f;



};

