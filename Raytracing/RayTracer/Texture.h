#pragma once
#include "Color.h"

class Texture
{
public:
	virtual ~Texture();
	virtual Color color(float u, float v) const = 0;
};
