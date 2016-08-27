// DataConfDlg.cpp : implementation file
//


#include "stdafx.h"
#include "eSDK_TUP_PC_CONF_Demo.h"
#include "DataConfDlg.h"
#include "afxdialogex.h"
#include "NotifyCallBack.h"
#include "Tools.h"
#include <stdio.h>
// CDataConfDlg dialog

IMPLEMENT_DYNAMIC(CDataConfDlg, CDialogEx)

CDataConfDlg::CDataConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataConfDlg::IDD, pParent)
	,m_bisPresent(false)
	,m_intdlgModel(0)
	,m_DataConfHandle(0)
	,m_ulCallID(0)
	,m_ulConfID(0)
	,m_bIsChairMan(false)
	,m_ChairmainBindNum("")
{

}

CDataConfDlg::~CDataConfDlg()
{
}

void CDataConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONF_MENBER, m_listDataConfMember);
	DDX_Control(pDX, IDC_EDIT_ADD_ACCOUNT, m_editAddAccount);
	DDX_Control(pDX, BTN_ADD_ACCOUNT, m_btnAddAccount);
	DDX_Control(pDX, BTN_REQUEST_ROLE, m_btnRequestRole);
	DDX_Control(pDX, BTN_STOP_SHARE_DESKTOP, m_btnStopShareDesktop);
	DDX_Control(pDX, IDCANCEL, m_btnCancelConf);
	DDX_Control(pDX, BTN_CLOSE_CONF, m_btnCloseConf);
	//DDX_Control(pDX, IDC_STATIC_DESKTOP, m_pictureDesktop);
	DDX_Control(pDX, TXT_CONF_NAME, m_txtConfName);
	DDX_Control(pDX, TXT_ACCOUNT_NAME, m_txtAccountName);
	DDX_Control(pDX, IDC_STATIC_DESKTOP, m_stcDeskTop);
	DDX_Control(pDX, IDC_SHARE_DESKTOP, m_btnShareDesktop);
}


BEGIN_MESSAGE_MAP(CDataConfDlg, CDialogEx)
	ON_MESSAGE(WM_DATACONF_CREAT, &CDataConfDlg::OnDataconfCreat)
	ON_MESSAGE(WM_DATACONF_JOINSUCCESS, &CDataConfDlg::OnDataconfJoinSuccess)
	ON_BN_CLICKED(BTN_REQUEST_ROLE, &CDataConfDlg::OnClickedBtnRequestRole)
	ON_MESSAGE(WM_DATACONF_UPDATE_PRESENTINFO, &CDataConfDlg::OnDataConfUpdatePresentInfo)
	ON_MESSAGE(WM_DATACONF_AS_SCREENDATA_NOTIFY, &CDataConfDlg::OnDataConfAsScreenDataNotify)
//	ON_WM_ACTIVATE()
	ON_MESSAGE(WM_DATACONF_AS_STATE_NOTIFY, &CDataConfDlg::OnDataConfAsStateNotify)
	ON_MESSAGE(WM_DATACONF_AS_OWNER_NOTIFY, &CDataConfDlg::OnDataConfAsOwnerNotify)
	ON_BN_CLICKED(BTN_STOP_SHARE_DESKTOP, &CDataConfDlg::OnClickedBtnStopShareDesktop)
	ON_MESSAGE(WM_DATACONF_USER_ADD, &CDataConfDlg::OnDataConfUserAdd)
	ON_BN_CLICKED(IDCANCEL, &CDataConfDlg::OnBnClickedCancel)
	ON_MESSAGE(WM_DATACONF_USER_DEL, &CDataConfDlg::OnDataConfUserDel)
	ON_BN_CLICKED(BTN_CLOSE_CONF, &CDataConfDlg::OnBnClickedCloseConf)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONF_MENBER, &CDataConfDlg::OnNMRClickListConfMenber)
	ON_COMMAND(ID_DELETE, &CDataConfDlg::OnDelete)
	ON_BN_CLICKED(BTN_ADD_ACCOUNT, &CDataConfDlg::OnClickedBtnAddAccount)
	ON_MESSAGE(WM_DATACONF_END, &CDataConfDlg::OnDataconfEnd)
	ON_BN_CLICKED(IDC_SHARE_DESKTOP, &CDataConfDlg::OnBnClickedShareDesktop)
	ON_MESSAGE(WM_DATACONF_BE_CLOSED, &CDataConfDlg::OnDataconfBeClosed)
	ON_BN_CLICKED(BTN_ATTACH, &CDataConfDlg::OnBnClickedAttach)
	ON_MESSAGE(WM_DATACONF_AS_ON_CHANNEL, &CDataConfDlg::OnDataConfAsOnChannel)
	ON_MESSAGE(WM_ONEKEY_TO_CONF_RESULT, &CDataConfDlg::OnOnekeyToConfResult)
END_MESSAGE_MAP()


// CDataConfDlg message handlers


