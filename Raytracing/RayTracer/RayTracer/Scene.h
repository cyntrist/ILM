#pragma once
#include <memory>

#include "Shape.h"

class Scene : public Shape
{
public:
	Scene() = default;

	void Add(std::shared_ptr<Shape> sh);

private:
	std::vector<std::shared_ptr<Shape>> _sceneShapes;
};