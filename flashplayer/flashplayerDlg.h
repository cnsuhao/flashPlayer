
// flashplayerDlg.h : ͷ�ļ�
//

#pragma once
#include "shockwaveflash1.h"


// CflashplayerDlg �Ի���
class CflashplayerDlg : public CDialogEx
{
// ����
public:
	CflashplayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FLASHPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 m_flash;
};
