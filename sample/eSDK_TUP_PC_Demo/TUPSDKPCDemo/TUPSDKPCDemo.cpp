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


// TUPSDKPCDemo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "LoginDlg.h"
#include "MainDlg.h"
#include "Tools.h"
#include <initguid.h>
#include "TUPSDKPCDemo_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTUPSDKPCDemoApp


class CTUPSDKPCDemoModule :
	public CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_TUPSDKPCDemoLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TUPSDKPCDEMO, "{F0BFAD01-521D-488F-9DD2-57BC6AA6D528}");};

CTUPSDKPCDemoModule _AtlModule;

BEGIN_MESSAGE_MAP(CTUPSDKPCDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTUPSDKPCDemoApp 构造

CTUPSDKPCDemoApp::CTUPSDKPCDemoApp():m_pMainDlgWnd(NULL),m_pLoginDlgWnd(NULL)
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CTUPSDKPCDemoApp 对象

CTUPSDKPCDemoApp theApp;


// CTUPSDKPCDemoApp 初始化

BOOL CTUPSDKPCDemoApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	AfxOleInit();
	/////只运行一个实例
// 	HANDLE m_hMutex=CreateMutex(NULL,TRUE,m_pszAppName);
// 	if(GetLastError() == ERROR_ALREADY_EXISTS)
// 	{
// 		AfxMessageBox(L"该程序已经运行");
// 		ExitProcess(0);
// 	} 
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxInitRichEdit2();

	AfxEnableControlContainer();
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// 通过 CoRegisterClassObject() 注册类工厂。
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// 应用程序是用 /Embedding 或 /Automation 开关启动的。
	// 将应用程序作为自动化服务器运行。
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// 不显示主窗口
		return TRUE;
	}
	// 应用程序是用 /Unregserver 或 /Unregister 开关启动的。
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// 应用程序是用 /Register 或 /Regserver 开关启动的。
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		return FALSE;
	}

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//gdi+用到的两个变量   装载gdi+
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	////初始化IM模块
	TUP_RESULT tRet = tup_im_init();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_init failed!"));
		return FALSE;
	}

	// 初始化离线文件组件
	CString strAppPath = CTools::getCurrentPath();
	strAppPath += _T("\\log");
	OFFLINE_INITCONFIG stInitConfig;
	memset(&stInitConfig, 0, sizeof(OFFLINE_INITCONFIG));
	stInitConfig.stLogConfig.enLevel = OFFLINE_LOG_INFO;
	stInitConfig.stLogConfig.uiLogFileSize = 15;
	stInitConfig.stLogConfig.pcFilePath = (TUP_CHAR*)malloc(TC_MAX_PATH);
	memset(stInitConfig.stLogConfig.pcFilePath,0,TC_MAX_PATH);
	strncpy_s(stInitConfig.stLogConfig.pcFilePath,TC_MAX_PATH,CTools::UNICODE2UTF(strAppPath).c_str(),_TRUNCATE);
	stInitConfig.uiHandleNum = 100;
	stInitConfig.bUseSvn = TUP_FALSE;
	tRet = tup_offlinefile_init(&stInitConfig);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_offlinefile_init failed!"));
		return FALSE;
	}

	//Modified by w00321336 to fix image missing issue at 2015-1-21 begin
	tup_call_log_start(CALL_E_LOG_DEBUG,10000,10, CTools::UNICODE2UTF(strAppPath).c_str());
	tRet = tup_call_init();
	if(TUP_SUCCESS != tRet)
	{		
		return FALSE;
	}

	//数据会议
	//会议日志路径
	string strLog = CTools::UNICODE2UTF(strAppPath);
	//初始化会议参数
	Init_param sInitParam; 
	sInitParam.os_type = CONF_OS_WIN;
	sInitParam.dev_type = CONF_DEV_PC;
	sInitParam.media_log_level = 2;
	sInitParam.sdk_log_level = 2;
	(VOID)strncpy_s(sInitParam.log_path, sizeof(sInitParam.log_path), strLog.c_str(), TC_MAX_PATH-1);
	(VOID)strncpy_s(sInitParam.temp_path, sizeof(sInitParam.temp_path), strLog.c_str(), TC_MAX_PATH-1);
	tup_conf_init((TUP_BOOL)false, &sInitParam);

	/////释放参数////
	SAFE_DELETE_ARRAY(stInitConfig.stLogConfig.pcFilePath);
	stInitConfig.stLogConfig.pcFilePath = NULL;
	
	while(1)
	{		
		CLoginDlg LoginDlg;
		m_pLoginDlgWnd = &LoginDlg;
		INT_PTR mRet = LoginDlg.DoModal();
		if(mRet == IDCANCEL)
		{
			break;
		}
		bool bRet = LoginDlg.GetLoginflag();

		CMainDlg mainDlg;
		if(bRet)
		{		
			mainDlg.SetLoginFlag(true);
			mainDlg.SetCurLoginAccount(LoginDlg.GetLoginAccount());
			mainDlg.SetCurSipAccount(LoginDlg.GetSipAccount());
			mainDlg.SetCurStatus(LoginDlg.GetStatus());
			m_pMainDlgWnd = &mainDlg;
			INT_PTR nResponse = mainDlg.DoModal();
			if (nResponse == IDOK)
			{
				// TODO: 在此放置处理何时用	
				continue;

				//  “确定”来关闭对话框的代码
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: 在此放置处理何时用
				//  “取消”来关闭对话框的代码
			}
			break;
		}
		else
		{
			mainDlg.SetLoginFlag(false);		
		}
	}

	/////数据会议模块卸载////
	tup_conf_uninit();

	/////Call模块卸载/////
	tup_call_uninit();	
	tup_call_log_stop();

	////IM模块卸载/////
	tup_im_uninit();

	/////Offline模块卸载////
	tup_offlinefile_uninit();

	//卸载gdi+
	GdiplusShutdown(m_pGdiToken);

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。

	return FALSE;
}

BOOL CTUPSDKPCDemoApp::ExitInstance(void)
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	return CWinApp::ExitInstance();
}
