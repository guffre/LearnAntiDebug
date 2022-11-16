## IsDebuggerPresent

This technique goes over the "IsDebuggerPresent()" API call.

Here is the Windows man page description:
![firefox_2022-11-15_22-53-45](https://user-images.githubusercontent.com/21281361/202087912-fcca6d8e-cf9f-4e3a-a67d-c8b9886200e5.png)

The API call actually accesses the PEB (Process Environment Block) and reads the value of the "BeingDebugged" flag.
In 64-bit code, the PEB address can be found in the GS register:

![x64dbg_2022-11-15_22-55-39](https://user-images.githubusercontent.com/21281361/202087881-50b26acf-a48e-4365-a033-0daae1c02cf3.png)

In 32-bit code, the PEB address can be found in the FS register:

![x32dbg_2022-11-15_22-58-58](https://user-images.githubusercontent.com/21281361/202087893-ecd92678-c6f6-43ed-a8aa-83a767e37a0c.png)

This flag is set to either 1 or 0, if the process is being debugged or not.

## NtGlobalFlag

There is an undocumented API called RtlGetNtGlobalFlags found in ntdll. Viewing it in Ghidra, you can see it is pretty straightforward:

Ghidra view of 64-bit:

![javaw_2022-11-16_16-29-54](https://user-images.githubusercontent.com/21281361/202317015-b797610f-299b-4b16-bedb-f40dc1e841bc.png)

Ghidra view of 32-bit:

![javaw_2022-11-16_16-29-44](https://user-images.githubusercontent.com/21281361/202317026-2a01a2a2-f7c2-4627-ada3-6a91ef3262d5.png)


Using this MSDN page as a reference, we can see what each of the flags mean:
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/gflags-flag-table

When a debugger is present, the following three flags are set:

```
FLG_HEAP_ENABLE_TAIL_CHECK  	0x10  
FLG_HEAP_ENABLE_FREE_CHECK  	0x20  
FLG_HEAP_VALIDATE_PARAMETERS 	0x40  
```
