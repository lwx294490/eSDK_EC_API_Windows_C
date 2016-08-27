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
			// �û����߳�
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
			HWND hwndModel = ::FindWindowEx(NULL, NULL, _T("#32770"), _T("�»�������"));
			if (hwndModel)
			{
				::SendMessage(hwndModel, WM_CLOSE, 0, 0);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_CREATE_RESULT:
		{
			// ����������
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
			// ��Ƶ�����޸��¼�,��ʱ�ò���
// 			CALL_S_MODIFY_VIDEO_RESULT *pResult = (CALL_S_MODIFY_VIDEO_RESULT*)pBody;
// 			theApp.m_pMainWnd->SendMessage(WM_CALL_CREATE_VIDEO_WND, 0, param1);
		}
		break;
	case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			// ���������
			TUP_UINT32 uiConfID = param1;
			if (TUP_SUCCESS == param2)
			{

				theApp.m_pMainWnd->SendMessage(WM_CONF_CONNECTED, NULL, NULL);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			// ���������¼�
			CALL_S_CONF_INFO *info = (CALL_S_CONF_INFO*)pBody;
			CALL_S_CONF_INFO *pNotify = new CALL_S_CONF_INFO;
			memcpy(pNotify, info, sizeof(CALL_S_CONF_INFO));
			theApp.m_pMainWnd->PostMessage(WM_CONF_INCMING, (WPARAM)pNotify, NULL);
		}
		break;
	case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:
		{
			// �������߽��
		}
		break;
	case CALL_E_EVT_SERVERCONF_REFRESHLIST:
		{
			// ˢ������߽��
// 			TUP_UINT32 uiMemberSize = param2;
// 			CALL_S_CONF_MEMBER *pInfo = (CALL_S_CONF_MEMBER*)pBody;
// 			CALL_S_CONF_MEMBER *pNotify = new CALL_S_CONF_MEMBER[uiMemberSize];
// 			memcpy(pNotify, pInfo, sizeof(CALL_S_CONF_MEMBER) * uiMemberSize);
// 			theApp.m_pMainWnd->SendMessage(WM_CONF_REFESH_LIST, (WPARAM)pNotify, uiMemberSize);
		}
		break;
	case CALL_E_EVT_SERVERCONF_SUBJECT:
		{
			// �ϱ���������
		}
		break;
	case CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM:
		{
			// �ϱ���ϯ����
		}
		break;
	case CALL_E_EVT_SERVERCONF_DATACONF_PARAM:
		{
			// �ϱ�������ز���
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
			// �߳�����߽��
		}
		break;
	case CALL_E_EVT_SERVERCONF_END_RESULT:
		{
			// ����������
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEKICKED:
		{
			// ����߱��߳�
		}
		break;
	case CALL_E_EVT_SERVERCONF_ENDED:
		{
			// ���鱻����
			HWND hwndModel = ::FindWindowEx(NULL, NULL, _T("#32770"), _T("�»�������"));
			if (hwndModel)
			{
				::SendMessage(hwndModel, WM_CLOSE, 0, 0);
			}
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
		{
			// ����߼���ɹ�
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
			// ����߼���ʧ��
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
			// ͬ�����鲼��
			::PostMessage(hwndMain, WM_CONF_LAYOUT_CHANGE, (WPARAM)nValue1, 0);
		}
		break;
	case CONF_MSG_ON_CONFERENCE_JOIN:
		{
			//�������ݻ���ɹ�
			if(nValue1 == TC_OK)
			{
				::SendMessage(hwndMain, WM_DATACONF_JOINSUCCESS, NULL, NULL);
			}
			else
			{
				AfxMessageBox(_T("Join Dataconf Failed��"));
			}	
			break;
		}
	case CONF_MSG_ON_COMPONENT_LOAD:
		{
			//��������ɹ�
			if(nValue1 != TC_OK)
			{
				AfxMessageBox(_T("Load Component Failed��"));
			}
		}
		break;
	case CONF_MSG_USER_ON_ENTER_IND:
		{
			//�û�����
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
			::SendMessage(hwndMain, WM_DATACONF_USER_ADD, (WPARAM)nValue2, (LPARAM)pNewRcd);
		}
		break;
	case CONF_MSG_USER_ON_LEAVE_IND:
		{
			////�û��뿪//////
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
			::SendMessage(hwndMain, WM_DATACONF_USER_DEL, (WPARAM)nValue2, (LPARAM)pNewRcd);
		}
		break;
	case CONF_MSG_ON_CONFERENCE_TERMINATE:
	case CONF_MSG_ON_CONFERENCE_LEAVE:
		{
			/////�������///
			::SendMessage(hwndMain, WM_DATACONF_END, NULL, NULL);
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
			/////�û���Ϣ֪ͨ
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;

		}
		break;
	case CONF_MSG_USER_ON_HOST_CHANGE_IND:
		{
			/////��������Ϣ���(�����˶����յ�)/////
			//nValue2�������˵�ID/////
// 			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,FALSE);
		}
		break;
	case CONF_MSG_USER_ON_HOST_CHANGE_CFM:
		{
			/////��������Ϣ���(���������յ�)/////
			/////���κα��//////
// 			::SendMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,TRUE);

		}
		break;
	case CONF_MSG_ON_MUTE:
		{
			////������ȡ��������������
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
				////��Ƶ����////
				::SendMessage(hMainWnd, WM_DATACONF_ADD_VIDEO, nValue2, (LPARAM)pDeviceid);
			}
			else
			{
				//////��Ƶ�ر�/////
				::SendMessage(hMainWnd, WM_DATACONF_DEL_VIDEO, nValue2, (LPARAM)pDeviceid);
			}

			break;
		}
	case COMPT_MSG_VIDEO_ON_NOTIFY:
		{
			/////�յ�����Ƶ֪ͨ/////
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
			//����״̬
// 			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_STATE_NOTIFY,(WPARAM)nValue1,(LPARAM)nValue2);
			break;
		}
	case COMPT_MSG_AS_ON_SHARING_SESSION:
		{
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			//����ӵ����֪ͨ
// 			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_OWNER_NOTIFY,nValue1,(LPARAM)pRecord->user_alt_id);
			break;
		}
	case COMPT_MSG_AS_ON_SCREEN_DATA:
		{
			//������Ļ����ˢ��
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
			////�½��ĵ�////

		}
		break;
	case COMPT_MSG_WB_ON_PAGE_NEW:
		{
			///�½�ҳ��/////

		}
		break;
	case COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY:
		{
			/////��������/////

		}
		break;
	case COMPT_MSG_WB_ON_CURRENT_PAGE_IND:
		{
			/////��ҳԤ��֪ͨ/////

		}
		break;
	default:
		break;
	}
}