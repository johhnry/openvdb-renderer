#include "Material.hpp"

Material::Material(glm::vec3 color) : ambient(color), diffuse(color), specular(1.0f), shininess(32.f) {}

Material::~Material() {}
