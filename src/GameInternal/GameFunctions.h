#include <stdarg.h>
#include "../helpers.h"

int BigMessage(char *string, int type, int size, int u0, int length, char *stack[2048]);
int pushMessage(char *data, int arg1, int arg2, int arg3);
void freeGameFunctions();
void patch_functions();