#include "Player.h"
#include <iostream>

Player::Player(const ThreeBlade& startPosition, const ThreeBlade& pillarPosition, const Rectf& bounds, float size, float speed)
    : m_Position{ startPosition }
    , m_Movement{ pillarPosition[0], pillarPosition[1], 0, 0, 0, 200}
    , m_bounds{ bounds }
    , m_Size{ size }
    , m_Speed{ speed }
{}

void Player::Move(float elapsedSec) {
    Motor translator{ Motor::Translation(m_Speed * elapsedSec, m_Movement) };
    m_Position = (translator * m_Position * ~translator).Grade3();

    // Walls
    OneBlade leftWall{ 0, 0, 0, 720 };
    OneBlade bottomWall{ 0, 0, 1280, 0 };
    OneBlade rightWall{ 1280, 0, 1280, 720 };
    OneBlade topWall{ 0, 720, 1280, 720 };

    // Calculate distances from player to each wall
    float distanceToLeft = CalculateDistance(m_Position, leftWall);
    float distanceToRight = CalculateDistance(m_Position, rightWall);
    float distanceToTop = CalculateDistance(m_Position, topWall);
    float distanceToBottom = CalculateDistance(m_Position, bottomWall);

    const float threshold = 2.f;
    if (distanceToLeft <= threshold) {
        // Player has passed or is at the left wall: reverse x-direction
        m_Movement = TwoBlade(-m_Movement[0], m_Movement[1], m_Movement[2],
            m_Movement[3], m_Movement[4], m_Movement[5]);

        // Prevent player from going past the left wall
        m_Position[0] = m_Size / 2;  // Place player at the left edge
    }

    if (distanceToRight <= threshold) {
        // Player has passed or is at the right wall: reverse x-direction
        m_Movement = TwoBlade(-m_Movement[0], m_Movement[1], m_Movement[2],
            m_Movement[3], m_Movement[4], m_Movement[5]);

        // Prevent player from going past the right wall
        m_Position[0] = 1280 - m_Size / 2;  // Place player at the right edge
    }

    if (distanceToTop <= threshold) {
        // Player has passed or is at the top wall: reverse y-direction
        m_Movement = TwoBlade(m_Movement[0], -m_Movement[1], m_Movement[2],
            m_Movement[3], m_Movement[4], m_Movement[5]);

        // Prevent player from going past the top wall
        m_Position[1] = 720 - m_Size / 2;  // Place player at the top edge
    }

    if (distanceToBottom <= threshold) {
        // Player has passed or is at the bottom wall: reverse y-direction
        m_Movement = TwoBlade(m_Movement[0], -m_Movement[1], m_Movement[2],
            m_Movement[3], m_Movement[4], m_Movement[5]);

        // Prevent player from going past the bottom wall
        m_Position[1] = m_Size / 2;  // Place player at the bottom edge
    }

}

void Player::Rotate(float elapsedSec, const ThreeBlade& rotationPoint)
{
    Motor translationToOrigin = Motor::Translation(rotationPoint.VNorm(),
        TwoBlade(rotationPoint[0], rotationPoint[1], 0, 0, 0, 0));
    Motor rotator{ Motor::Rotation(m_Speed * elapsedSec, TwoBlade(0, 0, 0, 0, 0, 1))};

    rotator = (translationToOrigin * rotator * ~translationToOrigin);
    m_Position = (rotator * m_Position * ~rotator).Grade3();
}

void Player::Draw() const {
    utils::SetColor(Color4f{ 1,0,0,1 });
    utils::FillRect(m_Position[0], m_Position[1], m_Size, m_Size);
}

const ThreeBlade Player::GetCenter() const
{
    return ThreeBlade{ m_Position[0] + m_Size / 2, m_Position[1] + m_Size / 2, 0 };
}

float Player::CalculateDistance(const ThreeBlade& player, const OneBlade& wall)
{
    // Wall point positions
    float x1 = wall[0];
    float y1 = wall[1];
    float x2 = wall[2];
    float y2 = wall[3];

    // Player position
    float px = player[0];
    float py = player[1];

    // Distance from point to line
    float numerator = std::abs((y2 - y1) * px - (x2 - x1) * py + x2 * y1 - y2 * x1);
    float denominator = std::sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));

    return numerator / denominator;
}