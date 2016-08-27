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

// DataConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "DataConfDlg.h"
#include "NotifyCallBack.h"
#include "Tools.h"
#include <stdlib.h>
#include "SelectDlg.h"
#include "ConfDlg.h"
#include "IMManage.h"
#include "MainDlg.h"

enum DATACONFLIST_COLUMNID
{
	COL_DATACONFMEM_ID, 
	COL_DATACONFMEM_NAME,
	COL_DATACONFMEM_STATUS,
	COL_DATACONFMEM_MUTE
};

enum DOCUMENTLIST_COLUMNID
{
	COL_DOCUMENT_STATE,
	COL_DOCUMENT_NAME
};

enum SHARETYPE
{
	//0表示没有选择//1表示屏幕，2表示文档，3表示白板，4表示程序，5表示媒体
	NOTHING =0,
	DESKTOP,
	DOCUMENT,
	WHITEBOARD,
	PROGRAME,
	MEDIA
};

typedef enum {                 /////定义图片标记的类型
	ANNOTCUSTOMER_PICTURE,
	ANNOTCUSTOMER_MARK,
	ANNOTCUSTOMER_POINTER,

	CUSTOMER_ANNOT_COUNT
};


typedef enum {             /////定义图片标记的Index
	LOCALRES_CHECK,
	LOCALRES_XCHECK,
	LOCALRES_LEFTPOINTER,
	LOCALRES_RIGHTPOINTER,
	LOCALRES_UPPOINTER,
	LOCALRES_DOWNPOINTER,
	LOCALRES_LASERPOINTER,

	LOCALRES_COUNT
};


const int DOC_WIDTH = 1240;
const int NORM_WIDTH = 1050;
// CDataConfDlg 对话框

IMPLEMENT_DYNAMIC(CDataConfDlg, CDialog)

CDataConfDlg::CDataConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataConfDlg::IDD, pParent)
	, m_handle(0)
	,ulConfID(0)
	,ulCallID(0)
	, m_bisChairMan(false)
	,m_bisPresent(false)
	,m_bisMute(false)
    ,m_ChaMainAccount("")
	,m_ChairMainBindNum("")
	,m_PresentAccount("")
	,m_PresentBindNUm("")
	,m_OwnerBindNum("")
	,m_RadButChoice(NOTHING)
	,m_curDoc(0)
	,m_curPage(0)
	,m_laserBegin(false)
{

}

CDataConfDlg::~CDataConfDlg()
{
	/////会议刚创建成功强制关闭会议对话框，导致程序奔溃   c00327158 2015-10-28 Start
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}
	/////会议刚创建成功强制关闭会议对话框，导致程序奔溃   c00327158 2015-10-28 End
}

void CDataConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATACONF_MEMBER, m_DataConfMem);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_stcStatusTxt);
	DDX_Control(pDX, IDC_EDIT_CHAIRMAN, m_edtChairMan);
	DDX_Control(pDX, IDC_EDIT_PRENSENTER, m_edtPresenter);
	DDX_Control(pDX, IDC_BUTTON_SHAREDESK, m_btnSharDesk);
	DDX_Control(pDX, IDC_BUTTON_GET_PRENSNT, m_btnGetPresenterRole);
	DDX_Control(pDX, IDC_STATIC_DESKTOP, m_stcDeskTop);
	DDX_Control(pDX, IDC_STATIC_USER_DESKTOP, m_stcShareState);
	DDX_Control(pDX, IDC_STATIC_V1, m_stcVideo1);
	DDX_Control(pDX, IDC_STATIC_V2, m_stcVideo2);
	DDX_Control(pDX, IDC_STATIC_V3, m_stcVideo3);
	DDX_Control(pDX, IDC_STATIC_V4, m_stcVideo4);
	DDX_Control(pDX, IDC_STATIC_V5, m_stcVideo5);
	DDX_Control(pDX, IDC_STATIC_V6, m_stcVideo6);
	DDX_Control(pDX, IDC_STATIC_CharManVideo, m_PresentOrChairmanVideo);
	DDX_Control(pDX, IDC_STATIC_V7, m_stcVideo7);
	DDX_Control(pDX, IDC_BUTTON_OPENVIDEO, m_btnOpenCammer);
	DDX_Control(pDX, IDC_DATA_COMBO, m_DataComBox);
	DDX_Control(pDX, IDC_LIST_DOC, m_DocOrBoardList);
	DDX_Control(pDX, IDC_COMB_ACTIONTYPE, m_PenType);
	DDX_Control(pDX, IDC_COMBO1, m_LineWidth);
	DDX_Control(pDX, IDC_COMB_SELECT, m_comSelectPage);
}


BEGIN_MESSAGE_MAP(CDataConfDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SHAREDESK, &CDataConfDlg::OnBnClickedButtonSharedesk)
	ON_BN_CLICKED(IDC_BUTTON_GET_PRENSNT, &CDataConfDlg::OnBnClickedButtonGetPrensnt)
	ON_MESSAGE(WM_DATACONF_JOINSUCCESS,&CDataConfDlg::OnJoinDataConfSuccess)
	ON_MESSAGE(WM_DATACONF_LOADCOM_SUCCESS,&CDataConfDlg::OnLoadComponetSuccess)
	ON_MESSAGE(WM_DATACONF_USER_ADD,&CDataConfDlg::OnDataConfUserAdd)
	ON_MESSAGE(WM_DATACONF_USER_DEL,&CDataConfDlg::OnDataConfUserDEL)
	ON_MESSAGE(WM_CONF_ADD_MEM_FAIL,&CDataConfDlg::OnInviteMemberFailed)
	ON_MESSAGE(WM_DATACONF_END,&CDataConfDlg::OnDataConfEnd)
	ON_MESSAGE(WM_DATACONF_AS_OWNER_NOTIFY,&CDataConfDlg::OnDataConfASGetOwerOK)	
	ON_MESSAGE(WM_DATACONF_AS_SCREENDATA_NOTIFY,&CDataConfDlg::OnDataConfASUpdateScreen)
	ON_MESSAGE(WM_DATACONF_AS_STATE_NOTIFY,&CDataConfDlg::OnDataConfASStateShare)
	ON_MESSAGE(WM_DATACONF_ADD_VIDEO,&CDataConfDlg::OnDataConfAddVideoUser)
	ON_MESSAGE(WM_DATACONF_DEL_VIDEO,&CDataConfDlg::OnDataConfDelVideoUser)
	ON_MESSAGE(WM_DATACONF_UPDATE_PRESENTINFO,&CDataConfDlg::UpdatePresentInfo)
	ON_MESSAGE(WM_DATACONF_UPDATE_CHAIRMAININFO,&CDataConfDlg::UpdateChairmainInfo)    
	ON_MESSAGE(WM_DATACONF_UPDATE_MUTE,&CDataConfDlg::UpdateMuteInfo)
	ON_MESSAGE(WM_DATACONF_DOCUMENT_WND,&CDataConfDlg::OnDocumentWnd)
	ON_MESSAGE(WM_DATACONF_WB_DOC_NEW,&CDataConfDlg::OnNewDocSuc)
	ON_MESSAGE(WM_DATACONF_WB_DOC_DEL,&CDataConfDlg::OnDelDocSuc)
	ON_MESSAGE(WM_DATACONF_WB_PAG_NEW,&CDataConfDlg::OnNewPageSuc)
	ON_MESSAGE(WM_DATACONF_WB_DRAW,&CDataConfDlg::OnDrawWhileBackData)
	ON_MESSAGE(WM_DATACONF_WB_PAGE_IND,&CDataConfDlg::OnPageInd)
	ON_MESSAGE(WM_DATACONF_LAYOUT_CHANGE,&CDataConfDlg::OnLayoutChange)
	ON_MESSAGE(WM_DATACONF_WB_REFRESH_INFO, &CDataConfDlg::OnRefreshDocInf)
	ON_BN_CLICKED(IDC_BUTTON_OPENVIDEO, &CDataConfDlg::OnBnClickedButtonOpenvideo)
	ON_BN_CLICKED(IDC_BT_ADD, &CDataConfDlg::OnBnClickedBtAdd)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RAD_NULL,IDC_RAD_MEDIA,&CDataConfDlg::OnBnClickRadio)
	ON_CONTROL_RANGE(BN_CLICKED,ID_DATACONF_DEL_MEM_MENU,ID_DATACONF_INVITEDTOSHARE_MEM_MENU,&CDataConfDlg::OnClickListMemMenu)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DATACONF_MEMBER, &CDataConfDlg::OnNMRClickListDataconfMember)
	ON_BN_CLICKED(IDC_BT_ConfMute, &CDataConfDlg::OnBnClickedBtConfmute)
	ON_BN_CLICKED(IDC_BT_OPEN_NEW, &CDataConfDlg::OnBnClickedBtOpenNew)
	ON_BN_CLICKED(IDC_BT_SELECTCOLOR, &CDataConfDlg::OnBnClickedBtSelectcolor)
	ON_BN_CLICKED(IDC_BT_NEWPAGE, &CDataConfDlg::OnBnClickedBtNewpage)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMB_ACTIONTYPE, &CDataConfDlg::OnCbnSelchangeCombActiontype)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDataConfDlg::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DOC, &CDataConfDlg::OnNMDblclkListDoc)
	ON_BN_CLICKED(IDC_BT_DELDOC, &CDataConfDlg::OnBnClickedBtDeldoc)
	ON_BN_CLICKED(IDC_BT_SALVE, &CDataConfDlg::OnBnClickedBtSalve)
	ON_BN_CLICKED(IDC_BT_LOAD, &CDataConfDlg::OnBnClickedBtLoad)
	ON_BN_CLICKED(IDC_BT_COPYPAGE, &CDataConfDlg::OnBnClickedBtCopypage)
	ON_BN_CLICKED(IDC_BT_DELPAGE, &CDataConfDlg::OnBnClickedBtDelpage)
	ON_BN_CLICKED(IDC_BT_PREPAGE, &CDataConfDlg::OnBnClickedBtPrepage)
	ON_BN_CLICKED(IDC_BT_NEXTPAGE, &CDataConfDlg::OnBnClickedBtNextpage)
	ON_CBN_SELCHANGE(IDC_COMB_SELECT, &CDataConfDlg::OnCbnSelchangeCombSelect)
	ON_BN_CLICKED(IDC_BT_UPDATE, &CDataConfDlg::OnBnClickedBtUpdate)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BT_CALCLE, &CDataConfDlg::OnBnClickedBtCalcle)
	ON_BN_CLICKED(IDC_BT_DEL, &CDataConfDlg::OnBnClickedBtDel)
END_MESSAGE_MAP()


// CDataConfDlg 消息处理程序

BOOL CDataConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_DataConfMem.DeleteAllItems();

	m_DataConfMem.ModifyStyle(0,LVS_SINGLESEL);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_ID, _T("ID"), LVCFMT_LEFT, 50);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_NAME, _T("姓名"), LVCFMT_LEFT, 115);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_STATUS, _T("状态"), LVCFMT_LEFT, 60);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_MUTE, _T("静音"), LVCFMT_LEFT, 60);
	DWORD dwStyle = m_DataConfMem.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_DataConfMem.SetExtendedStyle(dwStyle); //设置扩展风格

	m_btnGetPresenterRole.EnableWindow(FALSE);
	m_btnSharDesk.EnableWindow(FALSE);

	/////设置共享按钮状态/////
	CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_NULL);
	m_btnSharDesk.SetWindowText(L"请选择共享类型");
	m_btnSharDesk.EnableWindow(FALSE);

	//////初始界面视频显示框/////
	m_videoDis[0]= GetDlgItem(IDC_STATIC_V2);
 	m_videoDis[1]= GetDlgItem(IDC_STATIC_V3);
 	m_videoDis[2]= GetDlgItem(IDC_STATIC_V4);
 	m_videoDis[3]= GetDlgItem(IDC_STATIC_V5);
 	m_videoDis[4]= GetDlgItem(IDC_STATIC_V6);
 	m_videoDis[5]= GetDlgItem(IDC_STATIC_V7);
	//////初始化摄像头装置//////////
	TUP_UINT32 retCount;
	TUP_RESULT tRet = tup_conf_video_get_deviceinfo(m_handle,NULL,&retCount);
	if(tRet != TC_OK||retCount == 0)
	{
		GetDlgItem(IDC_BUTTON_OPENVIDEO)->EnableWindow(FALSE);
		m_DataComBox.InsertString(0,L"无视频设备");
	}
	else
	{
		//////增加视频模块//////
			TC_DEVICE_INFO *info = new TC_DEVICE_INFO[retCount];
			tup_conf_video_get_deviceinfo(m_handle,info,&retCount);
		    for (int i = 0;i < retCount ;i++)
		    {
				m_DataComBox.InsertString(i,CTools::UTF2UNICODE(info[i]._szName));
				m_DataComBox.SetItemData(i,info[i]._DeviceID);
		    }
			delete []info;
			info = NULL;
	}
	m_DataComBox.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDataConfDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	/////将颜色绘制在控件上////////
	CDC *pDC = GetDlgItem(IDC_STATIC_COLOR)->GetDC();
	CRect m_rct;
	GetDlgItem(IDC_STATIC_COLOR)->GetClientRect(m_rct);
	CBrush m_brs;
	m_brs.CreateSolidBrush(m_penInfo.m_clr);
	pDC->FillRect(&m_rct,&m_brs);

}

