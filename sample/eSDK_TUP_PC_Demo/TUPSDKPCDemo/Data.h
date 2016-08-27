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

#include "call_interface.h"
#include "call_advanced_interface.h"
#include "offlinefile_def.h"
#include "offlinefile_interface.h"
#include "tup_im_baseapi.h"
#include "tup_im_extendapi.h"
#include "tup_im_util.h"
#include "tup_conf_baseapi.h"
#include "tup_conf_otherapi.h"
#include "tup_conf_extendapi.h"
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

#define WM_HEARTBEAT_NOTIFY	(WM_USER+999)			//心跳
#define WM_MENU_SEND_IM		(WM_USER+1000)			//发送即时消息
#define WM_SHOW_DETAIL		(WM_USER+1001)			//显示联系人详情
#define WM_CLOSE_IM_WND		(WM_USER+1002)			//关闭即时消息对话框
#define WM_RECV_IM			(WM_USER+1003)			//关闭即时消息对话框
#define WM_HANGUP			(WM_USER+1004)			//挂断电话
#define WM_UPDATE_CONTACT	(WM_USER+1005)			//刷新联系人
#define WM_CAll_CONNECTED	(WM_USER+1006)			//通话建立
#define WM_CAll_END			(WM_USER+1007)			//通话结束
#define WM_CAll_INCMING		(WM_USER+1008)			//来电
#define WM_CAll_HOLD		(WM_USER+1009)			//保持
#define WM_CAll_UNHOLD		(WM_USER+1010)			//取消保持
#define WM_CALL_MIC_MUTE	(WM_USER+1011)			//麦克风静音
#define WM_CALL_MIC_UNMUTE	(WM_USER+1012)			//取消麦克风静音
#define WM_CALL_SPK_MUTE	(WM_USER+1013)			//扬声器静音
#define WM_CALL_SPK_UNMUTE	(WM_USER+1014)			//取消扬声器静音
#define WM_CALL_START_REC	(WM_USER+1015)			//开始录音
#define WM_CALL_END_REC		(WM_USER+1016)			//结束录音
#define WM_CALL_BLIND_TRAN	(WM_USER+1017)			//呼叫转移-盲转
#define WM_CALL_SHOW_WND	(WM_USER+1018)			//显示或者隐藏视频窗口
#define WM_CLOSE_SET_DLG	(WM_USER+1019)			//关闭设置对话框
#define WM_CLOSE_ENT_DLG	(WM_USER+1020)			//关闭企业通讯录对话框
#define WM_CLOSE_DETAIL_DLG	(WM_USER+1021)			//关闭详情对话框
#define WM_CAll_ADD_VIDEO	(WM_USER+1022)			//收到语音转视频请求
#define WM_CAll_DEL_VIDEO	(WM_USER+1023)			//收到视频转语音请求
#define WM_NET_LEVEL		(WM_USER+1024)			//网络质量信息通告
#define WM_NET_INFO			(WM_USER+1025)			//网络统计信息
#define WM_CAll_RGE_RESLUT	(WM_USER+1026)			//注册结果
#define WM_CALL_BETRANSFER_CONF	     (WM_USER+1027)		   //通话被转语音会议
#define WM_CALL_HOLE_RESULT	         (WM_USER+1028)		       //呼叫保持成功
#define WM_CALL_UNHOLE_RESULT	     (WM_USER+1029)		   //取消呼叫保持成功
#define WM_CALL_BLIND_RESULT	     (WM_USER+1030)		   //呼叫转移-盲转结果
#define WM_CALL_OUTGOING	         (WM_USER+1031)		   //呼出事件////
#define WM_CALL_INFOCHANGE	         (WM_USER+1032)		   //呼叫信息变化////


