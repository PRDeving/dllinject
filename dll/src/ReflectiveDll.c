//===============================================================================================//
// This is a stub for the actuall functionality of the DLL.
//===============================================================================================//
#include "ReflectiveLoader.h"
#include <stdio.h>

// Note: REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR and REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN are
// defined in the project properties (Properties->C++->Preprocessor) so as we can specify our own 
// DllMain and use the LoadRemoteLibraryR() API to inject this DLL.

// You can use this value as a pseudo hinstDLL value (defined and set via ReflectiveLoader.c)
extern HINSTANCE hAppInstance;
//===============================================================================================//

int getEBP(void) {
	_asm {
		mov eax, [ebp]
	}
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved )
{
    BOOL bReturnValue = TRUE;
	switch( dwReason ) 
    { 
		case DLL_QUERY_HMODULE:
			if( lpReserved != NULL )
				*(HMODULE *)lpReserved = hAppInstance;
			break;
		case DLL_PROCESS_ATTACH:
			hAppInstance = hinstDLL;

			HMODULE base = GetModuleHandle("dummy.exe");

			printf("\n-------------------------\n");
			printf("getEBP is %#x\n", (int)getEBP());
			printf("Base is %#x\n\n", (int)base);

			int * p = (int *)((int)base + 71983);
			*p = 0x83;
			p++;
			*p = 0xE8;
			p++;
			*p = 0xFF;
			
			/* int * p = (int *)(0x00AFF928);
			if (p != NULL) {
				printf("\nVal in %p is %d\n\n", p, *p);
				*p = 4000;
				printf("\nNew val in %p is %d\n\n", p, *p);
			}*/

			MessageBoxA( NULL, "Hello from DllMain!", "Reflective Dll Injection", MB_OK );
			break;
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
            break;
    }
	return bReturnValue;
}