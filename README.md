# assault-cube-hack
MacOS Based Assault Cube hack. This hack includes a working openGL Hook, function overrides and inline jump patching.
# preface
This Hack is barely usable and only for development purposes at the moment. As of right now it doesnt have any functionality. The only things that work are the openGL Hook and the Arrow Key Menu navigation
### How to run
- run `make`
- inject the dylib into assaultcube with either [osxinj](https://github.com/scen/osxinj) for development or [insert_dylib](https://github.com/Tyilo/insert_dylib) for persistence
### Offsets
0x10002421c - change `jne 0x10002422e` to `jmp 0x10002422e` to allow edit mode in multiplayer

### Credits 
- Memory Managment and Hooking was done by [notxdev](https://github.com/notxdev)
- The openGL Hook is based on [karek314](https://github.com/karek314/macOS-OpenGL-hook)'s version.
