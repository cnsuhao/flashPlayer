
// flashplayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CflashplayerApp:
// �йش����ʵ�֣������ flashplayer.cpp
//

class CflashplayerApp : public CWinApp
{
public:
	CflashplayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CflashplayerApp theApp;