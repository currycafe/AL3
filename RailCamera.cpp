#include "RailCamera.h"
#include "Input.h"
#include <cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"

void RailCamera::Initialize()
{

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void RailCamera::Update()
{

}
