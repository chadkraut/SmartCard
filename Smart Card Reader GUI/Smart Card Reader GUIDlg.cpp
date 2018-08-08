// Smart Card Reader GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Smart Card Reader GUI.h"
#include "Smart Card Reader GUIDlg.h"
#include "winscard.h"
#include "WinCrypt.h"
#include <windows.h>
#include <CryptDlg.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#pragma comment(lib, "winscard.lib")
#pragma comment(lib, "crypt32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_CERT_SIMPLE_NAME_STR 1000

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0500	// Change this to the appropriate value to target other versions of Windows.
#endif

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#pragma warning(disable:4996)



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CSmartCardReaderGUIDlg dialog

CSmartCardReaderGUIDlg::CSmartCardReaderGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SMARTCARDREADERGUI_DIALOG, pParent)
	, m_TextBoxVar(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmartCardReaderGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboControl);

}

BEGIN_MESSAGE_MAP(CSmartCardReaderGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSmartCardReaderGUIDlg::OnBnClickedButton1)

END_MESSAGE_MAP()

// CSmartCardReaderGUIDlg message handlers

BOOL CSmartCardReaderGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	SCARDCONTEXT    hSC;
	LONG            lReturn;
	// Establish the context.
	lReturn = SCardEstablishContext(SCARD_SCOPE_USER,
		NULL,
		NULL,
		&hSC);
	if (SCARD_S_SUCCESS != lReturn)
		printf("Failed SCardEstablishContext\n");
	else
	{
		LPTSTR          pmszReaders = NULL;
		LPTSTR          pReader;
		LONG            lReturn2;
		DWORD           cch = SCARD_AUTOALLOCATE;
		// Retrieve the list the readers.
		// hSC was set by a previous call to SCardEstablishContext.
		lReturn = SCardListReaders(hSC,
			NULL,
			(LPTSTR)&pmszReaders,
			&cch);
		switch (lReturn)
		{
		case SCARD_E_NO_READERS_AVAILABLE:
			m_ComboControl.AddString(L"No Card Reader Available!");
			return TRUE;
			break;
		case SCARD_S_SUCCESS:
			// Output the values.
			// A double-null terminates the list of values.
			pReader = pmszReaders;
			while ('\0' != *pReader)
			{
				// Display the value.
				m_ComboControl.AddString(pReader);
				// Advance to the next value.
				pReader = pReader + wcslen((wchar_t *)pReader) + 1;
			}
			// Free the memory.
			lReturn2 = SCardFreeMemory(hSC,
				pmszReaders);
			if (SCARD_S_SUCCESS != lReturn2)
				printf("Failed SCardFreeMemory\n");
			return TRUE;
			break;
		}
		return TRUE;  // return TRUE  unless you set the focus to a control
	}
	return TRUE;
}

void CSmartCardReaderGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmartCardReaderGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmartCardReaderGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSmartCardReaderGUIDlg::OnBnClickedButton1()
{
	int index = m_ComboControl.GetCurSel();
	CString data;
	if (index != LB_ERR)
	{
		m_ComboControl.GetLBText(index,data);
	}

	// Display certificates on the first available smart card
	dwErr = ShowCertsDlg(_T("Microsoft Base Smart Card Crypto Provider"), data);
	//printf("ShowCertsDlg returned 0x%.8X\n", dwErr);
}

DWORD CallDlgFunction(HCRYPTPROV hProv, PCCERT_CONTEXT* pContexts, DWORD dwContextsCount)
{
	DWORD dwErr = 0;
	HCERTSTORE hStore = NULL;
	CERT_SELECT_STRUCT certSel;
	HMODULE hDll = NULL;
	typedef BOOL(WINAPI* pCertSelectCertificateFnType) (PCERT_SELECT_STRUCT);
	pCertSelectCertificateFnType pCertSelectCertificateFn = NULL;

	SecureZeroMemory(&certSel, sizeof(CERT_SELECT_STRUCT));

	//create a certificate store in memory
	hStore = CertOpenStore(CERT_STORE_PROV_MEMORY,
		PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,
		NULL,
		0,
		NULL);

	if (!hStore)
	{
		dwErr = GetLastError();
		printf("CertOpenStore failed with error 0x%.8X\n", dwErr);
		return dwErr;
	}

	//add the certificate contexts to this store
	for (DWORD i = 0; i < dwContextsCount; i++)
	{
		if (!CertAddCertificateContextToStore(hStore,
			pContexts[i],
			CERT_STORE_ADD_USE_EXISTING,
			NULL))
		{
			dwErr = GetLastError();
			printf("CertAddCertificateContextToStore failed with error 0x%.8X\n", dwErr);
			goto finish;
		}
	}

	certSel.dwSize = sizeof(certSel);
	certSel.szTitle = _T("All smart card certificates");
	certSel.cCertStore = 1;
	certSel.arrayCertStore = &hStore;
	certSel.cCertContext = dwContextsCount;
	certSel.arrayCertContext = pContexts;
	certSel.hprov = hProv;
	certSel.szHelpFileName = _T("");

	hDll = ::LoadLibrary(_T("cryptdlg.dll"));
	if (hDll)
	{
#ifdef _UNICODE
		pCertSelectCertificateFn = (pCertSelectCertificateFnType)GetProcAddress(hDll, "CertSelectCertificateW");
#else
		pCertSelectCertificateFn = (pCertSelectCertificateFnType)GetProcAddress(hDll, "CertSelectCertificateA");
#endif
		if (pCertSelectCertificateFn)
		{
			BOOL bResult = pCertSelectCertificateFn(&certSel); // this throws a pop-up but no certificates displayed at all.
			if (!bResult)
			{
				dwErr = GetLastError();
				printf("CertSelectCertificate failed with error 0x%.8X\n", dwErr);
			}
			else
			{
				printf("A certificate has been selected\n");
			}

		}
		::FreeLibrary(hDll);
	}
finish:
	CertCloseStore(hStore, 0);
	return dwErr;
}

