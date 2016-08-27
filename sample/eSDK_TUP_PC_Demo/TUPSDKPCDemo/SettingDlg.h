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
#include "afxcmn.h"
#include "SelfSetDlg.h"
#include "MediaSetDlg.h"
#include "CallSetDlg.h"
#include "FileSetDlg.h"


// CSettingDlg 对话框

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSelfSetDlg *m_pSelfSetDlg;
	CMediaSetDlg *m_pMediaSetDlg;
	CCallSetDlg* m_pCallSetDlg;
	CFileSetDlg* m_pFileSetDlg;
public:
	CTabCtrl m_tabSetting;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
