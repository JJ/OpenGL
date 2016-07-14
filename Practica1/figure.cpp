#include <vector>
#include "./vertex.h"
#include "./figure.h"
#include <iostream>

using namespace std;

 void Figura::init(vector<_vertex3f> vertices, vector<_vertex3i> caras){
    //iteramos sobre los puntos y los vamos metiendo en el vector puntos.

   cout << vertices.size() << endl;
    for(int i=0; i < vertices.size(); i++){
      cout << "Aqui i vale " << i << endl;
      this->vertices.push_back(vertices[i]);
      cout << this->vertices[i]._0 << " " << this->vertices[i]._1 << " " << this->vertices[i]._2 << endl;
    }

    for(int i=0; i < caras.size(); i++){
      cout << "Caras: " << caras.size()  << endl;
      this->caras.push_back(caras[i]);
      cout << this->caras[i]._0 << " " << this->caras[i]._1 << " " << this->caras[i]._2 << endl;
    }
  }

  void Figura::asignaAristas(vector<_vertex3f> vertices){
    for(int i=0, j=0; i < vertices.size(); i++, j++){
      _vertex2i aux(i, i+1);
      //aristas.resize(aristas.size()+1);
      aristas.push_back(aux);
      if(i%2 == 0){
	_vertex2i aux2(i-2, i);
	j++;
	//aristas.resize(aristas.size()+1);
	aristas.push_back(aux);
      }
    }

    
  }
/*void Figura::asignaCaras(vector<_vertex3f> vertices){
    
    for(int i=0, j=0; i < aristas.size(); i+2, j++){
      _vertex3i aux(i, i+1, i+2);
      caras[j] = aux;
    }
    
    }*/
  
  void Figura::pointsMode(){
    glColor3f(0, 1, 0); //Color.
    glPointSize(5); //Tamanio del punto a pintar
    
    // cout << "Voy a pintar wee" << endl;
    glBegin(GL_POINTS);
    for(int i=0; i<this->vertices.size(); i++){
      glVertex3f(vertices[i]._0, vertices[i]._1, vertices[i]._2);
    }

    glEnd();
  }

  void Figura::linesMode(){
    glColor3f(0, 1, 0); //Color.
    glLineWidth(1); //Grosor de la línea
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //para que dibuje líneas

    glBegin(GL_TRIANGLES);

    for(int i=0; i<this->caras.size(); i++){
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
    if(chess_mode == false){
      for(int i=0; i < caras.size(); i++){
      }
    }
  }

