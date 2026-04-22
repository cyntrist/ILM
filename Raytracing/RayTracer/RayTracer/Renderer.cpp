#include "Renderer.h"

#include <geometric.hpp>

Renderer::Renderer(std::shared_ptr<Film> film, std::shared_ptr<Camera> camera, std::shared_ptr<Shape> shape)
	: _film(film), _camera(camera), _shape(shape)
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
            const Ray ray_primary = _camera->get_ray(x, y);
            const Color c = ray_color(ray_primary);
            _film->AddPixel(c);
        }
    }
}

Color Renderer::ray_color(const Ray& r)
{
    InfoIntersection ii;
    if (_shape->Intersect(r, 0, 100, ii))
    {
        return ii.m->getColor();
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float a = 0.5 * (unit_direction.y + 1.0);
    return (1.0f - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
