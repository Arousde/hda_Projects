#include "Aktive.h"

void Aktive::Setbetreten(bool done) {
    this->betreten = done;
}

bool Aktive::Istbetreten() const {
    return betreten;
}

void Aktive::Set_Ptr_passive(Passive* t_pass) {
    this->Ptr_pass = t_pass;
}

