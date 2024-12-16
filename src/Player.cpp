#include "Player.h"
#include <iostream>

Player::Player(const ThreeBlade& startPosition, const Rectf& bounds, float size, float speed)
    : m_Position{ startPosition }
    , m_Direction{ 1, 1, 0, 0, 0, 0 }
    , m_bounds{ bounds }
    , m_Size{ size }
    , m_Speed{ speed }
{}

void Player::Move(float elapsedSec) {
    Motor translator{ Motor::Translation(m_Speed * elapsedSec, m_Direction) };
    m_Position = (translator * m_Position * ~translator).Grade3();

    // check collision with walls
    if (CheckCollision())
    {
        // reverse direction in which collision was detected
        ReverseDirection();
    }
}

void Player::Rotate(float elapsedSec, const ThreeBlade& rotationPoint)
{
    Motor translationToOrigin = Motor::Translation(rotationPoint.VNorm(),
        TwoBlade(rotationPoint[0], rotationPoint[1], rotationPoint[2], 0, 0, 0));
    Motor rotator{ Motor::Rotation(m_Speed * elapsedSec,TwoBlade{0, 0, 0, 0, 0, -1}) };

    rotator = (translationToOrigin * rotator * ~translationToOrigin);
    m_Position = (rotator * m_Position * ~rotator).Grade3();
}

void Player::Draw() const {
    utils::SetColor(Color4f{ 1,0,0,1 });
    utils::FillRect(m_Position[0], m_Position[1], m_Size, m_Size);
}

const ThreeBlade& Player::GetPosition() const
{
    return m_Position;
}

void Player::ReverseDirection() {
    // Reverse the x-direction if the player hits the left or right bounds
    if (m_Position[0] <= m_bounds.left || m_Position[0] + m_Size >= m_bounds.left + m_bounds.width) {
        m_Direction = TwoBlade(-m_Direction[0], m_Direction[1], m_Direction[2],
            m_Direction[3], m_Direction[4], m_Direction[5]);
    }

    // Reverse the y-direction if the player hits the top or bottom bounds
    if (m_Position[1] <= m_bounds.bottom || m_Position[1] + m_Size >= m_bounds.bottom + m_bounds.height) {
        m_Direction = TwoBlade(m_Direction[0], -m_Direction[1], m_Direction[2],
            m_Direction[3], m_Direction[4], m_Direction[5]);
    }
}

bool Player::CheckCollision() {
    return (m_Position[0] <= m_bounds.left || m_Position[0] + m_Size >= m_bounds.left + m_bounds.width ||
        m_Position[1] <= m_bounds.bottom || m_Position[1] + m_Size >= m_bounds.bottom + m_bounds.height);
}
