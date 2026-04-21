#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Film.h"
#include "Color.h"
#include "Camera.hpp"

#include <fstream>

#include "../../RayTracer/RayTracer/Sphere.h"

const glm::vec3 sphere_position{ 0.0, 0.0, 1.0 };
std::shared_ptr<Sphere> sphere() = std::make_shared

bool hit_sphere(std::shared_ptr<Sphere> sphere, const Ray& r)
{
    glm::vec3 oc = sphere->getCenter() - r.origin();

    auto a = glm::dot(r.direction(), r.direction());
    auto b = -2.0 * glm::dot(r.direction(), oc);
    auto c = glm::dot(oc, oc) - sphere->getRadius() * sphere->getRadius();
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

Color ray_color(const Ray& r)
{
    if (hit_sphere(sphere, r))
    {
        return Color(1, 0, 0);
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float a = 0.5 * (unit_direction.y + 1.0);
    return (1.0f - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main(void)
{
    std::ofstream out{ "imagen.ppm" };
    Film film{ 800, 600, out };
    glm::vec3 unit_direction{};

    const Camera cam{
        {0.0, 0.0, 0.0},
        sphere_position,
        {0.0, 1.0, 0.0},
        film,
        90.0
    };

    for (std::size_t y = 0; y < film.GetTamY(); ++y)
    {
        for (std::size_t x = 0; x < film.GetTamX(); ++x)
        {
            const Ray ray_primary = cam.get_ray(x, y);
            const Color c = ray_color(ray_primary);
            film.AddPixel(c);
        }
    }
    return 0;
}
