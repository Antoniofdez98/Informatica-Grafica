//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"
#include "file_ply_stl.hpp"

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  int i;
  glPointSize(grosor);
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  for (i = 0; i < vertices.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[i]);
  }
  glEnd();
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  b_normales_caras = false;
  b_normales_vertices = false;

  ambiente_difusa = _vertex4f(0.2, 0.4, 0.9, 1.0); //coeficientes ambiente y difuso
  especular = _vertex4f(0.5, 0.5, 0.5, 1.0);       //coeficiente especular
  brillo = 50;                                     //exponente del brillo
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);

  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  for (i = 0; i < caras.size(); i++)
  {
    if (i % 2 == 0)
    {
      glColor3f(r1, g1, b1);
      glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
      glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
      glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
    }
    else
    {
      glColor3f(r2, g2, b2);
      glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
      glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
      glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
    }
  }
  glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  switch (modo)
  {
  case POINTS:
    draw_puntos(r1, g1, b1, grosor);
    break;
  case EDGES:
    draw_aristas(r1, g1, b1, grosor);
    break;
  case SOLID_CHESS:
    draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);
    break;
  case SOLID:
    draw_solido(r1, g1, b1);
    break;
  case SOLID_ILLUMINATED_FLAT:
    draw_iluminacion_plana();
    break;
  case SOLID_ILLUMINATED_GOURAUD:
    draw_iluminacion_suave();
    break;
  }
}

//*************************************************************************
// dibujar con iluminacion
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana()
{
  int i;
  if (b_normales_caras == false)
  {
    calcular_normales_caras();
  }

  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT); //GL_SMOOTH
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glNormal3fv((GLfloat *)&normales_caras[i]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_iluminacion_suave()
{
  int i;
  if (b_normales_vertices == false)
  {
    calcular_normales_vertices();
  }

  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH); //GL_SMOOTH
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

    glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

    glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras()
{
  _vertex3f a1, a2, n;
  normales_caras.resize(caras.size());

  for (int i = 0; i < caras.size(); i++)
  {
    // obtener dos vectores en el triángulo y calcular el producto vectorial
    a1 = vertices[caras[i]._1] - vertices[caras[i]._0];
    a2 = vertices[caras[i]._2] - vertices[caras[i]._0];
    n = a1.cross_product(a2);
    // modulo
    float m = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
    // normalización
    normales_caras[i] = _vertex3f(n.x / m, n.y / m, n.z / m);
  }

  b_normales_caras = true;
}

void _triangulos3D::calcular_normales_vertices()
{
  int n, m, i;
  n = vertices.size();
  normales_vertices.resize(n);

  for (i = 0; i < n; i++)
  {
    normales_vertices[i].x = 0.0;
    normales_vertices[i].y = 0.0;
    normales_vertices[i].z = 0.0;
  }

  m = caras.size();

  for (i = 0; i < m; i++)
  {
    normales_vertices[caras[i]._0] += normales_caras[i];
    normales_vertices[caras[i]._1] += normales_caras[i];
    normales_vertices[caras[i]._2] += normales_caras[i];

    b_normales_vertices = true;
  }
}


//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
int i;
//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

}
//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

