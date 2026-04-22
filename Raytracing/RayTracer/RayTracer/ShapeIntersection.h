#pragma once
#include "Material.h"
#include "Ray.hpp"

struct InfoIntersection
{
	Material material;
	float t; // punto en el que el rayo ha producido colision, solamente devuelve la info de la primera colision (para controlar objetos encima de objetos)
};

class ShapeIntersection
{
public:
	// Determina si el rayo pasado como parametro interseca con el objeto o no
	// La colision se evalua unicamente en el segmento del rayo en el que el 
	// multiplicador de su direccion (t, parametro de la funcion at) esta entre tMin y tMax
	bool Intersect(const Ray& ray, float tMin, float tMax, InfoIntersection& info);

private:
	Material _intersectionMat; // el material del que esta hecho el objeto con el que se ha colisionado el rayo
};
