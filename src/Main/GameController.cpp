//
//  GameController.cpp
//  PhysicsGameEngineTesting
//
//  Created by Mortimer Pavlitski on 24/01/2018.
//

#include "GameController.hpp"

void GameController::keyDown(int key) {
    switch(key) {
        case 357:       // up key
            isUpPressed_    = true;
            break;
        case 359:       // down key
            isDownPressed_  = true;
            break;
        case 356:       // left key
            isLeftPressed_  = true;
            break;
        case 358:       // right key
            isRightPressed_ = true;
            break;
        case 32:        // Space bar
            isSpacePressed_ = true;
            break;
    }
}

void GameController::keyUp(int key) {
    switch(key) {
        case 357:       // up key
            isUpPressed_    = false;
            break;
        case 359:       // down key
            isDownPressed_  = false;
            break;
        case 356:       // left key
            isLeftPressed_  = false;
            break;
        case 358:       // right key
            isRightPressed_ = false;
            break;
        case 32:        // Space bar
            isSpacePressed_ = false;
            break;
    }
}

//

bool GameController::getIsUpPressed() {
    return isUpPressed_;
}

bool GameController::getIsDownPressed() {
    return isDownPressed_;
}

bool GameController::getIsLeftPressed() {
    return isLeftPressed_;
}

bool GameController::getIsRightPressed() {
    return isRightPressed_;
}

bool GameController::getIsSpacePressed() {
    return isSpacePressed_;
}
