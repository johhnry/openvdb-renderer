#include "FullScreenVAO.hpp"

typedef struct _COORDS_ {
  GLfloat x;
  GLfloat y;
  GLfloat s;
  GLfloat t;
} CoordinatesSet;

typedef struct _RGBA_ {
  GLfloat Red;
  GLfloat Green;
  GLfloat Blue;
  GLfloat Alpha;
} RGBAValues;

FullScreenVAO::FullScreenVAO()
{
  CoordinatesSet *quadVertex = new CoordinatesSet[4];
  unsigned short int *quadIndex = new unsigned short int[3];

  quadVertex[0].x = -1.0f;
  quadVertex[0].y = 1.0f;

  quadVertex[1].x = -1.0f;
  quadVertex[1].y = -1.0f;

  quadVertex[2].x = 1.0f;
  quadVertex[2].y = 1.0f;

  quadVertex[3].x = 1.0f;
  quadVertex[3].y = -1.0f;

  quadIndex[0] = 0;
  quadIndex[1] = 1;
  quadIndex[2] = 2;
  quadIndex[3] = 3;

  quadVertex[0].s = 0.0f;
  quadVertex[0].t = 0.0f;
  quadVertex[1].s = 0.0f;
  quadVertex[1].t = 1.0f;
  quadVertex[2].s = 1.0f;
  quadVertex[2].t = 0.0f;
  quadVertex[3].s = 1.0f;
  quadVertex[3].t = 1.0f;

  glGenBuffers(1, &quadIBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned short int),
               quadIndex, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(CoordinatesSet) * 4, 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CoordinatesSet) * 4, quadVertex);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &quadVAO);
  glBindVertexArray(quadVAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);

  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                        (GLvoid *)(sizeof(GLfloat) * 2));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

void FullScreenVAO::bind() const
{
  glBindVertexArray(quadVAO);
}

void FullScreenVAO::unbind() const
{
  glBindVertexArray(0);
}

void FullScreenVAO::draw() const
{
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (GLvoid *)0);
}
