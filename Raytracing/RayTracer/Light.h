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
};