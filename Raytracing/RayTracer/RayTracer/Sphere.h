#pragma once
#include <memory>

#include "Material.h"
#include "Ray.hpp"
#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere(point3 center, double radius, const std::shared_ptr<Material>& material);

	point3 getCenter() const { return _center; }
	double getRadius() const { return _radius; }

protected:
	bool Intersect(const Ray& ray, float tMin, float tMax) const override;

private:
	point3 _center;
	double _radius;
	std::shared_ptr<Material> _material;
};

