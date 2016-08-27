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

// GroupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "GroupSearchDlg.h"
#include "Tools.h"

// CGroupDlg 对话框

IMPLEMENT_DYNAMIC(CGroupSearchDlg, CDialog)

CGroupSearchDlg::CGroupSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupSearchDlg::IDD, pParent)
	, m_groupSearch(_T(""))
{
}

CGroupSearchDlg::~CGroupSearchDlg()
{
}

void CGroupSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_groupSearch);
	DDX_Control(pDX, IDC_LIST1, m_groupSearchList);
}


BEGIN_MESSAGE_MAP(CGroupSearchDlg, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CGroupSearchDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CGroupDlg 消息处理程序

BOOL CGroupSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	LONG lStyle;
	lStyle = GetWindowLong(m_groupSearchList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_groupSearchList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_groupSearchList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_groupSearchList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_groupSearchList.InsertColumn( 0, _T("群组名称"), LVCFMT_LEFT,700);//插入列
	return TRUE;  
}




void CGroupSearchDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取固定群列表
	IM_S_GETIMGROUPLIST_ARG arg;
	IM_S_GETIMGROUPLIST_ACK ack;
	memset(&arg,0,sizeof(IM_S_GETIMGROUPLIST_ARG));
	memset(&ack,0,sizeof(IM_S_GETIMGROUPLIST_ACK));
	int len = 0;
	UpdateData(TRUE);
	m_groupSearchList.DeleteAllItems();
	arg.isNeedAmount = false;
	arg.offset = 0;
	arg.count = 20;
	arg.queryType = IM_E_IMGROUPQUERYTYPE_BY_NAME;
	TUP_CHAR Key[IM_D_GENEAL_LENGTH] = {0};
	CTools::CString2Char(m_groupSearch,Key,IM_D_GENEAL_LENGTH);
	strcpy_s( arg.queryKey, sizeof(arg.queryKey), Key);

	TUP_RESULT getRst = tup_im_getfixedgroups (&arg, &ack);
	if(getRst == TUP_SUCCESS)
	{
		TUP_S_LIST* list =  ack.imGroupList;
		while(list != NULL)
		{
			IM_S_IMGROUPINFO* groupUser = (IM_S_IMGROUPINFO*)list->data;
			if(NULL != groupUser)
			{
				CString cstrAccount = CTools::UTF2UNICODE(groupUser->name);
				int nRow = m_groupSearchList.InsertItem(0, cstrAccount);//插入行
				//m_groupSearchList.SetItemText(nRow, 1, _T("jacky"));//设置数据
			}
			list = list->next;
		}
		tup_im_release_tup_list(ack.imGroupList);
	}
}




BOOL CGroupSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_RETURN)
		{
			return TRUE;
		}
		if(nVirtKey == VK_ESCAPE)
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
