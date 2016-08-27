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
static const int SHUT_DLG_TIMEID  = 30001;      //Ĭ�Ϲر�������ʾ��Ϣ///
static const int SHUT_DLG_TIME_DURATION = 30*1000;   //������˷�Ķ�ʱ��ʱ��


// CNewCallDlg �Ի���

class CNewCallDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewCallDlg)

public:
	CNewCallDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewCallDlg();

// �Ի�������
	enum { IDD = IDD_INCOMINGCALL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_stcName;
	CStatic m_stcDept;
	CStatic m_stcNum;
	afx_msg void OnBnClickedButtonAccept();
	afx_msg void OnBnClickedButtonReject();
	CString m_strName;
	CString m_strNum;
	BOOL m_BVideoCall;
	CImageStatic m_stcUserHead;
	CImageStatic m_stcVideo;
	bool m_bConfCall;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
