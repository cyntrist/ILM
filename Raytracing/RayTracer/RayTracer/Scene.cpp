#include "Scene.h"

void Scene::Add(std::shared_ptr<Shape> sh)
{
	_sceneShapes.push_back(sh);
}

bool Scene::Intersect(const Ray& ray, float tMin, float tMax) const
{
	
	return false;
}

bool Scene::Intersect(const Ray& ray, float tMin, float tMax, InfoIntersection& info) const
{
	
	return false;

}
