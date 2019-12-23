#include "mach_override.h"
#include "helpers.h"
#include "offsets.h"
char *EXECUTABLE_NAME = "assaultcube";
int64_t aslr_slide = 0;


void drawBitmapText(char *string, float x, float y, float z){
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void set_mem_rx(void *addr, uint64_t size){
    task_for_pid(mach_task_self(), getpid(), &pTw);
    if(mach_vm_protect(pTw, (mach_vm_address_t)addr, (mach_vm_size_t)size, FALSE, VM_PROT_READ | VM_PROT_EXECUTE) != KERN_SUCCESS){
        printf("[ERROR] Changing memory protection failed\n");
    }
    return;
}

void set_mem_rwx(void *addr, uint64_t size){
    task_for_pid(mach_task_self(), getpid(), &pTw);
    if(mach_vm_protect(pTw, (mach_vm_address_t)addr, (mach_vm_size_t)size, FALSE, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE) != KERN_SUCCESS){
        printf("[ERROR] Changing memory protection failed\n");
    }
    return;
}

void set_mem_rw(void *addr, uint64_t size){
    task_for_pid(mach_task_self(), getpid(), &pTw);
    if(mach_vm_protect(pTw, (mach_vm_address_t)addr, (mach_vm_size_t)size, FALSE, VM_PROT_READ | VM_PROT_WRITE) != KERN_SUCCESS){
        printf("[ERROR] Changing memory protection failed\n");
    }
    return;
}


void calculate_aslr_slide(){
    for (uint32_t i = 0; i < _dyld_image_count(); i++) {
        const char *name = _dyld_get_image_name(i);
        if(strcmp(basename((char*)name), "assaultcube") == 0){
            aslr_slide = _dyld_get_image_vmaddr_slide(0);
            printf("[PATCHER] ASLR Slide: 0x%0lx (%s) [%d]\n", _dyld_get_image_vmaddr_slide(0), name, i);
        }
    }
}

uint64_t calculate_address_with_aslr(uint64_t base, uint64_t offset_from_base){
    calculate_aslr_slide();
    return base + offset_from_base + aslr_slide;
}

uint64_t patch_jmp(void *addr, void *dst){
    set_mem_rwx(addr, sizeof(uint64_t));
    uint64_t orig_bytes = *(uint64_t *)addr;
    printf("[JMP] original bytes: %08llx\n", orig_bytes);
    uint32_t jmp_offset = (uint32_t)((char*)dst - (char*)addr - 5);
    printf("[JMP] offset: %08x\n", jmp_offset);
    jmp_offset = OSSwapInt32(jmp_offset);
    uint64_t bytes = 0xE900000000000000LL;
    bytes |= ((uint64_t)jmp_offset & 0xFFFFFFFF) << 24;
    bytes = OSSwapInt64(bytes);
    *(uint64_t *)addr = bytes;
    printf("[JMP] offset: 0x%08x\n", jmp_offset);
    printf("[PATCHER] replaced bytes: 0x%08llx\n", bytes);
    set_mem_rwx(addr, sizeof(uint64_t));
    return orig_bytes;
}
