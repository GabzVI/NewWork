#include <glm/glm.hpp>

class Ray;
class Camera;

struct intersectResult
{
	bool hit;
	float pointdistance;
    glm::vec3 sphereintersection;
	
};

class Sphere 
{

private:
  float radius; //radius of sphere
  glm::vec3 sphereOri; //Sphere Origin
  glm::vec3 sphereNormal;
  float distfromCameratoSphere;
	
public:

  intersectResult Rayintersection(Ray _ray, Camera camera);
  void SetRadius(float _setr);
  void SetSphereori(glm::vec3 _setsphereOri);
  float getRadius();
  glm::vec3 getSphereori();
  glm::vec3 getSpherenormal();
  float getSphereDistFromCamera(intersectResult rtn, Camera camera);
	

};