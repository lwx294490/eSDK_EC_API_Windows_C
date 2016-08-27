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

#pragma once
#include "tup_im_baseapi.h"
#include "tup_im_extendapi.h"
#include "tup_im_util.h"
#include "call_interface.h"
#include "call_advanced_interface.h"

#define WM_MEET_CREATE_SUCCESS			(WM_USER+1000)			//创建会议成功
#define WM_MEET_MANAGER_CONNECTED		(WM_USER+1001)			//主席加入会议成功
#define WM_MEET_INVITE					(WM_USER+1002)			//会议邀请
#define WM_MEET_MEMBER_JOINED_SUCCESS	(WM_USER+1003)			//成功加入一名会议参加者
#define WM_MEET_MEMBER_REFRESH			(WM_USER+1004)			//刷新会议列表
#define WM_MEET_MEM_SPEAK				(WM_USER+1005)			//显示发言人
#define WM_MEET_ENDED					(WM_USER+1006)			//结束会议
#define WM_KICK_USER					(WM_USER+1007)			//被踢下线


class NotifyCallBack
{
private:
	NotifyCallBack(void);
	~NotifyCallBack(void);
public:
	static TUP_BOOL IMNotify(IM_E_EVENT_ID eventID, void *body);
	static TUP_VOID CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody);
};


