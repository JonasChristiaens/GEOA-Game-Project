#include "Player.h"
#include <algorithm>

Player::Player(const ThreeBlade& startPosition, float size, const Color4f& color)
    : m_Position(startPosition)
    , m_Size(size)
    , m_Color(color)            
    , m_Direction{ 1.0f, 0.0f }
{

}

void Player::Move(float elapsedSec, const Rectf& viewport) {
    Motor translator{ Motor::Translation(m_Speed * elapsedSec, TwoBlade{m_Direction[0], m_Direction[1], 0, 0, 0, 0}) };
    m_Position = (translator * m_Position * ~translator).Grade3();

    HandleCollision(viewport);
}

void Player::Draw() const {
    utils::SetColor(m_Color);
    utils::FillRect(m_Position[0], m_Position[1], m_Size, m_Size);
}

void Player::HandleCollision(const Rectf& viewport) {

    // Reverse horizontal direction if hitting left or right sides
    if (m_Position[0] < viewport.left || m_Position[0] + m_Size > viewport.left + viewport.width)
    {
        m_Direction[0] = -m_Direction[0];
    }

    // Reverse vertical direction if hitting top or bottom sides
    if (m_Position[1] < viewport.bottom || m_Position[1] + m_Size > viewport.bottom + viewport.height)
    {
        m_Direction[1] = -m_Direction[1];
    }
}
