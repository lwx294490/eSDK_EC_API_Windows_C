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

// FullScreenModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "FullScreenModelDlg.h"
#include "afxdialogex.h"


// CFullScreenModelDlg dialog

IMPLEMENT_DYNAMIC(CFullScreenModelDlg, CDialog)

CFullScreenModelDlg::CFullScreenModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFullScreenModelDlg::IDD, pParent)
{

}

CFullScreenModelDlg::~CFullScreenModelDlg()
{
}

void CFullScreenModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFullScreenModelDlg, CDialog)
END_MESSAGE_MAP()


// CFullScreenModelDlg message handlers


BOOL CFullScreenModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitVideoInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//************************************************************************
void CFullScreenModelDlg::InitVideoInfo()
{
	FullScreenModeInfo[0].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO0);
	FullScreenModeInfo[0].isValuable = true;
	FullScreenModeInfo[0].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME0);

	FullScreenModeInfo[1].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO1);
	FullScreenModeInfo[1].isValuable = true;
	FullScreenModeInfo[1].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME1);

	FullScreenModeInfo[2].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO2);
	FullScreenModeInfo[2].isValuable = true;
	FullScreenModeInfo[2].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME2);

	FullScreenModeInfo[3].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO3);
	FullScreenModeInfo[3].isValuable = true;
	FullScreenModeInfo[3].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME3);

	FullScreenModeInfo[4].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO4);
	FullScreenModeInfo[4].isValuable = true;
	FullScreenModeInfo[4].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME4);

	FullScreenModeInfo[5].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO5);
	FullScreenModeInfo[5].isValuable = true;
	FullScreenModeInfo[5].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME5);

	FullScreenModeInfo[6].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO6);
	FullScreenModeInfo[6].isValuable = true;
	FullScreenModeInfo[6].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME6);

	FullScreenModeInfo[7].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO7);
	FullScreenModeInfo[7].isValuable = true;
	FullScreenModeInfo[7].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME7);

	FullScreenModeInfo[8].m_VideoHwnd = GetDlgItem(IDC_STATIC_FULL_VIDEO8);
	FullScreenModeInfo[8].isValuable = true;
	FullScreenModeInfo[8].m_NameHwnd = GetDlgItem(IDC_STATIC_FULL_NAME8);
}