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
#include "stdafx.h"
#include "NotifyCallBack.h"
#include "eSDK_TUP_PC_CONF_Demo.h"
#include "eSDK_TUP_PC_CONF_DemoDlg.h"
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

	switch (eventID)
	{
		case IM_E_EVENT_IM_LOGOUT_NOTIFY:		//用户退出
			{
				//ASSERT(NULL != theApp.m_pMainWnd);
				if ( NULL != theApp.m_pMainWnd )
				{
					HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();
					if ( NULL != hwndNotify )
					{
						IM_S_LOGOUT_NOTIFY *notify = (IM_S_LOGOUT_NOTIFY*)body;
						if ( NULL != notify )
						{
							::SendMessage(hwndNotify, WM_LOGOUT, (WPARAM)notify, 0);
						}
						notify = NULL;
					}
				}
				break;
			}
		case IM_E_EVENT_IM_KICKOUT_NOTIFY:			//用户被踢通知,应该是用户被挤下线
			{
				//ASSERT(NULL != theApp.m_pMainWnd);
				if ( NULL != theApp.m_pMainWnd )
				{
					HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();
					if ( NULL != hwndNotify )
					{
						IM_S_KICKOUT_NOTIFY* notify = (IM_S_KICKOUT_NOTIFY*)body;
						if ( NULL != notify )
						{
							::SendMessage(hwndNotify, WM_USER_KICKOUT, (WPARAM)notify, 0);
						}
						notify = NULL;
					}
				}
				break;
			}
		default:
			break;
	}
	return TUP_TRUE;
}

