#pragma once
#include "Color.h"

class Material
{
public: 
	Material(Color color);

	Color getColor() const
	{
		return _color;
	}

private:
	Color _color;
};
