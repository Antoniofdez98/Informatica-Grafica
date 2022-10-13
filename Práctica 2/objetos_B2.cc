//**************************************************************************
// Práctica 2
//**************************************************************************

#include "objetos_B2.h"
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
// dibujar en modo sólido con un único color
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
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores()
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glColor3f(colores_caras[i].r, colores_caras[i].g, colores_caras[i].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
  switch (modo)
  {
  case POINTS:
    draw_puntos(r, g, b, grosor);
    break;
  case EDGES:
    draw_aristas(r, g, b, grosor);
    break;
  case SOLID:
    draw_solido(r, g, b);
    break;
  case SOLID_COLORS:
    draw_solido_colores();
    break;
  }
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
  int i;
//vertices
vertices.resize(8);

vertices[0].x = -tam; vertices[0].y = 0; vertices[0].z = tam;
vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
vertices[2].x = tam; vertices[2].y = 0; vertices[2].z = -tam;
vertices[3].x = -tam; vertices[3].y = 0; vertices[3].z = -tam;
vertices[4].x = -tam; vertices[4].y = 2*tam; vertices[4].z = tam;
vertices[5].x = tam; vertices[5].y = 2*tam; vertices[5].z = tam;
vertices[6].x = tam; vertices[6].y = 2*tam; vertices[6].z = -tam;
vertices[7].x = -tam; vertices[7].y = 2*tam; vertices[7].z = -tam;

// triangulos
caras.resize(12);

caras[0]._0=0; caras[0]._1=1; caras[0]._2=5;
caras[1]._0=0; caras[1]._1=4; caras[1]._2=5;
caras[2]._0=1; caras[2]._1=2; caras[2]._2=6;
caras[3]._0=1; caras[3]._1=5; caras[3]._2=6;
caras[4]._0=2; caras[4]._1=3; caras[4]._2=7;
caras[5]._0=2; caras[5]._1=6; caras[5]._2=7;
caras[6]._0=3; caras[6]._1=0; caras[6]._2=4;
caras[7]._0=3; caras[7]._1=4; caras[7]._2=7;
caras[8]._0=0; caras[8]._1=1; caras[8]._2=3;
caras[9]._0=1; caras[9]._1=2; caras[9]._2=3;
caras[10]._0=4; caras[10]._1=5; caras[10]._2=6;
caras[11]._0=4; caras[11]._1=6; caras[11]._2=7;

  // colores
  colores_caras.resize(12);
  for (i = 0; i < 12; i++)
  {
    colores_caras[i].r = (rand() % 1000) / 1000.0;
    colores_caras[i].g = (rand() % 1000) / 1000.0;
    colores_caras[i].b = (rand() % 1000) / 1000.0;
  }
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

  // colores
  colores_caras.resize(6);
  for (i = 0; i < 6; i++)
  {
    colores_caras[i].r = (rand() % 1000) / 1000.0;
    colores_caras[i].g = (rand() % 1000) / 1000.0;
    colores_caras[i].b = (rand() % 1000) / 1000.0;
  }
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::parametros(char *archivo)
{
  int n_ver, n_car, i, k;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);
  k = 0;

  for (i = 0; i < n_ver; i++)
  {
    vertices[i]._0 = ver_ply[k++];
    vertices[i]._1 = ver_ply[k++];
    vertices[i]._2 = ver_ply[k++];
  }

  k = 0;
  for (i = 0; i < n_car; i++)
  {
    caras[i]._0 = car_ply[k++];
    caras[i]._1 = car_ply[k++];
    caras[i]._2 = car_ply[k++];
  }

  colores_caras.resize(n_car);
  for (i = 0; i < n_car; i++)
  {
    colores_caras[i].r = (rand() % 1000) / 1000.0;
    colores_caras[i].g = (rand() % 1000) / 1000.0;
    colores_caras[i].b = (rand() % 1000) / 1000.0;
  }
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo)
{
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio, altura;

  // giramos el perfil el num de veces
  //  si es cilindro = 0, si es cono = 1, si es esfera = 2

  if (tipo == 2)
  {
    radio = sqrt((perfil[0].x * perfil[0].x) + (perfil[0].y * perfil[0].y));
  }

  else if (tipo == 0 || tipo == 1)
  {
    radio = abs(perfil[0].x);
    altura = abs(perfil[1].y);
  }
  // tratamiento de los vértice

  num_aux = perfil.size();

  // si es un cono no rotamos el punto de arriba
  if (tipo == 1)
  {
    num_aux = 1;
  }

  vertices.resize(num_aux * num + 2);
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

  // tratamiento de las caras
  caras.resize(2 * (num_aux - 1) * num + 2 * num);
  int c = 0;
  if (tipo == 0 || tipo == 2)
  {
    for (j = 0; j < num - 1; j++)
    {
      for (i = 0; i < num_aux - 1; i++)
      {
        caras[c]._0 = i + j * num_aux;
        caras[c]._1 = i + num_aux + 1 + j * num_aux;
        caras[c]._2 = num_aux + i + j * num_aux;
        c++;

        caras[c]._0 = i + j * num_aux;
        caras[c]._1 = i + 1 + j * num_aux;
        caras[c]._2 = i + num_aux + 1 + j * num_aux;

        c++;
      }
    }

    // Ultima cara con la primera
    int verts_ult_perfil = j * num_aux;
    for (i = 0; i < num_aux - 1; i++)
    {
      caras[c]._0 = i + verts_ult_perfil;
      caras[c]._1 = i + 1;
      caras[c]._2 = i;
      c++;
      caras[c]._0 = i + verts_ult_perfil;
      caras[c]._1 = i + 1 + verts_ult_perfil;
      caras[c]._2 = i + 1;
      c++;
    }
  }
  // tapa inferior
  if (fabs(perfil[0].x) > 0.0)
  {
    vertice_aux.x = 0.0;
    if (tipo == 0)
      vertice_aux.y = perfil[0].y;
    else if (tipo == 1)
      vertice_aux.y = 0.0;
    else if (tipo == 2)
      vertice_aux.y = -radio;
    vertice_aux.z = 0.0;
    vertices[num * num_aux] = vertice_aux;

    for (i = 0; i < num; i++)
    {
      caras[c]._0 = num * num_aux; // el del centro
      caras[c]._1 = i * num_aux;
      caras[c]._2 = ((i + 1) % num) * num_aux;
      // SI no hicieramos módulo sería (i+1)*num_aux
      c++;
    }
  }

  // tapa superior
  if (fabs(perfil[num_aux - 1].x) > 0.0)
  {
    vertice_aux.x = 0.0;
    if (tipo == 0)
      vertice_aux.y = perfil[num_aux - 1].y;
    else if (tipo == 1)
      vertice_aux.y = altura;
    else if (tipo == 2)
      vertice_aux.y = radio;
    vertice_aux.z = 0.0;
    vertices[num * num_aux + 1] = vertice_aux;
    if (tipo == 0 || tipo == 2)
    {
      for (i = 0; i < num - 1; i++) // num-1 -> casi todas de primeras y cara de ult con primero de forma indepe
      {
        caras[c]._0 = num * num_aux + 1; // el del centro
        caras[c]._1 = i * num_aux + (num_aux - 1);
        caras[c]._2 = (i + 1) * num_aux + (num_aux - 1);
        c++;
      }
      //última cara
      caras[c]._0 = num * num_aux + 1;           // el del centro
      caras[c]._1 = i * num_aux + (num_aux - 1); // el ult
      caras[c]._2 = (num_aux - 1);               // el primero
      c++;
    }
    else if (tipo == 1) // tipo =1 --> Cono
    {
      for (j = 0; j < num; j++)
      {
        caras[c]._0 = num * num_aux + 1; // el del centro
        caras[c]._1 = j * num_aux;
        caras[c]._2 = num_aux * ((j + 1) % num); // Procesamos la última cara
        c++;
      }
    }
  } // Fin tapa superior

  colores_caras.resize(c);

  for (int i = 0; i < c; i++)
  {
    colores_caras[i].r = (rand() % 1000) / 1000.0;
    colores_caras[i].g = (rand() % 1000) / 1000.0;
    colores_caras[i].b = (rand() % 1000) / 1000.0;
  }

} // Fin método

