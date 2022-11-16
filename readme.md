## IsDebuggerPresent

This technique goes over the "IsDebuggerPresent()" API call.

The API call actually accesses the PEB (Process Environment Block) and reads the value of the "BeingDebugged" flag.

This flag is set to either 1 or 0, if the process is being debugged or not.

The file reviews calling the API, as well as accessing the PEB directly.