void CDataConfDlg::StartConf(CALL_S_DATACONF_PARAM* pNotify)
{
	if(0 != m_handle)
	{
		return;
	}
	m_stcStatusTxt.SetWindowText(L"正在加入数据会议");
	//会议信息
	TC_CONF_INFO* confInfo = new TC_CONF_INFO;
	TUP_UINT8 * pdata = new TUP_UINT8[10];
	memset(pdata, '8', 10);
	pdata[9] = 0;
	confInfo->conf_id = atoi(pNotify->acDataConfID);
	confInfo->user_id = g_UserID;
	confInfo->os_type = CONF_OS_WIN;
	confInfo->dev_type = CONF_DEV_PC;
	confInfo->user_info = pdata;
	confInfo->user_info_len = 9;
	//confInfo->conf_title;
	memset(confInfo->conf_title,0,TC_MAX_CONF_TITLE_LEN);
	if(CALL_E_CONF_ROLE_CHAIRMAN == pNotify->enRole)
	{
		confInfo->user_type = CONF_ROLE_PRESENTER + CONF_ROLE_HOST;
		m_bisChairMan = true;
	}
	else if(CALL_E_CONF_ROLE_ATTENDEE == pNotify->enRole)
	{
		confInfo->user_type = CONF_ROLE_GENERAL;
		m_bisChairMan = false;
		////取消全体静音功能////
		(CButton *)GetDlgItem(IDC_BT_ConfMute)->EnableWindow(FALSE);
		////取消增加成员权限//////
		(CButton *)GetDlgItem(IDC_BT_ADD)->EnableWindow(FALSE);
	}
	
	strcpy(confInfo->user_name,g_Name.c_str());
	strcpy(confInfo->host_key, "111111");
	strcpy(confInfo->site_id, "6jf1");
	strcpy(confInfo->ms_server_ip,g_DataConfAddr.c_str());
	strcpy(confInfo->encryption_key, pNotify->acAuthKey);
	strcpy(confInfo->site_url, pNotify->acCmAddr);
	strcpy(confInfo->user_log_uri,g_BindNO.c_str());
	CONF_HANDLE handle;
	TUP_RESULT tRet = tup_conf_new(NotifyCallBack::ConfNotify, confInfo, CONF_OPTION_BASE | CONF_OPTION_USERLIST|CONF_OPTION_PHONE|CONF_OPTION_PRESENTER_GRAB,&handle);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_new failed."));
		return;
	}

	m_handle = handle;



	tRet = tup_conf_join(handle);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_join failed."));
		return;
	}

	/////更新本地会议ID
	SetConfID(pNotify->ulConfID);
	SetCallID(pNotify->ulCallID);
	/////设置初始会议成员信息/////
	InitiMenberlist(ulConfID,pNotify->acGroupUri);
	
	////保存主席相关信息/////
	IM_S_USERINFO m_CharmanInfo;
	if (0 == strlen(pNotify->acCharman))
	{
		////此时pNotify.acCharman（USM不带主席信息）那么，我们就查询群组的拥有者，指定其为主席//////
		IM_S_IMGROUPINFO _groupInfo;
 		tRet = tup_im_getfixedgroupdetail(pNotify->acGroupUri,&_groupInfo);
		if (tRet != TUP_SUCCESS || !getAccountINfoByAccount(std::string(_groupInfo.owner),m_CharmanInfo))
		{
			CTools::ShowMessageTimeout(_T("获取主席信息失败"),2000);
			return;
		}

	}
	else
	{
		if (!getAccountINfoByBingNum(std::string(pNotify->acCharman),m_CharmanInfo))
		{
			CTools::ShowMessageTimeout(_T("获取主席信息失败"),2000);
			return;
		}
	}
	m_ChairMainBindNum = m_CharmanInfo.bindNO;
	m_ChaMainAccount = m_CharmanInfo.account;
	std::string m_ChairmanName = m_CharmanInfo.name;
	CString m_str;
	CTools::string2CString(m_ChairmanName,m_str);
	m_edtChairMan.SetWindowText(m_str);

	/////初始化视频会议等按钮/////
	InitVideoINfo();
	////初始化数据会议界面，将界面初始化成共享界面形式////
	SendMessage(WM_DATACONF_DOCUMENT_WND,0,NULL);
	InitShareButton();
	m_stcDeskTop.m_handle = m_handle;
	////初始化数据会议界面，将界面初始化成共享界面形式////

	////析构参数/////
	delete confInfo;   /*pdata 在confInfo析构的时候会被析构掉，这儿不需要单独释放pdata */
	confInfo = NULL;
	
	SAFE_DELETE(pNotify);
	return;
}

LRESULT CDataConfDlg::OnDataConfEnd(WPARAM,LPARAM)
{
	OnClose();
	return 0L;
}

void CDataConfDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_handle != 0)
	{

		if(m_bisChairMan)
		{
		   tup_conf_terminate(m_handle);
			CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByConfID(ulConfID);
			if(pDlg != NULL)
			{
				pDlg->EnableCallButton(true);
			}
		}	
		else
		{
			/////如果自己是主讲人，退出会议时，将主讲人权限设置给主席//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}
	}
	////语音会议也需要关闭////
	if(ulCallID != 0)
	{
		tup_call_end_call(ulCallID);
		ulCallID = 0;
	}
	if(ulConfID != 0)
	{
		if(m_bisChairMan)
		{
			tup_call_serverconf_end(ulConfID);
		}
		else
		{
			tup_call_serverconf_leave(ulConfID);
		}

		ulConfID = 0;
	}


	m_DataConfMem.DeleteAllItems();
	m_LocalMenber.clear();
	ulConfID = 0;
    ulCallID = 0;
	m_bisChairMan = false;
    m_bisPresent = false;
	m_ChaMainAccount = "";
	m_ChairMainBindNum = "";
	m_PresentAccount = "";
	m_PresentBindNUm = "";
	m_OwnerBindNum = "";
	m_bisMute = false;
	m_RadButChoice = NOTHING ;
	m_laserBegin = false;
	m_curDoc = 0;
	m_curPage = 0;
	m_edtPresenter.SetWindowText(L"");
	m_edtChairMan.SetWindowText(L"");
	///////发布状态///////
	if(!PubSelfStatus(IM_E_STATUS_ONLINE))
	{
		TRACE("PubSelf Status Failed");
	}

	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_DATACONF_END,(WPARAM)this,NULL);
	OnOK();
	CDialog::OnClose();
}

void CDataConfDlg::OnBnClickedButtonSharedesk()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_RadButChoice)
	{
	case NOTHING:
	{
		return ;
		break;
	}
	case DESKTOP:
		{
			//////共享屏幕//////
			CString m_str ;
			m_btnSharDesk.GetWindowText(m_str);
			if (L"共享屏幕" == m_str)
			{
				TUP_RESULT  tRet = tup_conf_as_set_sharetype(m_handle,AS_SHARINGTYPE_DESKTOP);
				if(tRet != TUP_SUCCESS)
				{
					AfxMessageBox(L"tup_conf_as_set_sharetype failed");
					InitShareButton();
					return ;
				}
				tRet = tup_conf_as_start(m_handle);
				if(tRet != TUP_SUCCESS)
				{
					AfxMessageBox(L"tup_conf_as_start failed");
					InitShareButton();
					return ;
				}
				m_btnSharDesk.SetWindowText(L"停止共享");
			}else if (L"停止共享" == m_str)
			{
				TUP_RESULT tRet = tup_conf_as_stop(m_handle);
				if(tRet != TUP_SUCCESS)
				{
					AfxMessageBox(L"tup_conf_as_stop failed");
					InitShareButton();
					return ;
				}
				m_btnSharDesk.SetWindowText(L"共享屏幕");

			}
			else
			{
				return ;
			}

		}
		break;
	case DOCUMENT:
		{
			//to do
		}
		break;
	case WHITEBOARD:
		{
			/////白板文档//////
		}
		break;
	case PROGRAME:
		{
			//to do
		}
		break;
	case MEDIA:
		{
			//to do
		}
		break;
	default:
		{
			return ;
	
		}
		break;
	}

}

LRESULT CDataConfDlg::OnJoinDataConfSuccess(WPARAM,LPARAM)
{
	m_stcStatusTxt.SetWindowText(L"加入数据会议成功");
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
		AfxMessageBox(_T("tup_conf_reg_component_callback WhiteBoard failed."));
		return -1L;
	}

	tRet = tup_conf_reg_component_callback(m_handle,IID_COMPONENT_DS,NotifyCallBack::ConfComDSNotify);

	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_conf_reg_component_callback DocumentShare failed."));
		return -1L;
	}

	m_btnGetPresenterRole.EnableWindow(TRUE);

	///////发布状态///////
	if(!PubSelfStatus(IM_E_STATUS_BUSY))
	{
		TRACE("PubSelf Status Failed");
	}

	if(m_bisChairMan)
	{
		tup_conf_as_set_owner(m_handle,g_UserID,AS_ACTION_ADD);
	}
	return 0L;
}
LRESULT CDataConfDlg::OnLoadComponetSuccess(WPARAM w,LPARAM)
{
	CString cstr;
	TUP_ULONG id = (TUP_ULONG)w;
	switch (id)
	{
	case IID_COMPONENT_BASE:
		{
			cstr.Format(L"load IID_COMPONENT_BASE success");
		}break;
	case IID_COMPONENT_DS:
		{
			cstr.Format(L"load IID_COMPONENT_DS success");
		}break;
	case IID_COMPONENT_AS:
		{
			cstr.Format(L"load IID_COMPONENT_AS success");
		}break;
	case IID_COMPONENT_AUDIO:
		{
			cstr.Format(L"load IID_COMPONENT_AUDIO success");
		}break;
	case IID_COMPONENT_VIDEO:
		{
			cstr.Format(L"load IID_COMPONENT_VIDEO success");
		}break;
	case IID_COMPONENT_RECORD:
		{
			cstr.Format(L"load  IID_COMPONENT_RECORD success");
		}break;
	case IID_COMPONENT_CHAT:
		{
			cstr.Format(L"load IID_COMPONENT_CHAT success");
		}break;
	case IID_COMPONENT_POLLING:
		{
			cstr.Format(L"load IID_COMPONENT_POLLING success");
		}break;
	case IID_COMPONENT_MS:
		{
			cstr.Format(L"load IID_COMPONENT_MS success");
		}break;
	case IID_COMPONENT_FT:
		{
			cstr.Format(L"load IID_COMPONENT_FT success");
		}break;
	case IID_COMPONENT_WB:
		{
			cstr.Format(L"load IID_COMPONENT_WB success");
	    	InitWhiteBackElement();
		}break;
	default:
		break;
	}
	TRACE(cstr);
	m_stcStatusTxt.SetWindowText(cstr);
	return 0L;
}
LRESULT CDataConfDlg::OnDataConfUserAdd(WPARAM w,LPARAM l)
{
	TUP_ULONG role = (TUP_ULONG)w;
	TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)l;
	if(NULL == pRecord || (pRecord->user_alt_id<0) || (pRecord->user_alt_id >4294967295))
	{
		return -1L;
	}
	AddConfMemBer(pRecord);

	SAFE_DELETE(pRecord);
	return 0L;
}
LRESULT CDataConfDlg::OnDataConfUserDEL(WPARAM w,LPARAM l)
{
	TUP_ULONG role = (TUP_ULONG)w;
	TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)l;
	if(NULL == pRecord)
	{
		return -1L;
	}
	DleConfMemBer(pRecord);

	SAFE_DELETE(pRecord);
	return 0L;
}
LRESULT CDataConfDlg::OnInviteMemberFailed(WPARAM w,LPARAM l)
{
	//////邀请用户失败，需要修改下用户列表的界面显示/////
	char* num = (char*)w;
	int iSize = m_DataConfMem.GetItemCount();
	for (int i = 0;i<iSize;i++)
	{
		TUP_ULONG m_BindNUm = m_DataConfMem.GetItemData(i);
		if (m_BindNUm == CTools::str2num(num))
		{
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"挂断");
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"");
		}
	}
	return 0L;
}

LRESULT CDataConfDlg::OnDataConfASGetOwerOK(WPARAM l,LPARAM m)
{
	bool m_IsSucess = l;
	TUP_ULONG m_OwnerId = (TUP_ULONG)m;
	if (!GetUserBindNumByid(m_OwnerId,m_OwnerBindNum))
	{
		m_OwnerBindNum = "";
		return -1L;
	}
	/////查找具有共享权限的人的信息////
	IM_S_USERINFO m_OwnerInfo;
	if (!getAccountINfoByBingNum(m_OwnerBindNum,m_OwnerInfo))
	{
		return -1L;
	}
	std::string m_OwnerName = m_OwnerInfo.name;
	CString m_strname;
	CTools::string2CString(m_OwnerName,m_strname);
	///////默认有共享权限的人是主讲人   Start/////////
	if (m_IsSucess)
	{
		m_edtPresenter.SetWindowText(m_strname);
		//////检查是否是会场静音//////
		if (m_bisMute)
		{
			int iSize = m_DataConfMem.GetItemCount();
			for (int i = 0;i<iSize;i++)
			{
				if (m_OwnerInfo.bindNO == CTools::num2str(m_DataConfMem.GetItemData(i)))
				 {
					 m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
					 m_PresentBindNUm = m_OwnerInfo.bindNO;
				 }
			}

		}
	}

	///////默认有共享权限的人是主讲人   End/////////

	m_strname+=L"具有共享权限";
	m_stcShareState.SetWindowText(m_strname);
	InitShareButton();
	if (!m_IsSucess)
	{
		/////设置没有成功//////
		m_btnGetPresenterRole.EnableWindow(TRUE);
		if (m_bisPresent)
		{
			Sleep(1000);
			(void)tup_conf_as_set_owner(m_handle,m_OwnerId,AS_ACTION_ADD);
			m_btnGetPresenterRole.EnableWindow(FALSE);

		}
	}

	/////默认具有共享权限的人才能更换共享模式///////
	if(m_OwnerId == g_UserID)
	{
		GetDlgItem(IDC_RAD_NULL)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_SCREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_DOC)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAD_WHITEBOARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAD_MEDIA)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_RAD_NULL)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAD_SCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAD_DOC)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAD_WHITEBOARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAD_MEDIA)->EnableWindow(FALSE);
	}

	return 0L;
}

