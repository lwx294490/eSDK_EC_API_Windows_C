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


// eSDK_TUP_PC_VIDEO_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "eSDK_TUP_PC_VIDEO_DemoDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include "NotifyCallBack.h"
#include "NewDialog.h"

const int HEARTBEAT_TIME = 30000;	 // ���ʱ��30��
const int HEART_BEAT_TIMEID = 1000;	 // ������ʱ��ID

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
//************************************************************************
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
//************************************************************************
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
//************************************************************************
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//************************************************************************
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
//************************************************************************

// CeSDK_TUP_PC_VIDEO_DemoDlg dialog



//************************************************************************
CeSDK_TUP_PC_VIDEO_DemoDlg::CeSDK_TUP_PC_VIDEO_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CeSDK_TUP_PC_VIDEO_DemoDlg::IDD, pParent)
	, m_pEntAddDlg(NULL)
	, m_bLoginFlag(FALSE)
	, m_bVideoFlag(FALSE)
	, m_handle(0)
	, m_strSipAccount("")
	, m_ChairMainBindNum("")
	, m_ChaMainAccount("")
	, m_PresentAccount("")
	, m_PresentBindNUm("")
	, m_uiCallID(0)
	, m_uiConfID(0)
	, m_pFullScreenModelDlg(NULL)
	, m_pShowModalDlg(NULL)
	, m_pCurrentUserInfo(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
//************************************************************************
CeSDK_TUP_PC_VIDEO_DemoDlg::~CeSDK_TUP_PC_VIDEO_DemoDlg()
{
	SAFE_DELETE(m_pFullScreenModelDlg);
	SAFE_DELETE(m_pShowModalDlg);
	SAFE_DELETE(m_pCurrentUserInfo);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPSD);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddress);
	DDX_Control(pDX, IDC_LIST_MEMBERS, m_listMemberList);
	DDX_Control(pDX, IDC_BUTTON_LOGININ, m_btnLogin);
	DDX_Control(pDX, IDC_BUTTON_ADD_MEMBER, m_btnAddMember);
	DDX_Control(pDX, IDC_BUTTON_DEL_MEMBER, m_btnDelMember);
	DDX_Control(pDX, IDC_BUTTON_TURNON_VIDEO, m_btnTrunOnVideo);
	DDX_Control(pDX, IDC_BUTTON_START_CONF, m_btnStartConf);
	DDX_Control(pDX, IDC_BUTTON_END_CONF, m_btnEndConf);
	DDX_Control(pDX, IDC_COMBO_VIDEO, m_DataComBox);
	DDX_Control(pDX, IDC_EDIT_CONF_STATUS, m_editCONFStatus);
	DDX_Control(pDX, IDC_EDIT_CONF_TIME, m_editCONFTime);
	DDX_Control(pDX, IDC_EDIT_CONF_TITLE, m_editCONFTitle);
	DDX_Control(pDX, IDC_EDIT_CONF_CALL_ACCOUNT, m_editCONFCallAccount);
	DDX_Control(pDX, IDC_TAB_VIDEO_MODAL, m_tabVideoModal);
}
//************************************************************************
BEGIN_MESSAGE_MAP(CeSDK_TUP_PC_VIDEO_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOGININ, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonLoginin)
	ON_MESSAGE(WM_CLOSE_ENT_DLG,&CeSDK_TUP_PC_VIDEO_DemoDlg::OnCloseEntAddrDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MEMBER, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonAddMember)
	ON_MESSAGE(WM_UPDATE_CONTACT,&CeSDK_TUP_PC_VIDEO_DemoDlg::OnUpdateConatct)
	ON_BN_CLICKED(IDC_BUTTON_DEL_MEMBER, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonDelMember)
	ON_BN_CLICKED(IDC_BUTTON_START_CONF, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonStartConf)
	ON_BN_CLICKED(IDC_BUTTON_TURNON_VIDEO, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonTurnonVideo)
	ON_MESSAGE(WM_USER_KICKOUT, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnUserBeKickOut)
	ON_MESSAGE(WM_CONF_CREATE_RET, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfCreate)
	ON_MESSAGE(WM_CONF_CONNECTED,&CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfConnect)
	ON_MESSAGE(WM_CONF_INCMING, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfInComing)
	ON_MESSAGE(WM_CONF_ADD_MEM_SUC, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfAddMemSuccess)
	ON_MESSAGE(WM_CONF_ADD_MEM_FAIL, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfAddMemFail)
	ON_MESSAGE(WM_DATACONF_CREAT, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfCreate)
	ON_MESSAGE(WM_DATACONF_JOINSUCCESS, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnJoinDataConfSuccess)
	ON_MESSAGE(WM_DATACONF_ADD_VIDEO, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfAddVideoUser)
	ON_MESSAGE(WM_DATACONF_DEL_VIDEO, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfDelVideoUser)
	ON_MESSAGE(WM_DATACONF_USER_ADD, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfUserAdd)
	ON_MESSAGE(WM_DATACONF_USER_DEL, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfUserDel)
	ON_MESSAGE(WM_CONF_REFESH_LIST, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnRefreshMemList)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_END_CONF, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonEndConf)
	ON_MESSAGE(WM_DATACONF_END, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataBeKickedFromConf)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VIDEO_MODAL, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnTcnSelchangeTabVideoModal)
	ON_MESSAGE(WM_CONF_LAYOUT_CHANGE, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfLayoutChange)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MEMBERS, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnNMRClickListMembers)
	ON_COMMAND(ID_32772, &CeSDK_TUP_PC_VIDEO_DemoDlg::OnAgainInviteAddConf)
	ON_WM_TIMER()
END_MESSAGE_MAP()
//************************************************************************
// CeSDK_TUP_PC_VIDEO_DemoDlg message handlers
//************************************************************************
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::AvaluableFullScreenVideo(int &Index)
{
	///////��ѯĿǰ�Ƿ񻹴��ڿ��õ���Ƶ����///////
	for (int i = 0; i<9; i++)
	{
		if (m_pFullScreenModelDlg->FullScreenModeInfo[i].isValuable)
		{
			Index = i;
			return TRUE;
		}
	}

	return FALSE;
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::ClearFullScreenNameText()
{
	if (NULL != m_pFullScreenModelDlg)
	{
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME0)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME1)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME2)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME3)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME4)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME5)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME6)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME7)->SetWindowText(_T(""));
		m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME8)->SetWindowText(_T(""));
	}
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::DisableRelativeControls()
{
	// ���õ�¼��Ϣ��ؿؼ�
	m_editAccount.EnableWindow(TRUE);
	m_editPort.EnableWindow(TRUE);
	m_editPSD.EnableWindow(TRUE);
	m_ipAddress.EnableWindow(TRUE);

	// ���������ؼ�
	m_btnAddMember.EnableWindow(FALSE);
	m_btnDelMember.EnableWindow(FALSE);
	m_btnTrunOnVideo.EnableWindow(FALSE);
	m_btnStartConf.EnableWindow(FALSE);
	m_btnEndConf.EnableWindow(FALSE);
	m_DataComBox.EnableWindow(FALSE);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::EnableRelativeControls()
{
	// ���õ�¼��Ϣ��ؿؼ�
	m_editAccount.EnableWindow(FALSE);
	m_editPort.EnableWindow(FALSE);
	m_editPSD.EnableWindow(FALSE);
	m_ipAddress.EnableWindow(FALSE);

	// ���������ؼ�
	m_btnAddMember.EnableWindow(TRUE);
	m_btnDelMember.EnableWindow(TRUE);
	m_btnStartConf.EnableWindow(TRUE);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::UpdateVideoUI(int iIndex)
{
	m_tabVideoModal.SetCurSel(iIndex);
	switch (iIndex)
	{
	case 0:
		{
			VecShowModalVideoUserInfo::iterator iShowBegin = m_vecShowModalScreenVideoUserInfo.begin();
			VecShowModalVideoUserInfo::iterator iShowEnd = m_vecShowModalScreenVideoUserInfo.end();
			VecFullScreenVideoUserInfo::iterator iFullBegin = m_vecFullScreenVideoUserInfo.begin();
			VecFullScreenVideoUserInfo::iterator iFullEnd = m_vecFullScreenVideoUserInfo.end();
			if (m_handle)
			{
				for (; iShowBegin != iShowEnd; iShowBegin++)
				{
					tup_conf_video_detach(iShowBegin->confHandle, (TUP_INT32)iShowBegin->userInfo.staffID, iShowBegin->deviceID, iShowBegin->videoHwnd, TUP_FALSE);
				}

				for (; iFullBegin != iFullEnd; iFullBegin++)
				{
					tup_conf_video_attach(iFullBegin->confHandle, (TUP_INT32)iFullBegin->userInfo.staffID, iFullBegin->deviceID, iFullBegin->videoHwnd, TUP_TRUE, 0);
				}
			}
			m_pFullScreenModelDlg->ShowWindow(SW_SHOW);
			m_pShowModalDlg->ShowWindow(SW_HIDE);
			m_pFullScreenModelDlg->Invalidate(TRUE);
		}
		break;
	case 1:
		{
			VecShowModalVideoUserInfo::iterator iShowBegin = m_vecShowModalScreenVideoUserInfo.begin();
			VecShowModalVideoUserInfo::iterator iShowEnd = m_vecShowModalScreenVideoUserInfo.end();
			VecFullScreenVideoUserInfo::iterator iFullBegin = m_vecFullScreenVideoUserInfo.begin();
			VecFullScreenVideoUserInfo::iterator iFullEnd = m_vecFullScreenVideoUserInfo.end();
			if (m_handle)
			{
				for (; iFullBegin != iFullEnd; iFullBegin++)
				{
					tup_conf_video_detach(iFullBegin->confHandle, (TUP_INT32)iFullBegin->userInfo.staffID, iFullBegin->deviceID, iFullBegin->videoHwnd, TUP_FALSE);
				}

				for (; iShowBegin != iShowEnd; iShowBegin++)
				{
					tup_conf_video_attach(iShowBegin->confHandle, (TUP_INT32)iShowBegin->userInfo.staffID, iShowBegin->deviceID, iShowBegin->videoHwnd, TUP_TRUE, 0);
				}
			}
			m_pFullScreenModelDlg->ShowWindow(SW_HIDE);
			m_pShowModalDlg->ShowWindow(SW_SHOW);

			// �����ϯ�Ǳ��ˣ�����չʾģʽ�£�ֻ��ʾ��ϯ��Ƶ
			if (m_ChairMainBindNum == g_BindNO)
			{
				m_pShowModalDlg->GetDlgItem(IDC_STATIC_SHOW_LOCAL)->ShowWindow(FALSE);
			}
			// �ж��Ƿ�򿪱�����Ƶ
			if ((g_BindNO != m_ChairMainBindNum) && (m_bVideoFlag))
			{
				m_pShowModalDlg->GetDlgItem(IDC_STATIC_SHOW_LOCAL)->ShowWindow(TRUE);
			}
			else if ((g_BindNO != m_ChairMainBindNum) && (!m_bVideoFlag))
			{
				m_pShowModalDlg->GetDlgItem(IDC_STATIC_SHOW_LOCAL)->ShowWindow(FALSE);
			}
			m_pShowModalDlg->Invalidate(TRUE);
		}
		break;
	}
}
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::FindColum(const CString& cstrKey,int iColumn,int& iFind)
{
	int iSize = m_listMemberList.GetItemCount();
	for(int i = 0; i< iSize; i++)
	{
		if(cstrKey.Compare(m_listMemberList.GetItemText(i,iColumn)) == 0)
		{
			iFind = i;
			return TRUE;
		}
	}
	return FALSE;
}
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::getAccountINfoByBingNum( std::string _phoneID, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	memset(&arg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
	memset(&ack,0,sizeof(IM_S_QUERY_USERINFO_ACK));
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _phoneID.c_str());
	arg.type = IM_E_IMUSERQUERYTYPE_BY_BINDNO;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"Query Account Failed");
		return FALSE;
	}

	BOOL bRet = FALSE;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (strcmp(curUserInfo.bindNO, _phoneID.c_str()) == 0)
		{
			_userInfo = curUserInfo;
			bRet = TRUE;
			break;
		}

		pUserList = pUserList->next;
	}
	/////�ͷ�IM_S_QUERY_USERINFO_ACK��TUPLISTָ��////
	tup_im_release_tup_list(ack.userList);

	if(!bRet)
	{
		AfxMessageBox(L"Query Account Failed");
		return FALSE;
	}

	return TRUE;
}

