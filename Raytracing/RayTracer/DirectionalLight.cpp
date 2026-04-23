#include "DirectionalLight.h"

#include <iostream>
#include <detail/func_geometric.inl>

DirectionalLight::DirectionalLight(glm::vec3 direction, Color color)
	: _direction(direction), _color(color)
{

}

Color DirectionalLight::Shade(Ray r, InfoIntersection& hit)
{
    Color ret; // color resultante

    // -- ambiente
    Color ambient = _color;
    glm::vec3 normal = glm::normalize(hit.normal);
    glm::vec3 mainLightIntensity = glm::max(glm::vec3(0,0,0), glm::dot(normal, _direction));
    float f = glm::length(mainLightIntensity);
    // -- difusa
    glm::vec3 diffuse = _color * f;
    glm::vec3 diffuseLighting = (ambient + diffuse);
    
    // -- especular
    //IN.view = normalize(IN.view);
    //float3 halfVetor = normalize(mainLight.direction + IN.view);
    //float specular = max(0, dot(IN.normalWS, halfVetor));
    //specular = pow(specular, _GlossPower);
    //float3 specularColor = mainLight.color * specular;
    //IN.specularLighting = float4(specularColor, 1);

    ret = hit.m->GetColor() * diffuseLighting; // + specularLighting

    return ret;
}