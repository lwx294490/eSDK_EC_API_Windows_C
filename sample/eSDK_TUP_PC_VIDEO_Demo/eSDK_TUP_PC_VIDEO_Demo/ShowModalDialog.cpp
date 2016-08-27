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

// ShowModalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "ShowModalDialog.h"
#include "afxdialogex.h"


// CShowModalDialog dialog

IMPLEMENT_DYNAMIC(CShowModalDialog, CDialog)

CShowModalDialog::CShowModalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CShowModalDialog::IDD, pParent)
{

}

CShowModalDialog::~CShowModalDialog()
{
}

void CShowModalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowModalDialog, CDialog)
END_MESSAGE_MAP()


// CShowModalDialog message handlers


BOOL CShowModalDialog::OnInitDialog()
{
	LONG style = GetWindowLong(GetDlgItem(IDC_STATIC_SHOW_LOCAL)->GetSafeHwnd(),GWL_STYLE);
	style = style | WS_CLIPSIBLINGS ;
	SetWindowLong(GetDlgItem(IDC_STATIC_SHOW_LOCAL)->GetSafeHwnd(),GWL_STYLE,style);

	style = GetWindowLong(GetDlgItem(IDC_STATIC_SHOW_CHAIRMAN)->GetSafeHwnd(),GWL_STYLE);
	style = style | WS_CLIPSIBLINGS ;
	SetWindowLong(GetDlgItem(IDC_STATIC_SHOW_CHAIRMAN)->GetSafeHwnd(),GWL_STYLE,style);

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitVideoInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//************************************************************************
void CShowModalDialog::InitVideoInfo()
{
	ShowModalInfo[0].m_VideoHwnd = GetDlgItem(IDC_STATIC_SHOW_CHAIRMAN);
	ShowModalInfo[0].isValuable = true;
	ShowModalInfo[1].m_VideoHwnd = GetDlgItem(IDC_STATIC_SHOW_LOCAL);
	ShowModalInfo[1].isValuable = true;
}