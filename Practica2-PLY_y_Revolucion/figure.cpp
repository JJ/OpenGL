#include <vector>
#include "./vertex.h"
#include "./figure.h"
#include <iostream>
#include "./lector_ply/file_ply_stl.cc"

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

  this->vertices = _puntos;
  this->caras = _caras;
}
void Figura::pointsMode(){
  glColor3f(0, 1, 0); //Color.
  glPointSize(5); //Tamanio del punto a pintar
  
  cout << "Pinto puntos" << endl;
  glBegin(GL_POINTS);
  for(int i=0; i<this->vertices.size(); i++){
    glVertex3f(vertices[i]._0, vertices[i]._1, vertices[i]._2);
    //cout << "pintando punto " << vertices[i]._0 << " " << vertices[i]._1 << " " << vertices[i]._2 << endl;
  }

  glEnd();
}

void Figura::linesMode(){
  glColor3f(0, 1, 0); //Color.
  glLineWidth(1); //Grosor de la línea
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //para que dibuje líneas 
  glBegin(GL_TRIANGLES);
  cout << "Pintar lineas" << endl;

  for(int i=0; i<=this->caras.size(); i++){
    cout << "cara " << i << endl;
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

void Figura::solidMode(bool chess_mode){
  int v_1, v_2, v_3;
  cout << "Pintar modo solido" << endl;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //los poligonos iran "rellenos" Coloreados.
  glBegin(GL_TRIANGLES); //Modo triangulos.

  for(int i=0; i < caras.size(); i++){
    if(chess_mode == true && i%2 == 0)
      glColor3f(1, 0, 0);
    else glColor3f(0, 1, 0);
    
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


