#include "CheckerTexture.h"

CheckerTexture::CheckerTexture(const std::shared_ptr<Texture>& texture1, const std::shared_ptr<Texture>& texture2, 
    int f, int c)
	    : _texture1(texture1), _texture2(texture2), _f(f), _c(c)
{
}

Color CheckerTexture::color(float u, float v) const
{
    int uInt = std::floor(u * _c);
    int vInt = std::floor(v * _f);

    bool isEven = (uInt + vInt) % 2 == 0;

    return isEven ? _texture1->color(u, v) : _texture2->color(u, v);
}