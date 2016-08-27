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


// eSDK_TUP_PC_VIDEO_DemoDlg.h : header file
//

#pragma once
#include <string>
#include "afxwin.h"
#include "EntAddrDlg.h"
#include "Data.h"
#include "FullScreenModelDlg.h"
#include "ShowModalDialog.h"
#include <vector>

struct VideoUserInfo
{
	CONF_HANDLE		confHandle;// ������
	IM_S_USERINFO	userInfo;// �˻���Ϣ
	TUP_INT32		deviceID;// �豸ID
	HWND			videoHwnd;// �󶨵Ĵ��ھ��
};

// CeSDK_TUP_PC_VIDEO_DemoDlg dialog
class CeSDK_TUP_PC_VIDEO_DemoDlg : public CDialogEx, public CUserQueryHelper
{
// Construction
public:
	CeSDK_TUP_PC_VIDEO_DemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CeSDK_TUP_PC_VIDEO_DemoDlg();
// Dialog Data
	enum { IDD = IDD_ESDK_TUP_PC_VIDEO_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	
protected:
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAgainInviteAddConf();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonLoginin();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonAddMember();
	afx_msg void OnBnClickedButtonDelMember();
	afx_msg void OnBnClickedButtonStartConf();
	afx_msg void OnBnClickedButtonTurnonVideo();
	afx_msg void OnBnClickedButtonEndConf();
	afx_msg void OnNMRClickListMembers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabVideoModal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnCloseEntAddrDlg(WPARAM,LPARAM);
	afx_msg LRESULT OnConfAddMemFail(WPARAM, LPARAM);
	afx_msg LRESULT OnConfAddMemSuccess(WPARAM, LPARAM);
	afx_msg LRESULT OnConfCreate(WPARAM, LPARAM);
	afx_msg LRESULT OnConfConnect(WPARAM, LPARAM);
	afx_msg LRESULT OnConfInComing(WPARAM, LPARAM);
	afx_msg LRESULT OnDataBeKickedFromConf(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfAddVideoUser(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfCreate(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfDelVideoUser(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfLayoutChange(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfUserAdd(WPARAM, LPARAM);
	afx_msg LRESULT OnDataConfUserDel(WPARAM, LPARAM);
	afx_msg LRESULT OnJoinDataConfSuccess(WPARAM, LPARAM);
	afx_msg LRESULT OnRefreshMemList(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateConatct(WPARAM,LPARAM);
	afx_msg LRESULT OnUserBeKickOut(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	// �ؼ����ͱ���
public:
	CButton							m_btnAddMember;
	CButton							m_btnDelConf;
	CButton							m_btnDelMember;
	CButton							m_btnEndConf;
	CButton							m_btnLogin;
	CButton							m_btnStartConf;
	CButton							m_btnTrunOnVideo;
	CComboBox						m_DataComBox;
	CEdit							m_editAccount;
	CEdit							m_editCONFCallAccount;
	CEdit							m_editCONFStatus;
	CEdit							m_editCONFTime;
	CEdit							m_editCONFTitle;
	CEdit							m_editPort;
	CEdit							m_editPSD;
	CIPAddressCtrl					m_ipAddress;
	CListCtrl						m_listMemberList;
	CTabCtrl						m_tabVideoModal;

	// ��ͨ���ͱ���
public:
	typedef std::map<const std::string ,TUP_INT64> LocalMember;  // �󶨺��������stuffIDӳ���ϵ
	typedef std::map<CONF_HANDLE, std::vector<VideoUserInfo> > MapFullScreenVideoUserInfo;// ��������ȫ��ģʽ����Ƶ�û�ӳ���ϵ
	typedef std::vector<VideoUserInfo> VecFullScreenVideoUserInfo;// ��������ȫ��ģʽ��������Ƶ�û������Ϣ
	typedef std::map<CONF_HANDLE, std::vector<VideoUserInfo> > MapShowModalVideoUserInfo;// ��������չʾģʽ����Ƶ�û�ӳ���ϵ
	typedef std::vector<VideoUserInfo> VecShowModalVideoUserInfo;// ��������չʾģʽ��������Ƶ�û������Ϣ

	BOOL							m_bVideoFlag;
	BOOL							m_bLoginFlag;
	std::string						m_ChairMainBindNum;
	std::string						m_ChaMainAccount;
	CString							m_cstrAccount;
	BOOL							m_isChairman;
	CONF_HANDLE						m_handle;
	IM_S_USERINFO					*m_pCurrentUserInfo;
	LocalMember						m_LocalMenber;
	MapFullScreenVideoUserInfo		m_mapFullScreenVideoUserInfo;
	MapShowModalVideoUserInfo		m_mapShowModalVideoUserInfo;
	CEntAddrDlg						*m_pEntAddDlg;
	CFullScreenModelDlg				*m_pFullScreenModelDlg;
	std::string						m_PresentAccount;
	std::string						m_PresentBindNUm;
	CShowModalDialog				*m_pShowModalDlg;
	std::string						m_strSipAccount;
	std::string						m_strDataConfAddr;
	IM_S_USERINFO					m_targetUserInfo;
	TUP_UINT32						m_uiCallID;
	TUP_UINT32						m_uiConfID;
	VecFullScreenVideoUserInfo		m_vecFullScreenVideoUserInfo;
	VecShowModalVideoUserInfo		m_vecShowModalScreenVideoUserInfo;

public:
	BOOL AvaluableFullScreenVideo(int &Index);// ��ѯĿǰ�Ƿ񻹴��ڿ��õ���Ƶ����
	void ClearFullScreenNameText();
	void DisableRelativeControls();// ������ؿؼ�
	void EnableRelativeControls();// ������ؿؼ�
	void UpdateVideoUI(int iIndex);// ˢ����Ƶ����
	BOOL FindColum(const CString& cstrKey,int column,int& iFind);// ��������ֵ(column)��ѯ��Ӧֵ
	BOOL GetUserBindNumByid(TUP_ULONG id ,std::string& BindNum);// ͨ���û�ID��ѯ�Ƿ��������
	BOOL IsInconf(std::string BindNum);// �ж��Ƿ��ڻ�����
	BOOL getAccountINfoByBingNum(std::string _phoneID, IM_S_USERINFO& _userInfo);// ͨ���󶨺����ѯ�û���ϸ��Ϣ
	BOOL GetVideoINdexByid(int& Index,TUP_ULONG m_Userid);// ͨ���û�ID��ѯ�����Ƶ����
	BOOL SetUseridByBindNum(std::string BindNum,TUP_ULONG id);// �����û��󶨺��������û�ID
};
