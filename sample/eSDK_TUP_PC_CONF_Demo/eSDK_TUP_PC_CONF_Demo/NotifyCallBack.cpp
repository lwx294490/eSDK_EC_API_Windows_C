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
#include "eSDK_TUP_PC_CONF_Demo.h"
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
	ASSERT(NULL != theApp.m_pMainWnd);
	HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();
	switch (eventID)
	{
	case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{
			::PostMessage(hwndNotify, WM_KICK_USER, 0, 0);
		}
		break;
	default:break;
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
		}
		break;
	case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			if(NULL != theApp.m_pMainWnd)
			{
				//主席加入会议成功
				Sleep(500);
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_MANAGER_CONNECTED, NULL, NULL);
			}
		}
		break;
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
		}
		break;
	case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:
		{
			TRACE0("add conf menber result!\n");
		}
		break;
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
		}
		break;
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
		}
		break;
	case CALL_E_EVT_SERVERCONF_ENDED:
		{
			//结束会议
			TUP_UINT32 uiConfID = param1;
			if(NULL != theApp.m_pMainWnd)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_ENDED, (WPARAM)uiConfID, NULL);
			}
		}
		break;
		case CALL_E_EVT_SERVERCONF_ADDRESSOR:
			{
				//显示发言人
				char* cPhoneNum = new char[IM_D_MAX_PHONE_LENGTH];
				memset(cPhoneNum, 0, IM_D_MAX_PHONE_LENGTH);
				strcpy_s(cPhoneNum, IM_D_MAX_PHONE_LENGTH, (char*)pBody);
				if(NULL != theApp.m_pMainWnd)
				{
					::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_MEM_SPEAK, (WPARAM)cPhoneNum, NULL);
				}
			}
			break;
	}
	return;
}