TUP_VOID NotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	TRACE1("\nCallNotify msgid[%d] received!\n", msgid);
	switch (msgid)
	{
		case CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF:		//被转会议
			{
				/////被转成会议//一键入会后收到的会议成功消息//////
				ASSERT(NULL != theApp.m_pMainWnd);
				HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
				if ( NULL != hwndNotify )
				{
					CALL_S_CONF_BETRANSFERTOCONF* pNotify = (CALL_S_CONF_BETRANSFERTOCONF*)pBody;
					if ( NULL != pNotify )
					{
						::SendMessage(hwndNotify,WM_INTOCONF,(WPARAM)pNotify,NULL);
					}
					pNotify = NULL;
				}
				break;
			}
		case CALL_E_EVT_SERVERCONF_REFRESHLIST:			//刷新与会者列表
			{
				TRACE0("refresh conf member !\n");
				ASSERT(NULL != theApp.m_pMainWnd);
				HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
				if ( NULL != hwndNotify )
				{
					TUP_UINT32 uiConfID = param1;
					TUP_UINT32 uiMemberSize = param2;
					CALL_S_CONF_MEMBER* pMem = (CALL_S_CONF_MEMBER*)pBody;
					if ( NULL != pMem )
					{
						CALL_S_CONF_MEMBER* pNotify = new CALL_S_CONF_MEMBER[uiMemberSize];
						if ( NULL != pNotify )
						{
							memcpy(pNotify,pMem,sizeof(CALL_S_CONF_MEMBER)*uiMemberSize);
							::SendMessage(hwndNotify,WM_REFRESHMEMBER,(WPARAM)pNotify,uiMemberSize);
							delete [] pNotify;
							pNotify = NULL;
						}
						pMem = NULL;
					}
				}
				break;
			}
		case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:		//收到添加成员结果信息后，刷新成员列表
			{
				break;
			}
		case CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT:		//踢出与会者结果
			{
				break;
			}
		case CALL_E_EVT_SERVERCONF_ENDED:		//133 会议被结束
			{
				// 会议被结束
				ASSERT(NULL != theApp.m_pMainWnd);
				if ( NULL != theApp.m_pMainDlg )
				{
					HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
					if ( NULL != theApp.m_pMainDlg->m_pConfDlg )
					{
						HWND hwndModel = theApp.m_pMainDlg->m_pConfDlg->GetSafeHwnd();
						if ( NULL != hwndModel)
						{
							::SendMessage( hwndModel, WM_CLOSE, 0, 0 );
						}
					}
					if ( NULL != theApp.m_pMainDlg->m_pDataConfDlg )
					{
						HWND hwndModel = theApp.m_pMainDlg->m_pDataConfDlg->GetSafeHwnd();
						if ( NULL != hwndModel )
						{
							::SendMessage( hwndModel, WM_DATACONF_BE_CLOSED, 0, 0 );
						}
					}
					if ( NULL != hwndNotify )
					{
						::SendMessage( hwndNotify, WM_CLEAR_MEETING_LIST, 0, 0 ); 
					}
				}
				break;
			}
		case CALL_E_EVT_CALL_DESTROY:			//删除呼叫ID
			{
				//在这里开始
				break;
			}
		case CALL_E_EVT_SERVERCONF_INCOMING:	//会议邀请事件
			{
				ASSERT(NULL != theApp.m_pMainWnd);
				HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
				if ( NULL != hwndNotify )
				{
					CALL_S_CONF_INFO *info = (CALL_S_CONF_INFO*)pBody;
					if (NULL != info)
					{
						CALL_S_CONF_INFO *pNotify = new CALL_S_CONF_INFO;
						if ( NULL != pNotify )
						{
							memcpy(pNotify, info, sizeof(CALL_S_CONF_INFO));
							::SendMessage(hwndNotify,WM_CONF_INCMING, (WPARAM)pNotify, NULL);
							delete pNotify;
							pNotify = NULL;
						}
						info = NULL;
					}
				}
				break;
			}
		case CALL_E_EVT_SERVERCONF_CREATE_RESULT:
			{
				// 创建会议结果
				ASSERT(NULL != theApp.m_pMainWnd);
				HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
				if ( NULL != hwndNotify )
				{
					CALL_S_CONF_CREATE_RESULT *pInfo = (CALL_S_CONF_CREATE_RESULT*)pBody;
					if ( NULL != pInfo )
					{
						CALL_S_CONF_CREATE_RESULT *pNotify = new CALL_S_CONF_CREATE_RESULT;
						if ( NULL != pNotify )
						{
							memcpy(pNotify, pInfo, sizeof(CALL_S_CONF_CREATE_RESULT));
							::SendMessage(hwndNotify, WM_CONF_CREATE_RET, (WPARAM)pNotify, NULL);
							delete pNotify;
							pNotify = NULL;
						}
						pInfo = NULL;
					}
				}
				break;
			}
		case CALL_E_EVT_CALL_ENDED:			//语音会议结束
			{
				ASSERT(NULL != theApp.m_pMainWnd);
				HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
				if ( NULL != hwndNotify )
				{
					HWND hwndModel = GetDlgItem(hwndNotify,IDD_DIALOG_INCOMING);
					if ( NULL != hwndModel)
					{
						::SendMessage(hwndModel, WM_CLOSE, 0, 0);
					}
				}
				break;
			}
		case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
			{
				break;
			}
		case CALL_E_EVT_EXIT_UI_MSGQUEUE:
			{
				break;
			}
		case CALL_E_EVT_SIPACCOUNT_INFO:                     /**< 通知上层应用，SIP账户信息改变 1*/
			{
				TRACE0("SIPACCOUNT_INFO be changed !\n");
				break;
			}
		case CALL_E_EVT_SERVERCONF_END_RESULT:				// 131 结束会议结果  语音会议
			{
				ASSERT(NULL != theApp.m_pMainWnd);
				if ( NULL != theApp.m_pMainDlg )
				{
					if ( NULL != theApp.m_pMainDlg->m_pConfDlg )
					{
						HWND hwndModel = theApp.m_pMainDlg->m_pConfDlg->GetSafeHwnd();
						if ( NULL != hwndModel )
						{
							::SendMessage(hwndModel, WM_CLOSE, 0, 0);
						}
					}
					HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
					if ( NULL != hwndNotify )
					{
						::SendMessage( hwndNotify, WM_CLEAR_MEETING_LIST, 0, 0 ); 
					}
				}
				break;
			}
		case CALL_E_EVT_SERVERCONF_DATACONF_PARAM:
			{
				ASSERT(NULL != theApp.m_pMainWnd);
				HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
				if (hwndNotify)
				{
					CALL_S_DATACONF_PARAM *pPara = (CALL_S_DATACONF_PARAM*)pBody;
					if(NULL != pPara)
					{
						CALL_S_DATACONF_PARAM *pNotify = new CALL_S_DATACONF_PARAM;
						if ( NULL != pNotify )
						{
							memcpy(pNotify, pPara, sizeof(CALL_S_DATACONF_PARAM));
							//CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = CeSDK_TUP_PC_CONF_DemoDlg::FromHandle(hwndNotify);
							CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
							if(NULL != pDemoDlg)
							{
								if (NULL != pDemoDlg->m_pDataConfDlg)
								{
									::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(), WM_DATACONF_CREAT, (WPARAM)pNotify, NULL);
								}
								pDemoDlg = NULL;
							}
							delete pNotify;
							pNotify = NULL;
						}
					}
					pPara = NULL;
				}
				break;
			}
		case CALL_E_EVT_SERVERCONF_CONNECT_ONEKEY_TO_CONF_RESULT:
			{
				if ( NULL != theApp.m_pMainWnd )
				{
					HWND hwndNotify = theApp.m_pMainWnd->GetSafeHwnd();	//得到窗口对象指针的句柄
					if ( NULL != hwndNotify )
					{
						CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
						if(NULL != pDemoDlg)
						{
							if ( NULL != pDemoDlg->m_pConfDlg )
							{
								if ( NULL != pDemoDlg->m_pConfDlg->GetSafeHwnd() )
								{
									::SendMessage(pDemoDlg->m_pConfDlg->GetSafeHwnd(), WM_ONEKEY_TO_CONF_RESULT, (WPARAM)param1, (LPARAM)param2);
								}
							}
							if ( NULL != pDemoDlg->m_pDataConfDlg )
							{
								if ( NULL != pDemoDlg->m_pDataConfDlg->GetSafeHwnd() )
								{
									::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(), WM_ONEKEY_TO_CONF_RESULT, (WPARAM)param1, (LPARAM)param2);
								}
							}
							pDemoDlg = NULL;
						}
					}
				}
				break;
			}
		default:
			{
				TRACE1("\nCallNotify msgid[%d] received but not be accepted!\n", msgid);
				break;
			}
	}
	return ;
}