BOOL CDataConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_txtConfName.SetWindowText(_T("会议成员列表"));
	//////设置列表框状态//////
	m_listDataConfMember.ModifyStyle(0,LVS_SINGLESEL);
	m_listDataConfMember.InsertColumn(COL_MEM_Compere, _T("主席"), LVCFMT_LEFT, 40);
	m_listDataConfMember.InsertColumn(COL_MEM_Status, _T("状态"), LVCFMT_LEFT, 40);
	m_listDataConfMember.InsertColumn(COL_MEM_Name, _T("姓名"), LVCFMT_LEFT, 50);
	m_listDataConfMember.InsertColumn(COL_MEM_ACCOUNT, _T("账号"), LVCFMT_LEFT, 40);
	m_listDataConfMember.InsertColumn(COL_MEM_CALLNO, _T("号码"), LVCFMT_LEFT, 50);
	m_listDataConfMember.InsertColumn(COL_MEM_CALLSTATE, _T("呼叫状态"), LVCFMT_LEFT, 60);
	m_listDataConfMember.InsertColumn(COL_MEM_SPK, _T("发言"), LVCFMT_LEFT, 50);
	m_listDataConfMember.InsertColumn(COL_MEM_MUTE, _T("静音"), LVCFMT_LEFT, 50);
	DWORD dwStyle = m_listDataConfMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listDataConfMember.SetExtendedStyle(dwStyle); //设置扩展风格

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


afx_msg LRESULT CDataConfDlg::OnDataconfCreat(WPARAM wParam, LPARAM lParam)
{
	CALL_S_DATACONF_PARAM* pNotify = (CALL_S_DATACONF_PARAM*)wParam;
	ASSERT(NULL != theApp.m_pMainWnd);
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针

	TC_CONF_INFO *confInfo = new TC_CONF_INFO;
	memset(confInfo,0,sizeof(TC_CONF_INFO));
	if ( NULL == confInfo )
	{
		return 1;
	}
	confInfo->conf_id = atoi(pNotify->acDataConfID);
	confInfo->user_id = atoi(pMainDlg->m_CurrentUserInfo.bindNO);
	confInfo->os_type = CONF_OS_WIN;
	confInfo->dev_type = CONF_DEV_PC;
	TUP_UINT8 *pdata = new TUP_UINT8[10];
	if ( NULL == pdata )
	{
		delete confInfo;
		confInfo = NULL;
		return 1;
	}
	memset(pdata, '8', 10);
	pdata[9] = 0;
	confInfo->user_info = pdata;
	confInfo->user_info_len = 9;
	if ( 0 == strcmp(pNotify->acCharman,pMainDlg->m_CurrentUserInfo.bindNO) )	//若当前用户是此数据会议的主席
	{
		confInfo->user_type = CONF_ROLE_HOST|CONF_ROLE_PRESENTER;
		m_bChairmanFlag = true;
	}
	else
	{
		confInfo->user_type = CONF_ROLE_GENERAL;
		m_bChairmanFlag = false;
	}

	strncpy_s(confInfo->user_name, TC_MAX_USER_NAME_LEN, pMainDlg->m_CurrentUserInfo.name,_TRUNCATE );
	strncpy_s(confInfo->host_key, TC_MAX_HOST_KEY_LEN, "111111",_TRUNCATE);

	strncpy_s(confInfo->site_id, TC_MAX_CONF_SITE_ID_LEN,  "6jf1",_TRUNCATE);
	strncpy_s(confInfo->ms_server_ip, TC_MAX_CONF_SERVER_IP, pMainDlg->m_strConfServerAddress.c_str(),_TRUNCATE);
	strncpy_s(confInfo->encryption_key, TC_MAX_ENCRYPTION_KEY, pNotify->acAuthKey,_TRUNCATE);		//会议鉴权密码

	//strcpy_s(confInfo->site_url, TC_MAX_SITE_URL_LEN, "10.170.103.86:5060");
	strncpy_s(confInfo->site_url, TC_MAX_SITE_URL_LEN,pNotify->acCmAddr,_TRUNCATE);
	strncpy_s(confInfo->user_log_uri, TC_MAX_USER_LOG_URI_LEN, pMainDlg->m_CurrentUserInfo.bindNO,_TRUNCATE);
	CONF_HANDLE handle;
	TUP_RESULT tRet = tup_conf_new(NotifyCallBack::ConfNotify, confInfo, CONF_OPTION_BASE | CONF_OPTION_USERLIST|CONF_OPTION_PHONE|CONF_OPTION_PRESENTER_GRAB,&handle);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_new failed."));
		confInfo->user_info = NULL;	//必须先把confInfo->user_info置NULL，才能delete confInfo
		delete [] pdata;
		pdata = NULL;
		delete confInfo;
		confInfo = NULL;
		return 1;
	}

	m_DataConfHandle = handle;

	tRet = tup_conf_join(handle);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_join failed."));
		confInfo->user_info = NULL;	//必须先把confInfo->user_info置NULL，才能delete confInfo
		delete [] pdata;
		pdata = NULL;
		delete confInfo;
		confInfo = NULL;
		return 1;
	}

	confInfo->user_info = NULL;	//必须先把confInfo->user_info置NULL，才能delete confInfo
	delete [] pdata;
	pdata = NULL;
	delete confInfo;
	confInfo = NULL;
	m_ulConfID = pNotify->ulConfID;
	m_ulCallID = pNotify->ulCallID;
	
	m_ChairmainBindNum = pNotify->acCharman;

	m_stcDeskTop.m_handle = m_DataConfHandle;
	return 0;
}


