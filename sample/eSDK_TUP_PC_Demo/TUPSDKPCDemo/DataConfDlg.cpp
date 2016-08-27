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

// DataConfDlg.cpp : ʵ���ļ�
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
	//0��ʾû��ѡ��//1��ʾ��Ļ��2��ʾ�ĵ���3��ʾ�װ壬4��ʾ����5��ʾý��
	NOTHING =0,
	DESKTOP,
	DOCUMENT,
	WHITEBOARD,
	PROGRAME,
	MEDIA
};

typedef enum {                 /////����ͼƬ��ǵ�����
	ANNOTCUSTOMER_PICTURE,
	ANNOTCUSTOMER_MARK,
	ANNOTCUSTOMER_POINTER,

	CUSTOMER_ANNOT_COUNT
};


typedef enum {             /////����ͼƬ��ǵ�Index
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
// CDataConfDlg �Ի���

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
	/////����մ����ɹ�ǿ�ƹرջ���Ի��򣬵��³�����   c00327158 2015-10-28 Start
	if (m_handle)
	{
		tup_conf_release(m_handle);
		m_handle = 0;
	}
	/////����մ����ɹ�ǿ�ƹرջ���Ի��򣬵��³�����   c00327158 2015-10-28 End
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


// CDataConfDlg ��Ϣ�������

BOOL CDataConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_DataConfMem.DeleteAllItems();

	m_DataConfMem.ModifyStyle(0,LVS_SINGLESEL);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_ID, _T("ID"), LVCFMT_LEFT, 50);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_NAME, _T("����"), LVCFMT_LEFT, 115);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_STATUS, _T("״̬"), LVCFMT_LEFT, 60);
	m_DataConfMem.InsertColumn(COL_DATACONFMEM_MUTE, _T("����"), LVCFMT_LEFT, 60);
	DWORD dwStyle = m_DataConfMem.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;		//�����ߣ�ֻ������report����listctrl��
	m_DataConfMem.SetExtendedStyle(dwStyle); //������չ���

	m_btnGetPresenterRole.EnableWindow(FALSE);
	m_btnSharDesk.EnableWindow(FALSE);

	/////���ù���ť״̬/////
	CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_NULL);
	m_btnSharDesk.SetWindowText(L"��ѡ��������");
	m_btnSharDesk.EnableWindow(FALSE);

	//////��ʼ������Ƶ��ʾ��/////
	m_videoDis[0]= GetDlgItem(IDC_STATIC_V2);
 	m_videoDis[1]= GetDlgItem(IDC_STATIC_V3);
 	m_videoDis[2]= GetDlgItem(IDC_STATIC_V4);
 	m_videoDis[3]= GetDlgItem(IDC_STATIC_V5);
 	m_videoDis[4]= GetDlgItem(IDC_STATIC_V6);
 	m_videoDis[5]= GetDlgItem(IDC_STATIC_V7);
	//////��ʼ������ͷװ��//////////
	TUP_UINT32 retCount;
	TUP_RESULT tRet = tup_conf_video_get_deviceinfo(m_handle,NULL,&retCount);
	if(tRet != TC_OK||retCount == 0)
	{
		GetDlgItem(IDC_BUTTON_OPENVIDEO)->EnableWindow(FALSE);
		m_DataComBox.InsertString(0,L"����Ƶ�豸");
	}
	else
	{
		//////������Ƶģ��//////
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
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CDataConfDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	/////����ɫ�����ڿؼ���////////
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
	m_stcStatusTxt.SetWindowText(L"���ڼ������ݻ���");
	//������Ϣ
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
		////ȡ��ȫ�徲������////
		(CButton *)GetDlgItem(IDC_BT_ConfMute)->EnableWindow(FALSE);
		////ȡ�����ӳ�ԱȨ��//////
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

	/////���±��ػ���ID
	SetConfID(pNotify->ulConfID);
	SetCallID(pNotify->ulCallID);
	/////���ó�ʼ�����Ա��Ϣ/////
	InitiMenberlist(ulConfID,pNotify->acGroupUri);
	
	////������ϯ�����Ϣ/////
	IM_S_USERINFO m_CharmanInfo;
	if (0 == strlen(pNotify->acCharman))
	{
		////��ʱpNotify.acCharman��USM������ϯ��Ϣ����ô�����ǾͲ�ѯȺ���ӵ���ߣ�ָ����Ϊ��ϯ//////
		IM_S_IMGROUPINFO _groupInfo;
 		tRet = tup_im_getfixedgroupdetail(pNotify->acGroupUri,&_groupInfo);
		if (tRet != TUP_SUCCESS || !getAccountINfoByAccount(std::string(_groupInfo.owner),m_CharmanInfo))
		{
			CTools::ShowMessageTimeout(_T("��ȡ��ϯ��Ϣʧ��"),2000);
			return;
		}

	}
	else
	{
		if (!getAccountINfoByBingNum(std::string(pNotify->acCharman),m_CharmanInfo))
		{
			CTools::ShowMessageTimeout(_T("��ȡ��ϯ��Ϣʧ��"),2000);
			return;
		}
	}
	m_ChairMainBindNum = m_CharmanInfo.bindNO;
	m_ChaMainAccount = m_CharmanInfo.account;
	std::string m_ChairmanName = m_CharmanInfo.name;
	CString m_str;
	CTools::string2CString(m_ChairmanName,m_str);
	m_edtChairMan.SetWindowText(m_str);

	/////��ʼ����Ƶ����Ȱ�ť/////
	InitVideoINfo();
	////��ʼ�����ݻ�����棬�������ʼ���ɹ��������ʽ////
	SendMessage(WM_DATACONF_DOCUMENT_WND,0,NULL);
	InitShareButton();
	m_stcDeskTop.m_handle = m_handle;
	////��ʼ�����ݻ�����棬�������ʼ���ɹ��������ʽ////

	////��������/////
	delete confInfo;   /*pdata ��confInfo������ʱ��ᱻ���������������Ҫ�����ͷ�pdata */
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			/////����Լ��������ˣ��˳�����ʱ����������Ȩ�����ø���ϯ//////
			if(m_bisPresent)
			{
				tup_conf_user_set_role(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),CONF_ROLE_PRESENTER);
				tup_conf_as_set_owner(m_handle,GetUserIDByBindNum(m_ChairMainBindNum),AS_ACTION_ADD);
			}
			tup_conf_leave(m_handle);
		}
	}
	////��������Ҳ��Ҫ�ر�////
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
	///////����״̬///////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch (m_RadButChoice)
	{
	case NOTHING:
	{
		return ;
		break;
	}
	case DESKTOP:
		{
			//////������Ļ//////
			CString m_str ;
			m_btnSharDesk.GetWindowText(m_str);
			if (L"������Ļ" == m_str)
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
				m_btnSharDesk.SetWindowText(L"ֹͣ����");
			}else if (L"ֹͣ����" == m_str)
			{
				TUP_RESULT tRet = tup_conf_as_stop(m_handle);
				if(tRet != TUP_SUCCESS)
				{
					AfxMessageBox(L"tup_conf_as_stop failed");
					InitShareButton();
					return ;
				}
				m_btnSharDesk.SetWindowText(L"������Ļ");

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
			/////�װ��ĵ�//////
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
	m_stcStatusTxt.SetWindowText(L"�������ݻ���ɹ�");
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

	///////����״̬///////
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
	//////�����û�ʧ�ܣ���Ҫ�޸����û��б�Ľ�����ʾ/////
	char* num = (char*)w;
	int iSize = m_DataConfMem.GetItemCount();
	for (int i = 0;i<iSize;i++)
	{
		TUP_ULONG m_BindNUm = m_DataConfMem.GetItemData(i);
		if (m_BindNUm == CTools::str2num(num))
		{
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"�Ҷ�");
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
	/////���Ҿ��й���Ȩ�޵��˵���Ϣ////
	IM_S_USERINFO m_OwnerInfo;
	if (!getAccountINfoByBingNum(m_OwnerBindNum,m_OwnerInfo))
	{
		return -1L;
	}
	std::string m_OwnerName = m_OwnerInfo.name;
	CString m_strname;
	CTools::string2CString(m_OwnerName,m_strname);
	///////Ĭ���й���Ȩ�޵�����������   Start/////////
	if (m_IsSucess)
	{
		m_edtPresenter.SetWindowText(m_strname);
		//////����Ƿ��ǻ᳡����//////
		if (m_bisMute)
		{
			int iSize = m_DataConfMem.GetItemCount();
			for (int i = 0;i<iSize;i++)
			{
				if (m_OwnerInfo.bindNO == CTools::num2str(m_DataConfMem.GetItemData(i)))
				 {
					 m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
					 m_PresentBindNUm = m_OwnerInfo.bindNO;
				 }
			}

		}
	}

	///////Ĭ���й���Ȩ�޵�����������   End/////////

	m_strname+=L"���й���Ȩ��";
	m_stcShareState.SetWindowText(m_strname);
	InitShareButton();
	if (!m_IsSucess)
	{
		/////����û�гɹ�//////
		m_btnGetPresenterRole.EnableWindow(TRUE);
		if (m_bisPresent)
		{
			Sleep(1000);
			(void)tup_conf_as_set_owner(m_handle,m_OwnerId,AS_ACTION_ADD);
			m_btnGetPresenterRole.EnableWindow(FALSE);

		}
	}

	/////Ĭ�Ͼ��й���Ȩ�޵��˲��ܸ�������ģʽ///////
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
		//�ƶ��ն�ʹ�ô�����
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
			m_stcShareState.SetWindowText(L"���˹���");
			break;
		}
	case AS_STATE_START:
	case AS_STATE_VIEW:
		{
			m_stcShareState.SetWindowText(L"���ڹ���");
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

	///��ѯ������Ƿ����
	if (SetUseridByBindNum(pRecord->user_alt_uri,pRecord->user_alt_id))
	{
		//�޸Ľ���״̬��Ϣ
		int iSize = m_DataConfMem.GetItemCount();
		for (int i = 0;i<iSize;i++)
		{
			TUP_ULONG m_BindNUm = m_DataConfMem.GetItemData(i);
			if (m_BindNUm == CTools::str2num(bindno))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_ID,cstrID);
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"������");
				if (m_bisMute)
				{

					m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"����");
					
				}
				else
				{
					m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
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
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_STATUS,L"������");
		if (m_bisMute)
		{
			/////�᳡������/////
			if (isChairManOrPresent(cstrContent))
			{
				m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"δ����");
			}
			else
			{
				m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"����");
			}

			/////�᳡���������£��Լ�����ʱӦ�ý��Լ����óɾ���״̬/////////////
			if (g_UserID == pRecord->user_alt_id)
			{
                (void)tup_call_media_mute_mic(ulCallID,TUP_TRUE);
			}
		}
		else
		{
			m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"δ����");
		}

		////���ش洢�������Ϣ//////
		m_LocalMenber[pRecord->user_alt_uri] = pRecord->user_alt_id;

	}
}
void CDataConfDlg::DleConfMemBer(TC_Conf_User_Record* pRecord)
{
	std::string bindno = pRecord->user_alt_uri;
	if (SetUseridByBindNum(pRecord->user_alt_uri,pRecord->user_alt_id))
	{
		//�޸Ľ���״̬��Ϣ
		int iSize = m_DataConfMem.GetItemCount();
		for (int i = 0;i<iSize;i++)
		{
			TUP_ULONG m_BindNUm = m_DataConfMem.GetItemData(i);
			if (m_BindNUm == CTools::str2num(bindno))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"�Ҷ�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TUP_RESULT tRet = tup_conf_user_request_role(m_handle,CONF_ROLE_PRESENTER,"");
	if(tRet != TUP_SUCCESS)
	{
		AfxMessageBox(_T("Get ROLE_PRESENTER Failed��"));
	}
	////��ȡ����ӵ����//////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

// 	//��ȡ��Ƶ�豸
 	TUP_RESULT tRet = TUP_FALSE;
// 	int index = m_DataComBox.GetCurSel();

	////�������߹ر�����ͷ/////
    CString m_str;
	GetDlgItem(IDC_BUTTON_OPENVIDEO)->GetWindowText(m_str);
	if (m_str == L"��������ͷ")
	{
		tRet = tup_conf_video_open(m_handle,m_DataComBox.GetItemData(m_DataComBox.GetCurSel()),TUP_TRUE);
		if(tRet != TC_OK)
		{
			AfxMessageBox(L"tup_conf_video_open failed");
			return;
		}

		/////��ϯ֪ͨ�������������Ƶ/////
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

		GetDlgItem(IDC_BUTTON_OPENVIDEO)->SetWindowText(L"�ر�����ͷ");
	}
	else
	{
		/////�ر���Ƶ////
		tRet = tup_conf_video_close(m_handle,m_DataComBox.GetItemData(m_DataComBox.GetCurSel()));
		if(tRet != TC_OK)
		{
			AfxMessageBox(L"tup_conf_video_open failed");
			return ;
		}
		GetDlgItem(IDC_BUTTON_OPENVIDEO)->SetWindowText(L"��������ͷ");
	}

	
}
LRESULT CDataConfDlg::OnDataConfAddVideoUser(WPARAM id,LPARAM l)
{

	TUP_UINT32* deviceid = (TUP_UINT32*)l;/////�豸////
	TUP_ULONG m_ConfMemId = (TUP_ULONG) id;

	std::string m_BindNum;
	if (!GetUserBindNumByid(m_ConfMemId,m_BindNum))
	{
		return -1L;
	}

	if (m_BindNum == g_BindNO)
	{
		/////�Լ�����Ƶ
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
		/////��ϯ///////
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
        ////��ͨ�����/////
		IM_S_USERINFO m_userInfo;
		if(!getAccountINfoByBingNum(m_BindNum,m_userInfo)) return 0L;
		int m_VideoINfoIndex;
		/////��ѯ���õ��Ӵ�����//////
		if (!AvaluableVudeo(m_VideoINfoIndex))
		{
			return -1L;
		}
		m_LocalVideoINfo[m_VideoINfoIndex].isValuable = false;
		m_LocalVideoINfo[m_VideoINfoIndex].Devideid = *deviceid;
		m_LocalVideoINfo[m_VideoINfoIndex].Userid = m_ConfMemId;
		///////������ʾ��Ϣ///////
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

	/////���ٱ�����Ƶ/////
	TUP_UINT32* deviceid = (TUP_UINT32*)l;/////�豸////
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
		/////�Լ�����Ƶ
		return 0L;
	}else if (m_BindNum == m_ChairMainBindNum)
	{
		Invalidate(TRUE);
		/////��ϯ///////
		return 0L;
	}
	else
	{
		/////���ҹرյĴ���index;
		int m_VideoINfoIndex;
		if (!GetVideoINdexByid(m_VideoINfoIndex,id))
		{
			return -1L;
		}
		m_LocalVideoINfo[m_VideoINfoIndex].isValuable = true;
		m_LocalVideoINfo[m_VideoINfoIndex].Devideid = 0;
		m_LocalVideoINfo[m_VideoINfoIndex].Userid = 0;
		///////������ʾ��Ϣ///////
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
		///���Լ��ĵ�¼�˺Ų���g_BindNO
		if(!getAccountINfoByBingNum(g_BindNO,m_CharmanInfo))  
		{
			return -1L;
		}
		/////���ؼ�¼��������Ϣ/////
		m_ChairMainBindNum = g_BindNO;
		m_bisChairMan = true;
	} 
	else
	{
		/////��ѯ��������Ϣ///////
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

	//////��ʾ��������Ϣ/////
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
	TUP_ULONG m_prePresentid = w;   ////ǰһ�������˵�ID
	TUP_ULONG m_Presentid = l;   ////��ǰ�����˵�ID




	IM_S_USERINFO m_PresentInfo;

	if (m_Presentid == g_UserID)
	{
		////��ǰ�����������Լ�
		///���Լ��ĵ�¼�˺Ų���g_BindNO
		if (!getAccountINfoByBingNum(g_BindNO,m_PresentInfo))
			return  -1L;
		m_PresentBindNUm = g_BindNO;
		m_bisPresent = true;

		/////����ȡ����Ȩ�޵ĶԻ��򲻿���
		m_btnGetPresenterRole.EnableWindow(FALSE);

		/////�����˻������˲�����/////
		(void)tup_call_media_mute_mic(ulCallID, TUP_FALSE);
	} 
	else
	{
		////��ǰ�����˲����Լ�////
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

		/////����ȡ����Ȩ�޵ĶԻ������
		m_btnGetPresenterRole.EnableWindow(TRUE);

		if(m_bisMute)
		{
			if(!m_bisChairMan)
			{
				/////�������˻��������˾���/////
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

	//�����˱����ˢ��һ���б�
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
	////�ͷ�IM_S_QUERY_USERINFO_ACK�ṹ���е�TUPLIST�ڴ�/////
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
	////�ͷ�IM_S_QUERY_USERINFO_ACK�ṹ���е�TUPLIST�ڴ�/////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	   /////��Ҫ�������������Ա�Ƿ��ڻ����У��ڻ����еĲ�Ҫ����//////
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
		m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_STATUS,L"������");
		if (m_bisMute)
		{
			m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"����");
		}
		else
		{
			m_DataConfMem.SetItemText(iSize,COL_DATACONFMEM_MUTE,L"δ����");
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
			m_stcShareState.SetWindowText(L"���湲��");
		}break;
	case DOCUMENT:
		{
			SendMessage(WM_DATACONF_DOCUMENT_WND,1,NULL);
			GetDlgItem(IDC_ST_DOC)->SetWindowText(_T("�ĵ��б�"));
			GetDlgItem(IDC_BT_OPEN_NEW)->SetWindowText(_T("��"));
		}break;
	case WHITEBOARD:
		{
			SendMessage(WM_DATACONF_DOCUMENT_WND,1,NULL);
			GetDlgItem(IDC_ST_DOC)->SetWindowText(_T("�װ��б�"));
			GetDlgItem(IDC_BT_OPEN_NEW)->SetWindowText(_T("�½�"));
			//////�����ڹ���İװ��ѯ�������ĵ��б���//////
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
			//////����ǲ����Լ��Ĺ���/////
			if (g_BindNO == m_OwnerBindNum)
			{
				/////���������Լ�//////
				m_stcShareState.SetWindowText(L"�����ڹ���װ�");
			}
			else
			{
				/////��ѯ����������/////
				if (m_OwnerBindNum.size() == 0)
				{
					return;
				}
				IM_S_USERINFO m_OwnerInfo;
				getAccountINfoByBingNum(m_OwnerBindNum,m_OwnerInfo);
				CString m_strname;
				CTools::string2CString(m_OwnerInfo.name,m_strname);
				m_strname += L"���ڹ���װ�";
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
	/////���ðװ������/////
	//�����õĻ�Ĭ�ϱ���Ϊ��ɫ����0xFFFFFFFF
	tup_conf_ds_set_bgcolor(m_handle, IID_COMPONENT_WB, 0xFFFFFFFF);
	//�����õĻ�Ĭ��ģʽΪDS_DISP_MODE_FREE
	tup_conf_ds_set_dispmode(m_handle, IID_COMPONENT_WB,  DS_DISP_MODE_FREE);
	//�����õĻ�Ĭ�������ʽΪSUR_OUTPUT_HDC
	tup_conf_ds_set_surface_outputformat(m_handle, IID_COMPONENT_WB, SUR_OUTPUT_HDC);
	CRect m_rct;
	m_stcDeskTop.GetClientRect(m_rct);
	CDC *pDC = m_stcDeskTop.GetDC();
	int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
	int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);

	TC_SIZE disp = {m_rct.Width()*ppiX,m_rct.Height()*ppiY};
	//���һ������Ϊ1��ʾ���ú������ػ���棬Ϊ0���ػ�
	TUP_RESULT tRet = tup_conf_ds_set_canvas_size(m_handle, IID_COMPONENT_WB, disp, TUP_TRUE);
	if (TC_OK == tRet)
	{
		////���óɹ�/////
		SendMessage(WM_DATACONF_WB_DRAW,NULL,NULL);
	}

	//////��ʼ���Զ����ע/////
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
	//////��������/////
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
			 /////����Ƿ����Ѿ���ѡ�еİ�ť////
			 if (IDC_RAD_NULL == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))   return FALSE;
			 break;
		 case DESKTOP:
			 {
				 /////����Ƿ����Ѿ���ѡ�еİ�ť////
				 if (IDC_RAD_SCREEN == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;

				 ////����Ƿ������湲����/////
				 CString m_str ;
				 m_stcShareState.GetWindowText(m_str);
				 if (L"���ڹ���" == m_str )
				 {
					 //////���湲�����ڽ�����/////
					 CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_SCREEN);
					 CTools::ShowMessageTimeout(_T("��ֹͣ������ٽ��в���"),2000);
					 return FALSE;
				 }
			 }
			 break;
		 case DOCUMENT:
			 {
				 /////����Ƿ����Ѿ���ѡ�еİ�ť////
				 if (IDC_RAD_DOC == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
				 
			 }
			 break;
		 case WHITEBOARD:
			 {
				 /////����Ƿ����Ѿ���ѡ�еİ�ť////
				 if (IDC_RAD_WHITEBOARD == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
				 //////����Ƿ��аװ��ڹ���/////
				 DsSyncInfo info;
				 if(TC_OK == tup_conf_ds_get_syncinfo(m_handle, IID_COMPONENT_WB, &info)  && info.docId !=0)
				 {
					 CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_WHITEBOARD);
					 CTools::ShowMessageTimeout(_T("�������ǰ�װ干������"),2000);
					 return FALSE;
				 }
			 }
			 break;
		 case PROGRAME:
			 {
				 /////����Ƿ����Ѿ���ѡ�еİ�ť////
				 if (IDC_RAD_PROGRAM == GetCheckedRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA))  return FALSE;
			 }break;
		 case MEDIA:
			 {
				 /////����Ƿ����Ѿ���ѡ�еİ�ť////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//////��鵱ǰ״̬//////
	if(!CheckShareStatu(m_RadButChoice))
	{
		return ;
	}
	/////
	switch(idCtl)
	{
	case IDC_RAD_NULL:
		{
			m_btnSharDesk.SetWindowText(L"��ѡ��������");
			m_btnSharDesk.EnableWindow(FALSE);
			m_RadButChoice = NOTHING;
		}
		break;
	case IDC_RAD_SCREEN:
		{
			m_btnSharDesk.SetWindowText(L"������Ļ");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = DESKTOP;
		}
		break;
	case IDC_RAD_DOC:
		{
			m_btnSharDesk.SetWindowText(L"�����ĵ�");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = DOCUMENT;
		}
		break;
	case IDC_RAD_WHITEBOARD:
		{
			m_btnSharDesk.SetWindowText(L"����װ�");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = WHITEBOARD;
		}
		break;
	case IDC_RAD_PROGRAM:
		{
			m_btnSharDesk.SetWindowText(L"�������");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = PROGRAME;
		}
		break;
	case IDC_RAD_MEDIA:
		{
			m_btnSharDesk.SetWindowText(L"����ý��");
			m_btnSharDesk.EnableWindow(TRUE);
			m_RadButChoice = MEDIA;
		}
		break;
	default:
		{
			m_btnSharDesk.EnableWindow(FALSE);
			m_btnSharDesk.SetWindowText(L"��ѡ��������");
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
		/////����������ת���ݻ���/////
		////��ȡ��ʼ��Ա/////
		int iSize =  pConfDlg->m_listMember.GetItemCount();
		for(int i=0;i<iSize;i++)
		{
			CString cstrCallNo = pConfDlg->m_listMember.GetItemText(i,COL_MEM_CALLNO);
			CString cstrName = pConfDlg->m_listMember.GetItemText(i,COL_MEM_Name);
			std::string strCallno = CTools::UNICODE2UTF(cstrCallNo);
			m_LocalMenber[strCallno] = 0;
			/////���ز���/////
			m_DataConfMem.InsertItem(i,L"");
			m_DataConfMem.SetItemData(i,CTools::str2num(strCallno));
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_ID,0);
			cstrName = cstrName +L"(" + cstrCallNo + L")";
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_NAME,cstrName);
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_STATUS,L"δ����");
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
		}
		pConfDlg->CloseDlg();
	}
	else
	{

		///��ѯȺ���ȡ��Ա/////
		IM_S_REQUESTIMGROUPMEMBERS_ARG arg={0};
		IM_S_GROUPUSERLIST ack={0};
		arg.isSyncAll = TUP_TRUE;
		strcpy_s(arg.groupID, IM_D_GROUPID_LENGTH, strGroupID.c_str());
		//ֻ�ܲ�ѯUC�˻�
		TUP_RESULT tRet = tup_im_getfixedgroupmembers(&arg,&ack);
		if(tRet != TUP_SUCCESS)
		{
			TRACE("tup_im_getfixedgroupmembers failed");
			return ;
		}
		/////�������Ա���б�/////
		TUP_S_LIST* list =  ack.memberInfo;
		while(list != NULL)
		{
			IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
			if(NULL != groupUser)
			{
				TUP_UINT32 stuffID = groupUser->staffID;
				std::string strBingNum = groupUser->bindNO;
				/////����Ⱥ���еĳ�Ա//////
				if (m_bisChairMan)
				{
					tup_call_serverconf_add_attendee(m_ConfID,1,strBingNum.c_str(),strBingNum.size()+1);
				}
				/////��¼�¼����Ա
				m_LocalMenber[strBingNum] = stuffID;

				CString m_name,m_number,m_strID;
				CTools::string2CString(std::string(groupUser->name),m_name);
				CTools::string2CString(strBingNum,m_number);
				CTools::string2CString(CTools::num2str(stuffID),m_strID);

				//��ʼ��������Ϣ/////
				m_name = m_name +L"(" +m_number +L")";
				int nSize = m_DataConfMem.GetItemCount();
				m_DataConfMem.InsertItem(nSize,L"");
				m_DataConfMem.SetItemData(nSize,CTools::str2num(strBingNum));
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_ID,m_strID);
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_NAME,m_name);
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_STATUS,L"δ����");
				m_DataConfMem.SetItemText(nSize,COL_DATACONFMEM_MUTE,L"δ����");


			}
			list = list->next;
		}
		//////�ͷ�IM_S_GROUPUSERLIST�е�TUP_S_LISTָ��/////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			menu.AppendMenu(MF_STRING, ID_DATACONF_SETPRESENT_MEM_MENU, _T("��Ϊ������"));
		}

		    menu.AppendMenu(MF_STRING, ID_DATACONF_DEL_MEM_MENU, _T("�Ƴ������"));
		if (m_BindNum == CTools::str2num(m_ChairMainBindNum))
		{
			menu.EnableMenuItem(ID_DATACONF_DEL_MEM_MENU, MF_DISABLED|MF_GRAYED);
		}

		if ((m_BindNum == CTools::str2num(m_PresentBindNUm))||(m_BindNum == CTools::str2num(m_ChairMainBindNum)))
		{
			menu.AppendMenu(MF_STRING, ID_DATACONF_INVITEDTOSHARE_MEM_MENU, _T("���빲��"));
		}

		CString cstrCallState = m_DataConfMem.GetItemText(hSelectedItem,COL_DATACONFMEM_STATUS);
		if(cstrCallState != L"������")
		{

			menu.AppendMenu(MF_STRING, ID_DATACONF_RECALL_MEM_MENU, _T("���·������"));
/*			m_DataConfMem.SetItemText(hSelectedItem,COL_DATACONFMEM_STATUS,L"������");*/
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
			////���Ƴ����������ˣ��ջ�����Ȩ�޼�����Ȩ��
			tup_conf_user_set_role(m_handle,g_UserID,CONF_ROLE_PRESENTER);
			tup_conf_as_set_owner(m_handle,g_UserID,AS_ACTION_ADD);
		}
		tup_conf_user_kickout(m_handle,m_userInfo.staffID);
		tup_call_serverconf_kick_attendee(ulConfID,m_strCallNum.c_str());
	}
	else if(nID == ID_DATACONF_RECALL_MEM_MENU)
	{
		 tup_call_serverconf_add_attendee(ulConfID,1,m_strCallNum.c_str(),m_strCallNum.size()+1);
		 m_DataConfMem.SetItemText(nItem,COL_DATACONFMEM_STATUS,L"������");
	}
	else if(nID == ID_DATACONF_SETPRESENT_MEM_MENU)
	{
		////����Ϊ������/////
	    tup_conf_user_set_role(m_handle,m_userInfo.staffID,CONF_ROLE_PRESENTER);
		////���ù���Ȩ��/////
		tup_conf_as_set_owner(m_handle,m_userInfo.staffID,AS_ACTION_ADD);
	}
	else if(nID == ID_DATACONF_INVITEDTOSHARE_MEM_MENU)
	{
		///////���빲��//////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	TUP_RESULT tRet = tup_conf_mute(m_handle,!m_bisMute);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(L"tup_conf_mute Failed��");
		return ;
	}

}

