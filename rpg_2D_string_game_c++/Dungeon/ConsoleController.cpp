/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConsoleController.h"
#include <iostream>

ConsoleController::ConsoleController() : Controller() {
}

int ConsoleController::move() {
    int m;
   
        std::cout << "Bewegungsrichtung eingeben 5 für bleiben " << std::endl;
        std::cout << "###############" << std::endl;
        std::cout << "# 7    8    9 #" << std::endl;
        std::cout << "#  +   +   +  #" << std::endl;
        std::cout << "#    + + +    #" << std::endl;
        std::cout << "# 4++++5++++6 #" << std::endl;
        std::cout << "#    + + +    #" << std::endl;
        std::cout << "#  +   +   +  #" << std::endl;
        std::cout << "# 1    2    3 #" << std::endl;
        std::cout << "###############" << std::endl;
        
          std::cin>> m;
          if(std::cin.fail()){
              std::cin.clear();
              std::cin.ignore(100, '\n');
          }
    
       
    return m;

}

         std::string ConsoleController::typ(){
    return "control" ;
}