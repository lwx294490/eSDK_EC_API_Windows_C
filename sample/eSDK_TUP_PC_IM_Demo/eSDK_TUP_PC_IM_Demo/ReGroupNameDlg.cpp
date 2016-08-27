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

// ReGroupNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_IM_Demo.h"
#include "ReGroupNameDlg.h"
#include "afxdialogex.h"


// CReGroupNameDlg dialog

IMPLEMENT_DYNAMIC(CReGroupNameDlg, CDialogEx)

CReGroupNameDlg::CReGroupNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReGroupNameDlg::IDD, pParent)
	, cstrPrompt(L"")
{

}

CReGroupNameDlg::~CReGroupNameDlg()
{
}

void CReGroupNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReGroupNameDlg, CDialogEx)
END_MESSAGE_MAP()


// CReGroupNameDlg message handlers


BOOL CReGroupNameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_STATIC)->SetWindowText(cstrPrompt); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CReGroupNameDlg::SetPromptCStr(CString CStrPrompt)
{
	cstrPrompt = _T("该分组名已经存在，自动命名为：\r\n") + CStrPrompt;
}