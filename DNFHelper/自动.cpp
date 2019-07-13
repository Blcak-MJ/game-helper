#include "stdafx.h"
#include "�Զ�.h"
#include "�ٻ���ż����.h"
#include "ȫ��.h"
#include "�ж�.h"
#include "΢��buff.h"

int ��ͼ[100][100][4];
bool ��ͼ��ʼ�� = false;
int �߷�[100][100] = { -1 };
extern int ����Ƶ��;
extern int �����˺�;
extern int ���ܸ���;
extern int ���ܴ���;
extern int ���ܴ��뼯��[100];
extern int ���ܴ������;

int ���򼯺�[16][4] =
{
	{ 0, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 1, 0, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 0, 1, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 1 },
	{ 0, 1, 0, 1 },
	{ 0, 0, 1, 1 },
	{ 0, 1, 1, 1 },
	{ 1, 0, 0, 1 },
	{ 1, 1, 0, 1 },
	{ 1, 0, 1, 1 },
	{ 1, 1, 1, 1 }
};

void ��ȡ����(int *p, int ͨ��)
{
	if (ͨ�� < 0 || ͨ��>15)
	{
		p[0] = p[1] = p[2] = p[3] = 0;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		p[i] = ���򼯺�[ͨ��][i];
	}
}

void ��ȡ��ͼ()
{
	int ��ͼ��� = ����(ȡƫ�Ƶ�ַ(������, { ʱ���ַ,A��ƫ��_0,0 }) + (BOSS����X - 24)) + 1;
	int ��ͼ��� = read(ȡƫ�Ƶ�ַ(������, { ʱ���ַ,A��ƫ��_0,A��ƫ��_1,0 }) + ��ͼ��� * 8 - 8);
	int ��ͼ�߶� = read(ȡƫ�Ƶ�ַ(������, { ʱ���ַ,A��ƫ��_0,A��ƫ��_1,0 }) + ��ͼ��� * 8 - 4);
	int ��ʱ��ַ = read(ȡƫ�Ƶ�ַ(������, { ʱ���ַ,A��ƫ��_0,A��ƫ��_2,0 }) + ��ͼ��� * 20 - 16);
	int ���� = ��ͼ��� * ��ͼ�߶�;
	int ͨ��, x, y;
	memset(��ͼ, 0, sizeof(��ͼ));
	for (int i = 0; i < ����; i++)
	{
		ͨ�� = read(��ʱ��ַ + 4 * i);
		x = i % ��ͼ���;
		y = i / ��ͼ���;
		for (int j = 0; j < 4; j++)
		{
			��ͼ[x][y][j] = ���򼯺�[ͨ��][j];
		}
	}
}

int ���㷽��(Point cur, Point next)
{
	int x = cur.x - next.x;
	int y = cur.y - next.y;
	if (x == 0)
	{
		if (y == 1)
			return 2; //��
		else if(y == -1)
			return 3; // ��
	}
	if (y == 0)
	{
		if (x == 1)
			return 0;//��
		else if (x == -1)
			return 1;//��
	}
	return -1;
}

int ��ȡ�߷�()
{
	��ȡ��ͼ();
	int curx = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����X);
	int cury = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����Y);
	int bossx = ����(read(read(read(������) + ʱ���ַ) + 204) + BOSS����X);
	int bossy = ����(read(read(read(������) + ʱ���ַ) + 204) + BOSS����Y);
	int Vis[100][100];
	memset(Vis, 0, sizeof(Vis));
	memset(�߷�, -1, sizeof(�߷�));
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	std::stack<Point> sta;
	sta.push(Point{ curx,cury });
	Vis[curx][cury] = 1;
	int step = 1;
	while (!sta.empty())
	{
		Point point = sta.top();
		int i;
		int x = point.x;
		int y = point.y;
		for (i = 0; i < 4; i++)
		{
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if (nx >= 0 && ny >= 0 && ��ͼ[x][y][i] == 1 && Vis[nx][ny] == 0)
			{
				Vis[nx][ny] = 1;
				sta.push(Point{ nx,ny });
				�߷�[x][y] = i;
				step++;
				if (nx == bossx && ny == bossy)
					return step;
				break;
			}
		}
		if (i == 4)
		{
			step--;
			sta.pop();
		}
	}
	return 0;
}

Point ������һ��������(int ����)
{
	int X = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����X);
	int Y = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����Y);
	switch (����)
	{
	case 2:
		Y++;
		break;
	case 3:
		Y--;
		break;
	case 0:
		X--;
		break;
	case 1:
		X++;
	}
	return Point(X, Y);
}

