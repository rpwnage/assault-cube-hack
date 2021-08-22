#include "mach_override.h"
#include "helpers.h"
#include "payload.h"
#include "UI/ui.h"
#include "GameInternal/GameFunctions.h"
#include "UI/openGL/Interface.h"
#define DWORD unsigned int

void getCurrentAmmo(){
    printf("[PATCHES] Using playerbase %p\n", playerBase);
}

void commandPatches(){
    printf("[CommandHanlder] Command Handler Patches injected\n");
    void *dst = (void *)(AC_BASE + commandHandlerOffset);
    *(uint64_t *)dst = commandOverwrites;
    printf("[PATCHER] Rerouting to %p\n", dst);
    void (*objc_load_addr_orig)(void);
    objc_load_addr_orig = dst;
    objc_load_addr_orig();
}

int applyPatches(){
    void *src = (void *)((AC_BASE + commandHandlerOffset));
    void *dst = (void *)&commandPatches;
    printf("[PATCHER] %p -> %p\n", src, dst);
   // commandOverwrites = patch_jmp(src, dst);
    printf("[PATCHER] Command-Overwrite return: 0x%02llx\n", commandOverwrites);
    return 0;
}

__attribute__((constructor)) static void ctor(void) {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 3 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        if(applyPatches() != 0){
            printf("[ERROR] Error occured while trying to apply patches.\n");
            exit(1);
        }else {
            printf("[PATCHER] applied!\n");
        }
        if(menuType == 1){
            mach_override_ptr(dlsym(RTLD_DEFAULT, "CGLFlushDrawable"), CGLFlushDrawableOverride, (void **)&Original_CGLFlushDrawable);
        }
        freeGameFunctions();
        patch_functions();
        playerBase = calculatePlayerBase();
        entityBase = calculateEntityBase();
        
        if (playerBase != NULL && entityBase != NULL){
            printf("[PATCHER] Using Playerbase: %p\n", playerBase);
            printf("[PATCHER] Using Entitybase: %p\n", entityBase);
            printf("[PATCHER] Everything set\n");
        } else {
            printf("[PATCHER] Error: playerBase and entityBase are null. Couldn't set!\n");
            //handle error
        }
    });
}

