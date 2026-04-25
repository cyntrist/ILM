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

	void SetGlossFactor(float gf)
	{
		_glossFactor = gf;
	}

private:
	Color _color;
	float _glossFactor = 0;
};
