#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include "texturas/RGBImage.h"
#include <math.h>
#define PI 3.14159265f
using namespace std;


float camaraX = -20;
float camaraY = 15;
float camaraZ = 50;

float radio = sqrt(pow(camaraX, 2) + pow(camaraZ, 2));
float angulo = acos(camaraX / radio);
float centroY = 10;

string nombres[] = {
"bloque de tierra ABAJO.bmp",
"bloque de tierra gras ARRIBA.bmp",
"bloque de tierra gras LADO.bmp",
"pierna ABAJO.bmp",
"pierna ADELANTE.bmp",
"pierna ARRIBA.bmp",
"pierna ATRAS.bmp",
"pierna LADO.bmp",
"brazo ADELANTE Y ATRAS.bmp",
"brazo CONTRA Y CONTACTO TORSO.bmp",
"cabeza ABAJO.bmp",
"cabeza ADELANTE.bmp",
"cabeza ARRIBA.bmp",
"cabeza LADO.bmp",
"torso ADELANTE.bmp",
"torso ATRAS.bmp",
"torso DERECHA.bmp",
"torso IZQUIERDA.bmp",
"torso ABAJO.bmp",
"torso ARRIBA.bmp",
"cabeza ATRAS.bmp"
};

const int nombres_length = sizeof(nombres) / sizeof(string);

GLuint texturas[nombres_length];

void loadTexturesFromFile(const char* filename, int index) {
	RgbImage theTextMap(filename);
	glGenTextures(1, &texturas[index]);
	glBindTexture(GL_TEXTURE_2D, texturas[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTextMap.GetNumCols(),
		theTextMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTextMap.ImageData());
}

void cargarImagenes() {
	for (int i = 0; i < nombres_length; i++) {
		const string ruta = "texturas/" + nombres[i];
		loadTexturesFromFile(ruta.c_str(), i);
	}
}

int buscarTextura(string nombre) {
	for (int i = 0; i < nombres_length; i++) {
		if (nombres[i] == nombre) {
			return i;
		}
	}
	throw runtime_error("El nombre de monito especificado no existe :,v");
}

void iniciarVentana(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, (float)w / (float)h, 1, 200);
}
void inicializarLuces() {

	GLfloat luz_ambiente[] = { 0.2,0.2,0.2,1 };
	GLfloat luz_difusa[] = { 0.2,0.2,0.2,1 };
	GLfloat luz_specular[] = { 0.1,0.1,0.,1 };

	float reflejo[] = { 0,0,0,1 };
	float posicionLuz[] = { 0,70,0,1 };
	int sombra = 128;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_specular);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, reflejo);
	glMateriali(GL_FRONT, GL_SHININESS, sombra);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

	GLfloat luz_ambiente1[] = { 0.1,0.1,0.1,1 };
	GLfloat luz_difusa1[] = { 0.1,0.1,0.1,1 };
	GLfloat luz_specular1[] = { 0.1,0.1,0.1,1 };

	float posicionLuz1[] = { -50,0,0,1 };
	float posicionLuz2[] = { 0,0,50,1 };
	float posicionLuz3[] = { 50,0,0,1 };
	float posicionLuz4[] = { 0,0,-50,1 };

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicionLuz1);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, luz_ambiente1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luz_difusa1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luz_specular1);
	glLightfv(GL_LIGHT2, GL_POSITION, posicionLuz2);

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, luz_ambiente1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, luz_difusa1);
	glLightfv(GL_LIGHT3, GL_SPECULAR, luz_specular1);
	glLightfv(GL_LIGHT3, GL_POSITION, posicionLuz3);

	glEnable(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, luz_ambiente1);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, luz_difusa1);
	glLightfv(GL_LIGHT4, GL_SPECULAR, luz_specular1);
	glLightfv(GL_LIGHT4, GL_POSITION, posicionLuz4);

}

void ejes() {

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(50, 0, 0);
	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 50, 0);
	glColor3ub(0, 0, 255);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 50);
	glEnd();

	glPopMatrix();

}

