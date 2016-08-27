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

#include "StdAfx.h"
#include "TUPSDKPCDemo.h"
#include "NotifyCallBack.h"
#include "Tools.h"
#include "IMManage.h"
#include "IMDlg.h"
#include "ConfDlg.h"
#include "DataConfDlg.h"
#include "MainDlg.h"

NotifyCallBack::NotifyCallBack(void)
{
}

NotifyCallBack::~NotifyCallBack(void)
{
}

TUP_BOOL NotifyCallBack::IMNotify(IM_E_EVENT_ID eventID, void *body)
{
	TRACE1("\nIMNotify eventID[%d] received!\n", eventID);
	switch(eventID)
	{
	case IM_E_EVENT_IM_HEARTBEAT_NOTIFY:
		{
			CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
			if(pMainDlg != NULL)
			{
				::PostMessage(pMainDlg->GetSafeHwnd(),WM_HEARTBEAT_NOTIFY,NULL,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_USERSTATUS_NOTIFY:
		{
			IM_S_USERSTATUS_NOTIFY* pNotify = new IM_S_USERSTATUS_NOTIFY;
			memset(pNotify,0,sizeof(IM_S_USERSTATUS_NOTIFY));
			memcpy(pNotify,(IM_S_USERSTATUS_NOTIFY*)body,sizeof(IM_S_USERSTATUS_NOTIFY));
			//////���״̬����///////
			CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
			CContactDlg *pDlg;
			if (pMainDlg != NULL)
			{
				 pDlg= pMainDlg->GetContacDlg();
				 if (pDlg != NULL)
				 {
					 pDlg->UpdateConStatus(pNotify->origin,pNotify->status);
				 }
			}
			
		}
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY:
		{
			IM_S_DISCUSSGROUP_NOTIFY* pBody = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_DISCUSSGROUP_NOTIFY));

			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_GROUP_NOTIFY,(WPARAM)pNotify,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY:
		{
			IM_S_DISCUSSGROUP_NOTIFY* pBody = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pNotify->groupID);
			if(NULL == pIMDlg)
			{
				pIMDlg = CIMManage::GetIntance().CreateIMDlgByGroupID(pNotify->groupID);
				pIMDlg->SetLoginAccount(g_Account);
				pIMDlg->SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
				pIMDlg->m_stcName.SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
			}
			if(NULL != pIMDlg)
			{
				pIMDlg->PostMessage(WM_GROUP_INF_CHANGE,(WPARAM)pNotify,NULL);
			}

		}
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY:
		{
			IM_S_DISCUSSGROUP_NOTIFY* pBody = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pNotify->groupID);
			if(NULL != pIMDlg)
			{
				pIMDlg->PostMessage(WM_GROUP_MEM_ADD,(WPARAM)pNotify,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY:
		{
			IM_S_DISCUSSGROUP_NOTIFY* pBody = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pNotify->groupID);
			if(NULL != pIMDlg)
			{
				pIMDlg->PostMessage(WM_GROUP_MEM_DEL,(WPARAM)pNotify,NULL);
			}

		}
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY:
		{
			IM_S_DISCUSSGROUP_NOTIFY* pBody = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByGroupID(pNotify->groupID);
			if(NULL != pIMDlg)
			{
				pIMDlg->PostMessage(WM_GROUP_MEM_OWNER,(WPARAM)pNotify,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_SENDIMINPUT_NOTIFY:
		{

		}
		break;
	case IM_E_EVENT_IM_CODECHAT_NOTIFY:
		{
			IM_S_CODECHAT_NOTIFY *notify = new IM_S_CODECHAT_NOTIFY;
			memcpy(notify,(IM_S_CODECHAT_NOTIFY*)body,sizeof(IM_S_CODECHAT_NOTIFY));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_RECV_IM,(WPARAM)notify,NULL);
			}
			
		}
		break;
	case IM_E_EVENT_IM_MSG_SENDACK_NOTIFY:
		{
			////��Ϣ���ͽ��֪ͨ////
			IM_S_SENDACK_NOTIFY *notify = new IM_S_SENDACK_NOTIFY;
			memset(notify,0,sizeof(IM_S_SENDACK_NOTIFY));
			memcpy(notify,(IM_S_SENDACK_NOTIFY*)body,sizeof(IM_S_SENDACK_NOTIFY));
			int kkk = 0;

		}
		break;
	case IM_E_EVENT_IM_LOGOUT_NOTIFY:
		{
			IM_S_LOGOUT_NOTIFY* notify = (IM_S_LOGOUT_NOTIFY*)body;
		}
		break;
//Add by lWX294490 to fix DTS2015082706818 at 2015-08-27 begin
	case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{
			IM_S_KICKOUT_NOTIFY* notify = (IM_S_KICKOUT_NOTIFY*)body;
			if(notify)
			{
				if(IM_E_EXITSTATUS_NORMALOFFLINE == notify->exitFlag)
				{
					CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
					if (pMainDlg != NULL)
					{
						::PostMessage(pMainDlg->GetSafeHwnd(), WM_IM_KICKOUT_NOTIFY, NULL, NULL);
					}
				}
			}
		}
		break;
//Add by lWX294490 to fix DTS2015082706818 at 2015-08-27 end
	case IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY:
		{
			IM_S_IMGROUP_NOTIFY* pBody = (IM_S_IMGROUP_NOTIFY*)body;
			IM_S_IMGROUP_NOTIFY* pNotfiy = new IM_S_IMGROUP_NOTIFY;
			memset(pNotfiy,0,sizeof(IM_S_IMGROUP_NOTIFY));
			memcpy(pNotfiy,pBody,sizeof(IM_S_IMGROUP_NOTIFY));
			if(NULL!= theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CONFIRM_JOINFIXEDGROUP_NOTIFY,(WPARAM)pNotfiy,NULL);
			}
		}
		break;
	case IM_E_EVENT_FIXEDGROUP_DISMISS_NOTIFY:
		{
			IM_S_IMGROUP_NOTIFY* pBody = (IM_S_IMGROUP_NOTIFY*)body;
			IM_S_IMGROUP_NOTIFY* pNotfiy = new IM_S_IMGROUP_NOTIFY;
			memset(pNotfiy,0,sizeof(IM_S_IMGROUP_NOTIFY));
			memcpy(pNotfiy,pBody,sizeof(IM_S_IMGROUP_NOTIFY));
			if(NULL!= theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_DISMISS_FIXEDGROUP_NOTIFY,(WPARAM)pNotfiy,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY:
		{
			IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY* pBody = (IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY*)body;
			IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY* pNotify = new IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_FIXGROUP_IDENTIFY_NOTIFY,(WPARAM)pNotify,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY:
		{

		}
		break;
	case IM_E_EVENT_FIXEDGROUP_WASADDEDTOGROUP_NOTIFY:
		{
			
		}
		break;
	case  IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY:
		{
			IM_S_IMGROUP_NOTIFY* pBody = (IM_S_IMGROUP_NOTIFY*)body;
			IM_S_IMGROUP_NOTIFY* pNotify = new IM_S_IMGROUP_NOTIFY;
			memcpy(pNotify,pBody,sizeof(IM_S_IMGROUP_NOTIFY));
			if(NULL!= theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_FIXGROUP_DELETE_NOTIFY,(WPARAM)pNotify,NULL);
			}
		}
		break;
	}
	return TUP_TRUE;
}
TUP_VOID NotifyCallBack::ProgressCallBack(OFFLINEHANDLE fileHandle, TUP_UINT64 ulTotal, TUP_UINT64 ulNow, void *userInfo)
{
	TRACE2("ulTotal = %d, ulNow = %d", ulTotal, ulNow);
}
TUP_INT NotifyCallBack::UMMsgTransResultCallback(OFFLINEHANDLE fileHandle, TUP_ULONG enCode, OFFLINE_RSPFILEINFO *pstFileRsp, void *userInfo)
{
	////��ȡ�û���Ϣ/////
	IM_S_USERINFO* m_User = (IM_S_USERINFO*)(userInfo);
	if (NULL == pstFileRsp) return -1;
	///��ȡ�Ի���///
	CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByAccount(m_User->account);
	if(NULL == pIMDlg)
	{
		return -1;
	}
	if (0 == enCode && 200 == pstFileRsp->ulStatusCode)// �ϴ��ɹ�  /*200����C50������ϸ����*/
	{
		switch (pstFileRsp->enCallbackType)
		{
		case OFFLINE_CALLBACK_PREUPLOAD: 	 // Ԥ�ϴ��ص�
			{
				////�ݲ�����////
				break;
			}
		case OFFLINE_CALLBACK_UPLOAD:        // �ϴ��ص�
			{
			    ::SendMessage(pIMDlg->m_hWnd, WM_SEND_IMAGEINFO_IM, (WPARAM)pstFileRsp, 0);
				break;
			}
		case OFFLINE_CALLBACK_DOWNLOAD:    // ���ػص�
			{
					::SendMessage(pIMDlg->m_hWnd, WM_SHOW_DOWNLOADIMAGE_IM, 0, 0);
				break;
			}
		case OFFLINE_CALLBACK_UPLOAD_PART:  // �ϴ���Ƭ�ص�
			{
				////�ݲ�����////
				break;
			}
		default:
			break;
		}
	}
	return 0;
}
TUP_VOID NotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	TRACE1("\nCallNotify msgid[%d] received!\n", msgid);
	switch (msgid)
	{
	case CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT:
		{
			CALL_S_MODIFY_VIDEO_RESULT *pResult = (CALL_S_MODIFY_VIDEO_RESULT*)pBody;
			TUP_INT32 callid = param1;
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);

			if (TUP_FALSE == pResult->bIsVideo)
			{
				if(NULL != pIMDlg)
				{
					pIMDlg->SendMessage(WM_CALL_SHOW_WND,0,0);
				}
			}
			if (TUP_TRUE == pResult->bIsVideo)
			{
				pIMDlg->SendMessage(WM_CALL_SHOW_WND, 1, callid);
			}
		}
		break;

	case CALL_E_EVT_CALL_STARTCALL_RESULT:
		{
			TRACE("CALL_E_EVT_CALL_STARTCALL_RESULT");
		}
		break;

	case CALL_E_EVT_SIPACCOUNT_INFO:
		{
			CALL_S_SIP_ACCOUNT_INFO* accountInfo = (CALL_S_SIP_ACCOUNT_INFO*)pBody;
			CALL_S_SIP_ACCOUNT_INFO* Info = new CALL_S_SIP_ACCOUNT_INFO;
			memcpy(accountInfo,Info,sizeof(CALL_S_SIP_ACCOUNT_INFO));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::SendMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CAll_RGE_RESLUT,(WPARAM)Info,NULL);
			}
		}
		break;
	case CALL_E_EVT_CALL_INCOMMING:
		{
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CAll_INCMING,(WPARAM)notifyInfo,NULL);
			}
			
		}
		break;
	case CALL_E_EVT_CALL_OUTGOING:
		{
			//////�����¼�/////
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CALL_OUTGOING,(WPARAM)notifyInfo,NULL);
			}
		}break;
	case CALL_E_EVT_CALL_CONNECTED:
		{		
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CAll_CONNECTED,(WPARAM)notifyInfo,NULL);
			}
			
		}
		break;
	case CALL_E_EVT_CALL_ENDED:
		{
			HWND hwndModel = ::FindWindowEx(NULL, NULL, _T("#32770"), _T("������"));
			if (hwndModel)
			{
				::PostMessage(hwndModel, WM_CLOSE, 0, 0);
				return ;
			}

			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CAll_END,(WPARAM)notifyInfo,NULL);
			}
			
		}
		break;
	case CALL_E_EVT_CALL_CALL_REINVITED:
		{
			/////Call���ܶԶ˵�Reinvite�� ���ϱ���////
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));
			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(notifyInfo->stCallStateInfo.ulCallID);
			if (pIMDlg)
			{
				pIMDlg->PostMessage(WM_CALL_INFOCHANGE,(WPARAM)notifyInfo,NULL);
			}
		}
		break;
	case CALL_E_EVT_VIDEO_OPERATION:
		{
			
		}
		break;
	case CALL_E_EVT_CALL_ADD_VIDEO:
		{
			//�յ���Ƶת��Ƶ����
			TRACE1("CallNotify Video Add received!\n", msgid);
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));

			TUP_UINT32 callid = param1;

			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);

			if(NULL != pIMDlg && ::IsWindow(pIMDlg->GetSafeHwnd()))
			{
				pIMDlg->PostMessage(WM_CAll_ADD_VIDEO,(WPARAM)notifyInfo,NULL);
			}
		}
		break;
	case CALL_E_EVT_CALL_DEL_VIDEO:
		{
			TRACE1("CallNotify Video DEL received!\n", msgid);
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));

			TUP_UINT32 callid = param1;

			CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);

			if(NULL != pIMDlg && ::IsWindow(pIMDlg->GetSafeHwnd()))
			{
				pIMDlg->SendMessage(WM_CAll_DEL_VIDEO,(WPARAM)notifyInfo,NULL);
			}
		}
		break;
	case CALL_E_EVT_NET_QUALITY_CHANGE:
		{
			CALL_S_NETQUALITY_CHANGE* pInfo = (CALL_S_NETQUALITY_CHANGE*)pBody;
			CALL_S_NETQUALITY_CHANGE* pChangeInfo = new CALL_S_NETQUALITY_CHANGE;
			memcpy(pChangeInfo,pInfo,sizeof(CALL_S_NETQUALITY_CHANGE));

			if(NULL != pChangeInfo)
			{
				TUP_UINT32 callid = param1;
				CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);
				if(NULL != pIMDlg && ::IsWindow(pIMDlg->GetSafeHwnd()))
				{
					pIMDlg->SendMessage(WM_NET_LEVEL,(WPARAM)pChangeInfo,NULL);
				}				
			}
		}
		break;
	case CALL_E_EVT_STATISTIC_NETINFO:
		{
			CALL_S_STATISTIC_NETINFO* pNetInfo = (CALL_S_STATISTIC_NETINFO*)pBody;
			if(NULL != pNetInfo)
			{
				TUP_UINT32 callid = param1;
				CIMDlg* pIMDlg = CIMManage::GetIntance().GetIMDlgByCallID(callid);
				if(NULL != pIMDlg && ::IsWindow(pIMDlg->GetSafeHwnd()))
				{
					pIMDlg->SendMessage(WM_NET_INFO,(WPARAM)pNetInfo,NULL);
				}				
			}
		}
		break;

	case CALL_E_EVT_SERVERCONF_CREATE_RESULT:
		{
			TRACE0("create conf result received!\n");
			CALL_S_CONF_CREATE_RESULT* result = (CALL_S_CONF_CREATE_RESULT*)pBody;
			CALL_S_CONF_CREATE_RESULT *pNotify = new CALL_S_CONF_CREATE_RESULT;
			memcpy(pNotify,result,sizeof(CALL_S_CONF_CREATE_RESULT));
			if(NULL != result && result->ulResult == TUP_SUCCESS)
			{	
				if(NULL != theApp.m_pMainDlgWnd)
				{
					::SendMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CONF_CREATE_RET,(WPARAM)pNotify,NULL);
				}				
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			//���������
			TRACE0("join conf result received!\n");
			TUP_UINT32 uiConfID = param1;
			CALL_S_CONF_CONNECT_RESULT *pInfo = (CALL_S_CONF_CONNECT_RESULT*)pBody;
			if(param2 == TUP_SUCCESS)
			{
				CALL_S_CONF_CONNECT_RESULT *pNotify = new CALL_S_CONF_CONNECT_RESULT;
				memcpy(pNotify,pInfo,sizeof(CALL_S_CONF_CONNECT_RESULT));
				::SendMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CONF_CONNECTED,(WPARAM)pNotify,NULL);
			}
			else
			{
				AfxMessageBox(_T("��������ʧ��"));
			}

		}
		break;
	case CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF:
		{
			////��ת�ɻ���/////
			CALL_S_CONF_BETRANSFERTOCONF* pInfo = (CALL_S_CONF_BETRANSFERTOCONF*)pBody;
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(pInfo->ulConfID);
			if (NULL == pDlg && NULL != pInfo)
			{
				CALL_S_CONF_BETRANSFERTOCONF *pNotify = new CALL_S_CONF_BETRANSFERTOCONF;
				memcpy(pNotify,pInfo,sizeof(CALL_S_CONF_BETRANSFERTOCONF));
				if(NULL != theApp.m_pMainDlgWnd)
				{
					//////��ʱ֧����������///////
					::SendMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CALL_BETRANSFER_CONF,(WPARAM)pNotify,NULL);
				}	
			}
			/////�Ҷ�����������н���/////
			CIMDlg* pIMdlg = CIMManage::GetIntance().GetIMDlgByCallID(pInfo->ulCallID);
			if (pIMdlg)
			{
				pIMdlg->CloseDlg();
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_REFRESHLIST:
		{
			//ˢ�����������
			TRACE0("refresh conf menber !\n");
			TUP_UINT32 uiConfID = param1;
			TUP_UINT32 uiMemberSize = param2;
			CALL_S_CONF_MEMBER* pMem = (CALL_S_CONF_MEMBER*)pBody;
			CALL_S_CONF_MEMBER* pNotify = new CALL_S_CONF_MEMBER[uiMemberSize];
			memcpy(pNotify,pMem,sizeof(CALL_S_CONF_MEMBER)*uiMemberSize);			
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(uiConfID);
			if(NULL != pDlg)
			{			
				pDlg->SendMessage(WM_CONF_REFESH_LIST,(WPARAM)pNotify,(LPARAM)uiMemberSize);
			}

		}
		break;
	case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:
		{
			TRACE0("add conf menber result!\n");

		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
		{			
			TUP_UINT32 uiConfID = param1;
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(uiConfID);
			char* num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num,0,IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num,IM_D_MAX_PHONE_LENGTH,(char*)pBody);
			TRACE("[%s] join in conference success!\n",num);
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CONF_ADD_MEM_SUC,(WPARAM)num,NULL);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEQUIT:
		{
			//������˳�
			TUP_UINT32 uiConfID = param1;
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(uiConfID);
			char* num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num,0,IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num,IM_D_MAX_PHONE_LENGTH,(char*)pBody);
			TRACE("[%s] exit conference!\n",num);
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CONF_MEM_QUIT,(WPARAM)num,NULL);
			}
		}

		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED:
		{
			//����߼���ʧ��
			TUP_UINT32 uiConfID = param1;
			char* num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num,0,IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num,IM_D_MAX_PHONE_LENGTH-1,(char*)pBody);
			TRACE("mem[%s] join conf failed!\n",num);
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(uiConfID);
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CONF_ADD_MEM_FAIL,(WPARAM)num,NULL);
			}
			else
			{
				/////���ݻ������ʧ��֪ͨ////
				CDataConfDlg* pDataConfDlg = NULL;
				CMainDlg* pDlg ;
				if(NULL != theApp.m_pMainDlgWnd)
				{
					pDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
					if(pDlg)
					{
						pDataConfDlg = pDlg->GetDataConfDlg();
					}
					if (pDataConfDlg)
					{
						/////֪ͨ���ݻ�����棬��Ա����ʧ��/////
						pDataConfDlg->SendMessage(WM_CONF_ADD_MEM_FAIL,(WPARAM)num,NULL);

					}
				}

			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_ADDRESSOR:
		{
			//��ʾ������
			TUP_UINT32 uiConfID = param1;
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(uiConfID);
			char* num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num,0,IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num,IM_D_MAX_PHONE_LENGTH,(char*)pBody);
			TRACE("[%s] speaking in conference!\n",num);
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CONF_MEM_SPK,(WPARAM)num,NULL);
			}

		}
		break;
	case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			//��������
			CALL_S_CONF_INFO* info = (CALL_S_CONF_INFO*)pBody;
			CALL_S_CONF_INFO* confInfo = new CALL_S_CONF_INFO;
			memcpy(confInfo,info,sizeof(CALL_S_CONF_INFO));
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CONF_INCMING,(WPARAM)confInfo,NULL);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_SUBJECT:
		{
			//��������֪ͨ
			CALL_S_CONF_SUBJECT* pSub = (CALL_S_CONF_SUBJECT*)pBody;
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(pSub->ulConfID);
			std::string* strSub = new std::string(pSub->acSubject);
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CONF_SUBJECT,(WPARAM)strSub,NULL);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_ENDED:
		{
			//�������
			HWND hwndModel = ::FindWindowEx(NULL, NULL, _T("#32770"), _T("�»�������"));
			if (hwndModel)
			{
				::SendMessage(hwndModel, WM_CLOSE, 0, 0);
			}

			TUP_UINT32 uiConfID = param1;
			CConfDlg* pDlg = CIMManage::GetIntance().GetConfDlgByConfID(uiConfID);
			
			if (NULL != theApp.m_pMainDlgWnd)
			{
				((CMainDlg*)theApp.m_pMainDlgWnd)->SetCurStatus(IM_E_STATUS_ONLINE);
			}
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CLOSE,NULL,NULL);
			}
			
		}
		break;
	case CALL_E_EVT_SERVERCONF_DATACONF_PARAM:
		{
			CALL_S_DATACONF_PARAM* pPara = (CALL_S_DATACONF_PARAM*)pBody;
			if(NULL != pPara)
			{
				CALL_S_DATACONF_PARAM *pNotify = new CALL_S_DATACONF_PARAM;
				memcpy(pNotify,pPara,sizeof(CALL_S_DATACONF_PARAM));
				TRACE("dataConf:acAuthKey=[%s],acCharman=[%s],acCmAddr=[%s],acDataConfID=[%s],acGroupUri=[%s],acPassCode=[%s]!\n",
					pNotify->acAuthKey,
					pNotify->acCharman,
					pNotify->acCmAddr,
					pNotify->acDataConfID,
					pNotify->acGroupUri,
					pNotify->acPassCode);
				if(NULL != theApp.m_pMainDlgWnd)
				{
					::SendMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_DATACONF_CREAT,(WPARAM)pNotify,NULL);
				}				
			}

		}
		break;
	case CALL_E_EVT_CALL_HOLD_SUCCESS:
	case CALL_E_EVT_CALL_HOLD_FAILED:
		{
			////���б��ֽ��/////
			TUP_UINT32 uiCallID = param1;
			CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByCallID(uiCallID);
			if (pDlg)
			{
				pDlg->SendMessage(WM_CALL_HOLE_RESULT,msgid,NULL);
			}
		}
		break;
	case CALL_E_EVT_CALL_UNHOLD_SUCCESS:
	case CALL_E_EVT_CALL_UNHOLD_FAILED:
		 {
			 /////ȡ�����б��ֳɹ�//////
			 TUP_UINT32 uiCallID = param1;
			 CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByCallID(uiCallID);
			 if (pDlg)
			 {
				 pDlg->SendMessage(WM_CALL_UNHOLE_RESULT,msgid,NULL);
			 }

		 }
		 break;
	case CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS:
	case CALL_E_EVT_CALL_BLD_TRANSFER_FAILED:
		{
			/////����ת�ƽ��/////
			CALL_S_CALL_INFO *Info = (CALL_S_CALL_INFO*)pBody;
			TUP_UINT32 uiCallID = param1;
			CIMDlg* pDlg = CIMManage::GetIntance().GetIMDlgByCallID(uiCallID);
			if (pDlg)
			{
				CALL_S_CALL_INFO *pNotify = new CALL_S_CALL_INFO;
				memcpy(pNotify,Info,sizeof(CALL_S_CALL_INFO));
				pDlg->SendMessage(WM_CALL_BLIND_RESULT,(WPARAM)pNotify,msgid);
			}

		}
		break;
	}
	return;
}



