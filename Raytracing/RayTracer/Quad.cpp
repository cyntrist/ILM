#include "Quad.h"

Quad::Quad(point3 bottom_left, glm::vec3 u, glm::vec3 v, const std::shared_ptr<Material>& material)
{

}

bool Quad::Intersect(const Ray& ray, float tMin, float tMax) const
{
    return false;
}

bool Quad::Intersect(const Ray& ray, float tMin, float tMax, InfoIntersection& info) const
{
    return false;
}
