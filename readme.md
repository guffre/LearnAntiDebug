## IsDebuggerPresent

This technique goes over the "IsDebuggerPresent()" API call.

The API call actually accesses the PEB (Process Environment Block) and reads the value of the "BeingDebugged" flag.

This flag is set to either 1 or 0, if the process is being debugged or not.

The file reviews calling the API, as well as accessing the PEB directly.

## NtGlobalFlag

There is an undocumented API called RtlGetNtGlobalFlags found in ntdll. Viewing it in Ghidra, you can see it is pretty straightforward:

Ghidra view of 32-bit:

Ghidra view of 64-bit:

Using this MSDN page as a reference, we can see what each of the flags mean:
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/gflags-flag-table

When a debugger is present, the following three flags are set:

FLG_HEAP_ENABLE_TAIL_CHECK 	0x10
FLG_HEAP_ENABLE_FREE_CHECK 	0x20
FLG_HEAP_VALIDATE_PARAMETERS 	0x40