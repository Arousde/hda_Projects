/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: arous
 *
 * Created on 22. April 2017, 20:53
 */

#include <cstdlib>
#include<iostream>
#include<string>
#include <vector>
#include "GameEngine.h"
#include <fstream>
#include <sstream>
using namespace std;

/*
 * 
 */




void loadFromFile(string level) {
    ifstream datei;
    datei.open(level);

    int hoehe, breite;
    datei >> hoehe >> breite;
    cout << hoehe << " " << breite << endl;
    vector<string> data;
    vector<string> parameter;
    string Zeile;

    getline(datei, Zeile);

    for (int i = 0; i < hoehe; i++) {
        getline(datei, Zeile);
        if (Zeile != "")
            data.push_back(Zeile);
    }



    while (!datei.eof()) {
        getline(datei, Zeile);
        if (Zeile != "")
            parameter.push_back(Zeile);
    }


    datei.close();

  



    GameEngine ge(hoehe, breite, data, parameter);

    ge.turn();
}

int main(int argc, char** argv) {
  

    string level = "/home/arous/NetBeansProjects/Praktikum 2/level1.txt";
    
   
        
    loadFromFile(level);

   

    return 0;
}

