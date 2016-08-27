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


// eSDK_TUP_PC_VIDEO_Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "eSDK_TUP_PC_VIDEO_DemoDlg.h"
#include "Tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeSDK_TUP_PC_VIDEO_DemoApp

BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_VIDEO_DemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CeSDK_TUP_PC_VIDEO_DemoApp construction

CeSDK_TUP_PC_VIDEO_DemoApp::CeSDK_TUP_PC_VIDEO_DemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CeSDK_TUP_PC_VIDEO_DemoApp object

CeSDK_TUP_PC_VIDEO_DemoApp theApp;


// CeSDK_TUP_PC_VIDEO_DemoApp initialization

BOOL CeSDK_TUP_PC_VIDEO_DemoApp::InitInstance()
{
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


	AfxEnableControlContainer();

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
	// GDI初始化设置
	GdiplusStartupInput startupInfo;
	ULONG_PTR gdiToken;
	GdiplusStartup(&gdiToken, &startupInfo, NULL);

	// IM组件初始化
	TUP_RESULT tRet = tup_im_init();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_init failed!"));
		return FALSE;
	}

	// CALL组件初始化
	CString strAppPath = CTools::getCurrentPath();
	strAppPath += _T("\\log");
	tup_call_log_start(CALL_E_LOG_DEBUG, 10000, 10, CTools::UNICODE2UTF(strAppPath).c_str());
	tRet = tup_call_init();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_init failed!"));
		return FALSE;
	}

	// 会议组件初始化
	std::string strLog = CTools::UNICODE2UTF(strAppPath);// 会议日志路径
	// 初始化会议参数
	Init_param sInitParam;
	sInitParam.os_type = CONF_OS_WIN;
	sInitParam.dev_type = CONF_DEV_PC;
	sInitParam.media_log_level = 2;
	sInitParam.sdk_log_level = 2;
	strncpy_s(sInitParam.log_path, sizeof(sInitParam.log_path), strLog.c_str(), TC_MAX_PATH - 1);
	strncpy_s(sInitParam.temp_path, sizeof(sInitParam.temp_path), strLog.c_str(), TC_MAX_PATH - 1);
	tup_conf_init((TUP_BOOL)false, &sInitParam);

	CeSDK_TUP_PC_VIDEO_DemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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

	//卸载gdi+
	GdiplusShutdown(gdiToken);
	tup_conf_uninit();
	tRet = tup_call_uninit();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_uninit failed!"));
		return FALSE;
	}

	tup_call_log_stop();

	// IM组件反初始化
	tRet = tup_im_uninit();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_uninit failed!"));
		return FALSE;
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}