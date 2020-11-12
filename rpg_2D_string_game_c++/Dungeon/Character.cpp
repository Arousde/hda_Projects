#include "Character.h"
#include "StationaryController.h"
#include <iostream>

Character::Character(char Zeichen, int Strength, int Stamina ,Controller* c) {

   m_Controller = c ;

        
    m_Zeichen = Zeichen;
    m_Strength = Strength;
    m_Stamina = Stamina;
    m_Hitpoints = getMaxHP();
};

Character::~Character(){
    delete m_Controller;
    if(!m_vec_Item.empty()){
    for (int i = 0; i < m_vec_Item.size(); i++) {
        delete m_vec_Item[i];
    }}
m_vec_Item.clear();
}

void Character::SetController(Controller* Controller) {
    m_Controller = Controller;
}

int Character::move() {
    int a = m_Controller->move();
    return a;
}

Controller* Character::GetController() const {
    return m_Controller;
}

void Character::SetZeichen(char Zeichen) {
    m_Zeichen = Zeichen;
}

char Character::GetZeichen() const {
    return m_Zeichen;
}

int Character::getMaxHP() {
    int MaxHP;
    MaxHP = 20 + (GetStamina() * 5) ;
    return MaxHP;
}

void Character::showInfo()  {
    std::cout << "player :" << " " << m_Zeichen << std::endl;
    std::cout << "Stamina :" << " " << GetStamina() << std::endl;
    std::cout << "Strength :" << " " << GetStrength() << std::endl;
    std::cout << "Hitpoints :" << " " << m_Hitpoints << std::endl;
//     std::cout << "controller :" << " " << *m_Controller<< std::endl;



}

int Character::GetStamina()  {

    int result =m_Stamina;
    for (int i = 0; i < m_vec_Item.size(); i++) {

        result = result + m_vec_Item[i]->modifyStamina(m_Stamina);
    }
//    result = result + m_Stamina;

    return result;

}

int Character::GetStrength()  {
    int boniStrength = m_Strength;
    for (int i = 0; i < m_vec_Item.size(); i++) {

        boniStrength = boniStrength + m_vec_Item[i]->modifyStrength(m_Strength);
    }

    return boniStrength;
   
}

void Character::addItem(Item* item) {
    
    m_vec_Item.push_back(item);

}

void Character::SetHitpoints(int Hitpoints) {
    m_Hitpoints = Hitpoints;
}

int Character::GetHitpoints() const {
    return m_Hitpoints;
}