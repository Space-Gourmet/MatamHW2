
#pragma once

#include <iostream>

using std::string;

class Pirate {
private:
    string name;
    int bounty;

public:
    Pirate(const string& name, const int bounty);

    Pirate() = default;

    ~Pirate() = default;

    void setName(const string& name);

    void setBounty(const int bounty);

    string getName();

    int getBounty();

    friend std::ostream &operator<<(std::ostream &os, const Pirate &pirate);
};
