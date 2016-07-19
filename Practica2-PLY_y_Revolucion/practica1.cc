//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "./figure.cpp"
#include "./vertex.h"
#include "vector"


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//Las declaro aqui para que no se cree un nuevo cubo en cada llamada a
//drawobjects.
//Declaracion de las estructuras a representar.
//CUBO, los puntos van en orden de los ejes de coordenadas x, y, z.
Figura Cubo;
//TETRAEDRO.
Figura Tetraedro;
Figura Pinta = Cubo;

//Modo en el que pintar
int modo = 0;
//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(Figura &pinta, int modo)
{
  switch (modo){
  case 0:
    pinta.pointsMode();
    break;
  case 1:
    pinta.linesMode();
    break;
  case 2:
    pinta.solidMode(false);
    break;
  case 3:
    pinta.solidMode(true);
  }
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects(Pinta, modo);
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

/****************************************************************************
Funcion para imprimir la ayuda
****************************************************************************/
void printHelp(){}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

  if (toupper(Tecla1)=='Q') exit(0);
  if (toupper(Tecla1) == 'A'){
    Pinta = Cubo;
  }else if(toupper(Tecla1) == 'S'){
    Pinta = Tetraedro;
  }else{
    char Tecla = toupper(Tecla1);
    
    switch (Tecla){
    case 'Z':
      modo = 0; //Puntos
      break;
    case 'X':
      modo = 1; //Lineas
      break;
    case 'C':
      modo = 2; //Solido
      break;
    case 'V':
      modo = 3; //Ajedrez
      break;
    default:
      cout << "La tecla pulsadas es erronea " << endl;
      printHelp();
      break;
    }
  }

  draw_scene();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
  //CUBO  
_vertex3f p1 = _vertex3f(0, 1, 0);
_vertex3f p2 = _vertex3f(0, 1, 1);
_vertex3f p3 = _vertex3f(1, 1, 1);
_vertex3f p4 = _vertex3f(1, 1, 0);
_vertex3f p5 = _vertex3f(0, 0, 0);
_vertex3f p6 = _vertex3f(0, 0, 1);
_vertex3f p7 = _vertex3f(1, 0, 1);
_vertex3f p8 = _vertex3f(1, 0, 0);
 //Caras del cubo
 _vertex3i c1 = _vertex3i(0, 1, 2);
 _vertex3i c2 = _vertex3i(2, 3, 0);
 _vertex3i c3 = _vertex3i(0, 4, 1);
 _vertex3i c4 = _vertex3i(4, 5, 1);
 _vertex3i c5 = _vertex3i(4, 0, 3);
 _vertex3i c6 = _vertex3i(3, 7, 4);
 _vertex3i c7 = _vertex3i(4, 5, 6);
 _vertex3i c8 = _vertex3i(6, 7, 4);
 _vertex3i c9 = _vertex3i(6, 5, 1);
 _vertex3i c10 = _vertex3i(6, 2, 1);
 _vertex3i c11 = _vertex3i(6, 2, 3);
 _vertex3i c12 = _vertex3i(6, 7, 3);
 
 vector<_vertex3f> vert;
 vector<_vertex3i> car;
 
 
vert.push_back(p1);
vert.push_back(p2);
vert.push_back(p3);
vert.push_back(p4);
vert.push_back(p5);
vert.push_back(p6);
vert.push_back(p7);
vert.push_back(p8);

 car.push_back(c1);
 car.push_back(c2);
 car.push_back(c3);
 car.push_back(c4);
 car.push_back(c5);
 car.push_back(c6);
 car.push_back(c7);
 car.push_back(c8);
 car.push_back(c9);
 car.push_back(c10);
 car.push_back(c11);
 car.push_back(c12);
 
//Inicializo el cubo.
 Cubo.init(vert, car);
//TETRAEDRO 
_vertex3f p1t = _vertex3f(0, 1, 0);
_vertex3f p2t = _vertex3f(1, 0, 0);
_vertex3f p3t = _vertex3f(1, 1, 1);
_vertex3f p4t = _vertex3f(0, 0, 0);

//Caras del tetraedro
 _vertex3i c1t = _vertex3i(0, 2, 1);
 _vertex3i c2t = _vertex3i(0, 3, 2);
 _vertex3i c3t = _vertex3i(1, 3, 2);
 _vertex3i c4t = _vertex3i(1, 3, 0);


 vector<_vertex3f> vertT; //Vector de vertices del tetraedro
 vector<_vertex3i> carT;
 vertT.push_back(p1t);
vertT.push_back(p2t);
vertT.push_back(p3t);
vertT.push_back(p4t);

 carT.push_back(c1t);
 carT.push_back(c2t);
 carT.push_back(c3t);
 carT.push_back(c4t);
//inicializo el tetraedro.
Tetraedro.init(vertT, carT);
// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 1 Rafael Leyva");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
