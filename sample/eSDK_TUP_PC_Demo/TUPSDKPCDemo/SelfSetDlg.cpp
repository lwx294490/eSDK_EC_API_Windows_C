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

// SelfSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "SelfSetDlg.h"
#include "Tools.h"
#include "MainDlg.h"


// CSelfSetDlg 对话框

IMPLEMENT_DYNAMIC(CSelfSetDlg, CDialog)

CSelfSetDlg::CSelfSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelfSetDlg::IDD, pParent)
{
}

CSelfSetDlg::~CSelfSetDlg()
{
}

void CSelfSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcName);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_stcAccount);
	DDX_Control(pDX, IDC_STATIC_SEX, m_stcGender);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_DEPT, m_stcdpt);
	DDX_Control(pDX, IDC_EDIT_SIGNATRUE, m_edtSign);
	DDX_Control(pDX, IDC_STATIC_BINDNO, m_stcBindNO);
	DDX_Control(pDX, IDC_STATIC_MOBILE, m_stcMobile);
	DDX_Control(pDX, IDC_STATIC_OFFICE1, m_stcOffice1);
	DDX_Control(pDX, IDC_STATIC_OFFICE2, m_stcOffice2);
	DDX_Control(pDX, IDC_STATIC_HOME, m_stcHome);
	DDX_Control(pDX, IDC_STATIC_OTHER, m_stcOther);
	DDX_Control(pDX, IDC_STATIC_FAX, m_stcFax);
	DDX_Control(pDX, IDC_STATIC_EMAIL, m_stcEmail);
	DDX_Control(pDX, IDC_STATIC_ZIP, m_stcPostalCode);
	DDX_Control(pDX, IDC_STATIC_ADDR, m_stcAddr);
	DDX_Control(pDX, IDC_STATIC_HEAD, m_stcHead);
}


BEGIN_MESSAGE_MAP(CSelfSetDlg, CDialog)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CSelfSetDlg 消息处理程序

