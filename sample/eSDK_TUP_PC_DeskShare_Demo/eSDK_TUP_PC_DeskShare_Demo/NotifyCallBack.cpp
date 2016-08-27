#include "StdAfx.h"
#include "eSDK_TUP_PC_DeskShare_Demo.h"
#include "NotifyCallBack.h"


NotifyCallBack::NotifyCallBack(void)
{
}

NotifyCallBack::~NotifyCallBack(void)
{
}

TUP_BOOL NotifyCallBack::IMNotify(IM_E_EVENT_ID eventID, void *body)
{
	TRACE1("\nIMNotify eventID[%d] received!\n", eventID);
	switch (eventID)
	{
		case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{
			// 用户被踢出
			theApp.m_pMainWnd->SendMessage(WM_USER_KICKOUT, 0, 0);
			break;
		}
		default:
		{
			break;
		}
	}

	return TUP_TRUE;
}

TUP_VOID NotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	switch(msgid)
	{
		case CALL_E_EVT_SERVERCONF_CREATE_RESULT:
		{
			//创建会议
			CALL_S_CONF_CREATE_RESULT* result = (CALL_S_CONF_CREATE_RESULT*)pBody;
			if(NULL != result && result->ulResult == TUP_SUCCESS)
			{
				if(NULL != theApp.m_pMainWnd)
				{
					//创建会议成功
					::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_CREATE_SUCCESS, NULL, NULL);
				}
			}
			break;
		}
 		case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			if(NULL != theApp.m_pMainWnd)
			{
				//主席加入会议成功
				Sleep(500);
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_MANAGER_CONNECTED, NULL, NULL);
			}
			break;
		}
		case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			//会议邀请
			CALL_S_CONF_INFO* info = (CALL_S_CONF_INFO*)pBody;
			CALL_S_CONF_INFO* confInfo = new CALL_S_CONF_INFO;
			memcpy(confInfo, info, sizeof(CALL_S_CONF_INFO));
			if(NULL != theApp.m_pMainWnd)
			{
				//会议邀请
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_INVITE, (WPARAM)confInfo, NULL);
			}
			break;
		}
		case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:
		{
			TRACE0("add conf menber result!\n");
			break;
		}
		case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
		{
			//成功加入一名会议参加者
			char* num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num, 0, IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num, IM_D_MAX_PHONE_LENGTH, (char*)pBody);
			if(NULL != theApp.m_pMainWnd)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_MEMBER_JOINED_SUCCESS, (WPARAM)num, NULL);
			}
			break;
		}
		case CALL_E_EVT_SERVERCONF_REFRESHLIST:
		{
			//刷新会议列表
			TUP_UINT32 uiConfID = param1;
			TUP_UINT32 uiMemberSize = param2;
			CALL_S_CONF_MEMBER* pMemList = (CALL_S_CONF_MEMBER*)pBody;
			CALL_S_CONF_MEMBER* pNotify = new CALL_S_CONF_MEMBER[uiMemberSize];
			memcpy(pNotify, pMemList, sizeof(CALL_S_CONF_MEMBER)*uiMemberSize);
			if(NULL != theApp.m_pMainWnd)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_MEMBER_REFRESH, (WPARAM)pNotify, (LPARAM)uiMemberSize);
			}
			break;
		}
		case CALL_E_EVT_SERVERCONF_ENDED:
		{
			//结束会议
			TUP_UINT32 uiConfID = param1;
			if(NULL != theApp.m_pMainWnd)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_ENDED, (WPARAM)uiConfID, NULL);
			}
			break;
		}
		case CALL_E_EVT_SERVERCONF_DATACONF_PARAM:
		{
			CALL_S_DATACONF_PARAM* pPara = (CALL_S_DATACONF_PARAM*)pBody;
			if(NULL != pPara)
			{
				CALL_S_DATACONF_PARAM *pNotify = new CALL_S_DATACONF_PARAM;
				memcpy(pNotify, pPara, sizeof(CALL_S_DATACONF_PARAM));
				if(NULL != theApp.m_pMainWnd)
				{
					::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_DATACONF_CREAT, (WPARAM)pNotify, NULL);
				}
			}
			break;
		}
	}
	return;
}

