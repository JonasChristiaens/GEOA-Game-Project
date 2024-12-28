#pragma once
#include "FlyFish.h"
#include "utils.h"

class Player {
public:
    Player(const ThreeBlade& startPosition, const ThreeBlade& pillarPosition, const Rectf& bounds, float size, float speed);

    void Move(float elapsedSec);
    void Rotate(float elapsedSec, const ThreeBlade& rotationPoint);
    void Draw() const;

    const ThreeBlade GetCenter() const;

private:
    float CalculateDistance(const ThreeBlade& player, const OneBlade& wall);

    ThreeBlade m_Position;
    TwoBlade m_Movement;
    const Rectf& m_bounds;

    float m_Speed;
    float m_Size;
};
