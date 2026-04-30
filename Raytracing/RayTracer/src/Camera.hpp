#pragma once

#include <memory>
#include <random>

#include "glm/vec3.hpp"
#include "Film.h"
#include "Ray.hpp"

class Camera 
{
public:
    Camera(
        glm::vec3 position,
        glm::vec3 look,
        glm::vec3 up,
        const std::shared_ptr<Film>& film,
        float fov_degrees_vertical);

    Camera(
        glm::vec3 position,
        glm::vec3 look,
        glm::vec3 up,
        const std::shared_ptr<Film>& film,
        float fov_degrees_vertical,
        float focalLength,
        float blurDegrees);

    Ray GetRay(int x, int y) const;

private:
    glm::vec3 position;
    glm::vec3 delta_x;
    glm::vec3 delta_y;
    glm::vec3 position_top_left;

    float _focalLength; // distancia focal
    float _blurDegrees; // angulo desenfoque

    float desenfoqueU = 0;
    float desenfoqueV = 0;

    std::random_device rd{};
    std::mt19937 gen{ rd() };
};