#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Film.h"
#include "Color.h"
#include "Camera.hpp"

#include <memory>

#include <fstream>

#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"

// listado 16 raytracing en un fin de semana para el calculo de la interseccion entre una esfera y un rayo

const glm::vec3 sphere_position{ 0.0, 0.0, 1.0 };
const float sphere_radius = 0.5f;

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

    std::shared_ptr<Film> film = std::make_shared<Film>(1920, 1080, out);

    glm::vec3 position = { 0.0, 0.0, 0.0 };
    glm::vec3 look = { 0.0, 0.0, 1.0 };
    glm::vec3 up = { 0.0, 1.0, 0.0 };
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(position, look, up, film, 90.0);

    std::shared_ptr<Material> azul = std::make_shared<Material>(BLUE);
    std::shared_ptr<Material> amarillo = std::make_shared<Material>(YELLOW);
    std::shared_ptr<Material> rojo = std::make_shared<Material>(RED);

    std::shared_ptr<Sphere> obj3 =
        std::make_shared<Sphere>(glm::vec3(-1, 0, -1), sphere_radius, azul);
    std::shared_ptr<Sphere> obj2 =
        std::make_shared<Sphere>(glm::vec3(0, 0, -2), sphere_radius * 2, amarillo);
    std::shared_ptr<Sphere> obj1 =
        std::make_shared<Sphere>(glm::vec3(1, 0, -1), sphere_radius, rojo);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->Add(obj1); scene->Add(obj2); scene->Add(obj3);

    Renderer renderer(film, cam, scene);
    renderer.Render();

    return 0;
}
