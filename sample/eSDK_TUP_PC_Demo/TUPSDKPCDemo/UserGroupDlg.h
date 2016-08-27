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


// CUserGroupDlg 对话框

class CUserGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserGroupDlg)

public:
	CUserGroupDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserGroupDlg();

// 对话框数据
	enum { IDD = IDD_USERGROUP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
public:
	CString GetGroupName(void);
	void SetGroupName(const CString &);
private:
	CString m_cstrGroupName;
public:
	int m_iShowType;//0-表示新建分组 1-表示修改分组名称
public:
	CEdit m_edtUserGroupName;

};
