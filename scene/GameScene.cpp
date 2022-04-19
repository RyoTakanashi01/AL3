#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャ読み込み
	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//モデル生成
	model_ = Model::Create();
	
	//ワールドトランスフォームの初期化

	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};
	worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	worldTransform_.Initialize();
	
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();



	//サウンドデータ読み込み
	//soundDataHandle_ = audio_->LoadWave("se_sad03.wav");
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
	//audio_->SetVolume(soundDataHandle_, 0.01f);

}

void GameScene::Update() {}

	XMFLOAT2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);

	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
	}
	//value_++;
	//rot += XM_PI / 180.0f;
	//worldTransform_.rotation_ = {rot, rot, 0.0f};
	//worldTransform_.Initialize();
	/* 旧式
	std::string strDebug = std::string("Value:") + std::to_string(value_);
	debugText_->Print(strDebug, 50, 50, 1.0f);
	*/

	//新仕様
	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "scale:(%f, %f, %f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z); 
	debugText_->SetPos(50, 86);
	debugText_->Printf(
	  "rotation:(%f, %f, %f)", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);

	debugText_->SetPos(50, 102);
	debugText_->Printf(
	  "scale:(%f, %f, %f)", worldTransform_.scale_.x, worldTransform_.scale_.y,
	  worldTransform_.scale_.z);
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
	//Sprite::PostDraw();
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

	//sprite_->Draw();

	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
