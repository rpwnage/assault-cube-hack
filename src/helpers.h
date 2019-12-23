#pragma once
#include <stdio.h>
#include <OpenCL/opencl.h>
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenCL/cl_gl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mach_override.h"
#include "helpers.h"

void drawBitmapText(char *string, float x, float y, float z);
uint64_t patch_jmp(void *addr, void *dst);
void calculate_aslr_slide();
uint64_t calculate_address_with_aslr(uint64_t base, uint64_t offset_from_base);