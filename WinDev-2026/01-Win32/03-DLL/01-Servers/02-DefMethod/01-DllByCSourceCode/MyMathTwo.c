// Header files
#include<Windows.h>

// Entry-point function
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	// code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return(TRUE);
}

// Functions to be exported from this DLL
int MakeCube(int num)
{
	// function prototype
	void CheckNumber(int);

	// code
	CheckNumber(num);
	return (num * num * num);
}

// functions for DLL's internal usage
void CheckNumber(int num)
{
	// code
	if (num < 0)
	{
		MessageBox(NULL, TEXT("User input number is less than 0"), TEXT("NUMBER CHECK"), MB_OK);
	}
	else if (num > 0)
	{
		MessageBox(NULL, TEXT("User input number is greater than 0"), TEXT("NUMBER CHECK"), MB_OK);
	}
	else
	{
		MessageBox(NULL, TEXT("User input number is 0"), TEXT("NUMBER CHECK"), MB_OK);
	}
}
