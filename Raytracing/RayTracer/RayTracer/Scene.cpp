#include "Scene.h"

void Scene::Add(std::shared_ptr<Shape> sh)
{
	_sceneShapes.push_back(sh);
}