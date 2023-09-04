#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>
#include"ImGuiManager.h"
#include"stdio.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete modelSkydome_;
	delete skydome_;
	delete railCamera_;
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	delete titleTextureHandle_;
	delete sceneCangeHandle_;
	delete playerModel_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();


	playerModel_ = Model::CreateFromOBJ("spray", true);
	enemyModel_ = Model::CreateFromOBJ("cockroach", true);

	model_ = Model::Create();
	//playerModel_ = Model::CreateFromOBJ("needle_Body", true);

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//敵を消す
	//enemies_.clear();
	//enemyBullets_.clear();

	player_ = new Player();
	player_->Initialize(playerModel_, textureHandle_, { 0.0f,-5.0f,20.0f });

	AddEnemy({ 0.0f,3.0f,80.0f });
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	railCamera_ = new RailCamera();
	railCamera_->Initialize({ 0.0f,0.0f,-20.0f }, { 0.0f,0.0f,0.0f });

	player_->SetParent(&railCamera_->GetWorldTransformProjection());

	LoadEnemyPopData();
	//UpdateEnemyPopCommands();


	//画像読み込み
	textureHandle_ = TextureManager::Load("sample.png");
	titleTexture_ = TextureManager::Load("title.png");
	operationTexture_ = TextureManager::Load("operation.png");
	supplementTexture_ = TextureManager::Load("Supplement.png");
	gameClearTexture_ = TextureManager::Load("GameClear.png");
	gameOverTexture_ = TextureManager::Load("GameOver.png");
	sceneCangeTexture_ = TextureManager::Load("Sprite-0001.png");
	level1Texture_ = TextureManager::Load("Level1.png");
	level2Texture_ = TextureManager::Load("Level2.png");
	level3Texture_ = TextureManager::Load("Level3.png");
	level4Texture_ = TextureManager::Load("Level4.png");
	level5Texture_ = TextureManager::Load("Level5.png");


	//画像生成
	titleTextureHandle_ = Sprite::Create(titleTexture_, { 0,0 });
	operationTextureHandle_ = Sprite::Create(operationTexture_, { 0,0 });
	supplementTextureHandle_ = Sprite::Create(supplementTexture_, { 0,0 });
	gameClearTextureHandle_ = Sprite::Create(gameClearTexture_, { 0,0 });
	gameOverTextureHandle_ = Sprite::Create(gameOverTexture_, { 0,0 });
	level1TextureHandle_ = Sprite::Create(level1Texture_, { 0,0 });
	level2TextureHandle_ = Sprite::Create(level2Texture_, { 0,0 });
	level3TextureHandle_ = Sprite::Create(level3Texture_, { 0,0 });
	level4TextureHandle_ = Sprite::Create(level4Texture_, { 0,0 });
	level5TextureHandle_ = Sprite::Create(level5Texture_, { 0,0 });

	//シーン遷移
	sceneCangeHandle_ = Sprite::Create(sceneCangeTexture_, { 0,0 });
	sceneCangeHandle_->SetColor(Vector4{ 1,1,1,0 });

	soundHandle_ = audio_->LoadWave("051_long_BPM140.wav");
	audio_->PlayWave(soundHandle_);
	clearHandle_ = audio_->LoadWave("se_amd03.wav");
	shotHandle_ = audio_->LoadWave("sd006_05.wav");
	selectHandle_ = audio_->LoadWave("se_sab03.wav");
	gameOverHandle_ = audio_->LoadWave("se_sua02.wav");
}

void GameScene::Update() {
	if (scene_ == GameScene::Scene::Supplement || scene_ == GameScene::Scene::GamePlay) {
		SceneCange(Scene::GamePlay);  
	}
	switch (scene_) {
	case GameScene::Scene::Title:
		Vector2 positeion = titleTextureHandle_->GetPosition();
		if (input_->TriggerKey(DIK_RETURN)) {
			audio_->PlayWave(selectHandle_, false, 1.0f);
			scene_ = Scene::Operation;
		}
		titleTextureHandle_->SetPosition(positeion);
		enemyBullets_.clear();
		enemies_.clear();
		player_->SetIsDead(false);
		break;

	case GameScene::Scene::Operation:
		if (input_->TriggerKey(DIK_RETURN)) {
			audio_->PlayWave(selectHandle_, false, 1.0f);
			scene_ = Scene::Supplement;
		}
		break;

	case GameScene::Scene::Supplement:
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(selectHandle_, false, 1.0f);
			SceneCange(Scene::GamePlay);
			//scene_ = Scene::GamePlay;
		}
		break;

	case GameScene::Scene::GamePlay:
		player_->Updete();
		skydome_->Update();
		railCamera_->Update();
		CheckAllCollisions();
		UpdateEnemyPopCommands();
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(shotHandle_, false, 1.0f);
		}
		enemyBullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
			});

		enemies_.remove_if([](Enemy* enemy) {
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}
			return false;
			});

		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}
		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Update();
		}
#ifdef  _DEBUG
		if (input_->TriggerKey(DIK_1)) {
			isDebugCameraActive_ = true;
		}
