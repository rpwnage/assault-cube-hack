#define AC_BASE 0x100000000
static void *entryOffset          = (void*)0x18c0;
static void *commandHandlerOffset = (void*)0x3F58E;
static void *pushMessageOffset    = (void*)0x4B720;
static void *BigMessageOffset     = (void*)0x91160;
static void *HandleBulletDec      = (void*)0x103fda;
static void *shotFired            = (void*)0x100370;
static void *entityOffset         = (void*)0x1ABEF8;
static void *playerBase;
static void *entityBase;