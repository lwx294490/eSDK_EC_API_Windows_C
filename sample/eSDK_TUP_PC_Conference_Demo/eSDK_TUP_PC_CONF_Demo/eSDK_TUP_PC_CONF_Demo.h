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


// eSDK_TUP_PC_CONF_Demo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "eSDK_TUP_PC_CONF_DemoDlg.h"

// CeSDK_TUP_PC_CONF_DemoApp:
// See eSDK_TUP_PC_CONF_Demo.cpp for the implementation of this class
//

class CeSDK_TUP_PC_CONF_DemoApp : public CWinApp
{
public:
	CeSDK_TUP_PC_CONF_DemoApp();
	CeSDK_TUP_PC_CONF_DemoDlg* m_pMainDlg;
// Overrides
public:
	virtual BOOL InitInstance();
// Implementation

	DECLARE_MESSAGE_MAP()
public:
	std::string m_Account;
//	std::string m_SipAccount;
	std::string m_BindNO;
};

extern CeSDK_TUP_PC_CONF_DemoApp theApp;