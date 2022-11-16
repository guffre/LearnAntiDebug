#include <stdio.h>
#include <windows.h>

void normal(int argc, char** argv, char** argve) {
    printf("[+] Normal mode, argc: %d\n", argc);
}

void* function = normal;

void detected(int argc, char** argv, char** argve) {
    printf("[!] Debugger Detected!\n");
    function = normal;
}

int main(int argc, char** argv, char** argve) {
    /* API call that checks PEB for "BeingDebugged" */
    if (IsDebuggerPresent()){
        function = detected;
    }
    (*(void(*)(int, char**, char**)) function)(argc, argv, argve);
    
    /* You can hide the  API call and access the PEB directly */
    #if defined(_M_X64)
    unsigned __int64 PEB = __readgsqword(0x60);
    #else
    unsigned __int32 PEB = __readfsdword(0x30);
    #endif
    char BeingDebugged = ((char*)PEB)[2];
    if (BeingDebugged) {
        function = detected;
    }
    (*(void(*)(int, char**, char**)) function)(argc, argv, argve);
}