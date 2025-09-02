#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved) {
  
  switch (ul_reason_for_call) {
  
  	case DLL_PROCESS_ATTACH:
    		MessageBox( NULL, "Hello from evil.dll!!!!!","Evil dll message!!!!!!!!!!", MB_OK );
    	break;
  }
  
  return TRUE;
}
