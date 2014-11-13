#ifndef FIGHTER_H
#define FIGHTER_H

#include<random>

#define MAX_HP 80
#define MIN_HP 20

#define MAX_SPEED 10
#define MAX_DEFENSE 10
#define MAX_STRENGTH 10
#define MAX_SKILL 10
#define MAX_LUCK 10

#define MIN_SPEED 1
#define MIN_DEFENSE 1
#define MIN_STRENGTH 1
#define MIN_SKILL 1
#define MIN_LUCK 1

class Fighter
{
    
public:
    int hp;
    int maxhp;
    int speed;
    int defense;
    int strength;
    int skill;
    float luck;
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
            float l = 0):
        unit(u),maxhp(h),hp(h),speed(sp),defense(d),strength(st),skill(sk),luck(l){};

    void init_random();
    float critical_rate();
    float accuracy(Fighter defender);
    int damage(Fighter defender);
    float critical_chance(Fighter defender);
    void combat(Fighter *defender);
};

#endif
