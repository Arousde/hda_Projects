 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Controller.h"
Controller::Controller(){}

void Controller::setAttak(Character* attak) {
    this->attak = attak;
}

Character* Controller::getAttak() const {
    return attak;
}

void Controller::setControl_character(Character* control_character) {
    this->control_character = control_character;
}

Character* Controller::getControl_character() const {
    return control_character;
}

void Controller::setOpfer(Character* opfer) {
    this->opfer = opfer;
}

Character* Controller::getOpfer() const {
    return opfer;
}