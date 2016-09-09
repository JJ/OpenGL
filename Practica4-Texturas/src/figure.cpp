#include <vector>
#include "vertex.h"
#include "figure.h"
#include <cmath>
#include <iostream>
#include "file_ply_stl.cc"
#include "jpg_imagen.cpp"

using namespace std;

Figura::Figura(char* ply_name){
  //Abrimos el fichero PLY
  _file_ply pLY;
  pLY.open(ply_name);
  //Creamos las estructuras de datos que vamos a usar.
  vector<_vertex3f> _puntos;
  vector<_vertex3i> _caras;

  vector<float> _coordenadas;
  vector<int> _indices_caras;

  //Leemos el ply
  pLY.read(_coordenadas, _indices_caras);

  //ALmacenamos los puntos en el vector _puntos
  for(int i=0; i < _coordenadas.size(); i+3){
    //Creamos un vertice con las coordenadas que hemos leido del PLY.
    _vertex3f aux;
    aux._0 = _coordenadas.at(i);
    aux._1 = _coordenadas.at(i+1);
    aux._2 = _coordenadas.at(i+2);

    //Lo guardamos en el vector de puntos.
    _puntos.push_back(aux);
  }

  //Igual para las caras.
  for(int i=0; i < _indices_caras.size(); i+3){
    _vertex3i aux;
    aux._0 = _indices_caras.at(i);
    aux._1 = _indices_caras.at(i+1);
    aux._2 = _indices_caras.at(i+2);

    _caras.push_back(aux);
  }

  //Asignamos el valor a las variables de clase.
  this->vertices = _puntos;
  this->caras = _caras;
}

void Figura::init(vector<_vertex3f> vertices, vector<_vertex3i> caras){
  //iteramos sobre los puntos y los vamos metiendo en el vector puntos.

  //cout << vertices.size() << endl;
  for(int i=0; i < vertices.size(); i++){
    //cout << "Aqui i vale " << i << endl;
    this->vertices.push_back(vertices[i]);
    //cout << this->vertices[i]._0 << " " << this->vertices[i]._1 << " " << this->vertices[i]._2 << endl;
  }

  for(int i=0; i < caras.size(); i++){
    //cout << "Caras: " << caras.size()  << endl;
    this->caras.push_back(caras[i]);
    //cout << this->caras[i]._0 << " " << this->caras[i]._1 << " " << this->caras[i]._2 << endl;
  }
}

//Operador de asignacion
Figura& Figura::operator=(Figura &asig){
  this->vertices = asig.vertices;
  this->caras = asig.caras;

  return *this;
}

//Metodo para leer un PLY en una figura ya creada.
void Figura::initfromPLY(char* ply_name){
  _file_ply pLY;
  pLY.open(ply_name);

    //Creamos las estructuras de datos que vamos a usar.
  vector<_vertex3f> _puntos;
  vector<_vertex3i> _caras;

  vector<float> _coordenadas;
  vector<int> _indices_caras;

  //Leemos el ply
  pLY.read(_coordenadas, _indices_caras);

  //ALmacenamos los puntos en el vector _puntos
  for(int i=0; i < _coordenadas.size(); i+=3){
    //Creamos un vertice con las coordenadas que hemos leido del PLY.
    _vertex3f aux;
    aux._0 = _coordenadas.at(i);
    aux._1 = _coordenadas.at(i+1);
    aux._2 = _coordenadas.at(i+2);

    //Lo guardamos en el vector de puntos.
    _puntos.push_back(aux);
  }

  long_perfil = vertices.size();

  //Igual para las caras.
  for(int i=0; i < _indices_caras.size(); i+=3){
    _vertex3i aux;
    aux._0 = _indices_caras.at(i);
    aux._1 = _indices_caras.at(i+1);
    aux._2 = _indices_caras.at(i+2);

    _caras.push_back(aux);
  }

  //cout << "Voy a ponerlo en los vectores de la clase" << endl;

  this->vertices = _puntos;
  this->caras = _caras;

  //cout << "Ya he almacenado los vectores" << endl;
}