void �����ͼ(int ����)
{
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	int tmp = read(������);
	tmp = read(tmp + ʱ���ַ);
	tmp = read(tmp + ����ṹƫ��01);
	int ����ṹ = tmp + (���� + ���� * 8) * 4 + ����ṹƫ��02;
	����ṹ = ����ṹ + 4 * ����;
	int x = read(����ṹ);
	int y = read(����ṹ + 4);
	int xf = read(����ṹ + 8);
	int yf = read(����ṹ + 12);
	int cx, cy;
	switch (����)
	{
	case 0:
		cx = x + xf + 20;
		cy = y + yf / 2;
		break;
	case 1:
		cx = x - 20;
		cy = y + yf / 2;
		break;
	case 2:
		cx = x + xf / 2;
		cy = y + yf + 20;
		break;
	case 3:
		cx = x + xf / 2;
		cy = y - 20;
		break;
	default:
		break;
	}
	����call(һ��ƫ��, cx, cy, 0);
	������ʱ(200);
	����call(һ��ƫ��, x + xf / 2, y, 0);
}

void �����ͼ(int ����)
{

	int X = ȡƫ�Ƶ�ַ(�̵��ַ - 8, { ʱ���ַ, A��ƫ��_3, 0 });
	int Y = ȡƫ�Ƶ�ַ(�̵��ַ - 8, { ʱ���ַ, A��ƫ��_4, 0 });
	����(L"X��%d  Y:%d ", X, Y);
	Sleep(1000);
	switch(����)
	{
	case 2:
		Y--;
		break;
	case 3:
		Y++;
		break;
	case 0:
		X--;
		break;
	case 1:
		X++;
		break;
	}
	�����ͼ(X, Y);
}

void ��ͼ()
{
	// 0����  1����  2����  3����
	int curx = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����X);
	int cury = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����Y);
	if (�߷�[curx][cury] >= 0)
	{
		�����ͼ(�߷�[curx][cury]);
	}
	else
		��ȡ�߷�();
	if (�Ƿ���() == true)
		��ȡ�߷�();
}

DWORD �Զ���ͼ(LPVOID)
{
	VMBEGIN
	int ���ܼ�[12] = { 'A','S','D','F','G','H','Q','W','E','R','T','Y' };
	int flag = 0;
	int cnt = 0;
	int time = 0;
	int ��ǰ��ɫ = 0;
	while(true)
	{
		�����¼�();
		if (read(�����ַ) <= 0)
		{
			Sleep(5000);
			if (read(�����ַ) > 0)
				continue;
			ѡ��ɫ(��ǰ��ɫ, 1);
			continue;
		}
		if (�Ƿ��ڳ���() == false)
		{
			flag = 999999;
			if (��ͼ��ʼ�� == false && �Ƿ���BOSS��() == false)
			{
				��ͼ��ʼ�� = true;
				��ȡ�߷�();
			}
			if (�Ƿ���BOSS��() == true)
			{
				�������();
				��ͼ��ʼ�� = false;
				ʰȡ();
				for (int i = 0; i < 5; i++)
				{
					if (�Ƿ�����Ʒ() == true)
					{
						ʰȡ();
						����();
						����('X');
						Sleep(500);
					}
					else break;
				}
				int �� = ���ܼ�[cnt % 12];
				����(��);
				����(VK_ESCAPE);
				time = 0;
			}
			else if (�Ƿ���() == true)
			{
				ʰȡ();
				Sleep(300);
				ʰȡ();
				��ͼ();
			}
			else
			{
				�������();
				if (time > 35 && time % 5 == 0)
					��ͼ();
				int �� = ���ܼ�[cnt% 12];
				����(��);
			}
			����(VK_SPACE, 666);
			cnt++;
			time++;
			if (cnt % 100 == 0)
			{
				cnt = cnt * cnt % 4567;
			}
		}
		else
		{
			time = 0;
			��ͼ��ʼ�� = false;
			if (ʣ��ƣ��() == 0)
			{
				Sleep(1000);
				ϵͳ����(L"��ǰ��ɫƣ���Ѿ�����");
				��ǰ��ɫ++;
				Sleep(4000);
				�����¼�();
				ѡ��ɫ(0, 0);
				�����¼�();
				Sleep(3000);
				ѡ��ɫ(��ǰ��ɫ, 1);
				flag = 0;
				continue;
			}
			if (flag == 999999 + 5)
			{
				װ������();
				ϵͳ����(L"װ���Ѿ�����");
				for (int i = 0; i < 5; i++)
				{
					MessageBeep(MB_ICONHAND);
					Sleep(500);
				}
				MessageBox(NULL, L"����", L"����", MB_OK);
			}
			flag++;
			Sleep(1000);
		}

	}
	return 0;
	VMEND
}

DWORD �Զ��һ�(LPVOID)
{
	int cnt = 0;
	while(true)
	{
		�����¼�();
		if (read(�����ַ) <= 0)
		{
			Sleep(1000);
			continue;
		}
		cnt++;
		if (�Ƿ��ڳ���() == false)
		{
			����(VK_SPACE);
			����(VK_SPACE);
			if (�Ƿ���BOSS��() == true)
			{
				����(VK_ESCAPE);
				����(VK_ESCAPE);
				����(VK_SPACE);
				����(VK_SPACE);
			}
			else
			{
				int curx = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����X);
				int cury = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����Y);
				int ���� = -1;
				switch (�߷�[curx][cury])
				{
				case 0:���� = VK_LEFT; break;
				case 1:���� = VK_RIGHT; break;
				case 2:���� = VK_UP; break;
				case 3:���� = VK_DOWN; break;
				}
				����(����, 800);
			}
		}
		if (cnt % 100 == 0)
		{
			cnt = cnt * cnt * cnt % 1234;
		}
	}
	return 0;
}

