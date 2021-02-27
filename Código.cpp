// PROJETO  EM C++ COM O OBJETIVO DE CRIAR 10 OBJETOS 3D no OpenGl

#include<iostream>
#include<conio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/freeglut.h>
#include <windows.h>
#include <gl/glut.h>
#include <fstream>            // File library
#include <iostream>
using namespace std;

double rotate_y=0; 
double rotate_x=0;
bool iluminacao = true;  //variavel de iluminação
int tecladoObj;  //selecionar um objeto 
bool visivel = true;

int numObjects;
int ObjectList[10];         // Lista de Objetos, 10 é o número máximo
int x[10], y[10], z[10];	// coordenadas dos objetos
float r[10], g[10], b[10], r1[10], r2[10], r3[10];  // cores dos objetos

char title[] = "OpenGL-PUC PR (ProjetoFinal)";
GLfloat nRange = 180;   //Inicio camera

float rAngle = 0.0;

void update(int value) {
	rAngle += 1.0f;
	if (rAngle > 360) rAngle -= 360;
	glutPostRedisplay(); 
	glutTimerFunc(25, update, 0);
}

void initGL() {
	glClearDepth(1.0f);                  
	glEnable(GL_DEPTH_TEST);   
	glDepthFunc(GL_LEQUAL);    
	glShadeModel(GL_FLAT);   

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };	   // "cor" 
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };// "brilho" 
	GLfloat posicaoLuz[4] = { 0, 20.0, 100.0, 1.0 }; //posição da luz

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 60;
	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
}

//função cubo
void cubo(float a) {
		
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-a / 2, a / 2, a / 2);
    glVertex3f(-a / 2, -a / 2, a / 2);
    glVertex3f(a / 2, a / 2, a / 2);
    glVertex3f(a / 2, -a / 2, a / 2);
    glVertex3f(a / 2, a / 2, -a / 2);
    glVertex3f(a / 2, -a / 2, -a / 2);
    glVertex3f(-a / 2, a / 2, -a / 2);
    glVertex3f(-a / 2, -a / 2, -a / 2);
    glVertex3f(-a / 2, a / 2, a / 2);
    glVertex3f(-a / 2, -a / 2, a / 2);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-a / 2, a / 2, -a / 2);
    glVertex3f(-a / 2, a / 2, a / 2);
    glVertex3f(a / 2, a / 2, -a / 2);
    glVertex3f(a / 2, a / 2, a / 2);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(a / 2, -a / 2, -a / 2);
    glVertex3f(a / 2, -a / 2, a / 2);
    glVertex3f(-a / 2, -a / 2, -a / 2);
    glVertex3f(-a / 2, -a / 2, a / 2);
    glEnd();
}

//função cilindro
void cilindro(float radius, float height) {
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-rAngle, 0.0f, 1.0f, 0.0f);
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
	glTranslatef(100,0,0);	
    
    double x, z;
    glBegin(GL_TRIANGLE_FAN); //BASE
    glVertex3f(0.0, 0.0, 0.0); // CENTRO
    for (double angle = 0.0; angle < (2.0 * M_PI); angle += (2.0 * M_PI / 36.0))
    {
        x = radius * sin(angle);
        z = radius * cos(angle);
        glVertex3f(x, 0.0, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); //TOPO
    glVertex3f(0.0, height, 0.0); // CENTRO
    for (double angle = 0.0; angle < (2.0 * M_PI); angle += (2.0 * M_PI / 36.0))
    {
        x = radius * sin(angle);
        z = radius * cos(angle);
        glVertex3f(x, height, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP); // LATERAL
    
    for (double angle = 0.0; angle < (2.0 * M_PI); angle += (2.0 * M_PI / 36.0))
    {
        x = radius * sin(angle);
        z = radius * cos(angle);
        glVertex3f(x, 0.0, z);
        glVertex3f(x, height, z);
    }
    glEnd();

}

//função cone
void cone(float r, float H)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	glRotatef(-rAngle, 0.0f, 1.0f, 0.0f);
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
	glTranslatef(100,0,0);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
        glVertex3f(r * sin(angle), 0, r * cos(angle));
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, H, 0);
    for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
        glVertex3f(r * sin(angle), 0, r * cos(angle));
    glEnd();
    glTranslatef(-8, 0, 0);
}

//CANUDO
void canudo(float r, float r2, float h){
	glBegin(GL_TRIANGLE_STRIP); // canudo1
		for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
		{
			glVertex3f(r * sin(angle), 0 , r * cos(angle) );
			glVertex3f(r * sin(angle), h , r * cos(angle) );
		}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP); // canudo2
		for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
		{
			glVertex3f(r2 * sin(angle), 0 , r2 * cos(angle) );
			glVertex3f(r2 * sin(angle), h , r2 * cos(angle) );
		}
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP); // espessura
		for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
		{
			glVertex3f(r * sin(angle), 0 , r * cos(angle) );
			glVertex3f(r2 * sin(angle), 0, r2 * cos(angle) );
			
		}
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP); // espessura2
		for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
		{
			glVertex3f(r * sin(angle), h , r * cos(angle) );
			glVertex3f(r2 * sin(angle), h, r2 * cos(angle) );
			
		}
	glEnd();
		
}

void DisplayFileRead(const char * fileName) // na versão 2015 (char * fileName)
{
    fstream inStream;
    inStream.open(fileName, ios::in); // abre o arquivo
    if (inStream.fail()) return;      //falha na abertura do arquivo
    cout << "Abertura do arquivo com sucesso ..." << endl;
    inStream >> numObjects;              // lê primeira linha do arquivo, número de objetos 
    cout << numObjects << " Objetos na cena ..." << endl;
    for (int i = 1; i <= numObjects; i++) { // leitura das demais linhas, ID dos objetos, posição e cor
        inStream >> ObjectList[i] >> x[i] >> y[i] >> z[i] >> r[i] >> g[i] >> b[i] >> r1[i] >> r2[i] >> r3[i];
    }
    inStream.close();                 // fecha o arquivo
}


