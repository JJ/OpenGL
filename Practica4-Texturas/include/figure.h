

//Rafa Leyva Ruiz

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "jpg_imagen.hpp"

using namespace std;

#ifndef FIGURA
#define FIGURA

class Figura{
 private:
  vector<_vertex3f> vertices;
  vector<_vertex3i> caras;
  vector<_vertex2i> aristas;
  vector<_vertex3f> normales;
  vector<_vertex2f> texturas;  //
  int long_perfil;
  jpg::Imagen *textura;

  //Para las texturas
  void calculaNormales();
  void calculaCoordenadasTextura();
  

  void calculaTapas(int axis, int ngiros);
  bool checkTapas();
  void rotateX(int ncaras);
  void rotateY(int ncaras);
  void rotateZ(int ncaras);
  //void calculeNewCoord(float& a_1, float& b_1, const float a, const float b,  double alfa);
  void pointsMode(double red, double green, double blue);
  void linesMode(double red, double green, double blue);
  void solidMode(bool chessMode, double red, double green, double blue);
 public:
  Figura(){};
  Figura(char* ply_name); //Constructor a partir de un ply;
  void init(vector<_vertex3f> vertices, vector<_vertex3i> caras);
  Figura& operator = (Figura &asig);
  void initfromPLY(char* ply_name);
  void rotate(int ncaras = 36);
  void draw(int modo, double red, double green, double blue);

  void rotate();

  void aplicaTextura(char* name);
};

#endif