//NOTA: esta funcion es para un bloque SIMETRICO
void dibujarTexturaBloque(string textura_nombre, float tamaño, float rotar_ejeX, float rotar_ejeY, float c_x, float c_y, float c_z) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[buscarTextura(textura_nombre)]);
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslated(c_x, c_y, c_z);
	glRotated(rotar_ejeY, 0, 1, 0);
	glRotated(rotar_ejeX, 1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(0, tamaño, 0);
	glTexCoord2f(1, 1); glVertex3d(tamaño, tamaño, 0);
	glTexCoord2f(1, 0); glVertex3d(tamaño, 0, 0);
	glTexCoord2f(0, 0); glVertex3d(0, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
//NOTA: esta funcion es para un bloque NO SIMETRICO
void dibujarTexturaBloque(string nombre_textura, float altura, float anchura, float rotar_ejeX, float rotar_ejeY, float rotar_ejeZ, float c_x, float c_y, float c_z) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[buscarTextura(nombre_textura)]);
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslated(c_x, c_y, c_z);
	glRotated(rotar_ejeX, 1, 0, 0);
	glRotated(rotar_ejeY, 0, 1, 0);
	glRotated(rotar_ejeZ, 0, 0, 1);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(0, altura, 0);
	glTexCoord2f(1, 1); glVertex3d(anchura, altura, 0);
	glTexCoord2f(1, 0); glVertex3d(anchura, 0, 0);
	glTexCoord2f(0, 0); glVertex3d(0, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void bloqueDeTierraGras(float coodenada_centroX, float coodenada_centroY, float coodenada_centroZ, float largo_y_ancho) {

	//A partir de aqui es el codigo para darle textura
	const float correcion = (largo_y_ancho / 2.f);

	//dibujar un lado del bloque EJE Z atras
	dibujarTexturaBloque("bloque de tierra gras LADO.bmp", largo_y_ancho, 0, 0, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);
	//dibujar un lado del bloque EJE Z adelante
	dibujarTexturaBloque("bloque de tierra gras LADO.bmp", largo_y_ancho, 0, 0, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ + correcion);
	//dibujar un lado del bloque EJE X izquierda
	dibujarTexturaBloque("bloque de tierra gras LADO.bmp", largo_y_ancho, 0, -90, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);
	//dibujar un lado del bloque EJE X derecha
	dibujarTexturaBloque("bloque de tierra gras LADO.bmp", largo_y_ancho, 0, -90, coodenada_centroX + correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);

	//textura top y bottom :V
	//textura en el TOP
	dibujarTexturaBloque("bloque de tierra gras ARRIBA.bmp", largo_y_ancho, 90, 0, coodenada_centroX - correcion, coodenada_centroY + correcion, coodenada_centroZ - correcion);
	//textura en el bottom
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 90, 0, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);

}

void bloqueDeTierra(float coodenada_centroX, float coodenada_centroY, float coodenada_centroZ, float largo_y_ancho) {

	//A partir de aqui es el codigo para darle textura
	const float correcion = (largo_y_ancho / 2.f);

	//dibujar un lado del bloque EJE Z atras
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 0, 0, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);
	//dibujar un lado del bloque EJE Z adelante
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 0, 0, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ + correcion);
	//dibujar un lado del bloque EJE X izquierda
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 0, -90, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);
	//dibujar un lado del bloque EJE X derecha
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 0, -90, coodenada_centroX + correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);

	//textura top y bottom :V
	//textura en el TOP
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 90, 0, coodenada_centroX - correcion, coodenada_centroY + correcion, coodenada_centroZ - correcion);
	//textura en el bottom
	dibujarTexturaBloque("bloque de tierra ABAJO.bmp", largo_y_ancho, 90, 0, coodenada_centroX - correcion, coodenada_centroY - correcion, coodenada_centroZ - correcion);

}