void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		glMatrixMode(GL_MODELVIEW);        
		glLoadIdentity();   
	
		glRotatef(-rAngle, 0.0f, 1.0f, 0.0f);
		glRotatef( rotate_x, 1.0, 0.0, 0.0 );
   		glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
		glTranslatef(100,0,0);
		
	
	if (visivel == true){
		
		for (int i = 1; i <= numObjects; i++) {
			glTranslatef(x[i], y[i], z[i]);
			glColor3f(r[i], g[i], b[i]);
			glRotatef(r1[i], 1.0f, 0.0f, 0.0f);
			glRotatef(r2[i], 0.0f, 1.0f, 0.0f);
			glRotatef(r3[i], 0.0f, 0.0f, 1.0f);
			switch (ObjectList[i]) {
				case 1: //xicara
					if (tecladoObj == 1){
						glutSolidTeapot(50);
					}
					break;
				case 2: //cubo
					if (tecladoObj == 2){
						cubo(100);
					}
					break;
				case 3: //cone
					if (tecladoObj == 3){
						cone(50, 100);
					}
					break;
				case 4: // torus
					if (tecladoObj == 4){
						glutSolidTorus(20, 50, 50, 50);
					}
					break;
				case 5: //SPHERA
					if (tecladoObj == 5){
						glutSolidSphere(50, 60, 60);
					}
					break;
				case 6: // cilindro
					if (tecladoObj == 6){
				    	cilindro(50, 120);
				    }
					break;
				case 7:  // canudo
					if (tecladoObj == 7){
						canudo(20, 30, 120);
					}
					break;
				case 8:  //Icosa
					if (tecladoObj == 8){
						glScalef(80.0f, 80.0f, 80.0f);
						glutSolidIcosahedron();
						
					}
					break;
				case 9: //TETRA
					if (tecladoObj == 9){
						glScalef(80.0f, 80.0f, 80.0f);
						glutSolidTetrahedron();
					}
					break;
				case 0: //COMPOSTO
					if (tecladoObj == 0){
							//FIGURA COMPOSTA 
							glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
					    	canudo(20, 30, 120);
					    	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
					    	canudo(20, 30, 120);
					    	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
					    	canudo(20, 30, 120);
					    	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
					    	canudo(20, 30, 120);	
					}
					break;
			}
		}
		if (iluminacao == true){
			glEnable(GL_LIGHTING);
		}	    
		if (iluminacao == false){
			glDisable(GL_LIGHTING);
		}   
		glutSwapBuffers(); 	
	}
	else if(visivel == false){
		glutSwapBuffers(); 
	}
	
}

void teclado( int key, int x, int y) 
{
  //girar PARA A DIREITA
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 10;
   //girar PARA A ESQUERDA
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 10;
   //girar PARA A CIMA
  else if (key == GLUT_KEY_UP)
    rotate_x += 10;
   //girar PARA A BAIXO
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 10;
   //ligar e desligar a iluminação
  else if (key == GLUT_KEY_PAGE_UP){
  if (iluminacao){
  		iluminacao = false;
	  }
	else{
		iluminacao = true;
	}
}
   else if(key == GLUT_KEY_PAGE_DOWN){
   	if (visivel){
  		visivel = false;
	  }
	else{
		visivel = true;
   }
  }
	glutPostRedisplay();

}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
}

// Função callback chamada para gerenciar eventos do mouse
void mouse(int button, int state, int x, int y)
{
	float w = glutGet(GLUT_WINDOW_WIDTH);
    float h = glutGet(GLUT_WINDOW_HEIGHT);
    
	if (button == GLUT_LEFT_BUTTON)  //botão esquerdo
		if (state == GLUT_DOWN) {  // Zoom-in
			if (nRange >= 150) nRange -= 10;
		}
	if (button == GLUT_RIGHT_BUTTON)  // botão direito
		if (state == GLUT_DOWN) {  // Zoom-out
			if (nRange <= 300) nRange += 10;
		}
	reshape(w,h);
	glutPostRedisplay();
}

void trocar(unsigned char Key, int x, int y){  //TROCA DE OBJETOS SELEÇÃO
	switch(Key){
		case '1':
  			tecladoObj = 1;
  			break;
  		case '2':
  			tecladoObj = 2;
  			break;
  		case '3':
  			tecladoObj = 3;
  			break;
  		case '4':
  			tecladoObj = 4;
  			break;
  		case '5':
  			tecladoObj = 5;
  			break;
  		case '6':
  			tecladoObj = 6;
  			break;
  		case '7':
  			tecladoObj = 7;
  			break;
  		case '8':
  			tecladoObj = 8;
  			break;
  		case '9':
  			tecladoObj = 9;
  			break;
  		case '0':
  			tecladoObj = 0;
  			break;
	  }
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	DisplayFileRead("df.txt");
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480);     // Set the window's initial width & height
	glutInitWindowPosition(50, 50);   // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(render);          // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);         // Register callback handler for window re-size event
    glutSpecialFunc(teclado);
    glutKeyboardFunc(trocar);
    glutMouseFunc(mouse);
    glMatrixMode(GL_MODELVIEW);
	initGL();                         
	glutTimerFunc(25, update, 0);
	glutMainLoop();                   
	return 0;
}
