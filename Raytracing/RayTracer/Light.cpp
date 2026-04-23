#include "Light.h"

Color Light::Shade(Ray r, InfoIntersection& hit)
{
	Color ret; // color resultante

	// Ambiente
	ret += WHITE; // Luz de ambiente cableada

	return ret; 
}