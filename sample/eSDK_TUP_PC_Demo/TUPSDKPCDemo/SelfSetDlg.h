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


// CSelfSetDlg �Ի���

class CSelfSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelfSetDlg)

public:
	CSelfSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelfSetDlg();

// �Ի�������
	enum { IDD = IDD_SELFINFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void Save();
	CStatic m_stcName;
	CStatic m_stcAccount;
	CStatic m_stcGender;
	CStatic m_stcTitle;
	CStatic m_stcdpt;
	CEdit m_edtSign;
	CStatic m_stcBindNO;
	CStatic m_stcMobile;
	CStatic m_stcOffice1;
	CStatic m_stcOffice2;
	CStatic m_stcHome;
	CStatic m_stcOther;
	CStatic m_stcFax;
	CStatic m_stcEmail;
	CStatic m_stcPostalCode;
	CStatic m_stcAddr;	
	CImageStatic m_stcHead;
};