TUP_VOID NotifyCallBack::ConfNotify(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize)
{
	TRACE1("\nDataConfNotify msgid[%d] received!\n", nType);
	switch (nType)
	{
		case CONF_MSG_ON_CONFERENCE_JOIN:
			{
				//加入数据会议成功
				if(nValue1 == TC_OK)
				{
					CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
					if(NULL != pDemoDlg)
					{
						if (NULL != pDemoDlg->m_pDataConfDlg)
						{
							::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(), WM_DATACONF_JOINSUCCESS, NULL, NULL);
						}
					}
					pDemoDlg = NULL;
				}
				else
				{
					AfxMessageBox(_T("加入数据会议失败！"));
				}	
				break;
			}
		case CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM:		//主动申请人收到
		case CONF_MSG_USER_ON_PRESENTER_CHANGE_IND:		//主讲人变更，所有人都能收到此通知
			{
				CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
				if(NULL != pDemoDlg)
				{
					if (NULL != pDemoDlg->m_pDataConfDlg)
					{
					    /////查询主讲人信息nvalue1是上一个主讲人的ID，nValue2是新设主持人的ID///////
					    ::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_UPDATE_PRESENTINFO,(LPARAM)nValue1,(LPARAM)nValue2);
					}
				}
				pDemoDlg = NULL;
				break;
			}
		case CONF_MSG_USER_ON_ENTER_IND:            ////用户加入//////
			{
				TC_Conf_User_Record *pRecord = (TC_Conf_User_Record *)pVoid;
				if ( NULL != pRecord )
				{
					TC_Conf_User_Record *pNewRcd = new TC_Conf_User_Record;
					if ( NULL != pNewRcd )
					{
						memcpy(pNewRcd, pRecord, sizeof(TC_Conf_User_Record));
						CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
						if(NULL != pDemoDlg)
						{
							if (NULL != pDemoDlg->m_pDataConfDlg)
							{
								::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_USER_ADD,(WPARAM)nValue2,(LPARAM)pNewRcd);
							}
							pDemoDlg = NULL;
						}
						delete pNewRcd;
						pNewRcd = NULL;
					}
					pRecord = NULL;
				}
				break;
			}
		case CONF_MSG_USER_ON_LEAVE_IND:					////用户离开//////
			{
				TC_Conf_User_Record *pRecord = (TC_Conf_User_Record*)pVoid;
				if ( NULL != pRecord )
				{
					TC_Conf_User_Record *pNewRcd = new TC_Conf_User_Record;
					if ( NULL != pNewRcd )
					{
						memcpy(pNewRcd,pRecord,sizeof(TC_Conf_User_Record));
						CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
						if(NULL != pDemoDlg)
						{
							if (NULL != pDemoDlg->m_pDataConfDlg)
							{
								::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_USER_DEL,(WPARAM)nValue2,(LPARAM)pNewRcd);
							}
							pDemoDlg = NULL;
						}
						delete pNewRcd;
						pNewRcd = NULL;
					}
					pRecord = NULL;
				}
				break;
			}
		case CONF_MSG_ON_CONFERENCE_LEAVE:		//用户被踢出会议
			{
				CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
				if(NULL != pDemoDlg)
				{
					if (NULL != pDemoDlg->m_pDataConfDlg)
					{
						::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_END,NULL,NULL);
					}
				}
				pDemoDlg = NULL;
				break;
			}
		default:
			break;
	}
	return;
}

