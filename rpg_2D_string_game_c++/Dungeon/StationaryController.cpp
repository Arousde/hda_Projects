/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "StationaryController.h"

StationaryController::StationaryController(): Controller(){
    
}

int StationaryController::move(){
    int einfachreturnfuenf = 5 ;
    std::cout<<"pass auf"<<std::endl;
    return einfachreturnfuenf ;
}

        std::string StationaryController::typ(){
    return "station" ;
}