afx_msg LRESULT CDataConfDlg::OnDataconfJoinSuccess(WPARAM wParam, LPARAM lParam)
{
	//加载指定的组件
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

	TUP_RESULT tRet = tup_conf_load_component(m_DataConfHandle,compts);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_load_component failed."));
		return -1L;
	}

	tRet = tup_conf_reg_component_callback(m_DataConfHandle,IID_COMPONENT_AS,NotifyCallBack::ConfComASNotify);	//注册指定组件回调函数
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_reg_component_callback AS failed."));
		return -1L;
	}
	if (m_bChairmanFlag)
	{
		m_btnShareDesktop.EnableWindow(FALSE);
		m_btnRequestRole.EnableWindow(TRUE);
	}
	else
	{
		m_btnShareDesktop.EnableWindow(TRUE);
		m_btnRequestRole.EnableWindow(TRUE);
	}

	return 0;
}


void CDataConfDlg::OnClickedBtnRequestRole()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_conf_user_request_role(m_DataConfHandle,CONF_ROLE_PRESENTER,"");		//获得主讲人权限
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("Get ROLE_PRESENTER Failed！"));
	}

}


afx_msg LRESULT CDataConfDlg::OnDataConfUpdatePresentInfo(WPARAM wParam, LPARAM lParam)		//主讲人变更
{
	TUP_ULONG prePresentid = wParam;   ////前一个主讲人的ID
	TUP_ULONG Presentid = lParam;   ////当前主讲人的ID

	if ( 0 != Presentid )
	{
		MarkPresent(Presentid);

		CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
		if ( NULL != pMainDlg )
		{
			if ( Presentid == atoi(pMainDlg->m_CurrentUserInfo.bindNO) )			////当前的主讲人是自己
			{
				m_bisPresent = true;
				pMainDlg = NULL;
				TUP_RESULT tRet = tup_conf_as_set_owner(m_DataConfHandle, Presentid, AS_ACTION_ADD);			//设定自己获得共享权限
				if ( TC_OK != tRet )
				{
					AfxMessageBox(L"tup_conf_as_set_owner failed 111");
					return -1L;
				}
			} 
			else
			{
				m_bisPresent = false;
				pMainDlg = NULL;
			}
		}
	}

	return 0;
}


void CDataConfDlg::OnClickedBtnShareDesktop()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT  tRet = tup_conf_as_set_sharetype(m_DataConfHandle,AS_SHARINGTYPE_DESKTOP);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_set_sharetype failed");
		return ;
	}
	tRet = tup_conf_as_start(m_DataConfHandle);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_start failed");
		return ;
	}
}


afx_msg LRESULT CDataConfDlg::OnDataConfAsScreenDataNotify(WPARAM wParam, LPARAM lParam)
{

	TC_AS_SCREENDATA screenData = {0};
	//memcpy(&screenData,(TC_AS_SCREENDATA*)lParam,sizeof(TC_AS_SCREENDATA));
	TUP_RESULT  tRet = tup_conf_as_get_screendata(m_DataConfHandle,&screenData);
	if ( TC_OK != tRet )
	{
		return -1L;
	}

	TRACE("\nScreenData:[%d][0X%x][0X%x]\n",screenData.ucDataType,screenData.pUpdateInfo,screenData.pData);

	TC_AS_ScreenDataInfo *pInfo = (TC_AS_ScreenDataInfo*)(screenData.pUpdateInfo);
	if(NULL == pInfo)
	{
		return -1L;
	}

	pInfo = NULL;
	if (AS_SCREENDATAFORMAT_DDB == screenData.ucDataType)
	{
		m_stcDeskTop.SetBitmap2((BITMAP*)(screenData.pData));
	}
	else if (AS_SCREENDATAFORMAT_DIB == screenData.ucDataType)
	{
		//移动终端使用此类型
	}
	else if (AS_SCREENDATAFORMAT_DC == screenData.ucDataType)
	{
		HDC hAnnotDataDC = (HDC)screenData.pData;
		BITMAP bm;
		HBITMAP hBmp = (HBITMAP)::GetCurrentObject(hAnnotDataDC, OBJ_BITMAP);
		if ( NULL == hBmp)
		{
			DWORD  nRet = GetLastError();
			TRACE("CReceViewRenderWnd::OnAsScreenData() NULL == hBmp GetLastError:%d",nRet );
		}
		(VOID)::GetObject(hBmp, sizeof(bm), &bm);
		m_stcDeskTop.SetBitmap(hBmp);
	}
	else
	{
		//to do
	}
	return 0;
}


afx_msg LRESULT CDataConfDlg::OnDataConfAsStateNotify(WPARAM wParam, LPARAM lParam)
{
	unsigned long ulState = (unsigned long)lParam;
	switch (ulState)
	{
		case AS_STATE_NULL:			//无活动
			{
				m_stcDeskTop.SetBitmap2(NULL);
				if (true == m_bisPresent)
				{
					m_btnShareDesktop.EnableWindow(TRUE);
					m_btnStopShareDesktop.EnableWindow(FALSE);
				}
				break;
			}
		case AS_STATE_START:		//共享端共享
		case AS_STATE_VIEW:			//观看端观看
			{
				if (m_bisPresent)
				{
					m_btnShareDesktop.EnableWindow(FALSE);
					m_btnStopShareDesktop.EnableWindow(TRUE);
				}
			
				break;
			}
		default:
				break;
	}
	return 0;
}


