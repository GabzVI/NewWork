#include "Camera.h"
#include "Ray.h"
#include <GLM/ext.hpp>
#include <iostream>

Ray Camera::Returnray(glm::ivec2 _pixelcp) 
{
	Ray _ray;
	
  projectionMatrix = glm::perspective((30.0f * 3.14159265358979f / 180.0f), ((float)windowSize.x / (float)windowSize.y), 0.1f, 100.0f);
  viewMatrix = glm::translate(glm::mat4(1.0f), camPosition); //Modelmatrix of camera created

  float NDCcoordinatex, NDCcoordinatey;

  // Setting the NDC coordinates
  NDCcoordinatex = (2.0f * (float)_pixelcp.x) / ((float)windowSize.x) - 1.0f;
  NDCcoordinatey = (2.0f * (float)_pixelcp.y) / ((float)windowSize.y) - 1.0f;


  //Setting near and far plane
  //Doing the inverse of projection matrix onto planes
  //Applying the view matrix onto planes
  nearPlane = glm::vec4(NDCcoordinatex, NDCcoordinatey, -1.0f, 1.0f);
  farPlane = glm::vec4(NDCcoordinatex, NDCcoordinatey, 1.0f, 1.0f);


  nearPlane = glm::inverse(projectionMatrix) * nearPlane;
  nearPlane = glm::inverse(viewMatrix) * nearPlane;
  nearPlane = nearPlane/nearPlane.w;

  farPlane = glm::inverse(projectionMatrix) * farPlane;
  farPlane = glm::inverse(viewMatrix) * farPlane;
  farPlane = farPlane/farPlane.w;

  _ray.origin = glm::vec3(nearPlane);
  _ray.direction = glm::vec3(glm::normalize(farPlane - nearPlane));
	 
	return _ray;
}

void Camera::setWindowsize(glm::ivec2 _windowSize)
{
  windowSize = _windowSize;
}
glm::ivec2 Camera::getWindowsize()
{
  return windowSize;
}
void Camera::setCampos(glm::vec3 camPos) 
{
	camPosition = camPos;
}

glm::vec3 Camera::getCampos() 
{
	return camPosition;
}

