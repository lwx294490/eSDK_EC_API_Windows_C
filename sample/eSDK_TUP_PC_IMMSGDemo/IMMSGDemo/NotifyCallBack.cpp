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

/*********************************************************************************
  *Copyright ? Huawei Technologies Co., Ltd. 1998-2011. All rights reserved.
  *FileName:			NotifyCallBack.cpp
  *Author:			王飞
  *ID				wwx302776
  *Version:			v1.1.11.103
  *Date:				2015-7-30
  *Description:		消息回调函数
**********************************************************************************/
#include "StdAfx.h"
#include "IMMSGDemo.h"
#include "NotifyCallBack.h"
#include "Tools.h"

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
	ASSERT(NULL != theApp.m_pMainWnd);
	HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();

	switch(eventID)
	{
	case IM_E_EVENT_IM_SENDIMINPUT_NOTIFY:
		{
			IM_S_SENDIMINPUT_NOTIFY *notify = (IM_S_SENDIMINPUT_NOTIFY*)body;
			::PostMessage(hwndNotify, WM_INPUT_STATUS, (WPARAM)notify, 0);
		}
		break;
	case IM_E_EVENT_IM_CODECHAT_NOTIFY:
		{
			IM_S_CODECHAT_NOTIFY *notify = new IM_S_CODECHAT_NOTIFY;
			memcpy(notify,(IM_S_CODECHAT_NOTIFY*)body,sizeof(IM_S_CODECHAT_NOTIFY));
			::PostMessage(hwndNotify, WM_RECV_IM, (WPARAM)notify, 0);			
		}
		break;
	case IM_E_EVENT_IM_CHATLIST_NOTIFY:
		{
			IM_S_CHATLIST_NOTIFY *notify = new IM_S_CHATLIST_NOTIFY;
			memcpy(notify, (IM_S_CHATLIST_NOTIFY*)body, sizeof(IM_S_CHATLIST_NOTIFY));
			::PostMessage(hwndNotify, WM_RECV_OFFLINE_IM, (WPARAM)notify, 0);
		}
		break;
	case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{
			::SendMessage(hwndNotify, WM_USER_KICKOUT, 0, 0);
		}
		break;
	default:break;
	}
	return TUP_TRUE;
}