//�����б��о����е�״̬
//m_bisMuteָ�ǲ��Ǵ���ȫ�徲����״̬
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
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"����");
			}
			else
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
			}
		}
	}
	else
	{
		for (int i = 0;i<iSize;i++)
		{
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
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
	//////�������֪ͨ����/////
	m_bisMute = bool(w);
	if (m_bisMute)
	{
		if((!m_bisPresent)&&(!m_bisChairMan))
		{
			/////��ϯ�������˲�����/////
			(void)tup_call_media_mute_mic(ulCallID,TUP_TRUE);
		}
		GetDlgItem(IDC_BT_ConfMute)->SetWindowText(L"ȡ������");
		///�޸�״̬////
		int iSize = m_DataConfMem.GetItemCount();
		
		for (int i = 0;i<iSize;i++)
		{
			CString cstrName = m_DataConfMem.GetItemText(i, COL_DATACONFMEM_NAME);
			if(!isChairManOrPresent(cstrName))
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"����");
			}
			else
			{
				m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
			}
		}
		
	}
	else
	{
		GetDlgItem(IDC_BT_ConfMute)->SetWindowText(L"ȫ�徲��");
	
		///�޸�״̬////
		int iSize = m_DataConfMem.GetItemCount();
		for (int i = 0;i<iSize;i++)
		{
			m_DataConfMem.SetItemText(i,COL_DATACONFMEM_MUTE,L"δ����");
			(void)tup_call_media_mute_mic(ulCallID,TUP_FALSE);

		}
		
	}
	

	return 0L;
}

