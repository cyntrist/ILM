#include "Material.h"

Material::Material(Color color, const std::shared_ptr<Texture>& texture)
	: _color(color), _texture(texture)
{

}

Material::Material(Color color)
	: _color(color)
{
}