//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::GetUserBindNumByid(TUP_ULONG id ,std::string& BindNum)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (id == iter->second)
		{
			BindNum = iter->first; 
			return TRUE ;
		}
	}
	return FALSE;
}
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::GetVideoINdexByid(int& Index,TUP_ULONG m_Userid)
{
	for (int i = 0; i<9; i++)
	{
		if (m_Userid == m_pFullScreenModelDlg->FullScreenModeInfo[i].UserID)
		{
			Index = i;
			return TRUE;
		}
	}

	return FALSE;
}
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::IsInconf(std::string BindNum)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			return TRUE ;
		}
	}
	return FALSE;
}
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::SetUseridByBindNum(std::string BindNum,TUP_ULONG id)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			iter->second = id; 
			return TRUE ;
		}

	}

	return FALSE;
}
//************************************************************************
BOOL CeSDK_TUP_PC_VIDEO_DemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// ��ʼ����¼�Ի���
	m_editAccount.SetWindowText(_T("chenensheng01"));
	m_editPSD.SetWindowText(_T("huawei.123"));
	m_editPort.SetWindowText(_T("8011"));
	m_ipAddress.SetAddress(172, 22, 9, 42);

	// ����ListCtrl�ؼ����
	LONG lStyle;
	lStyle = GetWindowLong(m_listMemberList.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	//lStyle |= LVS_SINGLESEL;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listMemberList.m_hWnd, GWL_STYLE, lStyle);

	// ����ListCtrl�ؼ���չ���
	DWORD dwStyle = m_listMemberList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;// ������
	m_listMemberList.SetExtendedStyle(dwStyle);

	// ����ListCtrl�б�ͷ
	m_listMemberList.InsertColumn(COL_MEM_ID, _T("ID"), LVCFMT_LEFT, 55);
	m_listMemberList.InsertColumn(COL_MEM_ACCOUNT, _T("�˺�"), LVCFMT_LEFT, 50);
	m_listMemberList.InsertColumn(COL_MEM_STATUS, _T("����״̬"), LVCFMT_LEFT, 65);
	m_listMemberList.InsertColumn(COL_MEM_HOST, _T("������"), LVCFMT_LEFT, 55);
	m_listMemberList.InsertColumn(COL_MEM_KeynoteSpeaker, _T("������"), LVCFMT_LEFT, 55);

	m_tabVideoModal.InsertItem(0, _T("ȫ���᳡"));
	m_tabVideoModal.InsertItem(1, _T("��Ƶչʾ"));

	if (NULL == m_pFullScreenModelDlg)
	{
		m_pFullScreenModelDlg = new CFullScreenModelDlg();
	}
	m_pFullScreenModelDlg->Create(IDD_DIALOG_FULLSCREEN_MODEL, &m_tabVideoModal);

	if (NULL == m_pShowModalDlg)
	{
		m_pShowModalDlg = new CShowModalDialog();
	}
	m_pShowModalDlg->Create(IDD_DIALOG_SHOW_MODAL, &m_tabVideoModal);

	CRect rc;
	m_tabVideoModal.GetClientRect(&rc);
	rc.top += 25;
	rc.left += 3;
	rc.bottom -= 3;
	rc.right -= 3;
	m_pShowModalDlg->MoveWindow(&rc, TRUE);
	m_pShowModalDlg->ShowWindow(SW_NORMAL);
	m_pFullScreenModelDlg->MoveWindow(&rc, TRUE);
	m_pFullScreenModelDlg->ShowWindow(SW_NORMAL);
	m_tabVideoModal.SetCurSel(0);

	m_vecFullScreenVideoUserInfo.empty();
	m_mapFullScreenVideoUserInfo.empty();
	m_vecShowModalScreenVideoUserInfo.empty();
	m_mapShowModalVideoUserInfo.empty();

	m_editAccount.LimitText(IM_D_MAX_ACCOUNT_LENGTH);
	m_editPSD.LimitText(IM_D_MAX_PASSWORD_LENGTH);
	m_editPort.LimitText(10);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
//************************************************************************
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnBnClickedButtonEndConf();
	Sleep(500);
	TUP_RESULT tRet = TUP_FALSE;
	// ע�����з�����
	if (!m_strSipAccount.empty())
	{
		tRet = tup_call_deregister(m_strSipAccount.c_str());
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_deregister failed!"));
		}
		m_strSipAccount = "";
	}

	// ע��IM������
	tRet = tup_im_setcancelsendingmessage();
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
	}

	tRet = tup_im_logout();
	if (tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("tup_im_logout failed!"));
	}

	tRet = tup_im_setdispatchmessage(TUP_FALSE);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
	}

	CDialogEx::OnClose();
}
//************************************************************************
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CeSDK_TUP_PC_VIDEO_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonAddMember()
{
	// TODO: Add your control notification handler code here
	m_pEntAddDlg->ShowWindow(SW_SHOW);
	m_pEntAddDlg->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonDelMember()
{
	// TODO: Add your control notification handler code here
	int nItem = -1;
	POSITION pos = m_listMemberList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		while (pos != NULL)
		{
			nItem = m_listMemberList.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			CString cstrAccount = m_listMemberList.GetItemText(nItem, COL_MEM_ACCOUNT);
			std::string memAccount;
			memAccount = CTools::UNICODE2UTF(cstrAccount);

			int nResult = memAccount.compare(g_Account);
			if (nResult == 0)
			{
				AfxMessageBox(_T("Your Account��"));
				return;
			}
			m_listMemberList.DeleteItem(nItem);

			MAP_USER::iterator ibegin = g_mapUser.begin();
			MAP_USER::iterator iend = g_mapUser.end();
			for (; ibegin != iend; ++ibegin)
			{
				nResult = memAccount.compare(std::string(ibegin->second.account));
				if (nResult == 0)
				{
					if (0 != m_uiConfID)
					{
						IM_S_USERINFO userInfo;
						getAccountINfoByBingNum(std::string(ibegin->second.bindNO), userInfo);
						tup_conf_user_kickout(m_handle, (TUP_INT32)(userInfo.staffID));
						tup_call_serverconf_kick_attendee(m_uiConfID, ibegin->second.bindNO);
					}
					g_mapUser.erase(ibegin);
					break;
				}
			}
			pos = m_listMemberList.GetFirstSelectedItemPosition();
		}
	}
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonEndConf()
{
	// TODO: Add your control notification handler code here
	// �رջ���
	if (m_handle != 0)
	{
		// �ر���Ƶ
		CString cstrVideo;
		m_btnTrunOnVideo.GetWindowText(cstrVideo);
		if (cstrVideo == _T("�ر���Ƶ"))
		{
			m_btnTrunOnVideo.SetWindowText(_T("������Ƶ"));
			m_bVideoFlag = FALSE;
		}

		TUP_RESULT tRet = TUP_FAIL;
		if (m_isChairman)
		{
			tRet = tup_conf_terminate(m_handle);
		}
		else
		{
			tRet = tup_conf_leave(m_handle);
		}
		tup_conf_release(m_handle);
		m_handle = 0;
	}

	// �ر���������
	if (m_uiCallID != 0)
	{
		tup_call_end_call(m_uiCallID);
		m_uiCallID = 0;
	}

	// �ر����ݻ���
	if (m_uiConfID != 0)
	{
		if (m_isChairman)
		{
			tup_call_serverconf_end(m_uiConfID);
		}
		else
		{
			tup_call_serverconf_leave(m_uiConfID);
		}
		m_uiConfID = 0;
	}

	m_LocalMenber.clear();
	g_mapUser.clear();
	m_handle = 0;
	m_isChairman = FALSE;
	m_ChairMainBindNum = "";
	m_ChaMainAccount = "";
	m_uiConfID = 0;
	m_uiCallID = 0;
	m_editCONFStatus.SetWindowText(_T(""));
	m_editCONFCallAccount.SetWindowText(_T(""));
	m_btnStartConf.EnableWindow(TRUE);
	m_btnEndConf.EnableWindow(FALSE);
	m_btnAddMember.EnableWindow(TRUE);
	m_btnDelMember.EnableWindow(TRUE);
	m_DataComBox.SetCurSel(-1);
	m_DataComBox.ResetContent();
	m_DataComBox.EnableWindow(FALSE);
	m_btnTrunOnVideo.EnableWindow(FALSE);
	m_listMemberList.DeleteAllItems();
	m_pFullScreenModelDlg->InitVideoInfo();
	m_pShowModalDlg->InitVideoInfo();
	ClearFullScreenNameText();
	Invalidate(TRUE);

	if (NULL != m_pCurrentUserInfo)
	{
		g_mapUser.insert(std::make_pair(g_UserID, *m_pCurrentUserInfo));
		//////���Լ���������б��з�������б���û���Լ�  c00327158 2015-11-28 Start/////
		m_listMemberList.InsertItem(0, CTools::UTF2UNICODE(std::string(m_pCurrentUserInfo->bindNO)));
		m_listMemberList.SetItemText(0, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(g_Account));
		////���Լ����뱾�ػ����¼�б���////
		m_LocalMenber[m_pCurrentUserInfo->bindNO] = m_pCurrentUserInfo->staffID;
		//////���Լ���������б��з�������б���û���Լ�  c00327158 2015-11-28 End/////
	}

}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonLoginin()
{
	m_vecFullScreenVideoUserInfo.empty();
	m_mapFullScreenVideoUserInfo.empty();
	m_vecShowModalScreenVideoUserInfo.empty();
	m_mapShowModalVideoUserInfo.empty();
	// TODO: Add your control notification handler code here
	if (m_bLoginFlag)
	{
		OnBnClickedButtonEndConf();
		// ע�����з�����
		TUP_RESULT tRet = TUP_FALSE;
		if (!m_strSipAccount.empty())
		{
			tRet = tup_call_deregister(m_strSipAccount.c_str());
			if (TUP_SUCCESS != tRet)
			{
				AfxMessageBox(_T("tup_call_deregister failed!"));
			}
			m_strSipAccount = "";
		}

		// ע��IM������
		tRet = tup_im_setcancelsendingmessage();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
		}

		tRet = tup_im_logout();
		if (tRet != TUP_SUCCESS)
		{
			AfxMessageBox(_T("tup_im_logout failed!"));
		}

		tRet = tup_im_setdispatchmessage(TUP_FALSE);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
		}

		if (::IsWindow(m_pEntAddDlg->GetSafeHwnd()))
		{
			m_pEntAddDlg->DestroyWindow();
		}
		SAFE_DELETE(m_pEntAddDlg);
		m_btnLogin.SetWindowText(_T("��¼"));
		DisableRelativeControls();
		m_bLoginFlag = FALSE;// ע����ΪFALSE
		g_mapUser.clear();
		m_listMemberList.DeleteAllItems();
	}
	else
	{
		UpdateData(TRUE);
		// ��ȡ�ؼ�IP����
		BYTE field0, field1, field2, field3;
		m_ipAddress.GetAddress(field0, field1, field2, field3);
		char IP[100];
		memset(IP, 0, 100);
		sprintf_s(IP, "%d.%d.%d.%d", field0, field1, field2, field3);

		// ��ȡ�ؼ��˿�
		CString cstrPort;
		m_editPort.GetWindowText(cstrPort);
		if (cstrPort.IsEmpty())
		{
			AfxMessageBox(_T("port is empty!"));
			return;
		}
		std::string strPort = CTools::UNICODE2UTF(cstrPort);
		int iPort = atoi(strPort.c_str());

		// ���÷�����IP�Ͷ˿�
		TUP_RESULT tRet = tup_im_setserveraddress(IP, iPort);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setserveraddress failed!"));
			return;
		}

		// ���ûص�����
		tRet = tup_im_register_callback(NotifyCallBack::IMNotify);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_register_callback failed!"));
			return;
		}

		// ʹ�ַܷ���Ϣ
		tRet = tup_im_setdispatchmessage(TUP_TRUE);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
			return;
		}

		// ���õ�¼����
		CString cstrAccount;
		CString cstrPSD;
		m_editPSD.GetWindowText(cstrPSD);
		m_editAccount.GetWindowText(cstrAccount);
		if (cstrAccount.IsEmpty() || cstrPSD.IsEmpty())
		{
			AfxMessageBox(_T("Account or Password is empty��"));
			return;
		}
		IM_S_LOGIN_ARG arg;
		CTools::CString2Char(cstrAccount, arg.account, IM_D_MAX_ACCOUNT_LENGTH);

		CTools::CString2Char(cstrPSD, arg.password, IM_D_MAX_PASSWORD_LENGTH);
		arg.authType = IM_E_LOGIN_AUTHTYPE_BYPASSWORD;
		CString cstrVersion(_T("v1.1.11.103"));
		CTools::CString2Char(cstrVersion, arg.version, IM_D_MAX_VERSION_LENGTH);
		// ���õ�¼�ӿ�
		IM_S_LOGIN_ACK ack;
		tRet = tup_im_login(&arg, &ack);
		if (TUP_SUCCESS != tRet)
		{
			switch (ack.reason)
			{
				// ��Ϣ��ʱ
			case IM_E_LOGING_RESULT_TIMEOUT:
				{
					AfxMessageBox(_T("Message timeout!"));
				}
				break;
				// �����ڲ�����
			case IM_E_LOGING_RESULT_INTERNAL_ERROR:
				{
					AfxMessageBox(_T("Internal error!"));
				}
				break;
				// �������
			case IM_E_LOGING_RESULT_PASSWORD_ERROR:
				{
					if (0 == ack.retryTimes)
					{
						AfxMessageBox(_T("Password error five times, account is locked!"));
					}
					else
					{
						CString cstrErrorTip;
						cstrErrorTip.Format(_T("Password error, number of attempts remaining: %d"), ack.retryTimes);
						AfxMessageBox(cstrErrorTip);
					}
				}
				break;
				// �˺Ų�����
			case IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST:
				{
					AfxMessageBox(_T("Account does not exist!"));
				}
				break;
				// �û��Ѵ���
			case IM_E_LOGING_RESULT_ALREADY_LOGIN:
				{
					AfxMessageBox(_T("User already exist!"));
				}
				break;
				// �ʺ�������
			case IM_E_LOGING_RESULT_ACCOUNT_LOCKED:
				{
					AfxMessageBox(_T("Account has been locked!"));
				}
				break;
				// ��Ҫ�����°汾�������¼
			case IM_E_LOGING_RESULT_NEED_NEW_VERSION:
				{
					AfxMessageBox(_T("Need to download the new version of this to allow login!"));
				}
				break;
				// �û�δ����
			case IM_E_LOGING_RESULT_NOT_ACTIVE:
				{
					AfxMessageBox(_T("User is not activated!"));
				}
				break;
				// �û��˺ű���ͣ
			case IM_E_LOGING_RESULT_ACCOUNT_SUSPEND:
				{
					AfxMessageBox(_T("User account was suspended!"));
				}
				break;
				// �û��˺Ź���
			case IM_E_LOGING_RESULT_ACCOUNT_EXPIRE:
				{
					AfxMessageBox(_T("User account expired!"));
				}
				break;
				// ��Ϣ����ʧ��
			case IM_E_LOGING_RESULT_DECRYPT_FAILED:
				{
					AfxMessageBox(_T("Message decryption failed!"));
				}
				break;
				// ֤������ʧ��
			case IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED:
				{
					AfxMessageBox(_T("Certificate download failed!"));
				}
				break;
				// ֤��У��ʧ��
			case IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED:
				{
					AfxMessageBox(_T("Certificate validation failed!"));
				}
				break;
				// ������������
			case IM_E_LOGING_RESULT_DNS_ERROR:
				{
					AfxMessageBox(_T("Domain name resolution error!"));
				}
				break;
			default:break;
			}
			return;
		}

		// ����������ʱ��
		SetTimer(HEART_BEAT_TIMEID, HEARTBEAT_TIME, NULL);

		// ����ҵ�����
		IM_S_GETSERVICEPROFILEARG serviceArg;
		serviceArg.isSyncAll = TUP_TRUE;
		serviceArg.isVpnAccess = TUP_FALSE;
		serviceArg.needIcon = TUP_TRUE;
		std::string localIPAddr;
		if (!CTools::GetBestHostip(localIPAddr, IP)) return;
		strcpy_s(serviceArg.localIP, IM_D_IP_LENGTH, localIPAddr.c_str());
		strcpy_s(serviceArg.timestamp, IM_D_MAX_TIMESTAMP_LENGTH, "19000000000000");

		IM_S_SERVICEPROFILEACK serviceAck;
		tRet = tup_im_getserviceprofile(&serviceArg, &serviceAck);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_getserviceprofile failed!"));
			return;
		}

		// ע����лص�����
		tRet = tup_call_register_process_notifiy(NotifyCallBack::CallNotify);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_register_process_notifiy failed!"));
			return;
		}

		if (serviceAck.dataConfAddrList->data != NULL)
		{
			IM_S_DATACONFADDRINFO *pDataAddr = (IM_S_DATACONFADDRINFO*)serviceAck.dataConfAddrList->data;
			g_DataConfAddr = pDataAddr->dataConfAddr;
		}
		m_strSipAccount = serviceAck.sipAccount;

		CALL_E_TRANSPORTMODE eTransMode = CALL_E_TRANSPORTMODE_UDP;
		tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TRANS_MODE, &eTransMode);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg failed!"));
			return;
		}

		std::string ip;
		int iServerPort;
		CTools::GetIPPort(serviceAck.sipServer, ip, iServerPort);

		TUP_UINT32 server_port =iServerPort;
		if (eTransMode == CALL_E_TRANSPORTMODE_TLS)
		{
			TUP_CHAR path[] = "D:\\V200R002\\Winbin\\Debug_vc11\\root_cert_1.pem";
			tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TLS_ROOTCERTPATH, path);
			if (TUP_SUCCESS != tRet)
			{
				AfxMessageBox(_T("tup_call_set_cfg failed!"));
				return;
			}
			server_port = 5061;
		}

		CALL_S_SERVER_CFG sipServerCfg = {0};
		strcpy_s(sipServerCfg.server_address, ip.c_str());
		sipServerCfg.server_port = iServerPort;
		tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_SERVER_REG_PRIMARY failed!"));
			return;
		}

		tRet = tup_call_set_cfg(CALL_D_CFG_ENV_USEAGENT, USER_AGENT);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_USEAGENT failed!"));
			return;
		}

		CALL_E_PRODUCT_TYPE eProductType = CALL_E_PRODUCT_TYPE_PC;
		tRet = tup_call_set_cfg(CALL_D_CFG_ENV_PRODUCT_TYPE, (TUP_VOID*)&eProductType);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_ENV_PRODUCT_TYPE failed!"));
			return;
		}

		CALL_S_IF_INFO IFInfo;
		memset(&IFInfo, 0, sizeof(CALL_S_IF_INFO));
		IFInfo.ulType = CALL_E_IP_V4;
		IFInfo.uAddress.ulIPv4 = inet_addr(localIPAddr.c_str());
		tRet = tup_call_set_cfg(CALL_D_CFG_NET_NETADDRESS, &IFInfo);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_set_cfg CALL_D_CFG_NET_NETADDRESS failed!"));
			return;
		}

		std::string sipAccount = serviceAck.sipAccount;
		std::string sipUserName = sipAccount + "@" + localIPAddr;

		tRet = tup_call_register(sipAccount.c_str(), sipUserName.c_str(), serviceAck.sipPassword);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_register failed!"));
			return;
		}

		m_editAccount.GetWindowText(m_cstrAccount);
		g_Account = CTools::UNICODE2UTF(m_cstrAccount);
		g_SipAccount =  serviceAck.sipAccount;

		IM_S_QUERY_USERINFO_ARG accountArg;
		IM_S_QUERY_USERINFO_ACK accountAck;
		memset(&accountArg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
		memset(&accountAck,0,sizeof(IM_S_QUERY_USERINFO_ACK));
		strcpy_s(accountArg.key, IM_D_MAX_ACCOUNT_LENGTH, g_Account.c_str());
		accountArg.type = IM_E_IMUSERQUERYTYPE_BY_ACCOUNT;
		tRet = tup_im_queryuserinfo(&accountArg, &accountAck);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_queryuserinfo failed!"));
			return;
		}

		if (NULL != m_pCurrentUserInfo)
		{
			SAFE_DELETE(m_pCurrentUserInfo);
		}
		m_pCurrentUserInfo = new IM_S_USERINFO;
		memcpy(m_pCurrentUserInfo, (IM_S_USERINFO*)(accountAck.userList->data), sizeof(IM_S_USERINFO));
		g_UserID = m_pCurrentUserInfo->staffID;
		g_Name = m_pCurrentUserInfo->name;
		g_BindNO = m_pCurrentUserInfo->bindNO;

		m_bLoginFlag = TRUE;// ��¼�ɹ���ΪTRUE
		g_mapUser.insert(std::make_pair(g_UserID, *m_pCurrentUserInfo));
		m_listMemberList.InsertItem(0, CString(m_pCurrentUserInfo->bindNO));
		m_listMemberList.SetItemText(0, COL_MEM_ACCOUNT, CString(m_pCurrentUserInfo->account));
		CString cstrBindNO = CTools::UTF2UNICODE(g_BindNO);
		CString cstrTempAccount = CTools::UTF2UNICODE(g_Account);
		// ��¼�ɹ����������ִ��
		m_btnLogin.SetWindowText(_T("�ǳ�"));
		EnableRelativeControls();

		if(NULL == m_pEntAddDlg)
		{
			m_pEntAddDlg = new CEntAddrDlg();
		}

		m_pEntAddDlg->Create(CEntAddrDlg::IDD, CWnd::FromHandle(this->m_hWnd));
		//////�ͷ�tup_im_getserviceprofile�ṹ��ָ��/////
		tup_im_release_tup_list(serviceAck.funcIDList);
		tup_im_release_tup_list(serviceAck.configList);
		tup_im_release_tup_list(serviceAck.panelList);
		tup_im_release_tup_list(serviceAck.serverList);
		tup_im_release_tup_list(serviceAck.componentList);
		tup_im_release_tup_list(serviceAck.componentParamList);
		tup_im_release_tup_list(serviceAck.dataConfAddrList);
		tup_im_release_tup_list(serviceAck.umServerHttpList);
		tup_im_release_tup_list(serviceAck.umServerHttpsList);
		tup_im_release_tup_list(accountAck.userList);
	}
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonStartConf()
{
	// TODO: Add your control notification handler code here
	// �����������飬��ת���ݻ���
	if (g_mapUser.size() <= 1)
	{
		AfxMessageBox(_T("The number is less than one"));
		return;
	}
	TUP_UINT32 uiConfID;
	TUP_UINT32 uiCallID;
	TUP_RESULT tRet = tup_call_serverconf_create(&uiConfID, &uiCallID, "");
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tuo_call_serverconf_create failed!"));
		return;
	}
	Sleep(1000);
	m_uiConfID = uiConfID;
	tRet = tup_call_serverconf_transferto_dataconf(m_uiConfID);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_serverconf_transferto_dataconf failed!"));
		return;
	}
	// �ݲ�֧��˫·����
	m_btnStartConf.EnableWindow(FALSE);
	m_btnEndConf.EnableWindow(TRUE);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedButtonTurnonVideo()
{
	// TODO: Add your control notification handler code here
	// �������߹ر�����ͷ	
	CString cstrIsTurnonVideo;
	m_btnTrunOnVideo.GetWindowText(cstrIsTurnonVideo);
	if (cstrIsTurnonVideo == _T("������Ƶ"))
	{
		TUP_RESULT tRet = tup_conf_video_open(m_handle, m_DataComBox.GetItemData(m_DataComBox.GetCurSel()), TUP_TRUE);
		if (TC_OK != tRet)
		{
			AfxMessageBox(_T("tup_conf_video_open failed!"));
			return;
		}

		// ��ϯ֪ͨ���������ߴ���Ƶ
		TC_VIDEO_PARAM para;
		memset(&para, 0, sizeof(TC_VIDEO_PARAM));
		LocalMember::iterator iter=m_LocalMenber.begin();
		for (;iter!=m_LocalMenber.end();iter++)
		{
			TUP_UINT32 m_BindNum = CTools::str2num(iter->first);
			tup_conf_video_notify(m_handle, VIDEO_NOTIFY_OPEN, m_BindNum, &para);
		}
		m_btnTrunOnVideo.SetWindowText(_T("�ر���Ƶ"));
		m_bVideoFlag = TRUE;
		if (NULL != m_pFullScreenModelDlg)	m_pFullScreenModelDlg->Invalidate(TRUE);
		if (NULL != m_pShowModalDlg) m_pShowModalDlg->Invalidate(TRUE);
	}
	else
	{
		// �ر���Ƶ
		TUP_RESULT tRet = tup_conf_video_close(m_handle, m_DataComBox.GetItemData(m_DataComBox.GetCurSel()));
		if (TC_OK != tRet)
		{
			AfxMessageBox(_T("tup_conf_video_close failed!"));
			return;
		}
		m_btnTrunOnVideo.SetWindowText(_T("������Ƶ"));
		m_bVideoFlag = FALSE;
	}
	
	Invalidate(TRUE);
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnCloseEntAddrDlg(WPARAM,LPARAM)
{
	CHECK_POINTER_RETURN(m_pEntAddDlg,-1L);

	m_pEntAddDlg->ShowWindow(SW_HIDE);
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfAddMemFail(WPARAM wParam, LPARAM lParam)
{
	TRACE0("CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfAddMemFail\n");;
	char *num = (char*)wParam;
	CString cstrNum = CTools::UTF2UNICODE(num);
	int iNum = m_listMemberList.GetItemCount();
	for (int i = 0; i != iNum; ++i)
	{
		if (cstrNum.Compare(m_listMemberList.GetItemText(i, COL_MEM_ID)) == 0)
		{
			m_listMemberList.SetItemText(i, COL_MEM_STATUS, _T("δ����"));
		}
	}

	delete[] num;
	num = 0;
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfAddMemSuccess(WPARAM wParam, LPARAM lParam)
{
	TRACE0("CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfAddMemSuccess\n");;
	char *num = (char*)wParam;
	CString cstrNum = CTools::UTF2UNICODE(num);
	int iNum = m_listMemberList.GetItemCount();
	BOOL isExists = FALSE;
	for (int i = 0; i != iNum; ++i)
	{
		if (cstrNum.Compare(m_listMemberList.GetItemText(i, COL_MEM_ID)) == 0)
		{
			m_listMemberList.SetItemText(i, COL_MEM_STATUS, _T("������"));
			isExists = TRUE;
			break;
		}
	}

	if (!isExists)
	{
		IM_S_USERINFO userInfo;
		if (!getAccountINfoByBingNum(std::string(num), userInfo)) return -1L;
		CString cstrAccount = CTools::UTF2UNICODE(std::string(userInfo.account));

		std::wstring strCallNO = CTools::string2wstring(std::string(num));
		m_listMemberList.InsertItem(iNum, strCallNO.c_str());
		m_listMemberList.SetItemText(iNum, COL_MEM_STATUS, _T("������"));
		m_listMemberList.SetItemText(iNum, COL_MEM_ACCOUNT, cstrAccount);
	}

	if (m_ChairMainBindNum == std::string(num))
	{
		m_listMemberList.SetItemText(iNum, COL_MEM_HOST, _T("��"));
		m_listMemberList.SetItemText(iNum, COL_MEM_KeynoteSpeaker, _T("��"));
	}

	delete[] num;
	num = 0;

	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfCreate(WPARAM wParam, LPARAM lParam)
{
	TRACE0("CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfCreate\n");
	CALL_S_CONF_CREATE_RESULT *result = (CALL_S_CONF_CREATE_RESULT*)wParam;
	m_uiConfID = result->ulConfID;
	if (TUP_SUCCESS != result->ulResult)
	{
		AfxMessageBox(_T("Create conference failed!"));
	}
	SAFE_DELETE(result);
	return 0L;
}
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfConnect(WPARAM, LPARAM)
{
	int nNum = m_listMemberList.GetItemCount();
	for (int i = 0; i < nNum; ++i)
	{
		CString cstrCallNO = m_listMemberList.GetItemText(i, COL_MEM_ID);
		if (CTools::UNICODE2UTF(cstrCallNO) == g_BindNO) continue;
		std::string strCallNO = CTools::UNICODE2UTF(cstrCallNO);
		TUP_RESULT tRet = tup_call_serverconf_add_attendee(m_uiConfID, 1, strCallNO.c_str(), strCallNO.size() + 1);
		if (TUP_SUCCESS != tRet)
		{
			m_listMemberList.SetItemText(i, COL_MEM_STATUS, _T("δ����"));

		}
	}
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnConfInComing(WPARAM wParam, LPARAM lParam)
{
	CALL_S_CONF_INFO *notifyInfo = (CALL_S_CONF_INFO*)wParam;
	if (NULL == notifyInfo) return -1L;
	m_uiCallID = notifyInfo->ulCallID;
	m_uiConfID = notifyInfo->ulConfID;
	TUP_RESULT tRet = TUP_FAIL;

	IM_S_USERINFO userInfo;
	getAccountINfoByBingNum(std::string(notifyInfo->acUserNumber), userInfo);
	CNewDialog IncomingDlg;
	IncomingDlg.m_strNum = CTools::UTF2UNICODE(std::string(notifyInfo->acUserNumber));
	IncomingDlg.m_strName = CTools::UTF2UNICODE(std::string(userInfo.name));
	int nResult = IncomingDlg.DoModal();
	if (IDOK == nResult)
	{
		m_editCONFTitle.SetWindowText(CTools::UTF2UNICODE(notifyInfo->acGroupUri));
		m_editCONFCallAccount.SetWindowText(CTools::UTF2UNICODE(notifyInfo->acUserNumber));
		tRet = tup_call_serverconf_accept(notifyInfo->ulConfID);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_call_serverconf_accept failed!"));
		}
		// ͬ�����������޸�״̬
		CString cstrNO = CTools::UTF2UNICODE(g_BindNO);
		int i = -1;
		if (FindColum(cstrNO, COL_MEM_ID, i))
		{
			m_listMemberList.SetItemText(i, COL_MEM_STATUS, _T("������"));
		}

		m_btnStartConf.EnableWindow(FALSE);
		m_btnEndConf.EnableWindow(TRUE);
		if (m_ChairMainBindNum != g_BindNO)
		{
			m_btnAddMember.EnableWindow(FALSE);
			m_btnDelMember.EnableWindow(FALSE);
		}
		m_ChairMainBindNum = notifyInfo->acUserNumber;
	}
	else
	{
		tRet = tup_call_serverconf_end(notifyInfo->ulConfID);

		m_btnStartConf.EnableWindow(TRUE);
		m_btnEndConf.EnableWindow(FALSE);
	}
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataBeKickedFromConf(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedButtonEndConf();
	return 0L;
}


//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfAddVideoUser(WPARAM wParam, LPARAM lParam)
{
	TUP_UINT32 *deviceID = (TUP_UINT32*)lParam;
	TUP_ULONG m_ConfMemID = (TUP_LONG)wParam;

	std::string m_BindNum;
	if (!GetUserBindNumByid(m_ConfMemID, m_BindNum)) return -1;
	IM_S_USERINFO userInfo;
	if (!getAccountINfoByBingNum(m_BindNum, userInfo)) return 0L;

	int videoInfoIndex;
	if (!AvaluableFullScreenVideo(videoInfoIndex)) return -1L;

	m_pFullScreenModelDlg->FullScreenModeInfo[videoInfoIndex].isValuable = FALSE;
	m_pFullScreenModelDlg->FullScreenModeInfo[videoInfoIndex].DevideID = *deviceID;
	m_pFullScreenModelDlg->FullScreenModeInfo[videoInfoIndex].UserID = m_ConfMemID;

	CWnd *pWnd = m_pFullScreenModelDlg->FullScreenModeInfo[videoInfoIndex].m_VideoHwnd;
	TUP_RESULT tRet = tup_conf_video_attach(m_handle, (TUP_UINT32)userInfo.staffID, *deviceID, pWnd->GetSafeHwnd(),TUP_TRUE,0);

	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_video_attach failed!"));
		return -1L;
	}

	VideoUserInfo videoInfo;
	videoInfo.confHandle = m_handle;
	videoInfo.deviceID = *deviceID;
	videoInfo.userInfo = userInfo;
	videoInfo.videoHwnd = pWnd->GetSafeHwnd();
	m_vecFullScreenVideoUserInfo.push_back(videoInfo);
	m_mapFullScreenVideoUserInfo[m_handle] = m_vecFullScreenVideoUserInfo;

	pWnd = m_pFullScreenModelDlg->FullScreenModeInfo[videoInfoIndex].m_NameHwnd;
	CString str;
	CTools::string2CString(userInfo.name, str);
	if (m_BindNum == m_ChairMainBindNum) str += _T("(��ϯ)");
	pWnd->SetWindowText(str);

	if (m_BindNum == m_ChairMainBindNum)
	{
		VideoUserInfo videoInfo;
		videoInfo.confHandle = m_handle;
		videoInfo.deviceID = *deviceID;
		videoInfo.userInfo = userInfo;
		videoInfo.videoHwnd = m_pShowModalDlg->ShowModalInfo[0].m_VideoHwnd->GetSafeHwnd();
		m_vecShowModalScreenVideoUserInfo.push_back(videoInfo);
		m_mapShowModalVideoUserInfo[m_handle] = m_vecShowModalScreenVideoUserInfo;
	}
	if (m_BindNum == g_BindNO && m_BindNum != m_ChairMainBindNum)
	{
		VideoUserInfo videoInfo;
		videoInfo.confHandle = m_handle;
		videoInfo.deviceID = *deviceID;
		videoInfo.userInfo = userInfo;
		videoInfo.videoHwnd = videoInfo.videoHwnd = m_pShowModalDlg->ShowModalInfo[1].m_VideoHwnd->GetSafeHwnd();
		m_vecShowModalScreenVideoUserInfo.push_back(videoInfo);
		m_mapShowModalVideoUserInfo[m_handle] = m_vecShowModalScreenVideoUserInfo;
	}
	int iIndex = m_tabVideoModal.GetCurSel();
	UpdateVideoUI(iIndex);
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfCreate(WPARAM wParam, LPARAM lParam)
{
	CALL_S_DATACONF_PARAM *pParam = (CALL_S_DATACONF_PARAM*)wParam;
	if (NULL == pParam) return -1L;

	// ������Ϣ
	TC_CONF_INFO *confInfo = new TC_CONF_INFO;
	TUP_UINT8 *pData = new TUP_UINT8[10];
	memset(pData, '8', 10);
	pData[9] = '\0';
	confInfo->conf_id = atoi(pParam->acDataConfID);
	confInfo->user_id = (TUP_UINT32)g_UserID;
	confInfo->os_type = CONF_OS_WIN;
	confInfo->dev_type = CONF_DEV_PC;
	confInfo->user_info = pData;
	confInfo->user_info_len = 9;
	if (CALL_E_CONF_ROLE_CHAIRMAN == pParam->enRole)
	{
		confInfo->user_type |= CONF_ROLE_HOST;// ������
		confInfo->user_type |= CONF_ROLE_PRESENTER;// ������
		m_isChairman = TRUE;
	}
	else if (CALL_E_CONF_ROLE_ATTENDEE == pParam->enRole)
	{
		confInfo->user_type = CONF_ROLE_GENERAL;
		m_isChairman = FALSE;
	}
	if(0 != strlen(pParam->acCharman))
	{
			m_ChairMainBindNum = pParam->acCharman;
	}



	if (m_isChairman)
	{
		m_editCONFStatus.SetWindowText(_T("���ڴ������ݻ���"));
	}
	else
	{
		m_editCONFStatus.SetWindowText(_T("���ڼ������ݻ���"));
	}

	strcpy_s(confInfo->user_name, g_Name.c_str());
	strcpy_s(confInfo->host_key, "111111");
	strcpy_s(confInfo->site_id, "6jf1");
	strcpy_s(confInfo->ms_server_ip, g_DataConfAddr.c_str());
	strcpy_s(confInfo->encryption_key, pParam->acAuthKey);
	strcpy_s(confInfo->site_url, pParam->acCmAddr);
	strcpy_s(confInfo->user_log_uri, g_BindNO.c_str());
	TUP_RESULT tRet = tup_conf_new(NotifyCallBack::ConfNotify, confInfo, CONF_OPTION_BASE | CONF_OPTION_USERLIST | CONF_OPTION_PHONE | CONF_OPTION_PRESENTER_GRAB, &m_handle);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_new failed!"));
		return -1L;
	}

	tRet = tup_conf_join(m_handle);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_join failed!"));
		return -1L;
	}

// 	int iNum = m_listMemberList.GetItemCount();
// 	for (int i = 0; i != iNum; ++i)
// 	{
// 		std::string strTemp = CTools::UNICODE2UTF(m_listMemberList.GetItemText(i, COL_MEM_ACCOUNT));
// 		if (m_ChairMainBindNum.compare(strTemp) == 0)
// 		{
// 			m_listMemberList.SetItemText(i, COL_MEM_HOST, _T("��"));
// 			m_listMemberList.SetItemText(i, COL_MEM_KeynoteSpeaker, _T("��"));
// 		}
// 	}

	// ��ʼ����Ƶ����ؼ�
	m_DataComBox.EnableWindow(TRUE);
	m_btnTrunOnVideo.EnableWindow(TRUE);

	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfDelVideoUser(WPARAM wParam, LPARAM lParam)
{
	// ���ٱ�����Ƶ
	TUP_UINT32 *deviceID = (TUP_UINT32*)lParam;
	TUP_ULONG ConfMemID = (TUP_ULONG)wParam;

	std::string bindNO;
	if (!GetUserBindNumByid(ConfMemID, bindNO)) return -1L;
	IM_S_USERINFO userInfo;
	if (!getAccountINfoByBingNum(bindNO, userInfo)) return 0L;

	VecFullScreenVideoUserInfo::iterator ibegin = m_vecFullScreenVideoUserInfo.begin();
	VecFullScreenVideoUserInfo::iterator iend = m_vecFullScreenVideoUserInfo.end();
	for (; ibegin != iend; ibegin++)
	{
		if (bindNO == ibegin->userInfo.bindNO)
		{
			m_vecFullScreenVideoUserInfo.erase(ibegin);
			break;
		}
	}
	m_mapFullScreenVideoUserInfo[m_handle] = m_vecFullScreenVideoUserInfo;

	int VideoInfoIndex;
	if (!GetVideoINdexByid(VideoInfoIndex, wParam)) return -1L;

	m_pFullScreenModelDlg->FullScreenModeInfo[VideoInfoIndex].isValuable = TRUE;
	m_pFullScreenModelDlg->FullScreenModeInfo[VideoInfoIndex].DevideID = 0;
	m_pFullScreenModelDlg->FullScreenModeInfo[VideoInfoIndex].UserID = 0;
	// ������ʾ��Ϣ
	CWnd *pWnd = m_pFullScreenModelDlg->FullScreenModeInfo[VideoInfoIndex].m_NameHwnd;
	pWnd->SetWindowText(_T(""));
// 	Invalidate(TRUE);

	if (bindNO == m_ChairMainBindNum)
	{
		m_pShowModalDlg->ShowModalInfo[0].isValuable = TRUE;
		m_pShowModalDlg->ShowModalInfo[0].DevideID = 0;
		m_pShowModalDlg->ShowModalInfo[0].UserID = 0;
	}
	if ((bindNO == g_BindNO) && (bindNO != m_ChairMainBindNum))
	{
		m_pShowModalDlg->ShowModalInfo[1].isValuable = TRUE;
		m_pShowModalDlg->ShowModalInfo[1].DevideID = 0;
		m_pShowModalDlg->ShowModalInfo[1].UserID = 0;
	}

	VecShowModalVideoUserInfo::iterator iShowbegin = m_vecShowModalScreenVideoUserInfo.begin();
	VecShowModalVideoUserInfo::iterator iShowend = m_vecShowModalScreenVideoUserInfo.end();
	for (; iShowbegin != iShowend; iShowbegin++)
	{
		if (bindNO == iShowbegin->userInfo.bindNO)
		{
			m_vecShowModalScreenVideoUserInfo.erase(iShowbegin);
			break;
		}
	}
	m_mapShowModalVideoUserInfo[m_handle] = m_vecShowModalScreenVideoUserInfo;

	int iIndex = m_tabVideoModal.GetCurSel();
	UpdateVideoUI(iIndex);
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfLayoutChange(WPARAM wParam, LPARAM lParam)
{
	TUP_INT iIndex = (TUP_INT)wParam;
	if (g_BindNO != m_ChairMainBindNum)
	{
		m_tabVideoModal.SetCurSel(iIndex);
		switch (iIndex)
		{
		case 0:
			{
				VecShowModalVideoUserInfo::iterator iShowBegin = m_vecShowModalScreenVideoUserInfo.begin();
				VecShowModalVideoUserInfo::iterator iShowEnd = m_vecShowModalScreenVideoUserInfo.end();
				VecFullScreenVideoUserInfo::iterator iFullBegin = m_vecFullScreenVideoUserInfo.begin();
				VecFullScreenVideoUserInfo::iterator iFullEnd = m_vecFullScreenVideoUserInfo.end();
				if (m_handle)
				{
					for (; iShowBegin != iShowEnd; iShowBegin++)
					{
						tup_conf_video_detach(iShowBegin->confHandle, (TUP_INT32)iShowBegin->userInfo.staffID, iShowBegin->deviceID, iShowBegin->videoHwnd, TUP_FALSE);
					}

					for (; iFullBegin != iFullEnd; iFullBegin++)
					{
						tup_conf_video_attach(iFullBegin->confHandle, (TUP_INT32)iFullBegin->userInfo.staffID, iFullBegin->deviceID, iFullBegin->videoHwnd, TUP_TRUE, 0);
					}
				}
				m_pFullScreenModelDlg->ShowWindow(SW_SHOW);
				m_pShowModalDlg->ShowWindow(SW_HIDE);
				m_pFullScreenModelDlg->Invalidate(TRUE);
			}
			break;
		case 1:
			{
				VecShowModalVideoUserInfo::iterator iShowBegin = m_vecShowModalScreenVideoUserInfo.begin();
				VecShowModalVideoUserInfo::iterator iShowEnd = m_vecShowModalScreenVideoUserInfo.end();
				VecFullScreenVideoUserInfo::iterator iFullBegin = m_vecFullScreenVideoUserInfo.begin();
				VecFullScreenVideoUserInfo::iterator iFullEnd = m_vecFullScreenVideoUserInfo.end();
				if (m_handle)
				{
					for (; iFullBegin != iFullEnd; iFullBegin++)
					{
						tup_conf_video_detach(iFullBegin->confHandle, (TUP_INT32)iFullBegin->userInfo.staffID, iFullBegin->deviceID, iFullBegin->videoHwnd, TUP_FALSE);
					}

					for (; iShowBegin != iShowEnd; iShowBegin++)
					{
						tup_conf_video_attach(iShowBegin->confHandle, (TUP_INT32)iShowBegin->userInfo.staffID, iShowBegin->deviceID, iShowBegin->videoHwnd, TUP_TRUE, 0);
					}
				}
				m_pFullScreenModelDlg->ShowWindow(SW_HIDE);
				m_pShowModalDlg->ShowWindow(SW_SHOW);

				// �����ϯ�Ǳ��ˣ�����չʾģʽ�£�ֻ��ʾ��ϯ��Ƶ
				if (m_ChairMainBindNum == g_BindNO)
				{
					m_pShowModalDlg->GetDlgItem(IDC_STATIC_SHOW_LOCAL)->ShowWindow(FALSE);
				}
				// �ж��Ƿ�򿪱�����Ƶ
				if ((g_BindNO != m_ChairMainBindNum) && (m_bVideoFlag))
				{
					m_pShowModalDlg->GetDlgItem(IDC_STATIC_SHOW_LOCAL)->ShowWindow(TRUE);
				}
				else if ((g_BindNO != m_ChairMainBindNum) && (!m_bVideoFlag))
				{
					m_pShowModalDlg->GetDlgItem(IDC_STATIC_SHOW_LOCAL)->ShowWindow(FALSE);
				}
				m_pShowModalDlg->Invalidate(TRUE);
			}
			break;
		}
	}
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfUserAdd(WPARAM wParam, LPARAM lParam)
{
	TUP_ULONG role = (TUP_LONG)wParam;
	TC_Conf_User_Record *pRecord = (TC_Conf_User_Record*)lParam;
	if (NULL == pRecord || (pRecord->user_alt_id < 0) || pRecord->user_alt_id > 4294967295) return -1L;
	std::string name = pRecord->user_name;
	std::string bindNO = pRecord->user_alt_uri;
	CString cstrNO = CTools::UTF2UNICODE(bindNO);
	CString cstrID;
	char strID[25] = {0};
	_itoa_s(pRecord->user_alt_id, strID, 10);
	CTools::string2CString(strID, cstrID);

	// ��ѯ������Ƿ����
	if (SetUseridByBindNum(pRecord->user_alt_uri, pRecord->user_alt_id))
	{
		// �޸Ľ�����Ϣ
		int iSize = m_listMemberList.GetItemCount();
		for (int i = 0; i < iSize; i++)
		{
			CString cstrBindNO = m_listMemberList.GetItemText(i, COL_MEM_ID);
			if (cstrBindNO == cstrNO)
			{
				m_listMemberList.SetItemText(i, COL_MEM_STATUS, _T("������"));
			}
		}
	}
	else
	{
		////�������/////
		if (!m_isChairman && bindNO != g_BindNO)
		{
			int iSize = m_listMemberList.GetItemCount();
			m_listMemberList.InsertItem(iSize, _T(""));
			m_listMemberList.SetItemText(iSize, COL_MEM_ID, cstrNO);
			m_listMemberList.SetItemText(iSize, COL_MEM_STATUS, _T("������"));

			if (m_ChairMainBindNum == bindNO)
			{
				m_listMemberList.SetItemText(iSize, COL_MEM_HOST, _T("��"));
				m_listMemberList.SetItemText(iSize, COL_MEM_KeynoteSpeaker, _T("��"));
			}

			IM_S_USERINFO userInfo;
			if (!getAccountINfoByBingNum(bindNO, userInfo)) return -1L;

			CString cstrAccount = CTools::UTF2UNICODE(std::string(userInfo.account));
			m_listMemberList.SetItemText(iSize, COL_MEM_ACCOUNT, cstrAccount);
		}

		////���ش洢�������Ϣ//////
		m_LocalMenber[pRecord->user_alt_uri] = pRecord->user_alt_id;
	}
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnDataConfUserDel(WPARAM wParam, LPARAM lParam)
{
	TC_Conf_User_Record *pRecord = (TC_Conf_User_Record*)lParam;
	if (NULL == pRecord || (pRecord->user_alt_id < 0) || pRecord->user_alt_id > 4294967295) return -1L;
	std::string name = pRecord->user_name;
	std::string bindNO = pRecord->user_alt_uri;
	CString cstrNO = CTools::UTF2UNICODE(bindNO);
	CString cstrID;
	char strID[25] = {0};
	_itoa_s(pRecord->user_alt_id, strID, 10);
	CTools::string2CString(strID, cstrID);

	// ��ѯ������Ƿ����
	if (SetUseridByBindNum(pRecord->user_alt_uri, pRecord->user_alt_id))
	{
		// �޸Ľ�����Ϣ
		int iSize = m_listMemberList.GetItemCount();
		for (int i = 0; i < iSize; i++)
		{
			CString cstrBindNO = m_listMemberList.GetItemText(i, COL_MEM_ID);
			std::string strBindNO = CTools::UNICODE2UTF(cstrBindNO);
			if (strBindNO == bindNO)
			{
				m_listMemberList.DeleteItem(i);
				LocalMember::iterator ibegin = m_LocalMenber.begin();
				LocalMember::iterator iend = m_LocalMenber.end();
				for (; ibegin != iend; ibegin++)
				{
					if (bindNO == ibegin->first)
					{
						m_LocalMenber.erase(ibegin);
						break;
					}
				}
				MAP_USER::iterator iBeg = g_mapUser.begin();
				MAP_USER::iterator iEnd = g_mapUser.end();
				for (; iBeg != iEnd; iBeg++)
				{
					if (bindNO == std::string(iBeg->second.bindNO))
					{
						g_mapUser.erase(iBeg);
						break;
					}
				}
				break;
			}
		}
	}
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnJoinDataConfSuccess(WPARAM wParam, LPARAM lParam)
{
	m_editCONFStatus.SetWindowText(_T("�������ɹ�"));
	if (m_isChairman)
	{
		int iNum = m_listMemberList.GetItemCount();
		CString strBindNO = CTools::UTF2UNICODE(g_BindNO);
		for (int i = 0; i != iNum; ++i)
		{
			if (strBindNO.Compare(m_listMemberList.GetItemText(i, COL_MEM_ID)) == 0)
			{
				m_listMemberList.SetItemText(i, COL_MEM_HOST, _T("��"));
				m_listMemberList.SetItemText(i, COL_MEM_KeynoteSpeaker, _T("��"));
			}
		}
	}
	else
	{
		m_listMemberList.DeleteAllItems();
		//////���Լ���������б��з�������б���û���Լ�  c00327158 2015-11-28 Start/////
		m_listMemberList.InsertItem(0, CTools::UTF2UNICODE(std::string(m_pCurrentUserInfo->bindNO)));
		m_listMemberList.SetItemText(0, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(g_Account));
		////���Լ����뱾�ػ����¼�б���////
		m_LocalMenber[m_pCurrentUserInfo->bindNO] = m_pCurrentUserInfo->staffID;
		//////���Լ���������б��з�������б���û���Լ�  c00327158 2015-11-28 End/////

	}

	TUP_UINT32 compts = IID_COMPONENT_BASE|
		IID_COMPONENT_DS|
		IID_COMPONENT_AS|
		IID_COMPONENT_AUDIO|
		IID_COMPONENT_VIDEO|
		IID_COMPONENT_RECORD|
		IID_COMPONENT_CHAT|
		IID_COMPONENT_POLLING|
		IID_COMPONENT_MS|
		IID_COMPONENT_FT|
		IID_COMPONENT_WB;

	TUP_RESULT tRet = tup_conf_load_component(m_handle,compts);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_load_component failed."));
		return -1L;
	}

	tRet = tup_conf_reg_component_callback(m_handle,IID_COMPONENT_AS,NotifyCallBack::ConfComASNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_reg_component_callback AS failed."));
		return -1L;
	}

	tRet = tup_conf_reg_component_callback(m_handle,IID_COMPONENT_VIDEO,NotifyCallBack::ConfComVideoNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_reg_component_callback VIDEO failed."));
		return -1L;
	}

	tRet = tup_conf_reg_component_callback(m_handle,IID_COMPONENT_WB,NotifyCallBack::ConfComWBNotify);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_reg_component_callback VIDEO failed."));
		return -1L;
	}


	TUP_UINT32 retCount;
	tRet = tup_conf_video_get_deviceinfo(m_handle, NULL, &retCount);
	if (TC_OK != tRet || retCount == 0)
	{
		m_btnTrunOnVideo.EnableWindow(FALSE);
		m_DataComBox.InsertString(0, _T("����Ƶ�豸"));
	}
	else
	{
		// ������Ƶģ��
		m_btnTrunOnVideo.EnableWindow(TRUE);
		TC_DEVICE_INFO *info = new TC_DEVICE_INFO[retCount];
		tup_conf_video_get_deviceinfo(m_handle, info, &retCount);
		for (int i = 0; i != retCount; i++)
		{
			m_DataComBox.InsertString(i, CTools::UTF2UNICODE(info[i]._szName));
			m_DataComBox.SetItemData(i, info[i]._DeviceID);
		}
	}
	m_DataComBox.SetCurSel(0);
	////������Ƶ��Ŀ////
	tup_conf_video_set_max_count(m_handle,9); ///Ĭ����6��////

	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnRefreshMemList(WPARAM wParam, LPARAM lParam)
{
	CALL_S_CONF_MEMBER *pInfo = (CALL_S_CONF_MEMBER*)wParam;
	TUP_UINT32 uiSize = (TUP_INT32)lParam;
	for (TUP_UINT32 i = 0; i < uiSize; i++)
	{
		CString cstrConfState;
		CString cstrNum = CTools::UTF2UNICODE(pInfo[i].acAttendeeNumber);
		int j = -1;
		if (FindColum(cstrNum, COL_MEM_ID, j))
		{
			if (pInfo[i].enState != CALL_E_CONF_ATTENDEE_OUT)
			{
				m_listMemberList.SetItemText(j, COL_MEM_STATUS, cstrConfState);
			}
			else
			{
				m_listMemberList.DeleteItem(j);// �û��˳������ɾ������
				continue;
			}
		}
		if (pInfo[i].enRole == CALL_E_CONF_ROLE_CHAIRMAN)
		{
			m_listMemberList.SetItemText(j, COL_MEM_HOST, _T("��"));
			m_listMemberList.SetItemText(j, COL_MEM_KeynoteSpeaker, _T("��"));
		}

		if (uiSize > 1)
		{
			SAFE_DELETE(pInfo);
		}
		else
		{
			delete[] pInfo;
		}
	}

	return 0L;
}
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnTcnSelchangeTabVideoModal(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
 	int iIndex = m_tabVideoModal.GetCurSel();
	if (g_BindNO == m_ChairMainBindNum)
	{
		tup_conf_update_layout(m_handle, iIndex);
	}

	UpdateVideoUI(iIndex);	
	*pResult = 0;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnUpdateConatct(WPARAM wParam,LPARAM lParam)
{
	MAP_USER::iterator ibegin = g_mapUser.begin();
	MAP_USER::iterator iend = g_mapUser.end();

	if (m_uiConfID == 0)
	{
		int i = 0;
		m_listMemberList.DeleteAllItems();
		for (; ibegin != iend; ibegin++)
		{
			std::wstring wstrTemp = CTools::string2wstring(std::string(ibegin->second.bindNO));
			m_listMemberList.InsertItem(i, wstrTemp.c_str());
			wstrTemp = CTools::string2wstring(std::string(ibegin->second.account));
			m_listMemberList.SetItemText(i, 1, wstrTemp.c_str());
			++i;	
		}
	}
	else
	{	
		int iNum = m_listMemberList.GetItemCount();
		BOOL isExists = TRUE;
		for (; ibegin != iend; ibegin++)
		{
			std::string strBindID(ibegin->second.bindNO);
			for (int i = 0; i != iNum; ++i)
			{
				std::string strBindID2 = CTools::UNICODE2UTF(m_listMemberList.GetItemText(i, COL_MEM_ID));
				if (strBindID == strBindID2) break;
				if ((i == iNum -1) && (strBindID != strBindID2)) isExists = FALSE;
			}
			if (!isExists)
			{
				std::string strCallNO(ibegin->second.bindNO);
				TUP_RESULT tRet = tup_call_serverconf_add_attendee(m_uiConfID, 1, strCallNO.c_str(), strCallNO.size() + 1);
				if (TUP_SUCCESS != tRet)
				{
					AfxMessageBox(_T("tup_call_serverconf_add_attendee failed!"));
				}
				std::wstring wstrTemp = CTools::string2wstring(std::string(ibegin->second.bindNO));
				m_listMemberList.InsertItem(iNum, wstrTemp.c_str());
				wstrTemp = CTools::string2wstring(std::string(ibegin->second.account));
				m_listMemberList.SetItemText(iNum, COL_MEM_ACCOUNT, wstrTemp.c_str());
				m_listMemberList.SetItemText(iNum, COL_MEM_STATUS, _T("������"));

				break;
			}
		}
	}
	return 0L;
}
//************************************************************************
LRESULT CeSDK_TUP_PC_VIDEO_DemoDlg::OnUserBeKickOut(WPARAM wParam, LPARAM lParam)
{
	if (m_bLoginFlag)
	{
		if (m_handle != 0)
		{
			// �ر���Ƶ
			CString cstrVideo;
			m_btnTrunOnVideo.GetWindowText(cstrVideo);
			if (cstrVideo == _T("�ر���Ƶ"))
			{
				TUP_RESULT tRet = tup_conf_video_close(m_handle, m_DataComBox.GetItemData(m_DataComBox.GetCurSel()));
				if (TC_OK != tRet)
				{
					AfxMessageBox(_T("tup_conf_video_close failed!"));
				}
				m_btnTrunOnVideo.SetWindowText(_T("������Ƶ"));
				m_bVideoFlag = FALSE;
			}

			TUP_RESULT tRet = TUP_FAIL;
			if (m_isChairman)
			{
				tRet = tup_conf_terminate(m_handle);
			}
			else
			{
				tRet = tup_conf_leave(m_handle);
			}
			tup_conf_release(m_handle);
			m_handle = 0;
		}

		// �ر���������
		if (m_uiCallID != 0)
		{
			tup_call_end_call(m_uiCallID);
			m_uiCallID = 0;
		}
		// �ر����ݻ���
		if (m_uiConfID != 0)
		{
			if (m_isChairman)
			{
				tup_call_serverconf_end(m_uiConfID);
			}
			else
			{
				tup_call_serverconf_leave(m_uiConfID);
			}
			m_uiConfID = 0;
		}

		TUP_RESULT tRet = TUP_FAIL;
		// ע�����з�����
		if (!m_strSipAccount.empty())
		{
			tRet = tup_call_deregister(m_strSipAccount.c_str());
			if (TUP_SUCCESS != tRet)
			{
				AfxMessageBox(_T("tup_call_deregister failed!"));
			}
			m_strSipAccount = "";
		}

		// ע��IM������
		tRet = tup_im_setcancelsendingmessage();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setcancelsendingmessage failed!"));
		}

		tRet = tup_im_logout();
		if (tRet != TUP_SUCCESS)
		{
			AfxMessageBox(_T("tup_im_logout failed!"));
		}

		tRet = tup_im_setdispatchmessage(TUP_FALSE);
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(_T("tup_im_setdispatchmessage failed!"));
		}

		m_LocalMenber.clear();
		m_handle = 0;
		m_isChairman = FALSE;
		m_ChairMainBindNum = "";
		m_ChaMainAccount = "";
		m_uiConfID = 0;
		m_uiCallID = 0;
		m_editCONFStatus.SetWindowText(_T(""));
		m_btnStartConf.EnableWindow(TRUE);
		m_btnEndConf.EnableWindow(FALSE);
		m_btnAddMember.EnableWindow(TRUE);
		m_btnDelMember.EnableWindow(TRUE);
		m_listMemberList.DeleteAllItems();
		m_DataComBox.SetCurSel(-1);
		m_DataComBox.ResetContent();
		m_DataComBox.EnableWindow(FALSE);
		m_btnTrunOnVideo.EnableWindow(FALSE);
		g_mapUser.clear();
		m_pFullScreenModelDlg->InitVideoInfo();
		m_pShowModalDlg->InitVideoInfo();
		if (NULL != m_pFullScreenModelDlg)
		{
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME0)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME1)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME2)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME3)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME4)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME5)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME6)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME7)->SetWindowText(_T(""));
			m_pFullScreenModelDlg->GetDlgItem(IDC_STATIC_FULL_NAME8)->SetWindowText(_T(""));
		}
		Invalidate(TRUE);

		m_bLoginFlag = FALSE;
		m_btnLogin.SetWindowText(_T("��¼"));
		g_mapUser.clear();
		m_listMemberList.DeleteAllItems();
		m_DataComBox.SetCurSel(-1);
		m_DataComBox.ResetContent();
		DisableRelativeControls();
		if (::IsWindow(m_pEntAddDlg->GetSafeHwnd()))
		{
			m_pEntAddDlg->DestroyWindow();
		}
		SAFE_DELETE(m_pEntAddDlg);
		AfxMessageBox(_T("Kicked Off,Please Relogin!"));
	}

	return 0L;
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnNMRClickListMembers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if ((m_listMemberList.GetSelectedCount() <= 0) || (m_uiConfID == 0))
	{
		return;
	}
