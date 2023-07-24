#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "CollisionConfig.h"
class Collider
{
public:
	virtual void OnCollision();
	virtual Vector3 GetWorldPosition();
	float GetRadius() { return radius_; }
	void SetRadius(float radius) {
		radius_ = radius;
	}
	uint32_t GetCollisionAttribute() { return collisionAttribute_; }
	void SetCollisionAttribute(uint32_t collisionAttribute) {
		collisionAttribute_ = collisionAttribute;
	}

	uint32_t GetCollisionMask() { return collisionMask_; }
	void SetCollisionMask(uint32_t collisionMask) {
		collisionMask_ = collisionMask;
	}


private:
	float radius_ = 1.0f;
	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t collisionMask_ = 0xffffffff;
};