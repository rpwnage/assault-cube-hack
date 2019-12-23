#include <OpenCL/opencl.h>
#include <libgen.h>
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <errno.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenCL/cl_gl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <mach/mach.h>
#include <mach/vm_region.h>
#include <sys/mman.h>
#include <mach-o/dyld.h>
#include <stdint.h>
#include <pthread.h>
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

void set_mem_read_execute(void *addr, uint64_t size){
    mprotect(addr, size, PROT_READ | PROT_EXEC);
    return;
}

void set_mem_read_write(void *addr, uint64_t size){
    int ret;
    if((ret = mprotect(addr, (size_t)size, (PROT_READ|PROT_WRITE|PROT_EXEC))) == 0){
        printf("[PATCHER] Successfully set r-w-x [%p]\n", addr);
    }else {
        printf("[PATCHER] Failed while setting r-w-x [%p] (%d)\n", addr, ret);
        printf("Address: %p\nSize: %llu\n", addr, size);
        printf("ERROR: %s\n", strerror(errno));
        exit(errno);
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
    set_mem_read_write(addr, sizeof(uint64_t));
    uint64_t orig_bytes = *(uint64_t *)addr;
    printf("[JMP] original bytes: %08llx\n", orig_bytes);
    uint32_t jmp_offset = (uint32_t)((char*)dst - (char*)addr - 5);
    printf("[JMP] offset: %08x\n", jmp_offset);
    jmp_offset = OSSwapInt32(jmp_offset);
    uint64_t bytes = 0xE900000000000000LL;
    bytes |= ((uint64_t)jmp_offset & 0xFFFFFFFF) << 24;
    bytes = OSSwapInt64(bytes);
    *(uint64_t *)addr = bytes;
    printf("[JMP] offset: %08x\n", jmp_offset);
    printf("[PATCHER] replaced bytes: %08llx\n", bytes);
    
    set_mem_read_execute(addr, sizeof(uint64_t));
    
    return orig_bytes;
}
