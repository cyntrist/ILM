#pragma once

#include "InfoIntersection.h"
#include "Ray.hpp"

class Light
{
public:
	Light() = default;

	// recibe:
	// - el rayo que provoca el calculo (que viene desde la camara) y 
	// - la informacion de la colision con el objeto
	// devuelve:
	// - el color resultante
	virtual Color Shade(Ray r, InfoIntersection& hit); // calcula el color de un rayo que choca con una superficie

	bool GetShadow() const
	{
		return _shadow;
	}

	// calcula la direccion desde position hasta la luz
	virtual glm::vec3 ShadowDir(glm::vec3 position);

protected:
	bool _shadow; // si la luz genera sombras o no
};