#include "SDLViewer.h"
#include <SDL3/SDL.h>

SDLViewer::SDLViewer(int width, int height, const char* title)
    : _width(width), _height(height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return;
    }

    if (!SDL_CreateWindowAndRenderer(title, _width, _height, SDL_WINDOW_RESIZABLE, &_window, &_renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    _texture = SDL_CreateTexture(
        _renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        _width,
        _height);

    if (!_texture)
    {
        SDL_Log("SDL_CreateTexture failed: %s", SDL_GetError());
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        _renderer = nullptr;
        _window = nullptr;
        return;
    }

    _initialized = true;
}

SDLViewer::~SDLViewer()
{
    if (_texture)
    {
        SDL_DestroyTexture(_texture);
    }

    if (_renderer)
    {
        SDL_DestroyRenderer(_renderer);
    }

    if (_window)
    {
        SDL_DestroyWindow(_window);
    }

    if (_initialized)
    {
        SDL_Quit();
    }
}

bool SDLViewer::Show(const Film& film)
{
    if (!_initialized)
    {
        return false;
    }

    if (!SDL_UpdateTexture(_texture, nullptr, film.Data(), film.Pitch()))
    {
        SDL_Log("SDL_UpdateTexture failed: %s", SDL_GetError());
    }

    SDL_RenderClear(_renderer);
    SDL_RenderTexture(_renderer, _texture, nullptr, nullptr);
    SDL_RenderPresent(_renderer);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        SDL_Delay(16);
    }

    return true;
}
