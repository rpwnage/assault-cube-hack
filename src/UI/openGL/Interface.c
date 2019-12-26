#include "Interface.h"

float option = 1.00, oldOption;
int arrowBuffer = 0;
char *actions[5] = {"Unlimited Ammo", "Speed Hack", "Moon Jump", "Give Akimbo", "Snake"};
int actions_active[sizeof(actions)] = { 0, 0, 0, 0 };

void toggleOption(int option){
    if(actions_active[option] > 0.1){
        actions_active[option] = 0;
    }else if(actions_active[option] == 0){
        if((option) == 1){
            hacksloop(actions_active);
        }if((option) == 2){
            speedHack(3);
        }if((option) == 3){
            moon_jump();
        }if((option) == 4){
            hacksloop(actions_active);
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
        if(actions_active[i] == 1){
            drawBottomLeftOption(actions[i - 1], 1, 0, 0, i);
        }
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
    hacksloop(actions_active);
    oldOption = option;
    if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_PageDown)) {
        if(option >= 0 && option < (sizeof(actions)/sizeof(actions[0]))){
            option = option + 0.25;
        }
    }else if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_PageUp)) {
        if(option > 0.000){
            option = option - 0.25;
        }
    }else if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_End)) {
        while(CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_End)){
            if(!CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,kVK_End)){
                toggleOption(option);
                break;
            }
        }
    }
    drawMenu(option);
    Original_CGLFlushDrawable(ctx);
}