inline void CDataConfDlg::InitShareButton()
{
//	SendMessage(WM_DATACONF_DOCUMENT_WND,0,NULL);
	CheckRadioButton(IDC_RAD_NULL,IDC_RAD_MEDIA,IDC_RAD_NULL);
	m_btnSharDesk.SetWindowText(L"��ѡ��������");
	m_btnSharDesk.EnableWindow(FALSE);
	m_RadButChoice = NOTHING;
	m_stcDeskTop.SetBitmap2(NULL);
	
}

inline void CDataConfDlg::InitVideoINfo()
{

	//////��ʼ������/////
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
	///////��ʼ��������Ϣ////////
	GetDlgItem(IDC_BUTTON_OPENVIDEO)->SetWindowText(L"��������ͷ");
	//////���ñ�����Ƶ��Ϊ���ɼ�///////
	GetDlgItem(IDC_STATIC_V1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_V8)->ShowWindow(SW_HIDE);
    /////�����ϵ���Ƶ���ڼ�������ʾ���ֲ��ɼ�//////
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
	//////��ʼ��������Ϣ/////
	m_penInfo.m_clr = 0;
	m_penInfo.m_linewidth = 1;
	m_penInfo.m_penstyle = DS_PEN_TYPE_NORMAL;
}

bool CDataConfDlg::AvaluableVudeo(int &Index)
{
	///////��ѯĿǰ�Ƿ񻹴��ڿ��õ���Ƶ����///////
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
   ��������OnDocumentWnd;
   �������ܣ��޸Ĵ�����ʾ
   ������wParam   ��Σ���ʾ��ʾģʽ////1������ģʽ 2���ĵ����װ�ģʽ
   ������lPara    �����壬��ʱ����
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
			//////����ģʽ
	 		rc.left = rcSize.left;
			rc.top = rcSize.top;
			rc.right = rc.left+ NORM_WIDTH;
	 		rc.bottom = rcSize.bottom ;
			GetDlgItem(IDC_BUTTON_SHAREDESK)->EnableWindow(TRUE);
		}break;
	case 1:
		{
			/////�ĵ�����ģʽ
			rc.left = rcSize.left;
			rc.top = rcSize.top;
			rc.right = rc.left+ DOC_WIDTH;
			rc.bottom = rcSize.bottom ;
			GetDlgItem(IDC_BUTTON_SHAREDESK)->EnableWindow(FALSE);
			///////��ʼ���ĵ��б�
			m_DocOrBoardList.DeleteAllItems();
			while ( m_DocOrBoardList.DeleteColumn (0));
			m_DocOrBoardList.ModifyStyle(0,LVS_SINGLESEL);
			m_DocOrBoardList.InsertColumn(COL_DOCUMENT_STATE, _T("״̬"), LVCFMT_LEFT, 70);
			m_DocOrBoardList.InsertColumn(COL_DOCUMENT_NAME, _T("����"), LVCFMT_LEFT, 90);
			DWORD dwStyle = m_DocOrBoardList.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;	//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
			dwStyle |= LVS_EX_GRIDLINES;		//�����ߣ�ֻ������report����listctrl��
			m_DocOrBoardList.SetExtendedStyle(dwStyle); //������չ���
			/////���û�������//////
			m_PenType.ResetContent();
			m_PenType.AddString(_T("�ޱ�ע"));
			m_PenType.AddString(_T("��ͨ����"));
			m_PenType.AddString(_T("��������"));
			m_PenType.AddString(_T("�����"));
			m_PenType.SetCurSel(0);
			/////���û�����ɫ//////
			m_LineWidth.ResetContent();
			m_LineWidth.AddString(_T("1 px"));
			m_LineWidth.AddString(_T("2 px"));
			m_LineWidth.AddString(_T("3 px"));
			m_LineWidth.AddString(_T("4 px"));
			m_LineWidth.AddString(_T("5 px"));
			m_LineWidth.AddString(_T("6 px"));
			m_LineWidth.SetCurSel(0);
			/////����ɫ�����ڿؼ���////////
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
   ��������OnBnClickedBtOpenNew;
   �������ܣ����ĵ����ߴ����װ�
   ������ ��
*/
void CDataConfDlg::OnBnClickedBtOpenNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("û�й���Ȩ�ޣ������ĵ�ʧ��"),3000);
		return ;
	}
	CString m_str;
	GetDlgItem(IDC_BT_OPEN_NEW)->GetWindowText(m_str);
	if (_T("��") == m_str)
	{
		///////�ĵ�����//////
		///1.���ĵ�////
		CString  m_DocumentPath;
		CFileDialog Filedlg(true);
		if (Filedlg.DoModal())
		{
			m_DocumentPath = Filedlg.GetPathName();
		}
		std::string m_filepath;

		//TUP_RESULT tRet = tup_conf_ds_open(m_handle,IID_COMPONENT_DS,m_DocumentPath.GetBuffer(0),DS_OPTION_SIZE,);
	} 
	else if(_T("�½�") == m_str)
	{
		//////�������ĵ�//////
		TUP_UINT32 nDocID = 0;
		if(TC_OK == tup_conf_ds_new_doc(m_handle,IID_COMPONENT_WB,&nDocID) && nDocID != 0)
		{
			m_curDoc = nDocID;
			m_curPage = 0;
			tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,0,TUP_TRUE);

		}
		else
		{
			CTools::ShowMessageTimeout(_T("�����ĵ�ʧ��"),3000);
			return ;
		}
	}
	else
	{
		/////to do  nothing
	}
}

