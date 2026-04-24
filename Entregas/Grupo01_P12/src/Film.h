#ifndef _FILM_H
#define _FILM_H
#include "Color.h"
#include <iostream>

class Film {
public:
    Film(int x, int y, std::ostream& output);
    Film(int x, int y);

    void AddPixel(Color color);

    int GetTamX() const { return _tamX; }
    int GetTamY() const { return _tamY; }

    float GetAspectRatio() const { return (float)_tamX / _tamY; }

private:
    int _tamX;
    int _tamY;

    std::ostream &_out;

    float _aspectRatio;

    bool missingHeader = true;
};

#endif