
// flashplayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "flashplayer.h"
#include "flashplayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflashplayerDlg 对话框




CflashplayerDlg::CflashplayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CflashplayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CflashplayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_flash);
}

BEGIN_MESSAGE_MAP(CflashplayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CflashplayerDlg 消息处理程序

void SetAlpha(CWnd *pWnd,int r,int g, int b)
{
	COLORREF alphaClr = RGB(r,g,b);
#define LWA_COLORKEY   0x00000001
#define LWA_ALPHA      0x00000002
#define WS_EX_LAYERED  0x00080000

	typedef BOOL (WINAPI *LPFNSETLAYEREDWINDOWATTRIBUTES)(HWND hWnd,COLORREF crKey,BYTE bAlpha,DWORD dwFlags);
	LPFNSETLAYEREDWINDOWATTRIBUTES SetLayeredWindowAttributes;
	HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
	SetLayeredWindowAttributes = (LPFNSETLAYEREDWINDOWATTRIBUTES)GetProcAddress(hUser32,"SetLayeredWindowAttributes");
	SetWindowLong(pWnd->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(pWnd->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(pWnd->GetSafeHwnd(),alphaClr,0,LWA_COLORKEY);
}
CString GetCurPath()
{
	CString path;
	GetModuleFileName(NULL, path.GetBuffer(MAX_PATH), MAX_PATH);   
	path.ReleaseBuffer();

	path = path.Left(path.ReverseFind(_T('\\')));
	return path;
}
BOOL CflashplayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	CString path = GetCurPath();
	int r = GetPrivateProfileInt(_T("cfg"),_T("r"),0,path + _T("\\cfg.ini"));
	int g = GetPrivateProfileInt(_T("cfg"),_T("g"),0,path + _T("\\cfg.ini"));
	int b = GetPrivateProfileInt(_T("cfg"),_T("b"),0,path + _T("\\cfg.ini"));

	ShowWindow(SW_SHOWMAXIMIZED);
	int cx=GetSystemMetrics(SM_CXSCREEN); 
	int cy=GetSystemMetrics(SM_CYSCREEN); 
	m_flash.SetWindowPos(NULL,0,0,cx,cy,0);
	SetAlpha(this,r,g,b);

	

	if(1 == ::GetPrivateProfileInt(_T("cfg"),_T("top"),0,path + _T("\\cfg.ini")))
	{
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE); 
	}

	CString flashName;
	::GetPrivateProfileString(_T("cfg"),_T("swf"),_T("skin"),flashName.GetBuffer(1024),1024,path + _T("\\cfg.ini"));
	flashName.ReleaseBuffer();
	CString flashPathName = path + _T("\\") + flashName + _T(".swf");
	if (!PathFileExists(flashPathName))
	{
		AfxMessageBox(_T("没有找到 ")+flashPathName);
		exit(0);
	}

	
	
	m_flash.LoadMovie(0,flashPathName);
	m_flash.Play();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CflashplayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CflashplayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

