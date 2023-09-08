#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"


GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	Handle0_ = TextureManager::Load("0.png");
	Handle1_ = TextureManager::Load("1.png");
	Handle2_ = TextureManager::Load("2.png");
	Handle3_ = TextureManager::Load("3.png");
	Handle4_ = TextureManager::Load("4.png");
	Handle5_ = TextureManager::Load("5.png");
	Handle6_ = TextureManager::Load("6.png");
	Handle7_ = TextureManager::Load("7.png");
	Handle8_ = TextureManager::Load("8.png");
	Handle9_ = TextureManager::Load("9.png");


	TextureHandle0_ = Sprite::Create(Handle0_, { 0,0 });
	TextureHandle1_ = Sprite::Create(Handle1_, { 0,0 });
	TextureHandle2_ = Sprite::Create(Handle2_, { 0,0 });
	TextureHandle3_ = Sprite::Create(Handle3_, { 0,0 });
	TextureHandle4_ = Sprite::Create(Handle4_, { 0,0 });
	TextureHandle5_ = Sprite::Create(Handle5_, { 0,0 });
	TextureHandle6_ = Sprite::Create(Handle6_, { 0,0 });
	TextureHandle7_ = Sprite::Create(Handle7_, { 0,0 });
	TextureHandle8_ = Sprite::Create(Handle8_, { 0,0 });
	TextureHandle9_ = Sprite::Create(Handle9_, { 0,0 });





}

void GameScene::Update() {
	_XINPUT_GAMEPAD A = {};
	ImGui::Begin("asdghj");
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_X);
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_Y);
	ImGui::End();


}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	TextureHandle1_->Draw();


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);








	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
