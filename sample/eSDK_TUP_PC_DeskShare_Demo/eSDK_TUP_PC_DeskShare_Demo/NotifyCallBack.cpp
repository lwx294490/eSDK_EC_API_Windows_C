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
			// �û����߳�
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
			//��������
			CALL_S_CONF_CREATE_RESULT* result = (CALL_S_CONF_CREATE_RESULT*)pBody;
			if(NULL != result && result->ulResult == TUP_SUCCESS)
			{
				if(NULL != theApp.m_pMainWnd)
				{
					//��������ɹ�
					::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_CREATE_SUCCESS, NULL, NULL);
				}
			}
			break;
		}
 		case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			if(NULL != theApp.m_pMainWnd)
			{
				//��ϯ�������ɹ�
				Sleep(500);
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_MEET_MANAGER_CONNECTED, NULL, NULL);
			}
			break;
		}
		case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			//��������
			CALL_S_CONF_INFO* info = (CALL_S_CONF_INFO*)pBody;
			CALL_S_CONF_INFO* confInfo = new CALL_S_CONF_INFO;
			memcpy(confInfo, info, sizeof(CALL_S_CONF_INFO));
			if(NULL != theApp.m_pMainWnd)
			{
				//��������
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
			//�ɹ�����һ������μ���
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
			//ˢ�»����б�
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
			//��������
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
			//�������ݻ���ɹ�
			if(nValue1 == TC_OK)
			{
				::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_DATACONF_JOINSUCCESS, NULL, NULL);
			}
			else
			{
				AfxMessageBox(_T("�������ݻ���ʧ�ܣ�"));
			}	
			break;
		}
		case CONF_MSG_ON_COMPONENT_LOAD:
		{
			//��������ɹ�
			if(nValue1 == TC_OK)
			{
				//::PostMessage(pDataConfDlg->GetSafeHwnd(),WM_DATACONF_LOADCOM_SUCCESS,(WPARAM)nValue2,NULL);
			}
			else
			{
				AfxMessageBox(_T("�������ʧ�ܣ�"));
			}

			break;
		}
		case CONF_MSG_USER_ON_ENTER_IND:
		{
			//�û�����
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_USER_ADD,(WPARAM)nValue2,(LPARAM)pNewRcd);
			break;
		}
		case CONF_MSG_USER_ON_LEAVE_IND:
		{
			////�û��뿪//////
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			memcpy(pNewRcd,pRecord,sizeof(TC_Conf_User_Record));
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_USER_DEL,(WPARAM)nValue2,(LPARAM)pNewRcd);
			break;
		}
		case CONF_MSG_ON_CONFERENCE_TERMINATE:
		case CONF_MSG_ON_CONFERENCE_LEAVE:
		{
			/////�������///
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_END,NULL,NULL);	\
			break;
		}
		case CONF_MSG_USER_ON_MODIFY_IND:
		{
			/////�û���Ϣ���///////
			break;
		}
		case CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM:  ///�����������յ�
		case CONF_MSG_USER_ON_PRESENTER_CHANGE_IND: //�����˱���������˶����յ�֪ͨ
		{			
			/////��ѯ��������Ϣnvalue1����һ�������˵�ID��nValue2�����������˵�ID///////
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
			/////�û���Ϣ֪ͨ
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			TC_Conf_User_Record* pNewRcd = new TC_Conf_User_Record;
			break;
		}
		case CONF_MSG_USER_ON_HOST_CHANGE_IND:
		{
			/////��������Ϣ���(�����˶����յ�)/////
			//nValue2�������˵�ID/////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,false);
			break;
		}
		case CONF_MSG_USER_ON_HOST_CHANGE_CFM:
		{
			/////��������Ϣ���(���������յ�)/////
			/////���κα��//////
			::PostMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_UPDATE_CHAIRMAININFO,(LPARAM)nValue2,true);
			break;
		}
		case CONF_MSG_ON_MUTE:
		{
			////������ȡ��������������
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
			//����״̬
			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_STATE_NOTIFY,(WPARAM)nValue1,(LPARAM)nValue2);
			break;
		}
		case COMPT_MSG_AS_ON_SHARING_SESSION:
		{
			TC_Conf_User_Record* pRecord = (TC_Conf_User_Record*)pVoid;
			//����ӵ����֪ͨ
			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_OWNER_NOTIFY,nValue1,(LPARAM)pRecord->user_alt_id);
			break;
		}
		case COMPT_MSG_AS_ON_SCREEN_DATA:
		{
			//������Ļ����ˢ��
			TC_AS_SCREENDATA* pData = (TC_AS_SCREENDATA*)pVoid;
			TC_AS_SCREENDATA* pNewData = new TC_AS_SCREENDATA;
			memcpy(pNewData,pData,sizeof(TC_AS_SCREENDATA));
			::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(),WM_DATACONF_AS_SCREENDATA_NOTIFY,NULL,(LPARAM)pNewData);
			break;
		}
	}
}