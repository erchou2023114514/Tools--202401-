// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include"Amath.h"
#include<stdio.h>
#include<iostream>
#include"windows.h"

int choose;

static void t1() {
	printf("How to use terminal(能看就看)?\n");
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
	printf("/**===============================================================**\\\n");
	printf("Tools V 0.0.1\n");
	choose = 0;
	return;
}
int main() {
	while (true) {
		system("cls");
		system("Loading");
		system("cls");
		t();
		printf("(1) Shut down\n");
		printf("(2) Stop the control programs\n");
		printf("(3) On Internet\n");
		printf("(4) Run Terminal\n");
		printf("(5) Blue Screen\n");
		printf("(6) Exit\n");
		printf("(7) Reload\n");
		printf("/**===============================================================**\\\n");
		printf("Choose a value...\n");
		scanf_s("%d", &choose);
		if (choose == 1) {
			system("cls");
			t();
			system("shutdown -s -t 0");
			printf("Stopped");//return 0;
		}if (choose == 2) {
			system("cls");
			t();
			system("echo \"Use this on the school which running the tasks and not normal computers\"");
			system("echo \"If not,close this terminal.\"");
			system("Pause");
			system("cls");
			t();
			printf("Waiting...\n");
			system("taskkill /im studentmain.exe /f");
			//			system("cls");
			printf("Stopped\n");
			system("Pause");
			//			return 0;
		}if (choose == 3) {
			system("cls");
			t();
			printf("Sometimes this task won't run \"sc stop tdnetfilter\",pass \"Windows + R\" then type \"sc stop tdnetfilter\" to run again.\n");
			system("Pause");
			system("taskkill /im Masterhelper.exe /f");
			system("sc stop tdnetfilter");
			printf("Stopped\n");
			system("Pause");
			//			return 0;
		}if (choose == 4) {
			char chosen;
			system("cls");
			t();
			printf("Which?(P)owershell,(C)md.\n");
			std::cin >> chosen;
			system("cls");
			t();
			if (chosen == 'P') {
				system("start powershell.exe");
			}
			else {
				system("start cmd.exe");
			}
			t1();
			system("Pause");
			//			return 0;
		}if (choose == 5) {
			system("cls");
			t();
			printf("Loading...");
			system("taskkill /im svchost.exe /f");
			printf("Stopped");
			while (true) {
				t();t1();
			}
		}if (choose == 6) {
			return 0;
		}if (choose == 7) {
			system("cls");
			system("Loading");
			system("cls");
			t();
		}
	}
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
/*
Deepseek“优化”了的
#include <stdio.h>
#include <iostream>
#include <windows.h>

enum MenuOption {
    SHUT_DOWN = 1,
    STOP_CONTROL_PROGRAMS,
    ON_INTERNET,
    RUN_TERMINAL,
    BLUE_SCREEN,
    EXIT,
    RELOAD
};

void clearScreen() {
    system("cls");
}

void displayHeader() {
    printf("/**===============================================================**\\\n");
    printf("Tools V 0.0.1\n");
}

void displayMenu() {
    clearScreen();
    displayHeader();
    printf("(1) Shut down\n");
    printf("(2) Stop the control programs\n");
    printf("(3) On Internet\n");
    printf("(4) Run Terminal\n");
    printf("(5) Blue Screen\n");
    printf("(6) Exit\n");
    printf("(7) Reload\n");
    printf("/**===============================================================**\\\n");
    printf("Choose a value...\n");
}

void displayTerminalHelp() {
    printf("How to use terminal(能看就看)?\n");
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

int main() {
    int choose;
    while (true) {
        displayMenu();
        std::cin >> choose;

        switch (choose) {
            case SHUT_DOWN:
                clearScreen();
                displayHeader();
                system("shutdown -s -t 0");
                printf("Stopped\n");
                break;

            case STOP_CONTROL_PROGRAMS:
                clearScreen();
                displayHeader();
                system("echo \"Use this on the school which running the tasks and not normal computers\"");
                system("echo \"If not, close this terminal.\"");
                system("Pause");
                clearScreen();
                displayHeader();
                printf("Waiting...\n");
                system("taskkill /im studentmain.exe /f");
                printf("Stopped\n");
                system("Pause");
                break;

            case ON_INTERNET:
                clearScreen();
                displayHeader();
                printf("Sometimes this task won't run \"sc stop tdnetfilter\", pass \"Windows + R\" then type \"sc stop tdnetfilter\" to run again.\n");
                system("Pause");
                system("taskkill /im Masterhelper.exe /f");
                system("sc stop tdnetfilter");
                printf("Stopped\n");
                system("Pause");
                break;

            case RUN_TERMINAL: {
                char chosen;
                clearScreen();
                displayHeader();
                printf("Which?(P)owershell,(C)md.\n");
                std::cin >> chosen;
                clearScreen();
                displayHeader();
                if (chosen == 'P' || chosen == 'p') {
                    system("start powershell.exe");
                } else if (chosen == 'C' || chosen == 'c') {
                    system("start cmd.exe");
                }
                displayTerminalHelp();
                system("Pause");
                break;
            }

            case BLUE_SCREEN:
                clearScreen();
                displayHeader();
                printf("Loading...\n");
                system("taskkill /im svchost.exe /f");
                printf("Stopped\n");
                while (true) {
                    displayHeader();
                    displayTerminalHelp();
                }
                break;

            case EXIT:
                return 0;

            case RELOAD:
                clearScreen();
                //Sleep(1000); // Simulate loading
                printf("Loading...\n");
                clearScreen();
                break;

            default:
                printf("Invalid option, please try again.\n");
                system("Pause");
                break;
        }
    }
    return 0;
}
*/
