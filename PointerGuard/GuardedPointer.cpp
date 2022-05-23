#include "GuardedPointer.h"

GuardedPointer::GuardedPointer(
	PVOID PointerToGuard,
	BOOL MonitorReads
) {
	this->Pointer = PointerToGuard;
	this->MonitorReads = MonitorReads;
}
