#eSDK TUP API#
华为eSDK提供的*eSDK TUP API*可以帮助开发者快速具备消息，呼叫以及多媒体会议等集成开发能力，具体功能如下：

- 联系人管理：包含联系人信息及其状态的查询，发布以及管理功能。
- 消息：包含点对点消息，群组消息以及公告等。
- VoIP业务：包含呼叫、接听、拒绝接听、挂机、保持、通话中二次拨号、静音、切换语音路由、升级为视频呼叫
- 群组会议：包含群组会议管理，成员管理以及群组成员权限管理等功能。
- 多媒体会议：包含桌面协同，视频会议，文档共享会议等多媒体会议，同时还包含投票，涂鸦等附件功能。
##版本信息##
V1.5.60

##开发环境##
- 操作系统： Windows7专业版
- Microsoft Visual Studio：Visual Studio 2010专业版

##文档指引##
- src文件夹：包含TUP API的二进制文件
- sample文件夹：包含eSDK提供的场景话展示样例
- doc：包含eSDK提供的开发指引文档

##入门指引##
在开始阅读本章节，请至[远程实验室](http://developer.huawei.com/cn/ict/remotelab)企业云通信（EC）的调测环境，以方便后续操作。
###发送IM消息###

*点对点发送文本消息*

TUP_CHAR origin[] = "zhangkui";	
		
TUP_CHAR target[] = "weipenghui";

TUP_CHAR groupID[] = "";
		
TUP_CHAR content[] = "hello";
	
TUP_CHAR displayname[] = "";
	
SendImArg.chatType = IM_E_IM_CHAT_TYPE_SINGLE;

SendImArg.regionID = 0;

SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;

SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;

SendImArg.utcStamp = -1;

strcpy_s(arg.origin, sizeof(arg.origin), origin);

strcpy_s(arg.target, sizeof(arg.target), target);

strcpy_s(arg.groupID, sizeof(arg.groupID), groupID);

strcpy_s(arg.content, sizeof(arg.content),content);

strcpy_s(arg.displayname, sizeof(arg.displayname),displayname);

TUP_RESULT Ret =  tup_im_sendim(&arg);

bool rslt = (Ret == TUP_SUCCESS) ? true : false;

*具体用例参考doc中的《开发指南》*

###点对点呼叫##

*//发起呼叫请求 *

TUP_UINT32 callRequestId; 

TUP_RESULT tRet = tup_call_start_call(&callRequestId, CALL_E_CALL_TYPE_IPAUDIO, m_strCalleerSipNumber.c_str());

*详细介绍请参考doc中的《开发指南》*
	 			
### 获取帮助 ###

在开发过程中，您有任何问题均可以至[DevCenter](https://devcenter.huawei.com)中提单跟踪。也可以在[华为开发者社区](http://bbs.csdn.net/forums/hwucdeveloper)中查找或提问。另外，华为技术支持热线电话：400-822-9999（转二次开发）




