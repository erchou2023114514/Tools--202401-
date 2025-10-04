/*
借鉴文档： https://blog.csdn.net/weixin_42112038/article/details/127480471
感谢这个大师的帮助！awa
*/ 
#include <windows.h>
#include <commctrl.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string>
#include <vector>

__int64 __stdcall WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hIns;

char pn;

HWND hBdCst = NULL;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != *(DWORD*)lParam) return TRUE;
    char szClass[5];
    if (GetClassName(hwnd, szClass, 5) && _stricmp(szClass, "Afx:") == 0) {
        int nLength = GetWindowTextLength(hwnd);
        char szName[256];
        GetWindowText(hwnd, szName, sizeof(szName));
        if (_stricmp(szName, "屏幕广播") == 0 ||
            (nLength > strlen(" 正在共享屏幕") && 
             _stricmp(szName + nLength - strlen(" 正在共享屏幕"), " 正在共享屏幕") == 0)) {
            hBdCst = hwnd;
            return FALSE;
        }
    }
    return TRUE;
}

bool IsAdm() {
	BOOL f = FALSE;
	PSID g = NULL;
	SID_IDENTIFIER_AUTHORITY n = SECURITY_NT_AUTHORITY;
	if (AllocateAndInitializeSid(&n, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &g)) {
		CheckTokenMembership(NULL, g, &f);
		FreeSid(g);
	}
	return f;
}

void Elev() {
	CHAR p[MAX_PATH];
	GetModuleFileNameA(NULL, p, MAX_PATH);
	SHELLEXECUTEINFOA s = { sizeof(s) };
	s.lpVerb = "runas";
	s.lpFile = p;
	s.nShow = SW_NORMAL;
	if (ShellExecuteExA(&s)) {
		exit(0);
	}
}
/*
static void KillMthKeyboradControler() {

	return;
}
*/
//Keyborad
static HANDLE keyHook = NULL;
static HHOOK kbdHook = NULL;
static HWND BtKbh = NULL;

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(kbdHook, nCode, wParam, lParam);
}

static void KillMthKeyboradControler() {
	HANDLE hDevice = CreateFileA("\\\\.\\TDKeybd", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice != INVALID_HANDLE_VALUE) {
		BOOL bEnable = TRUE;
		if (DeviceIoControl(hDevice, 0x220000, &bEnable, sizeof(bEnable),
			NULL, 0, NULL, NULL)) {
		}
		CloseHandle(hDevice);
	}
	system("sc stop tdkeybd 2>nul");
	system("sc delete tdkeybd 2>nul");
	system("ren C:\\Windows\\System32\\drivers\\tdkeybd.sys tdkeybd.sys.bak 2>nul");
}

