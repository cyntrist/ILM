#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

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

    glm::vec3 desenfoqueU;
    glm::vec3 desenfoqueV;

    std::random_device rd;
    mutable std::mt19937 gen{ rd() };
    std::uniform_real_distribution<float> pDistr;

    glm::vec3 RandomEnCirculo() const;
};