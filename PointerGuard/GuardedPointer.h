#pragma once
#include <Windows.h>

struct GuardedPointer {
	PVOID Pointer;
	BOOL MonitorReads;

	GuardedPointer(
		PVOID PointerToGuard,
		BOOL MonitorReads = FALSE
	);
};