#endif //  _DEBUG
		if (isDebugCameraActive_) {
			debugCamera_->Update();
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		}
		else if (!isDebugCameraActive_) {
			viewProjection_.matView = railCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		}
		break;

	case GameScene::Scene::GameClear:
		if (input_->TriggerKey(DIK_RETURN)) {
			audio_->PlayWave(selectHandle_, false, 1.0f);
			scene_ = Scene::Title;
		}
		break;

	case GameScene::Scene::GameOver:
		if (input_->TriggerKey(DIK_RETURN)) {
			audio_->PlayWave(selectHandle_, false, 1.0f);
			scene_ = Scene::Title;
		}
		break;
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
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}
	for (Enemy* enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (scene_ == GameScene::Scene::Title) {
		titleTextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::Operation) {
		operationTextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::Supplement) {
		supplementTextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GameClear) {
		gameClearTextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GameOver) {
		gameOverTextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GamePlay && levelFlag_ == 1) {
		level1TextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GamePlay && levelFlag_ == 2) {
		level2TextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GamePlay && levelFlag_ == 3) {
		level3TextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GamePlay && levelFlag_ == 4) {
		level4TextureHandle_->Draw();
	}
	if (scene_ == GameScene::Scene::GamePlay && levelFlag_ == 5) {
		level5TextureHandle_->Draw();
	}
	sceneCangeHandle_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA;
	Vector3 posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemyBullets_;

#pragma region
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullets : enemyBullets) {
		posB = bullets->GetWorldPosition();

		float distance = (posB.x - posA.x) * (posB.x - posA.x) +
			(posB.y - posA.y) * (posB.y - posA.y) +
			(posB.z - posA.z) * (posB.z - posA.z);

		if (distance <= player_->GetRadius() + bullets->GetRadius()) {
			player_->OnCollision();
			bullets->OnCollision();
			scene_ = Scene::GameOver;
			audio_->PlayWave(gameOverHandle_, false, 1.0f);
			enemyPopComands.clear();
			enemyPopComands.seekg(0, std::ios::beg);
			levelFlag_ = 1;
		}
	}

#pragma endregion

#pragma region
	for (Enemy* enemy : enemies_) {
		posA = enemy->GetWorldPosition();
		for (PlayerBullet* bullets : playerBullets) {
			posB = bullets->GetWorldPosition();

			float distance = (posB.x - posA.x) * (posB.x - posA.x) +
				(posB.y - posA.y) * (posB.y - posA.y) +
				(posB.z - posA.z) * (posB.z - posA.z);

			if (distance <= player_->GetRadius() + bullets->GetRadius()) {
				enemy->OnCollision();
				bullets->OnCollision();
			}
		}

	}
#pragma endregion

#pragma region
	for (PlayerBullet* playerbullets : playerBullets) {
		for (EnemyBullet* enemybullets : enemyBullets) {
			posA = playerbullets->GetWorldPosition();
			posB = enemybullets->GetWorldPosition();
			float distance = (posB.x - posA.x) * (posB.x - posA.x) +
				(posB.y - posA.y) * (posB.y - posA.y) +
				(posB.z - posA.z) * (posB.z - posA.z);
			if (distance <= playerbullets->GetRadius() + enemybullets->GetRadius()) {
				playerbullets->OnCollision();
				enemybullets->OnCollision();
			}
		}
	}
#pragma endregion
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::AddEnemy(Vector3 pos) {
	Enemy* enemy = new Enemy();
	enemy->Initialize(enemyModel_, pos);
	enemy->SetPlayer(player_);
	enemy->SetGameScene(this);
	enemies_.push_back(enemy);
}

void GameScene::LoadEnemyPopData() {
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	//assert(file.is_open());
	enemyPopComands << file.rdbuf();

	file.close();

}

void GameScene::UpdateEnemyPopCommands() {
	if (waitFlag_ == true) {
		waitTimer_--;
		if (waitTimer_ <= 0) {
			waitFlag_ = false;
		}
		return;
	}

	std::string line;

	while (getline(enemyPopComands, line)) {
		std::istringstream line_stream(line);
		std::string word;

		getline(line_stream, word, ',');
		if (word.find("//") == 0) {
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			AddEnemy(Vector3(x, y, z));
		}
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());

			//待機開始
			waitFlag_ = true;
			waitTimer_ = waitTime;
			//コマンドループを抜けます
			break;
		}
		else if (word.find("count") == 0) {
			getline(line_stream, word, ',');
			levelFlag_ += 1;
		}
		else if (word.find("clear") == 0) {
			getline(line_stream, word, ',');
			audio_->PlayWave(clearHandle_, false, 1.0f);
			scene_ = Scene::GameClear;
			//再度読み込み
			enemyPopComands.clear();
			enemyPopComands.seekg(0, std::ios::beg);
			levelFlag_ = 1;
		}
	}
}

void GameScene::SceneCange(Scene scene) {
	if (scene_ == GameScene::Scene::Supplement) {
		if (input_->PushKey(DIK_SPACE) && IsSceneCangeFlag_ == false) {
			IsSceneCangeFlag_ = true;
			IsSceneCangeFlagUp_ = true;
			IsSceneCangeFlagDown_ = false;
		}
	}
	if (IsSceneCangeFlag_ == true) {
		if (IsSceneCangeFlagUp_ == true) {
			alpha_ += 0.01f;
		}
		if (alpha_ >= 1.0f && IsSceneCangeFlagUp_ == true) {
			IsSceneCangeFlagUp_ = false;
			IsSceneCangeFlagDown_ = true;
			scene_ = scene;
		}
		if (IsSceneCangeFlagDown_ == true) {
			alpha_ -= 0.1f;
		}
		if (alpha_ <= 0.0f) {
			alpha_ = 0.0f;
			IsSceneCangeFlag_ = false;
		}
		sceneCangeHandle_->SetColor(Vector4{ 1,1,1,alpha_ });
	}
}