/*
   ��������OnNewDocSuc;
   �������ܣ��½��ĵ��ɹ�
   ������ nValue1  �ĵ�ID
   ������ nValue2  �ĵ��½���ID
*/
LRESULT CDataConfDlg::OnNewDocSuc(WPARAM nValue1,LPARAM nValue2)
{
	TUP_ULONG m_DocShareID = TUP_ULONG(nValue2);
	m_curDoc = TUP_UINT32(nValue1);
	std::string m_BindNum = "";
	GetUserBindNumByid(m_DocShareID,m_BindNum);
	//////����ǲ����Լ��Ĺ���/////
	if (g_BindNO == m_BindNum)
	{
		/////���������Լ�//////
		m_stcShareState.SetWindowText(L"�����ڹ���װ�");
	}
	else
	{
		/////�����߲����Լ�///
		/////��ѯ����������/////
		IM_S_USERINFO m_OwnerInfo;
		getAccountINfoByBingNum(m_BindNum,m_OwnerInfo);
		CString m_strname;
		CTools::string2CString(m_OwnerInfo.name,m_strname);
		m_strname += L"���ڹ���װ�";
		m_stcShareState.SetWindowText(m_strname);
	}
	UpdateDocInfo(m_curDoc);
	return 0L;
}

/*
   ��������OnDelDocSuc;
   �������ܣ��½��ĵ��ɹ�
   ������ nValue1  �ĵ�ID
*/

