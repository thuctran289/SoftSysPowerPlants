// compile via 
// compile first: 
// g++ Point.h -std=
//
//  g++ draw.cpp -lm -lGL -lGLU -lglut -std=c++11 -o draw

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Generation.h"
#include <chrono>
#include <thread>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawBridge(Bridge* bridge);
void drawBeam(Beam* beam);
void drawPoint(Point* p);

using namespace std;
using namespace std::this_thread; // For sleep
using namespace std::chrono;  // For sleep

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {

  // Use a single buffered window in RGB mode (as opposed to a double-buffered
  // window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Drawing beams");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glClear(GL_COLOR_BUFFER_BIT);

  // Window stretches from (-1,1) in the x-axis and y-axis.

  srand(time(NULL));

  Bridge* bridge = new Bridge();
  //bridge->generateBridge(10, .25,0);
  int road_points = 15;
  bridge->generateBridge(20, 1, road_points);
  bridge->stripBridge();

  // Beam* b = new Beam(p1, p2, r);
  // bridge->distributeLoad(Beam b, pair Force);

  drawBridge(bridge);
  glutSwapBuffers();


  int k = 1;
  while (k > 0) {
    sleep_for(nanoseconds(10000000));
    //cin >> k;
    //cout << "next frame...." << endl;
    for (int i = 0; i < 5; i++) { //What is the magic number 5???
      bridge->calculateForce(road_points);
    }
    //usleep(300);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBridge(bridge);
    glutSwapBuffers();
  }

  bool converged = false;
  while (!converged) {
    sleep_for(nanoseconds(500000));
    //cout << "next frame...." << endl;
    for (int i = 0; i < 5; i++) {
      converged = bridge->calculateForce(road_points);
    }
    //usleep(300);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBridge(bridge);
    glutSwapBuffers();
  }
  bridge->calculateFitness();
  cout << "Animation done, convergence found..." << endl;


  glutMainLoop();
}





void drawBridge(Bridge* bridge) {
  for (Beam* beam : bridge->getBeams()) {
    drawBeam(beam);
  }
  for (Point* point : bridge->getPoints()) {
    drawPoint(point);
  }
}

void drawBeam(Beam* beam) {
  glBegin(GL_LINES);
    double color = beam->getStress();
    if (color < 0) 
      glColor3f(1, 1, 0);
    else 
      glColor3f(color, 0, 0);
  /*if(beam->beamType == 1) 
    glColor3f(0,1,0);*/

    glVertex2f(beam->p1->x, beam->p1->y);
    glVertex2f(beam->p2->x, beam->p2->y);
  glEnd();
}

void drawPoint(Point* p) {
  double x = p->x;
  double y = p->y;
  glBegin(GL_POLYGON);
    if (p->fixed) glColor3f(0, 0, 1);
    else if (p->road) glColor3f(0,1,1);
    else glColor3f(0, 1, 0); 
    glVertex3f(x - 0.02, y - 0.025, 0);
    glVertex3f(x + 0.02, y - 0.025, 0);
    glVertex3f(x, y + 0.025, 0);
  glEnd();
}