#include "Film.h"

Film::Film(int x, int y, std::ostream& output) 
	: _tamX(x), _tamY(y), _aspectRatio(1.0f * _tamX / _tamY), _out(output)
{}

Film::Film(int x, int y)
    : Film(x, y, std::cout) 
{}

void Film::AddPixel(Color color) 
{
    if (missingHeader) 
    {
        _out << "P3\n" << _tamX << ' ' << _tamY << "\n255\n";
        missingHeader = false;
    }

    int ir = (int)(255.99 * color.x);
    int ig = (int)(255.99 * color.y);
    int ib = (int)(255.99 * color.z);

    _out << ir << ' ' << ig << ' ' << ib << '\n';
}