//************************************************************************
// objeto esfera
//************************************************************************

_esfera::_esfera(float radio, int n, int m)
{
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  for (int i = 1; i < n; i++)
  {
    vertice_aux.x = radio * cos(M_PI * i / n - M_PI / 2.0);
    vertice_aux.y = radio * sin(M_PI * i / n - M_PI / 2.0);
    vertice_aux.z = 0.0;
    perfil.push_back(vertice_aux);
  }
  parametros(perfil, m, 2);
}

//************************************************************************
// objeto cono
//************************************************************************

_cono::_cono(float radio, float altura, int m)
{
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  vertice_aux.x = radio;
  vertice_aux.y = 0.0;
  vertice_aux.z = 0.0;
  perfil.push_back(vertice_aux);
  vertice_aux.x = 0.0;
  vertice_aux.y = altura;
  vertice_aux.z = 0.0;
  perfil.push_back(vertice_aux);
  parametros(perfil, m, 1.0);
}

//************************************************************************
// objeto cilindro
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int m)
{
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  vertice_aux.x = radio;
  vertice_aux.y = -altura / 2.0;
  vertice_aux.z = 0.0;
  perfil.push_back(vertice_aux);
  vertice_aux.x = radio;
  vertice_aux.y = altura / 2.0;
  vertice_aux.z = 0.0;
  perfil.push_back(vertice_aux);
  parametros(perfil, m, 0);
}

//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice

  num_aux = poligono.size();
  vertices.resize(num_aux * 2);
  for (i = 0; i < num_aux; i++)
  {
    vertices[2 * i] = poligono[i];
    vertices[2 * i + 1].x = poligono[i].x + x;
    vertices[2 * i + 1].y = poligono[i].y + y;
    vertices[2 * i + 1].z = poligono[i].z + z;
  }

  // tratamiento de las caras

  caras.resize(num_aux * 2);
  int c = 0;
  for (i = 0; i < num_aux; i++)
  {
    caras[c]._0 = i * 2;
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
    caras[c]._0 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2) + 1;
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
  }

  // colores
  colores_caras.resize(num_aux * 2);

  for (int i = 0; i < num_aux * 2; i++)
  {
    colores_caras[i].r = (rand() % 1000) / 1000.0;
    colores_caras[i].g = (rand() % 1000) / 1000.0;
    colores_caras[i].b = (rand() % 1000) / 1000.0;
  }
}