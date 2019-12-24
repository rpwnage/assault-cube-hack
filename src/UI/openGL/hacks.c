#include "hack.h"

void hacksloop(int actions[]){
    if(actions[1] == 1){
        unlimited_ammo();
    }
}

int unlimited_ammo(){
    for(int i = 0; i < 5; i++){
        playerBase = calculatePlayerBase();
        *(int*)(playerBase + 0x150) = 999;
        *(int*)(playerBase + 0x13C) = 999;
    }
    return 0;
}

int snake(){
    playerBase = calculatePlayerBase();
    *(int*)(playerBase + 0x48) = *(int*)(playerBase + 0x48) + 10000000;
    printf("[SNAKE] Enabled snake mode (%d)\n", *(int*)(playerBase + 0x48));
    return 0;
}

int speedHack(int speed){
    return 0;
}

int moon_jump(){
    playerBase = calculatePlayerBase();
    *(int*)(playerBase + 0x40) = -130;
    return 0;
}

int give_akimbo(){
    for(int i = 0; i < 5; i++){
        playerBase = calculatePlayerBase();
        *(int*)(playerBase + 0x10C) = 1;
        *(int*)(playerBase + 0x15C) = 999;
        if((*(int*)(playerBase + 0x15C) == 999) && (*(int*)(playerBase + 0x10C) != 999)){
            return -1;
        }
    }
    return 0;
}
