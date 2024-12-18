#include "Pillar.h"

Pillar::Pillar(const ThreeBlade& startPosition, float size)
	: m_Position{ startPosition }
	, m_Size{ size }
{}

void Pillar::Draw()
{
	utils::SetColor(Color4f{ 1,0,1,1 });
	utils::FillRect(m_Position[0], m_Position[1], m_Size, m_Size);
}

void Pillar::HorizontalOscillate(float elapsedSec)
{
}

void Pillar::VerticalOscillate(float elapsedSec)
{
}

ThreeBlade Pillar::GetCenter() const
{
	return ThreeBlade{ m_Position[0] + m_Size / 2, m_Position[1] + m_Size / 2, 0 };
}