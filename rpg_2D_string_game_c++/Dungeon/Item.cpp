/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Item.h"
#include <iostream>
Item::Item(){
    
}

ArmingSword::ArmingSword():Item(){
    
}

int ArmingSword::modifyStamina(int stamina){
    int boni = 0 ;
    return boni;
}

int ArmingSword::modifyStrength(int strength){
    int boni = 3;
    return boni;
}
Greatsword::Greatsword():Item(){
    
}
int Greatsword::modifyStamina(int stamina){
    int boni = -1 ;
    return boni;
}

int Greatsword::modifyStrength(int strength){
    int boni = 5 ;
    return boni ;
}

Club::Club():Item(){
    
}

int Club::modifyStamina(int stamina){
    int boni = 0 ;
    return boni ;
}

int Club::modifyStrength(int strength){
    
    int boni = strength /2.0 ;
    
    return boni ;
}

RapierUndDagger::RapierUndDagger():Item(){
    
}

int RapierUndDagger::modifyStamina(int stamina){
     int boni = 1 ;
     return boni ;
}

int RapierUndDagger::modifyStrength(int strength){
    int boni = 2 ;
    return boni ;
}


Gambeson::Gambeson():Item(){
    
}

int Gambeson::modifyStamina(int stamina){
    int boni = 1;
    return boni ;
}

int Gambeson::modifyStrength(int strength){
    int boni = 0;
    return boni ;
}

MailArmour::MailArmour():Item(){
    
}

int MailArmour::modifyStamina(int stamina){
    int boni = 3 ;
    return boni ;
}

int MailArmour::modifyStrength(int strength){
    int boni =0 ;
    return boni ;
}

Shield::Shield():Item(){
    
}

int Shield::modifyStamina(int stamina){
        int boni = stamina ;
        return boni ;
}
int Shield::modifyStrength(int strength){
    int boni = -1;
    return boni ;
    
}

FullPlateArmour::FullPlateArmour():Item(){
    
}

int FullPlateArmour::modifyStamina(int stamina){
     int boni = 6;
     return boni ;
}

int FullPlateArmour::modifyStrength(int strength){
     int boni = -2;
     return boni ;
}