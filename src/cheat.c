#include <sys/proc_info.h>
#include <libproc.h>
#include <stdio.h>
#include <mach/mach_init.h>
#include <sys/sysctl.h>
#include <mach/mach_vm.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mach/mach.h>

pid_t getPIDByName(char * name){
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof pids);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    for (int i = 0; i < procCnt; i++){
        if (!pids[i]) continue;
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        int len = strlen(curPath);
        if (len){
            int pos = len;
            while (pos && curPath[pos] != '/') --pos;
            strcpy(curName, curPath + pos + 1);
            if (!strcmp(curName, name)){
                return pids[i];
            }
        }
    }
    return 0;
}

int main(int argc, char **argv){
    int hackedAmmo = 12;
    int pid = getPIDByName(argv[1]);
    vm_offset_t buffer = 0;
    unsigned int size;
    kern_return_t ret;
    printf("Injecting cheat into %d...\n", pid);
    mach_port_t pTw;
    vm_region_basic_info_data_t info;
    mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
    mach_port_t objectName;
    mach_vm_size_t vsize;
    vm_address_t baseAddress;
    ret = task_for_pid(mach_task_self(), pid, &pTw);
    if(ret != KERN_SUCCESS) printf("Error 1\n");
    mach_vm_address_t address = 1;
    int regionCount = 0, flag = 0;
    while(flag == 0){
        if((ret = mach_vm_region(pTw, &address, &vsize, VM_REGION_BASIC_INFO, (vm_region_info_t) &info, &count, &objectName)) == KERN_SUCCESS){
            if(regionCount == 0){
                baseAddress = address;
                regionCount++;
            }
            address += vsize;
        }else{ flag = 1; }
    }
    printf("Got base: 0x%02lx\n", baseAddress);
    if((ret = vm_read(pTw, (0x10403F + baseAddress), sizeof(uint32_t), &buffer, &size)) == KERN_SUCCESS){
        void **bytes = (void *)buffer;
        printf("Ammo: 0x%02x\n", *((int*)bytes));
    }
    if((ret = vm_write(pTw, (0x10403F + baseAddress), (vm_address_t)&hackedAmmo , sizeof(hackedAmmo))) == KERN_SUCCESS){
        printf("Gave Ammo.\n");
    }else {
        printf("Failed to write\n");
    }
	return 0;
}
