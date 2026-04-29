#pragma once

#include "Film.h"

class SDLViewer
{
public:
    SDLViewer(int width, int height, const char* title = "RayTracer");
    ~SDLViewer();

    bool Show(const Film& film);

private:
    int _width;
    int _height;

    struct SDL_Window* _window = nullptr;
    struct SDL_Renderer* _renderer = nullptr;
    struct SDL_Texture* _texture = nullptr;
    bool _initialized = false;
};