LRESULT CDataConfDlg::OnDataConfASUpdateScreen(WPARAM,LPARAM)
{
	TC_AS_SCREENDATA screenData;
	tup_conf_as_get_screendata(m_handle,&screenData);	

	TRACE("\nScreenData:[%d][0X%x][0X%x]\n",screenData.ucDataType,screenData.pUpdateInfo,screenData.pData);
	
	TC_AS_ScreenDataInfo *pInfo = (TC_AS_ScreenDataInfo*)(screenData.pUpdateInfo);
	if(NULL == pInfo)
	{
		return -1L;
	}

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

	return 0L;
}

LRESULT CDataConfDlg::OnDataConfASStateShare(WPARAM ,LPARAM l)
{
	unsigned long ulState = (unsigned long)l;
	switch (ulState)
	{
	case AS_STATE_NULL:
		{
			m_stcDeskTop.SetBitmap2(NULL);
			m_stcShareState.SetWindowText(L"无人共享");
			break;
		}
	case AS_STATE_START:
	case AS_STATE_VIEW:
		{
			m_stcShareState.SetWindowText(L"正在共享");
			break;
		}
	}
	return 0L;
}

void CDataConfDlg::AddConfMemBer(TC_Conf_User_Record* pRecord)
{
	std::string name = pRecord->user_name;
	std::string bindno = pRecord->user_alt_uri;
	CString cstrID;
	char strID[25]={0};
	itoa(pRecord->user_alt_id,strID,10);
	CTools::string2CString(strID,cstrID);

	///查询与会者是否存在
	if (SetUseridByBindNum(pRecord->user_alt_uri,pRecord->user_alt_id))
	{
		//修改界面状态信息
		int iSize = m_DataConfMem.GetItemCount();
		for (int i = 0;i<iSize;i++)
		{
			TUP_ULONG m_BindNUm = m_DataConfMem.GetItemData(i);
			if (m_BindNUm == CTools::str2num(bindno))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_ID,cstrID);
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"会议中");
				if (m_bisMute)
				{

					m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"静音");
					
				}
				else
				{
					m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
				}
				
			}

		}

	}
	else
	{
		int iSize = m_DataConfMem.GetItemCount();
		m_DataConfMem.InsertItem(iSize,L"");
		m_DataConfMem.SetItemData(iSize,CTools::str2num(pRecord->user_alt_uri));
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_ID,cstrID);
		std::string content = name+"("+bindno+")";
		CString cstrContent;
		CTools::string2CString(content,cstrContent);
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_NAME,cstrContent);
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_STATUS,L"会议中");
		if (m_bisMute)
		{
			/////会场被静音/////
			if (isChairManOrPresent(cstrContent))
			{
				m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"未静音");
			}
			else
			{
				m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"静音");
			}

			/////会场静音条件下，自己加入时应该讲自己设置成静音状态/////////////
			if (g_UserID == pRecord->user_alt_id)
			{
                (void)tup_call_media_mute_mic(ulCallID,TUP_TRUE);
			}
		}
		else
		{
			m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"未静音");
		}

		////本地存储与会者信息//////
		m_LocalMenber[pRecord->user_alt_uri] = pRecord->user_alt_id;

	}
}
void CDataConfDlg::DleConfMemBer(TC_Conf_User_Record* pRecord)
{
	std::string bindno = pRecord->user_alt_uri;
	if (SetUseridByBindNum(pRecord->user_alt_uri,pRecord->user_alt_id))
	{
		//修改界面状态信息
		int iSize = m_DataConfMem.GetItemCount();
		for (int i = 0;i<iSize;i++)
		{
			TUP_ULONG m_BindNUm = m_DataConfMem.GetItemData(i);
			if (m_BindNUm == CTools::str2num(bindno))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"挂断");
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"");
			}

		}

	}
	else
	{
		return ;
	}
	
}
void CDataConfDlg::OnBnClickedButtonGetPrensnt()
{
	// TODO: 在此添加控件通知处理程序代码
	TUP_RESULT tRet = tup_conf_user_request_role(m_handle,CONF_ROLE_PRESENTER,"");
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("Get ROLE_PRESENTER Failed！"));
	}
	////获取共享拥有者//////
	IM_S_USERINFO m_userInfo;
	if (! getAccountINfoByBingNum(g_BindNO, m_userInfo))
	{
		return ;
	}

	 tRet = tup_conf_as_set_owner(m_handle,m_userInfo.staffID,AS_ACTION_ADD);
	if(tRet != TC_OK)
	{
		AfxMessageBox(L"tup_conf_as_set_owner failed");
	}
}

void CDataConfDlg::OnBnClickedButtonOpenvideo()
{
	// TODO: 在此添加控件通知处理程序代码

// 	//获取视频设备
 	TUP_RESULT tRet = TUP_FALSE;
// 	int index = m_DataComBox.GetCurSel();

	////开启或者关闭摄像头/////
    CString m_str;
	GetDlgItem(IDC_BUTTON_OPENVIDEO)->GetWindowText(m_str);
	if (m_str == L"开启摄像头")
	{
		tRet = tup_conf_video_open(m_handle,m_DataComBox.GetItemData(m_DataComBox.GetCurSel()),TUP_TRUE);
		if(tRet != TC_OK)
		{
			AfxMessageBox(L"tup_conf_video_open failed");
			return;
		}

		/////主席通知其他参与这打开视频/////
		TC_VIDEO_PARAM para;
		para.dwUserID	= 0;
		para.dwDeviceID	= 0;
		para.xResolution = 0;
		para.yResolution = 0;
		para.nFrameRate	= 0;
		para.nBitRate	= 0;
		para.nRawtype	= 0;
		para.nFecValue	= 0;
		LocalMember::iterator iter=m_LocalMenber.begin();
		for (;iter!=m_LocalMenber.end();iter++)
		{
			TUP_UINT32 m_BindNum = CTools::str2num(iter->first);
			tup_conf_video_notify(m_handle,VIDEO_NOTIFY_OPEN,m_BindNum,&para);
		}

		GetDlgItem(IDC_BUTTON_OPENVIDEO)->SetWindowText(L"关闭摄像头");
	}
	else
	{
		/////关闭视频////
		tRet = tup_conf_video_close(m_handle,m_DataComBox.GetItemData(m_DataComBox.GetCurSel()));
		if(tRet != TC_OK)
		{
			AfxMessageBox(L"tup_conf_video_open failed");
			return ;
		}
		GetDlgItem(IDC_BUTTON_OPENVIDEO)->SetWindowText(L"开启摄像头");
	}

	
}
LRESULT CDataConfDlg::OnDataConfAddVideoUser(WPARAM id,LPARAM l)
{

	TUP_UINT32* deviceid = (TUP_UINT32*)l;/////设备////
	TUP_ULONG m_ConfMemId = (TUP_ULONG) id;

	std::string m_BindNum;
	if (!GetUserBindNumByid(m_ConfMemId,m_BindNum))
	{
		return -1L;
	}

	if (m_BindNum == g_BindNO)
	{
		/////自己的视频
		if (m_bisChairMan)
		{
			TUP_RESULT tRet = tup_conf_video_attach(m_handle,g_UserID,*deviceid,(TUP_VOID*)m_PresentOrChairmanVideo.GetSafeHwnd(),TUP_TRUE,0);
			if(tRet != TC_OK)
			{
				AfxMessageBox(L"tup_conf_video_attach failed");
				return -1L;
			}
		}
		else
		{
			GetDlgItem(IDC_STATIC_V1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_S_V8)->ShowWindow(SW_SHOW);
			TUP_RESULT tRet = tup_conf_video_attach(m_handle,g_UserID,*deviceid,(TUP_VOID*)m_stcVideo1.GetSafeHwnd(),TUP_TRUE,0);
			if(tRet != TC_OK)
			{
				AfxMessageBox(L"tup_conf_video_attach failed");
				return -1L;
			}

		}
		return 0L;
	}else if (m_BindNum == m_ChairMainBindNum)
	{
		/////主席///////
		IM_S_USERINFO m_userInfo;
		if(!getAccountINfoByBingNum(m_BindNum,m_userInfo)) return 0L;
		TUP_RESULT tRet = tup_conf_video_attach(m_handle,m_userInfo.staffID,*deviceid,(TUP_VOID*)m_PresentOrChairmanVideo.GetSafeHwnd(),TUP_TRUE,0);
		if(tRet != TC_OK)
		{
			AfxMessageBox(L"tup_conf_video_attach failed");
			return -1L;
		}
		return 0L;
	}
	else
	{
        ////普通与会者/////
		IM_S_USERINFO m_userInfo;
		if(!getAccountINfoByBingNum(m_BindNum,m_userInfo)) return 0L;
		int m_VideoINfoIndex;
		/////查询可用的视窗界面//////
		if (!AvaluableVudeo(m_VideoINfoIndex))
		{
			return -1L;
		}
		m_LocalVideoINfo[m_VideoINfoIndex].isValuable = false;
		m_LocalVideoINfo[m_VideoINfoIndex].Devideid = *deviceid;
		m_LocalVideoINfo[m_VideoINfoIndex].Userid = m_ConfMemId;
		///////设置显示信息///////
		CWnd *m_wid;
		m_wid = m_LocalVideoINfo[m_VideoINfoIndex].m_VideoDisp;
		m_wid->ShowWindow(SW_SHOW);
		TUP_RESULT tRet = tup_conf_video_attach(m_handle,m_userInfo.staffID,*deviceid,m_wid->GetSafeHwnd(),TUP_TRUE,0);
		if(tRet != TC_OK)
		{
			AfxMessageBox(L"tup_conf_video_attach failed");
			return -1L;
		}

		m_wid =  m_LocalVideoINfo[m_VideoINfoIndex].m_NameDisp;
		m_wid->ShowWindow(SW_SHOW);
		CString m_str;
		CTools::string2CString(m_userInfo.name,m_str);
		m_wid->SetWindowText(m_str);
		return 0L;
	}
}

LRESULT CDataConfDlg::OnDataConfDelVideoUser(WPARAM id,LPARAM l)
{

	/////减少本地视频/////
	TUP_UINT32* deviceid = (TUP_UINT32*)l;/////设备////
	TUP_ULONG m_ConfMemId = (TUP_ULONG) id;

	std::string m_BindNum;
	if (!GetUserBindNumByid(m_ConfMemId,m_BindNum))
	{
		return -1L;
	}

	if (m_BindNum == g_BindNO)
	{
		if (!m_bisChairMan)
		{
			GetDlgItem(IDC_STATIC_V1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_S_V8)->ShowWindow(SW_HIDE);
		}
		else
		{
			Invalidate(TRUE);
		}
		/////自己的视频
		return 0L;
	}else if (m_BindNum == m_ChairMainBindNum)
	{
		Invalidate(TRUE);
		/////主席///////
		return 0L;
	}
	else
	{
		/////查找关闭的窗口index;
		int m_VideoINfoIndex;
		if (!GetVideoINdexByid(m_VideoINfoIndex,id))
		{
			return -1L;
		}
		m_LocalVideoINfo[m_VideoINfoIndex].isValuable = true;
		m_LocalVideoINfo[m_VideoINfoIndex].Devideid = 0;
		m_LocalVideoINfo[m_VideoINfoIndex].Userid = 0;
		///////设置显示信息///////
		CWnd *m_wid;
		m_wid = m_LocalVideoINfo[m_VideoINfoIndex].m_VideoDisp;
		m_wid->ShowWindow(SW_HIDE);
		m_wid = m_LocalVideoINfo[m_VideoINfoIndex].m_NameDisp;
		m_wid->ShowWindow(SW_HIDE);
		m_wid->SetWindowText(L"");
	   return 0L;
	}
}

LRESULT CDataConfDlg::UpdateChairmainInfo(WPARAM w,LPARAM l)
{

	TUP_ULONG id = TUP_ULONG(w);
	bool m_isMe = bool(l);
	IM_S_USERINFO m_CharmanInfo;

	if (m_isMe)
	{
		///从自己的登录账号查找g_BindNO
		if(!getAccountINfoByBingNum(g_BindNO,m_CharmanInfo))  
		{
			return -1L;
		}
		/////本地记录主持人信息/////
		m_ChairMainBindNum = g_BindNO;
		m_bisChairMan = true;
	} 
	else
	{
		/////查询主持人信息///////
		if (!GetUserBindNumByid(id,m_ChairMainBindNum))
		{
			return -1L;
		}

		if(!getAccountINfoByBingNum(m_ChairMainBindNum,m_CharmanInfo))  
		{
			return -1L;
		}
		if (m_ChairMainBindNum != g_BindNO)
		{
			m_bisChairMan = false;
		}
	}

	//////显示主持人信息/////
	m_ChaMainAccount = m_CharmanInfo.account;
	m_ChairMainBindNum = m_CharmanInfo.bindNO;
	std::string m_ChairmanName = m_CharmanInfo.name;
	CString m_str;
	CTools::string2CString(m_ChairmanName,m_str);
	m_edtChairMan.SetWindowText(m_str);
	return 0L;
}


