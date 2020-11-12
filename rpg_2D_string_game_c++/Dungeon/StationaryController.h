/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StationaryController.h
 * Author: arous
 *
 * Created on 25. Mai 2017, 17:32
 */

#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H
#include "Controller.h"
class StationaryController : public Controller{
    public:
        StationaryController();
        int move()override;
        std::string typ()override;
};


#endif /* STATIONARYCONTROLLER_H */

