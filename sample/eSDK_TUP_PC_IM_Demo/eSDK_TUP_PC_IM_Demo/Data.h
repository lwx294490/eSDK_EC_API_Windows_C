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

#ifndef DATA_H
#define DATA_H

#include "tup_im_baseapi.h"
#include "tup_im_extendapi.h"
#include "tup_im_util.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

enum GROUPLIST_COLUMNID
{
	COL_MEM_Compere, 
	COL_MEM_Status, 
	COL_MEM_Name, 
	COL_MEM_ACCOUNT,
	COL_MEM_CALLNO,
	COL_MEM_CALLSTATE,
	COL_MEM_SPK,
	COL_MEM_MUTE
};

enum STAFFLIST_COLUMNID
{
	COL_Status, 
	COL_Name, 
	COL_ACCOUNT, 
	COL_DptName,
	COL_Email,
	COL_BINDNO1,
	COL_BINDNO2,
	COL_MOBILE,
	COL_OFFICENUM,
	COL_OFFICENUM2,
	COL_HOMENUM,
	COL_OTHERNUM,
	COL_OTHERNUM2,
	COL_FAX,
	COL_TITLE
};

#define WM_MENU_SEND_IM		(WM_USER+1000)			//发送个人即时消息
#define WM_SHOW_DETAIL		(WM_USER+1001)			//显示联系人详情
#define WM_CLOSE_IM_WND		(WM_USER+1002)			//关闭即时消息对话框
#define WM_RECV_IM			(WM_USER+1003)			//关闭即时消息对话框
#define WM_UPDATE_CONTACT	(WM_USER+1005)			//刷新联系人
#define WM_CLOSE_ENT_DLG	(WM_USER+1020)			//关闭企业通讯录对话框
#define WM_NET_LEVEL		(WM_USER+1032)			//网络质量信息通告
#define WM_NET_INFO			(WM_USER+1033)			//网络统计信息
#define WM_GROUP_NOTIFY		(WM_USER+1034)			//群组通知
#define WM_GROUP_INF_CHANGE	(WM_USER+1035)			//群组信息变更
#define WM_GROUP_MEM_ADD	(WM_USER+1036)			//群组成员增加
#define WM_GROUP_MEM_DEL	(WM_USER+1037)			//群组通知
#define WM_GROUP_MEM_OWNER 	(WM_USER+1038)			//群组管理员变更
#define WM_MENU_GROUP_SENDMESSAGE 	(WM_USER+1039)			//发送群组即时消息

//test
#define WM_DISPATCH_MESSAGE_IM			(WM_USER+1050)			//客户端程序调用eSDK UC的“取消消息回调”接口tup_im_setdispatchmessage，使eSDK UC不再向客户端程序上报消息
#define WM_KICK_USER					(WM_USER+1051)

//Menu ID
//Private Group
#define ID_PRIGROUP_MODIFY_MENU         32100
#define ID_PRIGROUP_DEL_MENU            32101
#define ID_PRIGROUP_ADD_MENU            32102
#define ID_PRIGROUP_ADD_CONTACT_MENU    32103
#define ID_PRIGROUP_ADD_UC_CONTACT_MENU 32104
#define ID_PRIGROUP_SENDMESSAGE			32105

#define ID_MAIN_SETTING_MENU			32201
#define ID_MAIN_PORTAL_MENU				32202
#define ID_MAIN_HELP_MENU				32203
#define ID_MAIN_LOGOUT_MENU				32204
#define ID_MAIN_EXIT_MENU				32205

//Private Contact
#define ID_PRIGROUP_DEL_CONTACT_MENU    32301
#define ID_PRIGROUP_MODIFY_CONTACT_MENU 32302
#define ID_PRIGROUP_CONTACT_DETAIL_MENU 32303
#define ID_PRIGROUP_INSTANTMSG_MENU     32304
#define ID_PRIGROUP_AUDIOCONF_MENU      32305

//Move Group List
#define ID_PRIGROUP_CONTACT_MOVE_MENU_START 32320
#define ID_PRIGROUP_CONTACT_MOVE_MENU_END	32399

//EntAddr Menu
#define ID_ENTADDR_ADD_CONTACT			32400
#define ID_ENTADDR_GROUP_ADD_MENU_START 32500
#define ID_ENTADDR_GROUP_ADD_MENU_END	32700

//IM 
#define ID_IM_GROUP_DEL_MEM_MENU        33100
#define ID_IM_GROUP_RECALL_MEM_MENU     33101


//通讯录
typedef std::map<TUP_INT64,IM_S_USERGROUPINFO> MAP_GROUP;
extern MAP_GROUP g_mapGroup;
typedef std::multimap<TUP_INT64,TUP_INT64> MAP_USER_GROUP;
extern MAP_USER_GROUP g_mapUserGroup;
typedef std::map<TUP_INT64,IM_S_CONTACTNFO> MAP_CONTACT;
extern MAP_CONTACT g_mapContact;
typedef std::map<TUP_INT64,IM_S_USERINFO> MAP_USER;
extern MAP_USER g_mapUser;


//个人信息
extern std::string g_Account;
extern std::string g_SipAccount;
extern std::string g_Name;
extern std::string g_BindNO;
extern TUP_INT64 g_UserID;

typedef struct tagCall_Member
{
	TUP_CHAR name[IM_D_MAX_NAME_LENGTH];				/**< 用户名 */
	TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];			/**< 成员账号 */ 
	TUP_CHAR CallNo[IM_D_MAX_PHONE_LENGTH];			/**< 呼叫的号码 */
}CALL_MEMBER;
typedef std::map<std::string,CALL_MEMBER> MAP_SELECT_USER;



//call

#define USER_AGENT				"Huawei SoftCoPCA"

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}
#define SAFE_DELETE_ARRAY(pPoint) 	if(NULL != pPoint)\
{\
	delete[] pPoint;\
	pPoint = NULL;\
}

#define CHECK_POINTER(pPoint) if(NULL == pPoint)\
{\
	return;\
}

#define CHECK_POINTER_RETURN(pPoint,ret) if(NULL == pPoint)\
{\
	return ret;\
}

class map_value_finder
{
public:
	map_value_finder(const int &cmp_int):m_s_cmp_int(cmp_int){}
	bool operator ()(const std::map<int, int>::value_type &pair)
	{
		return pair.second == m_s_cmp_int;
	}
private:
	const int m_s_cmp_int;                    
};

//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 begin
class CUserQueryHelper
{
public:
	bool GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack
		, const TUP_INT8 acTelNum[]
	, IM_S_USERINFO& userInfo
		);

	bool GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo);
};
//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 end
#endif