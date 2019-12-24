#pragma once
#include <stdio.h>

#include <mach/mach.h>
#include <mach/vm_region.h>
#include <mach-o/dyld.h>
#include <sys/mman.h>
#include <pthread.h>

#include <Carbon/Carbon.h>
#include <CoreGraphics/CoreGraphics.h>
#include <OpenCL/opencl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenCL/cl_gl.h>
#include <OpenGL/OpenGL.h>

#include <GLUT/glut.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>

#include "offsets.h"
#include "mach_override.h"

size_t pageSize;
mach_port_t pTw;
kern_return_t ret;
void *calculatePlayerBase();
void *getPointerFromAddress(void *addr);
void drawBitmapText(char *string, float x, float y, float z);
uint64_t patch_jmp(void *addr, void *dst);
void set_mem_rwx(void *addr, uint64_t size);
void set_mem_rw(void *addr, uint64_t size);
void set_mem_rx(void *addr, uint64_t size);
void calculate_aslr_slide();
uint64_t calculate_address_with_aslr(uint64_t base, uint64_t offset_from_base);