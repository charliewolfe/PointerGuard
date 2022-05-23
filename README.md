# PointerGuard
PointerGuard is a proof-of-concept tool used to create 'guarded' pointers which disguise pointer addresses, monitor reads/writes, and prevent access from external processes.

## Explanation
PointerGuard is implemented using a Vectored Exception Handler (VEH).

### Disguise Pointers
When a guarded pointer is created, it is assigned an invalid (disguised) address. Once the invalid pointer is dereferenced, an access violation is thrown to be caught by our VEH. If the exception handler determines that the access violation was caused from a guarded pointer, the register containing the invalid pointer will be replaced with the real pointer and execution will continue. 

### Monitor reads/writes
PointerGuard can be used to determine when and where a guarded pointer is dereferenced from. In the provided code, this is done by printing the instruction pointer (`RIP`) each time a guarded pointer is dereferenced.

### Prevent external access
When an external process tries to read our guarded pointer (e.g. using `ReadProcessMemory`), the VEH will not be triggered and the address will be recognized as invalid. 

## Example Output
```
Real pointer: 0x00000067FBD9F834
Fake pointer: 0x0000000001000001
Guarded pointer 0x0000000001000001 accessed from 0x00007FF790B114E0
Dereferenced real pointer (0x00000067FBD9F834): 50
Dereferenced fake pointer (0x0000000001000001): 50 
                                                                                                                                                   
Writing to the fake pointer...
Guarded pointer 0x0000000001000001 accessed from 0x00007FF790B11550
Guarded pointer 0x0000000001000001 accessed from 0x00007FF790B11563
Dereferenced real pointer (0x00000067FBD9F834): 60
Dereferenced fake pointer (0x0000000001000001): 60
```

## Build
Build as an x64 executable using Visual Studio 2022.

## Note
The binaries were only tested on Windows 10 21H1.

Code Optimization must be disabled (/Od).
