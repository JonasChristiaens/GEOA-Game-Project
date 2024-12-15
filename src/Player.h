#pragma once
#include "FlyFish.h"
#include "utils.h"

class Player {
public:
    Player(const ThreeBlade& startPosition, float size, const Color4f& color);

    void Move(float elapsedSec, const Rectf& viewport);
    void Draw() const;

private:
    ThreeBlade m_Position; 
    float m_Size;          
    Color4f m_Color;       
    float m_Speed{ 80.0f };
    float m_Direction[2];

    void HandleCollision(const Rectf& viewport);
};
