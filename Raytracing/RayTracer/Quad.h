#pragma once
#include <memory>

#include "Material.h"
#include "Ray.hpp"
#include "Shape.h"

class Quad : public Shape
{
public:
	Quad(point3 bottom_left, glm::vec3 u, glm::vec3 v, const std::shared_ptr<Material>& material);

protected:
	bool Intersect(const Ray& ray, float tMin, float tMax) const override;
	bool Intersect(const Ray& ray, float tMin, float tMax, InfoIntersection& info) const override;

private:
	point3 _bottomLeft;
	glm::vec3 _u;
	glm::vec3 _v;

	// v
	// |
	// +-- u
};