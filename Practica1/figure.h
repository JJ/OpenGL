//Rafa Leyva Ruiz

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

const int AXIS_SIZE = 5000;

using namespace std;

class Figura{
 private:
  vector<_vertex3f> vertices;
  vector<_vertex3i> caras;
  vector<_vertex3d> aristas;

  //metodos privados
  asignaAristas(vector<_vertex3f> vertices);
  asignaCaras(vector<vertex3d> aristas);

 public:
  Figura(vector<vertex3f> vertices);
  pintaVertices();
  pintaAristas();
  pintaCaras(boolean ajedrez);