LRESULT CDataConfDlg::OnDelDocSuc(WPARAM nValue1,LPARAM nValue2)
{
	TUP_UINT32 m_DocID = (TUP_UINT32)nValue1;
	int Index = GetDocumentIndex(m_DocID);
	if (-1 == Index)
	{
		return -1L;
	}

	/////ɾ���ĵ�////
	m_DocOrBoardList.DeleteItem(Index);
	return 0L;
}
/*
   ��������DocumentIndex;
   �������ܣ���ѯ
   �������  m_DocID
   ����ֵ���б��е�ID��ֵ����������ڣ�����-1

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
   ��������OnBnClickedBtSelectcolor;
   �������ܣ�ѡ�񻭱ʵ���ɫ
   ������ ��
*/

void CDataConfDlg::OnBnClickedBtSelectcolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//////ѡ����ɫ///////
	CColorDialog m_setColDlg;
	m_setColDlg.m_cc.Flags |= CC_FULLOPEN|CC_RGBINIT;  /////CC_RGBINIT������ʾ�ϴ�ѡ�����ɫ
	m_setColDlg.m_cc.rgbResult = m_penInfo.m_clr;                /////��¼�ϴ�ѡ�����ɫ/////
	if (IDOK == m_setColDlg.DoModal())
	{
		m_penInfo.m_clr = m_setColDlg.m_cc.rgbResult; 
	}
	/////����ɫ�����ڿؼ���////////
	CDC *pDC = GetDlgItem(IDC_STATIC_COLOR)->GetDC();
	CRect m_rct;
	GetDlgItem(IDC_STATIC_COLOR)->GetClientRect(m_rct);
	CBrush m_brs;
	m_brs.CreateSolidBrush(m_penInfo.m_clr);
	pDC->FillRect(&m_rct,&m_brs);
	/////���»�����Ϣ//////
	UpdatePenInfo(m_penInfo);
}
/*
   ��������OnCbnSelchangeCombActiontype;
   �������ܣ�ѡ�񻭱ʵ�����(��ͨ������)
   ������ ��
*/
void CDataConfDlg::OnCbnSelchangeCombActiontype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			//////�����/////
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
   ��������OnCbnSelchangeCombo1;
   �������ܣ�ѡ�񻭱ʵ��߿�(1~6px)
   ������ ��
*/
void CDataConfDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_penInfo.m_linewidth = m_LineWidth.GetCurSel() + 1;
	UpdatePenInfo(m_penInfo);
}
/*
   ��������UpdatePenInfo;
   �������ܣ����»�����ɫ���߿���Ϣ
   ������ ��
*/
void CDataConfDlg::UpdatePenInfo(PenInfo m_penInfo)
{
	DsPenInfo newPen;
	///////����������ɫ��COLORREF��ʽ�ģ���Ҫת����COLORRGBA��ʽ��///////
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
		CTools::ShowMessageTimeout(_T("���»�����Ϣʧ�ܣ�"),3000);
	}
}

/*
   ��������OnBnClickedBtNewpage;
   �������ܣ���ǰ�װ����½�ҳ��
   ������ ��
*/

void CDataConfDlg::OnBnClickedBtNewpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("û�й���Ȩ�ޣ��½�ҳ��ʧ��"),3000);
		return ;
	}
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("��ǰ�����ĵ�������"),2000);
		return ;
	}
	CRect m_Rect;
	m_stcDeskTop.GetClientRect(m_Rect);
	TUP_UINT32 nPageID;
	TUP_RESULT tRet = tup_conf_ds_new_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_Rect.Width(),m_Rect.Height(),&nPageID);
	UpdatePenInfo(m_penInfo);
	if (TC_OK != tRet)
	{
		CTools::ShowMessageTimeout(_T("�½�ҳ��ʧ�ܣ�"),3000);
		return ;
	}
	m_curPage = nPageID;
	tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,TUP_TRUE);
}
/*
   ��������UpdateDocInfo;
   �������ܣ������ĵ���Ϣ
   ������ m_DocID �ĵ�ID
*/
void CDataConfDlg::UpdateDocInfo(TUP_UINT32 m_DocID)
{
	///////������Doc��Ϣ/////
	if(!m_DocID)
	{
		return ;
	}
	/////�����ĵ�ҳ��/////////
	TUP_UINT32 m_count = 0;
	TUP_RESULT tRet = tup_conf_ds_get_page_count(m_handle,IID_COMPONENT_WB,m_DocID,&m_count);
	if (TC_OK != tRet)
	{
		CTools::ShowMessageTimeout(_T("��ѯ�ĵ�ʧ��!"),3000);
		return ;
	}
	////ɾ�������ĵ���״̬////
	for (int i = 0;i < m_DocOrBoardList.GetItemCount();i++)
	{
		m_DocOrBoardList.SetItemText(i,COL_DOCUMENT_STATE,L"");
	}

	int m_DocIndex = GetDocumentIndex(m_DocID);
	if (-1 != m_DocIndex)
	{
		//////�ĵ�����/////
		/////�޸ĵ�ǰ�ĵ���Ϣ////
		CString str;
		str.Format(_T("%d-%dP"), m_DocID, m_count);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_NAME,str);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_STATE,L"���ڹ���");
		
	}
	else
	{
		/////�ĵ�������////
		//////�ĵ������ڴ�ʱ��Ҫ�������ĵ����½����ĵ�/////
		m_DocIndex = m_DocOrBoardList.GetItemCount();
		m_DocOrBoardList.InsertItem(m_DocIndex,L"");
		m_DocOrBoardList.SetItemData(m_DocIndex,(DWORD_PTR)m_DocID);
		CString m_str;
		m_str.Format(_T("%d-%dP"), m_DocID, m_count);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_NAME,m_str);
		m_DocOrBoardList.SetItemText(m_DocIndex,COL_DOCUMENT_STATE,L"���ڹ���");
	}

	//////����ѡ��ҳ��ؼ�//////
	m_comSelectPage.ResetContent();
	if (!m_count)
	{
		/////ҳ����Ϊ0///////
		m_comSelectPage.AddString(_T("0P"));
		m_comSelectPage.SetCurSel(0);
	}
	else
	{
		//////ҳ������>=1/////
		for (int i = 1;i <= (int)m_count;i++)
		{
			CString str;
			str.Format(_T("%dP"),i);
			m_comSelectPage.AddString(str);
		}

		/////ͨ��m_curPageת���ɵ�ǰ��ҳ��/////
		int PageNUm = 0;
		tup_conf_ds_get_pageno_byid(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,&PageNUm);
		m_comSelectPage.SetCurSel(PageNUm);

	}
	
}
/*
   ��������OnNewPageSuc;
   �������ܣ��½��ĵ�ҳ��ɹ�
   ������ nValue1 �ĵ�ID
   ������ nValue2 ҳ��ID
*/