void APIENTRY NotifyCallBack::ConfComASNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize)
{
	TRACE1("\nConfComASNotify nType[%d] received!\n", nType);
	switch(nType)
	{
		case COMPT_MSG_AS_ON_SHARING_STATE:		//停止共享
		{
			//共享状态
			CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
			if(NULL != pDemoDlg)
			{
				if (NULL != pDemoDlg->m_pDataConfDlg)
				{
					::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_STATE_NOTIFY,(WPARAM)nValue1,(LPARAM)nValue2);
				}
			}
			pDemoDlg = NULL;
			break;
		}
		case COMPT_MSG_AS_ON_SHARING_SESSION:		//共享通道通知
		{
			TC_Conf_User_Record *pRecord = (TC_Conf_User_Record*)pVoid;
			if ( NULL != pRecord )
			{
				//共享拥有者通知
				CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
				if(NULL != pDemoDlg)
				{
					if (NULL != pDemoDlg->m_pDataConfDlg)
					{
						//if ( 1 == nValue1 && 1 == nValue2 )
						//{
							::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_OWNER_NOTIFY,nValue1,(LPARAM)pRecord->user_alt_id);
						//}
					}
					pDemoDlg = NULL;
				}
				pRecord = NULL;
			}
			break;
		}
		case COMPT_MSG_AS_ON_SCREEN_DATA:
		{
			//共享屏幕数据刷新
			TC_AS_SCREENDATA *pData = (TC_AS_SCREENDATA*)pVoid;
			if ( NULL != pData )
			{
				TC_AS_SCREENDATA *pNewData = new TC_AS_SCREENDATA;
				if ( NULL != pNewData )
				{
					memcpy(pNewData,pData,sizeof(TC_AS_SCREENDATA));
					CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
					if(NULL != pDemoDlg)
					{
						if (NULL != pDemoDlg->m_pDataConfDlg)
						{
							::SendMessage(pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_SCREENDATA_NOTIFY,NULL,(LPARAM)pNewData);
						}
						pDemoDlg = NULL;
					}
					delete pNewData;
					pNewData = NULL;
				}
				pData = NULL;
			}
			break;
		}
		case COMPT_MSG_AS_ON_CHANNEL:
			{
				TUP_UINT uiValue1 = nValue1;
				TUP_ULONG ulValue2 = nValue2;
				TUP_ULONG uadd =*(TUP_ULONG*)pVoid;
				CeSDK_TUP_PC_CONF_DemoDlg *pDemoDlg = (CeSDK_TUP_PC_CONF_DemoDlg *)theApp.m_pMainWnd;
				if ( NULL != pDemoDlg )
				{
					if ( NULL != pDemoDlg->m_pDataConfDlg )
					{
						//::SendMessage( pDemoDlg->m_pDataConfDlg->GetSafeHwnd(),WM_DATACONF_AS_ON_CHANNEL, nValue1,nValue2);
					}
					pDemoDlg = NULL;
				}
				int a;
				a = 0;
				//TC_AS_SCREENDATA *pData = (TC_AS_SCREENDATA*)pVoid;
				break;
			}
		default:
			{
				break;
			}
	}
}