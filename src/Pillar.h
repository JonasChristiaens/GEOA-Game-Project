#pragma once
#include "FlyFish.h"
#include "utils.h"

class Pillar
{
public:
	Pillar(const ThreeBlade& startPosition, float size);

	void Draw();
	void HorizontalOscillate(float elapsedSec);
	void VerticalOscillate(float elapsedSec);

	ThreeBlade GetCenter() const;
private:
	ThreeBlade m_Position;
	float m_Size;
};