void Figura::rotate(int ncaras){
  bool tapas;
  bool eje;
  int _eje;
  rotateY(ncaras);
  //if(checkTapas()){
    //}
  //calculaTapas(ncaras, 2);

  /*for(int i=0; i < vertices.size() && !eje; i++){
    //Comprobamos eje es constante en los vertices.
    if(vertices.at(i)._0 == vertices.at(i+1)._0 == 0){ 
      eje = true;
      rotateX(ncaras);
      if(checkTapas()){
	//calculaTapas();
      }
    }else if(vertices.at(i)._2 == vertices.at(i+1)._2 == 0){
      eje = true;
      rotateY(ncaras);
      if(checkTapas()){
	//calculaTapas();
      }
    }else if(vertices.at(i)._2 == vertices.at(i+1)._2 == 0){
      eje = true;
      rotateY(ncaras);
      if(checkTapas()){
	calculaTapas(ncaras, 2);
      }
    }
    }*/
}

void Figura::rotateX(int ngiros){
  //Variables de rotacion.
  cout << "Roto X" << endl;
  double alfa = 2*M_PI/ngiros;
  //double increase = alfa;
  int long_perfil = vertices.size();
  vector<_vertex3f> last = vertices;

  //Calculamos nuevos puntos.
  for(int i = 0; i < ngiros; i++){
    for(int j = 0; j < long_perfil; j++){
      _vertex3f aux;
      aux._0 = vertices[j]._0;
      aux._1 = cos(alfa)*aux._1 - sin(alfa)*aux._2;
      aux._2 = sin(alfa)*aux._1 + cos(alfa)*aux._2;
      vertices.push_back(aux);
      last[j] = aux;
    }
  }

  //Caras
}

void Figura::rotateY(int ngiros){
  //Variables de rotacion.
  //double alfa = 2*M_PI/ngiros;
  int long_perfil = vertices.size();
  this->long_perfil = long_perfil;
  
  vector<_vertex3f> new_vertices;

  cout << long_perfil << " vertices" << endl;

  _vertex3f aux1;
  for(int i=0; i < ngiros; i++){
    double alfa = (2*M_PI/ngiros)*i;
    for(int j=0;  j < long_perfil; j++){
      _vertex3f aux2;
      aux1 = vertices.at(j);
      aux2._1 = aux1._1;
      aux2._0 = (cos(alfa) * aux1._0) + (sin(alfa) * aux1._2);
      aux2._2 = (cos(alfa) * aux1._2) - (sin(alfa) * aux1._0);

      vertices.push_back(aux2);
    }
  }

  //vertices.clear();
  //vertices = new_vertices;
  caras.clear();

  //caras
  for(int i=1; i < ngiros-1; i++){
    for(int j=0; j < long_perfil-1; j++){
      _vertex3i cara1, cara2;
      //cout << "calculando caras " << endl; 
      cara1._0 = (i*long_perfil)+j;
      cara1._1 = ((i+1)*long_perfil)+j;
      cara1._2 = (i*long_perfil)+j+1;
      cara2._0 = (i*long_perfil)+j+1;
      cara2._1 = ((i+1)*long_perfil)+j;
      cara2._2 = ((i+1)*long_perfil)+j+1;
      caras.push_back(cara1);
      caras.push_back(cara2);
    }
  }

  calculaTapas(1, ngiros);
}


void Figura::rotateZ(int ngiros){
  //Variables de rotacion.
  cout << "Roto Z" << endl;
  double alfa = 2*M_PI/ngiros;
  //double increase = alfa;
  int long_perfil = vertices.size();
  vector<_vertex3f> last = vertices;

  //Calculamos nuevos puntos.
  for(int i = 0; i < ngiros; i++){
    for(int j = 0; j < long_perfil; j++){
      _vertex3f aux;
      aux._1 = 0;
      //calculeNewCoord(aux._0, aux._1, last.at(j)._0, last.at(j)._1, alfa);
      vertices.push_back(aux);
      last[j] = aux;
    }
  }     
}

