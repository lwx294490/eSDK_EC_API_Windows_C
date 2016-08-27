
// eSDK_TUP_PC_DeskShare_DemoDlg.h : header file
//

#pragma once
#include "NotifyCallBack.h"
#include "Tools.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <map>
#include "ShareStatic.h"


const int WIDTH = 505;
const int HEITH = 650;
const int DESKSHOW_WIDTH = 1350;

typedef enum GROUPLIST_COLUMNID
{
	COL_MEM_NAME,
	COL_MEM_ACCOUNT,
	COL_MEM_STATUS
};
typedef enum MEETCONNECT_COLUMNID
{
	MEET_INIT,			//初始状态
	MEET_IDLE,			//空闲
	MEET_REQUEST,		//发起呼叫请求
	MEET_INCOMING,		//来电
	MEET_CONNECTED,		//普通会议中
	DATAMEET_CONNECTED	//数据会议中

};
typedef std::map<std::string, std::string> MAP_MEET_MEMBER;

typedef std::map<std::string, IM_S_USERINFO> MAP_MEET_MEMBERS;

// CeSDK_TUP_PC_DeskShare_DemoDlg dialog
class CeSDK_TUP_PC_DeskShare_DemoDlg : public CDialogEx
{
// Construction
public:
	CeSDK_TUP_PC_DeskShare_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ESDK_TUP_PC_DESKSHARE_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit m_editLoginAccount;
	CEdit m_editLoginPassword;
	CIPAddressCtrl m_ipCtrlServerIP;
	CEdit m_editServerPort;
	CButton m_btnLogin;
	CEdit m_editMeetStatus;
	CEdit m_editMeetCompere;
	CEdit m_editMeetTime;
	CEdit m_editMeetSpeaker;
	CListCtrl m_listMeetMember;
	CButton m_btnMeetStart;
	CButton m_btnMeetEnd;
	CButton m_btnShareStart;
	CButton m_btnShareEnd;
	CEdit m_editTargetAccount;
	CButton m_btnAddMember;
	CButton m_btnDelMember;
	CEdit m_editComingAccount;
	CButton m_btnFullScreen;
	CButton m_btnAcceptMeet;
	CButton m_btnReFuseMeet;
	CButton m_btnLeaveMeet;
	CButton m_btnLogOff;
	CButton m_btnLogOut;
	MAP_MEET_MEMBER  m_mapMeetMember;
	MAP_MEET_MEMBERS m_mapMeetMembers;
	CONF_HANDLE m_handle;
	bool bLoginFlag;
	bool bChairmanFlag;
	bool m_bisPresent;
	bool bInMeetFlag;
	bool bInDataConfFlag;
	std::string m_strSipAccount;
	CString cstrOwnAccount;
	std::string m_PresentBindNUm;
	std::string m_PresentAccount;
	std::string strOwnName;
	std::string strOwnBindNO;
	std::string strOwnDataConfAddr;
	TUP_INT64 strOwnUserID;
	std::string m_strGroupID;
	TUP_UINT32 m_uiConfID;
	TUP_UINT32 m_uiCallID;
	std::string m_OwnerBindNum;          ///共享权限拥有人/////
	typedef std::map<const std::string ,TUP_INT64> LocalMember;  //绑定号码与与会stuffID映射关系
	std::string m_ChairMainBindNum;
	std::string m_ChaMainAccount;
	LocalMember m_LocalMenber;

private:
	bool LoginUCService(void);
	bool LoginCallService(void);
	void SetLoginSectionCtrl(bool bState);
	void SetLogOutSectionCtrl(bool bState);
	void ListMemberInit();
	void SetShareSectionCtrl(int iCallStatus);
	bool ListCtrlAndMapAddMember(const CString& AddMemberAccount);
	bool MemberListFindColum(const CString& cstrKey, int iColnum, int& iFind);
	bool getUserInfoByAccount(std::string _account, IM_S_USERINFO& _userInfo);
	bool getUserInfoByBindNo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo);
	void LogoutService();
	void ResourceClear();
	bool InviteNewMember(const CString& cstrTargetAccount);
	bool MemberListMapFindByBindNo(std::string& strAccount, const std::string& strBindNo);
	bool AddOtherMeetMember();

public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMemberAdd();
	afx_msg void OnBnClickedButtonMemberDelete();
	afx_msg void OnBnClickedButtonMeetStart();
	afx_msg void OnBnClickedButtonMeetEnd();
	afx_msg void OnBnClickedButtonMeetLeave();
	afx_msg void OnBnClickedButtonMeetRefuse();
	afx_msg void OnBnClickedButtonMeetAccept();
	afx_msg void OnBnClickedButtonLogoff();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT MeetCreateSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT MeetInvite(WPARAM wParam, LPARAM lParam);
	LRESULT MeetMemberJoined(WPARAM wParam, LPARAM lParam);
	LRESULT MeetMemberRefresh(WPARAM wParam, LPARAM lParam);
	LRESULT MeetEnded(WPARAM wParam, LPARAM lParam);
	LRESULT MeetShowSpkMember(WPARAM wParam, LPARAM lParam);
	LRESULT ManagetConnect(WPARAM wParam, LPARAM lParam);
	LRESULT DataConfCreate(WPARAM wParam, LPARAM lParam);
	LRESULT DataConfJoinSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonStartShare();
	afx_msg void OnBnClickedButtonFullScreen();
	afx_msg LRESULT OnUserBeKickOut(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfASGetOwerOK(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfASUpdateScreen(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfASStateShare(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfUserAdd(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfUserDEL(WPARAM,LPARAM);
	afx_msg LRESULT UpdatePresentInfo(WPARAM,LPARAM);
	afx_msg LRESULT UpdateChairmainInfo(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfEnd(WPARAM,LPARAM);

	void AddConfMemBer(TC_Conf_User_Record* pRecord);
	//void DleConfMemBer(TC_Conf_User_Record* pRecord);
	bool SetUseridByBindNum(std::string BindNum,TUP_ULONG id);
	bool GetUserBindNumByid(TUP_ULONG id ,std::string& BindNum);
	bool getAccountINfoByBingNum(std::string _phoneID, IM_S_USERINFO& _userInfo);
	TUP_UINT64 GetUserIDByBindNum(std::string BindNum);
	CShareStatic m_stcDeskTop;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonEndShare();
	CButton m_toShareDesk;
	afx_msg void OnBnClickedButton2();
	CButton m_getPresent;
	int m_dlgModel;
};
