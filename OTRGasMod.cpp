/* Gasoline Trainer for On The Road Steam Version - by j1m1l0k0 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>

/* prototypes */
int AbrePID(const std::string name);
void EscreverMemoria(LPVOID Address, float Value);
/* prototypes */


int AbrePID(const std::string name)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!Process32First(snapshot, &entry)) return NULL;

	do
	{
		if (strcmp(entry.szExeFile, name.c_str()) == 0)
		{
			CloseHandle(snapshot);
			return entry.th32ProcessID;
		}
	} while (Process32Next(snapshot, &entry));

	CloseHandle(snapshot);
	return NULL;
}

void EscreverMemoria(LPVOID Address, float Value)
{
	HANDLE Process;
	int pid;

	pid = AbrePID("OnTheRoad.exe");
	
	if (pid <= 0)
	{
		std::cout << "OTR not found" << pid << std::endl;
		exit(0);
	}

	Process = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_TERMINATE | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, 0, pid);

	// grava na memoria valor tipo float
	WriteProcessMemory (Process, reinterpret_cast<void*>(Address), &Value, sizeof(Value), 0);
	
	std::cout << "\nValor= " << Value << std::endl;

	CloseHandle(Process);
}

int main(int argc, char **argv)
{
	std::cout << "On The Road - Gasoline Trainer \nby j1m1 l0k0" << std::endl;
	
	//gasoline value
	float valor = 1200;
	
	// Write value in pointer address
	EscreverMemoria(LPVOID(0x1BFAD9F82BC), valor);
	Sleep(1000); //1 segundo
	
	return 0;
}
