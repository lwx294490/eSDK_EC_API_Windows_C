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
#include "NotifyCallBack.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "eSDK_TUP_PC_VIDEO_DemoDlg.h"
#include "Data.h"

//************************************************************************
NotifyCallBack::NotifyCallBack(void)
{
}
//************************************************************************
NotifyCallBack::~NotifyCallBack(void)
{
}
//************************************************************************
TUP_BOOL NotifyCallBack::IMNotify(IM_E_EVENT_ID eventID, void *body)
{
	TRACE1("\nIMNotify eventID[%d] received!\n", eventID);
	switch (eventID)
	{
	case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{
			// 用户被踢出
			theApp.m_pMainWnd->SendMessage(WM_USER_KICKOUT, 0, 0);
		}
		break;
		default:break;
	}

	return TUP_TRUE;
}
//************************************************************************
TUP_VOID NotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	TRACE1("\nCallNotify msgid[%d] received!\n", msgid);
	switch (msgid)
	{
	case CALL_E_EVT_CALL_ENDED:
		{
			HWND hwndModel = ::FindWindowEx(NULL, NULL, _T("#32770"), _T("新会议来电"));
			if (hwndModel)
			{
				::SendMessage(hwndModel, WM_CLOSE, 0, 0);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_CREATE_RESULT:
		{
			// 创建会议结果
			CALL_S_CONF_CREATE_RESULT *pInfo = (CALL_S_CONF_CREATE_RESULT*)pBody;
			CALL_S_CONF_CREATE_RESULT *pNotify = new CALL_S_CONF_CREATE_RESULT;
			memcpy(pNotify, pInfo, sizeof(CALL_S_CONF_CREATE_RESULT));
			if (NULL != pInfo)
			{
				theApp.m_pMainWnd->SendMessage(WM_CONF_CREATE_RET, (WPARAM)pNotify, 0);
			}
		}
		break;
	case CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT:
		{
			// 视频操作修改事件,暂时用不到
// 			CALL_S_MODIFY_VIDEO_RESULT *pResult = (CALL_S_MODIFY_VIDEO_RESULT*)pBody;
// 			theApp.m_pMainWnd->SendMessage(WM_CALL_CREATE_VIDEO_WND, 0, param1);
		}
		break;
	case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			// 加入会议结果
			TUP_UINT32 uiConfID = param1;
			if (TUP_SUCCESS == param2)
			{

				theApp.m_pMainWnd->SendMessage(WM_CONF_CONNECTED, NULL, NULL);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			// 会议邀请事件
			CALL_S_CONF_INFO *info = (CALL_S_CONF_INFO*)pBody;
			CALL_S_CONF_INFO *pNotify = new CALL_S_CONF_INFO;
			memcpy(pNotify, info, sizeof(CALL_S_CONF_INFO));
			theApp.m_pMainWnd->PostMessage(WM_CONF_INCMING, (WPARAM)pNotify, NULL);
		}
		break;
	case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:
		{
			// 添加与会者结果
		}
		break;
	case CALL_E_EVT_SERVERCONF_REFRESHLIST:
		{
			// 刷新与会者结果
// 			TUP_UINT32 uiMemberSize = param2;
// 			CALL_S_CONF_MEMBER *pInfo = (CALL_S_CONF_MEMBER*)pBody;
// 			CALL_S_CONF_MEMBER *pNotify = new CALL_S_CONF_MEMBER[uiMemberSize];
// 			memcpy(pNotify, pInfo, sizeof(CALL_S_CONF_MEMBER) * uiMemberSize);
// 			theApp.m_pMainWnd->SendMessage(WM_CONF_REFESH_LIST, (WPARAM)pNotify, uiMemberSize);
		}
		break;
	case CALL_E_EVT_SERVERCONF_SUBJECT:
		{
			// 上报会议主题
		}
		break;
	case CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM:
		{
			// 上报主席号码
		}
		break;
	case CALL_E_EVT_SERVERCONF_DATACONF_PARAM:
		{
			// 上报会议相关参数
			CALL_S_DATACONF_PARAM *pParam = (CALL_S_DATACONF_PARAM*)pBody;
			if (NULL != pParam)
			{
				CALL_S_DATACONF_PARAM *pNotify = new CALL_S_DATACONF_PARAM;
				memcpy(pNotify, pParam, sizeof(CALL_S_DATACONF_PARAM));
				TRACE("dataConf:acAuthKey=[%s],acCharman=[%s],acCmAddr=[%s],acDataConfID=[%s],acGroupUri=[%s],acPassCode=[%s]!\n",
					pNotify->acAuthKey,
					pNotify->acCharman,
					pNotify->acCmAddr,
					pNotify->acDataConfID,
					pNotify->acGroupUri,
					pNotify->acPassCode);

				theApp.m_pMainWnd->SendMessage(WM_DATACONF_CREAT, (WPARAM)pNotify, NULL);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT:
		{
			// 踢出与会者结果
		}
		break;
	case CALL_E_EVT_SERVERCONF_END_RESULT:
		{
			// 结束会议结果
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEKICKED:
		{
			// 与会者被踢出
		}
		break;
	case CALL_E_EVT_SERVERCONF_ENDED:
		{
			// 会议被结束
			HWND hwndModel = ::FindWindowEx(NULL, NULL, _T("#32770"), _T("新会议来电"));
			if (hwndModel)
			{
				::SendMessage(hwndModel, WM_CLOSE, 0, 0);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
		{
			// 与会者加入成功
			TUP_UINT32 uiConfID = param1;
			char *num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num, 0, IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num, IM_D_MAX_PHONE_LENGTH, (char*)pBody);
			TRACE("[%s] join in conference success!\n", num);
			theApp.m_pMainWnd->SendMessage(WM_CONF_ADD_MEM_SUC, (WPARAM)num, NULL);
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED:
		{
			// 与会者加入失败
			TUP_UINT32 uiConfID = param1;
			char *num = new char[IM_D_MAX_PHONE_LENGTH];
			memset(num, 0, IM_D_MAX_PHONE_LENGTH);
			strcpy_s(num, IM_D_MAX_PHONE_LENGTH, (char*)pBody);
			TRACE("[%s] join in conference fail!\n", num);
			theApp.m_pMainWnd->SendMessage(WM_CONF_ADD_MEM_FAIL, (WPARAM)num, NULL);
		}
		break;
	default:break;
	}
}
//************************************************************************
TUP_VOID NotifyCallBack::ConfNotify(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize)
{
	TRACE1("\n++++++++++ConfNotify nType[%d] received!\n", nType);
	HWND hwndMain = theApp.m_pMainWnd->m_hWnd;
	switch(nType)
	{
	case CONF_MSG_ON_LAYOUT_UPDATE:
		{
			// 同步会议布局
			::PostMessage(hwndMain, WM_CONF_LAYOUT_CHANGE, (WPARAM)nValue1, 0);
		}
		break;
	case CONF_MSG_ON_CONFERENCE_JOIN:
		{
			//加入数据会议成功
			if(nValue1 == TC_OK)
			{
				::SendMessage(hwndMain, WM_DATACONF_JOINSUCCESS, NULL, NULL);
			}
			else
			{
				AfxMessageBox(_T("Join Dataconf Failed！"));
			}	
			break;
		}
	case CONF_MSG_ON_COMPONENT_LOAD:
		{
			//加载组件成功
			if(nValue1 != TC_OK)
			{
				AfxMessageBox(_T("Load Component Failed！"));
			}
		}
		break;
	case CONF_MSG_USER_ON_ENTER_IND:
		{
			//用户加入
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
			::SendMessage(hwndMain, WM_DATACONF_USER_ADD, (WPARAM)nValue2, (LPARAM)pNewRcd);
		}
		break;
	case CONF_MSG_USER_ON_LEAVE_IND:
		{
			////用户离开//////
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
			::SendMessage(hwndMain, WM_DATACONF_USER_DEL, (WPARAM)nValue2, (LPARAM)pNewRcd);
		}
		break;
	case CONF_MSG_ON_CONFERENCE_TERMINATE:
	case CONF_MSG_ON_CONFERENCE_LEAVE:
		{
			/////会议结束///
			::SendMessage(hwndMain, WM_DATACONF_END, NULL, NULL);
		}
		break;
	case CONF_MSG_USER_ON_MODIFY_IND:
		{
			/////用户信息变更///////
		}
		break;
	case CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM:  ///主动申请人收到
	case CONF_MSG_USER_ON_PRESENTER_CHANGE_IND: //主讲人变更，所有人都能收到通知
		{			
			/////查询主讲人信息nvalue1是上一个主讲人的ID，nValue2是新设主持人的ID///////
// 			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_PRESENTINFO,(LPARAM)nValue1,(LPARAM)nValue2);
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

		}
		break;
	case CONF_MSG_USER_ON_HOST_CHANGE_IND:
		{
			/////主持人信息表更(所有人都能收到)/////
			//nValue2是主持人的ID/////
// 			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,FALSE);
		}
		break;
	case CONF_MSG_USER_ON_HOST_CHANGE_CFM:
		{
			/////主持人信息表更(仅主持人收到)/////
			/////无任何标记//////
// 			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,TRUE);

		}
		break;
	case CONF_MSG_ON_MUTE:
		{
			////静音（取消静音变更结果）
// 			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_MUTE,nValue1,NULL);
		}
		break;
	}
}
//************************************************************************
void APIENTRY NotifyCallBack::ConfComVideoNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n???????????????ConfComVideoNotify nType[%d] received!\n", nType);
	
	HWND hMainWnd = (theApp.m_pMainWnd)->GetSafeHwnd();
	switch (nType)
	{
	case COMPT_MSG_VIDEO_ON_SWITCH:
		{
			TUP_UINT32* pDeviceid = new TUP_UINT32;
			*pDeviceid = *((TUP_UINT32*)pVoid);
			if (nValue1)
			{
				////视频开启////
				::SendMessage(hMainWnd, WM_DATACONF_ADD_VIDEO, nValue2, (LPARAM)pDeviceid);
			}
			else
			{
				//////视频关闭/////
				::SendMessage(hMainWnd, WM_DATACONF_DEL_VIDEO, nValue2, (LPARAM)pDeviceid);
			}

			break;
		}
	case COMPT_MSG_VIDEO_ON_NOTIFY:
		{
			/////收到打开视频通知/////
			AfxMessageBox(L"Open Your Video");
		}
		break;
	}
}
//************************************************************************
void APIENTRY NotifyCallBack::ConfComNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n|||||||||||ConfComNotify nType[%d] received!\n", nType);
}
//************************************************************************
void APIENTRY NotifyCallBack::ConfComASNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n***********ConfComASNotify nType[%d] received!\n", nType);
	switch(nType)
	{
	case COMPT_MSG_AS_ON_SHARING_STATE:
		{
			//共享状态
// 			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_STATE_NOTIFY,(WPARAM)nValue1,(LPARAM)nValue2);
			break;
		}
	case COMPT_MSG_AS_ON_SHARING_SESSION:
		{
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			//共享拥有者通知
// 			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_OWNER_NOTIFY,nValue1,(LPARAM)pRecord->user_alt_id);
			break;
		}
	case COMPT_MSG_AS_ON_SCREEN_DATA:
		{
			//共享屏幕数据刷新
			TC_AS_SCREENDATA* pData = (TC_AS_SCREENDATA*)pVoid;
			TC_AS_SCREENDATA* pNewData = new TC_AS_SCREENDATA;
			memcpy(pNewData,pData,sizeof(TC_AS_SCREENDATA));
// 			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_SCREENDATA_NOTIFY,NULL,(LPARAM)pNewData);
			break;
		}
	}
}
//************************************************************************
void APIENTRY NotifyCallBack::ConfComWBNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\n|||||||||||ConfComWBNotify nType[%d] received!\n", nType);
	switch (nType)
	{
	case COMPT_MSG_WB_ON_DOC_NEW:
		{
			////新建文档////

		}
		break;
	case COMPT_MSG_WB_ON_PAGE_NEW:
		{
			///新建页面/////

		}
		break;
	case COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY:
		{
			/////绘制数据/////

		}
		break;
	case COMPT_MSG_WB_ON_CURRENT_PAGE_IND:
		{
			/////翻页预先通知/////

		}
		break;
	default:
		break;
	}
}