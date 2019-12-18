#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Ray;
class Sphere;

class Camera
{

private:
	glm::vec3 camPosition; // Camera Position
	glm::ivec2 windowSize;
	glm::vec3 mapCoordinate;
	glm::vec4 nearPlane;
	glm::vec4 farPlane;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;


public:

	Ray Returnray(glm::ivec2 _pixelcp);
	void setCampos(glm::vec3 camPos);
	void setWindowsize(glm::ivec2 _windowSize);
	glm::ivec2 getWindowsize();
	glm::vec3 getCampos();


};



