#include <stdio.h>
#include <windows.h>

#define CHECK_BIT(flag,bit) (((flag)>>(bit)) & 1)

typedef DWORD (CALLBACK* FUNC)(VOID);

void normal(int argc, char** argv, char** argve) {
    printf("[+] Normal mode, argc: %d\n", argc);
}

void* function = normal;

void detected(int argc, char** argv, char** argve) {
    printf("[!] Debugger Detected!\n");
    function = normal;
}

int main(int argc, char** argv, char** argve) {
    
    /* API call that checks PEB for "NtGlobalFlag" */
    FUNC RtlGetNtGlobalFlags = (FUNC)GetProcAddress(LoadLibrary("ntdll.dll"), "RtlGetNtGlobalFlags");
    DWORD NtGlobalFlag = RtlGetNtGlobalFlags();

    /*
        Bits 4,5, and 6 are all set if the process is being debugged
        This checks if any of the three bits are set
    */
    printf("NtGlobalFlag: %x\n", NtGlobalFlag);
    if (CHECK_BIT(NtGlobalFlag, 4) || 
        CHECK_BIT(NtGlobalFlag, 5) ||
        CHECK_BIT(NtGlobalFlag, 6)) {
            function = detected;
    }
    (*(void(*)(int, char**, char**)) function)(argc, argv, argve);
    
    NtGlobalFlag = 0;
    
    /* You can hide the API call and access the PEB directly */
    #if defined(_M_X64)
    unsigned __int64 PEB = __readgsqword(0x60);
    NtGlobalFlag = (int)(((char*)PEB)[0xbc]);
    #else
    unsigned __int32 PEB = __readfsdword(0x30);
    NtGlobalFlag = (int)(((char*)PEB)[0x68]);
    #endif

    printf("NtGlobalFlag: %x\n", NtGlobalFlag);
    if (CHECK_BIT(NtGlobalFlag, 4) || 
        CHECK_BIT(NtGlobalFlag, 5) ||
        CHECK_BIT(NtGlobalFlag, 6)) {
            function = detected;
    }
    (*(void(*)(int, char**, char**)) function)(argc, argv, argve);
}