LRESULT CDataConfDlg::OnNewPageSuc(WPARAM nValue1,LPARAM nValue2)
{
	TUP_UINT32 m_DocID = nValue1;
	UpdateDocInfo(m_DocID);
	return 0L;
}
/*
   ��������OnDrawWhileBackData;
   �������ܣ����ưװ�����
   ������ ��ʱ����
*/
LRESULT CDataConfDlg::OnDrawWhileBackData(WPARAM nValue1,LPARAM nValue2)
{
	//////���°װ�����//////
	//�����֪������ߣ��ڶ��͵������������Դ�NULL
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
		//ʧ�ܣ�һ���ǻ���δ���������δ����
	}
	::ReleaseDC(GetSafeHwnd(), pDC->GetSafeHdc());


	return 0L;
}

/*
   ��������OnLayoutChange;
   �������ܣ�����ҳ�沼��
   ������ nValue1 ����ID
*/

LRESULT CDataConfDlg::OnLayoutChange(WPARAM nValue1,LPARAM nValue2)
{
	m_RadButChoice = nValue1;
	InitSharePlatForm(m_RadButChoice);
	return 0L;
}

/*
   ��������OnNMDblclkListDoc;
   �������ܣ�˫���ĵ��б���Ŀ�����ø��ĵ�Ϊ��ǰ�ĵ�
   ������ ��
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
   ��������OnPageInd;
   �������ܣ�ͬ���ĵ���Ϣ
   ������ nValue1  �ĵ�ID
   ������ nValue2  ҳ��ID
*/
LRESULT CDataConfDlg::OnPageInd(WPARAM nValue1,LPARAM nValue2)
{
	/////ͬ������ҳ��/////
	if(nValue2 == 0)
	{
		//////�����ɾ��ҳ�浼��nValue2Ϊ0ʱ����ʱtup_conf_ds_set_current_page���޻ص�//////
		m_curDoc = nValue1;
		m_curPage = nValue2;
		UpdateDocInfo(m_curDoc);

	}
	tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,nValue1,nValue2,TUP_FALSE);

	return 0L;
}
/*
   ��������OnRefreshDocInf;
   �������ܣ���ҳ�ɹ��󣬸����ĵ���Ϣ
   ������ nValue1  �ĵ�ID
   ������ nValue2  ҳ��ID
*/

LRESULT CDataConfDlg::OnRefreshDocInf(WPARAM nValue1,LPARAM nValue2)
{
	///�����ĵ���Ϣ/////
	m_curDoc = nValue1;
	m_curPage = nValue2;
	TUP_UINT32 m_DocID = nValue1;
	UpdateDocInfo(m_DocID);
	UpdatePenInfo(m_penInfo);
	return 0L;
}

/*
   ��������OnBnClickedBtDeldoc;
   �������ܣ�ɾ��ѡ�е��ĵ�
   ������ ��
*/
void CDataConfDlg::OnBnClickedBtDeldoc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("û�й���Ȩ�ޣ�ɾ���ĵ�ʧ��"),3000);
		return ;
	}
	int m_SelIndex = m_DocOrBoardList.GetNextItem(-1,LVNI_FOCUSED);
	if (-1 == m_SelIndex)
	{
		/////��ѡ�е�////
		CTools::ShowMessageTimeout(_T("��ѡ����Ҫɾ������"),2000);
		return ;
	}

	/////ɾ��ѡ���ĵ��������µ�ѡ����//////
	int m_NewCur = m_SelIndex + 1;
	if (m_DocOrBoardList.GetItemCount() == 1)
	{
		m_NewCur = -1;
	}else if (m_SelIndex == m_DocOrBoardList.GetItemCount() - 1) ////ɾ���������һ��
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
		
		/////ɾ���ĵ��ɹ�/////
		if (m_NewCur != -1)
		{
			m_DocOrBoardList.SetItemState(m_NewCur,LVIS_SELECTED | LVIS_FOCUSED,LVIS_SELECTED | LVIS_FOCUSED);
		}

		if (m_DocID == m_curDoc)
		{
			////ɾ�����ǵ�ǰ�����ĵ�////
			if (m_NewCur != -1)
			{
				////����ѡ�е��ĵ�Ϊ��ǰ�����ĵ�////
				TUP_UINT32 m_DocID = m_DocOrBoardList.GetItemData(m_NewCur);
				tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_DocID,0,TUP_TRUE);
			}
			else
			{
				////�޹�������////
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
			//////��Ȼָ����ǰ�ĵ�Ϊ���ڹ����ĵ�/////
			tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,0,TUP_TRUE);

		}
	}
	else
	{
		/////ɾ���ĵ����ɹ�/////
	}
}
/*
   ��������OnBnClickedBtSalve;
   �������ܣ���ǰѡ�е��ĵ�
   ������ ��
*/

void CDataConfDlg::OnBnClickedBtSalve()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int m_SelIndex = m_DocOrBoardList.GetNextItem(-1,LVNI_FOCUSED);
	if (-1 == m_SelIndex)
	{
		/////��ѡ�е�////
		CTools::ShowMessageTimeout(_T("��ѡ����Ҫ�������"),2000);
		return ;
	}
	TUP_UINT32 m_DocID = m_DocOrBoardList.GetItemData(m_SelIndex);
	if (m_DocID)
	{
		/////��ȡ�ĵ�����////
		CString m_filename = m_DocOrBoardList.GetItemText(m_SelIndex,COL_DOCUMENT_NAME);
		////�����ĵ�/////
		CFileDialog fdlg(FALSE,NULL,m_filename,NULL,NULL);
		fdlg.m_ofn.lpstrFilter = _T("filetype(*.cwb)\0*.cwb\0\0");
		fdlg.m_ofn.lpstrTitle=_T("����װ�");

		if (fdlg.DoModal() == IDOK)
		{
			std::string m_strpath = CTools::UNICODE2UTF(fdlg.GetPathName());
			m_strpath.append(".cwb");
			tup_conf_ds_save(m_handle,IID_COMPONENT_WB,m_DocID,m_strpath.c_str());
		}

	}

}
/*
   ��������OnBnClickedBtLoad;
   �������ܣ����ز���������ĵ�
   ������ ��
*/

void CDataConfDlg::OnBnClickedBtLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("û�й���Ȩ�ޣ����ذװ�ʧ��"),3000);
		return ;
	}
	CFileDialog fdlg(TRUE);
	if (fdlg.DoModal())
	{
		std::string strFPath = CTools::UNICODE2UTF(fdlg.GetPathName());
		////���ذװ�
		TUP_UINT32 m_NewDoc = 0;
		tup_conf_ds_load(m_handle,IID_COMPONENT_WB,strFPath.c_str(),&m_NewDoc);
	}
}

