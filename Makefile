all:
	clang -fms-extensions src/helpers.c src/mach_override.c src/payload.c -dynamiclib -framework CoreGraphics -framework OpenCL -framework OpenGL -framework GLUT -Wno-deprecated -Wno-unused-value -o build/payload.dylib
	// - deprecated - 
	// gcc src/cheat.c -o build/cheat
.PHONY: all
clean:
	rm -rf build/*
