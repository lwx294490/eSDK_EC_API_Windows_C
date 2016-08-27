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

// DetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "DetailDlg.h"
#include "Tools.h"


// CDetailDlg 对话框

IMPLEMENT_DYNAMIC(CDetailDlg, CDialog)

CDetailDlg::CDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDetailDlg::IDD, pParent)
	,m_strAccount("")
	,isCustomContact(false)
{

}

CDetailDlg::~CDetailDlg()
{
}

void CDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_edtAccount);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_stcAccount);
	DDX_Control(pDX, IDC_STATIC_GENDER, m_stcGender);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_DEPT, m_stcDpt);
	DDX_Control(pDX, IDC_EDIT_GENDER, m_edtGender);
	DDX_Control(pDX, IDC_EDIT_m_treeContactTITLE, m_edtTitle);
	DDX_Control(pDX, IDC_EDIT_DEPT, m_edtDpt);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcName);
	DDX_Control(pDX, IDC_STATIC_HEADIMAGE, m_imgstcHead);
	DDX_Control(pDX, IDC_EDIT_BINDNO, m_edtBindNo);
	DDX_Control(pDX, IDC_EDIT_OFFICE, m_stcOffice);
	DDX_Control(pDX, IDC_EDIT_FAX, m_edt);
	DDX_Control(pDX, IDC_EDIT_EMAIL, m_edtEmail);
	DDX_Control(pDX, IDC_EDIT_POSTALCODE, m_edtZip);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_stcAddr);
}


BEGIN_MESSAGE_MAP(CDetailDlg, CDialog)
	ON_MESSAGE(WM_SHOW_DETAIL,CDetailDlg::UpdateDetail)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDetailDlg 消息处理程序

BOOL CDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDetailDlg::GetUserInfo(void)
{
	IM_S_GETUSERINFOARG arg;
	IM_S_USERINFO ack;

	//arg.account


	tup_im_getuserinfo(&arg,&ack);
}

void CDetailDlg::UpdateOtherInfo(IM_S_USERINFO* pUser)
{
	CHECK_POINTER(pUser);
	m_edtBindNo.SetWindowText(CTools::UTF2UNICODE(pUser->bindNO));
	m_stcOffice.SetWindowText(CTools::UTF2UNICODE(pUser->officePhone));
	m_edt.SetWindowText(CTools::UTF2UNICODE(pUser->fax));
	m_edtEmail.SetWindowText(CTools::UTF2UNICODE(pUser->email));
	m_edtZip.SetWindowText(CTools::UTF2UNICODE(pUser->postalcode));
	m_stcAddr.SetWindowText(CTools::UTF2UNICODE(pUser->address));
}

void CDetailDlg::UpdateOtherInfo(IM_S_CONTACTNFO* pUser)
{
	CHECK_POINTER(pUser);
	m_edtBindNo.SetWindowText(CTools::UTF2UNICODE(pUser->imNO));
	m_stcOffice.SetWindowText(CTools::UTF2UNICODE(pUser->officePhone));
	m_edt.SetWindowText(CTools::UTF2UNICODE(pUser->fax));
	m_edtEmail.SetWindowText(CTools::UTF2UNICODE(pUser->email));
	m_edtZip.SetWindowText(CTools::UTF2UNICODE(pUser->postalcode));
	m_stcAddr.SetWindowText(CTools::UTF2UNICODE(pUser->address));
}

