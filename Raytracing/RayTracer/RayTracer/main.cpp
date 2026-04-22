#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Film.h"
#include "Color.h"
#include "Camera.hpp"

#include <memory>

#include <fstream>

#include "Renderer.h"
#include "Sphere.h"

// listado 16 raytracing en un fin de semana para el calculo de la interseccion entre una esfera y un rayo

const glm::vec3 sphere_position{ 0.0, 0.0, 1.0 };
const glm::vec3 sphere_center{ 0.0, 0.0, -1.0 }; 

static bool hit_sphere(std::shared_ptr<Sphere> sphere, const Ray& r)
{
    glm::vec3 oc = sphere->getCenter() - r.origin();

    auto a = glm::dot(r.direction(), r.direction());
    auto b = -2.0 * glm::dot(r.direction(), oc);
    auto c = glm::dot(oc, oc) - sphere->getRadius() * sphere->getRadius();

    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

int main(void)
{
    std::ofstream out{ "imagen.ppm" };

    std::shared_ptr<Film> film = std::make_shared<Film>(800, 600, out);

    glm::vec3 position = { 0.0, 0.0, 0.0 };
    glm::vec3 look = { 0.0, 0.0, 1.0 };
    glm::vec3 up = { 0.0, 1.0, 0.0 };
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(position, look, up, film, 90.0);

    std::shared_ptr<Material> rojo = std::make_shared<Material>(RED);
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(sphere_position, 0.5, rojo);

    Renderer renderer(film, cam, sphere);
    renderer.Render();

    return 0;
}