int _objeto_ply::parametros(char *archivo)
{
  int n_ver, n_car, i;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);

  for (i = 0; i < n_ver; i++)
  {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  caras.resize(n_car);

  for (i = 0; i < n_car; i++)
  {
    caras[i]._0 = car_ply[3 * i];
    caras[i]._1 = car_ply[3 * i + 1];
    caras[i]._2 = car_ply[3 * i + 2];
  }

  return (0);
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{

  int i, j, c;

  //vertices_aux -> es un vertice float de 3 puntos
  _vertex3f vertice_aux;

  //cara_aux -> es un vertice int de 3 puntos
  _vertex3i cara_aux;

  //num_aux -> número de vertex3f en perfil
  int num_aux;

  // tratamiento de los vértice

  //Cogemos el número de vertex3f de perfil
  num_aux = perfil.size();

  vertices.resize(num_aux * num);

  //Con esto colocamos los puntos
  //12 vertices en horizontal
  for (j = 0; j < num; j++)
  {
    //4 vertices en vertical
    for (i = 0; i < num_aux; i++)
    {

      //Coseno -> x
      //Seno -> z

      //La línea perfil[i].z siempre es 0 ya que tenemos ese valor establecido
      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));

      vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));

      //la y es igual en todas las caras
      vertice_aux.y = perfil[i].y;

      //se mete en el vector vértices
      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  // tratamiento de las caras

  c = 0;

  //Número de aristas que vamos a necesitar
  caras.resize(3 * (num_aux - 1) * num);

  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux - 1; i++)
    {

      //Construye una cara con triangulos hacia arriba
      //%(num-1) Cierra la cara

      //(0,5,4)
      //(0,1,5)
      caras[c]._0 = j * num_aux + i;
      caras[c]._2 = ((j + 1) % num) * num_aux + i + 1;
      caras[c]._1 = ((j + 1) % num) * num_aux + i;

      c++;

      //(1,6,5)
      //(1,2,6)
      caras[c]._0 = j * num_aux + i;
      caras[c]._2 = j * num_aux + i + 1;
      caras[c]._1 = ((j + 1) % num) * num_aux + i + 1;

      c++;
    }
  }

  // tapa inferior
  if (fabs(perfil[0].x) > 0.0)
  {
    vertice_aux.x = 0;
    vertice_aux.y = perfil[0].y;
    vertice_aux.z = 0;

    vertices.push_back(vertice_aux);

    //Usamos num porque va a haber 12 triangulos
    for (i = 0; i < num; i++)
    {
      //Vertice centro
      caras[c]._0 = vertices.size() - 1;
      //Vertice base
      caras[c]._2 = i * num_aux;
      //Vertice del lado
      if (num == (num - 1))
      {
        caras[c]._1 = 0;
      }
      else
      {
        caras[c]._1 = ((i + 1) % num) * num_aux;
      }

      c++;
    }
  }

  // tapa superior
  if (fabs(perfil[num_aux - 1].x) > 0.0)
  {
    vertice_aux.x = 0;
    vertice_aux.y = perfil[perfil.size() - 1].y;
    vertice_aux.z = 0;

    vertices.push_back(vertice_aux);

    for (i = 0; i < num; i++)
    {
      caras[c]._0 = vertices.size() - 1;
      caras[c]._2 = (i * num_aux) + num_aux - 1;

      if (i == (num - 1))
      {
        caras[c]._1 = num_aux - 1;
      }
      else
      {
        caras[c]._1 = num_aux * (i + 1) + num_aux - 1;
      }

      c++;
    }
  }
}

//************************************************************************
// objeto cono
//************************************************************************

