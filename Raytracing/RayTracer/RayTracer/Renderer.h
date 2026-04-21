#pragma once
#include "Camera.hpp"
#include "Film.h"
#include "Shape.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Film> film, std::shared_ptr<Camera> camera, std::shared_ptr<Shape> shape);
	~Renderer();
		
	void Render();
	Color ray_color(const Ray& r);
};