bool �Զ����� = false;
HANDLE �Զ��߳� = NULL;
HANDLE �һ��߳� = NULL;
void �Զ�()
{
	VMBEGIN
	if (�Զ����� == false)
	{
		�Զ����� = true;
		��ͼ��ʼ�� = false;
		ϵͳ����(L"�Զ�ˢͼ����");
		�Զ��߳� = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)�Զ���ͼ, NULL, 0, NULL);
		�һ��߳� = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)�Զ��һ�, NULL, 0, NULL);
		SetThreadPriority(�Զ��߳�, THREAD_PRIORITY_IDLE);
		SetThreadPriority(�һ��߳�, THREAD_PRIORITY_IDLE);
	}
	else
	{
		�Զ����� = false;
		ϵͳ����(L"�Զ�ˢͼ�ر�");
		TerminateThread(�Զ��߳�,0);
		TerminateThread(�һ��߳�,0);
		memset(�߷�, -1, sizeof(�߷�));
	}
	VMEND
}


DWORD AllThread(LPVOID)
{
	int ���ܼ�[12] = { 'A','S','D','F','G','H','Q','W','E','R','T','Y' };
	int flag = 0;
	int cnt = 0;
	bool ��Ч = false;
	bool ͸������ = false;
	bool ��ż = false;
	int ��;
	int time = 0;
	while (true)
	{
		if (read(�����ַ) <= 0)
		{
			Sleep(1000);
			��Ч = false;
			continue;
		}
		if (�Ƿ��ڳ���() == false)
		{
			Sleep(8000);
			break;
		}
		else if(��Ч == false)
		{
			��Ч = true;
			��ЧBuff();
		}
		Sleep(500);
	}
	while(true)
	{
		if (read(�����ַ) <= 0)
		{
			Sleep(1000);
			��Ч = false;
			continue;
		}
		if (�Ƿ��ڳ���() == false)
		{
			flag = 999999;
			time++;
			if (time == 30 && ��ż == false)
			{
				if (�Ƿ���BOSS��() == true)
					continue;
				��ż = true;
				��żcall();
				Sleep(1000);
			}
			if (time > 30 && time % 5 == 0)
				��ͼ();
			if (��ͼ��ʼ�� == false)
			{
				��ͼ��ʼ�� = true;
				͸������ = false;
				��ȡ�߷�();
				Sleep(1000);
			}
			if (�Ƿ���BOSS��() == true)
			{
				��ͼ��ʼ�� = false;
				time = 0;
				��ż = false;
				͸������ = false;
				ʰȡ();
				����();
				����(VK_ESCAPE);
			}
			else if (�Ƿ���() == true)
			{
				if (͸������ == false)
				{
					if (�Ƿ���BOSS��() == false)
					{
						͸��();
						͸������ = true;
						Sleep(500);
						����();
						Sleep(500);
					}
				}
				ʰȡ();
				����();
				ʰȡ();
				Sleep(300);
				ʰȡ();
				��ͼ();
				Sleep(1000);
			}
			ʰȡ();
			ʰȡ();
			�� = ���ܼ�[(cnt*cnt) % 12];
			����(��);
			����(VK_SPACE);
			����(VK_SPACE);
			if (cnt % 100 == 0)
			{
				cnt = cnt * cnt % 4567;
			}

		}
		else if (��Ч == false)
		{
			��Ч = true;
			��ЧBuff();
		}
		else
		{
			��ͼ��ʼ�� = false;
			͸������ = false;
			time = 0;
			��ż = false;
			if (cnt % 100 == 0)
			{
				cnt = cnt * cnt * cnt % 1234;
			}
			if (flag == 999999 + 1)
			{
				for (int i = 0; i < 5; i++)
				{
					MessageBeep(MB_ICONHAND);
					Sleep(500);
				}
				MessageBox(NULL, L"����", L"����", MB_OK);
			}
			flag++;
			Sleep(3000);
		}
		cnt++;
	}
	return 0;
}

HANDLE ���߳� = NULL;
BOOL ���߳̿��� = FALSE;
VOID MAIN()
{
	if (���߳̿��� == FALSE)
	{
		���߳̿��� = TRUE;
		ϵͳ����(L"�Զ�����");
		����ȫ������();
		���߳� = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AllThread, NULL, 0, NULL);
		SetThreadPriority(���߳�, THREAD_PRIORITY_IDLE);
		//�һ��߳� = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)�Զ��һ�, NULL, 0, NULL);
		//SetThreadPriority(�һ��߳�, THREAD_PRIORITY_IDLE);
	}
	else
	{
		ϵͳ����(L"�ر��Զ�");
		���߳̿��� = TRUE;
		TerminateThread(���߳�, 0);
		TerminateThread(�һ��߳�, 0);
	}
}