///语音会议部分
#define WM_CONF_CREATE_RET	(WM_USER+1050)			//创建会议成功
#define WM_CONF_ADD_MEM_SUC	(WM_USER+1051)			//增加成员成功
#define WM_CONF_ADD_MEM_FAIL (WM_USER+1052)			//增加成员失败
#define WM_CONF_MEM_SPK		(WM_USER+1053)			//成员发言
#define WM_CONF_MEM_QUIT	(WM_USER+1054)			//成员发言
#define WM_CONF_INCMING		(WM_USER+1055)			//会议来电
#define WM_CONF_CONNECTED	(WM_USER+1056)			//进入会议
#define WM_CONF_SUBJECT		(WM_USER+1057)			//会议主题变更
#define WM_CLOSE_CONF_WND	(WM_USER+1058)			//关闭会议对话框
#define WM_CONF_REFESH_SIGNLE	(WM_USER+1059)		//刷新会议单个成员
#define WM_CONF_REFESH_LIST	(WM_USER+1060)			//刷新会议所有成员
#define WM_CONF_END			(WM_USER+1061)          //语音会议结束


////离线文件相关/////
#define WM_SHOW_DOWNLOADIMAGE_IM		(WM_USER+1046) //图片下载完毕通知
#define WM_SEND_IMAGEINFO_IM			(WM_USER+1047) //发送图片信息
#define WM_RECV_OFFLINE_IM				(WM_USER+1048) // 离线消息

//固定群组
#define WM_FIXGROUP_IDENTIFY_NOTIFY            (WM_USER+1101)   //固定群组认证通知
#define WM_CONFIRM_JOINFIXEDGROUP_NOTIFY       (WM_USER+1102)   //审批加入固定群申请
#define WM_MENU_GROUP_CHAT                     (WM_USER+1103)   //发送群组即时消息
#define WM_FIXGROUP_DELETE_NOTIFY              (WM_USER+1104)   //删除群组成员通知
#define WM_DISMISS_FIXEDGROUP_NOTIFY           (WM_USER+1105)   //固定群组解散通知
#define WM_GROUP_INVITEDLG_CLOSE               (WM_USER+1106)   //关闭群组通知对话框
#define WM_GROUP_NOTIFY		                   (WM_USER+1107)	//群组通知
#define WM_GROUP_INF_CHANGE	                   (WM_USER+1108)	//群组信息变更
#define WM_GROUP_MEM_ADD	                   (WM_USER+1109)	//群组成员增加
#define WM_GROUP_MEM_DEL	                   (WM_USER+1110)	//群组通知
#define WM_GROUP_MEM_OWNER 	                   (WM_USER+1111)	//群组管理员变更



//数据会议相关
#define WM_DATACONF_CREAT	             (WM_USER+1999)			//创建数据会议成功
#define WM_DATACONF_JOINSUCCESS          (WM_USER+2000)			//加入数据会议成功
#define WM_DATACONF_LOADCOM_SUCCESS      (WM_USER+2001)		    //组件加载议成功
#define WM_DATACONF_USER_ADD	         (WM_USER+2002)			//数据会议成员加入
#define WM_DATACONF_USER_DEL	         (WM_USER+2003)			//数据会议成员离开
#define WM_DATACONF_AS_OWNER_NOTIFY      (WM_USER+2005)		    //共享拥有者通知
#define WM_DATACONF_AS_SCREENDATA_NOTIFY (WM_USER+2006)	        //共享数据通知
#define WM_DATACONF_AS_STATE_NOTIFY	     (WM_USER+2007)	        //共享状态通知
#define WM_DATACONF_UPDATE_PRESENTINFO   (WM_USER+2008)         //更新本地主讲人信息
#define WM_DATACONF_UPDATE_CHAIRMAININFO (WM_USER+2009)         //更新本地主持人信息
#define WM_DATACONF_UPDATE_MUTE          (WM_USER+2010)         //更新静音（取消静音）通知
#define WM_DATACONF_END                  (WM_USER+2011)         //会议结束通知/////
#define WM_IM_KICKOUT_NOTIFY			 (WM_USER+2012)         //用户被踢下线通知/////
#define WM_DATACONF_DOCUMENT_WND	     (WM_USER+2013)	        //显示或者隐藏视频窗口
#define WM_DATACONF_LAYOUT_CHANGE	     (WM_USER+2014)	        //共享拥有者变换界面////
#define WM_CLOSE_DATACONF_WND		     (WM_USER+2015)	        //关闭多媒体会话框

