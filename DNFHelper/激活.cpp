#include "stdafx.h"
#include "����.h"
#include "����.h"

void ��Ϣѭ��()
{
	VMBEGIN
	MSG msg = { 0 };
	RegisterHotKey(NULL, 1, 0, VK_TAB);
	RegisterHotKey(NULL, 1, 0, VK_HOME);
	RegisterHotKey(NULL, 1, 0, VK_F1);
	RegisterHotKey(NULL, 1, 0, VK_F2);
	RegisterHotKey(NULL, 1, 0, VK_F3);
	RegisterHotKey(NULL, 1, 0, VK_F4);
	RegisterHotKey(NULL, 1, 0, VK_F5);
	RegisterHotKey(NULL, 1, 0, VK_F6);
	RegisterHotKey(NULL, 1, 0, VK_F7);
	RegisterHotKey(NULL, 1, 0, VK_F10);
	RegisterHotKey(NULL, 1, 0, VK_F11);
	
	RegisterHotKey(NULL, 1, 0, VK_END);
	RegisterHotKey(NULL, 1, MOD_ALT, VK_UP);
	RegisterHotKey(NULL, 1, MOD_ALT, VK_DOWN);
	RegisterHotKey(NULL, 1, MOD_ALT, VK_LEFT);
	RegisterHotKey(NULL, 1, MOD_ALT, VK_RIGHT);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (WM_HOTKEY == msg.message)
		{
			switch (msg.wParam)
			{
			case 1:
				switch (LOWORD(msg.lParam))
				{
				case 0:
					switch (HIWORD(msg.lParam))
					{
					case VK_HOME:
						test();
						/*ϵͳ����(L"F1 ȫ������");
						ϵͳ����(L"F2 �Զ�͸������");
						ϵͳ����(L"F3 �ٻ�����");
						ϵͳ����(L"F4 �ٻ���ż");
						ϵͳ����(L"F5 ������CD");
						ϵͳ����(L"F6 ΢��");
						ϵͳ����(L"F11 ��ЧBuff");
						ϵͳ����(L"F12 ȫ����ɱ");
						ϵͳ����(L"Tab ���־���");*/
						break;
					case VK_TAB:
						���־���();
						break;
					case VK_F1:
						����ȫ������();
						break;
					case VK_F2:
						�Զ�͸��();
						break;
					case VK_F3:
						����call();
						break;
					case VK_F4:
						��żcall();
						break;
					case VK_F5:
						��CD();
						break;
					case VK_F6:
						΢��();
						break;
					case VK_F7:
						�Զ�();
						break;
					case VK_F11:
						��ЧBuff();
						break;
					case VK_F10:
						ȫ����ɱ();
						break;
					case VK_END:
						break;
					}
					break;
				case MOD_ALT:
					switch (HIWORD(msg.lParam))
					{
					case VK_UP:
						�����ͼ(2);
						break;
					case VK_DOWN:
						�����ͼ(3);
						break;
					case VK_LEFT:
						�����ͼ(0);
						break;
					case VK_RIGHT:
						�����ͼ(1);
						break;
					}
					break;
				}
				break;
			}
		}
		Sleep(1000);
	}
	VMEND
}



void ����()
{
	VMBEGIN
	��ʼ������();
	ϵͳ����(L"����ɹ���");
	�Զ�();
	//�Զ�͸��();
	����ȫ������();
	//���();
	if (FindWindow(NULL, L"���³�����ʿ") == NULL)
		return;
	HANDLE hThread;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)��Ϣѭ��, NULL, 0, NULL);
	SetThreadPriority(hThread, THREAD_PRIORITY_IDLE);
	//MAIN();
	VMEND
}