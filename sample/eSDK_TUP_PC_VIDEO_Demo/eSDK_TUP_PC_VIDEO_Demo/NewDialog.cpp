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

// NewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "NewDialog.h"
#include "afxdialogex.h"


// CNewDialog dialog

IMPLEMENT_DYNAMIC(CNewDialog, CDialog)

CNewDialog::CNewDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDialog::IDD, pParent)
{

}

CNewDialog::~CNewDialog()
{
}

void CNewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcName);
	DDX_Control(pDX, IDC_STATIC_NUMBER, m_stcNum);
}


BEGIN_MESSAGE_MAP(CNewDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, &CNewDialog::OnBnClickedButtonAccept)
	ON_BN_CLICKED(IDC_BUTTON_REJECT, &CNewDialog::OnBnClickedButtonReject)
END_MESSAGE_MAP()


// CNewDialog message handlers


void CNewDialog::OnBnClickedButtonAccept()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CNewDialog::OnBnClickedButtonReject()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}


BOOL CNewDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_stcName.SetWindowText(m_strName);
	m_stcNum.SetWindowText(m_strNum);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
