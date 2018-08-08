// Smart Card Reader GUIDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <windows.h>
#include "wincrypt.h"
#include <stdio.h>
#include <string.h>
#include <tchar.h>


#define _CRT_SECURE_NO_WARNINGS
// CSmartCardReaderGUIDlg dialog
class CSmartCardReaderGUIDlg : public CDialogEx
{
// Construction
public:
	CSmartCardReaderGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMARTCARDREADERGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_ComboControl;
	CString m_TextBoxVar;
	DWORD dwErr;
};

DWORD ShowCertsDlg(
	LPCTSTR szProviderName,
	LPCTSTR szReaderName /* Can be NULL */);

DWORD CallDlgFunction(
	HCRYPTPROV hProv,
	PCCERT_CONTEXT* pContexts,
	DWORD dwContextsCount);