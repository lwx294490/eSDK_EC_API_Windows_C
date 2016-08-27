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
#include "call_interface.h"
#include "call_advanced_interface.h"

#define WM_CAll_INCMING		(WM_USER+1000)			//来电
#define WM_CAll_RING		(WM_USER+1001)			//振铃
#define WM_CAll_CONNECTED	(WM_USER+1002)			//接听来电
#define WM_CAll_ENDED		(WM_USER+1003)			//结束呼叫
#define WM_KICK_USER		(WM_USER+1004)			//被踢下线
#define WM_LOGIN_RESULT		(WM_USER+1005)			//注册成功

class NotifyCallBack
{
private:
	NotifyCallBack(void);
	~NotifyCallBack(void);
public:
	static TUP_VOID CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody);
};


