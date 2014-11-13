#include "fighter.h"
#include <iostream>
using namespace std;

void Fighter::init_random()
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<float>
        u(1,3),
        h(MIN_HP,MAX_HP),
        sp(MIN_HP,MAX_HP),
        d(MIN_HP,MAX_HP),
        st(MIN_HP,MAX_HP),
        sk(MIN_HP,MAX_HP),
        l(MIN_HP,MAX_HP);
    
    int un = u(gen);
    if(un == 1){
        this->unit = 's';
    }else if(un == 2){
        this->unit = 'a';
    }else{
        this->unit = 'l';
    }

    this->maxhp = h(gen);
    this->hp = this->maxhp;

    this->speed = sp(gen);
    this->defense = d(gen);
    this->strength = st(gen);
    this->skill = sk(gen);
    this->luck = l(gen);
};

float Fighter::critical_rate()
{
    return (this->skill+this->luck)/2;
}

float Fighter::accuracy(Fighter defender)
{
    float a = this->skill - defender.speed;
    if(this->unit=='s'){
        if(this->unit=='a'){
            a += 20;
        }else if(this->unit=='l'){
            a -= 20;
        }
    }else if(this->unit=='a'){
        if(this->unit=='l'){
            a += 20;
        }else if(this->unit=='s'){
            a -= 20;
        }
    }else if(this->unit=='l'){
        
        if(this->unit=='s'){
            a += 20;
        }else if(this->unit=='a'){
            a -= 20;
        }
    }
    
    return a > 0 ? a/100 : 0;
}

int Fighter::damage(Fighter defender)
{
    int d = this->strength - defender.defense;
    return d > 0 ? d : 0;
}

float Fighter::critical_chance(Fighter defender)
{
    float c = this->critical_rate() - defender.luck;
    return c > 0 ? c : 0;
}

void Fighter::combat(Fighter *defender)
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<float>
        dice(0,1);
    int times = (this->speed - defender->speed) > 3 ? 2 : 1;
    cout << "Acc: "<< this->accuracy(*defender) << "\tDam: " << this->damage(*defender) << "\tCrit: " << this->critical_chance(*defender) << endl;

    for(int i=0;i<times;i++){    
        float acc = dice(gen);
        cout << "hit?: " << acc;
        if(acc<this->accuracy(*defender)){
            cout<<"\thit";
            acc = dice(gen);
            cout << "\tcritical?: " << acc;        
            defender->hp -=
                acc < this->critical_chance(*defender) ?
                3*(this->damage(*defender)):
                this->damage(*defender);
        }else
            cout<<"\tmiss";
        cout << endl;
    }
    
}

