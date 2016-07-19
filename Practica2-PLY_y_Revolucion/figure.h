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

 public:
  Figura(char* ply_name); //Constructor a partir de un ply;
  void init(vector<_vertex3f> vertices, vector<_vertex3i> caras);
  Figura& operator = (Figura &asig);
  void initfromPLY(const char* ply_name);
  void pointsMode();
  void linesMode();
  void solidMode(bool chessMode);
};

#endif