afx_msg LRESULT CDataConfDlg::OnDataConfAsOwnerNotify(WPARAM wParam, LPARAM lParam)		//共享通道通知，tup_conf_as_set_owner的消息处理函数
{
	TUP_ULONG OwnerId = (TUP_ULONG)lParam;
	TUP_UINT uiIsSucess = (TUP_UINT)wParam;
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if (NULL != pMainDlg)
	{
		m_PresentBindNum = pMainDlg->m_CurrentUserInfo.bindNO;
		std::string strCurUserId = pMainDlg->m_CurrentUserInfo.bindNO;
		pMainDlg = NULL;
		std::string strOwnerId = "";
		char chrOwenId[32] = {0};
		sprintf_s(chrOwenId,32,"%d",OwnerId);
		strOwnerId = chrOwenId;
		if ( strCurUserId == strOwnerId && 1 == uiIsSucess )
		{
				//m_bisPresent = true;

				m_btnRequestRole.EnableWindow(FALSE);
				m_btnShareDesktop.EnableWindow(TRUE);
				m_btnStopShareDesktop.EnableWindow(FALSE);
		}
		else
		{
				//m_bisPresent = false;

				m_btnRequestRole.EnableWindow(TRUE);
				m_btnShareDesktop.EnableWindow(FALSE);
				m_btnStopShareDesktop.EnableWindow(FALSE);
		}
	}

	return 0;
}


void CDataConfDlg::OnClickedBtnStopShareDesktop()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_conf_as_stop(m_DataConfHandle);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_stop failed");
		return ;
	}
}


afx_msg LRESULT CDataConfDlg::OnDataConfUserAdd(WPARAM wParam, LPARAM lParam)
{
	TUP_ULONG role = (TUP_ULONG)wParam;
	TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)lParam;
	if(NULL == pRecord || (pRecord->user_alt_id<0) || (pRecord->user_alt_id >4294967295))
	{
		return -1L;
	}
	pRecord = NULL;

	TUP_UINT32 iPresenterId = 0;
 	TUP_RESULT tRet = tup_conf_user_get_presenter( m_DataConfHandle, &iPresenterId );		//获取主讲人ID
	if ( TC_OK != tRet )
	{
		AfxMessageBox(L"tup_conf_user_get_presenter failed");
		return -1L;
	}

	MarkPresent(iPresenterId);

	TUP_CHAR strPresentId[IM_D_MAX_PHONE_LENGTH]={0};
	sprintf_s( strPresentId, IM_D_MAX_PHONE_LENGTH, "%u", iPresenterId );
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if (NULL != pMainDlg)
	{
		if (  0 == strcmp (pMainDlg->m_CurrentUserInfo.bindNO,strPresentId ) )
		{
			m_bisPresent = true;
		}
		else
		{
			m_bisPresent = false;
		}
		pMainDlg = NULL;
	}

	return 0;
}


BOOL CDataConfDlg::FindColum(const CString& cstrKey, int iColnum, int& iFind)
{
	int iSize = m_listDataConfMember.GetItemCount();
	for(int i = 0; i< iSize; i++)
	{
		if(cstrKey.Compare(m_listDataConfMember.GetItemText(i,iColnum)) == 0)
		{
			iFind = i;
			return TRUE;
		}
	}
	return FALSE;
}


void CDataConfDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	///如果自己是主讲人但不是主席，退出会议时，将主讲人权限还给主席//////
	if( true == m_bisPresent && false == m_bChairmanFlag && 0 != m_DataConfHandle )
	{
		//设定自己释放共享权限
		CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
		if ( NULL != pMainDlg )
		{
			TUP_UINT32 iCurrentUserBindNo = 0;
			iCurrentUserBindNo = atoi(pMainDlg->m_CurrentUserInfo.bindNO);
			TUP_RESULT tRet = tup_conf_as_set_owner(m_DataConfHandle, iCurrentUserBindNo, AS_ACTION_DELETE);			//指定自己释放主讲权限
			if ( TC_OK != tRet )
			{
				AfxMessageBox(L"tup_conf_as_set_owner failed");
			}
			pMainDlg = NULL;
		}

		TUP_UINT32 iHostId = 0;
		TUP_RESULT tRet = tup_conf_user_get_host( m_DataConfHandle, &iHostId );		//查询会议主席
		if ( TC_OK == tRet )
		{
			if ( 0 != iHostId )
			{
				tRet = tup_conf_user_set_role(m_DataConfHandle,iHostId,CONF_ROLE_PRESENTER);	//直接指定iHostId为主讲人
				if ( TC_OK != tRet )		
				{
					AfxMessageBox(L"tup_conf_user_set_role failed");
				}
			}
		}
	}

	if( NULL != m_ulCallID )
	{
		TUP_RESULT tRet = tup_call_end_call(m_ulCallID);		//结束和其他用户的通话或者结束来电。
		if ( TUP_SUCCESS != tRet )
		{
			AfxMessageBox(L"tup_call_end_call failed");
		}
		m_ulCallID = 0;
	}
	if ( NULL != m_ulConfID )
	{
		TUP_RESULT tRet = tup_call_serverconf_leave(m_ulConfID);
		if ( TUP_SUCCESS != tRet )
		{
			AfxMessageBox(L"tup_call_serverconf_leave failed");
		}
		m_ulConfID = 0; 
	}
	if(m_DataConfHandle != 0)
	{
		//tup_conf_terminate(m_handle);
		TUP_RESULT tRet = tup_conf_leave(m_DataConfHandle);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_conf_leave failed");
		}
		tRet = tup_conf_release(m_DataConfHandle);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_conf_release failed");
		}
		m_DataConfHandle = 0;
	}
	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
}


