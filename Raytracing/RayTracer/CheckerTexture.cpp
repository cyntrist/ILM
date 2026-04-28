#include "CheckerTexture.h"

CheckerTexture::CheckerTexture(const std::shared_ptr<Texture>& texture1, const std::shared_ptr<Texture>& texture2, 
    int f, int c)
	    : _texture1(texture1), _texture2(texture2), _f(f), _c(c)
{
}

Color CheckerTexture::color(float u, float v) const
{
    return Color();
}