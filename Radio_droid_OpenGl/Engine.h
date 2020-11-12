/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Engine.h
 * Author: arous
 *
 * Created on 8. Mai 2018, 16:05
 */

#ifndef ENGINE_H
#define ENGINE_H
#include "RadioTransformer.h"

class Engine {
public:

    static Engine* getInstance();

    static void init(int &argc, char **argv);
    static void einfuegen(RadioTransformer* radio);
private:
    Engine();
    Engine(const Engine& orig);
    virtual ~Engine();

    static void animate(int value);
    static void renderScene();
    static void reshape(int width, int height);

    static void specialKeys(int key, int x, int y);
     static void Keys(unsigned char key, int x, int y);
    void renderPerspective(double cameraRotatex, double cameraRotatey);
    RadioTransformer *Transformer;

    float fRotation;

    static Engine* instance;
    
    double rotateCam_y = 0;
    double rotateCam_x = 0;
    
    float tranzobj_x = 0;
    float tranzobj_y = 0;
    float tranzobj_z = 0;
    
    float scalezobj_x = 1;
    float scaleobj_y = 1;
    float scaleobj_z = 1;
    
};

#endif /* ENGINE_H */

