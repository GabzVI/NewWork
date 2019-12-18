#include <glm/glm.hpp>

class Ray;
class Sphere;

class Geometry 
{

private:
  
public:
  glm::vec3 Closestpointonaline(Ray _ray, Sphere sphere);
  void Raysphereintercetion(Ray _ray, Sphere sphere);
  glm::vec3 Spherenormal(Sphere sphere, glm::vec3 _samplep);

};