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
#include "stdafx.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ShareStatic.h"

// CDataConfDlg 对话框
typedef struct 
{   
	TUP_ULONG Userid;         ////用户ID
	TUP_UINT32  Devideid;    ///设备ID
	CWnd* m_VideoDisp;       /////视频的wnd
    CWnd* m_NameDisp;        /////姓名的wnd
	bool isValuable;        /////是否可用
} VideoINfo;

typedef struct {
	TUP_INT m_penstyle;                //////画笔类型
	TUP_INT m_linewidth;               /////选择线宽////
	COLORREF m_clr;                     ////画笔颜色//////
}PenInfo;


class CDataConfDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataConfDlg)

public:
	CDataConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataConfDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DATACONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSharedesk();
	afx_msg LRESULT OnJoinDataConfSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnLoadComponetSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfUserAdd(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfUserDEL(WPARAM,LPARAM);
	afx_msg LRESULT OnInviteMemberFailed(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfEnd(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfASGetOwerOK(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfASUpdateScreen(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfASStateShare(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfAddVideoUser(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfDelVideoUser(WPARAM,LPARAM);
	afx_msg LRESULT UpdatePresentInfo(WPARAM,LPARAM);
	afx_msg LRESULT UpdateChairmainInfo(WPARAM,LPARAM);   
	afx_msg LRESULT UpdateMuteInfo(WPARAM,LPARAM);
	afx_msg LRESULT OnDocumentWnd(WPARAM,LPARAM);
	afx_msg LRESULT OnNewDocSuc(WPARAM,LPARAM);
	afx_msg LRESULT OnDelDocSuc(WPARAM,LPARAM);
	afx_msg LRESULT OnNewPageSuc(WPARAM nValue1,LPARAM nValue2);
	afx_msg LRESULT OnDrawWhileBackData(WPARAM nValue1,LPARAM nValue2);
	afx_msg LRESULT OnPageInd(WPARAM nValue1,LPARAM nValue2);
	afx_msg LRESULT OnLayoutChange(WPARAM nValue1,LPARAM nValue2);
	afx_msg LRESULT OnRefreshDocInf(WPARAM nValue1,LPARAM nValue2);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	void StartConf(CALL_S_DATACONF_PARAM* pNotify);
	void AddConfMemBer(TC_Conf_User_Record* pRecord);
	void DleConfMemBer(TC_Conf_User_Record* pRecord);
	void SetConfID(TUP_UINT32 id){ulConfID = id;}
	void SetCallID(TUP_UINT32 id){ulCallID = id;}
	TUP_UINT32 GetConfId(void) {return ulConfID;};
private:
	CONF_HANDLE m_handle;
	TUP_UINT32 ulConfID;
	TUP_UINT32 ulCallID;
	bool m_bisChairMan;
	bool m_bisPresent;
	bool m_bisMute;
	std::string m_ChaMainAccount;
	std::string m_ChairMainBindNum;
	std::string m_PresentAccount;
	std::string m_PresentBindNUm;
	std::string m_OwnerBindNum;          ///共享权限拥有人/////
	typedef std::map<const std::string ,TUP_INT64> LocalMember;  //绑定号码与与会stuffID映射关系
	LocalMember m_LocalMenber;
	int m_RadButChoice;  //0表示没有选择//1表示屏幕，2表示文档，3表示白板，4表示程序，5表示媒体
	CWnd* m_videoDis[6];  /////存放本地视频窗口句柄/////
	VideoINfo m_LocalVideoINfo[6];
	CButton m_btnOpenCammer;
    inline void InitShareButton();
	inline void InitVideoINfo();
	bool AvaluableVudeo(int& Index);
	bool GetVideoINdexByid(int& Index,TUP_ULONG m_Userid);
	bool PubSelfStatus(IM_E_USER_ONLINESTATUS _status);
	void InitSharePlatForm(int ShareID);
	bool CheckShareStatu(int m_choice);
     
private:
	///////文档共享部分变量//////
	TUP_UINT32 m_curDoc;
	TUP_UINT32 m_curPage;
	CListCtrl m_DocOrBoardList;
	CComboBox m_PenType;
    CComboBox m_LineWidth;
	CComboBox m_comSelectPage;
	PenInfo m_penInfo;
	bool  m_laserBegin;
	TC_POINT m_ptOrg;
	std::vector<TUP_UINT32> m_selectAnnots;   ////选中的标记//////////
	void UpdatePenInfo(PenInfo m_penInfo);   ////更新画笔颜色，线宽////
	void UpdateDocInfo(TUP_UINT32 m_DocID);
	int GetDocumentIndex(TUP_UINT32 m_DocID);   ////检索文档在列表中的ID，若不存在，返回-1////
	void InitWhiteBackElement();
	bool IsAnnotSelected(TUP_UINT32 docId, TUP_UINT32 pageId, TUP_UINT32 id)
	{
		if(docId != m_curDoc || pageId != m_curPage)
		{
			return false;
		}

		size_t len = m_selectAnnots.size();
		for(size_t i = 0; i < len; i++)
		{
			if(m_selectAnnots[i] == id)
			{
				return true;
			}
		}

		return false;
	}
	void UnSelectAnnots(bool bRedraw);
	void SelectAnnot(TUP_UINT32* ids, int count);

public:
	CListCtrl m_DataConfMem;
	CStatic m_stcStatusTxt;
	CEdit m_edtChairMan;
	CEdit m_edtPresenter;
	CButton m_btnSharDesk;
	CButton m_btnGetPresenterRole;
	CShareStatic m_stcDeskTop;
	CStatic m_stcShareState;
	CStatic m_stcVideo1;
	CStatic m_stcVideo2;
	CStatic m_stcVideo3;
	CStatic m_stcVideo4;
	CStatic m_stcVideo5;
	CStatic m_stcVideo6;
	CStatic m_stcVideo7;
	CStatic m_PresentOrChairmanVideo;
	afx_msg void OnBnClickedButtonGetPrensnt();
	afx_msg void OnBnClickedButtonOpenvideo();
	bool getAccountINfoByBingNum(std::string _phoneID, IM_S_USERINFO& _userInfo);
	bool getAccountINfoByAccount(std::string _account, IM_S_USERINFO& _userInfo);
	bool GetUserBindNumByid(TUP_ULONG id ,std::string& BindNum);
	bool SetUseridByBindNum(std::string BindNum,TUP_ULONG id);
	TUP_UINT64 GetUserIDByBindNum(std::string BindNum);
	bool IsInconf(std::string BindNum);
	afx_msg void OnBnClickedBtAdd();
	afx_msg void OnBnClickRadio(UINT idCtl);
	void InitiMenberlist(TUP_UINT32 m_ConfID,std::string strGroupID);//////点对点数据会，语音会议转成的数据会议处理模式不一样////
	afx_msg void OnNMRClickListDataconfMember(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListMemMenu(UINT nID);
	afx_msg void OnBnClickedBtConfmute();
	void UpdateMuteInfo();
	bool isChairManOrPresent(const CString& cstrName);
	CComboBox m_DataComBox;
public:
	afx_msg void OnBnClickedBtOpenNew();
	afx_msg void OnBnClickedBtSelectcolor();
	afx_msg void OnBnClickedBtNewpage();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCombActiontype();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnNMDblclkListDoc(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtDeldoc();
	afx_msg void OnBnClickedBtSalve();
	afx_msg void OnBnClickedBtLoad();
	afx_msg void OnBnClickedBtCopypage();
	afx_msg void OnBnClickedBtDelpage();
	afx_msg void OnBnClickedBtPrepage();
	afx_msg void OnBnClickedBtNextpage();
	afx_msg void OnCbnSelchangeCombSelect();
	afx_msg void OnBnClickedBtUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtCalcle();
	afx_msg void OnBnClickedBtDel();
};
