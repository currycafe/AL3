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
	score_ = new Score;
	score_->Initialize();
	





}

void GameScene::Update() {
	/*_XINPUT_GAMEPAD A = {};
	ImGui::Begin("asdghj");
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_X);
	ImGui::Text("state.a=%d", A.wButtons & XINPUT_GAMEPAD_Y);
	ImGui::End();*/
	//score_->DrawScoreUI(7894);
	if (input_->TriggerKey(DIK_1)) {
		scoreNumber += 10;
	}
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


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);








	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//TextureHandle1_->Draw();
	score_->DrawScoreUI(scoreNumber);
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
