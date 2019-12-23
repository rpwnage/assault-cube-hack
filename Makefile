SOURCE = src/helpers.c src/mach_override.c src/payload.c 
FRAMEWORKS = -framework CoreGraphics -framework OpenCL -framework OpenGL -framework GLUT
WARNINGS = -Wno-deprecated -Wno-unused-value -Wno-implicit-function-declaration
OUTPUT = build/payload.dylib
MISC_FLAGS = -dynamiclib
all:
	clang $(SOURCE) $(MISC_FLAGS) $(FRAMEWORKS) $(WARNINGS) -o $(OUTPUT)
.PHONY: all
clean:
	rm -rf $(OUTPUT)
