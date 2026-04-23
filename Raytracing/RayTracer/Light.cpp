#include "Light.h"

Color Light::Shade(Ray r, InfoIntersection& hit)
{
	Color ret; // color resultante

	// Ambiente
	ret += Color(1, 0, 0); // Luz de ambiente cableada

	return ret; 
}