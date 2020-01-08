#include "Trace.h"
#include "Ray.h"
#include "Sphere.h"
#include "LightSource.h"
#include "Camera.h"
#include <iostream>
#include <cmath>

glm::vec3 Traceray::Raytracer(Ray _ray, intersectResult &tmpResult, LightSource lightpoint, Camera camera, int count)
{
	glm::vec3 reflectColour;
	glm::vec3 reflectRayDirection;
	float temp = 0;
	Sphere chosenSphere;
	Ray reflectedRay;
	int chosenSphereElement;
	bool hit = false;
	
	for (int i = 0; i < spheres.size(); i++)
	{		
		tmpResult = spheres[i].Rayintersection(_ray, camera);
		if (tmpResult.hit && temp < spheres[i].getSphereDistFromCamera(tmpResult, camera)) 
		{
			
				temp = spheres[i].getSphereDistFromCamera(tmpResult, camera);
				chosenSphere = spheres[i];
				chosenSphereElement = i;
				hit = true;
		} 
	}
	
	
	if (hit == true)
		{
			if (count > 0)
			{

				reflectRayDirection = _ray.direction - (2.0f * glm::dot(_ray.direction, chosenSphere.getSpherenormal()) * chosenSphere.getSpherenormal());

				reflectedRay.direction = glm::normalize(reflectRayDirection);
				reflectedRay.origin = chosenSphere.getSphereIntersection(tmpResult) + chosenSphere.getSpherenormal() * 0.01f;

				reflectColour = Raytracer(reflectedRay, tmpResult, lightpoint, camera, count - 1);


			}
			pixelColour = lightpoint.Diffuselight(chosenSphere, tmpResult) + lightpoint.getAmbientLight() + lightpoint.getSpecularLight(_ray, chosenSphere, tmpResult); // Diffuse + Ambient + specular light
			pixelColour = glm::clamp(pixelColour * lightpoint.getSurfaceLight(chosenSphere) * lightpoint.getLightColour(), glm::vec3(0), glm::vec3(1));
    }
	else
	{
		pixelColour = glm::vec3(0.2, 0.2, 0.2);
		//std::cout << "not being drawn, yellow back" << std::endl;
	}


	return pixelColour;
;
}

void Traceray::SetSpheres(Sphere _spheres)
{
	spheres.push_back(_spheres);
	
}