#include "fighter.h"
#include <iostream>
using namespace std;

void Fighter::init_random()
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> u(0,2),l(1,20),d(0,100);

    int un = u(gen);
    if(un == 0){
        this->unit = 's';
	init_stats(BASE_SWORD_STATS);
    }else if(un == 1){
        this->unit = 'a';
	init_stats(BASE_AXE_STATS);
    }else{
        this->unit = 'l';
	init_stats(BASE_LANCE_STATS);
    }

    int level = l(gen);
    for(int i=0;i<level;++i){
      level_up(d(gen));
    }
    this->hp = this->maxhp;
    this->hit_rate = HIT_RATE[un];
};

void Fighter::init_random(char mander)
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> l(1,20),d(0,100);

    this->unit = mander;
    
    if(mander=='s'){
	init_stats(BASE_SWORD_STATS);
        this->hit_rate = HIT_RATE[0];
    }else if(mander=='a'){
	init_stats(BASE_AXE_STATS);
        this->hit_rate = HIT_RATE[1];
    }else{
	init_stats(BASE_LANCE_STATS);
        this->hit_rate = HIT_RATE[2];
    }

    int level = l(gen);
    for(int i=0;i<level;++i){
      level_up(d(gen));
    }
    this->hp = this->maxhp;
};

void Fighter::level_up(int roll){
    int cls = (this->unit == 's' ? 0 : (this->unit == 'a' ? 1 : 2));
    this->maxhp += (roll < HP_RATE[cls] ? 1 : 0);
    this->strength += (roll < STR_RATE[cls] ? 1 : 0);
    this->skill += (roll < SKL_RATE[cls] ? 1 : 0);
    this->speed += (roll < SPD_RATE[cls] ? 1 : 0);
    this->luck += (roll < LCK_RATE[cls] ? 1 : 0);
    this->defense += (roll < DEF_RATE[cls] ? 1 : 0);
}

void Fighter::init_stats(const int* s){
    this->maxhp = s[0];
    this->strength = s[1];
    this->skill = s[2];
    this->speed = s[3];
    this->luck = s[4];
    this->defense = s[5];
}

int Fighter::critical_rate()
{
    return (this->skill+this->luck)/2;
}

int Fighter::accuracy(Fighter defender)
{
    float a = this->skill + this->hit_rate - defender.speed;
    if(this->unit=='s'){
        if(defender.unit=='a'){
            a += 20;
        }else if(defender.unit=='l'){
            a -= 20;
        }
    }else if(this->unit=='a'){
        if(defender.unit=='l'){
            a += 20;
        }else if(defender.unit=='s'){
            a -= 20;
        }
    }else if(this->unit=='l'){
        
        if(defender.unit=='s'){
            a += 20;
        }else if(defender.unit=='a'){
            a -= 20;
        }
    }
    
    return a > 0 ? a : 0;
}

int Fighter::damage(Fighter defender)
{
    int d = this->strength - defender.defense;
    return d > 0 ? d : 0;
}

int Fighter::critical_chance(Fighter defender)
{
    int c = this->critical_rate() - defender.luck;
    return c > 0 ? c : 0;
}

void Fighter::combat(Fighter *defender)
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int>
        dice(0,100);
    int times = (this->speed - defender->speed) > 3 ? 2 : 1;

    int c_accuracy = this->accuracy(*defender);
    int c_damage = this->damage(*defender);
    int c_critical_chance = this->critical_chance(*defender);

    //cout << "Acc: "<< c_accuracy << "\tDam: " << c_damage << "\tCrit: " <<
    //c_critical_chance << endl;

    for(int i=0;i<times;i++){    
        int acc = dice(gen);
        //cout << "hit?: " << acc;
        if(acc<c_accuracy){
            //cout<<"\thit";
            acc = dice(gen);
            //cout << "\tcritical?: " << acc;        
            defender->hp -=
                acc < c_critical_chance ?
                3*(c_damage):
                c_damage;
        }//else
            //cout<<"\tmiss";
        //cout << endl;
    }
    
}

