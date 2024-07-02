//
// Created by ja on 7/1/24.
//

#include "arcadeScene.h"
#include "../graphics/screen.h"
#include "../shapes/line2D.h"
#include "../shapes/triangle.h"
#include "../shapes/AARectangle.h"
#include "../shapes/circle.h"
#include "../shapes/star2D.h"
#include <iostream>

ArcadeScene::ArcadeScene() {

}

void ArcadeScene::Init() {
    ButtonAction action;
    action.key = GameController::ActionKey();
    action.action = [](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            std::cout << "Action button was pressed!" << std::endl;
        }
    };

    mGameController.AddInputActionForKey(action);

    MouseButtonAction mouseAction;
    mouseAction.mouseButton = GameController::LeftMouseButton();
    mouseAction.mouseInputAction = [](InputState state, const MousePosition &position) {
        if(GameController::IsPressed(state)) {
            std::cout << "Left Mouse button pressed!" << std::endl;
        }
    };

    mGameController.AddMouseButtonAction(mouseAction);

    mGameController.SetMouseMovedAction([](const MousePosition &mousePosition) {
        std::cout << "Mouse position x: " << mousePosition.xPos << ", y: " << mousePosition.yPos << std::endl;
    });
}

void ArcadeScene::Update(u_int32_t deltaTime) {

}

void ArcadeScene::Draw(Screen &theScreen) {
    Triangle triangle = Triangle(Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110));
    AARectangle rectangle = AARectangle(Vec2D(100, 100), Vec2D(200, 200));
    Circle circle = Circle(Vec2D(100, 100), 50);
    Star2D star = Star2D(10, 20, Vec2D(100, 100), 6);

    theScreen.Draw(triangle, Color(200, 0, 0, 100), true, Color(40, 0, 0, 10));
    theScreen.Draw(rectangle, Color(0, 0, 255, 250), true, Color(0, 0, 255, 255));
    theScreen.Draw(circle, Color(0, 255, 0, 10), true, Color(0, 100, 0, 100));
    theScreen.Draw(star, Color::Orange());
}

const std::string &ArcadeScene::GetSceneName() const {
    static std::string sceneName = "Arcade Scene";
    return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
    switch(game) {
        case TETRIS: {

        }
        break;

        case BREAK_OUT: {

        }
        break;

        case ASTEROIDS: {

        }
        break;

        case PACMAN: {

        }
        break;

        default: {

        }
        break;
    }

    return nullptr;
}