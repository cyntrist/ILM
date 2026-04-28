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

#include "CheckerTexture.h"
#include "ConstantTexture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Quad.h"
#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"

int main(void)
{
    std::ofstream out{ "imagen.ppm" };

    std::shared_ptr<Film> film = std::make_shared<Film>(800, 600, out);

    glm::vec3 position = { 0.0, 0.0, 3.0 };
    glm::vec3 look = { 0.0, 0.0, -1.0 };
    glm::vec3 up = { 0.0, 1.0, 0.0 };
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(position, look, up, film, 60.0);
    // materiales basicos
    std::shared_ptr<Material> azul = std::make_shared<Material>(BLUE);
    std::shared_ptr<Material> amarillo = std::make_shared<Material>(YELLOW);
    std::shared_ptr<Material> rojo = std::make_shared<Material>(RED);
    std::shared_ptr<Material> verde = std::make_shared<Material>(GREEN);
    // gloss factor
    azul->SetGlossFactor(0.5);
    amarillo->SetGlossFactor(0.5);
    rojo->SetGlossFactor(0.5);
    verde->SetGlossFactor(0.5);
    // texturas
    std::shared_ptr<ConstantTexture> verde_ajdrz = std::make_shared<ConstantTexture>(GREEN);
    std::shared_ptr<ConstantTexture> blanco_ajdrz = std::make_shared<ConstantTexture>(WHITE);
    std::shared_ptr<CheckerTexture> ajedrez = std::make_shared<CheckerTexture>(verde_ajdrz, blanco_ajdrz, 10, 10);
    // material con texturas
    std::shared_ptr<Material> ajedrez_material = std::make_shared<Material>(GREEN, ajedrez);

    std::shared_ptr<Quad> obj5 = std::make_shared<Quad>(point3(3, -1, -5), glm::vec3(-6, 0, 0), glm::vec3(0, 0, 6), ajedrez_material);
    std::shared_ptr<Sphere> obj4 = std::make_shared<Sphere>(glm::vec3(0, -100, -2), 99.0f, verde);
    std::shared_ptr<Sphere> obj3 =
        std::make_shared<Sphere>(glm::vec3(-2, 0, -2), 1.0f, rojo);
    std::shared_ptr<Sphere> obj2 =
        std::make_shared<Sphere>(glm::vec3(0, 0, -2), 1.0f, amarillo);
    std::shared_ptr<Sphere> obj1 =
        std::make_shared<Sphere>(glm::vec3(2, 0, -2), 1.0f, azul);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->Add(obj1); scene->Add(obj2); scene->Add(obj3); 
	//scene->Add(obj4); // suelo esfera
	scene->Add(obj5); // suelo quad

    std::shared_ptr<World> world = std::make_shared<World>(scene);

    glm::vec3 dir = { 1.0, 1.0, 0.0 };
    std::shared_ptr<DirectionalLight> dirLight = std::make_shared<DirectionalLight>(dir, WHITE);

    glm::vec3 pos = { 2.0, 2.0, 0.0 };
    std::shared_ptr<PointLight> pointLight = std::make_shared<PointLight>(pos, WHITE);
    glm::vec3 pos2 = { -2.0, 2.0, -3.0 };
    std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(pos2, WHITE);

    dirLight->SetGlossPower(400);
    pointLight->SetGlossPower(400);
    pointLight2->SetGlossPower(400);

    //world->AddLight(dirLight);
    world->AddLight(pointLight);
    world->AddLight(pointLight2);

    Renderer renderer(film, cam, world);
    renderer.Render();

    return 0;
}