afx_msg LRESULT CDataConfDlg::OnDataConfUserDel(WPARAM wParam, LPARAM lParam)
{
	TUP_ULONG role = (TUP_ULONG)wParam;
	TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)lParam;
	if(NULL == pRecord || (pRecord->user_alt_id<0) || (pRecord->user_alt_id >4294967295))
	{
		pRecord = NULL;
		return -1L;
	}
	TUP_CHAR UserBindId[IM_D_MAX_PHONE_LENGTH] = {0};
	sprintf_s(UserBindId,IM_D_MAX_PHONE_LENGTH,"%d",pRecord->user_alt_id);
	CString cstrNum = CTools::UTF2UNICODE(UserBindId);
	pRecord = NULL;
	int j = -1;
	if(FindColum(cstrNum,COL_MEM_CALLNO,j))	////找到联系人并将其删除
	{
		m_listDataConfMember.DeleteItem(j);//用户退出会议就删除此人
	}

	//获得主讲人ID
	TUP_UINT32 uiPresenterId = 0;
	TUP_RESULT tRet = tup_conf_user_get_presenter( m_DataConfHandle, &uiPresenterId );		//获取主讲人ID
	if ( TC_OK != tRet )
	{
		AfxMessageBox(L"tup_conf_user_get_presenter failed");
	}
	else
	{
		if ( 0 == uiPresenterId )
		{
			CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
			if ( NULL != pMainDlg )
			{
				TUP_UINT32 uiHostId = atoi(pMainDlg->m_CurrentUserInfo.bindNO);
				pMainDlg = NULL;
				tRet = tup_conf_user_set_role(m_DataConfHandle,uiHostId,CONF_ROLE_PRESENTER);	//直接指定iHostId为主讲人
				if ( TC_OK != tRet )		
				{
					AfxMessageBox(L"tup_conf_user_set_role failed");
				}
			}
		}
	}

	return 0;
}


void CDataConfDlg::SetCallId(TUP_UINT32 ulCallId)
{
	m_ulCallID = ulCallId;
}


void CDataConfDlg::RefreshMember(CALL_S_CONF_MEMBER* confMember, TUP_UINT32 memberCount)
{
	int j = -1;
	for (TUP_UINT32 i = 0;i<memberCount;i++)
	{
		/////依次刷新/////
		CString cstrConfState;
 		switch (confMember[i].enState)
		{
		    case CALL_E_CONF_ATTENDEE_INVITING:
				{
					cstrConfState = L"邀请中";
					break;
				}
			case CALL_E_CONF_ATTENDEE_INCONF:
				{
					cstrConfState = L"会议中";
					IM_S_USERINFO userInfo;
					CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
					if (NULL == pMainDlg)
					{
						return;
					}
					if( !pMainDlg->getAccountInfo(confMember[i].acAttendeeNumber, IM_E_IMUSERQUERYTYPE_BY_BINDNO, userInfo) )
					{
						pMainDlg = NULL;
						AfxMessageBox(_T("Get target user info failed by bind no."));
						return;
					}
					pMainDlg = NULL;
					CString cstrNum = CTools::UTF2UNICODE(confMember[i].acAttendeeNumber);
					if (!FindColum(cstrNum,COL_MEM_CALLNO,j))	//若与会人员中找不到此人，则把他添加到与会人员列表
					{
						int iSize = m_listDataConfMember.GetItemCount();
						m_listDataConfMember.InsertItem(iSize,L"");
						j = iSize;
					}
					else	//若与会人员中找到此人，则更新他的状态
					{
					}
					m_listDataConfMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
					m_listDataConfMember.SetItemText(j, COL_MEM_Name, CTools::UTF2UNICODE(userInfo.name));
					m_listDataConfMember.SetItemText(j, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(userInfo.account));

					m_listDataConfMember.SetItemText(j,COL_MEM_CALLSTATE,cstrConfState);
					m_listDataConfMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);
					if(confMember[i].enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
					{
						m_listDataConfMember.SetItemText(j,COL_MEM_Compere,L"主席");
					}
					CString cstrAccount;
					m_txtAccountName.GetWindowText(cstrAccount);
					if ( cstrAccount == CTools::UTF2UNICODE(userInfo.account) )
					{
 						if(confMember[i].enRole ==  CALL_E_CONF_ROLE_CHAIRMAN)
						{
							m_bIsChairMan = true;
							GetDlgItem(BTN_ADD_ACCOUNT)->EnableWindow(true);
							GetDlgItem(BTN_CLOSE_CONF)->EnableWindow(true);
							m_editAddAccount.EnableWindow(true);
						}
						else
						{
							m_bIsChairMan = false;
							GetDlgItem(BTN_ADD_ACCOUNT)->EnableWindow(false);
							GetDlgItem(BTN_CLOSE_CONF)->EnableWindow(false);
							m_editAddAccount.EnableWindow(false);
						}
					}

					if(confMember[i].ulRight != 1)
					{
						m_listDataConfMember.SetItemText(j,COL_MEM_MUTE,L"静音");
					}
					else
					{
						m_listDataConfMember.SetItemText(j,COL_MEM_MUTE,L"未静音");
					}
					m_listDataConfMember.SetItemText(j,COL_MEM_CALLNO,cstrNum);
					break;
				}
			case CALL_E_CONF_ATTENDEE_INVITE_FAIL:
				{
					cstrConfState = L"邀请失败";
					break;
				}
			case CALL_E_CONF_ATTENDEE_OUT:
				{	
					cstrConfState = L"退出会议";
					CString cstrNum = CTools::UTF2UNICODE(confMember[i].acAttendeeNumber);
					if(FindColum(cstrNum,COL_MEM_CALLNO,j))	////找到联系人，但是联系人的状态是out
					{
						m_listDataConfMember.DeleteItem(j);//用户退出会议就删除此人
					}
					break;
				}
			default:
				{
					cstrConfState = L"添加失败";
					break;
				}
		}
	}
}


