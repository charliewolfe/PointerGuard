#pragma once
#include <Windows.h>

BOOL
InitializePointerGuard();

PVOID
CreateGuardedPointer(
	PVOID PointerToGuard,
	BOOL MonitorReads = FALSE
);

BOOL
DestroyPointerGuard();