TUP_VOID NotifyCallBack::ConfNotify(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize)
{
	TRACE1("\n++++++++++ConfNotify nType[%d] received!\n", nType);
	CDataConfDlg* pDataConfDlg = NULL;
	CMainDlg* pDlg ;
	if(NULL != theApp.m_pMainDlgWnd)
	{
		pDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if(pDlg)
		{
			pDataConfDlg = pDlg->GetDataConfDlg();
		}		
	}
	if(NULL == pDataConfDlg)
	{
		return;
	}
	switch(nType)
	{
	case CONF_MSG_ON_CONFERENCE_JOIN:
		{
			//�������ݻ���ɹ�
			if(nValue1 == TC_OK)
			{
				::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_JOINSUCCESS,NULL,NULL);
			}
			else
			{
				AfxMessageBox(_T("Join Dataconf Failed��"));
			}	
			break;
		}
	case CONF_MSG_ON_LAYOUT_UPDATE:
		{
			/////�᳡���ָı�//////
			SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_LAYOUT_CHANGE,nValue1,nValue2);

		}break;
	case CONF_MSG_ON_COMPONENT_LOAD:
		{
			//��������ɹ�
			if(nValue1 == TC_OK)
			{
				::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_LOADCOM_SUCCESS,(WPARAM)nValue2,NULL);
			}
			else
			{
				AfxMessageBox(_T("Load Component Failed��"));
			}

			break;
		}
	case CONF_MSG_USER_ON_ENTER_IND:
		{
			//�û�����
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd,pRecord,sizeof(TC_Conf_User_Record));
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_USER_ADD,(WPARAM)nValue2,(LPARAM)pNewRcd);
			break;
		}
	case CONF_MSG_USER_ON_LEAVE_IND:
		{
			////�û��뿪//////
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd,pRecord,sizeof(TC_Conf_User_Record));
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_USER_DEL,(WPARAM)nValue2,(LPARAM)pNewRcd);
			break;
		}
	case CONF_MSG_ON_CONFERENCE_TERMINATE:
	case CONF_MSG_ON_CONFERENCE_LEAVE:
		{
			/////�������///
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_END,NULL,NULL);	
		}
		break;
	case CONF_MSG_USER_ON_MODIFY_IND:
		{
			/////�û���Ϣ���///////
		}
		break;
	case CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM:  ///�����������յ�
	case CONF_MSG_USER_ON_PRESENTER_CHANGE_IND: //�����˱���������˶����յ�֪ͨ
		{			
			/////��ѯ��������Ϣnvalue1����һ�������˵�ID��nValue2�����������˵�ID///////
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_PRESENTINFO,(LPARAM)nValue1,(LPARAM)nValue2);
			break;
		}
	case CONF_MSG_ON_MESSAGE_UPADATE:
		{
			TC_CONF_Param_Update* pPara = (TC_CONF_Param_Update*)pVoid;
			TRACE("TC_CONF_Param_Update= %s\n",pPara->msg_name);
			break;
		}
	case CONF_MSG_USER_ON_MESSAGE_IND:
		{
			/////�û���Ϣ֪ͨ
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;

		}
		break;
	case CONF_MSG_USER_ON_HOST_CHANGE_IND:
		{
			/////��������Ϣ���(�����˶����յ�)/////
			//nValue2�������˵�ID/////
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,false);
		}
		break;
	case CONF_MSG_USER_ON_HOST_CHANGE_CFM:
		{
			/////��������Ϣ���(���������յ�)/////
			/////���κα��//////
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,true);

		}
		break;
	case CONF_MSG_ON_MUTE:
		{
			////������ȡ��������������
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_MUTE,nValue1,NULL);
		}
		break;
	}
}

