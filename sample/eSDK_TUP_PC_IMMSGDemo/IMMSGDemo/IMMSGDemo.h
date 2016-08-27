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


// IMMSGDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IMMSGDemo_i.h"
#include <GdiPlus.h>
using namespace Gdiplus;

// CIMMSGDemoApp:
// See IMMSGDemo.cpp for the implementation of this class
//

class CIMMSGDemoApp : public CWinApp
{
public:
	CIMMSGDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	BOOL ExitInstance(void);
private:
	ULONG_PTR m_pGdiToken;
};

extern CIMMSGDemoApp theApp;