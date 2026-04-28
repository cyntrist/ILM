#include "DirectionalLight.h"

#include <iostream>
#include <detail/func_geometric.inl>

DirectionalLight::DirectionalLight(glm::vec3 direction, Color color)
	: _direction(direction), _color(color)
{
    _shadow = false;
}

Color DirectionalLight::Shade(Ray r, InfoIntersection& hit)
{
    // Diffuse
    //float intensity = std::max(0.0f, glm::dot(hit.normal, _direction));
    //glm::vec3 diffuse = _color * intensity;
    //// Especular
    //glm::vec3 viewDir = glm::normalize(-r.Direction());
    //glm::vec3 lightDir = glm::normalize(_direction);
    //glm::vec3 halfVector = glm::normalize(lightDir + viewDir);

    //float specularIntensity = std::max(0.0f, glm::dot(hit.normal, halfVector));
    //specularIntensity = std::pow(specularIntensity, 0.5);
    //glm::vec3 specular = _color * specularIntensity;

    //return Color(hit.m->GetColor() * diffuse + specular);

    Color ret; // color resultante
    _direction = glm::normalize(_direction);
    glm::vec3 normal = glm::normalize(hit.normal);
    float lightIntensity = glm::max(0.0f, glm::dot(normal, _direction));

    // -- difusa
    glm::vec3 diffuse = _color * lightIntensity;
    glm::vec3 diffuseLighting = diffuse;

    // -- especular
    glm::vec3 view = glm::normalize(r.Direction());
    glm::vec3 halfVector = glm::normalize(_direction + view);
    float specular = std::max(0.0f, glm::dot(normal, halfVector));
    specular = std::pow(specular, hit.m->GetGlossFactor());
    glm::vec3 specularColor = _color * specular;

    ret = hit.m->GetColor() * diffuseLighting + specularColor;

    return ret;
}