//piso de tierra como en mi barrio :,,,,,V SAQUENME DE PERU
void pisoDeTierra(float largo_ancho_bloque, float coordenadaOrigen[], float limite_izquierdo_direccionX, float limite_derecho_direccionX, float limite_atras_direccionZ, float limite_adelante_direccionZ, float c1_zona2D_PXZ[], float c2_zona2D_PXZ[]) {
	string mError = "Error en pisoDeTierra(float largo_ancho_bloque,float coordenadaOrigen[], float limite_izquierdo_direccionX, float limite_derecho_direccionX, float limite_adelante_direccionZ, float limite_atras_direccionZ): ";

	if (largo_ancho_bloque <= 0) {
		throw runtime_error(mError + "Bruh, dale causa como quieres que imprima un bloque de 0 centimetros PE");
	}
	if (limite_izquierdo_direccionX > limite_derecho_direccionX || limite_atras_direccionZ > limite_adelante_direccionZ) {
		throw runtime_error(mError + "El limite izquierda no puede estar a la derecha del limite derecho o el limite de atras no puede estar adelante del limite de adelante y viceversa. monito");
	}
	if (coordenadaOrigen[0]<limite_izquierdo_direccionX || coordenadaOrigen[0] >limite_derecho_direccionX || coordenadaOrigen[2] < limite_atras_direccionZ || coordenadaOrigen[2] >limite_adelante_direccionZ) {
		throw runtime_error(mError + "Papu, Las coordenadas de origen deben estar dentro de los limites especificados, (inserte sticker de monito).");
	}
	if (c1_zona2D_PXZ[0] > c2_zona2D_PXZ[0] || c1_zona2D_PXZ[1] > c2_zona2D_PXZ[1]) {
		throw runtime_error(mError + "Papu, Las coordenadas de la zona prohibida estan mal. Recuerda que c1 siempre esta más a la izquierda y abajo que c2");
	}

	float verdaderoOrigen[] = { (limite_izquierdo_direccionX < 0 ? -1 : 1) * (trunc((fabs(limite_izquierdo_direccionX) - fabs(coordenadaOrigen[0])) / largo_ancho_bloque) * largo_ancho_bloque) - coordenadaOrigen[0] ,(limite_atras_direccionZ < 0 ? -1 : 1) * (trunc((fabs(limite_atras_direccionZ) - fabs(coordenadaOrigen[2])) / largo_ancho_bloque) * largo_ancho_bloque) - coordenadaOrigen[2] };
	bloqueDeTierraGras(verdaderoOrigen[0], coordenadaOrigen[1], verdaderoOrigen[1], largo_ancho_bloque);
	for (float x = verdaderoOrigen[0]; x <= limite_derecho_direccionX; x += largo_ancho_bloque)
	{
		for (float z = verdaderoOrigen[1]; z <= limite_adelante_direccionZ; z += largo_ancho_bloque)
		{
			if (x >= c1_zona2D_PXZ[0] && x <= c2_zona2D_PXZ[0] && z >= c1_zona2D_PXZ[1] && z <= c2_zona2D_PXZ[1]) {
				continue; //no dibujar bloque en zona prohibida
			}
			bloqueDeTierraGras(x, coordenadaOrigen[1], z, largo_ancho_bloque);
		}
	}

}
//	texturas indices 0=atras, 1=adelante, 2=izquierda, 3=derecha, 4=top, 5=bottom
void bloque_con_textura_deforme(float coordenadasXYZ[], float dimensionesXYZ[], string indice_textura[], float rotacionXYZ[]) {
	glPushMatrix();

	glTranslated(coordenadasXYZ[0], coordenadasXYZ[1], coordenadasXYZ[2]);
	glRotated(rotacionXYZ[0], 1, 0, 0);
	glRotated(rotacionXYZ[1], 0, 1, 0);
	glRotated(rotacionXYZ[2], 0, 0, 1);
	glScaled(dimensionesXYZ[0], dimensionesXYZ[1], dimensionesXYZ[2]);
	glutSolidCube(1);

	glPopMatrix();

	//A partir de aqui es el codigo para darle textura
	const float correcionAltura = dimensionesXYZ[1] / 2;
	const float correcionAnchoX = dimensionesXYZ[0] / 2;
	const float correcionAnchoZ = dimensionesXYZ[2] / 2;
	//dibujar un lado del bloque EJE Z atras
	dibujarTexturaBloque(indice_textura[0], dimensionesXYZ[1], dimensionesXYZ[0], rotacionXYZ[0], rotacionXYZ[1], rotacionXYZ[2], coordenadasXYZ[0] - correcionAnchoX, coordenadasXYZ[1] - correcionAltura, coordenadasXYZ[2] - (correcionAnchoZ + 0.01));
	//dibujar un lado del bloque EJE Z adelante
	dibujarTexturaBloque(indice_textura[1], dimensionesXYZ[1], dimensionesXYZ[0], rotacionXYZ[0], rotacionXYZ[1], rotacionXYZ[2], coordenadasXYZ[0] - correcionAnchoX, coordenadasXYZ[1] - correcionAltura, coordenadasXYZ[2] + (correcionAnchoZ + 0.01));
	//dibujar un lado del bloque EJE X izquierda
	dibujarTexturaBloque(indice_textura[2], dimensionesXYZ[1], dimensionesXYZ[2], rotacionXYZ[0], -(90 + rotacionXYZ[1]), rotacionXYZ[2], coordenadasXYZ[0] - (correcionAnchoX + 0.01), coordenadasXYZ[1] - correcionAltura, coordenadasXYZ[2] - correcionAnchoZ);
	//dibujar un lado del bloque EJE X derecha
	dibujarTexturaBloque(indice_textura[3], dimensionesXYZ[1], dimensionesXYZ[2], rotacionXYZ[0], -(90 + rotacionXYZ[1]), rotacionXYZ[2], coordenadasXYZ[0] + (correcionAnchoX + 0.01), coordenadasXYZ[1] - correcionAltura, coordenadasXYZ[2] - correcionAnchoZ);

	//textura top y bottom :V
	//textura en el TOP
	dibujarTexturaBloque(indice_textura[4], dimensionesXYZ[2], dimensionesXYZ[0], 90 + rotacionXYZ[0], rotacionXYZ[1], rotacionXYZ[2], coordenadasXYZ[0] - correcionAnchoX, coordenadasXYZ[1] + (correcionAltura + 0.01), coordenadasXYZ[2] - correcionAnchoZ);
	//textura en el bottom
	dibujarTexturaBloque(indice_textura[5], dimensionesXYZ[2], dimensionesXYZ[0], 90 + rotacionXYZ[0], rotacionXYZ[1], rotacionXYZ[2], coordenadasXYZ[0] - correcionAnchoX, coordenadasXYZ[1] - (correcionAltura + 0.01), coordenadasXYZ[2] - correcionAnchoZ);

}