void CDataConfDlg::OnBnClickedBtCopypage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("û�й���Ȩ�ޣ�����ҳ��ʧ��"),3000);
		return ;
	}
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("�ĵ���ҳ�治����"),2000);
		return;
	}
	if (m_curPage == 0)
	{
		CTools::ShowMessageTimeout(_T("��ǰΪ����ҳ���ɸ��ƣ���ָ������������ҳ"),2000);
		return;
	}
	TUP_UINT32 m_NewPageID = 0;
	tup_conf_ds_copy_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,&m_NewPageID);
	/////Ŀǰ���֣�û�лص���������ʱӦע��//////
	m_curPage = m_NewPageID;

	/////�������������ɾ�����½�����ʾ����  by c00327158 2015-10-28 Start
	///���ÿ���ҳΪ��ǰҳ/////
	tup_conf_ds_set_current_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_NewPageID,TUP_TRUE);
	/////�������������ɾ�����½�����ʾ����  by c00327158 2015-10-28 End

}

void CDataConfDlg::OnBnClickedBtDelpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_OwnerBindNum != g_BindNO)
	{
		CTools::ShowMessageTimeout(_T("û�й���Ȩ�ޣ�ɾ��ҳ��ʧ��"),3000);
		return ;
	}
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("�ĵ�������"),2000);
		return;
	}

	TUP_UINT32 pageCount = 0;
	tup_conf_ds_get_page_count(m_handle, IID_COMPONENT_WB, m_curDoc, &pageCount);

	if (m_curPage == 0 && pageCount == 0)
	{
		/////��ǰҳ����0����ʱӦָ��ҳ
		CTools::ShowMessageTimeout(_T("��ǰΪ����ҳ����ɾ������ָ������������ҳ"),2000);
		return;
	}
	tup_conf_ds_delete_page(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage);

	   
}

void CDataConfDlg::OnBnClickedBtPrepage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_curDoc == 0 || m_curPage == 0)
	{
		CTools::ShowMessageTimeout(_T("�ĵ���ҳ�治����"),2000);
		return;
	}

	/////��õ�ǰ��ҳ��/////
	int m_index = m_comSelectPage.GetCurSel();
	if (!m_index)
	{
		/////ҳ��Ϊ0��ֱ��return��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("�ĵ�������"),2000);
		return;
	}

	/////��õ�ǰ��ҳ��/////
	int m_index = m_comSelectPage.GetCurSel();
	TUP_UINT32 pageCount = 0;
	tup_conf_ds_get_page_count(m_handle, IID_COMPONENT_WB, m_curDoc, &pageCount);
	if (m_index == pageCount -1)
	{
		/////���һҳ��ֱ��return��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_curDoc == 0)
	{
		CTools::ShowMessageTimeout(_T("��ǰ�ĵ������ڣ����½���ָ�������ĵ�"),2000);
		return;
	}
	int m_Index = m_comSelectPage.GetCurSel();
	//////ҳ��ת����PageID///////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DsSyncInfo info;
	tup_conf_ds_get_syncinfo(m_handle, IID_COMPONENT_WB, &info);
	m_curDoc = info.docId;
	m_curPage = info.pageId;
    tup_conf_ds_set_current_page(m_handle, IID_COMPONENT_WB, info.docId, info.pageId, TUP_FALSE);
}

void CDataConfDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	////1.�жϵ����Ч��/////
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
			/////ѡ������ޱ�ע����ʱ����ѡ���ע////
			TUP_UINT32 id = 0;
			DS_HITTEST_CODE rst = DS_HITTEST_CODE_ERROR;
			TUP_UINT32 annotType = 0;
			tup_conf_annotation_hittest(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,m_ptOrg,DS_HITTEST_MODE_ALL,0,&id,&rst,&annotType);
			if(id != dsNullID && rst != DS_HITTEST_CODE_ERROR)	//ѡ����ĳ����ע,����༭״̬
			{
				if(IsAnnotSelected(m_curDoc, m_curPage, id) == false)//�ñ�ע֮ǰδ��ѡ��,���ԭ��ѡ�е���Щ����ѡ�е�ǰ�����ע
				{
					UnSelectAnnots(false);
					TUP_UINT32 ids[1] = {id};
					SelectAnnot(ids, 1);
				}
				/////����༭״̬���ı���ע������ʱ�ճ�/////////
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
			else  ////û�е����κα�ע�����ԭ��ѡ�еı�ע
			{
				UnSelectAnnots(true);
			}

		}break;
	case 1:
		{
			//////ѡ�������ͨ���ʣ���ʱ���Խ��л��ʱ�ע/////
			tup_conf_annotation_create_start(m_handle,IID_COMPONENT_WB,m_curDoc,m_curPage,DS_ANNOT_TYPE_DRAWING,DS_ANNOTDRAWING_TYPE_FREEHAND,m_ptOrg);

		}break;
	case 2:
		{
			//////ѡ����Ǹ�������//////
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	////1.�жϵ����Ч��/////
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
			/////ѡ������ޱ�ע����ʱ����ѡ���ע////
			if(m_selectAnnots.size() == 0)
				return ;
			/////����ѡ�еı�ע/////
			tup_conf_annotation_edit_update(m_handle,IID_COMPONENT_WB,m_ptCur);

		}break;
	case 1:
	case 2:
		{
			//////ѡ�������ͨ���ʣ��������ʾ����øò���/////
			CreateDrawingData data;
			data.pt = m_ptCur;
			tup_conf_annotation_create_update(m_handle,IID_COMPONENT_WB,(TUP_VOID*)&data);
		}break;
	case 3:
		{
			///////ѡ����Ǽ����//////
			tup_conf_annotation_laserpointer_moveto(m_handle,IID_COMPONENT_WB,m_ptCur);
		}break;
	default:
		break;
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDataConfDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	////1.�жϵ����Ч��/////
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
			/////ѡ������ޱ�ע����ʱ����ѡ���ע////
			if(m_selectAnnots.size() == 0)
				return ;
			/////����ѡ�еı�ע/////
			tup_conf_annotation_edit_done(m_handle,IID_COMPONENT_WB,TUP_FALSE);

		}break;
	case 1:
	case 2:
		{
			//////ѡ�������ͨ���ʣ��������ʾ����øò���/////
			tup_conf_annotation_create_done(m_handle,IID_COMPONENT_WB,TUP_FALSE,NULL);
		}break;
	default:
		break;
	}

		CDialog::OnLButtonUp(nFlags, point);
}
void CDataConfDlg::OnBnClickedBtCalcle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UnSelectAnnots(TUP_TRUE);
}

void CDataConfDlg::OnBnClickedBtDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TUP_UINT32* newids = new TUP_UINT32[m_selectAnnots.size()];
	for(size_t i = 0; i < m_selectAnnots.size(); i++)
	{
		newids[i] = m_selectAnnots[i]; 
	}

	tup_conf_annotation_delete(m_handle,IID_COMPONENT_WB, m_curDoc, m_curPage, newids, (int)m_selectAnnots.size());

	delete[] newids;
	newids = NULL;
	
}