void CDataConfDlg::OnBnClickedCloseConf()
{
	// TODO: Add your control notification handler code here

	////语音会议也需要关闭////
	if( 0 != m_ulCallID )
	{
		TUP_RESULT tRet = tup_call_end_call(m_ulCallID);
		if ( TUP_SUCCESS != tRet )
		{
			AfxMessageBox(L"tup_call_end_call failed");
		}
		m_ulCallID = 0;
	}
	if( true == m_bIsChairMan )
	{
		if( 0 != m_ulConfID )
		{
			TUP_RESULT tRet = tup_call_serverconf_end(m_ulConfID);
			if ( TUP_SUCCESS != tRet )
			{
				AfxMessageBox(L"tup_call_end_call failed");
			}
			m_ulConfID = 0;
		}

		if ( 0 != m_DataConfHandle )
		{
			TUP_RESULT tRet = tup_conf_terminate(m_DataConfHandle);
			if ( TUP_SUCCESS != tRet )
			{
				AfxMessageBox(L"tup_conf_terminate failed");
			}
			tRet = tup_conf_release(m_DataConfHandle);
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_conf_release failed");
			}
			m_DataConfHandle = 0;
		}
		m_bIsChairMan = false;
		m_bisPresent = false;
	}
	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
}


void CDataConfDlg::OnNMRClickListConfMenber(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	// 防止在空白区点击弹出菜单
	if (m_listDataConfMember.GetSelectedCount() <= 0)
	{
		return;
	}

	if ( true == m_bIsChairMan )
	{
		int nRow = m_listDataConfMember.GetNextItem(-1, LVIS_SELECTED);
		//获得成员的ID号
		CString cstrCallNo = m_listDataConfMember.GetItemText(nRow,COL_MEM_CALLNO);

		TUP_CHAR ctrCallNo[31] = {0};
		CTools::CString2Char(cstrCallNo, ctrCallNo, sizeof(ctrCallNo)/sizeof(*ctrCallNo));

		CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
		if (NULL != pMainDlg)
		{
			if ( 0 != strcmp( ctrCallNo, pMainDlg->m_CurrentUserInfo.bindNO ))	//当选中的人不是自己
			{
				CPoint hitPt;
				::GetCursorPos(&hitPt);
				CMenu menu;
				menu.LoadMenu(IDR_MENU2);
				if ( NULL != menu.m_hMenu )
				{
					CMenu *pop = menu.GetSubMenu(0);
					if ( NULL != pop )
					{
						pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, hitPt.x, hitPt.y, this);
					}
				}
			}
			pMainDlg = NULL;
		}
	}
	*pResult = 0;
}


void CDataConfDlg::OnDelete()
{
	// TODO: Add your command handler code here
	//////一键删除成员/////
	//1.获取选中的成员信息////
	int nRow = m_listDataConfMember.GetNextItem(-1, LVIS_SELECTED);
	//获得成员的ID号
	CString cstrCallNo = m_listDataConfMember.GetItemText(nRow,COL_MEM_CALLNO);

	TUP_CHAR ctrCallNo[31] = {0};
	CTools::CString2Char(cstrCallNo, ctrCallNo, sizeof(ctrCallNo)/sizeof(*ctrCallNo));

	IM_S_USERINFO userInfo;
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if (NULL != pMainDlg)
	{
		if( !pMainDlg->getAccountInfo(ctrCallNo, IM_E_IMUSERQUERYTYPE_BY_BINDNO, userInfo) )
		{
			AfxMessageBox(_T("Get target user info failed by bind no."));
			return;
		}
	}
	//获得主讲人ID
	TUP_UINT32 uiUserId = atoi(userInfo.bindNO);
	TUP_UINT32 uiPresenterId = 0;
	TUP_RESULT tRet = tup_conf_user_get_presenter( m_DataConfHandle, &uiPresenterId );		//获取主讲人ID
	if ( TC_OK != tRet )
	{
		AfxMessageBox(L"tup_conf_user_get_presenter failed");
	}
	else
	{
		//若被踢出人是主讲人
		if ( uiPresenterId == uiUserId )
		{
			//设定主讲人释放共享权限
			TUP_UINT32 iCurrentUserBindNo = 0;
			iCurrentUserBindNo = atoi(pMainDlg->m_CurrentUserInfo.bindNO);
			tRet = tup_conf_as_set_owner(m_DataConfHandle, uiUserId, AS_ACTION_DELETE);			//指定主讲人释放共享权限
			if ( TC_OK != tRet )
			{
				AfxMessageBox(L"tup_conf_as_set_owner failed");
			}
		}
	}

	//m_DataConfHandle:数据会议的句柄
	//uiUserId:被移除的成员BindNo
	tRet = tup_conf_user_kickout( m_DataConfHandle, uiUserId );
	if ( TUP_SUCCESS != tRet )
	{
		AfxMessageBox(_T("Kick attendee failed"));
		return ;
	}
}


