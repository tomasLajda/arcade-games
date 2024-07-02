//
// Created by ja on 7/1/24.
//

#include "gameScene.h"

GameScene::GameScene(std::unique_ptr<Game> optrGame): mGame(std::move(optrGame)) {}

void GameScene::Init() {
    mGame->Init(mGameController);
}

void GameScene::Update(uint32_t deltaTime) {
    mGame->Update(deltaTime);
}

void GameScene::Draw(Screen &screen) {
    mGame->Draw(screen);
}

const std::string &GameScene::GetSceneName() const {
    static std::string name = "";
    return name;
}