DWORD ShowCertsDlg(LPCTSTR szProviderName,
	LPCTSTR szReaderName /* Can be NULL */
)
{
	HCRYPTPROV HMainCryptProv = NULL;
	BOOL bStatus = FALSE;
	LPTSTR szMainContainerName = NULL;
	CHAR szContainerName[1024];
	DWORD dwContainerNameLen = sizeof(szContainerName);
	DWORD dwErr = 0;
	DWORD dwFlags = CRYPT_FIRST;
	PCCERT_CONTEXT pContextArray[128];
	DWORD dwContextArrayLen = 0;
	HCRYPTPROV hProv = NULL;
	//KEY IS HARD CODED RIGHT NOW!!!!!!!!!!!!!
	HCRYPTKEY hKey = 77777777;
	LPBYTE pbCert = NULL;
	DWORD dwCertLen = 0;
	PCCERT_CONTEXT pCertContext = NULL;
	DWORD pKeySpecs[2] = { AT_KEYEXCHANGE, AT_SIGNATURE };

	if (szReaderName)
	{
		size_t ulNameLen = _tcslen(szReaderName);
		szMainContainerName = (LPTSTR)LocalAlloc(0, (ulNameLen + 6) * sizeof(TCHAR));
		if (!szMainContainerName)
		{
			return GetLastError();
		}
		_stprintf(szMainContainerName, _T("\\\\.\\%s\\"), szReaderName);
	}
	//EDIT RSA Prov
	bStatus = CryptAcquireContext(&HMainCryptProv,
		szMainContainerName,
		szProviderName,
		PROV_RSA_FULL,
		0);
	if (!bStatus)
	{
		dwErr = GetLastError();
		goto end;
	}

	/* Enumerate all the containers */
	while (CryptGetProvParam(HMainCryptProv,
		PP_ENUMCONTAINERS,
		(LPBYTE)szContainerName,
		&dwContainerNameLen,
		dwFlags) &&
		(dwContextArrayLen < 128)
		)
	{
#ifndef _UNICODE
		if (CryptAcquireContext(&hProv,
			szContainerName,
			szProviderName,
			PROV_RSA_FULL,
			0))
#else
		// convert the container name to unicode
		int wLen = MultiByteToWideChar(CP_ACP, 0, szContainerName, -1, NULL, 0);
		LPWSTR szWideContainerName = (LPWSTR)LocalAlloc(0, wLen * sizeof(WCHAR));
		MultiByteToWideChar(CP_ACP, 0, szContainerName, -1, szWideContainerName, wLen);

		// Acquire a context on the current container
		if (CryptAcquireContext(&hProv,
			szWideContainerName,
			szProviderName,
			PROV_RSA_FULL,
			0))
#endif
		{
			// Loop over all the key specs
			for (int i = 0; i < 2; i++)
			{
				if (CryptGetUserKey(hProv,
					pKeySpecs[i],
					&hKey))
				{
					if (CryptGetKeyParam(hKey,
						KP_CERTIFICATE,
						NULL,
						&dwCertLen,
						0))
					{
						pbCert = (LPBYTE)LocalAlloc(0, dwCertLen);
						if (!pbCert)
						{
							dwErr = GetLastError();
							goto end;
						}
						if (CryptGetKeyParam(hKey,
							KP_CERTIFICATE,
							pbCert,
							&dwCertLen,
							0))
						{
							pCertContext = CertCreateCertificateContext(
								X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
								pbCert,
								dwCertLen);
							if (pCertContext)
							{
								pContextArray[dwContextArrayLen++] = pCertContext;
							}
						}
						LocalFree(pbCert);
					}
					CryptDestroyKey(hKey);
					hKey = NULL;
				}
			}
			CryptReleaseContext(hProv, 0);
			hProv = NULL;
		}

#ifdef _UNICODE
		LocalFree(szWideContainerName);
#endif

		// prepare parameters for the next loop
		dwContainerNameLen = sizeof(szContainerName);
		dwFlags = 0;
	}

	if (dwContextArrayLen == 0)
		printf("No certificate contexts found on card\n");
	else
	{
		//show the dialog
		dwErr = CallDlgFunction(HMainCryptProv, pContextArray, dwContextArrayLen);
	}

end:
	while (dwContextArrayLen--)
	{
		CertFreeCertificateContext(pContextArray[dwContextArrayLen]);
	}
	if (hKey)
		CryptDestroyKey(hKey);
	if (hProv)
		CryptReleaseContext(hProv, 0);
	if (szMainContainerName)
		LocalFree(szMainContainerName);
	if (HMainCryptProv)
		CryptReleaseContext(HMainCryptProv, 0);
	return dwErr;
}
