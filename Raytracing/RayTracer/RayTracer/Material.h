#pragma once
#include "Color.h"
#include "InfoIntersection.h"
#include "Texture.h"

#include <memory>

class Material
{
public: 
	Material(Color color, const std::shared_ptr<Texture>& texture);
	Material(Color color);

	Color GetColor() const
	{
		return _color;
	}

	Color GetColor(InfoIntersection& ii) const
	{
		if (_texture != nullptr)
		{
			return _texture->color(ii.u, ii.v);
		}
		else
		{
			return GetColor(); // si es nula llama al GetColor por defecto
		}
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

	std::shared_ptr<Texture> _texture;
};