void escena1Steve() {
	//Pierna izquierda
	//texturas indices 0=atras, 1=adelante, 2=izquierda, 3=derecha, 4=top, 5=bottom
	float coordenada_pierna_izquierda[] = { 1,4,0 };
	string texturas_pierna[] = { "pierna ATRAS.bmp","pierna ADELANTE.bmp","pierna LADO.bmp","pierna LADO.bmp","pierna ARRIBA.bmp","pierna ABAJO.bmp" };
	float dimensiones_pierna[] = { 2,8,2 };
	float rotaciones_pierna_izquierda[] = { 0,0,0 };
	bloque_con_textura_deforme(coordenada_pierna_izquierda, dimensiones_pierna, texturas_pierna, rotaciones_pierna_izquierda);

	//pierna derecha
	float coordenada_pierna_derecha[] = { -1,4,0 };
	float rotaciones_pierna_derecha[] = { 0,0,0 };
	bloque_con_textura_deforme(coordenada_pierna_derecha, dimensiones_pierna, texturas_pierna, rotaciones_pierna_derecha);

	//torso
	//recordando texturas indices 0=atras, 1=adelante, 2=izquierda, 3=derecha, 4=top, 5=bottom
	float coordenada_torso[] = { 0,12,0 };
	string texturas_torso[] = { "torso ATRAS.bmp","torso ADELANTE.bmp","torso DERECHA.bmp","torso IZQUIERDA.bmp","torso ARRIBA.bmp","torso ABAJO.bmp" };
	float dimensiones2[] = { 4,8,2 };
	float rotaciones_pierna_torso[] = { 0,0,0 };
	bloque_con_textura_deforme(coordenada_torso, dimensiones2, texturas_torso, rotaciones_pierna_torso);

	//cabeza
	float coordenadas_cabeza[] = { 0,18,0 };
	//recordando texturas indices 0=atras, 1=adelante, 2=izquierda, 3=derecha, 4=top, 5=bottom
	string texturas_cabeza[] = { "cabeza ATRAS.bmp","cabeza ADELANTE.bmp","cabeza LADO.bmp" ,"cabeza LADO.bmp","cabeza ARRIBA.bmp","cabeza ABAJO.bmp" };
	float dimensiones_cabeza[] = { 4.5,4.5,4.5 };
	float rotaciones_cabeza[] = { 0,0,0 };
	bloque_con_textura_deforme(coordenadas_cabeza, dimensiones_cabeza, texturas_cabeza, rotaciones_cabeza);

	//brazo izquierdo
	float coordenadas_brazo_izquierdo[] = { 3,12,0 };
	//recordando texturas indices 0=atras, 1=adelante, 2=izquierda, 3=derecha, 4=top, 5=bottom
	string texturas_brazo[] = { "brazo ADELANTE Y ATRAS.bmp","brazo ADELANTE Y ATRAS.bmp","brazo CONTRA Y CONTACTO TORSO.bmp","brazo CONTRA Y CONTACTO TORSO.bmp","bloque de tierra gras ARRIBA.bmp","bloque de tierra ABAJO.bmp" };
	float dimensiones_brazo_izquierdo[] = { 2,8,2 };
	float rotaciones_brazo_izquierdo[] = { 0,0,0 };
	bloque_con_textura_deforme(coordenadas_brazo_izquierdo, dimensiones_brazo_izquierdo, texturas_brazo, rotaciones_brazo_izquierdo);
	//brazo derecho
	float coordenadas_brazo_derecho[] = { -3,12,0 };
	//recordando texturas indices 0=atras, 1=adelante, 2=izquierda, 3=derecha, 4=top, 5=bottom
	float dimensiones_brazo_derecho[] = { 2,8,2 };
	float rotaciones_brazo_derecho[] = { 0,0,0 };
	bloque_con_textura_deforme(coordenadas_brazo_derecho, dimensiones_brazo_derecho, texturas_brazo, rotaciones_brazo_derecho);



}

