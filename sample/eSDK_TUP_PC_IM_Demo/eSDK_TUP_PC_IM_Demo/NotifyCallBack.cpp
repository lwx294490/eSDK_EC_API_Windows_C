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
#include "eSDK_TUP_PC_IM_Demo.h"
#include "NotifyCallBack.h"
#include "Tools.h"
#include "IMDlg.h"
#include "IMManage.h"

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
	//被添加到群组通知
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
	case IM_E_EVENT_IM_LOGOUT_NOTIFY:
		{
			IM_S_LOGOUT_NOTIFY* notify = (IM_S_LOGOUT_NOTIFY*)body;
			if(NULL != theApp.m_pMainDlgWnd)
			{
				::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_DISPATCH_MESSAGE_IM,(WPARAM)notify,NULL);
			}
		}
		break;
	case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{
			::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_KICK_USER, 0, 0);
		}
		break;
	default:break;
	}
	return TUP_TRUE;
}