LRESULT CDataConfDlg::UpdatePresentInfo(WPARAM w,LPARAM l)
{
	TUP_ULONG m_prePresentid = w;   ////前一个主讲人的ID
	TUP_ULONG m_Presentid = l;   ////当前主讲人的ID




	IM_S_USERINFO m_PresentInfo;

	if (m_Presentid == g_UserID)
	{
		////当前的主持人是自己
		///从自己的登录账号查找g_BindNO
		if (!getAccountINfoByBingNum(g_BindNO,m_PresentInfo))
			return  -1L;
		m_PresentBindNUm = g_BindNO;
		m_bisPresent = true;

		/////将获取主讲权限的对话框不可用
		m_btnGetPresenterRole.EnableWindow(FALSE);

		/////主持人或主讲人不静音/////
		(void)tup_call_media_mute_mic(ulCallID, TUP_FALSE);
	} 
	else
	{
		////当前主持人不是自己////
		std::string m_PresentBindNum;
		if (!GetUserBindNumByid(m_Presentid,m_PresentBindNum))
		{
			return  -1L;
		}

		if(!getAccountINfoByBingNum(m_PresentBindNum,m_PresentInfo))  
		{
			return  -1L;
		}

		if (m_PresentBindNum != g_BindNO)
		{
			m_bisPresent = false;
		}

		/////将获取主讲权限的对话框可用
		m_btnGetPresenterRole.EnableWindow(TRUE);

		if(m_bisMute)
		{
			if(!m_bisChairMan)
			{
				/////非主持人或者主讲人静音/////
				(void)tup_call_media_mute_mic(ulCallID, TUP_TRUE);
			}
		}
	}
	m_PresentAccount = m_PresentInfo.account;
	m_PresentBindNUm = m_PresentInfo.bindNO;
	std::string m_PresentName = m_PresentInfo.name;
	CString m_str;
	CTools::string2CString(m_PresentName,m_str);
	m_edtPresenter.SetWindowText(m_str);

	//主讲人变更后刷新一下列表
	UpdateMuteInfo();
	return 0L;
}



bool CDataConfDlg::getAccountINfoByBingNum( std::string _phoneID, IM_S_USERINFO& _userInfo)
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
		return false;
	}

	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memset(&curUserInfo,0,sizeof(IM_S_USERINFO));
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (strcmp(curUserInfo.bindNO, _phoneID.c_str()) == 0)
		{
			_userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}
	////释放IM_S_QUERY_USERINFO_ACK结构体中的TUPLIST内存/////
	tup_im_release_tup_list(ack.userList);

	if(!bRet)
	{
		return false;
	}

	return true;
}

bool CDataConfDlg::getAccountINfoByAccount(std::string _account, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	memset(&arg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
	memset(&ack,0,sizeof(IM_S_QUERY_USERINFO_ACK));
	ack.userList = NULL;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _account.c_str());
	arg.type = IM_E_IMUSERQUERYTYPE_BY_ACCOUNT;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		return false;
	}

	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memset(&curUserInfo,0,sizeof(IM_S_USERINFO));
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (strcmp(curUserInfo.account, _account.c_str()) == 0)
		{
			memcpy(&_userInfo,&curUserInfo,sizeof(IM_S_USERINFO));
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}
	////释放IM_S_QUERY_USERINFO_ACK结构体中的TUPLIST内存/////
	tup_im_release_tup_list(ack.userList);

	if(!bRet)
	{
		return false;
	}

	return true;
}

bool CDataConfDlg::IsInconf(std::string BindNum)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			return true ;
		}
	}
	return false;
}

bool CDataConfDlg::GetUserBindNumByid(TUP_ULONG id ,std::string& BindNum)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (id == iter->second)
		{
			BindNum = iter->first; 
			return true ;
		}
	}
	return false;
}
TUP_UINT64 CDataConfDlg::GetUserIDByBindNum(std::string BindNum)
{
	TUP_UINT64 m_tempid = 0;
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			m_tempid = iter->second;
		}
	}
	return m_tempid;
}

void CDataConfDlg::OnBnClickedBtAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelectDlg dlg;
	if(IDOK != dlg.DoModal())
	{
		return;
	}

	MAP_SELECT_USER selUser;
	dlg.GetSelectUser(selUser);	
	int iSize = selUser.size();
	if(iSize == 0)
	{
		return;		
	}
	MAP_SELECT_USER::iterator it = selUser.begin();
	MAP_SELECT_USER::iterator itEnd = selUser.end();
	for(;it!=itEnd;it++)
	{	
		std::string strCallno = it->second.CallNo;
	    tup_call_serverconf_add_attendee(ulConfID,1,strCallno.c_str(),strCallno.size()+1);
	   /////需要检查下所邀请人员是否在会议中，在会议中的不要更新//////
	   if (IsInconf(strCallno))
	   {
		   continue;
	   }
		m_LocalMenber[strCallno] = 0;
		int iSize = m_DataConfMem.GetItemCount();
		m_DataConfMem.InsertItem(iSize,L"");
		m_DataConfMem.SetItemData(iSize,CTools::str2num(strCallno));
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_ID,0);
		std::string content = it->second.name;
		content += "("+ strCallno + ")";
		CString cstrContent;
		CTools::string2CString(content,cstrContent);
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_NAME,cstrContent);
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_STATUS,L"邀请中");
		if (m_bisMute)
		{
			m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"静音");
		}
		else
		{
			m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"未静音");
		}
		
	}
}

void CDataConfDlg::InitSharePlatForm(int ShareID)
{
	switch (ShareID)
	{
	case NOTHING:
    case DESKTOP:
	case PROGRAME:
	case MEDIA:
		{
			SendMessage(WM_DATACONF_DOCUMENT_WND,0,NULL);
			m_stcShareState.SetWindowText(L"桌面共享");
		}break;
	case DOCUMENT:
		{
			SendMessage(WM_DATACONF_DOCUMENT_WND,1,NULL);
			GetDlgItem(IDC_ST_DOC)->SetWindowText(_T("文档列表"));
			GetDlgItem(IDC_BT_OPEN_NEW)->SetWindowText(_T("打开"));
		}break;
	case WHITEBOARD:
		{
			SendMessage(WM_DATACONF_DOCUMENT_WND,1,NULL);
			GetDlgItem(IDC_ST_DOC)->SetWindowText(_T("白板列表"));
			GetDlgItem(IDC_BT_OPEN_NEW)->SetWindowText(_T("新建"));
			//////将正在共享的白板查询并填充进文档列表中//////
			TUP_UINT32 docCount = 0;
			tup_conf_ds_get_doc_count(m_handle, IID_COMPONENT_WB, &docCount);
			for(int i = 0; i < docCount; i++)
			{
				TUP_UINT32 docId = 0;
				tup_conf_ds_get_docid_byindex(m_handle, IID_COMPONENT_WB, i, &docId);
				if(docId == 0)
				{
					continue;
				}

				TUP_UINT32 pageCount = 0;
				tup_conf_ds_get_page_count(m_handle, IID_COMPONENT_WB, docId, &pageCount);
				CString m_str;
				m_str.Format(_T("%d-%dP"), docId, pageCount);
				m_DocOrBoardList.InsertItem(i,L"");
				m_DocOrBoardList.SetItemText(i,COL_DOCUMENT_NAME,m_str);
				m_DocOrBoardList.SetItemData(i,(DWORD)docId);
			}
			//////检查是不是自己的共享/////
			if (g_BindNO == m_OwnerBindNum)
			{
				/////共享者是自己//////
				m_stcShareState.SetWindowText(L"您正在共享白板");
			}
			else
			{
				/////查询共享者姓名/////
				if (m_OwnerBindNum.size() == 0)
				{
					return;
				}
				IM_S_USERINFO m_OwnerInfo;
				getAccountINfoByBingNum(m_OwnerBindNum,m_OwnerInfo);
				CString m_strname;
				CTools::string2CString(m_OwnerInfo.name,m_strname);
				m_strname += L"正在共享白板";
				m_stcShareState.SetWindowText(m_strname);
			}
			OnBnClickedBtUpdate();
		}break;
	default:
		break;
	}

}

void CDataConfDlg::InitWhiteBackElement()
{
	/////设置白板的属性/////
	//不设置的话默认背景为白色，即0xFFFFFFFF
	tup_conf_ds_set_bgcolor(m_handle, IID_COMPONENT_WB, 0xFFFFFFFF);
	//不设置的话默认模式为DS_DISP_MODE_FREE
	tup_conf_ds_set_dispmode(m_handle, IID_COMPONENT_WB,  DS_DISP_MODE_FREE);
	//不设置的话默认输出格式为SUR_OUTPUT_HDC
	tup_conf_ds_set_surface_outputformat(m_handle, IID_COMPONENT_WB, SUR_OUTPUT_HDC);
	CRect m_rct;
	m_stcDeskTop.GetClientRect(m_rct);
	CDC *pDC = m_stcDeskTop.GetDC();
	int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
	int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);

	TC_SIZE disp = {m_rct.Width()*ppiX,m_rct.Height()*ppiY};
	//最后一个参数为1表示设置后立即重绘界面，为0不重绘
	TUP_RESULT tRet = tup_conf_ds_set_canvas_size(m_handle, IID_COMPONENT_WB, disp, TUP_TRUE);
	if (TC_OK == tRet)
	{
		////设置成功/////
		SendMessage(WM_DATACONF_WB_DRAW,NULL,NULL);
	}

	//////初始化自定义标注/////
	DsDefineAnnot types[] = {{ANNOTCUSTOMER_PICTURE, DS_ANNOT_FLAG_CANBESELECTED | DS_ANNOT_FLAG_CANBEMOVED},
	{ANNOTCUSTOMER_MARK, DS_ANNOT_FLAG_CANBESELECTED | DS_ANNOT_FLAG_CANBEMOVED | DS_ANNOT_FLAG_FIXEDSIZE},
	{ANNOTCUSTOMER_POINTER, DS_ANNOT_FLAG_EXCLUSIVEPERUSER | DS_ANNOT_FLAG_FIXEDSIZE}};
	tup_conf_annotation_reg_customer_type(m_handle,IID_COMPONENT_WB, types, CUSTOMER_ANNOT_COUNT);

	std::string m_AnnotPath;
	Anno_Resource_Item items[LOCALRES_COUNT];
	memset(items, 0, sizeof(items));
	FILE* fp = NULL;
	////1.check.png//////
	items[LOCALRES_CHECK].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_CHECK].picWidth = 28 * ppiX;
	items[LOCALRES_CHECK].picHeight = 28 * ppiY;
	items[LOCALRES_CHECK].ptOffset.x = 14 * ppiX;
	items[LOCALRES_CHECK].ptOffset.y = 14 * ppiY;
	items[LOCALRES_CHECK].resIndex = LOCALRES_CHECK;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\check.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_CHECK].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_CHECK].pData = new char[items[LOCALRES_CHECK].dataLen];
		fread(items[LOCALRES_CHECK].pData, 1, items[LOCALRES_CHECK].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
	///2.xcheck.png/////
	items[LOCALRES_XCHECK].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_XCHECK].picWidth = 28 * ppiX;
	items[LOCALRES_XCHECK].picHeight = 28 * ppiY;
	items[LOCALRES_XCHECK].ptOffset.x = 14 * ppiX;
	items[LOCALRES_XCHECK].ptOffset.y = 14 * ppiY;
	items[LOCALRES_XCHECK].resIndex = LOCALRES_XCHECK;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\xcheck.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_XCHECK].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_XCHECK].pData = new char[items[LOCALRES_XCHECK].dataLen];
		fread(items[LOCALRES_XCHECK].pData, 1, items[LOCALRES_XCHECK].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
	/////3.lpointer.png/////
	items[LOCALRES_LEFTPOINTER].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_LEFTPOINTER].picWidth = 28 * ppiX;
	items[LOCALRES_LEFTPOINTER].picHeight = 28 * ppiY;
	items[LOCALRES_LEFTPOINTER].ptOffset.x = 0;
	items[LOCALRES_LEFTPOINTER].ptOffset.y = 14 * ppiY;
	items[LOCALRES_LEFTPOINTER].resIndex = LOCALRES_LEFTPOINTER;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\lpointer.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_LEFTPOINTER].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_LEFTPOINTER].pData = new char[items[LOCALRES_LEFTPOINTER].dataLen];
		fread(items[LOCALRES_LEFTPOINTER].pData, 1, items[LOCALRES_LEFTPOINTER].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
	////4.rpointer.png////
	items[LOCALRES_RIGHTPOINTER].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_RIGHTPOINTER].picWidth = 28 * ppiX;
	items[LOCALRES_RIGHTPOINTER].picHeight = 28 * ppiY;
	items[LOCALRES_RIGHTPOINTER].ptOffset.x = 28 * ppiX;
	items[LOCALRES_RIGHTPOINTER].ptOffset.y = 14 * ppiY;
	items[LOCALRES_RIGHTPOINTER].resIndex = LOCALRES_RIGHTPOINTER;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\rpointer.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_RIGHTPOINTER].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_RIGHTPOINTER].pData = new char[items[LOCALRES_RIGHTPOINTER].dataLen];
		fread(items[LOCALRES_RIGHTPOINTER].pData, 1, items[LOCALRES_RIGHTPOINTER].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
	////5.upointer.png/////
	items[LOCALRES_UPPOINTER].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_UPPOINTER].picWidth = 28 * ppiX;
	items[LOCALRES_UPPOINTER].picHeight = 28 * ppiY;
	items[LOCALRES_UPPOINTER].ptOffset.x = 14 * ppiX;
	items[LOCALRES_UPPOINTER].ptOffset.y = 0;
	items[LOCALRES_UPPOINTER].resIndex = LOCALRES_UPPOINTER;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\upointer.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_UPPOINTER].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_UPPOINTER].pData = new char[items[LOCALRES_UPPOINTER].dataLen];
		fread(items[LOCALRES_UPPOINTER].pData, 1, items[LOCALRES_UPPOINTER].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
	////6.dpointer.png/////
	items[LOCALRES_DOWNPOINTER].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_DOWNPOINTER].picWidth = 28 * ppiX;
	items[LOCALRES_DOWNPOINTER].picHeight = 28 * ppiY;
	items[LOCALRES_DOWNPOINTER].ptOffset.x = 14 * ppiX;
	items[LOCALRES_DOWNPOINTER].ptOffset.y = 28 * ppiY;
	items[LOCALRES_DOWNPOINTER].resIndex = LOCALRES_DOWNPOINTER;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\dpointer.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_DOWNPOINTER].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_DOWNPOINTER].pData = new char[items[LOCALRES_DOWNPOINTER].dataLen];
		fread(items[LOCALRES_DOWNPOINTER].pData, 1, items[LOCALRES_DOWNPOINTER].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
	/////7.lp.png//////
	items[LOCALRES_LASERPOINTER].format = DS_PIC_FORMAT_PNG;
	items[LOCALRES_LASERPOINTER].picWidth = 28 * ppiX;
	items[LOCALRES_LASERPOINTER].picHeight = 28 * ppiY;
	items[LOCALRES_LASERPOINTER].ptOffset.x = 14 * ppiX;
	items[LOCALRES_LASERPOINTER].ptOffset.y = 14 * ppiY;
	items[LOCALRES_LASERPOINTER].resIndex = LOCALRES_LASERPOINTER;
	m_AnnotPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\lp.png";
	fp = fopen(m_AnnotPath.c_str(), "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		items[LOCALRES_LASERPOINTER].dataLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		items[LOCALRES_LASERPOINTER].pData = new char[items[LOCALRES_LASERPOINTER].dataLen];
		fread(items[LOCALRES_LASERPOINTER].pData, 1, items[LOCALRES_LASERPOINTER].dataLen, fp);

		fclose(fp);
		fp = NULL;
	}
    tRet = tup_conf_annotation_init_resource(m_handle,IID_COMPONENT_WB,items, LOCALRES_COUNT);
	//////析构数组/////
	for(int i = 0; i < LOCALRES_COUNT; i++)
	{
		char* pTmpData = (char*)items[i].pData;
		if(pTmpData)
		{
			delete[] pTmpData;
			pTmpData = NULL;
		}
	}

}

