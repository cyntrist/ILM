#pragma once
#include <memory>

#include "Material.h"
#include "Ray.hpp"
#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere(point3 center, float radius, const std::shared_ptr<Material>& material);

	point3 getCenter() const { return _center; }
	float getRadius() const { return _radius; }

protected:
	bool Intersect(const Ray& ray, float tMin, float tMax) const override;
	bool Intersect(const Ray& ray, float tMin, float tMax, InfoIntersection& info) const override;

private:
	point3 _center;
	float _radius;
	std::shared_ptr<Material> _material;
};

