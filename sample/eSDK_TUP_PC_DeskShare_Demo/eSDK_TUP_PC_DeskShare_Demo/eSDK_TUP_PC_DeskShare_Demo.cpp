
// eSDK_TUP_PC_DeskShare_Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "eSDK_TUP_PC_DeskShare_Demo.h"
#include "eSDK_TUP_PC_DeskShare_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeSDK_TUP_PC_DeskShare_DemoApp

BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_DeskShare_DemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CeSDK_TUP_PC_DeskShare_DemoApp construction

CeSDK_TUP_PC_DeskShare_DemoApp::CeSDK_TUP_PC_DeskShare_DemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CeSDK_TUP_PC_DeskShare_DemoApp object

CeSDK_TUP_PC_DeskShare_DemoApp theApp;


// CeSDK_TUP_PC_DeskShare_DemoApp initialization

BOOL CeSDK_TUP_PC_DeskShare_DemoApp::InitInstance()
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
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));\

	// GDI初始化设置
	/*GdiplusStartupInput startupInfo;
	ULONG_PTR gdiToken;
	GdiplusStartup(&gdiToken, &startupInfo, NULL);*/

	//初始化IM部分底层数据
	TUP_RESULT tIMRet = tup_im_init();
	if(TUP_SUCCESS != tIMRet)
	{
		AfxMessageBox(_T("tup_im_init Failed!"));
		return false;
	}

	CString strAppPath = CTools::getCurrentPath();
	strAppPath += _T("\\log");
	//设置call部分的日志级别，日志大小等参数
	tup_call_log_start(CALL_E_LOG_DEBUG, 10000, 10, CTools::UNICODE2UTF(strAppPath).c_str());
	//初始化call底层业务
	TUP_RESULT tCallRet = tup_call_init();
	if(TUP_SUCCESS != tCallRet)
	{		
		AfxMessageBox(_T("tup_call_init failed"));
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

	CeSDK_TUP_PC_DeskShare_DemoDlg dlg;
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

	//卸载Call部分底层数据
	tCallRet = tup_call_uninit();
	if(tCallRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_call_uninit failed."));
	}	
	//停止记录call部分的日志
	tup_call_log_stop();

	//卸载IM部分底层数据
	tIMRet = tup_im_uninit();
	if(tIMRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_uninit failed."));
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

