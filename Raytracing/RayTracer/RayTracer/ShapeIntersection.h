#pragma once
#include "Material.h"

struct InfoIntersection // almacena la informacion de una colision
{
	Material intersectionMat; // el material del que esta hecho el objeto con el que se ha colisionado el rayo
	float t; // punto en el que el rayo ha producido colision, solamente devuelve la info de la primera colision (para controlar objetos encima de objetos)
};