#pragma once
#include "Color.h"

class Material
{
public: 
	Material(Color color);

	Color GetColor() const
	{
		return _color;
	}

	float GetGlossFactor() const
	{
		return _glossFactor;
	}

private:
	Color _color;
	float _glossFactor;
};
