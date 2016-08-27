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

#pragma once
#include "afxwin.h"
#include "ImageStatic.h"


// CDetailDlg 对话框

class CDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CDetailDlg)

public:
	CDetailDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDetailDlg();

// 对话框数据
	enum { IDD = IDD_DETAIL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg LRESULT UpdateDetail(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	
	std::string m_strAccount;
	bool isCustomContact;		//是否是自定义联系人
public:
	void GetUserInfo(void);

	//Add by w00321336 for DTS2015010702574 at 2015-1-22 start
	void UpdateOtherInfo(IM_S_USERINFO* pUser);
	void UpdateOtherInfo(IM_S_CONTACTNFO* pUser);
	//Add by w00321336 for DTS2015010702574 at 2015-1-22 end
public:	
	CEdit m_edtAccount;
	CStatic m_stcAccount;
	CStatic m_stcGender;
	CStatic m_stcTitle;
	CStatic m_stcDpt;
	CEdit m_edtGender;
	CEdit m_edtTitle;
	CEdit m_edtDpt;
	CStatic m_stcName;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CImageStatic m_imgstcHead;
	CEdit m_edtBindNo;
	CEdit m_stcOffice;
	CEdit m_edt;
	CEdit m_edtEmail;
	CEdit m_edtZip;
	CEdit m_stcAddr;
	afx_msg void OnClose();
};
