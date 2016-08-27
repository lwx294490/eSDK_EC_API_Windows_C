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

// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "SettingDlg.h"


// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	,m_pSelfSetDlg(NULL)
	,m_pMediaSetDlg(NULL)
	,m_pCallSetDlg(NULL)
	,m_pFileSetDlg(NULL)
{

}

CSettingDlg::~CSettingDlg()
{
	SAFE_DELETE(m_pSelfSetDlg);
	SAFE_DELETE(m_pMediaSetDlg);
	SAFE_DELETE(m_pCallSetDlg);
	SAFE_DELETE(m_pFileSetDlg);
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SET, m_tabSetting);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SET, &CSettingDlg::OnTcnSelchangeTabSet)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CSettingDlg::OnBnClickedButtonApply)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������

BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(NULL == m_pSelfSetDlg)
	{
		m_pSelfSetDlg = new CSelfSetDlg();		
	}
	if(!::IsWindow(m_pSelfSetDlg->GetSafeHwnd()))
	{
		m_pSelfSetDlg->Create(CSelfSetDlg::IDD,&m_tabSetting);
	}

	if(NULL == m_pMediaSetDlg)
	{
		m_pMediaSetDlg = new CMediaSetDlg();		
	}
	if(!::IsWindow(m_pMediaSetDlg->GetSafeHwnd()))
	{
		m_pMediaSetDlg->Create(CMediaSetDlg::IDD,&m_tabSetting);
	}

	if(NULL == m_pCallSetDlg)
	{
		m_pCallSetDlg = new CCallSetDlg();		
	}
	if(!::IsWindow(m_pCallSetDlg->GetSafeHwnd()))
	{
		m_pCallSetDlg->Create(CCallSetDlg::IDD,&m_tabSetting);
	}

	if(NULL == m_pFileSetDlg)
	{
		m_pFileSetDlg = new CFileSetDlg();		
	}
	if(!::IsWindow(m_pFileSetDlg->GetSafeHwnd()))
	{
		m_pFileSetDlg->Create(CFileSetDlg::IDD,&m_tabSetting);
	}


	m_tabSetting.InsertItem(0,L"����");
	m_tabSetting.InsertItem(1,L"ý��");
	//m_tabSetting.InsertItem(2,L"����");
	//m_tabSetting.InsertItem(3,L"�ļ�����");
	

	CRect rc;
	m_tabSetting.GetClientRect(&rc);
	rc.top+=25; 
	rc.bottom-=3; 
	rc.left+=3; 
	rc.right-=3; 

	m_pSelfSetDlg->MoveWindow(&rc,TRUE);
	m_pMediaSetDlg->MoveWindow(&rc,TRUE);
	m_pCallSetDlg->MoveWindow(&rc,TRUE);
	m_pFileSetDlg->MoveWindow(&rc,TRUE);

	m_tabSetting.SetCurSel(0);
	m_pSelfSetDlg->ShowWindow(SW_NORMAL);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSettingDlg::OnTcnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iIndex = m_tabSetting.GetCurSel();
	switch (iIndex)
	{
	case -1:
		{
			break;
		}
	case 0:
		{          
			m_pSelfSetDlg->ShowWindow(SW_SHOW);
			m_pMediaSetDlg->ShowWindow(SW_HIDE);
			m_pCallSetDlg->ShowWindow(SW_HIDE);
			m_pFileSetDlg->ShowWindow(SW_HIDE);
			break;
		}
	case 1:
		{  
			m_pSelfSetDlg->ShowWindow(SW_HIDE);
			m_pMediaSetDlg->ShowWindow(SW_SHOW);
			m_pCallSetDlg->ShowWindow(SW_HIDE);
			m_pFileSetDlg->ShowWindow(SW_HIDE);
			break;
		}
	case 2:
		{  
			m_pSelfSetDlg->ShowWindow(SW_HIDE);
			m_pMediaSetDlg->ShowWindow(SW_HIDE);
			m_pCallSetDlg->ShowWindow(SW_SHOW);
			m_pFileSetDlg->ShowWindow(SW_HIDE);
			break;
		}
	case 3:
		{  
			m_pSelfSetDlg->ShowWindow(SW_HIDE);
			m_pMediaSetDlg->ShowWindow(SW_HIDE);
			m_pCallSetDlg->ShowWindow(SW_HIDE);
			m_pFileSetDlg->ShowWindow(SW_SHOW);
			break;
		}
	}



	*pResult = 0;
}

void CSettingDlg::OnBnClickedButtonApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iSel = m_tabSetting.GetCurSel();
	switch (iSel)
	{
	case 0:
		{
			m_pSelfSetDlg->Save();
		}
		break;
	case 1:
		{
			m_pMediaSetDlg->Save();			
		}
		break;
	}
}

void CSettingDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_SET_DLG,NULL,NULL);

	//CDialog::OnClose();
}

void CSettingDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();

	m_pSelfSetDlg->Save();
	m_pMediaSetDlg->Save();			
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_SET_DLG,NULL,NULL);
}

void CSettingDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnCancel();
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_SET_DLG,NULL,NULL);
}
