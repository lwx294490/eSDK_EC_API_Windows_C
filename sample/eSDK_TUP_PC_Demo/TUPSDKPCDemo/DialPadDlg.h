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
#include "Tools.h"


// CDialPadDlg 对话框

class CDialPadDlg : public CDialog
{
	DECLARE_DYNAMIC(CDialPadDlg)

public:
	CDialPadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialPadDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOne();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	void SetCallId(TUP_UINT32 _callId){m_ulCallId = _callId;};
public:
	CALL_E_DTMF_TONE m_key;
	TUP_UINT32 m_ulCallId;
private:
	void SendDTMF(TUP_UINT32 callId,CALL_E_DTMF_TONE Tone ,std::string m_Tonepath);
	std::string GetAudePath(void);
public:
	virtual BOOL OnInitDialog();
};
