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


// eSDK_TUP_PC_IM_Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "eSDK_TUP_PC_IM_Demo.h"
#include "LoginDlg.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeSDK_TUP_PC_IM_DemoApp

BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_IM_DemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CeSDK_TUP_PC_IM_DemoApp construction

CeSDK_TUP_PC_IM_DemoApp::CeSDK_TUP_PC_IM_DemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CeSDK_TUP_PC_IM_DemoApp object

CeSDK_TUP_PC_IM_DemoApp theApp;


// CeSDK_TUP_PC_IM_DemoApp initialization

BOOL CeSDK_TUP_PC_IM_DemoApp::InitInstance()
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

	//gdi+�õ�����������   װ��gdi+
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	//��ʼ��IM���ֵײ�����
	TUP_RESULT tIMRet = tup_im_init();
	if(TUP_SUCCESS != tIMRet)
	{		
		return FALSE;
	}

	while(1)
	{
		CLoginDlg LoginDlg;
		m_pLoginDlgWnd = &LoginDlg;
		INT_PTR nResponse = LoginDlg.DoModal();
		if(nResponse == IDCANCEL)
		{
			break;
		}
		bool bRet = LoginDlg.GetLoginflag();

		CMainDlg mainDlg;
		if(bRet)
		{		
			mainDlg.SetLoginFlag(true);
			//����¼�˺š�SIP�˺š�״̬�������Ի���
			mainDlg.SetCurLoginAccount(LoginDlg.GetLoginAccount());
			m_pMainDlgWnd = &mainDlg;
			INT_PTR nResponse = mainDlg.DoModal();
			if (nResponse == IDCANCEL)
			{
				// TODO: �ڴ˷��ô����ʱ��
				break;
			}
		}
		else
		{
			mainDlg.SetLoginFlag(false);		
		}
	}

	//�ͷ�IM���ֵײ�����
	tIMRet = tup_im_uninit();
	if(tIMRet == TUP_FAIL)
	{
		AfxMessageBox(_T("tup_im_uninit failed."));
	}

	//ж��gdi+
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

