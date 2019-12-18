#include <cmath>
#include <GLM/glm.hpp>


class Sphere;
class Trace;
class Ray;
struct intersectResult;

class LightSource
{
private:
	glm::vec3 lightPos; //Position of the light
	glm::vec3 lightColour; //Colour of the Light
	glm::vec3 surfaceLight; //Colour of surface or sphere
	glm::vec3 wi; //vector pointing to light source
	glm::vec3 lightDir; // vector of the direction of light
	glm::vec3 diffuseLight;
	glm::vec3 specularLight;
	glm::vec3 ambientLight;
	float shininess;
public:

	void setLightpos(glm::vec3 _setLightpos);
	void setLightColour(glm::vec3 _lightColour);
	void setSurfaceLight(glm::vec3 _surfaceLight);
	void setAmbientLight(glm::vec3 _ambientLight);
	void setObjectShininess(float _shineness);
	glm::vec3 Diffuselight(Sphere sphere, intersectResult tmpResult);
	glm::vec3 getSpecularLight(Ray _ray, Sphere sphere, intersectResult tmpResult);
	glm::vec3 getLightpos();
	glm::vec3 getLightColour();
	glm::vec3 getSurfaceLight();
	glm::vec3 getAmbientLight();
};
