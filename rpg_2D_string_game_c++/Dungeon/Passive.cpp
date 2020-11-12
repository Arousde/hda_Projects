#include "Passive.h"

Passive::Passive():Tile(){
    
}

void Passive::SetStatus(bool Status) {
    this->Status = Status;
}

bool Passive::GetStatus() const {
    return Status;
}