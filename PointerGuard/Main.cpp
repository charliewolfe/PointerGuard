#include <stdio.h>
#include <Windows.h>
#include <cassert>
#include "PointerGuard.h"

INT 
main() {
    if (!InitializePointerGuard()) {
        printf("Failed to initialize PointerGuard\n");
        return 1;
    }

    INT DemoInteger = 50;
    PVOID RealPointer = &DemoInteger;
    PVOID FakePointer = CreateGuardedPointer(RealPointer, TRUE);
    printf("Real pointer: 0x%p\n", RealPointer);
    printf("Fake pointer: 0x%p\n", FakePointer);

    INT DereferencedRealPointer = *(INT*)RealPointer;
    INT DereferencedFakePointer = *(INT*)FakePointer;
    printf("Dereferenced real pointer (0x%p): %i\n", RealPointer, DereferencedRealPointer);
    printf("Dereferenced fake pointer (0x%p): %i\n", FakePointer, DereferencedFakePointer);

    assert(DereferencedRealPointer == DereferencedFakePointer);

    printf("\nWriting to the fake pointer...\n");
    *(INT*)FakePointer = 60;
    DereferencedRealPointer = *(INT*)RealPointer;
    DereferencedFakePointer = *(INT*)FakePointer;

    printf("Dereferenced real pointer (0x%p): %i\n", RealPointer, DereferencedRealPointer);
    printf("Dereferenced fake pointer (0x%p): %i\n", FakePointer, DereferencedFakePointer);

    assert(DereferencedRealPointer == DereferencedFakePointer);

    if (!DestroyPointerGuard()) {
        printf("Failed to destroy PointerGuard\n");
        return 1;
    }

    return 0;
}