void Figura::calculaTapas(int axis, int ngiros){

  if(vertices.at(long_perfil)._0 != 0.0){ 
    //Superior
    _vertex3f superior(0.0, vertices[vertices.size()-1]._1, 0.0);
    vertices.push_back(superior);
    
    for (int i = 0; i < ngiros; i++){
      int act = (i+1) * long_perfil-1;
      int sig = act + long_perfil;
      caras.push_back(_vertex3i(vertices.size()-1, act, sig));
    }
  }

  
  if(vertices.at(0)._0 != 0.0){ 
    //vertice que se corresponde con el centro de la tapa de abajo.
    _vertex3f inferior(0.0, vertices[0]._1, 0.0);
    vertices.push_back(inferior);
  
    for (int i = 0; i < ngiros; i++){
      int act = i * long_perfil;
      int sig = act + long_perfil;
      caras.push_back(_vertex3i(vertices.size()-1, sig, act));
    }
  }
}

void Figura::draw(int modo, double red, double green, double blue){
  switch(modo){
  case 0:
    this->pointsMode(red, green, blue);
    break;
  case 1:
    this->linesMode(red, green, blue);
    break;
  case 2:
    this->solidMode(false, red, green, blue);
    break;
  case 3:
    this->solidMode(true, red, green, blue);
  }
}
/*
 *
 *MODOS DE DIBUJADO (Solido, Ajedrez, alambre, puntos)
 *
 */
void Figura::pointsMode(double red, double green, double blue){
  glColor3f(red, green, blue); //Color.
  glPointSize(5); //Tamanio del punto a pintar
  
  //cout << "Pinto puntos" << endl;
  glBegin(GL_POINTS);
  for(int i=0; i<this->vertices.size(); i++){
    glVertex3f(vertices[i]._0, vertices[i]._1, vertices[i]._2);
    //cout << "pintando punto " << vertices[i]._0 << " " << vertices[i]._1 << " " << vertices[i]._2 << endl;
  }

  glEnd();
}

void Figura::linesMode(double red, double green, double blue){
  glColor3f(red, green, blue); //Color.
  glLineWidth(1); //Grosor de la línea
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //para que dibuje líneas 
  glBegin(GL_TRIANGLES);
  //cout << "Pintar lineas" << endl;

  for(int i=0; i < this->caras.size(); i++){
    int v_1, v_2, v_3;
    v_1 = caras[i]._0;
    v_2 = caras[i]._1;
    v_3 = caras[i]._2;
    // Dibujamos la cara definida por las aristas
    glVertex3f(vertices[v_1]._0, vertices[v_1]._1, vertices[v_1]._2);
    glVertex3f(vertices[v_2]._0, vertices[v_2]._1, vertices[v_2]._2);
    glVertex3f(vertices[v_3]._0, vertices[v_3]._1, vertices[v_3]._2);
    
  }
  
  glEnd();
}

void Figura::solidMode(bool chess_mode, double red, double green, double blue){
  int v_1, v_2, v_3;
  //cout << "Pintar modo solido" << endl;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //los poligonos iran "rellenos" Coloreados.
  glBegin(GL_TRIANGLES); //Modo triangulos.

  for(int i=0; i < caras.size(); i++){
    if(chess_mode == true && i%2 == 0)
      glColor3f(1, 0, 0);
    else glColor3f(red, green, blue);
    
    v_1 = caras[i]._0;
    v_2 = caras[i]._1;
    v_3 = caras[i]._2;
    // Dibujamos la cara definida por las aristas
    glVertex3f(vertices[v_1]._0, vertices[v_1]._1, vertices[v_1]._2);
    glVertex3f(vertices[v_2]._0, vertices[v_2]._1, vertices[v_2]._2);
    glVertex3f(vertices[v_3]._0, vertices[v_3]._1, vertices[v_3]._2);
  }

  glEnd();
}


void Figura::aplicaTextura(char* name){
  this->textura = new jpg::Imagen(name);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, textura->tamX(), textura->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, textura->leerPixels());
}

/*
void Figura::calculaNormales(){
  for(int i=0; i< caras.size(); i++){
    int v1, v2, v3;
    v1 = caras[i]._0;
    v2 = caras[i]._1;
    v3 = caras[1]._2;
    
    normales.push_back(glNormal3f(vertices[v1]._0, vertices[v1]._1, vertices[v1]._2));
    normales.push_back(glNormal3f(vertices[v2]._0, vertices[v2]._1, vertices[v2]._2));
    normales.push_back(glNormal3f(vertices[v3]._0, vertices[v3]._1, vertices[v3]._2));
  }
}
*/
