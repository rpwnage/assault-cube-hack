#include "FunctionPatches.h"
uint64_t example_original;

void patch_functions(){
    printf("[PATCHER] Patching test function...\n");
    void (*chatMessage)(char *one, long three);
    chatMessage = (void*)(AC_BASE + 0x4B720);
    char *ork = "OrkSec Rules!";
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 3 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        printf("[PATCHER] Sending test address %p\n", &ork);
        chatMessage("[PATCHER] Payload injected successfully.", 0x241);
    });
}