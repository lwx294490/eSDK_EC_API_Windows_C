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

// NewCallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "NewCallDlg.h"
#include "Tools.h"


// CNewCallDlg 对话框

IMPLEMENT_DYNAMIC(CNewCallDlg, CDialog)

CNewCallDlg::CNewCallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCallDlg::IDD, pParent)
	,m_BVideoCall(FALSE)
	,m_bConfCall(false)
{

}

CNewCallDlg::~CNewCallDlg()
{
}

void CNewCallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcName);
	DDX_Control(pDX, IDC_STATIC_DEPT, m_stcDept);
	DDX_Control(pDX, IDC_STATIC_NUM, m_stcNum);
	DDX_Control(pDX, IDC_STATIC_HEAD, m_stcUserHead);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_stcVideo);
}


BEGIN_MESSAGE_MAP(CNewCallDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, &CNewCallDlg::OnBnClickedButtonAccept)
	ON_BN_CLICKED(IDC_BUTTON_REJECT, &CNewCallDlg::OnBnClickedButtonReject)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CNewCallDlg 消息处理程序

BOOL CNewCallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_stcNum.SetWindowText(m_strNum);
	m_stcName.SetWindowText(m_strName);

	CString strAppPath = CTools::getCurrentPath();
	CString strFullPath;
	strFullPath.Format(_T("%s\\image\\video.jpg"), strAppPath);
	m_stcVideo.SetImageFile(strFullPath);

	if(m_BVideoCall)
	{
		m_stcVideo.ShowWindow(SW_SHOW);
	}
	else
	{
		m_stcVideo.ShowWindow(SW_HIDE);
	}

	if(m_bConfCall)
	{
		SetWindowText(L"新会议来电");
	}

	(void)SetTimer(SHUT_DLG_TIMEID, SHUT_DLG_TIME_DURATION, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNewCallDlg::OnBnClickedButtonAccept()
{
	// TODO: 在此添加控件通知处理程序代码
	(void)KillTimer(SHUT_DLG_TIMEID);
	OnOK();
}

void CNewCallDlg::OnBnClickedButtonReject()
{
	// TODO: 在此添加控件通知处理程序代码
	 (void)KillTimer(SHUT_DLG_TIMEID);
	OnCancel();
}

void CNewCallDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(SHUT_DLG_TIMEID == nIDEvent)
	{
		OnBnClickedButtonReject();
	}
	else{}

	CDialog::OnTimer(nIDEvent);
}