void APIENTRY NotifyCallBack::ConfComNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n|||||||||||ConfComNotify nType[%d] received!\n", nType);
}
void APIENTRY NotifyCallBack::ConfComASNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n***********ConfComASNotify nType[%d] received!\n", nType);
	CDataConfDlg* pDataConfDlg = NULL;
	CMainDlg* pDlg ;
	if(NULL != theApp.m_pMainDlgWnd)
	{
		pDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if(pDlg)
		{
			pDataConfDlg = pDlg->GetDataConfDlg();
		}		
	}
	if(NULL == pDataConfDlg)
	{
		return;
	}
	switch(nType)
	{
		case COMPT_MSG_AS_ON_SHARING_STATE:
			{
				//����״̬
				::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_STATE_NOTIFY,(WPARAM)nValue1,(LPARAM)nValue2);
				break;
			}
		case COMPT_MSG_AS_ON_SHARING_SESSION:
			{
				TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
				//����ӵ����֪ͨ
				 ::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_OWNER_NOTIFY,nValue1,(LPARAM)pRecord->user_alt_id);
				break;
			}
		case COMPT_MSG_AS_ON_SCREEN_DATA:
			{
				//������Ļ����ˢ��
				TC_AS_SCREENDATA* pData = (TC_AS_SCREENDATA*)pVoid;
				TC_AS_SCREENDATA* pNewData = new TC_AS_SCREENDATA;
				memcpy(pNewData,pData,sizeof(TC_AS_SCREENDATA));
				::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_SCREENDATA_NOTIFY,NULL,(LPARAM)pNewData);
				break;
			}
	}
}

