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

// GroupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "GroupSearchDlg.h"
#include "Tools.h"

// CGroupDlg �Ի���

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


// CGroupDlg ��Ϣ�������

BOOL CGroupSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	LONG lStyle;
	lStyle = GetWindowLong(m_groupSearchList.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_groupSearchList.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_groupSearchList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_groupSearchList.SetExtendedStyle(dwStyle); //������չ���
	m_groupSearchList.InsertColumn( 0, _T("Ⱥ������"), LVCFMT_LEFT,700);//������
	return TRUE;  
}




void CGroupSearchDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�̶�Ⱥ�б�
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
				int nRow = m_groupSearchList.InsertItem(0, cstrAccount);//������
				//m_groupSearchList.SetItemText(nRow, 1, _T("jacky"));//��������
			}
			list = list->next;
		}
		tup_im_release_tup_list(ack.imGroupList);
	}
}




BOOL CGroupSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
