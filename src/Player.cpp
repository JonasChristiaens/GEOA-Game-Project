#include "Player.h"
#include <algorithm>

Player::Player(float x, float y, float width, float height, float windowWidth, float windowHeight)
    : m_Position(x, y, 0.0f)
    , m_Direction(200.f, 100.f, 0.f)
    , m_Width(width)
    , m_Height(height)
    , m_WindowWidth(windowWidth)
    , m_WindowHeight(windowHeight) {
}

void Player::Move(const ThreeBlade& direction, float elapsedSec) {
    m_Position += direction * elapsedSec;
    HandleCollision();
}

void Player::Draw() const {
    utils::SetColor(Color4f(1.0f, 0.f, 0.f, 1.0f));
    utils::FillRect(m_Position[0] - m_Width / 2, m_Position[1] - m_Height / 2, m_Width, m_Height);
}

void Player::HandleCollision() {
    // horizontal collision
    if (m_Position[0] - m_Width / 2 <= 0.0f || m_Position[0] + m_Width / 2 >= m_WindowWidth) {
        m_Direction[0] = -m_Direction[0];
        m_Position[0] = std::clamp(m_Position[0], m_Width / 2, m_WindowWidth - m_Width / 2);
    }

    // vertical collision
    if (m_Position[1] - m_Height / 2 <= 0.0f || m_Position[1] + m_Height / 2 >= m_WindowHeight) {
        m_Direction[1] = -m_Direction[1];
        m_Position[1] = std::clamp(m_Position[1], m_Height / 2, m_WindowHeight - m_Height / 2);
    }
}
