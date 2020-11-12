/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConsoleController.h
 * Author: arous
 *
 * Created on 8. Mai 2017, 13:19
 */

#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H
#include "Controller.h"
class ConsoleController : public Controller {
    public:
        std::string typ()override;
    ConsoleController();
    
    virtual int move() override;
};

#endif /* CONSOLECONTROLLER_H */

