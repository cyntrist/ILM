#include "Sphere.h"
#include "ray.hpp"
#include <cmath>
#include "glm/geometric.hpp"

Sphere::Sphere(point3 center, float radius, const std::shared_ptr<Material>& material)
	: _center(center), _radius(radius), _material(material)
{
	
}

bool Sphere::Intersect(const Ray& ray, float tMin, float tMax) const
{
    glm::vec3 oc = _center - ray.Origin();
    auto a = glm::squared_length(ray.Direction()); // he "hecho" squared_length pero realmente es lo mismo que glm::dot(v, v)
    auto h = dot(ray.Direction(), oc);
    auto c = glm::squared_length(oc) - _radius * _radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (root <= tMin || tMax <= root) {
        root = (h + sqrtd) / a;
        if (root <= tMin || tMax <= root)
            return false;
    }

    return true;
}

bool Sphere::Intersect(const Ray& ray, float tMin, float tMax, InfoIntersection& info) const
{
    glm::vec3 oc = _center - ray.Origin();
    auto a = glm::squared_length(ray.Direction());
    auto h = dot(ray.Direction(), oc);
    auto c = glm::squared_length(oc) - _radius * _radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (root <= tMin || tMax <= root) {
        root = (h + sqrtd) / a;
        if (root <= tMin || tMax <= root)
            return false;
    }

    info.t = root;
    info.p = ray.At(info.t);
    info.normal = (info.p - _center) / _radius;

    info.m = _material;

    return true;
}
