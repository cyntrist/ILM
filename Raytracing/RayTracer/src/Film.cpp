#include "Film.h"

Film::Film(int x, int y, std::ostream& output)
    : _tamX(x), _tamY(y), _aspectRatio(1.0f * _tamX / _tamY), _out(output)
{
}

Film::Film(int x, int y)
    : _tamX(x), _tamY(y), _aspectRatio(1.0f * _tamX / _tamY)
{
    _pixels.reserve(_tamX * _tamY * 4);
}

// original
//void Film::AddPixel(Color color)
//{
//    if (missingHeader)
//    {
//        _out << "P3\n" << _tamX << ' ' << _tamY << "\n255\n";
//        missingHeader = false;
//    }
//
//    int ir = (int)(255.99 * color.x);
//    int ig = (int)(255.99 * color.y);
//    int ib = (int)(255.99 * color.z);
//
//    _out << ir << ' ' << ig << ' ' << ib << '\n';
//}

unsigned char Film::UnitTo255(float v) 
{
    if (v < 0.0f) return 0;
    if (v > 1.0f) return 255;
    return static_cast<unsigned char>(255.99f * v);
}

void Film::AddPixel(Color color)
{
    _pixels.push_back(UnitTo255(color.x));
    _pixels.push_back(UnitTo255(color.y));
    _pixels.push_back(UnitTo255(color.z));
    _pixels.push_back(255);
}