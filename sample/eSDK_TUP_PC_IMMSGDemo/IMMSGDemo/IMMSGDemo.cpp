/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/


// IMMSGDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IMMSGDemo.h"
#include "IMMSGDemoDlg.h"
#include "offlinefile_def.h"
#include "offlinefile_interface.h"
#include <initguid.h>
#include "IMMSGDemo_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMMSGDemoApp


class CIMMSGDemoModule :
	public ATL::CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_IMMSGDemoLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_IMMSGDEMO, "{CA992A2F-4E87-49F0-94A7-618347786A70}");};

CIMMSGDemoModule _AtlModule;

BEGIN_MESSAGE_MAP(CIMMSGDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CIMMSGDemoApp construction

CIMMSGDemoApp::CIMMSGDemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIMMSGDemoApp object

CIMMSGDemoApp	theApp;

// CIMMSGDemoApp initialization

BOOL CIMMSGDemoApp::InitInstance()
{
	AfxOleInit();
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxInitRichEdit2();

	AfxEnableControlContainer();
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// Register class factories via CoRegisterClassObject().
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Don't show the main window
		return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// App was launched with /Register or /Regserver switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		return FALSE;
	}

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// 装载GDI+
	GdiplusStartupInput	m_gdiplusStartupInput;
	//ULONG_PTR			m_pGdiToken;
	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

	// 初始化IM部分底层数据
	TUP_RESULT tIMRet = tup_im_init();
	if (TUP_SUCCESS != tIMRet)
	{
		return FALSE;
	}

	// 初始化离线文件组件
	char logPath[100] = "..\\output\\release\\log";
	char *pcLog = logPath;
	OFFLINE_INITCONFIG stInitConfig;
	memset(&stInitConfig, 0, sizeof(OFFLINE_INITCONFIG));
	stInitConfig.stLogConfig.enLevel = OFFLINE_LOG_DEBUG;
	stInitConfig.stLogConfig.uiLogFileSize = 15;
	stInitConfig.stLogConfig.pcFilePath = pcLog;
	stInitConfig.uiHandleNum = 100;
	stInitConfig.bUseSvn = TUP_FALSE;
	tIMRet = tup_offlinefile_init(&stInitConfig);
	if (TUP_SUCCESS != tIMRet)
	{
		AfxMessageBox(_T("tup_offlinefile_init failed!"));
		return FALSE;
	}
	
	CIMMSGDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	//dlg.InitUIAndEmotionConfig();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// 释放IM部分底层数据
	tIMRet = tup_im_uninit();
	if (TUP_FAIL == tIMRet)
	{
		AfxMessageBox(_T("tup_im_uninit failed."));
	}

	// 去初始化离线文件
// 	tIMRet = tup_offlinefile_uninitlogout();
// 	if (TUP_SUCCESS != tIMRet)
// 	{
// 		AfxMessageBox(_T("tup_offlinefile_uninitlogout failed!"));
// 	}

	tIMRet = tup_offlinefile_logout();
	if (TUP_SUCCESS != tIMRet)
	{
		AfxMessageBox(_T("tup_offlinefile_logout failed!"));
	}
	
	tIMRet = tup_offlinefile_uninit();
	if (TUP_FAIL == tIMRet)
	{
		AfxMessageBox(_T("tup_offlinefile_uninit failed."));
	}
	// 卸载GDI+
	GdiplusShutdown(m_pGdiToken);

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



BOOL CIMMSGDemoApp::ExitInstance(void)
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	GdiplusShutdown(m_pGdiToken);
	return CWinApp::ExitInstance();
}