bool CDataConfDlg::CheckShareStatu(int m_choice)
{
	switch (m_choice)
	{
	     case NOTHING:
			 /////检查是否是已经被选中的按钮////
			 if (IDC_RAD_NULL == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))   return FALSE;
			 break;
		 case DESKTOP:
			 {
				 /////检查是否是已经被选中的按钮////
				 if (IDC_RAD_SCREEN == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;

				 ////检查是否处于桌面共享中/////
				 CString m_str ;
				 m_stcShareState.GetWindowText(m_str);
				 if (L"正在共享" == m_str )
				 {
					 //////桌面共享正在进行中/////
					 CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_SCREEN);
					 CTools::ShowMessageTimeout(_T("请停止共享后再进行操作"),2000);
					 return FALSE;
				 }
			 }
			 break;
		 case DOCUMENT:
			 {
				 /////检查是否是已经被选中的按钮////
				 if (IDC_RAD_DOC == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
				 
			 }
			 break;
		 case WHITEBOARD:
			 {
				 /////检查是否是已经被选中的按钮////
				 if (IDC_RAD_WHITEBOARD == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
				 //////检查是否有白板在共享/////
				 DsSyncInfo info;
				 if(TC_OK == tup_conf_ds_get_syncinfo(m_handle, IID_COMPONENT_WB, &info)  && info.docId !=0)
				 {
					 CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_WHITEBOARD);
					 CTools::ShowMessageTimeout(_T("请结束当前白板共享后操作"),2000);
					 return FALSE;
				 }
			 }
			 break;
		 case PROGRAME:
			 {
				 /////检查是否是已经被选中的按钮////
				 if (IDC_RAD_PROGRAM == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
			 }break;
		 case MEDIA:
			 {
				 /////检查是否是已经被选中的按钮////
				 if (IDC_RAD_MEDIA == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
			 }
			 break;
		 default:
			 break;
	}
	return TRUE;
}

void CDataConfDlg::OnBnClickRadio(UINT idCtl)
{
	// TODO: 在此添加控件通知处理程序代码
	//////检查当前状态//////
	if(!CheckShareStatu(m_RadButChoice))
	{
		return ;
	}
	/////
	switch(idCtl)
	{
	case IDC_RAD_NULL:
		{
			m_btnSharDesk.SetWindowText(L"请选择共享类型");
			m_btnSharDesk.EnableWindow(FALSE);
			m_RadButChoice = NOTHING;
		}
		break;
	case IDC_RAD_SCREEN:
		{
			m_btnSharDesk.SetWindowText(L"共享屏幕");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = DESKTOP;
		}
		break;
	case IDC_RAD_DOC:
		{
			m_btnSharDesk.SetWindowText(L"共享文档");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = DOCUMENT;
		}
		break;
	case IDC_RAD_WHITEBOARD:
		{
			m_btnSharDesk.SetWindowText(L"共享白板");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = WHITEBOARD;
		}
		break;
	case IDC_RAD_PROGRAM:
		{
			m_btnSharDesk.SetWindowText(L"共享程序");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = PROGRAME;
		}
		break;
	case IDC_RAD_MEDIA:
		{
			m_btnSharDesk.SetWindowText(L"共享媒体");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = MEDIA;
		}
		break;
	default:
		{
			m_btnSharDesk.EnableWindow(FALSE);
			m_btnSharDesk.SetWindowText(L"请选择共享类型");
			m_RadButChoice = NOTHING;
		}
		break;
	}
	InitSharePlatForm(m_RadButChoice); 
	if (m_OwnerBindNum == g_BindNO)
	{
		tup_conf_update_layout(m_handle,m_RadButChoice);
	}
}

void CDataConfDlg::InitiMenberlist(TUP_UINT32 m_ConfID,std::string strGroupID)
{
	m_DataConfMem.DeleteAllItems();
	CConfDlg* pConfDlg = CIMManage::GetIntance().GetConfDlgByConfID(m_ConfID);
	if (NULL != pConfDlg)
	{
		/////由语音会议转数据会议/////
		////获取初始成员/////
		int iSize =  pConfDlg->m_listMember.GetItemCount();
		for(int i=0;i<iSize;i++)
		{
			CString cstrCallNo = pConfDlg->m_listMember.GetItemText(i,COL_MEM_CALLNO);
			CString cstrName = pConfDlg->m_listMember.GetItemText(i,COL_MEM_Name);
			std::string strCallno = CTools::UNICODE2UTF(cstrCallNo);
			m_LocalMenber[strCallno] = 0;
			/////本地插入/////
			m_DataConfMem.InsertItem(i,L"");
			m_DataConfMem.SetItemData(i,CTools::str2num(strCallno));
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_ID,0);
			cstrName = cstrName +L"(" + cstrCallNo + L")";
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_NAME,cstrName);
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"未加入");
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
		}
		pConfDlg->CloseDlg();
	}
	else
	{

		///查询群组获取成员/////
		IM_S_REQUESTIMGROUPMEMBERS_ARG arg={0};
		IM_S_GROUPUSERLIST ack={0};
		arg.isSyncAll = TUP_TRUE;
		strcpy_s(arg.groupID, IM_D_GROUPID_LENGTH, strGroupID.c_str());
		//只能查询UC账户
		TUP_RESULT tRet = tup_im_getfixedgroupmembers(&arg,&ack);
		if(tRet != TUP_SUCCESS)
		{
			TRACE("tup_im_getfixedgroupmembers failed");
			return ;
		}
		/////新增入成员至列表/////
		TUP_S_LIST* list =  ack.memberInfo;
		while(list != NULL)
		{
			IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
			if(NULL != groupUser)
			{
				TUP_UINT32 stuffID = groupUser->staffID;
				std::string strBingNum = groupUser->bindNO;
				/////加入群组中的成员//////
				if (m_bisChairMan)
				{
					tup_call_serverconf_add_attendee(m_ConfID,1,strBingNum.c_str(),strBingNum.size()+1);
				}
				/////记录新加入成员
				m_LocalMenber[strBingNum] = stuffID;

				CString m_name,m_number,m_strID;
				CTools::string2CString(std::string(groupUser->name),m_name);
				CTools::string2CString(strBingNum,m_number);
				CTools::string2CString(CTools::num2str(stuffID),m_strID);

				//初始化界面信息/////
				m_name = m_name +L"(" +m_number +L")";
				int nSize = m_DataConfMem.GetItemCount();
				m_DataConfMem.InsertItem(nSize,L"");
				m_DataConfMem.SetItemData(nSize,CTools::str2num(strBingNum));
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_ID,m_strID);
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_NAME,m_name);
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_STATUS,L"未加入");
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_MUTE,L"未静音");


			}
			list = list->next;
		}
		//////释放IM_S_GROUPUSERLIST中的TUP_S_LIST指针/////
		tup_im_release_tup_list(ack.memberInfo);

	}
}

bool CDataConfDlg::SetUseridByBindNum(std::string BindNum,TUP_ULONG id)
{
	LocalMember::iterator iter = m_LocalMenber.begin();
	LocalMember::iterator itEnd = m_LocalMenber.end();
	for (;iter!=itEnd;iter++)
	{
		if (BindNum == iter->first)
		{
			iter->second = id; 
			return true ;
		}

	}

	return false;
}


void CDataConfDlg::OnNMRClickListDataconfMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (!m_bisChairMan)
	{
		return ;
	}

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_DataConfMem.ScreenToClient(&pt);

	UINT uFlag = 0;
	int hSelectedItem = m_DataConfMem.HitTest(pt,&uFlag);
	if (0 <= hSelectedItem)
	{
		CMenu menu;
		menu.CreatePopupMenu();

		int m_BindNum = m_DataConfMem.GetItemData(hSelectedItem);

		if (m_BindNum != CTools::str2num(m_PresentBindNUm))
		{
			menu.AppendMenu(MF_STRING, ID_DATACONF_SETPRESENT_MEM_MENU, _T("设为主讲人"));
		}

		    menu.AppendMenu(MF_STRING, ID_DATACONF_DEL_MEM_MENU, _T("移除与会者"));
		if (m_BindNum == CTools::str2num(m_ChairMainBindNum))
		{
			menu.EnableMenuItem(ID_DATACONF_DEL_MEM_MENU, MF_DISABLED|MF_GRAYED);
		}

		if ((m_BindNum == CTools::str2num(m_PresentBindNUm))||(m_BindNum == CTools::str2num(m_ChairMainBindNum)))
		{
			menu.AppendMenu(MF_STRING, ID_DATACONF_INVITEDTOSHARE_MEM_MENU, _T("邀请共享"));
		}

		CString cstrCallState = m_DataConfMem.GetItemText(hSelectedItem,COL_DATACONFMEM_STATUS);
		if(cstrCallState != L"会议中")
		{

			menu.AppendMenu(MF_STRING, ID_DATACONF_RECALL_MEM_MENU, _T("重新发起呼叫"));
/*			m_DataConfMem.SetItemText(hSelectedItem,COL_DATACONFMEM_STATUS,L"邀请中");*/
		}
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);		                 
	}
}


void CDataConfDlg::OnClickListMemMenu(UINT nID)
{
	int nItem = -1;
	POSITION pos = m_DataConfMem.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	else
	{
		while (pos)
		{
			nItem = m_DataConfMem.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			break;
		}
	}

	TUP_UINT32 m_BindNum = m_DataConfMem.GetItemData(nItem);
	std::string m_strCallNum = CTools::num2str(m_BindNum);
	IM_S_USERINFO m_userInfo;
     getAccountINfoByBingNum(m_strCallNum,m_userInfo);
	if(nID == ID_DATACONF_DEL_MEM_MENU)
	{
		if (m_strCallNum == m_PresentBindNUm)
		{
			////被移除的是主讲人，收回主讲权限及共享权限
			tup_conf_user_set_role(m_handle,g_UserID,CONF_ROLE_PRESENTER);
			tup_conf_as_set_owner(m_handle,g_UserID,AS_ACTION_ADD);
		}
		tup_conf_user_kickout(m_handle,m_userInfo.staffID);
		tup_call_serverconf_kick_attendee(ulConfID,m_strCallNum.c_str());
	}
	else if(nID == ID_DATACONF_RECALL_MEM_MENU)
	{
		 tup_call_serverconf_add_attendee(ulConfID,1,m_strCallNum.c_str(),m_strCallNum.size()+1);
		 m_DataConfMem.SetItemText(nItem,COL_DATACONFMEM_STATUS,L"邀请中");
	}
	else if(nID == ID_DATACONF_SETPRESENT_MEM_MENU)
	{
		////设置为主讲人/////
	    tup_conf_user_set_role(m_handle,m_userInfo.staffID,CONF_ROLE_PRESENTER);
		////设置共享权限/////
		tup_conf_as_set_owner(m_handle,m_userInfo.staffID,AS_ACTION_ADD);
	}
	else if(nID == ID_DATACONF_INVITEDTOSHARE_MEM_MENU)
	{
		///////邀请共享//////
		// to do////tup_conf_send_data
		TUP_RESULT tRet = tup_conf_send_data(m_handle,m_userInfo.staffID,(TUP_UINT8)(REMOTESHARE_ACTION_SHARE+ '\0'),'\0',0);
		if (tRet !=TC_OK)
		{
			TRACE("tup_conf_send_data failed!");
		}
	}
}

