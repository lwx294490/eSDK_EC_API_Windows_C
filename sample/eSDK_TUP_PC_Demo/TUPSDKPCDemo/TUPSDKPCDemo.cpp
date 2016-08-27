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


// TUPSDKPCDemo.cpp : ����Ӧ�ó��������Ϊ��
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


// CTUPSDKPCDemoApp ����

CTUPSDKPCDemoApp::CTUPSDKPCDemoApp():m_pMainDlgWnd(NULL),m_pLoginDlgWnd(NULL)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTUPSDKPCDemoApp ����

CTUPSDKPCDemoApp theApp;


// CTUPSDKPCDemoApp ��ʼ��

BOOL CTUPSDKPCDemoApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	AfxOleInit();
	/////ֻ����һ��ʵ��
// 	HANDLE m_hMutex=CreateMutex(NULL,TRUE,m_pszAppName);
// 	if(GetLastError() == ERROR_ALREADY_EXISTS)
// 	{
// 		AfxMessageBox(L"�ó����Ѿ�����");
// 		ExitProcess(0);
// 	} 
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxInitRichEdit2();

	AfxEnableControlContainer();
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// ͨ�� CoRegisterClassObject() ע���๤����
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// Ӧ�ó������� /Embedding �� /Automation ���������ġ�
	// ��Ӧ�ó�����Ϊ�Զ������������С�
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// ����ʾ������
		return TRUE;
	}
	// Ӧ�ó������� /Unregserver �� /Unregister ���������ġ�
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// Ӧ�ó������� /Register �� /Regserver ���������ġ�
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		return FALSE;
	}

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//gdi+�õ�����������   װ��gdi+
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	////��ʼ��IMģ��
	TUP_RESULT tRet = tup_im_init();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_init failed!"));
		return FALSE;
	}

	// ��ʼ�������ļ����
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

	//���ݻ���
	//������־·��
	string strLog = CTools::UNICODE2UTF(strAppPath);
	//��ʼ���������
	Init_param sInitParam; 
	sInitParam.os_type = CONF_OS_WIN;
	sInitParam.dev_type = CONF_DEV_PC;
	sInitParam.media_log_level = 2;
	sInitParam.sdk_log_level = 2;
	(VOID)strncpy_s(sInitParam.log_path, sizeof(sInitParam.log_path), strLog.c_str(), TC_MAX_PATH-1);
	(VOID)strncpy_s(sInitParam.temp_path, sizeof(sInitParam.temp_path), strLog.c_str(), TC_MAX_PATH-1);
	tup_conf_init((TUP_BOOL)false, &sInitParam);

	/////�ͷŲ���////
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
				// TODO: �ڴ˷��ô����ʱ��	
				continue;

				//  ��ȷ�������رնԻ���Ĵ���
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: �ڴ˷��ô����ʱ��
				//  ��ȡ�������رնԻ���Ĵ���
			}
			break;
		}
		else
		{
			mainDlg.SetLoginFlag(false);		
		}
	}

	/////���ݻ���ģ��ж��////
	tup_conf_uninit();

	/////Callģ��ж��/////
	tup_call_uninit();	
	tup_call_log_stop();

	////IMģ��ж��/////
	tup_im_uninit();

	/////Offlineģ��ж��////
	tup_offlinefile_uninit();

	//ж��gdi+
	GdiplusShutdown(m_pGdiToken);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�

	return FALSE;
}

BOOL CTUPSDKPCDemoApp::ExitInstance(void)
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	return CWinApp::ExitInstance();
}
