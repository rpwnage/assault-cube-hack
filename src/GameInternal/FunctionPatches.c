#include "FunctionPatches.h"
uint64_t example_original;

void patch_functions(){
    printf("[PATCHER] Patching test function...\n");
    // Initialize the hooks
    sendChatMessage = (void*)(AC_BASE + 0x4B720);   // sendChatMessage("orksec rocks", 0x241);
    sendBigMessage  = (void*)(AC_BASE + 0x91160);   // sendBigMessage("rpwnage rocks", 0x241);
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 3 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        sendBigMessage("rpwnage rocks", 0x241);
    });
}