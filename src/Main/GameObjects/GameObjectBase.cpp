//
//  GameObjectBase.cpp
//
//  Created by Mortimer Pavlitski on 15/04/2018.
//

#include "GameObjectBase.hpp"

GameObjectBase::GameObjectBase()
:
    xPos_(0),
    yPos_(0),
    width_(0),
    height_(0)
{
}

GameObjectBase::~GameObjectBase() {
}

//

void GameObjectBase::setBounds(float x, float y, float w, float h) {
    xPos_   = x;
    yPos_   = y;
    width_  = w;
    height_ = h;
}

void GameObjectBase::setVelocity(Vector vel) {
    vel_.x  = vel.x;
    vel_.y  = vel.y;
    updatePosition();
}

Vector GameObjectBase::getVelocity() {
    return vel_;
}

void GameObjectBase::updatePosition() {
    xPos_   += vel_.x;
    yPos_   += vel_.y;
}

//

float GameObjectBase::getX() {
    return xPos_;
}

float GameObjectBase::getY() {
    return yPos_;
}

float GameObjectBase::getW() {
    return width_;
}

float GameObjectBase::getH() {
    return height_;
}


void GameObjectBase::setX(float xPos) {
    xPos_ = xPos;
}

void GameObjectBase::setY(float yPos) {
    yPos_ = yPos;
}

void GameObjectBase::setW(float width) {
    width_ = width;
}

void GameObjectBase::setH(float height) {
    height_ = height;
}
