#include <glm/glm.hpp>
#include <vector>

class Ray;
class Sphere;
class LightSource;
class Camera;
struct intersectResult;


class Traceray 
{

private:
  glm::vec3 pixelColour;
  std::vector<Sphere> spheres;
public:
  glm::vec3 Raytracer(Ray _ray, intersectResult &tmpResult, LightSource pointlight, Camera camera);
  void SetSpheres(Sphere _spheres);

};