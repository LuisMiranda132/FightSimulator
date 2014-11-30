#include <iostream>
#include "fighter.h"
using namespace std;

const char TYPES[] = {'s','a','l'};

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
    
int main(int argc, char *argv[]){
    Fighter player;
    Fighter opponent;
    int numF = atoi(argv[3]);
    int numP = atoi(argv[2]);
    char type;

    for(int k;k<numP;k++){
        player.init_random(argv[1][0]);
//        cout<<player<<endl;
        for(int j=0;j<3;j++){
            type = TYPES[j];
//            cout<<type<<":"<<endl;        
            for(int i=0;i<numF;i++){
//                cout<<" "<<i<<": ";
                opponent.init_random(type);
                
                cout <<player.unit <<" "<<player.speed << " " <<  player.defense;
                cout << " " <<  player.strength << " " << player.skill << " ";
                cout << player.luck << " ";
            
                cout << opponent.unit << " " << opponent.speed;
                cout<<" "<<opponent.defense << " " <<  opponent.strength  << " ";
                cout<< opponent.skill << " " << opponent.luck << " ";
        
                player.combat(&opponent);
                opponent.combat(&player);

                float playerPerc = (float)player.hp/(float)player.maxhp;
                float opponentPerc = (float)opponent.hp/(float)opponent.maxhp;
                //cout << playerPerc << " " << opponentPerc << endl;
                int c = (playerPerc < opponentPerc ? 0 : 
                         (playerPerc == opponentPerc ? 1 : 2));
            
                cout << c << endl;
            }
        }
    }
    
}
