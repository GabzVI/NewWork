#include "Trace.h"
#include "Ray.h"
#include "Sphere.h"
#include "LightSource.h"
#include "Camera.h"
#include <iostream>
#include <cmath>

glm::vec3 Traceray::Raytracer(Ray _ray, LightSource lightpoint, Camera camera, int count)
{
	glm::vec3 reflectColour;
	glm::vec3 refractedColour;
	glm::vec3 reflectRayDirection;
	float temp = 0;
	Sphere chosenSphere;
	intersectResult tmpResult;
	Ray reflectedRay;
	int chosenSphereElement;
	bool hit = false;
	
	//Draws the closest sphere to screen by comparing the distance between camera and sphere origin of each sphere.
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

				reflectRayDirection = glm::reflect(_ray.direction, chosenSphere.getSpherenormal());

				reflectedRay.direction = glm::normalize(reflectRayDirection);
				reflectedRay.origin = tmpResult.sphereintersection + reflectedRay.direction * 0.1f;

			

				//Refraction
				float c1 = -glm::dot(chosenSphere.getSpherenormal(), reflectedRay.direction);
				float n2 = sin(glm::angle(reflectedRay.direction, chosenSphere.getSpherenormal()));
				float n1 = 1.0f;
				float totalN = n2/ n1; // n2  / n1 or n1 / n2?
				float c2 = sqrt(1.0f - pow(totalN, 2) * (1.0f - pow(c1, 2)));
				refractedColour = (totalN * reflectedRay.direction) + (totalN * c1 - c2) * chosenSphere.getSpherenormal();

				reflectColour = Traceray::Raytracer(reflectedRay, lightpoint, camera, --count);
			}

			//Adding all lighting together
			pixelColour = lightpoint.Diffuselight(chosenSphere, tmpResult) + lightpoint.getAmbientLight() + lightpoint.getSpecularLight(_ray, chosenSphere, tmpResult); // Diffuse + Ambient + specular light
			pixelColour = glm::clamp(pixelColour  * lightpoint.getSurfaceLight(chosenSphere) * lightpoint.getLightColour(), glm::vec3(0), glm::vec3(1));
			
    }
	else
	{
		pixelColour = glm::vec3(0.2, 0.2, 0.2);
		//std::cout << "not being drawn, yellow back" << std::endl;
	}


	return pixelColour + reflectColour;
;
}

void Traceray::SetSpheres(Sphere _spheres)
{
	spheres.push_back(_spheres);
	
}