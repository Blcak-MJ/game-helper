#pragma once
#include "stdafx.h"
#include "�ڴ��д.h"
#include "CALL.h"
#include "���.h"
#include "����.h"
#include "���ܽ���.h"
#include "�ж�.h"
#include "���ù���.h"
#include <stack>

struct Point
{
	int x, y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};

void ��ȡ����(int *p, int ͨ��);

void ��ȡ��ͼ();

int ���㷽��(Point cur, Point next);

int ��ȡ�߷�();

Point ������һ��������(int ����);

void �����ͼ(int ����);

void �����ͼ(int ����);

void ��ͼ();

DWORD �Զ���ͼ(LPVOID);

DWORD �Զ��һ�(LPVOID);

void �Զ�();

VOID MAIN();