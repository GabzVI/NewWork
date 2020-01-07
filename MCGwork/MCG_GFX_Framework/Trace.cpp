#include "Trace.h"
#include "Ray.h"
#include "Sphere.h"
#include "LightSource.h"
#include "Camera.h"
#include <iostream>
#include <cmath>

glm::vec3 Traceray::Raytracer(Ray _ray, intersectResult &tmpResult, LightSource lightpoint, Camera camera)
{
	
	float temp = 0;
	Sphere chosenSphere;
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

		pixelColour = lightpoint.Diffuselight(spheres.at(chosenSphereElement), tmpResult) + lightpoint.getAmbientLight()  + lightpoint.getSpecularLight(_ray , spheres.at(chosenSphereElement), tmpResult); // Diffuse + Ambient + specular light
		pixelColour = glm::clamp(pixelColour * lightpoint.getSurfaceLight(spheres.at(chosenSphereElement)) * lightpoint.getLightColour(), glm::vec3(0), glm::vec3(1));

	}
	else
	{
		pixelColour = glm::vec3(0.2, 0.2, 0.2);
		//std::cout << "not being drawn, yellow back" << std::endl;
	}



	return pixelColour;
}

void Traceray::SetSpheres(Sphere _spheres)
{
	spheres.push_back(_spheres);
	
}