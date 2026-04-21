#include "Renderer.h"

Renderer::Renderer(std::shared_ptr<Film> film, std::shared_ptr<Camera> camera, std::shared_ptr<Shape> shape)
{

}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
}

Color Renderer::ray_color(const Ray& r)
{
	return Color();
}
