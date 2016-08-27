#pragma once
#include "tup_im_baseapi.h"
#include "call_interface.h"
#include "call_advanced_interface.h"
#include "tup_conf_baseapi.h"
#include "tup_conf_otherapi.h"
#include "tup_conf_extendapi.h"

#define WM_MEET_CREATE_SUCCESS			(WM_USER+1000)			//创建会议成功
#define WM_MEET_MANAGER_CONNECTED		(WM_USER+1001)			//主席加入会议成功
#define WM_MEET_INVITE					(WM_USER+1002)			//会议邀请
#define WM_MEET_MEMBER_JOINED_SUCCESS	(WM_USER+1003)			//成功加入一名会议参加者
#define WM_MEET_MEMBER_REFRESH			(WM_USER+1004)			//刷新会议列表
#define WM_MEET_MEM_SPEAK				(WM_USER+1005)			//显示发言人
#define WM_MEET_ENDED					(WM_USER+1006)			//结束会议
#define WM_DATACONF_CREAT				(WM_USER+1007)			//结束会议
#define WM_DATACONF_JOINSUCCESS			(WM_USER+1008)			//成功加入数据会议
#define WM_DATACONF_LOADCOM_SUCCESS		(WM_USER+1009)			//组件加载议成功
#define WM_USER_KICKOUT			(WM_USER+1010)		 // 用户被踢出
#define WM_DATACONF_AS_STATE_NOTIFY	     (WM_USER+1011)	        //共享状态通知
#define WM_DATACONF_AS_OWNER_NOTIFY      (WM_USER+1012)		    //共享拥有者通知
#define WM_DATACONF_AS_SCREENDATA_NOTIFY (WM_USER+1013)	        //共享数据通知
#define WM_DATACONF_USER_ADD	         (WM_USER+1014)			//数据会议成员加入
#define WM_DATACONF_USER_DEL	         (WM_USER+1015)			//数据会议成员离开
#define WM_DATACONF_UPDATE_PRESENTINFO   (WM_USER+1016)         //更新本地主讲人信息
#define WM_DATACONF_UPDATE_CHAIRMAININFO (WM_USER+1017)         //更新本地主持人信息
#define WM_DATACONF_END                  (WM_USER+1018)         //会议结束通知/////

class NotifyCallBack
{
private:
	NotifyCallBack(void);
	~NotifyCallBack(void);
public:
	static TUP_BOOL IMNotify(IM_E_EVENT_ID eventID, void *body);
	static TUP_VOID CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody);
	static void APIENTRY ConfComASNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize);
	static TUP_VOID TUP_STDCALL ConfNotify(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);
};


