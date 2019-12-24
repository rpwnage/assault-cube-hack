#include "../../mach_override.h"
#include "../../helpers.h"
#include "../../payload.h"

int unlimited_ammo();
void toggleOption(int option);
void drawOptionRow(char *name, int red, int blue, int green, int index);
void drawBottomLeftOption(char *name, int red, int blue, int green, int index);
void drawOptions();
void drawOuterBox();
void drawMenu(int option);
void CGLFlushDrawableOverride(CGLContextObj ctx);
void (*Original_CGLFlushDrawable)(CGLContextObj ctx);
