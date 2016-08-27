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

// VideoPreviewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "VideoPreviewDlg.h"


// CVideoPreviewDlg 对话框

IMPLEMENT_DYNAMIC(CVideoPreviewDlg, CDialog)

CVideoPreviewDlg::CVideoPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoPreviewDlg::IDD, pParent)
	,m_uiIndex(0)
{

}

CVideoPreviewDlg::~CVideoPreviewDlg()
{
}

void CVideoPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_stcPreview);
}


BEGIN_MESSAGE_MAP(CVideoPreviewDlg, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CVideoPreviewDlg 消息处理程序

BOOL CVideoPreviewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// TODO:  在此添加额外的初始化
	TUP_RESULT tRet =tup_call_open_preview((TUP_UINT32)m_stcPreview.GetSafeHwnd(),m_uiIndex);
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(L"tup_call_open_preview failed.");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CVideoPreviewDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TUP_RESULT tRet = tup_call_close_preview();
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(L"tup_call_close_preview failed.");
	}

	m_uiIndex = 0;
	CDialog::OnClose();
}