void CDataConfDlg::OnBnClickedBtConfmute()
{
	// TODO: 在此添加控件通知处理程序代码

	TUP_RESULT tRet = tup_conf_mute(m_handle,!m_bisMute);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_conf_mute Failed！");
		return ;
	}

}

//更新列表中静音列的状态
//m_bisMute指是不是处于全体静音的状态
void  CDataConfDlg::UpdateMuteInfo()
{
	int iSize = m_DataConfMem.GetItemCount();

	if (m_bisMute)
	{
		for (int i = 0;i<iSize;i++)
		{
			CString cstrName = m_DataConfMem.GetItemText(i, COL_DATACONFMEM_NAME);
			if(!isChairManOrPresent(cstrName))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"静音");
			}
			else
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
			}
		}
	}
	else
	{
		for (int i = 0;i<iSize;i++)
		{
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
		}
	}
}

bool CDataConfDlg::isChairManOrPresent(const CString& cstrName)
{
	std::string strName = CTools::UNICODE2UTF(cstrName);
	if(m_ChairMainBindNum.size() > 0)
	{
		std::size_t ChairManfound = strName.find(m_ChairMainBindNum);
		if (ChairManfound != std::string::npos)
		{
			return true;
		}
	}

	if(m_PresentBindNUm.size() > 0)
	{
		std::size_t Presentfound = strName.find(m_PresentBindNUm);
		if(Presentfound != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

LRESULT CDataConfDlg::UpdateMuteInfo(WPARAM w,LPARAM l)
{
	//////静音结果通知处理/////
	m_bisMute = bool(w);
	if (m_bisMute)
	{
		if((!m_bisPresent)&&(!m_bisChairMan))
		{
			/////主席与主持人不静音/////
			(void)tup_call_media_mute_mic(ulCallID,TUP_TRUE);
		}
		GetDlgItem(IDC_BT_ConfMute)->SetWindowText(L"取消静音");
		///修改状态////
		int iSize = m_DataConfMem.GetItemCount();
		
		for (int i = 0;i<iSize;i++)
		{
			CString cstrName = m_DataConfMem.GetItemText(i, COL_DATACONFMEM_NAME);
			if(!isChairManOrPresent(cstrName))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"静音");
			}
			else
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
			}
		}
		
	}
	else
	{
		GetDlgItem(IDC_BT_ConfMute)->SetWindowText(L"全体静音");
	
		///修改状态////
		int iSize = m_DataConfMem.GetItemCount();
		for (int i = 0;i<iSize;i++)
		{
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"未静音");
			(void)tup_call_media_mute_mic(ulCallID,TUP_FALSE);

		}
		
	}
	

	return 0L;
}

inline void CDataConfDlg::InitShareButton()
{
//	SendMessage(WM_DATACONF_DOCUMENT_WND,0,NULL);
	CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_NULL);
	m_btnSharDesk.SetWindowText(L"请选择共享类型");
	m_btnSharDesk.EnableWindow(FALSE);
	m_RadButChoice = NOTHING;
	m_stcDeskTop.SetBitmap2(NULL);
	
}

inline void CDataConfDlg::InitVideoINfo()
{

	//////初始化参数/////
	m_LocalVideoINfo[0].m_VideoDisp = GetDlgItem(IDC_STATIC_V2);
	m_LocalVideoINfo[0].m_NameDisp = GetDlgItem(IDC_S_V2);
	m_LocalVideoINfo[0].isValuable = true;
	m_LocalVideoINfo[1].m_VideoDisp = GetDlgItem(IDC_STATIC_V3);
	m_LocalVideoINfo[1].m_NameDisp = GetDlgItem(IDC_S_V3);
	m_LocalVideoINfo[1].isValuable = true;
	m_LocalVideoINfo[2].m_VideoDisp = GetDlgItem(IDC_STATIC_V4);
	m_LocalVideoINfo[2].m_NameDisp = GetDlgItem(IDC_S_V4);
	m_LocalVideoINfo[2].isValuable = true;
	m_LocalVideoINfo[3].m_VideoDisp = GetDlgItem(IDC_STATIC_V5);
	m_LocalVideoINfo[3].m_NameDisp = GetDlgItem(IDC_S_V5);
	m_LocalVideoINfo[3].isValuable = true;
	m_LocalVideoINfo[4].m_VideoDisp = GetDlgItem(IDC_STATIC_V6);
	m_LocalVideoINfo[4].m_NameDisp = GetDlgItem(IDC_S_V6);
	m_LocalVideoINfo[4].isValuable = true;
	m_LocalVideoINfo[5].m_VideoDisp = GetDlgItem(IDC_STATIC_V7);
	m_LocalVideoINfo[5].m_NameDisp = GetDlgItem(IDC_S_V7);
	m_LocalVideoINfo[5].isValuable = true;
	///////初始化界面信息////////
	GetDlgItem(IDC_BUTTON_OPENVIDEO)->SetWindowText(L"开启摄像头");
	//////设置本地视频框为不可见///////
	GetDlgItem(IDC_STATIC_V1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V8)->ShowWindow(SW_HIDE);
    /////界面上的视频窗口及姓名显示部分不可见//////
	GetDlgItem(IDC_STATIC_V2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_V3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_V4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_V5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_V6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_V7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V7)->ShowWindow(SW_HIDE);
	if (m_bisChairMan)
	{
		GetDlgItem(IDC_BT_ConfMute)->EnableWindow(TRUE);
		GetDlgItem(IDC_BT_ADD)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BT_ConfMute)->EnableWindow(FALSE);
		GetDlgItem(IDC_BT_ADD)->EnableWindow(FALSE);
	}
	//////初始化画笔信息/////
	m_penInfo.m_clr = 0;
	m_penInfo.m_linewidth = 1;
	m_penInfo.m_penstyle = DS_PEN_TYPE_NORMAL;
}

bool CDataConfDlg::AvaluableVudeo(int &Index)
{
	///////查询目前是否还存在可用的视频窗口///////
	for (int i = 0;i<6;i++)
	{
		if (m_LocalVideoINfo[i].isValuable)
		{
			Index = i;
			return true;
		}
	}

	return false;
}

bool CDataConfDlg::GetVideoINdexByid(int& Index,TUP_ULONG m_Userid)
{
	for (int i = 0;i<6;i++)
	{
		if (m_Userid == m_LocalVideoINfo[i].Userid)
		{
			Index = i;
			return true;
		}
	}

	return false;
}

bool CDataConfDlg::PubSelfStatus(IM_E_USER_ONLINESTATUS _status)
{
	IM_S_STATUSARG arg;
	CTools::CString2Char(L"desc",arg.desc,IM_D_MAX_STATUS_DESCLEN);
	arg.status = _status;

	TUP_RESULT tRet = tup_im_publishstatus(&arg);
	if (TUP_SUCCESS == tRet)
	{
		///////
		CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if (NULL != pMainDlg)
		{
			pMainDlg->SetCurStatus(_status);
		}
		return true ;
	} 
	else
	{
		return false;
	}

}
/*
   函数名：OnDocumentWnd;
   函数功能：修改窗体显示
   参数：wParam   入参，表示显示模式////1，正常模式 2，文档、白板模式
   参数：lPara    无意义，暂时保留
*/

LRESULT CDataConfDlg::OnDocumentWnd(WPARAM wParam,LPARAM lPara)
{
	CRect rcSize;
	GetWindowRect(&rcSize);

	CRect rc;
	int iShow = (int)wParam;
	switch (iShow)
	{
	case  0:
		{
			//////正常模式
	 		rc.left = rcSize.left;
			rc.top = rcSize.top;
			rc.right = rc.left+ NORM_WIDTH;
	 		rc.bottom = rcSize.bottom ;
			GetDlgItem(IDC_BUTTON_SHAREDESK)->EnableWindow(TRUE);
		}break;
	case 1:
		{
			/////文档共享模式
			rc.left = rcSize.left;
			rc.top = rcSize.top;
			rc.right = rc.left+ DOC_WIDTH;
			rc.bottom = rcSize.bottom ;
			GetDlgItem(IDC_BUTTON_SHAREDESK)->EnableWindow(FALSE);
			///////初始化文档列表
			m_DocOrBoardList.DeleteAllItems();
			while ( m_DocOrBoardList.DeleteColumn (0));
			m_DocOrBoardList.ModifyStyle(0,LVS_SINGLESEL);
			m_DocOrBoardList.InsertColumn(COL_DOCUMENT_STATE, _T("状态"), LVCFMT_LEFT, 70);
			m_DocOrBoardList.InsertColumn(COL_DOCUMENT_NAME, _T("名称"), LVCFMT_LEFT, 90);
			DWORD dwStyle = m_DocOrBoardList.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
			dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
			m_DocOrBoardList.SetExtendedStyle(dwStyle); //设置扩展风格
			/////设置画笔属性//////
			m_PenType.ResetContent();
			m_PenType.AddString(_T("无标注"));
			m_PenType.AddString(_T("普通画笔"));
			m_PenType.AddString(_T("高亮画笔"));
			m_PenType.AddString(_T("激光笔"));
			m_PenType.SetCurSel(0);
			/////设置画笔颜色//////
			m_LineWidth.ResetContent();
			m_LineWidth.AddString(_T("1 px"));
			m_LineWidth.AddString(_T("2 px"));
			m_LineWidth.AddString(_T("3 px"));
			m_LineWidth.AddString(_T("4 px"));
			m_LineWidth.AddString(_T("5 px"));
			m_LineWidth.AddString(_T("6 px"));
			m_LineWidth.SetCurSel(0);
			/////将颜色绘制在控件上////////
			CDC *pDC = GetDlgItem(IDC_STATIC_COLOR)->GetDC();
			CRect m_rct;
			GetDlgItem(IDC_STATIC_COLOR)->GetClientRect(m_rct);
			CBrush m_brs;
			m_brs.CreateSolidBrush(m_penInfo.m_clr);
			pDC->FillRect(&m_rct,&m_brs);

		}break;
	default:
		break;
	}
	MoveWindow(&rc,TRUE);
	ShowWindow(SW_SHOW);
	return 0L;
}
/*
   函数名：OnBnClickedBtOpenNew;
   函数功能：打开文档或者创建白板
   参数： 无
*/
void CDataConfDlg::OnBnClickedBtOpenNew()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("没有共享权限，创建文档失败"),3000);
		return ;
	}
	CString m_str;
	GetDlgItem(IDC_BT_OPEN_NEW)->GetWindowText(m_str);
	if (_T("打开") == m_str)
	{
		///////文档共享//////
		///1.打开文档////
		CString  m_DocumentPath;
		CFileDialog Filedlg(true);
		if (Filedlg.DoModal())
		{
			m_DocumentPath = Filedlg.GetPathName();
		}
		std::string m_filepath;

		//TUP_RESULT tRet = tup_conf_ds_open(m_handle,IID_COMPONENT_DS,m_DocumentPath.GetBuffer(0),DS_OPTION_SIZE,);
	} 
	else if(_T("新建") == m_str)
	{
		//////创建空文档//////
		TUP_UINT32 nDocID = 0;
		if(TC_OK == tup_conf_ds_new_doc(m_handle,IID_COMPONENT_WB,&nDocID) && nDocID != 0)
		{
			m_curDoc = nDocID;
			m_curPage = 0;
			tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,0,TUP_TRUE);

		}
		else
		{
			CTools::ShowMessageTimeout(_T("创建文档失败"),3000);
			return ;
		}
	}
	else
	{
		/////to do  nothing
	}
}

/*
   函数名：OnNewDocSuc;
   函数功能：新建文档成功
   参数： nValue1  文档ID
   参数： nValue2  文档新建者ID
*/
LRESULT CDataConfDlg::OnNewDocSuc(WPARAM nValue1,LPARAM nValue2)
{
	TUP_ULONG m_DocShareID = TUP_ULONG(nValue2);
	m_curDoc = TUP_UINT32(nValue1);
	std::string m_BindNum = "";
	GetUserBindNumByid(m_DocShareID,m_BindNum);
	//////检查是不是自己的共享/////
	if (g_BindNO == m_BindNum)
	{
		/////共享者是自己//////
		m_stcShareState.SetWindowText(L"您正在共享白板");
	}
	else
	{
		/////共享者不是自己///
		/////查询共享者姓名/////
		IM_S_USERINFO m_OwnerInfo;
		getAccountINfoByBingNum(m_BindNum,m_OwnerInfo);
		CString m_strname;
		CTools::string2CString(m_OwnerInfo.name,m_strname);
		m_strname += L"正在共享白板";
		m_stcShareState.SetWindowText(m_strname);
	}
	UpdateDocInfo(m_curDoc);
	return 0L;
}

/*
   函数名：OnDelDocSuc;
   函数功能：新建文档成功
   参数： nValue1  文档ID
*/

LRESULT CDataConfDlg::OnDelDocSuc(WPARAM nValue1,LPARAM nValue2)
{
	TUP_UINT32 m_DocID = (TUP_UINT32)nValue1;
	int Index = GetDocumentIndex(m_DocID);
	if (-1 == Index)
	{
		return -1L;
	}

	/////删除文档////
	m_DocOrBoardList.DeleteItem(Index);
	return 0L;
}
/*
   函数名：DocumentIndex;
   函数功能：查询
   入参数：  m_DocID
   返回值：列表中的ID数值，如果不存在，返回-1

*/

