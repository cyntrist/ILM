#pragma once
#include "Camera.hpp"
#include "Film.h"
#include "Shape.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Film> film, std::shared_ptr<Camera> camera, std::shared_ptr<Shape> shape);
	~Renderer();
		
	void Render(); // genera la escena
	Color RayColor(const Ray& r); // devuelve el color del rayo lanzado sobre la geometria

private:
	std::shared_ptr<Film> _film;
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Shape> _shape;
};