DWORD WINAPI KeyHookThreadProc(LPVOID lpParameter) {
	HMODULE hModule = GetModuleHandle(NULL);
	while (true) {
		kbdHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)HookProc, hModule, 0);
		Sleep(25);
		if (kbdHook) {
			UnhookWindowsHookEx(kbdHook);
			kbdHook = NULL;
		}
	}
	return 0;
}

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE Fuck, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	hIns = hInstance;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO b;
	GetConsoleScreenBufferInfo(h, &b);
	if (!IsAdm()) {
		pn = 'B';
		if (MessageBoxA(NULL, "检测到你没有以管理员身份运行此程序...\n务必以管理员模式运行程序，否则程序部分功能会失效", "WARNING", MB_YESNO | MB_ICONWARNING)==IDYES) {
			Elev();pn = 'A';
		}
		// printf("检测到你没有以管理员身份运行此程序...\n务必以管理员模式运行程序，否则程序部分功能会失效\n(1)提升权限||(2)继续\n>");
	}
	else
	{
		pn = 'A';
	}
	WNDCLASSEXA wcex = { NULL };
	/*
	UINT        cbSize;
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;
    HICON       hIconSm;
	*/
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WindowProc;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpszClassName = "SP";
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = NULL;
	RegisterClassExA(&wcex);
	//CreateWindowExW(0, L"SWC", L"SWC", WS_OVERLAPPEDWINDOW, 91, 78, 500, 500, NULL, NULL, hInstance, NULL);
	HWND hWnd = CreateWindowExA(0, "SP", "Tools", WS_OVERLAPPEDWINDOW, 91, 78, 550, 600, NULL, NULL, hInstance, NULL);
	if (hWnd == 0) {
		MessageBoxA(NULL, "[ERROR]CreateWindowEx Failed!", "ERROR", MB_OK);
		return -1;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	return 0;
}
/*
printf("权限 Premisson: %c .A:Administrator,B:User\n", pn);
		SetConsoleTextAttribute(h, b.wAttributes);

		printf("(1) 关机 Shutdown\n");
		printf("(2) 解除控制 Kill Control-Process\n");
		printf("(3) 解除网络限制 Kill Net-control-Process\n");
		printf("(4) 运行命令行 Run terminal\n");
		printf("(5) 蓝瓶钙 BSOD\n");
		printf("(6) 解除文件限制 Stop File-Service\n");
		printf("(7) 特殊提权 sudo\n");
		printf("(8) 广播窗口化 Windows Boradcast\n");
		printf("(9) 解除键盘控制 Cover KeyBorad-LL\n");
		printf("(-1) 退出 Exit\n");
		printf("/**===============================================================**\\\n");
		printf("Choose a value...\n");
		scanf_s("%d", &choose);
*/
static HFONT BFont = NULL,hFont=NULL,ButtonFont=NULL;
bool TdNetFilter, TdFileFilter;
__int64 __stdcall WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE: {

		BFont = CreateFontA(32, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "微软雅黑");
		hFont = CreateFontA(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "宋体");
		ButtonFont = CreateFontA(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "宋体");
		CreateWindowA("BUTTON", "关机 Shutdown", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 50 , 290, 50, hWnd, (HMENU)1, hIns, NULL);
		CreateWindowA("BUTTON", "解除控制 Kill Control-Process", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 100, 290, 50, hWnd, (HMENU)2, hIns, NULL);
		CreateWindowA("BUTTON", "解除网络限制 Kill Net-control-Process", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 150, 290, 50, hWnd, (HMENU)3, hIns, NULL);
		CreateWindowA("BUTTON", "运行命令行 Run terminal", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 200, 290, 50, hWnd, (HMENU)4, hIns, NULL);
		CreateWindowA("BUTTON", "蓝瓶钙 BSOD", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 250, 290, 50, hWnd, (HMENU)5, hIns, NULL);
		CreateWindowA("BUTTON", "解除文件限制 Stop File-Servic", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 300, 290, 50, hWnd, (HMENU)6, hIns, NULL);
		CreateWindowA("BUTTON", "特殊提权 sudo", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 350, 290, 50, hWnd, (HMENU)7, hIns, NULL);
		CreateWindowA("BUTTON", "广播窗口化 Windows Boradcast", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 400, 290, 50, hWnd, (HMENU)8, hIns, NULL);
		//CreateWindowA("BUTTON", "解除键盘控制 Cover KeyBorad-LL", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 450, 290, 50, hWnd, (HMENU)9, hIns, NULL);
		BtKbh = CreateWindowA("BUTTON", "解除键盘控制 Cover KeyBorad-LL", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 450, 290, 50, hWnd, (HMENU)9, hIns, NULL);
		CreateWindowA("BUTTON", "退出 Exit", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 500, 290, 50, hWnd, (HMENU)0, hIns, NULL);
		HWND hwndButton;
		for (int i = 0; i <= 10; i++) {
			hwndButton = GetDlgItem(hWnd, i);
			if (hwndButton) {
				SendMessage(hwndButton, WM_SETFONT, (WPARAM)ButtonFont, TRUE);
			}
		}
		keyHook = CreateThread(NULL, 0, KeyHookThreadProc, NULL, CREATE_SUSPENDED, NULL);
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		HFONT FONT = (HFONT)SelectObject(hdc, BFont);
		TextOutA(hdc, 50, 10, "学校机房管理小工具", 18);
		SelectObject(hdc, hFont);
		//Premission
		RECT Rect;
		Rect.left = 300;
		Rect.top = 100;
		Rect.right = rect.right - 0;
		Rect.bottom = rect.bottom - 100;
		TextOutA(hdc, 1, 999, "GgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGgggggggggggggggggggGggggggggggggggggggg", 200);
		LPCSTR Text = NULL;
		//LPCWSTR Fuck = L"666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666";
		if (pn == 'A') {
			Text = "创作者：erchou2023114514\n免责说明：在任何情况下，都有：\n(1)被管理人员抓住并处分自行承担。\n(2)禁止抄袭，反编译此程序。\nPremission : A";
		}
		else {
			Text = "创作者：erchou2023114514\n免责说明：在任何情况下，都有：\n(1)被管理人员抓住并处分自行承担。\n(2)禁止抄袭，反编译此程序。\nPremission : USER\nWarning:非管理员权限会让程序失效!";
		}
		//LPCWSTR Text = L"创作者：erchou2023114514\n免责说明：在任何情况下，都有：\n(1)被管理人员抓住并处分自行承担。\n(2)禁止抄袭，反编译此程序。";
		DrawTextA(hdc, Text, -1, &Rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
		//DrawText(hdc, Fuck, -1, &FUCK, DT_LEFT | DT_TOP | DT_WORDBREAK);
		SelectObject(hdc, FONT);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_COMMAND: {
		int wmid = LOWORD(wParam);
		switch (wmid) {
		case 0: {
			exit(0);
			return 0;
		}
		case 1: {
			if (MessageBoxA(hWnd, "Are you Sure???", "Warning", MB_YESNO|MB_ICONWARNING)==IDYES){
				system("shutdown -s -f -t 5");
			}
			break;
		}
		case 2: {
			if (MessageBoxA(hWnd, "必须在学生机使用！\nUse this on the school which running Control-Process", "Warning", MB_YESNO | MB_ICONWARNING) == IDYES) {
				if (system("taskkill /im Studentmain.exe /f")) {
					MessageBoxA(hWnd, "FAILED!", "ERROR", MB_OK | MB_ICONERROR);
				}
				else {
					MessageBoxA(hWnd, "OK!", "Info", MB_OK);
				}
			}
			break;
		}
		case 3: {
			if (TdNetFilter == 0) {
				if (system("taskkill /im GATESRV.exe /f & taskkill /im MasterHelper.exe /f & sc stop TdNetFilter")) {
					MessageBoxA(hWnd, "FAILED!", "ERROR", MB_OK | MB_ICONERROR);
				}
				else {
					TdNetFilter = 1;
					MessageBoxA(hWnd, "OK!", "Info", MB_OK);
				}
			}
			else {
				if (system("sc start TdNetFilter")) {
					MessageBoxA(hWnd, "FAILED!", "ERROR", MB_OK | MB_ICONERROR);
				}
				else {
					TdNetFilter = 0;
					MessageBoxA(hWnd, "Locked!", "Info", MB_OK);
				}
			}
			
			break;
		}
		case 4: {
			system("start powershell");
			MessageBoxA(hWnd, "OK!", "Info", MB_OK);
			break;
		}
		case 5: {
			if (MessageBoxA(hWnd, "你是否确定！\nAre you sure?", "Warning", MB_YESNO | MB_ICONWARNING) == IDYES) {
				system("taskkill /im svchost.exe /f");
					MessageBoxA(hWnd, "Failed!", "ERROR", MB_OK | MB_ICONERROR);
			}
			break;
		}
		case 6: {
			if (system("sc stop TdFileFilter")) {
				MessageBoxA(hWnd, "Failed!", "ERROR", MB_OK | MB_ICONERROR);
			}
			else {
				MessageBoxA(hWnd, "OK!", "Info", MB_OK);
			}
			break;
		}
		case 7: {
			system("sc stop TrustedInstaller");
			int Result = system("sc start TrustedInstaller");
			if (system("sc start TrustedInstaller")) {
				if (system("echo [%time% ERROR]Broken service \"TrustedInstaller\" & DISM /Online /Cleanup-Image /StartComponentCleanup & DISM / Online / Cleanup - Image / ScanHealth & DISM / Online / Cleanup - Image / CheckHealth & sfc /scannow & sc config TrustedInstaller binPath = \"%SystemRoot%\\servicing\\TrustedInstaller.exe\" && sc config TrustedInstaller start = demand && sc sdset TrustedInstaller D : (A;;CCLCSWRPWPDTLOCRRC;;;SY)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;BA)(A;;CCLCSWLOCRRC;;;IU)(A;;CCLCSWLOCRRC;;;SU)")) {
					Result=MessageBoxA(hWnd, "Fixing TrustedInstaller Failed!\n你要继续吗？", "ERROR", MB_YESNO | MB_ICONERROR);
					if (Result == IDNO) {
						exit(0);
					}
					//return 0;
				}
				else {
					MessageBoxA(hWnd, "Fixing TrustedInstaller successful.", "Message", MB_OK);
				}
			}
			int Chs = MessageBoxA(hWnd, "现在只能获得TrustedInstaller权限Only Trustedinstaller Premisson...\n系统为WindowNT10.0以上？", "Message", MB_YESNOCANCEL);
			if (Chs == IDYES) {
				if (MessageBoxA(hWnd, "是否下载了NTObjectManager模块？Do you installed NTObjectManager module?\n", "Message", MB_YESNO) == IDNO) {
					MessageBoxA(hWnd,"需要允许脚本运行！Need allow PowershellScript run!\n在“设置”设置。Allow at \"Setting\"\n加载时间会比较久","Warning",MB_OK|MB_ICONWARNING);
					system("powershell -Command \"& {"
						"mkdir C:\\token;"
						"Set-ExecutionPolicy -Scope LocalMachine -ExecutionPolicy RemoteSigned; "
						"Save-Module -Name NtObjectManager -Path C:\\token; "
						"Install-Module -Name NtObjectManager -Force; "
						"Import-Module NtObjectManager;pause;}\""
					);
				}
				system("powershell -Command \"& {"
					"Start-Service TrustedInstaller; "
					"Set-NtTokenPrivilege SeDebugPrivilege; "
					"$p = Get-NtProcess -Name TrustedInstaller.exe; "
					"New-Win32Process cmd.exe -CreationFlags NewConsole -ParentProcess $p;pause;}\""
				);
			}
			else if (Chs==IDNO){
				system("sc stop TrustedInstaller & "
					"sc config TrustedInstaller binPath= \"cmd /k start\" type= own & "
					"sc start TrustedInstaller & sc stop TrustedInstaller & "
					"sc config TrustedInstaller binPath= \"%%SystemRoot%%\\servicing\\TrustedInstaller.exe\" & "
					"sc start TrustedInstaller"
				);
			}
			else {
				return 0;
			}
			break;
		}
		case 9: {
			//MessageBoxA(NULL, "原理：加载WH_KEYBORAD_LL覆盖原钩子，达到解控目的.\n这个是需要重复执行的，所以不会提示其它。", "Info", MB_OK);
			
			LRESULT check = SendMessage(BtKbh, BM_GETCHECK, 0, 0);
			if (check == BST_CHECKED) {
				
				ResumeThread(keyHook);

				HANDLE hDevice = CreateFileA("\\\\.\\TDKeybd", GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
				if (hDevice != INVALID_HANDLE_VALUE) {
					BOOL bEnable = TRUE;
					if (DeviceIoControl(hDevice, 0x220000, &bEnable, sizeof(bEnable),
						NULL, 0, NULL, NULL)) {
						MessageBoxA(hWnd, "Keyborad unlocked!", "Message", MB_OK);
					}
					else {
						MessageBoxA(hWnd, "Failed!\nUnlock keyborad failed.", "Error", MB_OK | MB_ICONERROR);
					}
					CloseHandle(hDevice);
				}
				else {
					MessageBoxA(hWnd, "Failed!\n", "Error", MB_OK | MB_ICONERROR);
				}

				KillMthKeyboradControler();
				MessageBoxA(hWnd, "Done!", "Message", MB_OK);
			}
			else {

				SuspendThread(keyHook);
				if (kbdHook) {
					UnhookWindowsHookEx(kbdHook);
					kbdHook = NULL;
				}
				MessageBoxA(hWnd, "Done!", "Message", MB_OK);
			}
			break;
		}
		case 8: {
			DWORD pid = 0;
    		PROCESSENTRY32 pe;
    		pe.dwSize = sizeof(PROCESSENTRY32);
    		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    		if (Process32First(hSnapshot, &pe)) {
    		    do {
     		       if (_stricmp(pe.szExeFile, "StudentMain.exe") == 0) {
    		            pid = pe.th32ProcessID;
    		            break;
    		        }
    		    } while (Process32Next(hSnapshot, &pe));
    		}
    		CloseHandle(hSnapshot);
    		if (pid == 0) {
    		    MessageBoxA(hWnd, "studentmain.exe 不存在", "Message", MB_OK);
    		    break;
    		}
       		hBdCst = NULL;
    		EnumWindows(EnumWindowsProc, (LPARAM)&pid);
    		if (hBdCst == NULL) {
    		    MessageBoxA(hWnd, "未找到广播窗口", "Message", MB_OK);
    		    break;
    		}
    		LONG lStyle = GetWindowLong(hBdCst, GWL_STYLE);
    		BOOL bWindowing = lStyle & (WS_CAPTION | WS_SIZEBOX);
    		if(bWindowing){
    			if(MessageBoxA(NULL,"是否替换到全屏？","Warning",MB_YESNO)==IDNO){
    				return DefWindowProc(hWnd,msg,wParam,lParam);
				}
			}
    		PostMessage(hBdCst, WM_COMMAND, MAKEWPARAM(1004, BM_CLICK), 0);
    
    		MessageBoxA(hWnd, bWindowing ? "切换到全屏" : "切换到窗口", "Message", MB_OK);
    		break;
			//MessageBoxA(NULL, "原理：模拟点击，向窗口发送消息。", "Info", MB_OK);
			//
			//ToggleBroadcastWindow();
			//MessageBoxA(NULL, "不会写awa", "Message", MB_OK);
			//MessageBoxA(NULL, "Done!", "Message", MB_OK);
			break;
		}
	}
	break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

