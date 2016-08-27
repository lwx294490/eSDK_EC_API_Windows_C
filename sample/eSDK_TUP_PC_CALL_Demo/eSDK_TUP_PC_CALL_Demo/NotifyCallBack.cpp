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
#include "eSDK_TUP_PC_CALL_Demo.h"
#include "NotifyCallBack.h"
#include "Tools.h"

NotifyCallBack::NotifyCallBack(void)
{
}

NotifyCallBack::~NotifyCallBack(void)
{
}


TUP_VOID NotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	TRACE1("\nCallNotify msgid[%d] received!\n", msgid);
	switch(msgid)
	{
	case CALL_E_EVT_SIPACCOUNT_INFO:
		{
			////sip注册消息////
			CALL_S_SIP_ACCOUNT_INFO* notify = (CALL_S_SIP_ACCOUNT_INFO*)pBody;
			int kkk = 0;
		}
		break;
	case CALL_E_EVT_CALL_INCOMMING:
		{
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo, info, sizeof(CALL_S_CALL_INFO));
			if(NULL != theApp.m_pMainWnd)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_CAll_INCMING, (WPARAM)notifyInfo, NULL);
			}
		}
		break;
	case CALL_E_EVT_CALL_RINGBACK:
		{
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_CAll_RING, NULL, NULL);
		}
		break;
	case CALL_E_EVT_CALL_CONNECTED:
		{
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_CAll_CONNECTED, NULL, NULL);
		}
		break;
	case CALL_E_EVT_CALL_ENDED:
		{
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_CAll_ENDED, NULL, NULL);
		}
		break;
	case CALL_E_EVT_CALL_AUTHORIZE_SUCCESS:
		{
			///鉴权成功/////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_LOGIN_RESULT, (WPARAM)true, NULL);
		}
		break;
	case CALL_E_EVT_CALL_AUTHORIZE_FAILED:
		{
			////鉴权失败/////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_LOGIN_RESULT, (WPARAM)false, NULL);
		}
		break;
	case CALL_E_EVT_CALL_LOGOUT_NOTIFY:
		{
			///CallLogout/////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_KICK_USER, NULL, NULL);
		}
	}
	return;
}