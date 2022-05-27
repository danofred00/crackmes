/*
	Author 			  : Danofred
	Last Modification : 27/05/2022
	----------------------------
	https://crackmes.one/
*/

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

void AddControls(HWND);
void CheckSerial(void);
void CheckDisk(void);
void CheckDebugger(void);
bool __str_cmp(const char *str1, const char *str2, size_t sz);
void GenerateSerial(char *buffer);
HWND hLabel, hEdit, hButton;

#define MAX_BUFFER_SIZE  0x19  // 25 en decimal
#define MAX_SERIAL_SIZE 0x19 // => 25 en decimal

#define LABEL_X 20
#define LABEL_Y 30
#define LABEL_WIDTH 50
#define LABEL_HEIGTH 30
#define EDIT_WIDTH 300
#define EDIT_HEIGTH 30
#define EDIT_X (LABEL_X + LABEL_WIDTH + 10)
#define EDIT_Y (LABEL_Y - (LABEL_HEIGTH)/4)
#define BUTTON_WIDTH 150
#define BUTTON_HEIGTH 50
#define BUTTON_X (EDIT_X + EDIT_WIDTH - BUTTON_WIDTH)/2
#define BUTTON_Y (LABEL_Y + LABEL_HEIGTH + 20)

#define WINDOW_WIDTH 420
#define WINDOW_HEIGTH 200 // (BUTTON_Y + BUTTON_HEIGTH + 20)

#define BUTTON_CLICKED 0x1

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// petite protection du crackme
	CheckDebugger();
	CheckDisk();

	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(hInstance, MAKEINTRESOURCE(10)); /* Load icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Crackme 01 By @Danofred",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		WINDOW_WIDTH, /* width */
		WINDOW_HEIGTH, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
			AddControls(hwnd);
			break;

		case WM_COMMAND:

			switch(LOWORD(wParam))
			{
				case BUTTON_CLICKED:
					CheckSerial();
					break;
			}

		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void AddControls(HWND hwnd)
{
	hLabel = CreateWindow("Static", "Serial : ", WS_CHILD | WS_VISIBLE | SS_CENTER,
							LABEL_X, LABEL_Y, LABEL_WIDTH, LABEL_HEIGTH, hwnd, NULL, NULL, NULL);
	hEdit = CreateWindow("Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
							EDIT_X, EDIT_Y, EDIT_WIDTH, EDIT_HEIGTH, hwnd, NULL, NULL, NULL);
	hButton = CreateWindow("Button", "Check Serial", WS_CHILD | WS_VISIBLE | BS_CENTER | WS_BORDER,
							BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGTH, hwnd, (HMENU)BUTTON_CLICKED, NULL, NULL);
}

void CheckSerial(void)
{
	char buffer[MAX_BUFFER_SIZE]{0}, serial[MAX_SERIAL_SIZE]{0};

	// generation du serial
	GenerateSerial(serial);

	// on recupere l'entree de l'utilisateur

	GetWindowText(hEdit, buffer, MAX_BUFFER_SIZE);

	if(__str_cmp(buffer, serial, strlen(serial)))
		MessageBox(0, "Good Serial", "Good !", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
	else
		MessageBeep(MB_ICONERROR);

	return;
}


bool __str_cmp(const char *str1, const char *str2, size_t sz)
{
	for(size_t i=0; i<sz; i++)
	{
		if(str1[i] != str2[i])
			return FALSE;
	}

	return TRUE;
}

void GenerateSerial(char *buffer)
{
	// SERIAL = 49 2D 41 4D 2D 41 2D 43 52 34 43 4B 45 52 5F 28 4F 20 7C 20 4F 29 -> Hexa
	char key[] = {
		0x49 , 0x2D , 0x41 , 0x4D ,
		0x2D , 0x41 , 0x2D , 0x43 ,
		0x52 , 0x34 , 0x43 , 0x4B ,
		0x45 , 0x52 , 0x5F , 0x28 ,
        0x6F , 0x20 , 0x7C , 0x20 ,
        0x6F , 0x29, 0x00
	};

	for(int i=0; i<strlen(key); i++)
		buffer[i] = key[i];

	return;
}

void CheckDisk(void)
{
	char buf[3];
	DWORD dir = GetCurrentDirectory(0x3, buf);

	// if the disk is CD_ROM disk
	if(GetDriveType(buf) != DRIVE_CDROM)
	{
		MessageBox(0, "This Crackme can't be launch on this drive", "Drive error", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}

}

void CheckDebugger(void)
{
	if(IsDebuggerPresent())
	{
		MessageBox(0, "This program couldn't work in a debugger", "Alert Debugger !", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(EXIT_FAILURE);
	}
}