void dibujarPilarArriba(float coordenada_inicial[], float ancho, float altura_limite) {
	float i;
	for (i = coordenada_inicial[1]; i < altura_limite; i += ancho)
	{
		bloqueDeTierra(coordenada_inicial[0], i, coordenada_inicial[2], ancho);
		
	}
	bloqueDeTierraGras(coordenada_inicial[0], i, coordenada_inicial[2], ancho);
}

float porcentajePi(float coordenada_actual, float c_final,float largo) {

	float largo_actual = fabs(c_final) - fabs(coordenada_actual);
	return largo_actual/ largo;
}

float calcularAlturaMontaña(float x_porcentaje, float z_porcentaje, float amplitud) {
	float altura = sin(PI*x_porcentaje) * amplitud + sin(PI * z_porcentaje) * amplitud;
	return altura > 0 ? altura : 0;
}

void montaña(float anchoBloque, float esquinaOrigen[], float largo, float altura) {
	string mError = "Error en montaña(float anchoBloque, float esquinaOrigen[], float largo, float altura): ";

	if (largo <= 0) {
		throw runtime_error(mError+"El largo de la montaña debe ser mayor a 0");
	}
	if (anchoBloque <= 0) {
		throw runtime_error(mError+"El ancho del bloque debe ser mayor a 0");
	}
	float cX_final = esquinaOrigen[0] + largo;
	float cZ_final = esquinaOrigen[2] + largo;

	for (float x = esquinaOrigen[0]; x <= cX_final; x += anchoBloque)
	{
		for (float z = esquinaOrigen[2]; z <= cZ_final; z += anchoBloque)
		{
			float c_temp[] = { x, esquinaOrigen[1], z};
			dibujarPilarArriba(c_temp, anchoBloque, esquinaOrigen[1] + calcularAlturaMontaña(porcentajePi(x,cX_final,largo), porcentajePi(z, cZ_final, largo), altura));
		}

	}
}

void dibujar() {

	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(radio * cos(angulo), camaraY, radio * sin(angulo), 0, centroY, 0, 0, 1, 0);
	glClearColor(255 / 255.0, 255 / 255.0, 210 / 255.0, 1);
	glPushMatrix();
	ejes();
	glPopMatrix();

	//codigo epicardo
	float coordenadaOrigen[] = { 0.f,-2.5f,0.f };
	//zona prohibida, es decir no se dibujará bloques en esa zona
	float c1XZ[] = { -2.5f,2.5f };
	float c2XZ[] = { 10.5f,11.f };
	pisoDeTierra(5, coordenadaOrigen, -100, 100, -100, 100, c1XZ, c2XZ);

	float coordenadaMontaña[] = { 0.f, -2.5f, 0.f };
	montaña(5, coordenadaMontaña, 50, 50);

	escena1Steve();
	//aqui irá la entrada a la mina uwu


	glutSwapBuffers();

}


void timer(int t) {

	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);

}


void teclado(int tecla, int x, int y) {
	cout << tecla << endl;

	switch (tecla)
	{
	case 100:
		angulo -= 0.05;
		break;
	case 102:
		angulo += 0.05;
		break;
	case 101:
		camaraY += 1;
		break;
	case 103:
		camaraY -= 1;
		break;
	case 105:
		radio += 2;
		break;
	case 104:
		radio -= 2;
		break;
	case 106:
		centroY += 2;
		break;
	case 107:
		centroY -= 2;
		break;
	default:
		break;
	}

}


int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1081, 762);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Bienvenidos a Gráficos en Computación");
	cargarImagenes();
	glutReshapeFunc(iniciarVentana),
		glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}