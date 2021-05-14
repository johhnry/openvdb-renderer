#include "Light.hpp"

Light::Light(glm::vec3 pos) : position(pos), ambient(glm::vec3(0.3f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)) {}

Light::~Light() {}
