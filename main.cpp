#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

void init();      
void draw_test();

void keybord_test(GLubyte key, GLint x, GLint y);
void keybord_test2(GLint key, GLint x, GLint y);

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;

//armazena os vértices de um objeto
struct VERTEX
{
  int x;
  int y;
};
//armazena a descrição geométrica de um objeto
struct OBJECT
{
  VERTEX *vertices;
  int nrvertices;
};

int t_x = 0; 
int t_y = 0;

int control = 0; // 1 up, 2 down, 3 left, 4 right, o centro

int t_x_inc = 0; 
int t_y_inc = 0;

float s_x_inc = 1; 
float  s_y_inc = 1;

OBJECT *object; //objeto global que será desenhado

OBJECT *create_object()
{
  OBJECT *obj = (OBJECT *)malloc(sizeof(OBJECT));
  obj->nrvertices = 5;
  obj->vertices = (VERTEX *)malloc(obj->nrvertices * sizeof(VERTEX));
  obj->vertices[0].x = 250;
  obj->vertices[0].y = 130;
  obj->vertices[1].x = 250;
  obj->vertices[1].y = 170;
  obj->vertices[2].x = 220;
  obj->vertices[2].y = 190;
  obj->vertices[3].x = 190;
  obj->vertices[3].y = 170;
  obj->vertices[4].x = 190;
  obj->vertices[4].y = 130;
  return obj;
}

VERTEX calculate_base(OBJECT *obj) {
  VERTEX less_y = obj->vertices[0];

  for (int i = 0; i < obj->nrvertices; i++) 
   if (less_y.y > obj->vertices[i].y)
    less_y = obj->vertices[i];
  
  std::cout<< less_y.x << ',' << less_y.y << '\n'; 

  return less_y;
}

VERTEX calculate_top(OBJECT *obj) {
  VERTEX greater_y = obj->vertices[0];

  for (int i = 0; i < obj->nrvertices; i++) 
   if (greater_y.y < obj->vertices[i].y)
    greater_y = obj->vertices[i];
  
  return greater_y;
}

VERTEX calculate_left(OBJECT *obj) {
  VERTEX greater_x = obj->vertices[0];

  for (int i = 0; i < obj->nrvertices; i++) 
   if (greater_x.x < obj->vertices[i].x)
    greater_x = obj->vertices[i];
  
  return greater_x;
}

VERTEX calculate_right(OBJECT *obj) {
  VERTEX lesser_x = obj->vertices[0];

  for (int i = 0; i < obj->nrvertices; i++) 
   if (lesser_x.x > obj->vertices[i].x)
    lesser_x = obj->vertices[i];
  
  return lesser_x;
}

VERTEX calculate_centroid(OBJECT *obj)
{
  int i;
  VERTEX cent;
  cent.x = 0;
  cent.y = 0;
  for (i = 0; i < obj->nrvertices; i++)
  {
    cent.x += obj->vertices[i].x;
    cent.y += obj->vertices[i].y;
  }
  cent.x /= obj->nrvertices;
  cent.y /= obj->nrvertices;
  return cent;
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
  object = create_object(); //cria o objeto
}

void draw_object(OBJECT *obj)
{
  int i;
  glBegin(GL_POLYGON); //desenha uma linha
  for (i = 0; i < obj->nrvertices; i++)
  {
    glVertex2i(obj->vertices[i].x, obj->vertices[i].y);
    
  }
  glEnd();
}

void draw_test()
{
  glClear(GL_COLOR_BUFFER_BIT); //desenha o fundo (limpa a janela)
  glMatrixMode(GL_MODELVIEW); //garante que a matrix seja a ModelView
  glLoadIdentity(); //carrega a matrix identidade
  
  VERTEX cent = calculate_centroid(object);

  glColor3f(0.0, 0.0, 1.0); //altera o atributo de cor
  

  glTranslatef(cent.x, cent.y, 0);  
  glScalef(s_x_inc, s_y_inc, 0);  

  glTranslatef((GLfloat)t_x_inc, (GLfloat)t_y_inc, 0);
  glTranslatef(-cent.x, -cent.y, 0);  

  draw_object(object); //desenha o objeto
  glutPostRedisplay();
  
  glFlush(); //processa as rotinas OpenGL o mais rápido possível
}


// funcao para processar eventos de teclado
void keybord_test(GLubyte key, GLint x, GLint y)
{
  GLint m = glutGetModifiers();
  
  if(m == GLUT_ACTIVE_SHIFT)
    std::cout<<"Shift ou Caps ";
  else if(m == GLUT_ACTIVE_CTRL)
    std::cout<<"Control ";
  else if(m == GLUT_ACTIVE_ALT)
    std::cout<<"Alt "; 
  
  //VERIFICAR TABELA ASCII QUANDO O CTRL ESTIVER PRECIONADO COM ALGUMA 
  //LETRA  
  if(m == GLUT_ACTIVE_CTRL && (GLint) key == 4)
    exit(EXIT_SUCCESS);

  // std::cout<<"Tecla: "<<(GLint) key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
  //ESC = 27
  if (key == 27)
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (key == 97){
      s_x_inc *= 0.99; // tecla para esquerda
    }
    if (key == 100){
      s_x_inc *= 1.01; // tecla para direita
    }
    if (key == 115){ // s
      s_y_inc *= 0.99; // tecla para baixo
    }
    if (key == 119){ // w
      s_y_inc *= 1.01; // tecla para cima
    }

  glutPostRedisplay();

}

void keybord_test2(GLint key, GLint x, GLint y)
{
//GLUT_KEY_F1 .. GLUT_KEY_F12
//GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT
//GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME etc.  
  
  std::cout<<"\nTecla especial: "<<key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
  if(key == GLUT_KEY_F11)
    glutFullScreen();

  if (key == 100){
    t_x_inc -= 1; // tecla para esquerda
  }
  if (key == 102){
    t_x_inc += 1; // tecla para direita
  }
  if (key == 103){
    t_y_inc -= 1; // tecla para baixo
  }
  if (key == 101){
    t_y_inc += 1; // tecla para cima
  }
  printf("\nt_x_inc = %d", t_x_inc);
  printf("\nt_y_inc = %d", t_y_inc);
  glutPostRedisplay();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("OpenGL - Transformacoes");
  
  init();
  glutDisplayFunc(draw_test);
  
  
  glutKeyboardFunc(keybord_test);
  glutSpecialFunc(keybord_test2);

  glutMainLoop();
  
  return EXIT_SUCCESS;
}


