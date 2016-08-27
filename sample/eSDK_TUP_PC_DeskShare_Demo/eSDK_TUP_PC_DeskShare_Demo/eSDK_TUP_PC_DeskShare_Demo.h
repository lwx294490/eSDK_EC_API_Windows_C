
// eSDK_TUP_PC_DeskShare_Demo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CeSDK_TUP_PC_DeskShare_DemoApp:
// See eSDK_TUP_PC_DeskShare_Demo.cpp for the implementation of this class
//

class CeSDK_TUP_PC_DeskShare_DemoApp : public CWinApp
{
public:
	CeSDK_TUP_PC_DeskShare_DemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CeSDK_TUP_PC_DeskShare_DemoApp theApp;