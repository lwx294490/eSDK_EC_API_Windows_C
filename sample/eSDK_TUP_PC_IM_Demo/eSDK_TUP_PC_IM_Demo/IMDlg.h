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

#include "afxcmn.h"
#include "Resource.h"
#include "ImageStatic.h"

typedef enum{
	SIGNLE_CHAT,
	MULTI_CHAT,
	SIGNLE_CALL,
	MULTI_CALL,
	SIGNLE_SMS,
	MULTI_SMS,
}DLG_TYPE;


// CIMDlg 对话框

class CIMDlg : public CDialog, public CUserQueryHelper
{
	DECLARE_DYNAMIC(CIMDlg)

public:
	CIMDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIMDlg();

// 对话框数据
	enum { IDD = IDD_IM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSendIM();
	afx_msg void OnBnClickedButtonAddUser();
	afx_msg LRESULT OnSendIMMenuClick(WPARAM,LPARAM);
	afx_msg LRESULT OnRecvIM(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupNotify(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupInfoChange(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupMemAdd(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupMemDel(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupOwnerChange(WPARAM,LPARAM);	
	afx_msg void OnNMRClickListMember(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListMemMenuItem(UINT nID);
	DECLARE_MESSAGE_MAP()

public:
	void SetLoginAccount(const std::string& strAccount){m_strLoginAccount = strAccount;}
	void SetLoginName(const std::string& strName){m_strLoginName = strName;}
	void SetGroupID(const std::string& strGroupID){m_strGroupID = strGroupID;}
	DLG_TYPE GetDlgType(){return m_DlgType;}
	// 压缩的消息格式
	void ComMsgFormat(CString& cotent, CString& sendCotent);

	// 未压缩的消息格式
	void UnCompMsgFormat(CString& content, CString& sendContent);

	// 处理从eSpace或UC传过来的消息内容（判断是否压缩，是否进行相应解压等操作）
	void ProcessCotentFromeSpaceOrUC(std::string& cotent);

	// 解析从eSpace或UC传过来的文本
	void ParseStringFromUCoreSpase(CString& content);

protected:
	void RefreshWindow(void);
	void RefreshMemberList(const std::string& groupID);
	BOOL FindColum(const CString& cstrKey,int colnum,int& iFind);
	void RefershChairMan(const std::string& strAccount);
	//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 begin
	void SetDefualtHeadImg();
	void SetGroupHeadImg();

	BOOL SetUserHeadImg(const IM_S_USERINFO& userInfo);
	BOOL GetUserDefHeadImg(const TUP_CHAR imageID[], IM_S_IMAGEINFO& imgInfo);

	int GetUserHeadImg(const IM_S_USERINFO& userInfo
		, IM_S_IMAGEINFO& imgeInfo
		, CString& strImgPath
		);

	CString GetLocalHeadImg(const TUP_CHAR imageID[]);
	CString GetDefaultHeadImg();
	//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 end

public:
	IM_S_USERINFO m_targetUserInfo;
	std::string m_strGroupID;
	CStatic m_stcName;

private:		
	CImageStatic m_stcHead;
	CEdit m_edtIMContent;
	CEdit m_edtSend;
	CListCtrl m_listMember;	
	CButton m_btnAdd;
	std::string m_strLoginAccount;
	std::string m_strLoginName;	
	DLG_TYPE m_DlgType;	//	对话框类型
};