// 
// 	int nItem = -1;
// 	POSITION pos = m_listMemberList.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		TRACE0("No items were selected!\n");
// 	}
// 	else
// 	{
// 		while (pos)
// 		{
// 			nItem = m_listMemberList.GetNextSelectedItem(pos);
// 			TRACE1("Item %d was selected!\n", nItem);
// 			// you could do your own processing on nItem here
// 			break;
// 		}
// 	}
// 	CString cstrStatus = m_listMemberList.GetItemText(nItem, COL_MEM_STATUS);
// 	if (cstrStatus != _T("δ����"))
// 	{
// 		return;
// 	}
// 	else
// 	{
// 		 m_listMemberList.SetItemText(nItem, COL_MEM_STATUS,L"������");
// 	}


	CPoint hitPt;
	::GetCursorPos(&hitPt);
	CMenu menu;
	menu.LoadMenu(IDR_MENU2);
	CMenu *pop = menu.GetSubMenu(0);
	pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, hitPt.x, hitPt.y, this);

	*pResult = 0;
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnAgainInviteAddConf()
{
	// TODO: Add your command handler code here
	int nItem = -1;
	POSITION pos = m_listMemberList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		while (pos)
		{
			nItem = m_listMemberList.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			break;
		}
	}
	CString cstrBindNO = m_listMemberList.GetItemText(nItem, COL_MEM_ID);

	std::string strCallNO = CTools::UNICODE2UTF(cstrBindNO);
	TUP_RESULT tRet = tup_call_serverconf_add_attendee(m_uiConfID, 1, strCallNO.c_str(), strCallNO.size() + 1);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_call_serverconf_add_attendee failed!"));
		return;
	}
	m_listMemberList.SetItemText(nItem, COL_MEM_STATUS,L"������");
}
//************************************************************************
void CeSDK_TUP_PC_VIDEO_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	// ��ʱ�����������������Ϣ
	if (HEART_BEAT_TIMEID == nIDEvent)
	{
		// ������������
		TUP_RESULT tRet = tup_im_sendheartbeat();
		if (TUP_SUCCESS != tRet)
		{
			AfxMessageBox(TEXT("tup_im_sendheartbeat failed."));
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
