#include "Sphere.h"

Sphere::Sphere(point3 center, double radius)
	: _center(center), _radius(radius)
{
	
}

Sphere::~Sphere()
{

}

bool Sphere::Intersect(const Ray& ray, float tMin, float tMax) const
{
	return false;
}
