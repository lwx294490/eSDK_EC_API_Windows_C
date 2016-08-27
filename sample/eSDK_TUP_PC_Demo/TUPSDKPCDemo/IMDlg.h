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
#include "CallCtrlDlg.h"
#include "afxcmn.h"
#include "ImageStatic.h"
#include "RichEditCtrlEx.h"

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
	afx_msg LRESULT OnHangUp(WPARAM,LPARAM);
	afx_msg LRESULT OnCallConnected(WPARAM,LPARAM);
	afx_msg LRESULT OnCallEnd(WPARAM,LPARAM);
	afx_msg LRESULT OnCallAddVideo(WPARAM l,LPARAM m);
	afx_msg LRESULT OnCallDelVideo(WPARAM,LPARAM);
	afx_msg LRESULT OnCallHold(WPARAM,LPARAM);
	afx_msg LRESULT OnCallUnHold(WPARAM,LPARAM);
	afx_msg LRESULT OnCallMicMute(WPARAM,LPARAM);
	afx_msg LRESULT OnCallMicUnMute(WPARAM,LPARAM);
	afx_msg LRESULT OnCallSpkMute(WPARAM,LPARAM);
	afx_msg LRESULT OnCallSpkUnMute(WPARAM,LPARAM);
	afx_msg LRESULT OnCallStartRec(WPARAM,LPARAM);
	afx_msg LRESULT OnCallEndRec(WPARAM,LPARAM);
	afx_msg LRESULT OnCallBlindTrans(WPARAM,LPARAM);
	afx_msg LRESULT OnCallBlindTransResult(WPARAM,LPARAM);
	afx_msg LRESULT OnShowVideoWnd(WPARAM,LPARAM);
	afx_msg LRESULT OnCallComing(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnCallInfoChange(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnCallDTMF(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnHoldCallResult(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnUNHoldCallResult(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnShowDownloadImage(WPARAM, LPARAM);

	afx_msg LRESULT OnNetLevelNotify(WPARAM,LPARAM);
	afx_msg LRESULT OnNetSTATISTIC(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupNotify(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupInfoChange(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupMemAdd(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupMemDel(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupOwnerChange(WPARAM,LPARAM);	
	afx_msg LRESULT OnGroupMessageWindow(WPARAM,LPARAM);
	afx_msg void OnBnClickedButtonUnfoldvideo();
	afx_msg void OnBnClickedButtonVideocall();
	afx_msg void OnBnClickedButtonCall();
	afx_msg void OnBnClickedButtonEndvideo();
	afx_msg void OnNMRClickListMember(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListMemMenuItem(UINT nID);
	DECLARE_MESSAGE_MAP()

public:
	void SetLoginAccount(const std::string& strAccount){m_strLoginAccount = strAccount;}
	void SetLoginName(const std::string& strName){m_strLoginName = strName,m_stcName.SetWindowText(CTools::UTF2UNICODE(strName));}
	void SetGroupID(const std::string& strGroupID){m_strGroupID = strGroupID;}
	void RefreshWindow(void);
	void RefreshMemberList(const std::string& groupID);
	BOOL FindColum(const CString& cstrKey,int colnum,int& iFind);
	void RefershChairMan(const std::string& strAccount);
	TUP_UINT32 GetCallid() {return m_uiCallID; };
	void CloseDlg(void);
	void EnableCallButton(bool bEnable);

	//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 begin
	void SetDefualtHeadImg();
	void SetGroupHeadImg();
	void SetCallStatus(DLG_TYPE status) {m_DlgType = status,RefreshWindow();};

	BOOL SetUserHeadImg(const IM_S_USERINFO& userInfo);
	BOOL GetUserDefHeadImg(const TUP_CHAR imageID[], IM_S_IMAGEINFO& imgInfo);

	int GetUserHeadImg(const IM_S_USERINFO& userInfo
		, IM_S_IMAGEINFO& imgeInfo
		, CString& strImgPath
		);

	CString GetLocalHeadImg(const TUP_CHAR imageID[]);
	CString GetDefaultHeadImg();
	//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 end
protected:

	////反解码，反压缩收到的消息////
	void ProcessCotentFromeSpaceOrUC(std::string& cotent);

	////组装未压缩的IM消息
	void UnCompMsgFormat(CString& content, CString& sendContent);
	////组装压缩的IM消息
	void ComCodeMsg(std::string& m_strSource, std::string& m_strTarget);
	/////更新对话框消息/////
	int UpdataChatContent(TUP_CHAR account[], TUP_INT64 utcStamp, const CString& chatContent);
	void InsertEmotion(vector<PicPathInfo>& OutImagelist,int Pos);
	/////从UM下载图片，返回下载图片的本地URL/////
	CString DownloadImageFromServerce(UMINFo& m_UMinfo);
	void ResizeImage(LONG& lWidth, LONG& lHeight);
	bool IsMemberInGroup(std::string _account,std::string _groupID);

private:
	std::string m_strLoginAccount;
	std::string m_strLoginName;	
	DLG_TYPE m_DlgType;	         //	对话框类型
	int m_ImagePosition;         //记录截图在本行代码中的位置/////
	CString m_downloadImagePath; ////下载图像本地地址/////
public:
	TUP_UINT32 m_uiCallID;
	TUP_UINT32 m_uiConfID;
	IM_S_USERINFO m_targetUserInfo;
	std::string m_strGroupID;
	CCallCtrlDlg* m_pCallCtrlDlg;
	bool IsVidesponsor;
public:		
	CImageStatic m_stcHead;
	CRichEditCtrlEx m_edtIMContent;
	CRichEditCtrlEx m_edtSend;
	CStatic m_stcName;
	CStatic m_stcCallWnd;
	CButton m_btnUnfold;
	CStatic m_stcRemoteVideo;
	CStatic m_stcLocalVideo;	
	CButton m_btnVideoCall;	
	CButton m_btnCall;	
	CListCtrl m_listMember;	
	CButton m_btnAdd;
	afx_msg void OnBnClickedButtonDataConf();
	bool m_fixGroupChat;
public:
	// ////发布自己状态//////
	bool PubSelfStatus(IM_E_USER_ONLINESTATUS _status);
	CButton m_DataConfCall;
};

