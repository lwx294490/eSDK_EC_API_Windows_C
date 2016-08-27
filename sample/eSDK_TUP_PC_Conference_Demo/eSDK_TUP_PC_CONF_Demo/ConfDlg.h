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
#include "afxwin.h"
#include  <string>
using namespace std;

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}
// ConfDlg dialog
enum GROUPLIST_COLUMNID
{
	COL_MEM_Compere, 
	COL_MEM_Status, 
	COL_MEM_Name, 
	COL_MEM_ACCOUNT,
	COL_MEM_CALLNO,
	COL_MEM_CALLSTATE,
	COL_MEM_SPK,
	COL_MEM_MUTE
};
class ConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfDlg)

public:
	ConfDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConfDlg();

// Dialog Data
	enum { IDD = IDD_CONFDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	void SetConfPara(std::string m_GropnUrl,TUP_UINT32 m_ulConfID);
	void SetCallID(TUP_UINT32 m_ulCallID,std::string m_subject);
	TUP_UINT32 GetCallID(){return m_ulCallID;};
	void RefreshMember(CALL_S_CONF_MEMBER* m_confMember,TUP_UINT32 m_memberCount);
private:
	// ////会议成员列表
	CListCtrl m_listMember;
	CStatic m_strConfName;
	TUP_UINT32 m_ulConfID;	//数据会议ID
	TUP_UINT32 m_ulCallID;	//语音会议ID
	std::string acGroupUri;
	void InitConfMember(std::string m_strGroupID);
	BOOL FindColum(const CString& cstrKey,int iColnum,int& iFind);
	bool GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo);
	bool GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack, const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo);
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_AccountName;
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
	afx_msg void OnClickedEndconf();
	afx_msg void OnClose();
private:
	CALL_E_SERVERCONF_TYPE m_ConfType;
public:
	void SetConfType(CALL_E_SERVERCONF_TYPE ConfType);
	CStatic m_strAccount;
private:
	bool m_bIsChairMan;
	virtual void OnCancel();
protected:
	afx_msg LRESULT OnOnekeyToConfResult(WPARAM wParam, LPARAM lParam);
};
