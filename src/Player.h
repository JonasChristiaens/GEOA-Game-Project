#pragma once
#include "FlyFish.h"
#include "utils.h"

class Player {
public:
    Player(float x, float y, float width, float height, float windowWidth, float windowHeight);

    void Move(const ThreeBlade& direction, float elapsedSec);
    void Draw() const;

    const ThreeBlade& GetDirection() const {
        return m_Direction;
    }

private:
    ThreeBlade m_Position;
    ThreeBlade m_Direction;
    float m_Width;
    float m_Height;
    float m_WindowWidth;
    float m_WindowHeight;

    void HandleCollision();
};
