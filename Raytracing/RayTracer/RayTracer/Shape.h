#pragma once
#include "Ray.hpp"

class Shape
{
public:
	Shape() = default;
	~Shape() = default;
protected:
	virtual bool Intersect(const Ray& ray, float tMin, float tMax) const = 0;
};

