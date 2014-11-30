#include <iostream>
#include "fighter.h"
#include "RedNeural.h"
#include <map>

using namespace std;

typedef map<char,int> Dict;
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
    int numF = atoi(argv[2]);
    int numP = atoi(argv[1]);
    char type;
    RedNeural red(12,10,3);
    double** input;

    red.leerPesos();

    Dict d;
    
    d['s']=1;
    d['a']=2;
    d['l']=3;

    int correct = 0;
    int combat = 1;
    int total = numP * numF * 3;
        
    for(int k=0;k<numP;k++){
        player.init_random('s');
        for(int j=0;j<3;j++){
            type = TYPES[j];     
            for(int i=0;i<numF;i++){
                input = Utilities::crearMatriz(1,12);
                opponent.init_random(type);

                player.combat(&opponent);
                opponent.combat(&player);
                
                input[0][0] = d[player.unit];
                input[0][1] = player.speed;
                input[0][2] = player.defense;
                input[0][3] = player.strength;
                input[0][4] = player.skill;
                input[0][5] = player.luck;
                input[0][6] = d[opponent.unit];
                input[0][7] = opponent.speed;
                input[0][8] = opponent.defense;
                input[0][9] = opponent.strength;
                input[0][10] = opponent.skill;
                input[0][11] = opponent.luck;
            
                double* temp = red.resolver(input[0]);
                    
                float playerPerc = (float)player.hp/(float)player.maxhp;
                float opponentPerc = (float)opponent.hp/(float)opponent.maxhp;
               
                int c = (playerPerc < opponentPerc ? 0 : 
                         (playerPerc == opponentPerc ? 1 : 2)); 

                int d = (temp[0]>temp[1] ? (temp[0]>temp[2] ? 0 : 2) 
		: (temp[1]>temp[2] ? 1 : 2));

		string real,reported;
		real = (c == 0 ? "Gana enemigo" : (c == 1 ? "Empate" : "Gana aliado"));
		reported = (d == 0 ? "Gana enemigo" : (d == 1 ? "Empate" : "Gana aliado"));


                cout << "Combate n.- " << combat << endl;
		cout << "\tResultado real: " << real << endl;
		cout << "\tResultado reportado: " << reported << endl;

	        if(c == d){
		  ++correct;
		  cout << "\tPredicción Correcta!" << endl;
	        }else cout << "\tPredicción Incorrecta" << endl;
		++combat;

            }
        }
    }

    cout << "Porcentaje de correctitud: " << (double)correct/(double)total*100;
    cout << " por ciento" << endl;
}
        
