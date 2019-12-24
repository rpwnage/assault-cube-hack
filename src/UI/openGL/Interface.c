#include "Interface.h"

float option = 1.00, oldOption;
int arrowBuffer = 0;
char *actions[5] = {"Unlimited Ammo", "Speed Hack", "Moon Jump", "Give Akimbo", "Snake"};
int actions_active[sizeof(actions)] = { 0, 0, 0, 0 };


int unlimited_ammo(){
    playerBase = calculatePlayerBase();
    printf("[AmmoHack] Setting ammo to 999. (%p)\n", (playerBase + 0x150));
    *(int*)(playerBase + 0x150) = 999;
    *(int*)(playerBase + 0x13C) = 999;
    printf("[AmmoHack] done (%d)\n", *(int*)(playerBase + 0x150));
    return 0;
}

int snake(){
    playerBase = calculatePlayerBase();
    *(int*)(playerBase + 0x48) = *(int*)(playerBase + 0x48) - 80000000;
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
    playerBase = calculatePlayerBase();
    printf("[AkimboHack] Setting %p\n", (playerBase + 0x10C));
    *(int*)(playerBase + 0x10C) = 1;
    *(int*)(playerBase + 0x15C) = 999;
    printf("[AkimboHack] Done (%d)\n", *(int*)(playerBase + 0x10C));
    if((*(int*)(playerBase + 0x15C) == 999) && (*(int*)(playerBase + 0x10C) == 999)){
        return 0;
    }else return -1;
}

void toggleOption(int option){
    if(actions_active[option] > 0.1){
        actions_active[option] = 0;
    }else if(actions_active[option] == 0){
        printf("Option: %d\n", option);
        if((option) == 1){
            unlimited_ammo();
        }if((option) == 2){
            speedHack(3);
        }if((option) == 3){
            moon_jump();
        }if((option) == 4){
            give_akimbo();
        }if((option) == 5){
            snake();
        }
        actions_active[option]++;
    }
}

void drawOptionRow(char *name, int red, int blue, int green, int index){
    glColor3f(red, blue, green);
    glLineWidth(5);
    if(index <= 0) index = 1;
    drawBitmapText(name, 40, 1200 + (45 * index), 0);
}

void drawBottomLeftOption(char *name, int red, int blue, int green, int index){
    glColor3f(red, blue, green);
    glLineWidth(5);
    if(index <= 0) index = 1;
    drawBitmapText(name, 2880, 455 + (35 * index), 0);
}

void drawOptions(){
    int activeDrawn = 0;
    for(int i = 1; i < (sizeof(actions)/sizeof(actions[0])) + 1; i++){
        
        if(option <= (i + .500000) && option >= (i - .500000) && activeDrawn != 1){
            activeDrawn++;
            drawOptionRow(actions[i-1], 0, 1, 0, i);
        }else if(option == 0 && activeDrawn != 1){
            activeDrawn++;
            drawOptionRow(actions[i-1], 0, 1, 0, 1);
        }
        drawOptionRow(actions[i-1], 1, 1, 1, i);
    }
}

void drawOuterBox(){
    glColor3f(0.0f, 0.0f, 1.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(25, 1200);
    glVertex2f(25, 1200 + 380);
    glVertex2f(25, 1200);
    glVertex2f(25 + 500, 1200);
    glVertex2f(25 + 500, 1200);
    glVertex2f(25 + 500, 1200 + 380);
    glVertex2f(25, 1200 + 380);
    glVertex2f(25 + 500, 1200 + 380);
    glEnd();
}

void drawMenu(int option){
    drawOuterBox();
    drawOptions();
}


void CGLFlushDrawableOverride(CGLContextObj ctx) {
    oldOption = option;
    if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_DownArrow)) {
        if(option >= 0 && option < (sizeof(actions)/sizeof(actions[0]))){
            option = option + 0.25;
        }
    }else if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_UpArrow)) {
        if(option > 0.000){
            option = option - 0.25;
        }
    }else if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_Return)) {
        while(CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_Return)){
            if(!CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_Return)){
                toggleOption(option);
                break;
            }
        }
    }
    drawMenu(option);
    Original_CGLFlushDrawable(ctx);
}