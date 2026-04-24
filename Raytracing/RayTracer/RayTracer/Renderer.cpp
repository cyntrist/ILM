#include "Renderer.h"

#include "glm/geometric.hpp"

Renderer::Renderer(std::shared_ptr<Film> film, std::shared_ptr<Camera> camera, std::shared_ptr<World> world)
	: _film(film), _camera(camera), _world(world)
{

}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
    for (std::size_t y = 0; y < _film->GetTamY(); ++y)
    {
        for (std::size_t x = 0; x < _film->GetTamX(); ++x)
        {
            const Ray ray_primary = _camera->GetRay(x, y);
            const Color c = RayColor(ray_primary);
            _film->AddPixel(c);
        }
    }
}

Color Renderer::RayColor(const Ray& r)
{
    InfoIntersection ii;
    if (_world->GetScene()->Intersect(r, 0, 100, ii))
    {
        Color color = ii.m->GetColor();

        for (auto l : _world->GetLights())
        {
            if (l->GetShadow())
            {
                Ray shadowRay = Ray(ii.p, l->ShadowDir(ii.p));

                if (_world->GetScene()->Intersect(shadowRay, 0, 100, ii))
                {
	                // saltar a la siguiente geometria
                    continue;
                }
            }

            color += l->Shade(r, ii);
        }

        return color;
    }

    return BLACK;
    // Skybox
    /*
    glm::vec3 unit_direction = glm::normalize(r.Direction());
    float a = 0.5 * (unit_direction.y + 1.0);
    return (1.0f - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	*/
}