int CDataConfDlg::GetDocumentIndex(TUP_UINT32 m_DocID)
{
	int m_Index = -1;
	for(int i = 0; i < m_DocOrBoardList.GetItemCount(); i++)
	{
		TUP_UINT32 ID = (TUP_UINT32)m_DocOrBoardList.GetItemData(i);
		if(ID == m_DocID) 
		{
			m_Index = i;
			break;
		}
	}
	return m_Index;
}

/*
   函数名：OnBnClickedBtSelectcolor;
   函数功能：选择画笔的颜色
   参数： 无
*/

void CDataConfDlg::OnBnClickedBtSelectcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	//////选择颜色///////
	CColorDialog m_setColDlg;
	m_setColDlg.m_cc.Flags |= CC_FULLOPEN|CC_RGBINIT;  /////CC_RGBINIT可以显示上次选择的颜色
	m_setColDlg.m_cc.rgbResult = m_penInfo.m_clr;                /////记录上次选择的颜色/////
	if (IDOK == m_setColDlg.DoModal())
	{
		m_penInfo.m_clr = m_setColDlg.m_cc.rgbResult; 
	}
	/////将颜色绘制在控件上////////
	CDC *pDC = GetDlgItem(IDC_STATIC_COLOR)->GetDC();
	CRect m_rct;
	GetDlgItem(IDC_STATIC_COLOR)->GetClientRect(m_rct);
	CBrush m_brs;
	m_brs.CreateSolidBrush(m_penInfo.m_clr);
	pDC->FillRect(&m_rct,&m_brs);
	/////更新画笔信息//////
	UpdatePenInfo(m_penInfo);
}
/*
   函数名：OnCbnSelchangeCombActiontype;
   函数功能：选择画笔的类型(普通，高亮)
   参数： 无
*/
void CDataConfDlg::OnCbnSelchangeCombActiontype()
{
	// TODO: 在此添加控件通知处理程序代码
	int m_penstyleIndex = m_PenType.GetCurSel();
	switch (m_penstyleIndex)
	{
	case 0:
		if (m_laserBegin)
		{
			tup_conf_annotation_laserpointer_stop(m_handle,IID_COMPONENT_WB);
			m_laserBegin = false;
		}
		return ;
		break;
	case 1:
		{
			if (m_laserBegin)
			{
				tup_conf_annotation_laserpointer_stop(m_handle,IID_COMPONENT_WB);
				m_laserBegin = false;
			}
			m_penInfo.m_penstyle = DS_PEN_TYPE_NORMAL;

		}
		break;
	case 2:
		{
			if (m_laserBegin)
			{
				tup_conf_annotation_laserpointer_stop(m_handle,IID_COMPONENT_WB);
				m_laserBegin = false;
			}
			m_penInfo.m_penstyle = DS_PEN_TYPE_HILIGHT;
		}break;
	case 3:
		{
			//////激光笔/////
			if (m_laserBegin) return;
			m_laserBegin = true;
			TC_POINT pt = {14 * 15, 14 * 15};
			TC_SIZE size = {28 * 15, 28 * 15};
			tup_conf_annotation_laserpointer_start(m_handle,IID_COMPONENT_WB, size, true, LOCALRES_LASERPOINTER, 0, NULL, 0, 0, 0, pt);
		}
	default:
		break;
	}
	UpdatePenInfo(m_penInfo);
}
/*
   函数名：OnCbnSelchangeCombo1;
   函数功能：选择画笔的线宽(1~6px)
   参数： 无
*/
void CDataConfDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_penInfo.m_linewidth = m_LineWidth.GetCurSel() + 1;
	UpdatePenInfo(m_penInfo);
}
/*
   函数名：UpdatePenInfo;
   函数功能：更新画笔颜色、线宽、信息
   参数： 无
*/
void CDataConfDlg::UpdatePenInfo(PenInfo m_penInfo)
{
	DsPenInfo newPen;
	///////传进来的颜色是COLORREF格式的，需要转换成COLORRGBA格式的///////
	newPen.color = GetRValue(m_penInfo.m_clr) *256*256*256 + GetGValue(m_penInfo.m_clr) *256*256 +GetBValue(m_penInfo.m_clr)*256;
	if (DS_PEN_TYPE_NORMAL == m_penInfo.m_penstyle)
	{
		newPen.width = m_penInfo.m_linewidth * 15;
	}
	else
	{
		newPen.width = m_penInfo.m_linewidth * 15 * 6;
	}
	
	newPen.style = DS_PEN_STYLE_SOLID;
	DsPenInfo oldPen;
	TUP_RESULT tRet = tup_conf_annotation_set_pen(m_handle,IID_COMPONENT_WB,m_penInfo.m_penstyle,newPen,&oldPen);
	if (TC_OK != tRet)
	{
		CTools::ShowMessageTimeout(_T("更新画笔信息失败！"),3000);
	}
}

/*
   函数名：OnBnClickedBtNewpage;
   函数功能：当前白板中新建页面
   参数： 无
*/

void CDataConfDlg::OnBnClickedBtNewpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("没有共享权限，新建页面失败"),3000);
		return ;
	}
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("当前共享文档不存在"),2000);
		return ;
	}
	CRect m_Rect;
	m_stcDeskTop.GetClientRect(m_Rect);
	TUP_UINT32 nPageID;
	TUP_RESULT tRet = tup_conf_ds_new_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_Rect.Width(),m_Rect.Height(),&nPageID);
	UpdatePenInfo(m_penInfo);
	if (TC_OK != tRet)
	{
		CTools::ShowMessageTimeout(_T("新建页面失败！"),3000);
		return ;
	}
	m_curPage = nPageID;
	tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,TUP_TRUE);
}
/*
   函数名：UpdateDocInfo;
   函数功能：更新文档信息
   参数： m_DocID 文档ID
*/
void CDataConfDlg::UpdateDocInfo(TUP_UINT32 m_DocID)
{
	///////更新下Doc信息/////
	if(!m_DocID)
	{
		return ;
	}
	/////查找文档页数/////////
	TUP_UINT32 m_count = 0;
	TUP_RESULT tRet = tup_conf_ds_get_page_count(m_handle,IID_COMPONENT_WB,m_DocID,&m_count);
	if (TC_OK != tRet)
	{
		CTools::ShowMessageTimeout(_T("查询文档失败!"),3000);
		return ;
	}
	////删除所有文档的状态////
	for (int i = 0;i < m_DocOrBoardList.GetItemCount();i++)
	{
		m_DocOrBoardList.SetItemText(i,COL_DOCUMENT_STATE,L"");
	}

	int m_DocIndex = GetDocumentIndex(m_DocID);
	if (-1 != m_DocIndex)
	{
		//////文档存在/////
		/////修改当前文档信息////
		CString str;
		str.Format(_T("%d-%dP"), m_DocID, m_count);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_NAME,str);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_STATE,L"正在共享");
		
	}
	else
	{
		/////文档不存在////
		//////文档不存在此时需要重新在文档中新建改文档/////
		m_DocIndex = m_DocOrBoardList.GetItemCount();
		m_DocOrBoardList.InsertItem(m_DocIndex,L"");
		m_DocOrBoardList.SetItemData(m_DocIndex,(DWORD_PTR)m_DocID);
		CString m_str;
		m_str.Format(_T("%d-%dP"), m_DocID, m_count);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_NAME,m_str);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_STATE,L"正在共享");
	}

	//////设置选择页面控件//////
	m_comSelectPage.ResetContent();
	if (!m_count)
	{
		/////页面数为0///////
		m_comSelectPage.AddString(_T("0P"));
		m_comSelectPage.SetCurSel(0);
	}
	else
	{
		//////页面数字>=1/////
		for (int i = 1;i <= (int)m_count;i++)
		{
			CString str;
			str.Format(_T("%dP"),i);
			m_comSelectPage.AddString(str);
		}

		/////通过m_curPage转换成当前的页码/////
		int PageNUm = 0;
		tup_conf_ds_get_pageno_byid(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,&PageNUm);
		m_comSelectPage.SetCurSel(PageNUm);

	}
	
}
/*
   函数名：OnNewPageSuc;
   函数功能：新建文档页面成功
   参数： nValue1 文档ID
   参数： nValue2 页面ID
*/

LRESULT CDataConfDlg::OnNewPageSuc(WPARAM nValue1,LPARAM nValue2)
{
	TUP_UINT32 m_DocID = nValue1;
	UpdateDocInfo(m_DocID);
	return 0L;
}
/*
   函数名：OnDrawWhileBackData;
   函数功能：绘制白板数据
   参数： 暂时不用
*/
LRESULT CDataConfDlg::OnDrawWhileBackData(WPARAM nValue1,LPARAM nValue2)
{
	//////更新白板数据//////
	//如果已知画布宽高，第二和第三个参数可以传NULL
	TUP_UINT32 m_hei;
	TUP_UINT32 m_wid;
	CRect m_rct;
	m_stcDeskTop.GetClientRect(m_rct);
	CDC *pDC = m_stcDeskTop.GetDC();
 	HDC *data = (HDC*)tup_conf_ds_get_surfacebmp(m_handle, IID_COMPONENT_WB,&m_wid,&m_hei);
	if(data)
	{
		::BitBlt(pDC->m_hDC, 0, 0, m_rct.Width(), m_rct.Height(), (HDC)data, 0, 0, SRCCOPY);
	}
	else
	{
		//失败，一般是画布未创建或会议未创建
	}
	::ReleaseDC(GetSafeHwnd(), pDC->GetSafeHdc());


	return 0L;
}

/*
   函数名：OnLayoutChange;
   函数功能：更新页面布局
   参数： nValue1 布局ID
*/

LRESULT CDataConfDlg::OnLayoutChange(WPARAM nValue1,LPARAM nValue2)
{
	m_RadButChoice = nValue1;
	InitSharePlatForm(m_RadButChoice);
	return 0L;
}

/*
   函数名：OnNMDblclkListDoc;
   函数功能：双击文档列表栏目，设置该文档为当前文档
   参数： 无
*/


void CDataConfDlg::OnNMDblclkListDoc(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_OwnerBindNum != g_BindNO)
	{
		return ;
	}

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_DocOrBoardList.ScreenToClient(&pt);

	UINT uFlag = 0;
	int hSelectedItem = m_DocOrBoardList.HitTest(pt,&uFlag);
	if (0 <= hSelectedItem)
	{
		CMenu menu;
		menu.CreatePopupMenu();

		TUP_UINT32 ID = (TUP_UINT32)m_DocOrBoardList.GetItemData(hSelectedItem);
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,ID,0,TUP_TRUE);
	}
}

/*
   函数名：OnPageInd;
   函数功能：同步文档信息
   参数： nValue1  文档ID
   参数： nValue2  页面ID
*/
LRESULT CDataConfDlg::OnPageInd(WPARAM nValue1,LPARAM nValue2)
{
	/////同步本地页面/////
	if(nValue2 == 0)
	{
		//////如果是删除页面导致nValue2为0时，此时tup_conf_ds_set_current_page后无回调//////
		m_curDoc = nValue1;
		m_curPage = nValue2;
		UpdateDocInfo(m_curDoc);

	}
	tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,nValue1,nValue2,TUP_FALSE);

	return 0L;
}
/*
   函数名：OnRefreshDocInf;
   函数功能：翻页成功后，更新文档信息
   参数： nValue1  文档ID
   参数： nValue2  页面ID
*/

LRESULT CDataConfDlg::OnRefreshDocInf(WPARAM nValue1,LPARAM nValue2)
{
	///更新文档信息/////
	m_curDoc = nValue1;
	m_curPage = nValue2;
	TUP_UINT32 m_DocID = nValue1;
	UpdateDocInfo(m_DocID);
	UpdatePenInfo(m_penInfo);
	return 0L;
}

/*
   函数名：OnBnClickedBtDeldoc;
   函数功能：删除选中的文档
   参数： 无
*/
void CDataConfDlg::OnBnClickedBtDeldoc()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("没有共享权限，删除文档失败"),3000);
		return ;
	}
	int m_SelIndex = m_DocOrBoardList.GetNextItem(-1,LVNI_FOCUSED);
	if (-1 == m_SelIndex)
	{
		/////无选中的////
		CTools::ShowMessageTimeout(_T("请选中需要删除的行"),2000);
		return ;
	}

	/////删除选中文档后，设置新的选中行//////
	int m_NewCur = m_SelIndex + 1;
	if (m_DocOrBoardList.GetItemCount() == 1)
	{
		m_NewCur = -1;
	}else if (m_SelIndex == m_DocOrBoardList.GetItemCount() - 1) ////删除的是最后一个
	{
		m_NewCur = 0;
	}

	TUP_UINT32 m_DocID = m_DocOrBoardList.GetItemData(m_SelIndex);
	if (m_DocID == 0)
	{
		return ;
	}

	TUP_RESULT tRet = tup_conf_ds_delete_doc(m_handle,IID_COMPONENT_WB,m_DocID);
	if (TC_OK == tRet)
	{
		
		/////删除文档成功/////
		if (m_NewCur != -1)
		{
			m_DocOrBoardList.SetItemState(m_NewCur,LVIS_SELECTED | LVIS_FOCUSED,LVIS_SELECTED | LVIS_FOCUSED);
		}

		if (m_DocID == m_curDoc)
		{
			////删除的是当前共享文档////
			if (m_NewCur != -1)
			{
				////设置选中的文档为当前共享文档////
				TUP_UINT32 m_DocID = m_DocOrBoardList.GetItemData(m_NewCur);
				tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_DocID,0,TUP_TRUE);
			}
			else
			{
				////无共享数据////
				m_comSelectPage.ResetContent();
				m_comSelectPage.AddString(_T("0P"));
				m_comSelectPage.SetCurSel(0);
				m_stcDeskTop.SetBitmap2(NULL);
				Invalidate(TRUE);
				m_curDoc = 0;
				m_curPage = 0;
			}
		}
		else
		{
			//////依然指定当前文档为正在共享文档/////
			tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,0,TUP_TRUE);

		}
	}
	else
	{
		/////删除文档不成功/////
	}
}
/*
   函数名：OnBnClickedBtSalve;
   函数功能：当前选中的文档
   参数： 无
*/

