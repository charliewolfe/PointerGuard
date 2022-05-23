#include "PointerGuard.h"
#include <stdio.h>
#include <unordered_map>
#include "GuardedPointer.h"

#define KEY 0xDEAD

PVOID Handle;
std::unordered_map<PVOID, GuardedPointer*> PointerMap;
ULONGLONG CurrentAddress = 0x1000000;

LONG WINAPI
Handler(
	PEXCEPTION_POINTERS ExceptionInfo
) {
	PVOID ExceptionAddress = (PVOID)ExceptionInfo->ContextRecord->Rax;
	if (!PointerMap.count(ExceptionAddress))
		return EXCEPTION_ACCESS_VIOLATION;

	if (PointerMap[ExceptionAddress]->MonitorReads)
		printf("Guarded pointer 0x%p accessed from 0x%p\n", ExceptionInfo->ContextRecord->Rax, ExceptionInfo->ContextRecord->Rip);

	PVOID EncryptedPointer = PointerMap[ExceptionAddress]->Pointer;
	ExceptionInfo->ContextRecord->Rax = (ULONGLONG)EncryptedPointer ^ KEY;

	return EXCEPTION_CONTINUE_EXECUTION;
}

BOOL
InitializePointerGuard() {
	Handle = AddVectoredExceptionHandler(1, Handler);
	if (!Handle)
		return FALSE;
	return TRUE;
}

PVOID
CreateGuardedPointer(
	PVOID PointerToGuard,
	BOOL MonitorReads
) {
	if (PointerMap.count(PointerToGuard))
		return NULL;

	PointerMap[(PVOID)++CurrentAddress] = new GuardedPointer((PVOID)((ULONGLONG)PointerToGuard ^ KEY), MonitorReads);

	return (PVOID)CurrentAddress;
}

BOOL
DestroyPointerGuard() {
	for (auto i = PointerMap.begin(); i != PointerMap.end(); i++)
		delete i->second;

	if (!RemoveVectoredExceptionHandler(Handle))
		return FALSE;
	return TRUE;
}