//视频相关
#define WM_DATACONF_ADD_VIDEO	         (WM_USER+2100)	       //增加本地视频
#define WM_DATACONF_DEL_VIDEO	         (WM_USER+2101)	       //减少本地视频
//共享白板相关
#define WM_DATACONF_WB_DOC_NEW           (WM_USER+2130)	       //新建白板文档 
#define WM_DATACONF_WB_PAG_NEW           (WM_USER+2131)	       //新建白板页
#define WM_DATACONF_WB_DRAW              (WM_USER+2132)	       //刷新界面数据
#define WM_DATACONF_WB_PAGE_IND          (WM_USER+2133)	       //同步本地页面
#define WM_DATACONF_WB_REFRESH_INFO      (WM_USER+2134)	       //更新本地文档信息
#define WM_DATACONF_WB_DOC_DEL           (WM_USER+2135)	       //删除白板文档
#define WM_DATACONF_WB_PAG_DEL           (WM_USER+2136)	       //删除白板页
#define WM_DATACONF_WB_PAG_CPY           (WM_USER+2137)	       //拷贝当前页


//Menu ID
//Private Group
#define ID_PRIGROUP_MODIFY_MENU         32100
#define ID_PRIGROUP_DEL_MENU            32101
#define ID_PRIGROUP_ADD_MENU            32102
#define ID_PRIGROUP_ADD_CONTACT_MENU    32103
#define ID_PRIGROUP_ADD_UC_CONTACT_MENU 32104

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

//CONF
#define ID_CONF_DEL_MEM_MENU        33100
#define ID_CONF_RECALL_MEM_MENU     33101
#define ID_CONF_MUTE_MEM_MENU		33102
#define ID_CONF_UNMUTE_MEM_MENU		33103

//DATACONF
#define ID_DATACONF_DEL_MEM_MENU               34100    //移除数据会议成员////
#define ID_DATACONF_RECALL_MEM_MENU            34101      
#define ID_DATACONF_SETPRESENT_MEM_MENU        34102
#define ID_DATACONF_INVITEDTOSHARE_MEM_MENU    34103

//GROUP
#define ID_GROUP_RELEASE_MEM_MENU		34500		//解散群组
#define ID_GROUP_ADD_MEMBER_MENU		34501		//添加成员
#define ID_GROUP_EXIT_MENU				34502		//退出群组
#define ID_GROUP_ADD_MENU				34503     //添加群组



//通讯录
typedef std::map<TUP_INT64,IM_S_USERGROUPINFO> MAP_GROUP;
extern MAP_GROUP g_mapGroup;
typedef std::multimap<TUP_INT64,TUP_INT64> MAP_USER_GROUP;
extern MAP_USER_GROUP g_mapUserGroup;
typedef std::map<TUP_INT64,IM_S_CONTACTNFO> MAP_CONTACT;
extern MAP_CONTACT g_mapContact;
typedef std::map<TUP_INT64,IM_S_USERINFO> MAP_USER;
extern MAP_USER g_mapUser;
typedef std::map<TUP_INT64,IM_S_IMGROUPINFO> MAP_IMGROUP;
extern MAP_IMGROUP g_mapImGroup;

//媒体设置
typedef std::map<int,std::string> MAP_DEVICE;
extern MAP_DEVICE g_mapInDevice;
extern MAP_DEVICE g_mapOutDevice;
extern MAP_DEVICE g_mapVideoDevice;
extern int g_iIndeviceIndex;
extern int g_iOutdeviceIndex;
extern int g_iVideodeviceIndex;
extern int g_iMicLevel;
extern int g_iSpeakerLevel;

//个人信息
extern std::string g_Account;
extern std::string g_SipAccount;
extern std::string g_DataConfAddr;
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