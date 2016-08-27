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

class CLevelDlg;

typedef enum{
	NO_CALL,
	CALLING,
	CALL_CONNECTED
};

// CCallCtrlDlg 对话框

class CCallCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CCallCtrlDlg)

public:
	CCallCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCallCtrlDlg();

// 对话框数据
	enum { IDD = IDD_CALLCTRL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	void SetCallState(int);
	void SetNetInfoLevel(TUP_UINT32 level,TUP_UINT32 errorinfo);
public:
	CString m_strPath;
	int m_state;
	TUP_UINT32 m_NetLevel;
	TUP_UINT32 m_NetErrorInfo;
	CStatic m_stcCalling;
	CButton m_btnHangup;
	CButton m_btnHold;
	afx_msg void OnBnClickedButtonHangup();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonHold();
	CButton m_btnMic;
	CButton m_btnSpk;
	afx_msg void OnBnClickedButtonMic();
	afx_msg void OnBnClickedButtonSpk();
	afx_msg void OnBnClickedButtonRec();
	afx_msg void OnBnClickedButtonTran();
	CButton m_btnRec;
	CButton m_btnTrans;
	CLevelDlg* m_pLevelDlg;
	afx_msg void OnBnHotItemChangeButtonMic(NMHDR *pNMHDR, LRESULT *pResult);
	CImageStatic m_imgStcNetLevel;
	CStatic m_stcErrInfo;
	afx_msg void OnBnClickedButton1();
	void ReshCallCtrlWindow();

private:
	std::string m_RecordPath;
};
