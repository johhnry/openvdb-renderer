#include <iostream>

#include <GL/glew.h>

#include "VAO.hpp"

VAO::VAO()
{
  glGenVertexArrays(1, &vaoID);
  glGenBuffers(1, &vboID);
  glGenBuffers(1, &eboID);
}

VAO::~VAO()
{
  glDeleteVertexArrays(1, &vaoID);
  glDeleteBuffers(1, &vboID);
  glDeleteBuffers(1, &eboID);
}

void VAO::pushVertex(float const x, float const y, float const z)
{
  vertices.push_back(x);
  vertices.push_back(y);
  vertices.push_back(z);
}

void VAO::pushNormal(float const x, float const y, float const z)
{
  pushVertex(x, y, z);
}

void VAO::pushColor(float const r, float const g, float const b)
{
  pushVertex(r, g, b);
}

void VAO::pushTexCoord(float const u, float const v)
{
  vertices.push_back(u);
  vertices.push_back(v);
}

void VAO::pushIndices(int const a, int const b, int const c)
{
  indices.push_back(a);
  indices.push_back(b);
  indices.push_back(c);
}

void VAO::commit()
{
  float *verticesData = vertices.data();

  glBindVertexArray(vaoID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), verticesData,
               GL_STATIC_DRAW);

  //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
  //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(),
  //                 indices.data(), GL_STATIC_DRAW);

  // Enable vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //    // Enable color attributes
  //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
  //                          (void *)(3 * sizeof(float)));
  //    glEnableVertexAttribArray(1);

  // Enable normal vectors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind VAO
  glBindVertexArray(0);
}

void VAO::bind() { glBindVertexArray(vaoID); }

void VAO::unbind() { glBindVertexArray(0); }

void VAO::draw() {
  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
}

void VAO::createCube(float x, float y, float z, float size) {
  float half = size / 2;

  // X+
  pushVertex(x + half, y - half, z + half);
  pushNormal(1, 0, 0);
  // pushTexCoord(0, 0);

  pushVertex(x + half, y - half, z - half);
  pushNormal(1, 0, 0);

  pushVertex(x + half, y + half, z - half);
  pushNormal(1, 0, 0);

  pushVertex(x + half, y - half, z + half);
  pushNormal(1, 0, 0);
  // pushTexCoord(0, 0);

  pushVertex(x + half, y + half, z - half);
  pushNormal(1, 0, 0);
  // pushTexCoord(1, 1);

  pushVertex(x + half, y + half, z + half);
  pushNormal(1, 0, 0);
  // pushTexCoord(0, 1);

  // X-
  pushVertex(x - half, y - half, z + half);
  pushNormal(-1, 0, 0);
  // pushTexCoord(0, 0);

  pushVertex(x - half, y - half, z - half);
  pushNormal(-1, 0, 0);
  // pushTexCoord(1, 0);

  pushVertex(x - half, y + half, z - half);
  pushNormal(-1, 0, 0);
  // pushTexCoord(1, 1);

  pushVertex(x - half, y - half, z + half);
  pushNormal(-1, 0, 0);
  // pushTexCoord(0, 0);

  pushVertex(x - half, y + half, z - half);
  pushNormal(-1, 0, 0);
  // pushTexCoord(0, 1);

  pushVertex(x - half, y + half, z + half);
  pushNormal(-1, 0, 0);
  // pushTexCoord(1, 1);

  // Y+
  pushVertex(x - half, y + half, z + half);
  pushNormal(0, 1, 0);
  // pushTexCoord(0, 0);

  pushVertex(x - half, y + half, z - half);
  pushNormal(0, 1, 0);
  // pushTexCoord(0, 1);

  pushVertex(x + half, y + half, z - half);
  pushNormal(0, 1, 0);
  // pushTexCoord(1, 0);

  pushVertex(x - half, y + half, z + half);
  pushNormal(0, 1, 0);
  // pushTexCoord(0, 0);

  pushVertex(x + half, y + half, z - half);
  pushNormal(0, 1, 0);
  // pushTexCoord(1, 1);

  pushVertex(x + half, y + half, z + half);
  pushNormal(0, 1, 0);
  // pushTexCoord(1, 0);

  // Y-
  pushVertex(x - half, y - half, z + half);
  pushNormal(0, -1, 0);
  // pushTexCoord(0, 0);

  pushVertex(x - half, y - half, z - half);
  pushNormal(0, -1, 0);
  // pushTexCoord(0, 1);

  pushVertex(x + half, y - half, z - half);
  pushNormal(0, -1, 0);
  // pushTexCoord(1, 1);

  pushVertex(x - half, y - half, z + half);
  pushNormal(0, -1, 0);
  // pushTexCoord(0, 0);

  pushVertex(x + half, y - half, z - half);
  pushNormal(0, -1, 0);
  // pushTexCoord(1, 1);

  pushVertex(x + half, y - half, z + half);
  // pushTexCoord(1, 0);
  pushNormal(0, -1, 0);

  // Z+
  pushVertex(x - half, y - half, z + half);
  pushNormal(0, 0, 1);
  // pushTexCoord(0, 0);

  pushVertex(x - half, y + half, z + half);
  pushNormal(0, 0, 1);
  // pushTexCoord(0, 1);

  pushVertex(x + half, y + half, z + half);
  pushNormal(0, 0, 1);
  // pushTexCoord(1, 1);

  pushVertex(x - half, y - half, z + half);
  pushNormal(0, 0, 1);
  // pushTexCoord(0, 0);

  pushVertex(x + half, y + half, z + half);
  pushNormal(0, 0, 1);
  // pushTexCoord(1, 1);

  pushVertex(x + half, y - half, z + half);
  pushNormal(0, 0, 1);
  // pushTexCoord(1, 0);

  // Z-
  pushVertex(x - half, y - half, z - half);
  pushNormal(0, 0, -1);
  // pushTexCoord(0, 0);

  pushVertex(x - half, y + half, z - half);
  pushNormal(0, 0, -1);
  // pushTexCoord(0, 1);

  pushVertex(x + half, y + half, z - half);
  pushNormal(0, 0, -1);
  // pushTexCoord(1, 1);

  pushVertex(x - half, y - half, z - half);
  pushNormal(0, 0, -1);
  // pushTexCoord(0, 0);

  pushVertex(x + half, y + half, z - half);
  pushNormal(0, 0, -1);
  // pushTexCoord(1, 1);

  pushVertex(x + half, y - half, z - half);
  pushNormal(0, 0, -1);
  // pushTexCoord(1, 0);
}
