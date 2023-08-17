#include "Title.h"
#include "Input.h"
#include "TextureManager.h"

void Title::Initialize(uint32_t textureHundle, const Vector3& position) {
	textureHundle_ = textureHundle;
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
}


void Title::Update() {

	Draw();

}


void Title::Draw() {
	textureHundle_ = TextureManager::Load("sample.png");
}