void CDataConfDlg::OnClickedBtnAddAccount()
{
	// TODO: Add your control notification handler code here
	CString cstrKey;
	m_editAddAccount.GetWindowText(cstrKey);
	cstrKey.MakeLower();  //转换成小写

	IM_S_QUERY_ENTADDRESSBOOK_ARG entArg;
	entArg.isNeedAmount = TUP_TRUE;
	entArg.deptID = 0;
	entArg.orderType = IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN;
	entArg.orderModel = IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC;
	entArg.offset = -20;
	entArg.count = 20;
	CTools::CString2Char(cstrKey,entArg.queryKey,IM_D_MAX_DESC_LENGTH);
	IM_S_QUERY_ENTADDRESSBOOK_ACK entAck;
	memset(&entAck,0,sizeof(IM_S_QUERY_ENTADDRESSBOOK_ACK));

	TUP_RESULT tRet = tup_im_queryentaddressbook(&entArg,&entAck);
	if ( TUP_SUCCESS != tRet )
	{
		AfxMessageBox(_T("tup_im_queryentaddressbook failed!"));
		tup_im_release_tup_list(entAck.userList);
		return;
	}

	TUP_S_LIST *pUserItem = entAck.userList;
	if ( NULL == pUserItem )
	{
		AfxMessageBox(_T("Account not exist!"));
		tup_im_release_tup_list(entAck.userList);
		return;
	}

	std::string strCallNO;
	while(NULL != pUserItem)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserItem->data;
		if(NULL != pUser)
		{
			if ( 0 == strcmp( pUser->account, entArg.queryKey ) )
			{
				strCallNO = pUser->bindNO;
				pUserItem = NULL;
				pUser = NULL;
				break;
			}
		}
		pUserItem = pUserItem->next;
	}
	//////释放IM_S_QUERY_ENTADDRESSBOOK_ACK中的tuplist指针////
	tup_im_release_tup_list(entAck.userList);

	if ( strCallNO == "" )
	{
		AfxMessageBox(_T("Account not match!"));
		return;
	}
	int iListMemberSize = m_listDataConfMember.GetItemCount();
	for ( int i = 0; i < iListMemberSize; i++ )
	{
		CString cstrMemberId = m_listDataConfMember.GetItemText(i,COL_MEM_CALLNO);
		CString cstrMemberState = m_listDataConfMember.GetItemText(i,COL_MEM_CALLSTATE);
		CString cstrCallNo;
		CTools::string2CString(strCallNO,cstrCallNo);
		if ( cstrMemberId == cstrCallNo && cstrMemberState == L"会议中" )
		{
			AfxMessageBox(_T("Account already in conference!"));
			return;
		}
	}

	// confid:会议ID
	// count:成员个数
	// number:成员号码组
	// persize:数组成员长度 
	tRet = tup_call_serverconf_add_attendee(m_ulConfID, 1, strCallNO.c_str(), strCallNO.size() + 1);
	if ( TUP_SUCCESS != tRet )
	{
		AfxMessageBox(_T("tup_call_serverconf_add_attendee failed!"));
		return;
	}
	else
	{
		AfxMessageBox(_T("操作成功"));
		return;
	}
}


afx_msg LRESULT CDataConfDlg::OnDataconfEnd(WPARAM wParam, LPARAM lParam)
{
	///如果自己是主讲人但不是主席，退出会议时，将主讲人权限还给主席//////
	//if( true == m_bisPresent && false == m_bChairmanFlag && 0 != m_DataConfHandle )
	//{
	//	TUP_UINT32 iHostId = 0;
	//	TUP_RESULT tRet = tup_conf_user_get_host( m_DataConfHandle, &iHostId );		//查询会议主席
	//	if ( TC_OK != tRet )
	//	{
	//		AfxMessageBox(L"tup_conf_user_get_host failed");
	//	}
	//	else
	//	{
	//		CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	//		if (NULL == pMainDlg)
	//		{
	//			return 0;
	//		}

	//		//设定自己释放共享权限
	//		TUP_UINT32 iCurrentUserBindNo = 0;
	//		iCurrentUserBindNo = atoi(pMainDlg->m_CurrentUserInfo.bindNO);
	//		tRet = tup_conf_as_set_owner(m_DataConfHandle, iCurrentUserBindNo, AS_ACTION_DELETE);			//指定自己释放主讲权限
	//		if ( TC_OK != tRet )
	//		{
	//			AfxMessageBox(L"tup_conf_as_set_owner failed");
	//		}
	//		tRet = tup_conf_user_set_role(m_DataConfHandle,iHostId,CONF_ROLE_PRESENTER);	//直接指定iHostId为主讲人
	//		if ( TC_OK != tRet )		
	//		{
	//			AfxMessageBox(L"tup_conf_user_set_role failed");
	//		}
	//	}
	//}


	if( NULL != m_ulCallID )
	{
		TUP_RESULT tRet = tup_call_end_call(m_ulCallID);		//结束和其他用户的通话或者结束来电。
		if ( TUP_SUCCESS != tRet )
		{
			AfxMessageBox(L"tup_call_end_call failed");
		}
		m_ulCallID = 0;
	}
	if ( NULL != m_ulConfID )
	{
		TUP_RESULT tRet = tup_call_serverconf_leave(m_ulConfID);
		if ( TUP_SUCCESS != tRet )
		{
			AfxMessageBox(L"tup_call_serverconf_leave failed");
		}
		m_ulConfID = 0; 
	}
	if(m_DataConfHandle != 0)
	{
		//tup_conf_terminate(m_handle);
		TUP_RESULT tRet = tup_conf_leave(m_DataConfHandle);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_conf_leave failed");
		}
		tRet = tup_conf_release(m_DataConfHandle);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_conf_release failed");
		}
		m_DataConfHandle = NULL;
	}
	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
	return 0;
}


