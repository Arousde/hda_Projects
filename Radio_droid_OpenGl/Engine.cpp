/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Engine.cpp
 * Author: arous
 * 
 * Created on 8. Mai 2018, 16:05
 */

#include <GL/freeglut.h>
#include "Engine.h"
Engine* Engine::instance = nullptr;

Engine* Engine::getInstance() {
    if (instance == nullptr)
        instance = new Engine();
    return instance;
}

void Engine::init(int& argc, char** argv) {

    instance->fRotation = 315.0;

    // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
    // durchgef�hrt werden m�ssen
    glutInit(&argc, argv); // GLUT initialisieren
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080); // Fenster-Konfiguration
    glutCreateWindow("Sonya Hedider; Arous Oussema"); // Fenster-Erzeugung
    glutDisplayFunc(renderScene); // Zeichenfunktion bekannt machen
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(Keys);
    glutReshapeFunc(reshape);
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10, animate, 0);

    // Licht
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    GLfloat light_position [] = {1.0, 1.0, 1.0, 0.0};
  
    glLightfv(GL_LIGHT0, GL_POSITION, light_position ); // Licht Nr. 0 rechts oben

    glEnable(GL_COLOR_MATERIAL);


    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glutMainLoop();

}

Engine::Engine() {
}

Engine::Engine(const Engine& orig) {
}

Engine::~Engine() {
}

void Engine::animate(int value) {
    // Hier werden Berechnungen durchgef�hrt, die zu einer Animation der Szene  
    // erforderlich sind. Dieser Prozess l�uft im Hintergrund und wird alle 
    // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
    // inkrementiert und dem Callback wieder uebergeben. 
    //cout << " rotation= " << instance->fRotation << endl;

    //teil4
    //    instance->fRotation = instance->fRotation - 1.0; // Rotationswinkel aendern
    //    if (instance->fRotation <= 0.0) {
    //        instance->fRotation = instance->fRotation + 360.0;
    //    }


    instance->Transformer->animate(0.0);

    // RenderScene aufrufen
    glutPostRedisplay();
    // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
    int wait_msec = 10;
    glutTimerFunc(wait_msec, animate, ++value);

}

void Engine::renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
    glLoadIdentity(); // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen	
    gluLookAt(0., 0., 15., 0., 0., 0., 0., 1., 0.); //camposX,camposY,camposZ, betrachtete Pos x,y,z, viewupdown...

    
    
    instance->renderPerspective(instance->rotateCam_x, instance->rotateCam_y);

    instance->Transformer->renderScene();
    glutSwapBuffers();
}

void Engine::reshape(int width, int height) {
    // Hier finden die Reaktionen auf eine Ver�nderung der Gr��e des 
    // Graphikfensters statt

    // Matrix f�r Transformation: Frustum->viewport
    glMatrixMode(GL_PROJECTION); //richtigen Stack aktivieren
    // Aktuelle Transformations-Matrix zuruecksetzen
    glLoadIdentity();
    // Viewport definieren
    glViewport(0, 0, width, height);
    // Frustum definieren (siehe unten)
    //glOrtho(-2., 2., -2., 2., 0.0, 2.0);	//begrenzt Sichtbereich f�r xyz-Achsen (ohne Perspektive)
    gluPerspective(45., (GLfloat) width / (GLfloat) height, 0.1, 1000.0); //2.para=1
    // Matrix f�r Modellierung/Viewing
    glMatrixMode(GL_MODELVIEW);
}

void Engine::einfuegen(RadioTransformer* radio) {
    instance->Transformer = radio;
}

void Engine::renderPerspective(double cameraRotatex, double cameraRotatey) {
    glRotatef(instance->rotateCam_x, 1.0, 0.0, 0.0);
    glRotatef(instance->rotateCam_y, 0.0, 1.0, 0.0);
    glScalef(instance->scalezobj_x,instance->scaleobj_y,1.);
    glTranslatef(instance->tranzobj_x, instance->tranzobj_y, instance->tranzobj_z);

}

void Engine::specialKeys(int key, int x, int y) {
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
        instance->rotateCam_y += 5;
        //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)
        instance->rotateCam_y -= 5;
    else if (key == GLUT_KEY_UP)
        instance->rotateCam_x += 5;
    else if (key == GLUT_KEY_DOWN)
        instance->rotateCam_x -= 5;
    //  Request display update
    glutPostRedisplay();
}

void Engine::Keys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            instance->tranzobj_y += 0.2;
            break;
        case 's':
            instance->tranzobj_y -= 0.2;
            break;
        case 'a':
            instance->tranzobj_x -= 0.2;
            break;
        case 'd':
            instance->tranzobj_x += 0.2;
            break;
        case 'y':
          //  instance->tranzobj_z += 0.2;
            break;
        case 'x':
       //     instance->tranzobj_z -= 0.2;
            break;
        case 'q':
            instance->scalezobj_x += 0.1;
            instance->scaleobj_y +=0.1;
            break;
        case 'e':
            instance->scalezobj_x -=0.1;
            instance->scaleobj_y -=0.1;
            break;
        case 'l':
            instance->Transformer->getArmLeft()->Armhoch();
            instance->Transformer->getArmRight()->Armhoch();
            break;
        case 'm' :
            instance->Transformer->getArmLeft()->getHand()->handhoch();
            instance->Transformer->getArmRight()->getHand()->handhoch();

            break;
        case  'o' :
             instance->Transformer->getArmLeft()->getHand()->swing();
            instance->Transformer->getArmRight()->getHand()->swing();

            break;
        default:
            break;
    }
}
