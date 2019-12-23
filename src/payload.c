//#include <Cocoa/Cocoa.h>
#include <OpenCL/opencl.h>
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenCL/cl_gl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <Carbon/Carbon.h>
#include <CoreGraphics/CoreGraphics.h>
#include <ft2build.h>
#include "mach_override.h"
#include "helpers.h"
#define DWORD unsigned int


float option = 1.00, oldOption;
int arrowBuffer = 0;
char *actions[4] = {"Unlimited Ammo", "GodMode", "Moon Jump", "Troll Menu"};
int actions_active[4] = { 0, 0, 0, 0 };

// Modules start here

void unlimited_ammo(){
    printf("Enabling unlimited ammo hack.");
}

// End of modules
void (*action_voids[1])() = { unlimited_ammo };



void toggleOption(int option){
    if(actions_active[option] > 0.1){
        actions_active[option] = 0;
    }else if(actions_active[option] == 0){
        unlimited_ammo();
        actions_active[option]++;
    }
}

void drawOptionRow(char *name, int red, int blue, int green, int index){
    glColor3f(red, blue, green);
    glLineWidth(5);
    if(index <= 0) index = 1;
    drawBitmapText(name, 40, 1280 + (45 * index), 0);
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
        if(actions_active[i-1] == 1){
            drawBottomLeftOption(actions[i-1], 1, 0, 0, i);
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
    glVertex2f(25, 1280);
    glVertex2f(25, 1280 + 300);
    glVertex2f(25, 1280);
    glVertex2f(25 + 500, 1280);
    glVertex2f(25 + 500, 1280);
    glVertex2f(25 + 500, 1280 + 300);
    glVertex2f(25, 1280 + 300);
    glVertex2f(25 + 500, 1280 + 300);
    glEnd();
}

void drawMenu(int option){
    drawOuterBox();
    drawOptions();
}


void (*Original_CGLFlushDrawable)(CGLContextObj ctx);
void (*Original_SDL_GetKeyboardState)();


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
        toggleOption(option);
    }
    drawMenu(option);
    Original_CGLFlushDrawable(ctx);
}

void SDL_GetKeyboardState(){
    Original_SDL_GetKeyboardState();
}

__attribute__((constructor)) static void ctor(void) {
    printf("Dylib constructor called!");
    printf("\nhooking opengl flush drawable\n");
    mach_override_ptr(dlsym(RTLD_DEFAULT, "CGLFlushDrawable"), CGLFlushDrawableOverride, (void **)&Original_CGLFlushDrawable);
    printf("First hook done\n");
}

