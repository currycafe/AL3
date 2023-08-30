#include "RailCamera.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"

void RailCamera::Initialize(Vector3 translation, Vector3 rotation) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;

	viewProjection_.Initialize();
}

void RailCamera::Update()
{
	Vector3 move = { 0.0f,0.0f,0.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;


	worldTransform_.rotation_.x += rotate.x;
	worldTransform_.rotation_.y += rotate.y;
	worldTransform_.rotation_.z += rotate.z;

	worldTransform_.UpdateMatrix();


	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();

	/*ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();*/
}
