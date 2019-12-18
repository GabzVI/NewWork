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
	temp = spheres[0].getSphereDistFromCamera(tmpResult, camera);

	for (int i = 0; i < spheres.size(); i++)
	{		
		tmpResult = spheres[i].Rayintersection(_ray, camera);
		if (tmpResult.hit)
		{

		if (temp >= spheres[i].getSphereDistFromCamera(tmpResult, camera)) 
		{
			
				temp = spheres[i].getSphereDistFromCamera(tmpResult, camera);
				chosenSphere = spheres[i];
		}
		}  
		
	}
	//std::cout << "temp result = " << temp << std::endl;
	if (tmpResult.hit == true)
	{

		pixelColour = lightpoint.Diffuselight(chosenSphere, tmpResult) + lightpoint.getAmbientLight()  + lightpoint.getSpecularLight(_ray , chosenSphere, tmpResult); // Diffuse + Ambient + specular light
		pixelColour = glm::clamp(pixelColour * lightpoint.getSurfaceLight() * lightpoint.getLightColour(), glm::vec3(0), glm::vec3(1));

	}
	else
	{
		pixelColour = glm::vec3(1, 1, 1);
		//std::cout << "not being drawn, yellow back" << std::endl;
	}



	return pixelColour;
}

void Traceray::SetSpheres(Sphere _spheres)
{
	spheres.push_back(_spheres);
	
}