LRESULT CDetailDlg::UpdateDetail(WPARAM pWPara,LPARAM pLPara)
{
	BOOL bFlag = (BOOL)pWPara;//是否是好友
	if(bFlag)
	{
		IM_S_USERINFO* pUserInfo = (IM_S_USERINFO*)pLPara;
		if(NULL == pUserInfo)
		{
			return -1L;
		}
		m_stcAccount.SetWindowText(_T("账号"));		
		m_stcGender.SetWindowText(_T("性别"));
		m_stcTitle.SetWindowText(_T("职务"));
		m_stcDpt.SetWindowText(_T("部门"));
		m_edtAccount.SetWindowText(CTools::UTF2UNICODE(pUserInfo->account));
		if(pUserInfo->gender == IM_E_GENDER_MALE)
		{
			m_edtGender.SetWindowText(L"男");
		}
		else if(pUserInfo->gender == IM_E_GENDER_FEMAIL)
		{
			m_edtGender.SetWindowText(L"女");
		}
		else
		{
			m_edtGender.SetWindowText(L"");
		}		
		m_edtTitle.SetWindowText(CTools::UTF2UNICODE(pUserInfo->title));
		m_edtDpt.SetWindowText(CTools::UTF2UNICODE(pUserInfo->deptNameEn));
		m_stcName.SetWindowText(CTools::UTF2UNICODE(pUserInfo->name));	

		UpdateOtherInfo(pUserInfo);//Add by w00321336 for DTS2015010702574 at 2015-1-22

		//设置头像
		if(0 != strlen(pUserInfo->imageID))
		{	
			if(strcmp(pUserInfo->imageID,pUserInfo->account) == 0)
			{
				//自定义头像
				IM_S_IMAGEREQARG ImageArg;
				IM_S_USERIMAGEINFO ImageAck;
				strcpy_s(ImageArg.id,IM_D_MAX_ACCOUNT_LENGTH,pUserInfo->imageID);
				CTools::CString2Char(L"19000000000000",ImageArg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH);
				TUP_RESULT tRet = tup_im_getuserdefineimage(&ImageArg,&ImageAck);
				if(TUP_SUCCESS != tRet)
				{
					AfxMessageBox(L"tup_im_getuserdefineimage failed.");
				}
				else
				{
					CString filepath;
					CTools::GetUserDefineImage(ImageArg.id,ImageAck.imagebits.data,ImageAck.imagebits.length,filepath);
					m_imgstcHead.SetImageFile(filepath);
				}
			}
			else
			{
				//系统头像
				CString strPath = CTools::getCurrentPath();
				CString strFulPath;
				strFulPath.Format(_T("%s\\face\\%s.png"), strPath, CTools::UTF2UNICODE(pUserInfo->imageID));
				m_imgstcHead.SetImageFile(strFulPath);
			}
		}
		else
		{
			CString strPath = CTools::getCurrentPath();
			CString strFulPath;
			strFulPath.Format(_T("%s\\face\\0.png"), strPath);
			m_imgstcHead.SetImageFile(strFulPath);
			
		}
		delete pUserInfo;
		pUserInfo = NULL;
	}
	else	
	{
		IM_S_CONTACTNFO* pContactInfo = (IM_S_CONTACTNFO*)pLPara;
		if(NULL == pContactInfo)
		{
			return -1L;
		}

		m_stcAccount.SetWindowText(_T("描述"));		
		m_stcGender.SetWindowText(_T("性别"));
		m_stcTitle.SetWindowText(_T("职务"));
		m_stcDpt.SetWindowText(_T("部门"));

		m_edtAccount.SetWindowText(CTools::UTF2UNICODE(pContactInfo->desc));
		if(pContactInfo->gender == IM_E_GENDER_MALE)
		{
			m_edtGender.SetWindowText(L"男");
		}
		else if(pContactInfo->gender == IM_E_GENDER_FEMAIL)
		{
			m_edtGender.SetWindowText(L"女");
		}
		else
		{
			m_edtGender.SetWindowText(L"");
		}		
		m_edtTitle.SetWindowText(CTools::UTF2UNICODE(pContactInfo->title));
		m_edtDpt.SetWindowText(CTools::UTF2UNICODE(pContactInfo->deptName));
		m_stcName.SetWindowText(CTools::UTF2UNICODE(pContactInfo->name));
        UpdateOtherInfo(pContactInfo);//Add by w00321336 for DTS2015010702574 at 2015-1-22
	}

	ShowWindow(SW_HIDE);
	UpdateData(FALSE);
	ShowWindow(SW_SHOW);

	return 0L;
}
BOOL CDetailDlg::PreTranslateMessage(MSG* pMsg)
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

void CDetailDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_DETAIL_DLG,NULL,NULL);
	//CDialog::OnClose();
}
