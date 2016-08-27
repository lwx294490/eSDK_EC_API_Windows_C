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

// UserGroupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "UserGroupDlg.h"


// CUserGroupDlg �Ի���

IMPLEMENT_DYNAMIC(CUserGroupDlg, CDialog)

CUserGroupDlg::CUserGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserGroupDlg::IDD, pParent)
	,m_iShowType(0)
	,m_cstrGroupName(L"")
{

}

CUserGroupDlg::~CUserGroupDlg()
{
}

void CUserGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtUserGroupName);
}


BEGIN_MESSAGE_MAP(CUserGroupDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CUserGroupDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserGroupDlg ��Ϣ�������

BOOL CUserGroupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(0==m_iShowType)
	{
		SetWindowText(L"�½�����");
	}
	else
	{
		SetWindowText(L"������");
	}
	/////DTS2015110405099 ����Ⱥ�����ַ�����   by c00327158 Start////
	m_edtUserGroupName.LimitText(IM_D_MAX_NAME_LENGTH);
	/////DTS2015110405099 ����Ⱥ�����ַ�����   by c00327158 End////

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
CString CUserGroupDlg::GetGroupName(void)
{	
	return m_cstrGroupName;

}
void CUserGroupDlg::SetGroupName(const CString &cstrName)
{
	m_edtUserGroupName.SetWindowText(cstrName);
}

void CUserGroupDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edtUserGroupName.GetWindowText(m_cstrGroupName);
	if(m_cstrGroupName.IsEmpty())
	{
		return;
	}
	OnOK();
}
