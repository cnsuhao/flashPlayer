
// flashplayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "flashplayer.h"
#include "flashplayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflashplayerDlg �Ի���




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


// CflashplayerDlg ��Ϣ�������

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
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
		AfxMessageBox(_T("û���ҵ� ")+flashPathName);
		exit(0);
	}

	
	
	m_flash.LoadMovie(0,flashPathName);
	m_flash.Play();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CflashplayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CflashplayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

