
// Smart Card Reader GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CSmartCardReaderGUIApp:
// See Smart Card Reader GUI.cpp for the implementation of this class
//

class CSmartCardReaderGUIApp : public CWinApp
{
public:
	CSmartCardReaderGUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSmartCardReaderGUIApp theApp;