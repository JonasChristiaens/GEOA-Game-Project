#pragma once
#include "FlyFish.h"
#include "utils.h"

class Player {
public:
    Player(const ThreeBlade& startPosition, const Rectf& bounds, float size, float speed);

    void Move(float elapsedSec);
    void Rotate(float elapsedSec, const ThreeBlade& rotationPoint);
    void Draw() const;

    const ThreeBlade& GetPosition() const;

private:
    void ReverseDirection();
    bool CheckCollision();


    ThreeBlade m_Position;
    TwoBlade m_Direction;
    const Rectf& m_bounds;

    float m_Speed;
    float m_Size;
};
