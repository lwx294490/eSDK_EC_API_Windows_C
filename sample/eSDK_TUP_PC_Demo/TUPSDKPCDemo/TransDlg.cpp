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

// TransDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "TransDlg.h"


// CTransDlg 对话框

IMPLEMENT_DYNAMIC(CTransDlg, CDialog)

CTransDlg::CTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransDlg::IDD, pParent)
	, m_cstrTransNUM(_T(""))
{

}

CTransDlg::~CTransDlg()
{
}

void CTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cstrTransNUM);
}


BEGIN_MESSAGE_MAP(CTransDlg, CDialog)
END_MESSAGE_MAP()


// CTransDlg 消息处理程序