TUP_VOID NotifyCallBack::ConfNotify(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize)
{
	switch(nType)
	{
		case CONF_MSG_ON_CONFERENCE_JOIN:
		{
			//加入数据会议成功
			if(nValue1 == TC_OK)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_DATACONF_JOINSUCCESS, NULL, NULL);
			}
			else
			{
				AfxMessageBox(_T("加入数据会议失败！"));
			}	
			break;
		}
		case CONF_MSG_ON_COMPONENT_LOAD:
		{
			//加载组件成功
			if(nValue1 == TC_OK)
			{
				//::PostMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_LOADCOM_SUCCESS,(WPARAM)nValue2,NULL);
			}
			else
			{
				AfxMessageBox(_T("加载组件失败！"));
			}

			break;
		}
		case CONF_MSG_USER_ON_ENTER_IND:
		{
			//用户加入
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_USER_ADD,(WPARAM)nValue2,(LPARAM)pNewRcd);
			break;
		}
		case CONF_MSG_USER_ON_LEAVE_IND:
		{
			////用户离开//////
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd,pRecord,sizeof(TC_Conf_User_Record));
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_USER_DEL,(WPARAM)nValue2,(LPARAM)pNewRcd);
			break;
		}
		case CONF_MSG_ON_CONFERENCE_TERMINATE:
		case CONF_MSG_ON_CONFERENCE_LEAVE:
		{
			/////会议结束///
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_END,NULL,NULL);	\
			break;
		}
		case CONF_MSG_USER_ON_MODIFY_IND:
		{
			/////用户信息变更///////
			break;
		}
		case CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM:  ///主动申请人收到
		case CONF_MSG_USER_ON_PRESENTER_CHANGE_IND: //主讲人变更，所有人都能收到通知
		{			
			/////查询主讲人信息nvalue1是上一个主讲人的ID，nValue2是新设主持人的ID///////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_UPDATE_PRESENTINFO,(LPARAM)nValue1,(LPARAM)nValue2);
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
			/////用户消息通知
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			break;
		}
		case CONF_MSG_USER_ON_HOST_CHANGE_IND:
		{
			/////主持人信息表更(所有人都能收到)/////
			//nValue2是主持人的ID/////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,false);
			break;
		}
		case CONF_MSG_USER_ON_HOST_CHANGE_CFM:
		{
			/////主持人信息表更(仅主持人收到)/////
			/////无任何标记//////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,true);
			break;
		}
		case CONF_MSG_ON_MUTE:
		{
			////静音（取消静音变更结果）
//			::PostMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_MUTE,nValue1,NULL);
			break;
		}
		
	}
	return;
}

void APIENTRY NotifyCallBack::ConfComASNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	/*TRACE1("\n***********ConfComASNotify nType[%d] received!\n", nType);
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
	}*/
	switch(nType)
	{
		case COMPT_MSG_AS_ON_SHARING_STATE:
		{
			//共享状态
			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_STATE_NOTIFY,(WPARAM)nValue1,(LPARAM)nValue2);
			break;
		}
		case COMPT_MSG_AS_ON_SHARING_SESSION:
		{
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			//共享拥有者通知
			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_OWNER_NOTIFY,nValue1,(LPARAM)pRecord->user_alt_id);
			break;
		}
		case COMPT_MSG_AS_ON_SCREEN_DATA:
		{
			//共享屏幕数据刷新
			TC_AS_SCREENDATA* pData = (TC_AS_SCREENDATA*)pVoid;
			TC_AS_SCREENDATA* pNewData = new TC_AS_SCREENDATA;
			memcpy(pNewData,pData,sizeof(TC_AS_SCREENDATA));
			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_SCREENDATA_NOTIFY,NULL,(LPARAM)pNewData);
			break;
		}
	}
}