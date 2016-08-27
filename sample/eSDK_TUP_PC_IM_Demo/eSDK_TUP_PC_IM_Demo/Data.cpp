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

#include "stdafx.h"
#include "Data.h"

MAP_GROUP g_mapGroup;
MAP_USER_GROUP g_mapUserGroup;
MAP_CONTACT g_mapContact;
MAP_USER g_mapUser;

std::string g_Account;
std::string g_SipAccount;
std::string g_Name;
std::string g_BindNO;
TUP_INT64 g_UserID;


bool CUserQueryHelper::GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack
								 , const TUP_INT8 acTelNum[]
, IM_S_USERINFO& userInfo)
{
	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (strcmp(curUserInfo.bindNO, acTelNum) == 0)
		{
			userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}

	return bRet;
}

bool CUserQueryHelper::GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	memset(&arg,0,sizeof(IM_S_QUERY_USERINFO_ARG));
	memset(&ack,0,sizeof(IM_S_QUERY_USERINFO_ACK));
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, acTelNum);
	arg.type = IM_E_IMUSERQUERYTYPE_BY_BINDNO;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		return false;
	}

	IM_S_USERINFO userQueryAck;
	memset(&userQueryAck,0,sizeof(IM_S_USERINFO));
	if(!GetUserInfoFromList(ack, acTelNum, userQueryAck))
	{
		return false;
	}
	memset(&userInfo,0,sizeof(IM_S_USERINFO));
	memcpy(&userInfo,&userQueryAck,sizeof(IM_S_USERINFO));
	////释放IM_S_QUERY_USERINFO_ACK结构体中的TUPLIST内存/////
	tup_im_release_tup_list(ack.userList);
	return true;
}





