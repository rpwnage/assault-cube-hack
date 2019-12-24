#include "GameFunctions.h"

int pushMessage(char *data, int arg1, int arg2, int arg3){
    printf("[PushMessage] Pushing messgae %s\n", data);
    void *dst = (void *)(AC_BASE + pushMessageOffset);
    *(uint64_t *)dst = (uint64_t)(AC_BASE + pushMessageOffset);
    void (*objc_load_addr_orig)(char *input);
    objc_load_addr_orig = dst;
    objc_load_addr_orig("test");
    return 0;
}

// BigMessage("You Lost the flag!", 3, 32, 0, 14, stack[2048]);
int BigMessage(char *string, int type, int size, int u0, int length, char *stack[2048]){
    printf("[BigMessage] Sending Big message (%s)\n", string);
    void *dst = (void *)(AC_BASE + BigMessageOffset);
    *(uint64_t *)dst = (uint64_t)(AC_BASE + BigMessageOffset);
    void (*objc_load_addr_orig)(char *string,int new, int type, int size, int u0, int length, char *stack[2048]);
    objc_load_addr_orig = dst;
        char *stack_b[3000];
    objc_load_addr_orig(string, 0, type, size, u0, length, stack_b);
    return 0;
}

void freeGameFunctions(){
    printf("[PATCHER] Freeing pushMessage function... (%p)\n", (void *)(AC_BASE + pushMessageOffset));
    set_mem_rwx(((void *)(AC_BASE + pushMessageOffset)), sizeof(uint64_t));
    printf("[PATCHER] Freeing bigMessage function... (%p)\n", (void *)(AC_BASE + BigMessageOffset));
    set_mem_rwx(((void *)(AC_BASE + BigMessageOffset)), sizeof(uint64_t));
    printf("[PATCHER] Free'd all game functions\n");
}