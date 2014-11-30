#include "fighter.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const Fighter dummy)
{
    out << "Unidad: "<< dummy.unit;
    out << "\nHP: "<< dummy.hp <<"/"<< dummy.maxhp;
    out << "\nStats:";
    out << "\n\tSpeed: " << dummy.speed;
    out << "\n\tDefense: " << dummy.defense;
    out << "\n\tStrength: " << dummy.strength;
    out << "\n\tSkill: " << dummy.skill;
    out << "\n\tLuck: " << dummy.luck;
    return out;
}

int main( int argc, char *argv[] )
{
    Fighter chrom;
    Fighter oponent;
    
    chrom.init_random();
    oponent.init_random();
    
    cout<<chrom<<endl;
    cout<<oponent<<endl;
    chrom.combat(&oponent);
    cout<<oponent<<endl;
    
}
