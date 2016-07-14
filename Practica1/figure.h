//Rafa Leyva Ruiz

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

#ifndef FIGURA
#define FIGURA

class Figura{
 private:
  vector<_vertex3f> vertices;
  vector<_vertex3i> caras;
  vector<_vertex2i> aristas;

  //metodos privados
  void asignaAristas(vector<_vertex3f> vertices);
  void asignaCaras(vector<_vertex3f> aristas);

 public:
  void init(vector<_vertex3f> vertices, vector<_vertex3i> caras);
  void pointsMode();
  void linesMode();
  void solidMode(bool ajedrez);
};

#endif