BOOL CSelfSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	IM_S_GETUSERINFOARG sefInfoarg;
	strcpy_s(sefInfoarg.account,IM_D_MAX_ACCOUNT_LENGTH,g_Account.c_str());
	IM_S_USERINFO userinfo;	
	TUP_RESULT tRet = tup_im_getuserinfo(&sefInfoarg,&userinfo);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_getuserinfo failed.");
		return FALSE;
	}

	m_stcAccount.SetWindowText(CTools::UTF2UNICODE(userinfo.account));
	m_stcName.SetWindowText(CTools::UTF2UNICODE(userinfo.name));
	if(userinfo.gender == IM_E_GENDER_MALE)
	{
		m_stcGender.SetWindowText(L"男");
	}
	else if(userinfo.gender == IM_E_GENDER_FEMAIL)
	{
		m_stcGender.SetWindowText(L"女");
	}
	else
	{
		m_stcGender.SetWindowText(L"");
	}
	m_stcAccount.SetWindowText(CTools::UTF2UNICODE(userinfo.account));
	m_stcTitle.SetWindowText(CTools::UTF2UNICODE(userinfo.title));
	m_stcdpt.SetWindowText(CTools::UTF2UNICODE(userinfo.deptNameEn));

	m_edtSign.SetWindowText(CTools::UTF2UNICODE(userinfo.signature));

	m_stcBindNO.SetWindowText(CTools::UTF2UNICODE(userinfo.bindNO));
	m_stcMobile.SetWindowText(CTools::UTF2UNICODE(userinfo.mobile));
	m_stcOffice1.SetWindowText(CTools::UTF2UNICODE(userinfo.officePhone));
	m_stcOffice2.SetWindowText(CTools::UTF2UNICODE(userinfo.shortPhone));
	m_stcHome.SetWindowText(CTools::UTF2UNICODE(userinfo.homePhone));
	m_stcOther.SetWindowText(CTools::UTF2UNICODE(userinfo.otherPhone));
	m_stcFax.SetWindowText(CTools::UTF2UNICODE(userinfo.fax));
	m_stcEmail.SetWindowText(CTools::UTF2UNICODE(userinfo.email));
	m_stcPostalCode.SetWindowText(CTools::UTF2UNICODE(userinfo.postalcode));
	m_stcAddr.SetWindowText(CTools::UTF2UNICODE(userinfo.address));

	if(0 != strlen(userinfo.imageID))
	{	
		if(strcmp(userinfo.imageID,userinfo.account) == 0)
		{
			//自定义头像
		}
		else
		{
			//系统头像
			//Modified by w00321336 to fix image missing issue at 2015-1-21 begin
			CString strAppPath = CTools::getCurrentPath();
			CString strFullPath;
			strFullPath.Format(_T("%s\\face\\%s.png"), strAppPath, CTools::UTF2UNICODE(userinfo.imageID));
			m_stcHead.SetImageFile(strFullPath);
			//Modified by w00321336 to fix image missing issue at 2015-1-21 end
		}
	}
	else
	{	
		//Modified by w00321336 to fix image missing issue at 2015-1-21 begin
		CString strAppPath = CTools::getCurrentPath();

		CString strFullPath;
		strFullPath.Format(_T("%s\\face\\0.png"), strAppPath);
		m_stcHead.SetImageFile(strFullPath);
		//Modified by w00321336 to fix image missing issue at 2015-1-21 end
	}

	/////DTS2015110405099 限制个人签名字符长度    by c00327158 Start////
	m_edtSign.LimitText(IM_D_MAX_DESC_LENGTH);
	/////DTS2015110405099 限制个人签名字符长度    by c00327158 End////

	//////初始化滚动条长度 c00327158 2015-11-10 Start//////
	CRect rc;
	GetClientRect(&rc);
	SetScrollRange(SB_VERT, 0, 12);
	//////初始化滚动条长度 c00327158 2015-11-10 End//////

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CSelfSetDlg::Save()
{
	IM_S_USERINFO stUserInfo;

	CString cstrAccount;
	m_stcAccount.GetWindowText(cstrAccount);
	CTools::CString2Char(cstrAccount,stUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH);
	CString cstrSign;
	m_edtSign.GetWindowText(cstrSign);
	CTools::CString2Char(cstrSign,stUserInfo.signature,IM_D_MAX_DESC_LENGTH);
	TUP_RESULT tRet = tup_im_setuserinfo(&stUserInfo);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_im_setuserinfo failed.");
		return ;
	}
	/////更新Main对话框的个人签名//////
	CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
	pMainDlg->m_edtSign.SetWindowText(cstrSign);

}
void CSelfSetDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SCROLLINFO scrollinfo;

	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

	switch (nSBCode) 

	{ 

	case SB_BOTTOM: 

		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*10); 

		scrollinfo.nPos = scrollinfo.nMax; 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		break; 

	case SB_TOP: 

		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*10); 

		scrollinfo.nPos = scrollinfo.nMin; 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		break; 

	case SB_LINEUP: 

		scrollinfo.nPos -= 1; 

		if (scrollinfo.nPos<scrollinfo.nMin)

		{ 

			scrollinfo.nPos = scrollinfo.nMin; 

			break;

		} 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		ScrollWindow(0,10); 

		break; 

	case SB_LINEDOWN:

		scrollinfo.nPos += 1; 

		if (scrollinfo.nPos>scrollinfo.nMax) 

		{ 

			scrollinfo.nPos = scrollinfo.nMax; 

			break; 

		} 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		ScrollWindow(0,-10); 

		break; 

	case SB_PAGEUP: 

		scrollinfo.nPos -= 5; 

		if (scrollinfo.nPos<scrollinfo.nMin)

		{ 

			scrollinfo.nPos = scrollinfo.nMin; 

			break; 

		} 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		ScrollWindow(0,10*5); 

		break; 

	case SB_PAGEDOWN: 

		scrollinfo.nPos += 5; 

		if (scrollinfo.nPos>scrollinfo.nMax) 

		{ 

			scrollinfo.nPos = scrollinfo.nMax; 

			break; 

		} 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		ScrollWindow(0,-10*5); 

		break; 

	case SB_ENDSCROLL: 

		// MessageBox("SB_ENDSCROLL"); 

		break; 

	case SB_THUMBPOSITION: 

		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 

		// scrollinfo.nPos = nPos; 

		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		break; 

	case SB_THUMBTRACK: 

		ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 

		scrollinfo.nPos = nPos; 

		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 

		break; 

	}


	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
