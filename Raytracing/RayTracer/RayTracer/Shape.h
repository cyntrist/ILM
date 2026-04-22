#pragma once
#include "Ray.hpp"

class Shape
{
public:
	Shape() = default;
	~Shape() = default;

	// Determina si el rayo pasado como parametro interseca con el objeto o no
	// La colision se evalua unicamente en el segmento del rayo en el que el 
	// multiplicador de su direccion (t, parametro de la funcion at) esta entre tMin y tMax
	virtual bool Intersect(const Ray& ray, float tMin, float tMax) const;
};