#include "LightSource.h"
#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include  <GLM/glm.hpp>

glm::vec3 LightSource::Diffuselight(Sphere sphere, intersectResult tmpResult)
{
	lightDir = glm::normalize(lightPos - tmpResult.sphereintersection);

	glm::vec3 diffuseLight = glm::vec3(glm::max(glm::dot(sphere.getSpherenormal(), lightDir), 0.0f));

	return diffuseLight;

}

glm::vec3 LightSource::getSpecularLight(Ray _ray, Sphere sphere, intersectResult tmpResult)
{
	lightDir = glm::normalize(lightPos - tmpResult.sphereintersection);

	//specularlighting
	glm::vec3 Ks = glm::vec3(1.0f); //Surface specular colour
	glm::vec3 H = glm::normalize(-_ray.direction + lightDir);// H is the half vector between light direction and eye direction.

	float stepone = glm::pow(glm::max(glm::dot(sphere.getSpherenormal(), H), 0.0f), shininess); //max(N 

	float facing;

	if (glm::dot(sphere.getSpherenormal(), lightDir) > 0)
	{
		facing = 1.0f;
	}
	else
	{
		facing = 0.0f;
	}

	specularLight = Ks * facing * lightColour * stepone;

	return specularLight;
}



void LightSource::setLightpos(glm::vec3 _setLightpos)
{
	lightPos = _setLightpos;
}

glm::vec3 LightSource::getLightpos()
{
	return lightPos;
}

void LightSource::setLightColour(glm::vec3 _lightColour)
{
	lightColour = _lightColour;
}

glm::vec3 LightSource::getLightColour()
{
	return lightColour;
}

void LightSource::setSurfaceLight(glm::vec3 _surfaceLight)
{
	surfaceLight = _surfaceLight;
}

glm::vec3 LightSource::getSurfaceLight()
{
	return surfaceLight;
}

void LightSource::setAmbientLight(glm::vec3 _ambientLight)
{
	ambientLight = _ambientLight;
}

glm::vec3 LightSource::getAmbientLight()
{
	return ambientLight;
}

void LightSource::setObjectShininess(float _shineness)
{
	shininess = _shineness;
}