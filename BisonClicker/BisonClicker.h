
// Bison���������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBisonClickerApp: 
// �йش����ʵ�֣������ Bison���������.cpp
//

class CBisonClickerApp : public CWinApp
{
public:
	CBisonClickerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBisonClickerApp theApp;