void CDataConfDlg::OnBnClickedShareDesktop()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT  tRet = tup_conf_as_set_sharetype(m_DataConfHandle,AS_SHARINGTYPE_DESKTOP);
	if( TC_OK != tRet)
	{
		AfxMessageBox(L"tup_conf_as_set_sharetype failed");
		return ;
	}
	tRet = tup_conf_as_start(m_DataConfHandle);
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(L"tup_conf_as_start failed");
		return ;
	}
}


afx_msg LRESULT CDataConfDlg::OnDataconfBeClosed(WPARAM wParam, LPARAM lParam)
{
	if( NULL != m_ulCallID )
	{
	//	TUP_RESULT tRet = tup_call_end_call(m_ulCallID);		//结束和其他用户的通话或者结束来电。
	//	if ( TUP_SUCCESS != tRet )
	//	{
	//		AfxMessageBox(L"tup_call_end_call failed");
	//	}
	//	m_ulCallID = 0;
	}
	if ( NULL != m_ulConfID )
	{
	//	//TUP_RESULT tRet = tup_call_serverconf_leave(m_ulConfID);
	//	//if ( TUP_SUCCESS != tRet )
	//	//{
	//	//	AfxMessageBox(L"tup_call_serverconf_leave failed");
	//	//}
		m_ulConfID = 0; 
	}
	if( 0 != m_DataConfHandle)
	{
	//	//tup_conf_terminate(m_handle);
	//	//TUP_RESULT tRet = tup_conf_leave(m_DataConfHandle);
	//	//if(TUP_SUCCESS != tRet)
	//	//{
	//	//	AfxMessageBox(L"tup_conf_leave failed");
	//	//}
	//	TUP_RESULT tRet = tup_conf_release(m_DataConfHandle);
	//	if(TUP_SUCCESS != tRet)
	//	{
	//		AfxMessageBox(L"tup_conf_release failed");
	//	}
		m_DataConfHandle = 0;
	}
	CWnd::DestroyWindow();
	CeSDK_TUP_PC_CONF_DemoDlg *pMainDlg = (CeSDK_TUP_PC_CONF_DemoDlg*)theApp.m_pMainWnd;	//得到主窗口的指针
	if ( NULL != pMainDlg )
	{
		pMainDlg->m_bInConference = false;
	}
	return 0;
}


void CDataConfDlg::OnBnClickedAttach()
{
	// TODO: Add your control notification handler code here
	TUP_RESULT tRet = tup_conf_as_attach(m_DataConfHandle, AS_CHANNEL_TYPE_NORMAL, NULL);
	if ( TC_OK != tRet )
	{
		AfxMessageBox(L"tup_conf_as_attach failed");
	}
}


afx_msg LRESULT CDataConfDlg::OnDataConfAsOnChannel(WPARAM wParam, LPARAM lParam)
{
	CONF_HANDLE uId = (CONF_HANDLE)wParam;
	TUP_INT32 iChannelType = (TUP_INT32)lParam;
	return 0;
}


void CDataConfDlg::MarkPresent(const TUP_ULONG uiPresentId)
{
	if ( 0 != uiPresentId )
	{
		for( int i = 0; i < m_listDataConfMember.GetItemCount(); i++ )
		{
			m_listDataConfMember.SetItemText(i,COL_MEM_SPK,_T(""));
		}

		//根据BindNo,定位主讲人在那哪一行
		CString cstrNum;
		cstrNum.Format(_T("%u"),uiPresentId);
		int j = 0;
		if (TRUE == FindColum(cstrNum,COL_MEM_CALLNO,j))	//若与会人员中找到此人，则把他标记为主讲人
		{
			//标记其为主讲人
			m_listDataConfMember.SetItemText(j,COL_MEM_SPK,_T("主讲人"));
		}
	}
}


afx_msg LRESULT CDataConfDlg::OnOnekeyToConfResult(WPARAM wParam, LPARAM lParam)
{
	TUP_UINT32 uiResult = (TUP_UINT32)lParam;
	if ( uiResult != 0 )
	{
		AfxMessageBox(_T("join in conference failed,please close conference dialog and try again!"));
	}
	return 0;
}


TUP_UINT32 CDataConfDlg::GetCallId(void)
{
	return m_ulCallID;
}


void CDataConfDlg::SetConfID(TUP_UINT32 ulConfId)
{
	m_ulConfID = ulConfId;
}