void CDataConfDlg::OnBnClickedBtSalve()
{
	// TODO: 在此添加控件通知处理程序代码
	int m_SelIndex = m_DocOrBoardList.GetNextItem(-1,LVNI_FOCUSED);
	if (-1 == m_SelIndex)
	{
		/////无选中的////
		CTools::ShowMessageTimeout(_T("请选中需要保存的行"),2000);
		return ;
	}
	TUP_UINT32 m_DocID = m_DocOrBoardList.GetItemData(m_SelIndex);
	if (m_DocID)
	{
		/////获取文档名称////
		CString m_filename = m_DocOrBoardList.GetItemText(m_SelIndex,COL_DOCUMENT_NAME);
		////保存文档/////
		CFileDialog fdlg(FALSE,NULL,m_filename,NULL,NULL);
		fdlg.m_ofn.lpstrFilter = _T("filetype(*.cwb)\0*.cwb\0\0");
		fdlg.m_ofn.lpstrTitle=_T("保存白板");

		if (fdlg.DoModal() == IDOK)
		{
			std::string m_strpath = CTools::UNICODE2UTF(fdlg.GetPathName());
			m_strpath.append(".cwb");
			tup_conf_ds_save(m_handle,IID_COMPONENT_WB,m_DocID,m_strpath.c_str());
		}

	}

}
/*
   函数名：OnBnClickedBtLoad;
   函数功能：加载并共享保存的文档
   参数： 无
*/

void CDataConfDlg::OnBnClickedBtLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("没有共享权限，加载白板失败"),3000);
		return ;
	}
	CFileDialog fdlg(TRUE);
	if (fdlg.DoModal())
	{
		std::string strFPath = CTools::UNICODE2UTF(fdlg.GetPathName());
		////加载白板
		TUP_UINT32 m_NewDoc = 0;
		tup_conf_ds_load(m_handle,IID_COMPONENT_WB,strFPath.c_str(),&m_NewDoc);
	}
}

void CDataConfDlg::OnBnClickedBtCopypage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("没有共享权限，复制页面失败"),3000);
		return ;
	}
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("文档或页面不存在"),2000);
		return;
	}
	if (m_curPage == 0)
	{
		CTools::ShowMessageTimeout(_T("当前为封面页不可复制，请指定当其他共享页"),2000);
		return;
	}
	TUP_UINT32 m_NewPageID = 0;
	tup_conf_ds_copy_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,&m_NewPageID);
	/////目前发现，没有回调过来，此时应注意//////
	m_curPage = m_NewPageID;

	/////解决拷贝后立马删除导致界面显示错误  by c00327158 2015-10-28 Start
	///设置拷贝页为当前页/////
	tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_NewPageID,TUP_TRUE);
	/////解决拷贝后立马删除导致界面显示错误  by c00327158 2015-10-28 End

}

void CDataConfDlg::OnBnClickedBtDelpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("没有共享权限，删除页面失败"),3000);
		return ;
	}
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("文档不存在"),2000);
		return;
	}

	TUP_UINT32 pageCount = 0;
	tup_conf_ds_get_page_count(m_handle, IID_COMPONENT_WB, m_curDoc, &pageCount);

	if (m_curPage == 0 && pageCount == 0)
	{
		/////当前页面是0，此时应指定页
		CTools::ShowMessageTimeout(_T("当前为封面页不可删除，请指定当其他共享页"),2000);
		return;
	}
	tup_conf_ds_delete_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage);

	   
}

void CDataConfDlg::OnBnClickedBtPrepage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_curDoc == 0 || m_curPage == 0)
	{
		CTools::ShowMessageTimeout(_T("文档或页面不存在"),2000);
		return;
	}

	/////获得当前的页数/////
	int m_index = m_comSelectPage.GetCurSel();
	if (!m_index)
	{
		/////页数为0，直接return；
		return ;
	}
	TUP_UINT32 m_NewPageID = 0;
	tup_conf_ds_get_pageid_byno(m_handle,IID_COMPONENT_WB,m_curDoc,TUP_UINT32(m_index -1),&m_NewPageID);
	if (m_OwnerBindNum == g_BindNO)
	{
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_NewPageID,TUP_TRUE);
	}
	else
	{
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_NewPageID,TUP_FALSE);
	}
	
}

void CDataConfDlg::OnBnClickedBtNextpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("文档不存在"),2000);
		return;
	}

	/////获得当前的页数/////
	int m_index = m_comSelectPage.GetCurSel();
	TUP_UINT32 pageCount = 0;
	tup_conf_ds_get_page_count(m_handle, IID_COMPONENT_WB, m_curDoc, &pageCount);
	if (m_index == pageCount -1)
	{
		/////最后一页，直接return；
		return ;
	}
	TUP_UINT32 m_NewPageID = 0;
	tup_conf_ds_get_pageid_byno(m_handle,IID_COMPONENT_WB,m_curDoc,TUP_UINT32(m_index + 1),&m_NewPageID);
	if (m_OwnerBindNum == g_BindNO)
	{
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_NewPageID ,TUP_TRUE);
	}
	else
	{
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_NewPageID,TUP_FALSE);
	}
}

void CDataConfDlg::OnCbnSelchangeCombSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("当前文档不存在，请新建或指定共享文档"),2000);
		return;
	}
	int m_Index = m_comSelectPage.GetCurSel();
	//////页码转换成PageID///////
	TUP_UINT32 PageID = 0;
	tup_conf_ds_get_pageid_byno(m_handle,IID_COMPONENT_WB,m_curDoc,TUP_UINT32(m_Index),&PageID);

	if (m_OwnerBindNum == g_BindNO)
	{
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,PageID,TUP_TRUE);
	}
	else
	{
		tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,PageID,TUP_FALSE);
	}
}

void CDataConfDlg::OnBnClickedBtUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	DsSyncInfo info;
	tup_conf_ds_get_syncinfo(m_handle, IID_COMPONENT_WB, &info);
	m_curDoc = info.docId;
	m_curPage = info.pageId;
    tup_conf_ds_set_current_page(m_handle, IID_COMPONENT_WB, info.docId, info.pageId, TUP_FALSE);
}

void CDataConfDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	////1.判断点的有效性/////
	ClientToScreen(&point);
	CRect m_rect;
	m_stcDeskTop.GetWindowRect(m_rect);
	if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
	{
		return;
	}

	CDC *pDC = m_stcDeskTop.GetDC();
	int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
	int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);
	ScreenToClient(&point);
	m_ptOrg.x = (point.x - 234) * ppiX;
	m_ptOrg.y = (point.y - 36) * ppiY;

	int m_Index = m_PenType.GetCurSel();
	switch (m_Index)
	{
	case 0:
		{
			/////选择的是无标注，此时可以选择标注////
			TUP_UINT32 id = 0;
			DS_HITTEST_CODE rst = DS_HITTEST_CODE_ERROR;
			TUP_UINT32 annotType = 0;
			tup_conf_annotation_hittest(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,m_ptOrg,DS_HITTEST_MODE_ALL,0,&id,&rst,&annotType);
			if(id != dsNullID && rst != DS_HITTEST_CODE_ERROR)	//选中了某个标注,进入编辑状态
			{
				if(IsAnnotSelected(m_curDoc, m_curPage, id) == false)//该标注之前未被选中,清除原来选中的那些，并选中当前这个标注
				{
					UnSelectAnnots(false);
					TUP_UINT32 ids[1] = {id};
					SelectAnnot(ids, 1);
				}
				/////进入编辑状态，文本标注部分暂时空出/////////
				/*
                    do with text

				*/
				TUP_UINT32* ids = new TUP_UINT32[m_selectAnnots.size()];
				for(size_t i = 0; i < m_selectAnnots.size(); i++)
				{
					ids[i] = m_selectAnnots[i];
				}
				tup_conf_annotation_edit_start(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,ids,m_selectAnnots.size(),id,rst,m_ptOrg);
				delete []ids;
				ids = NULL;

			}
			else  ////没有点中任何标注，清除原来选中的标注
			{
				UnSelectAnnots(true);
			}

		}break;
	case 1:
		{
			//////选择的是普通画笔，此时可以进行画笔标注/////
			tup_conf_annotation_create_start(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,DS_ANNOT_TYPE_DRAWING,DS_ANNOTDRAWING_TYPE_FREEHAND,m_ptOrg);

		}break;
	case 2:
		{
			//////选择的是高亮画笔//////
			tup_conf_annotation_create_start(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,DS_ANNOT_TYPE_DRAWING,DS_ANNOTDRAWING_TYPE_HILIGHT,m_ptOrg);

		}break;
	default:
		break;
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CDataConfDlg::UnSelectAnnots(bool bRedraw)
{
	if(m_selectAnnots.size() == 0)
	{
		return;
	}

	TUP_UINT32* ids = new TUP_UINT32[m_selectAnnots.size()];
	for(size_t i = 0; i < m_selectAnnots.size(); i++)
	{
		ids[i] = m_selectAnnots[i];
	}

	tup_conf_annotation_setselect(m_handle,IID_COMPONENT_WB, m_curDoc, m_curPage,ids, (int)m_selectAnnots.size(), DS_SELECT_MODE_UNSELECT,0,bRedraw);
	m_selectAnnots.clear();

	delete[] ids;
	ids = NULL;
}

void CDataConfDlg::SelectAnnot(TUP_UINT32* ids, int count)
{
	for(int i = 0; i < count; i++)
	{
		m_selectAnnots.push_back(ids[i]);
	}

	TUP_UINT32* newids = new TUP_UINT32[m_selectAnnots.size()];
	for(size_t i = 0; i < m_selectAnnots.size(); i++)
	{
		newids[i] = m_selectAnnots[i]; 
	}

	tup_conf_annotation_setselect(m_handle,IID_COMPONENT_WB, m_curDoc, m_curPage, newids, (int)m_selectAnnots.size(), DS_SELECT_MODE_ALL, 0, 1);
	delete[] newids;
	newids = NULL;

}

void CDataConfDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	////1.判断点的有效性/////
	ClientToScreen(&point);
	CRect m_rect;
	m_stcDeskTop.GetWindowRect(m_rect);
	if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
	{
		return;
	}

	ScreenToClient(&point);

	CDC *pDC = m_stcDeskTop.GetDC();
	int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
	int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);
	TC_POINT m_ptCur;
	m_ptCur.x = (point.x - 234) * ppiX;
	m_ptCur.y = (point.y - 36) * ppiY;

	int m_Index = m_PenType.GetCurSel();
	switch (m_Index)
	{
	case 0:
		{
			/////选择的是无标注，此时可以选择标注////
			if(m_selectAnnots.size() == 0)
				return ;
			/////处理选中的标注/////
			tup_conf_annotation_edit_update(m_handle,IID_COMPONENT_WB,m_ptCur);

		}break;
	case 1:
	case 2:
		{
			//////选择的是普通画笔，高亮画笔均采用该操作/////
			CreateDrawingData data;
			data.pt = m_ptCur;
			tup_conf_annotation_create_update(m_handle,IID_COMPONENT_WB,(TUP_VOID*)&data);
		}break;
	case 3:
		{
			///////选择的是激光笔//////
			tup_conf_annotation_laserpointer_moveto(m_handle,IID_COMPONENT_WB,m_ptCur);
		}break;
	default:
		break;
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDataConfDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	////1.判断点的有效性/////
	ClientToScreen(&point);
	CRect m_rect;
	m_stcDeskTop.GetWindowRect(m_rect);
	if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
	{
		return;
	}
	ScreenToClient(&point);
	int m_Index = m_PenType.GetCurSel();
	switch (m_Index)
	{
	case 0:
		{
			/////选择的是无标注，此时可以选择标注////
			if(m_selectAnnots.size() == 0)
				return ;
			/////处理选中的标注/////
			tup_conf_annotation_edit_done(m_handle,IID_COMPONENT_WB,TUP_FALSE);

		}break;
	case 1:
	case 2:
		{
			//////选择的是普通画笔，高亮画笔均采用该操作/////
			tup_conf_annotation_create_done(m_handle,IID_COMPONENT_WB,TUP_FALSE,NULL);
		}break;
	default:
		break;
	}

		CDialog::OnLButtonUp(nFlags, point);
}
void CDataConfDlg::OnBnClickedBtCalcle()
{
	// TODO: 在此添加控件通知处理程序代码
	UnSelectAnnots(TUP_TRUE);
}

void CDataConfDlg::OnBnClickedBtDel()
{
	// TODO: 在此添加控件通知处理程序代码
	TUP_UINT32* newids = new TUP_UINT32[m_selectAnnots.size()];
	for(size_t i = 0; i < m_selectAnnots.size(); i++)
	{
		newids[i] = m_selectAnnots[i]; 
	}

	tup_conf_annotation_delete(m_handle,IID_COMPONENT_WB, m_curDoc, m_curPage, newids, (int)m_selectAnnots.size());

	delete[] newids;
	newids = NULL;
	
}
