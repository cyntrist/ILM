// Nieves Alonso Gilsanz
// Cynthia Tristán Álvarez
// Grupo 01
// Iluminación y Materiales
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

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


int main(void)
{
    std::ofstream out{ "imagen.ppm" };

    std::shared_ptr<Film> film = std::make_shared<Film>(1920, 1080, out);

    glm::vec3 position = { 0.0, 0.0, 0.0 };
    glm::vec3 look = { 0.0, 0.0, -1.0 };
    glm::vec3 up = { 0.0, 1.0, 0.0 };
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(position, look, up, film, 90.0);

    std::shared_ptr<Material> azul = std::make_shared<Material>(BLUE);
    std::shared_ptr<Material> amarillo = std::make_shared<Material>(YELLOW);
    std::shared_ptr<Material> rojo = std::make_shared<Material>(RED);

    std::shared_ptr<Sphere> obj3 =
        std::make_shared<Sphere>(glm::vec3(-1, 0, -1), 0.5f, azul);
    std::shared_ptr<Sphere> obj2 =
        std::make_shared<Sphere>(glm::vec3(0, 0, -2), 1.0f, amarillo);
    std::shared_ptr<Sphere> obj1 =
        std::make_shared<Sphere>(glm::vec3(1, 0, -1), 0.5f, rojo);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->Add(obj1); scene->Add(obj2); scene->Add(obj3);

    Renderer renderer(film, cam, scene);
    renderer.Render();

    return 0;
}
