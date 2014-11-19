#ifndef FIGHTER_H
#define FIGHTER_H

#include<random>

//Rates en orden: Sword, Axe, Lance

const float HP_RATE[] = {70,90,70};
const float STR_RATE[] = {40,70,40};
const float SKL_RATE[] = {70,40,50};
const float SPD_RATE[] = {70,20,50};
const float LCK_RATE[] = {40,30,40};
const float DEF_RATE[] = {30,20,40};
const int HIT_RATE[] = {100,80,90};

const int BASE_SWORD_STATS[] = {16,4,8,10,1,4};
const int BASE_AXE_STATS[] = {20,8,4,7,1,2};
const int BASE_LANCE_STATS[] = {18,6,7,7,2,5};

class Fighter
{

public:
    int hp;
    int maxhp;
    int speed;
    int defense;
    int strength;
    int skill;
    int luck;
    int hit_rate;
    // s = swordman
    // a = axeman
    // l = lanceman
    char unit;
    
    Fighter(char u = 's',
            int h = 0,
            int sp = 0,
            int d = 0,
            int st = 0,
            int sk = 0,
            int l = 0,
	    int ht = 0):
        unit(u),maxhp(h),hp(h),speed(sp),defense(d),strength(st),skill(sk),luck(l),hit_rate(ht){};

    void init_random();
    void level_up(int roll);
    void init_stats(const int* s);
    int critical_rate();
    int accuracy(Fighter defender);
    int damage(Fighter defender);
    int critical_chance(Fighter defender);
    void combat(Fighter *defender);
};

#endif
