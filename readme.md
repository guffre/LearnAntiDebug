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
