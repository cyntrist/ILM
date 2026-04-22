#include "Sphere.h"

Sphere::Sphere(point3 center, double radius, const std::shared_ptr<Material>& material)
	: _center(center), _radius(radius), _material(material)
{
	
}

bool Sphere::Intersect(const Ray& ray, float tMin, float tMax) const
{
	return false;
}
