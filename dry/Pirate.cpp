
#include "Pirate.h"


Pirate::Pirate(const string& name, const int bounty): name(name), bounty(bounty) {}


void Pirate::setName(const string& name){
    this->name = name;
}

void Pirate::setBounty(const int bounty)
{
    this->bounty = bounty;
}

std::string Pirate::getName(){
    return name;
}

int Pirate::getBounty(){
    return bounty;
}

std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.name << " " << pirate.bounty;
    return os;
}