void APIENTRY NotifyCallBack::ConfComVideoNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n???????????????ConfComVideoNotify nType[%d] received!\n", nType);
	CDataConfDlg* pDataConfDlg = NULL;
	if(NULL != theApp.m_pMainDlgWnd)
	{
		CMainDlg* pDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if(pDlg)
		{
			pDataConfDlg = pDlg->GetDataConfDlg();
		}		
	}
	if(NULL == pDataConfDlg)
	{
		return;
	}

	switch (nType)
	{
	case COMPT_MSG_VIDEO_ON_SWITCH:
		{
			TUP_UINT32* pDeviceid = new TUP_UINT32;
			*pDeviceid = *((TUP_UINT32*)pVoid);
			if (nValue1)
			{
				////��Ƶ����////
				::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_ADD_VIDEO,nValue2,(LPARAM)pDeviceid);
			}
			else
			{
				//////��Ƶ�ر�/////
				::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_DEL_VIDEO,nValue2,(LPARAM)pDeviceid);
			}

			break;
		}
	case COMPT_MSG_VIDEO_ON_NOTIFY:
		{
			/////�յ�����Ƶ֪ͨ/////
			AfxMessageBox(L"Please Open LocalVideo");
		}
		break;
	}
}
void APIENTRY NotifyCallBack::ConfComWBNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n|||||||||||ConfComWBNotify nType[%d] received!\n", nType);
	CDataConfDlg* pDataConfDlg = NULL;
	CMainDlg* pDlg ;
	if(NULL != theApp.m_pMainDlgWnd)
	{
		pDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if(pDlg)
		{
			pDataConfDlg = pDlg->GetDataConfDlg();
			CRect rcSize;
			pDataConfDlg->GetWindowRect(rcSize);
			if (rcSize.right != rcSize.left+ 1240)
			{
				SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_LAYOUT_CHANGE,3,NULL);
			}
		}
	}
	if(NULL == pDataConfDlg)
	{
		return;
	}
	switch (nType)
	{
	case COMPT_MSG_WB_ON_DOC_NEW:
		{
			////�½��ĵ�////
            TRACE2("\nCOMPT_MSG_WB_ON_DOC_NEW nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_WB_DOC_NEW,nValue1,nValue2);
		}
		break;
	case COMPT_MSG_WB_ON_DOC_DEL:
		{
			/////ɾ���ĵ�////
			TRACE2("\nCOMPT_MSG_WB_ON_DOC_DEL nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_WB_DOC_DEL,nValue1,nValue2);

		}break;
	case COMPT_MSG_WB_ON_PAGE_NEW:
		{
			///�½�ҳ��/////
			 TRACE2("\nCOMPT_MSG_WB_ON_PAGE_NEW nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_WB_PAG_NEW,nValue1,nValue2);
		}
		break;
	case COMPT_MSG_WB_ON_PAGE_DEL:
		{
			/////ɾ��ҳ
			 TRACE2("\nCOMPT_MSG_WB_ON_PAGE_DEL nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
			 /////ɾ��ҳ������Ķ���������ҳ��ҳ������ˢ��/////
		}break;
	case COMPT_MSG_WB_ON_CURRENT_PAGE_IND:
		{
			/////��ҳԤ��֪ͨ/////
			TRACE2("\nCOMPT_MSG_WB_ON_CURRENT_PAGE_IND nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_WB_PAGE_IND,nValue1,nValue2);
		}
		break;
	case COMPT_MSG_WB_ON_CURRENT_PAGE:
		{
			//��ҳ�ɹ�֪ͨ
			TRACE2("\nCOMPT_MSG_WB_ON_CURRENT_PAGE nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
		   ::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_WB_REFRESH_INFO,nValue1,nValue2);
		}break;
	case COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY:
		{
			/////��������/////
			TRACE2("\nCOMPT_MSG_WB_ON_DRAW_DATA_NOTIFY nValue1 [%d]   nValue2 [%d]\n", nValue1,nValue2);
			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_WB_DRAW,nValue1,nValue2);
		}
		break;
	default:
		break;
	}
	

}

void APIENTRY NotifyCallBack::ConfComDSNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n|||||||||||ConfComDSNotify nType[%d] received!\n", nType);
	CDataConfDlg* pDataConfDlg = NULL;
	CMainDlg* pDlg ;
	if(NULL != theApp.m_pMainDlgWnd)
	{
		pDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if(pDlg)
		{
			pDataConfDlg = pDlg->GetDataConfDlg();
		}		
	}
	if(NULL == pDataConfDlg)
	{
		return;
	}
	switch (nType)
	{
	case COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY:
		{
			////�����ĵ�ҳ������/////

		}break;
	}

}