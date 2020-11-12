/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: arous
 *
 * Created on 6. Mai 2018, 10:26
 */

#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

#include "Engine.h"
using namespace std;




//void Init() {
//    // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
//    // durchgeführt werden müssen
//    glEnable(GL_DEPTH_TEST);
//    glClearDepth(1.0);
//}
//
//void RenderScene() //Zeichenfunktion
//{
//   
//    
//    // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
//    glLoadIdentity(); // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
//    glClearColor(1.0, 0.5, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//      gluLookAt(0.,0. ,1., 0., 0., 0., 0., 1., 0.);
//
//
//   float radius = 2., halfLength = 0.5;
//   int slices = 4;
//  for(int i=0; i<slices; i++) {
//    float theta = ((float)i)*2.0* M_PI;
//
//float nextTheta = ((float)i+1)*2.0* M_PI;
// 
////glColor4f( 1.0, 1.0, 1.0, 1.0);
//
//glBegin(GL_TRIANGLE_STRIP);
///*vertex at middle of end */ glVertex3f(0.0, halfLength, 0.0);
///*vertices at edges of circle*/ glVertex3f(radius*cos(theta), halfLength, radius*sin(theta));
//                                          glVertex3f (radius*cos(nextTheta), halfLength, radius*sin(nextTheta));
///* the same vertices at the bottom of the cylinder*/
// glVertex3f (radius*cos(nextTheta), -halfLength, radius*sin(nextTheta));
//glVertex3f(radius*cos(theta), -halfLength, radius*sin(theta));
//glVertex3f(0.0, -halfLength, 0.0);
//glEnd();
// 
//}
//   glutSwapBuffers();
//    
//   
//   
//}
//
//void Reshape(int width, int height) {
//
//    // Hier finden die Reaktionen auf eine Veränderung der Größe des 
//    // Graphikfensters statt
//    // Matrix für Transformation: Frustum->viewport
//    glMatrixMode(GL_PROJECTION);
//    // Aktuelle Transformations-Matrix zuruecksetzen
//    glLoadIdentity();
//    // Viewport definieren
//    glViewport(0, 0, width, height);
//    // Frustum definieren (siehe unten)
//    //glOrtho(-1., 1., -1., 1., 0.3, 1.3);
//    //       L    R    B   T   N    F
//    //glOrtho( -1., 1., -1., 1., 0.0, 1.3);
//   gluPerspective(45., 1., 0.1, 2.0);
//    //Transformationen des Betrachters werden in der Matrix GL_MODELVIEW gespeichert
//    // Matrix für Modellierung/Viewing
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void Animate(int value) {
//    // Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
//    // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
//    // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
//    // inkrementiert und dem Callback wieder uebergeben. 
//    std::cout << "value=" << value << std::endl;
//
//    
//    fRotation = fRotation - 1.0; // Rotationswinkel aendern
//    if (fRotation <= 0.0) {
//        fRotation = fRotation + 360.0;
//    }
//    // RenderScene aufrufen
//    glutPostRedisplay();
//    // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
//    int wait_msec = 10;
//    glutTimerFunc(wait_msec, Animate, ++value);
//}
/*
 * 
 */

int main(int argc, char** argv) {

    Engine* e = Engine::getInstance();
    RadioTransformer* r = new RadioTransformer(0., 0., 0.);
    Engine::einfuegen(r);
    e->init(argc, argv);
    return 0;
}