_cono::_cono(float radio, float altura, int num)
{
  int i, j, c;
  _vertex3f vertice_aux;
  vector<_vertex3f> perfil;

  vertice_aux.x = radio;
  vertice_aux.y = 0.0;
  vertice_aux.z = 0.0;

  //Meto el primer lado del perfil
  perfil.push_back(vertice_aux);
  vertices.resize(num);

  //Meto los vértices en rotación
  //Solo necesitamos un for porque estamos metiendo solo una altura de vertices
  for (j = 0; j < num; j++)
  {
    vertice_aux.x = perfil[0].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                    perfil[0].z * sin(2.0 * M_PI * j / (1.0 * num));

    vertice_aux.z = -perfil[0].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                    perfil[0].z * cos(2.0 * M_PI * j / (1.0 * num));
    vertice_aux.y = perfil[0].y;

    vertices[j] = vertice_aux;
  }

  //Meto el vertice de altura
  vertice_aux.x = 0.0;
  vertice_aux.y = altura;
  vertice_aux.z = 0.0;

  vertices.push_back(vertice_aux);

  //Pinto las caras
  caras.resize(2 * num);
  c = 0;
  for (j = 0; j < num; j++)
  {
    caras[c]._0 = vertices.size() - 1;
    caras[c]._1 = j;

    //Con % num enlazo la primera con la última
    caras[c]._2 = (j + 1) % num;

    c++;
  }

  //Tapa inferior
  if (fabs(perfil[0].x) > 0.0)
  {
    vertice_aux.x = 0;
    vertice_aux.y = 0;
    vertice_aux.z = 0;
    vertices.push_back(vertice_aux);

    for (i = 0; i < num; i++)
    {

      //Vertice centro
      caras[c]._0 = vertices.size() - 1;
      //Vertice de enfrente
      caras[c]._1 = i;
      //Vertice del lado
      caras[c]._2 = (i + 1) % num;

      c++;
    }
  }
}
//************************************************************************
// objeto cilindro
//************************************************************************
_cilindro::_cilindro(float radio, int num)
{
  int i, j, c, num_aux;
  _vertex3f vertice_aux;
  vector<_vertex3f> perfil;

  //Voy a meter al primer perfil de mi cilindro 2 puntos
  for (float k = -0.5; k <= 1.0; k = k + 1.5)
  {
    vertice_aux.x = radio;
    vertice_aux.y = k;
    vertice_aux.z = 0.0;
    perfil.push_back(vertice_aux);
  }

  num_aux = perfil.size();
  vertices.resize(num_aux * num);

  //Pinto todos los vertices en rotación
  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux; i++)
    {
      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));

      vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));

      vertice_aux.y = perfil[i].y;

      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  //Pinto las caras
  caras.resize(4 * (num_aux - 1) * num);
  c = 0;

  for (j = 0; j < num; j++)
    for (i = 0; i < num_aux - 1; i++)
    {
      caras[c]._0 = j * num_aux + i;
      caras[c]._2 = ((j + 1) % num) * num_aux + i + 1;
      caras[c]._1 = ((j + 1) % num) * num_aux + i;

      c++;

      caras[c]._0 = j * num_aux + i;
      caras[c]._2 = j * num_aux + i + 1;
      caras[c]._1 = ((j + 1) % (num)) * num_aux + i + 1;

      c++;
    }

  //tapa inferior
  if (fabs(perfil[0].x) > 0.0)

  {
    vertice_aux.x = 0;
    vertice_aux.y = -0.5;
    vertice_aux.z = 0;

    vertices.push_back(vertice_aux);
    for (i = 0; i < num; i++)
    {
      caras[c]._0 = vertices.size() - 1;
      caras[c]._2 = i * num_aux;

      if (i == (num - 1))
      {
        caras[c]._1 = 0;
      }
      else
      {
        caras[c]._1 = (i + 1) * num_aux;
      }

      c++;
    }
  }

  // tapa superior
  if (fabs(perfil[num_aux - 1].x) > 0.0)
  {
    vertice_aux.x = 0;
    vertice_aux.y = 1.0;
    vertice_aux.z = 0;

    vertices.push_back(vertice_aux);

    for (i = 1; i < num; i++)
    {
      caras[c]._0 = vertices.size() - 1;
      caras[c]._2 = (i * num_aux) - 1;
      caras[c]._1 = (i * num_aux) + 1;

      c++;
    }
  }
}
//************************************************************************
// objeto esfera
//************************************************************************

_esfera::_esfera(int radio, int num)
{
  int num_aux, i, j, c;
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  _rotacion esfera;

  for (int i = 1; i < num; i++)
  {
    vertice_aux.x = cos(i * M_PI / num - M_PI / 2) * radio;
    vertice_aux.y = sin(i * M_PI / num - M_PI / 2) * radio;
    vertice_aux.z = 0.0;
    perfil.push_back(vertice_aux);
  }

  esfera.parametros(perfil, num, 1);
  vertices = esfera.vertices;
  caras = esfera.caras;
}

