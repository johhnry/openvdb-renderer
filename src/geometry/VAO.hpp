#ifndef OPENVDB_RENDERER_SRC_GEOMETRY_VAO_HPP_
#define OPENVDB_RENDERER_SRC_GEOMETRY_VAO_HPP_

#include <vector>

class VAO
{
public:
  VAO();
  ~VAO();

  void pushVertex(float const x, float const y, float const z);
  void pushNormal(float const x, float const y, float const z);
  void pushTexCoord(float const u, float const v);
  void pushColor(float const r, float const g, float const b);
  void pushIndices(int const a, int const b, int const c);

  void commit();
  void bind();
  void unbind();
  void draw();

  void createCube(float x, float y, float z, float size);

private:
  unsigned int vaoID, vboID, eboID;

  std::vector<float> vertices;
  std::vector<int> indices;
  std::vector<float> normals;
};

#endif /* OPENVDB_RENDERER_SRC_GEOMETRY_VAO_HPP_ */
