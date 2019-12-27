#include <stdarg.h>
#include "../helpers.h"

// Hooked functions
void (*sendChatMessage)(char *one, long three);
void (*sendBigMessage)(char *one, long three);
// Function to initialize all Hooks
void patch_functions();