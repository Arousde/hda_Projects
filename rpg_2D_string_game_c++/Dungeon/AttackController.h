/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AttackController.h
 * Author: arous
 *
 * Created on 13. Juni 2017, 19:29
 */

#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "Controller.h"
#include "DungeonMap.h"
#include "Character.h"
class AttackController : public Controller {
public:

  AttackController(DungeonMap* map);


    int move() override;


std::string typ()override;

private:
DungeonMap* attak_map ;
//Character* m_zuattakieren;
//Character* m_attaker ;
};

#endif /* ATTACKCONTROLLER_H */

