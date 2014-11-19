#include <iostream>
#include "fighter.h"
using namespace std;

int main(){
    Fighter player;
    Fighter opponent;

    player.init_random();
    opponent.init_random();

    cout << player.unit << " " << player.speed << " " <<  player.defense;
    cout << " " <<  player.strength << " " << player.skill << " ";
    cout << player.luck << " ";

    cout << opponent.unit << " " << opponent.speed;
    cout << " " <<  opponent.defense << " " <<  opponent.strength  << " ";
    cout << opponent.skill << " " << opponent.luck << " ";

    player.combat(&opponent);
    opponent.combat(&player);

    float playerPerc = (float)player.hp/(float)player.maxhp;
    float opponentPerc = (float)opponent.hp/(float)opponent.maxhp;
    //cout << playerPerc << " " << opponentPerc << endl;
    int c = (playerPerc < opponentPerc ? 0 : 
    (playerPerc == opponentPerc ? 1 : 2));

    cout << c << endl;
}
