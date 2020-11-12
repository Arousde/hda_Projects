/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Aktiv.h
 * Author: arous
 *
 * Created on 6. Mai 2017, 11:30
 */


#ifndef AKTIV_H
#define AKTIV_H
#include "Passive.h"
class Aktive : public Tile {
public:
    Aktive():Tile(){};
    virtual void Setbetreten(bool done);
    virtual bool Istbetreten() const;
    virtual void Set_Ptr_passive(Passive* t_pass);

protected:
    bool betreten;
    Passive* Ptr_pass;

};


#endif /* AKTIV_H */

