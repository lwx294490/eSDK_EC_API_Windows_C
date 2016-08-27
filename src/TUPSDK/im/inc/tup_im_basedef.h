/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM子系统基础接口结构体定义头文件。 \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_BASEDEF_H_
#define _TUP_IM_BASEDEF_H_

#include "tup_def.h"
#include "tup_im_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

//--------------------------------------------------------------长度定义 begin--------------------------------------------------------------

#define IM_D_GENEAL_LENGTH    (32)                              /**< 默认长度 */

#define IM_D_URL_LENGTH    (2048)                               /**< URL最大长度 */

#define IM_D_ICON_LENGTH    (1024)                              /**< 图标长度 */

#define IM_D_MAX_ACCOUNT_LENGTH (32)                            /**< 帐号长度 */

#define IM_D_MAX_NAME_LENGTH (512)                              /**< 姓名长度 */

#define IM_D_MAX_DEPTNAME_LENGTH (1024)                         /**< 部门名长度 */

#define IM_D_MAX_PASSWORD_LENGTH (512)                          /**< 密码长度 */

#define IM_D_MAX_VERSION_LENGTH (100)                           /**< 版本号长度 */

#define IM_D_MAX_TIMESTAMP_LENGTH (15)                          /**< 时间戳长度 */

#define IM_D_MAX_PHONE_LENGTH (256)                             /**< 号码长度 */

#define IM_D_MAX_BIRTHDAY_LENGTH (64)                           /**< 生日长度 */

#define IM_D_MAX_DESC_LENGTH (1024)                             /**< 描述文字长度 */

#define IM_D_MAX_STATUS_DESCLEN (50)                            /**< 状态描述长度 */

#define IM_D_IP_LENGTH  (1024)                                  /**< IP地址长度 */  

#define IM_D_AGE_LENGTH  (8)                                    /**< 年龄长度 */

#define IM_D_GROUPID_LENGTH  (64)                               /**< 群ID长度 */

#define IM_D_MAX_MESSAGE_LENGTH (1024*10)                       /**< 即时消息文字长度 */

#define IM_D_MAX_PROGID_LENGTH (1024)                           /**< 插件PROGID */

#define IM_D_MAX_PLUGINPARAM_LENGTH (1024)                      /**< 插件参数长度 */

#define IM_D_MAX_PLUGINURL_LENGTH (1024)                        /**< 插件服务URL长度 */

#define IM_D_LOGIN_TOKEN_LENGTH (1024)                          /**< token 长度 */

#define IM_D_MAX_PATH_LENGTH (1024)                             /**< 路径长度 */

#define IM_D_MAX_CHAR_LENGTH (1024*10)                          /**< 字符串最长 长度 */

//--------------------------------------------------------------长度定义 end--------------------------------------------------------------

//--------------------------------------------------------------枚举 begin--------------------------------------------------------------
/**
 *  回调消息表
 *    注释中的NOTIFY是回调消息的消息结构体
 */
typedef enum tagIM_E_EVENT_ID
{
    IM_E_EVENT_IM_ORIGIN    = -1,                               /**< 初始化 */
/*******************************************************************登录与注销***************************************************************************************/
    IM_E_EVENT_IM_HEARTBEAT_NOTIFY,                             /**< 服务器返回心跳响应 */
    IM_E_EVENT_IM_SYSURLRET_NOTIFY,                             /**< 请求获取系统URL消息响应    消息结构体:IM_S_SYSURLS_NOTIFY */
    IM_E_EVENT_IM_LOGOUT_NOTIFY,                                /**< 用户退出                    消息结构体:IM_S_LOGOUT_NOTIFY */
    IM_E_EVENT_IM_KICKOUT_NOTIFY,                               /**< 用户被踢通知                消息结构体:IM_S_KICKOUT_NOTIFY */
    IM_E_EVENT_IM_MULTIDEVICE_NOTIFY,                           /**< 用户多终端登录/退出通知    消息结构体:IM_S_MULTIDEVICE_NOTIFY */
    IM_E_EVENT_IM_GENERAL_NOTIFY,                               /**< 客户端与服务器或其他客户端通信的会话通知            消息结构体:IM_S_GENERAL_NOTIFY */

/*******************************************************************联系人与好友*************************************************************************************/
    IM_E_EVENT_IM_ADDFRIEND_NOTIFY,                             /**< 对方添加自己好友成功通知    消息结构体:IM_S_ADDFRIEND_NOTIFY */
    IM_E_EVENT_IM_USERSTATUS_NOTIFY,                            /**< 好友状态变化通知            消息结构体:IM_S_USERSTATUS_NOTIFY */
    IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY,                        /**< 好友信息变化通知            消息结构体:IM_S_USERINFOCHANGE_LIST_NOTIFY;注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_GETIMGROUPDETAIL,                             /**< 获取IM群组详情响应消息        消息结构体:IM_S_GETIMGROUPDETAIL_NOTIFY （已废弃，不会使用）*/

/*******************************************************************固定群组*****************************************************************************************/
    IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY,           /**< 群成员收到管理员审批加入固定群通知的响应    消息结构体:IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY,                        /**< 固定群添加成员通知                            消息结构体:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY,                        /**< 群组中删除成员通知                            消息结构体:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_INFOCHG_NOTIFY,                       /**< 固定群信息修改通知                            消息结构体:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_OWNERCHG_NOTIFY,                      /**< 群组管理员变更通知                            消息结构体:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY,            /**< 用户收到管理员邀请通知                        消息结构体:IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY */
    IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY,                /**< 管理员收到用户申请加入群组通知                消息结构体:IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_WASADDEDTOGROUP_NOTIFY,               /**< 被添加到固定群通知                            消息结构体:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_DISMISS_NOTIFY,                       /**< 固定群解散通知                                消息结构体:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_OWNER_INVITE_RESULT_NOTIFY,           /**< 管理员收到用户对邀请加入固定群审批结果        消息结构体:IM_S_IMGROUP_OWNER_INVITE_RESULT_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_KICKOUT_NOTIFY,                       /**< 用户收到被管理员提出固定群通知                消息结构体:IM_S_IMGROUP_KICKOUT_NOTIFY*/
    IM_E_EVENT_FIXEDGROUP_LEAVE_RESULT_NOTIFY,                  /**< 用户主动离开固定群通知                        消息结构体:IM_S_IMGROUP_LEAVE_RESULT_NOTIFY*/

/*******************************************************************讨论组*******************************************************************************************/
    IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY,        /**< 讨论组成员列表添加成员变更消息        消息结构体:IM_S_DISCUSSGROUP_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY,        /**< 讨论组成员列表删除成员变更消息        消息结构体:IM_S_DISCUSSGROUP_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY,               /**< 讨论组信息更新                        消息结构体:IM_S_DISCUSSGROUP_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY,          /**< 被添加到讨论组通知                    消息结构体:IM_S_DISCUSSGROUP_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY,              /**< 讨论组管理员变更                    消息结构体:IM_S_DISCUSSGROUP_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_DISCUSSGROUP_DISMISS_NOTIFY,                  /**< 讨论组解散通知                        消息结构体:IM_S_DISCUSSGROUP_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_DISCUSSGROUP_OP_NOTIFY,                       /**< 广播讨论组操作消息                    消息结构体:IM_S_SEND_DISGROUP_OPT_MSG, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */

/*******************************************************************文件传输****************************************************************************************/
    IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY,                      /**< 收到文件传输请求                    消息结构体:IM_S_P2PFILECHOOSE_NOTIFY */
    IM_E_EVENT_IM_FILEPROCESS_NOTIFY,                           /**< 文件传输进度通知                    消息结构体:IM_S_FILEPROCESS_NOTIFY */
    IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY,                   /**< 文件传输开始结果                    消息结构体:IM_S_P2PFILE_RESULT_NOTIFY */
    IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY,                   /**< 文件传输停止结果                    消息结构体:IM_S_P2PFILE_RESULT_NOTIFY */
    IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY,                          /**< 文件传输停止通知                    消息结构体:IM_S_P2PFILESTATISTIC_NOTIFY */

/*********************************************************************IM消息****************************************************************************v*************/
    IM_E_EVENT_IM_SENDIMINPUT_NOTIFY,                           /**< 收到其他用户输入状态消息        消息结构体:IM_S_SENDIMINPUT_NOTIFY */    
    IM_E_EVENT_IM_CODECHAT_NOTIFY,                              /**< 新即时消息通知                 消息结构体:IM_S_CODECHAT_NOTIFY */    
    IM_E_EVENT_IM_CHATLIST_NOTIFY,                              /**< 新即时消息批量通知(离线)         消息结构体:IM_S_CHATLIST_NOTIFY, 注意:需要调用tup_im_release_tup_list释放结构中的TUP_S_LIST* 内存 */
    IM_E_EVENT_IM_SYSTEMBULLETIN_NOTIFY,                        /**< 系统公告通知                    消息结构体:IM_S_SYSTEMBULLETIN_NOTIFY */
    IM_E_EVENT_IM_SMS_NOTIFY,                                   /**< 新短信通知                        消息结构体:IM_S_SENDSMS_NOTIFY */
    IM_E_EVENT_IM_UNDELIVER_NOTIFY,                             /**< 聊天消息未送达（如研发和非研）    消息结构体:IM_S_UNDELIVER_NOTIFY */
    IM_E_EVENT_IM_MSG_READ_NOTIFY,                              /**< 聊天消息已读通知（多端登录）		消息结构体:IM_S_MSG_READ_NOTIFY */
	IM_E_EVENT_IM_MSG_SENDACK_NOTIFY,							/**< 聊天消息发送结果通知				消息结构体:IM_S_SENDACK_NOTIFY */

/*********************************************************************群共享文件****************************************************************************v*************/
    IM_E_EVENT_IM_GROUPFILE_NOTIFY,                             /**< 群共享文件变更通知                消息结构体: IM_S_GROUPFILE_NOTIFY*/

}IM_E_EVENT_ID;




/**
 *  登录鉴权类型
 */
typedef enum tagIM_E_LOGIN_AUTHTYPE
{
    IM_E_LOGIN_AUTHTYPE_BYPASSWORD                          = 1,    /**< 密码鉴权 */
    IM_E_LOGIN_AUTHTYPE_BYFINGER                            = 2,    /**< 指纹鉴权 */
    IM_E_LOGIN_AUTHTYPE_BYTHIRDPARTY                        = 3     /**< 第三方鉴权 */
}IM_E_LOGIN_AUTHTYPE;


/**
 *  登录结果，大于0错误是服务器错误，小于0是客户端内部错误。 
 */
typedef enum tagIM_E_LOGIN_RESUL
{
    IM_E_LOGING_RESULT_TIMEOUT                              = -100,  /**< 消息超时 */
    IM_E_LOGING_RESULT_SERVERNOTALLOW                       = -2,    /**< 不允许登录该服务器 */
    IM_E_LOGING_RESULT_INTERNAL_ERROR                       = -1,    /**< 程序内部错误 */
    IM_E_LOGING_RESULT_SUCCESS                              = 0,     /**< 登录成功 */
    IM_E_LOGING_RESULT_FAILED                               = 1,     /**< 登录失败 */
    IM_E_LOGING_RESULT_PASSWORD_ERROR                       = 2,     /**< 密码错误 */
    IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST                    = 3,     /**< 帐号不存在 */
    IM_E_LOGING_RESULT_ALREADY_LOGIN                        = 4,     /**< 用户已登录 （登录依然成功，其他已经登录的终端提示被踢下线）*/          
    IM_E_LOGING_RESULT_ACCOUNT_LOCKED                       = 5,     /**< 帐号被锁定 */
    IM_E_LOGING_RESULT_NEED_NEW_VERSION                     = 6,     /**< 需要下载新版本才允许登录 */
    IM_E_LOGING_RESULT_NOT_ACTIVE                           = 7,     /**< 用户未激活 */
    IM_E_LOGING_RESULT_ACCOUNT_SUSPEND                      = 8,     /**< 用户账号被暂停使用 */
    IM_E_LOGING_RESULT_ACCOUNT_EXPIRE                       = 9,     /**< 用户账号过期 */
    IM_E_LOGING_RESULT_DECRYPT_FAILED                       = 10,    /**< 消息解密失败 */
    IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED                 = 11,    /**< 证书下载失败 */
    IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED                 = 12,    /**< 证书校验失败 */
    IM_E_LOGING_RESULT_DNS_ERROR                            = 13,    /**< 域名解析错误 */
    IM_E_LOGING_RESULT_SYSTEM_ERROR                         = 14,    /**< 系统错误 */
    IM_E_LOGING_RESULT_TICKET_EXPIRE                        = 15,    /**< 令牌过期（令牌所指第三方鉴权登录的ticket）*/
    IM_E_LOGING_RESULT_TICKET_NOT_EXIST                     = 16,    /**< 令牌不存在（令牌所指第三方鉴权登录的ticket） */
    IM_E_LOGING_RESULT_TICKET_SUSPEND                       = 17,    /**< 令牌已禁用 （令牌所指第三方鉴权登录的ticket）*/
    IM_E_LOGING_RESULT_TICKET_ERROR                         = 18,    /**< 令牌验证错误 （令牌所指第三方鉴权登录的ticket）*/
    IM_E_LOGING_RESULT_TICKET_FLUID_EXCEED                  = 19,    /**< 超过流量控制 */
    IM_E_LOGING_RESULT_TICKET_FLUID_ERROR                   = 20,    /**< 流量控制异常 */
    IM_E_LOGING_RESULT_TICKET_REDIRECT_ERROR                = 21     /**< 重定向异常 */
}IM_E_LOGIN_RESULT;

/**
 *  加密方式 
 */
typedef enum tagIM_E_LOGIN_ENCRYPT_TYPE
{
    IM_E_LOGIN_ENCRYPT_TYPE_NONE = 0,   /**< 不加密 */
    IM_E_LOGIN_ENCRYPT_TYPE_NORMAL = 1, /**< 二进制移位方式加密 */
    IM_E_LOGIN_ENCRYPT_TYPE_PKI = 2,    /**< PKI加密 */
    IM_E_LOGIN_ENCRYPT_TYPE_AES_ECB = 3,/**< PKI+AES加密(ECB) */
    IM_E_LOGIN_ENCRYPT_TYPE_AES_CBC = 4, /**< PKI+AES加密(CBC) */
} IM_E_LOGIN_ENCRYPT_TYPE;

/**
 *  性别类型
 */
typedef enum tagIM_E_GENDER_TYPE
{
    IM_E_GENDER_MALE                                        = 0,    /**< 男 */
    IM_E_GENDER_FEMAIL                                      = 1,    /**< 女*/
    IM_E_GENDER_UNKNOWN                                     = 2     /**< 未知 */
}IM_E_GENDER_TYPE;


/**
 *  加入群组验证方式
 */
typedef enum tagIM_E_IMGROUP_JOIN_AUTH_FLAG
{
    IM_E_IMGROUP_JOIN_AUTO                                  = 0,    /**< 自动加入 */
    IM_E_IMGROUP_JOIN_NEED_APPROVE                          = 1,    /**< 需要管理员审批 */
    IM_E_IMGROUP_JOIN_DENY                                  = 2     /**< 不允许加入 */
}IM_E_IMGROUP_JOIN_AUTH_FLAG;


/**
 *  群组消息显示类型
 */
typedef enum  tagIM_E_IMGROUP_MSGPOLICY_TYPE 
{
    IM_E_IMGROUP_NOSHOW_GROUPMSG_TIP                        = 0,    /**< 接收但是不提示群组消息*/
    IM_E_IMGROUP_SHOW_GROUPMSG_TIP                          = 1,    /**< 接收并提示群组消息*/
    IM_E_IMGROUP_SHOW_GROUPMSG_NOREAD                       = 2     /**< 接收并提示未读*/
}IM_E_IMGROUP_MSGPOLICY_TYPE; 
 

/**
 *  群组类型
 */
typedef enum tagIM_E_IMGROUP_TYPE
{
    IM_E_IMGROUP_FIXGROUP_TYPE                              = 0,    /**< 固定群 */
    IM_E_IMGROUP_DISCUSSIONGROUP_TYPE                       = 1     /**< 讨论组 */
}IM_E_IMGROUP_TYPE;


/**
 *  是否固化群组标记
 */
typedef enum tagIM_E_IMGROUP_ISFIXDISCUSS 
{
    IM_E_IMGROUP_NOTSAVETOLIST                              = 0,    /**< 解除固化群组 */
    IM_E_IMGROUP_SAVETOLIST                                 = 1,    /**< 固化群组 */
}IM_E_IMGROUP_ISFIXDISCUSS;

/**
 *  讨论组操作类型
 */
typedef enum tagIM_E_DISGROUP_OP_TYPE
{
    IM_E_DISGROUP_OP_TYPE_ADD                               = 0,    /**< 添加成员 */
    IM_E_DISGROUP_OP_TYPE_DEL                               = 1,    /**< 删除成员 */
}IM_E_DISGROUP_OP_TYPE;

/**
 *  用户在线状态
 */
typedef enum tagIM_E_USER_ONLINESTATUS
{
    IM_E_STATUS_INIT                                        = -1,   /**< 初始状态 */
    IM_E_STATUS_OFFLINE                                     = 0,    /**< 离线 */
    IM_E_STATUS_ONLINE                                      = 1,    /**< 在线 */
    IM_E_STATUS_HIDDEN                                      = 2,    /**< 隐身 */
    IM_E_STATUS_BUSY                                        = 3,    /**< 忙碌 */
    IM_E_STATUS_LEAVE                                       = 4,    /**< 离开 */
    IM_E_STATUS_DONTDISTURB                                 = 5     /**< 请勿打扰 */
}IM_E_USER_ONLINESTATUS;


/**
 *  客户端类型 */
typedef enum tagIM_E_CLIENT_TYPE 
{
    IM_E_CLIENT_TYPE_PC                                     = 0,    /**< PC终端 */
    IM_E_CLIENT_TYPE_MOBILE                                 = 1,    /**< 移动手机终端 */
    IM_E_CLIENT_TYPE_WEB                                    = 2,    /**< web客户端 */
    IM_E_CLIENT_TYPE_MOBLIEHD                               = 3     /**< 移动PC终端 */
}IM_E_CLIENT_TYPE;

/**
 *  客户端操作事件类型 */
typedef enum tagIM_E_CLIENT_OPT_TYPE 
{
    IM_E_CLIENT_OPT_LOGIN                                   = 1,    /**< 登录 */
    IM_E_CLIENT_OPT_LOGOUT                                  = 2,    /**< 注销 */
}IM_E_CLIENT_OPT_TYPE ;

/**
 *  IM消息发送处类型
 */
typedef enum tagIM_E_IM_CHAT_SOURCE_FLAG
{
    IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG                      = 0,    /**< IM聊天窗口 */
    IM_E_IM_CHAT_SOURCE_FLAG_MULTIMEETING                   = 1     /**< 数据会议聊天窗口 */
}IM_E_IM_CHAT_SOURCE_FLAG;

/**
 *  IM消息内容格式
 */
typedef enum tagIM_E_IM_CHAT_CONTENT_TYPE 
{
    IM_E_IM_CHAT_CONTENT_TYPE_TEXT                          = 0,    /**< 纯文本 */
    IM_E_IM_CHAT_CONTENT_TYPE_RICHTEXT                      = 1     /**< 富文本 */
}IM_E_IM_CHAT_CONTENT_TYPE;

/**
 *  IM聊天输入状态
 */
typedef enum tagIM_E_IM_CHAT_STATUS
{
    IM_E_IM_CHAT_STATUS_CHATTING                            = 0,    /**< 正在输入 */
    IM_E_IM_CHAT_STATUS_STOPPED                             = 1     /**< 停止输入 */
}IM_E_IM_CHAT_STATUS;

/**
 *  IM消息类型
 */
typedef enum tagIM_E_IM_CHAT_TYPE
{
    IM_E_IM_CHAT_TYPE_SINGLE                                = 0,    /**< 单聊 */
    IM_E_IM_CHAT_TYPE_TEMP                                  = 1,    /**< 临时单聊 */
    IM_E_IM_CHAT_TYPE_FIXEDGROUP                            = 2,    /**< 固定群聊 */
    IM_E_IM_CHAT_TYPE_TEMPGROUP                             = 3,    /**< 临时群聊 */
    IM_E_IM_CHAT_TYPE_HELP                                  = 4,    /**< 在线客服 */
    IM_E_IM_CHAT_TYPE_APPNOTIFY                             = 5,    /**< 提醒信息 */
    IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP                       = 6,    /**< 多人会话讨论组 */
    IM_E_IM_CHAT_TYPE_FILETRANSFER                          = 7,    /**< 文件传输通知 */
    IM_E_IM_CHAT_TYPE_SYSTEMNOTIFY                          = 10,   /**< 系统通知 */
    IM_E_IM_CHAT_TYPE_SYSTEMAD                              = 11,   /**< 系统广告 */
    IM_E_IM_CHAT_TYPE_MULTIMEETINGS                         = 14,   /**< 融合会议通知 */
    IM_E_IM_CHAT_TYPE_IMNOTIFY                              = 20,   /**< IM通知消息 */
    IM_E_IM_CHAT_TYPE_AUTOREPLAY                            = 101   /**< 自动回复 */
}IM_E_IM_CHAT_TYPE;

/**
 *  IM媒体格式
 */
typedef enum tagIM_E_IM_CHATMEDIA_TYPE
{
    tagIM_E_IM_CHATMEDIA_TYPE_TEXT                          = 0,    /**< 纯文本 */
    tagIM_E_IM_CHATMEDIA_TYPE_AUDIO                         = 1,    /**< 富媒体 语音 */
    tagIM_E_IM_CHATMEDIA_TYPE_VIDEO                         = 2,    /**< 富媒体 视频 */
    tagIM_E_IM_CHATMEDIA_TYPE_IMAGE                         = 3,    /**< 富媒体 图片 */
    tagIM_E_IM_CHATMEDIA_TYPE_FILE                          = 4,    /**< 富媒体 文件 */
    tagIM_E_IM_CHATMEDIA_TYPE_PUBLIC                        = 5,    /**< 富媒体 公众号 */
    tagIM_E_IM_CHATMEDIA_TYPE_CARDSHARE                     = 7,    /**< 富媒体 卡片分享 */
    tagIM_E_IM_CHATMEDIA_TYPE_IMAGETEXT                     = 8     /**< 富媒体 单图文混排 */
}IM_E_IM_CHATMEDIA_TYPE;

/**
 *  查询历史记录消息类型
 */
typedef enum tagIM_E_IM_HISTORYMESSAGEMSG_TYPE 
{
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_SINGLECHAT               = 0,    /**< 单聊消息 */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_GROUPCHAT                = 1,    /**< 讨论组/固定群消息 */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_SMS                      = 2,    /**< 短信消息 */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_BULLETIN                 = 3,    /**< 系统公告 */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_NOTIFY                   = 4     /**< 其他（P2P文件传输，好友邀请，群组邀请，群组通知） */
}IM_E_IM_HISTORYMESSAGEMSG_TYPE;

/** 
 * 客户端与服务器或其他客户端通信的会话通知 （100+为客户端自定义）
 */
typedef enum tagIM_E_IM_GENERAL_NOTIFY_TYPE
{
    IM_E_IM_GENERAL_NOTIFY_TYPE_UNALLOWED                   = 1,    /**< 没有权限*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_SESSION_NOTFOUND            = 2,    /**< 服务器保存的会话不存在（注销状态）*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_CONFIG_CHANGED              = 10,   /**< 服务器配置信息变更*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_MULTIMEDIA_INFO             = 100,  /**< 数据会议使用的通知消息 */
    IM_E_IM_GENERAL_NOTIFY_TYPE_DISGROUP_NOTIFY             = 101,  /**< 讨论组相关的通知消息（两转三）*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_AUDIO_STATUS                = 102,  /**< 语音状态通知消息 */
}IM_E_IM_GENERAL_NOTIFY_TYPE;

/**
 *  接收到的短信消息的类型
 */
typedef enum tagIM_E_SMS_NOTIFY_TYPE
{
    IM_E_SMS_NOTIFY_TYPE_RECVSMS                            = 0,    /**< 收到短信通知*/
    IM_E_SMS_NOTIFY_TYPE_SENDSMSSUCCESS                     = 1,    /**< 发送短信成功通知*/
    IM_E_SMS_NOTIFY_TYPE_SMSRECEIPT                         = 3,    /**< 短信回执成功通知*/
    IM_E_SMS_NOTIFY_TYPE_SMSSENDFAIL                        = 4,    /**< 短信发送失败*/
    IM_E_SMS_NOTIFY_TYPE_SMSRECEIPTFAIL                     = 5,    /**< 短信回执失败通知*/
    IM_E_SMS_NOTIFY_TYPE_SMSSEND                            = 6     /**< 发送短信（短信漫游时使用）*/
}IM_E_SMS_NOTIFY_TYPE;

/**
 *  历史消息操作类型
 */
typedef enum tagIM_E_IM_HISTORYMESSAGEOP_TYPE 
{
    IM_E_IM_HISTORYMESSAGEOP_TYPE_QUERYBEFORE               = 0,    /**< 查询MsgID之前的消息 */
    IM_E_IM_HISTORYMESSAGEOP_TYPE_FIRSTQUERY                = 1        /**< 首次查询，不需要MsgID */
}IM_E_IM_HISTORYMESSAGEOP_TYPE ;

/**
 *  群组查询类型
 */
typedef enum tagIM_E_IMGROUPQUERYTYPE
{
    IM_E_IMGROUPQUERYTYPE_BY_NAME                           = 0,    /**< 以名称查询 */
    IM_E_IMGROUPQUERYTYPE_BY_ID                             = 1,    /**< 以群组ID查询 */
    IM_E_IMGROUPQUERYTYPE_BY_NAME_ID                        = 2     /**< 以名称和ID查询 */
}IM_E_IMGROUPQUERYTYPE;

/**
 *  查询用户信息的关键字类型
 */
typedef enum tagIM_E_IMUSERQUERYTYPE
{
    IM_E_IMUSERQUERYTYPE_BY_PHONE                           = 0,    /**< 号码 */
    IM_E_IMUSERQUERYTYPE_BY_ACCOUNT                         = 1,    /**< 帐号 */
    IM_E_IMUSERQUERYTYPE_BY_BINDNO                          = 2,    /**< 绑定号码 */
    IM_E_IMUSERQUERYTYPE_BY_EMAIL                           = 3,    /**< 邮箱 */
    IM_E_IMUSERQUERYTYPE_BY_STAFFNO                         = 4     /**< 工号 */
}IM_E_IMUSERQUERYTYPE;

/**
 *  群组操作结果
 */
typedef enum tagIM_E_FIXEDGROUP_OP_RESULT
{
    IM_E_FIXEDGROUP_OP_RESULT_SUCCESS                       = 0,    /**< 操作成功 */
    IM_E_FIXEDGROUP_OP_RESULT_FAILED                        = 1,    /**< 操作失败 */
    IM_E_FIXEDGROUP_OP_RESULT_NOT_EXIST                     = 3,    /**< 群组不存在 */
    IM_E_FIXEDGROUP_OP_RESULT_REACH_MAXIMUM                 = 32,   /**< 成员群组数目已经达到最大 */            
    IM_E_FIXEDGROUP_OP_RESULT_MEMBER_REACH_MAXIMUM          = 33,   /**< 组内成员达到最大数目 */            
    IM_E_FIXEDGROUP_OP_RESULT_DB_ERROR                      = 34,   /**< 数据库异常的返回码 */        
    IM_E_FIXEDGROUP_OP_RESULT_DISCUSSIONGROUP_REACH_MAXIMUM = 35    /**< 成员讨论组数目已经达到最大 */        
}IM_E_FIXEDGROUP_OP_RESULT;

/**
 *  转移好友/联系人操作类型
 */
typedef enum tagIM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE
{
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_MOVE               = 0,    /**< 移动到新分组 */
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_COPY               = 1     /**< 复制到新分组 */
}IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE;

/**
 *  企业通讯录查询结果排序类型
 */
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERTYPE
{
    IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN                  = 0,    /**< 按拼音排序 */
    IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_STAFFNO                 = 1,    /**< 按工号号排序 */
    IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_NATIVENAME              = 3     /**< 按nativename排序  */
}IM_E_ADDRBOOKQUERY_ORDERTYPE;

/**
 *  企业通讯录查询结果排序方式
 */
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERMODEL
{
    IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC                    = 0,    /**< 升序 */
    IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_DESC                   = 1     /**< 降序 */
}IM_E_ADDRBOOKQUERY_ORDERMODEL;

/**
 *  用户被踢下线原因
 */
typedef enum tagIM_E_EXITSTATUS
{
    IM_E_EXITSTATUS_NORMALOFFLINE                           = 0,    /**<在其他终端上登录，本端被踢下线 */
    IM_E_EXITSTATUS_PAUSEOFFLINE                            = 2,    /**<账号被服务端暂停，下线 */
    IM_E_EXITSTATUS_OVERDUEOFFLINE                          = 3     /**<账号过期下线 */
}IM_E_EXITSTATUS;

/**
 *  插件/工作台面板当前状态
 */
typedef enum tagIM_E_SYNC_TYPE
{
    IM_E_SYNC_TYPE_VALID                                    = 0,    /**< 有效 */
    IM_E_SYNC_TYPE_INVALID                                  = 1     /**< 无效 */
}IM_E_SYNC_TYPE;

/**
 * 离开群组方式
 */
typedef enum  tagIM_E_LEAVEGROUP_FLAG 
{
    IM_E_LEAVEGROUP                                         = 0,    /**< 主动离开 */
    IM_E_KICKEDOUT                                          = 1     /**< 被踢 */
}IM_E_LEAVEGROUP_FLAG;

/**
 * 未送达消息类型
 */
typedef enum tagIM_E_UNDELIVER_MSG_TYPE
{
    IM_E_UNDELIVER_MSG_NOTALLOW                             = 1,    /**< 研发区非研发区不能互通 */
    IM_E_UNDELIVER_MSG_EXCEEDLIMIT                          = 2     /**< 讨论组消息发送超过大小限制 */
}IM_E_UNDELIVER_MSG_TYPE;

/**
 * 离开群组结果
 */
typedef enum tagIM_E_LEAVEGROUP_RESULT 
{
    IM_E_LEAVEGROUP_SUCCESS                                 = 0,    /**< 成功 */
    IM_E_LEAVEGROUP_FAILED                                  = 1,    /**< 失败 */
    IM_E_LEAVEGROUP_ACCOUNT_NOT_EXIST                       = 3     /**< 账号不存在 */
}IM_E_LEAVEGROUP_RESULT;

   
/**
 *  最近会话类型
 */
typedef enum tagIM_E_IM_RECENT_CONVERSATION_TYPE 
{
    IM_E_IM_RECENT_CONVERSATION_TYPE_SINGLE_CHAT            = 0,    /**< 单聊消息 */
    IM_E_IM_RECENT_CONVERSATION_TYPE_AUDIO                  = 1,    /**< 语音 */
    IM_E_IM_RECENT_CONVERSATION_TYPE_GROUP_CHAT             = 2,    /**< 固定群消息 */
    IM_E_IM_RECENT_CONVERSATION_TYPE_BULLETIN               = 3,    /**< 系统公告 */
    IM_E_IM_RECENT_CONVERSATION_TYPE_OFFICAL_ACCOUNTS       = 4,    /**< 公众号*/
    IM_E_IM_RECENT_CONVERSATION_TYPE_SMS                    = 5,    /**< 短信消息 */
    IM_E_IM_RECENT_CONVERSATION_TYPE_DISSUCSS_CHAT          = 6     /**< 讨论组群聊*/
}IM_E_IM_RECENT_CONVERSATION_TYPE;

//--------------------------------------------------------------枚举 end--------------------------------------------------------------

//--------------------------------------------------------------参数结构体 begin--------------------------------------------------------------

/**
 *  存在账号信息的用户
 */
typedef struct tagIM_S_USERINFO
{
    TUP_INT64    staffID;                                           /**< staffID */
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 成员账号 */ 
    TUP_CHAR    staffNO[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 成员工号 */ 
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 用户名 */
    TUP_CHAR    nativeName[IM_D_MAX_NAME_LENGTH];                   /**< 本地名字 */
    TUP_CHAR    qPinYin[IM_D_MAX_NAME_LENGTH];                      /**< 全拼    */
    IM_E_GENDER_TYPE    gender;                                     /**< 性别 */
    TUP_CHAR    birthday[IM_D_MAX_BIRTHDAY_LENGTH];                 /**< 生日 */
    TUP_CHAR    age[IM_D_AGE_LENGTH];                               /**< 年龄 */
    TUP_CHAR    bindNO[IM_D_MAX_PHONE_LENGTH];                      /**< 绑定号码 */
    TUP_CHAR    mobile[IM_D_MAX_PHONE_LENGTH];                      /**< 手机号码 */
    TUP_CHAR    homePhone[IM_D_MAX_PHONE_LENGTH];                   /**< 家庭电话 */
    TUP_CHAR    officePhone[IM_D_MAX_PHONE_LENGTH];                 /**< 办公电话 */
    TUP_CHAR    shortPhone[IM_D_MAX_PHONE_LENGTH];                  /**< 短号 */
    TUP_CHAR    otherPhone[IM_D_MAX_PHONE_LENGTH];                  /**< 其他电话 */
    TUP_CHAR    voip[IM_D_MAX_PHONE_LENGTH];                        /**< VOIP号码 */
    TUP_CHAR    ipPhone[IM_D_MAX_PHONE_LENGTH];                     /**< 绑定IPPhone号码 */
    TUP_CHAR    fax[IM_D_MAX_PHONE_LENGTH];                         /**< 传真 */
    TUP_CHAR    email[IM_D_MAX_DESC_LENGTH];                        /**< email地址 */
    TUP_CHAR    webSite[IM_D_MAX_DESC_LENGTH];                      /**< 个人网站 */
    TUP_CHAR    signature[IM_D_MAX_DESC_LENGTH];                    /**< 用户签名 */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**< 描述 */
    TUP_CHAR    address[IM_D_MAX_DESC_LENGTH];                      /**< 地址 */
    TUP_CHAR    imageID[IM_D_MAX_DESC_LENGTH];                      /**< 头像ID */
    TUP_CHAR    postalcode[IM_D_MAX_DESC_LENGTH];                   /**< 邮政编码 */
    TUP_BOOL    isSecrecy;                                          /**< 是否是保密成员 */
    TUP_CHAR    title[IM_D_MAX_DESC_LENGTH];                        /**< 职务 */
    TUP_CHAR    deptID[IM_D_MAX_DEPTNAME_LENGTH];                   /**< 部门ID */
    TUP_CHAR    deptNameEn[IM_D_MAX_NAME_LENGTH];                   /**< 部门英文名称 */
    TUP_CHAR    deptNameCn[IM_D_MAX_NAME_LENGTH];                   /**< 部门中文名称 */
    TUP_CHAR    imageSyncTime[IM_D_MAX_TIMESTAMP_LENGTH];           /**< 头像同步时间戳 */
    TUP_CHAR    oldAccount[IM_D_MAX_ACCOUNT_LENGTH];                /**< 老账号 */
    TUP_CHAR    state[IM_D_MAX_DESC_LENGTH];                        /**< 在职状态 0：在职、1：离职 */
    TUP_CHAR    modifyTime[IM_D_MAX_TIMESTAMP_LENGTH];              /**< 最后更新时间 */
}IM_S_USERINFO;

/**
 *  联系人信息
 *  @brief 联系人包括：1.拥有账号信息的用户;2.没有账号的自定义联系人
 *  @attention 自定义联系人的staffID为0，拥有账号信息的用户有有效的staffID
 */
typedef struct tagIM_S_CONTACTNFO
{    
    TUP_INT64    id;                                                /**< 好友ID */
    TUP_INT64    staffID;                                           /**< staffID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 姓名 */
    TUP_CHAR    nickName[IM_D_MAX_NAME_LENGTH];                     /**< 昵称 */
    TUP_CHAR    foreignName[IM_D_MAX_NAME_LENGTH];                  /**< 英文名 */
    TUP_CHAR    birthday[IM_D_MAX_BIRTHDAY_LENGTH];                 /**< 生日 */
    IM_E_GENDER_TYPE gender;                                        /**< 性别 */
    TUP_CHAR    corpName[IM_D_MAX_NAME_LENGTH];                     /**< 公司名 */
    TUP_CHAR    deptName[IM_D_MAX_NAME_LENGTH];                     /**< 部门名称 */
    TUP_CHAR    title[IM_D_MAX_DESC_LENGTH];                        /**< 头衔 */
    TUP_CHAR    mobile[IM_D_MAX_PHONE_LENGTH];                      /**< 手机号 */
    TUP_CHAR    officePhone[IM_D_MAX_PHONE_LENGTH];                 /**< 办公号码 */
    TUP_CHAR    homePhone[IM_D_MAX_PHONE_LENGTH];                   /**< 家庭电话 */
    TUP_CHAR    otherPhone[IM_D_MAX_PHONE_LENGTH];                  /**< 其他号码 */
    TUP_CHAR    fax[IM_D_MAX_PHONE_LENGTH];                         /**< 传真 */
    TUP_CHAR    email[IM_D_MAX_DESC_LENGTH];                        /**< 电子邮箱 */
    TUP_CHAR    webSite[IM_D_MAX_DESC_LENGTH];                      /**< 首页 */
    TUP_CHAR    imNO[IM_D_MAX_DESC_LENGTH];                         /**< 聊天工具号码 */
    TUP_CHAR    address[IM_D_MAX_DESC_LENGTH];                      /**< 地址 */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**< 描述 */
    TUP_CHAR    postalcode[IM_D_MAX_DESC_LENGTH];                   /**< 邮编 */
    TUP_CHAR    state;                                              /**< 同步状态(增量同步时用到) */
}IM_S_CONTACTNFO;

/**
 *  好友分组信息
 */
typedef struct tagIM_S_USERGROUPINFO
{
    TUP_INT64    id;                                                /**< 组ID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 组名称 */
    TUP_INT64    index;                                             /**< 组序号 */
    TUP_CHAR    state;                                              /**< 同步状态(增量同步时用到) */
}IM_S_USERGROUPINFO;

/**
 *  好友分组和组内成员对应关系
 */
typedef struct tagIM_S_USERGROUPMEMBERINFO
{
    TUP_INT64    groupID;                                           /**< 好友分组ID */
    TUP_INT64    contactID;                                         /**< 好友分组成员ID，即结构体IM_S_CONTACTNFO的id字段 */
    TUP_CHAR    state;                                              /**< 同步状态(增量同步时用到) */
}IM_S_USERGROUPMEMBERINFO;

/**
 *  固定群详细信息
 */
typedef struct tagIM_S_IMGROUPINFO
{
    TUP_CHAR    id[IM_D_GROUPID_LENGTH];                            /**<  群ID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**<  群名称 */
    TUP_INT32    capacity;                                          /**<  群大小 */
    TUP_CHAR    manifesto[IM_D_MAX_DESC_LENGTH];                    /**<  公告 */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**<  简介 */
    TUP_CHAR    owner[IM_D_MAX_ACCOUNT_LENGTH];                     /**<  管理员 */
    IM_E_IMGROUP_JOIN_AUTH_FLAG    autoJoinFlag;                    /**<  加入群是否可以审批 */
    IM_E_IMGROUP_MSGPOLICY_TYPE msgpolicyType;                      /**<  群组消息策略 */
    IM_E_IMGROUP_TYPE groupType;                                    /**<  固定群和讨论组标记 */
    IM_E_IMGROUP_ISFIXDISCUSS fixdiscuss;                           /**<  讨论组是否固化 */
    TUP_CHAR    state[IM_D_GENEAL_LENGTH];                          /**<  状态:'0'有效，‘1’无效*/
}IM_S_IMGROUPINFO;

/**
 *  获取固定群或讨论组成员列表响应
 */
typedef struct tagIM_S_GROUPUSERLIST
{
    TUP_BOOL  isSyncAll;                                            /**<  是否全量同步 */
    TUP_CHAR  timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];                 /**<  同步时间戳，19000000000000（年月日时分秒） */
    TUP_CHAR  groupID[IM_D_GROUPID_LENGTH];                         /**<  群ID */
    TUP_S_LIST*    memberInfo;                                      /**<  成员信息 TUP_S_LIST中的*dada结构类型为IM_S_USERINFO */
}IM_S_GROUPUSERLIST;

/**
 *  部门信息
 */
typedef struct tagIM_S_DEPTINFO
{
    TUP_INT64    deptID;                                            /**< 部门ID */
    TUP_INT64    parentDeptID;                                      /**< 上级部门ID */
    TUP_INT64    deptLevel;                                         /**< 部门层级 */
    TUP_CHAR    deptName[IM_D_MAX_DEPTNAME_LENGTH];                 /**< 部门名称 */
    TUP_CHAR    fullDeptName[IM_D_MAX_DEPTNAME_LENGTH];             /**< 部门全称 */
}IM_S_DEPTINFO;

/**
 *  登录请求
 */
typedef struct tagIM_S_LOGIN_ARG
 {
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 帐号(账号登陆时必填) */
    TUP_CHAR    password[IM_D_MAX_PASSWORD_LENGTH];                 /**< 密码(账号登陆时必填) */
    TUP_CHAR    version[IM_D_MAX_VERSION_LENGTH];                   /**< 版本号(必填，默认值"0.0.0.0") */
    IM_E_LOGIN_AUTHTYPE    authType;                                /**< 登陆使用的鉴权类型 (选填，默认为账号登陆)*/
    TUP_CHAR    language[IM_D_GENEAL_LENGTH];                       /**< 登录语言 (选填， 默认值"zh-cn")*/
    TUP_CHAR    clientDesc[IM_D_GENEAL_LENGTH];                     /**< 客户端描述(PC/VDI) (选填，默认值"PC")*/
    TUP_CHAR    ticket[IM_D_MAX_DESC_LENGTH];                       /**< 第三方鉴权ticket (鉴权登陆时必填)*/
 }IM_S_LOGIN_ARG;

/**
 *  登录响应
 */
typedef struct tagIM_S_LOGIN_ACK
 {
    TUP_BOOL    result;                                             /**< 登录结果 */
    IM_E_LOGIN_RESULT    reason;                                    /**< 登录结果详情（可以在result为false的时候获取失败原因） */
    TUP_INT32    retryTimes;                                        /**< 登录重试剩余次数(result为IM_E_LOGING_RESULT_ACCOUNT_LOCKED有效) */
    TUP_INT32    lockInterval;                                      /**< 帐号被锁定剩余时间（单位：分钟） (result为IM_E_LOGING_RESULT_ACCOUNT_LOCKED有效*/
    TUP_CHAR    token[IM_D_MAX_DESC_LENGTH];                        /**< 客户端进行HTTP请求的鉴权字符串 */
    TUP_INT32    regionID;                                          /**< 区域ID */
    TUP_CHAR    lastLoginIP[IM_D_IP_LENGTH];                        /**< 上一次登录的服务器IP */
    TUP_CHAR    lastLoginTime[IM_D_MAX_TIMESTAMP_LENGTH];           /**< 上一次登录的服务器时间 */
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 服务器返回的帐号信息 */
    TUP_INT64    sessionID;                                         /**< 登录成功后服务器返回的会话ID */
    IM_E_LOGIN_ENCRYPT_TYPE encryptType;                            /**< 加密方式 */
 }IM_S_LOGIN_ACK;

/**
 *  查询好友列表请求
 */
typedef struct tagIM_S_GETCONTACTLIST_ARG
 {
    TUP_BOOL    isSyncAll;                                          /**< 是否全量同步：本次查询是返回所有好友列表信息，或者返回某个时间段到现在新增的好友列表以及好友(必填) */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 增量同步时间戳，时间格式：19000000000000（年月日时分秒） (isSyncAll为TUP_FALSE时必填) */
 }IM_S_GETCONTACTLIST_ARG;

/**
 *  查询联系人列表响应
 */
typedef struct tagIM_S_GETCONTACTLIST_ACK
 {
    TUP_BOOL    result;                                             /**< 操作结果 */
    TUP_BOOL    isSyncAll;                                          /**< 本次同步是否是增量同步 */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 增量同步时间戳，格式为：19000000000000（年月日时分秒），isSyncAll为TUP_TRUE时时间戳有效 */
    TUP_S_LIST*    userList;                                        /**< 有账号的用户好友列表（拥有账号信息的用户）列表， TUP_S_LIST中的*dada结构类型为IM_S_USERINFO */
    TUP_S_LIST* contactList;                                        /**< 好友列表，好友包括账号用户和自定义联系人， TUP_S_LIST中的*dada结构类型为IM_S_CONTACTNFO */
    TUP_S_LIST* userGroupList;                                      /**< 好友分组， TUP_S_LIST中的*dada结构类型为IM_S_USERGROUPINFO */
    TUP_S_LIST* userGroupMemberList;                                /**< 好友分组和联系人对应关系， TUP_S_LIST中的*dada结构类型为M_S_USERGROUPMEMBERINFO */
    TUP_S_LIST* imGroupList;                                        /**< 固定群列表， TUP_S_LIST中的*dada结构类型为IM_S_IMGROUPINFO*/
 }IM_S_GETCONTACTLIST_ACK;

/**
 *  查询业务配置数据请求
 */
typedef struct tagIM_S_GETSERVICEPROFILEARG
{
    TUP_BOOL    isSyncAll;                                          /**< 是否全量同步 */
    TUP_BOOL    needIcon;                                           /**< 是否需要面板信息的图标 */
    TUP_BOOL    isVpnAccess;                                        /**< 是否VPN接入  */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 增量同步时间戳，格式为：19000000000000（年月日时分秒），isSyncAll为TUP_TRUE时有效 */
    TUP_CHAR    localIP[IM_D_IP_LENGTH];                            /**< 本地IP地址 */
}IM_S_GETSERVICEPROFILEARG;

/**
 *  查询业务配置数据结果响应
 */
typedef struct tagIM_S_SERVICEPROFILEACK
{
    TUP_BOOL    syncType;                                           /**< 是否全量同步 */
    TUP_BOOL    isSetIpphone;                                       /**< 是否设置了IPPhone */
    TUP_BOOL    isJointUser;                                        /**< 是否设置联动 */
    TUP_BOOL    bindChange;                                         /**< IP变化是否绑定切换 */
    TUP_INT32   sipExpires;                                         /**< sip注册心跳时间 */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 服务器时间戳 */    
    TUP_CHAR    ipPhone[IM_D_GENEAL_LENGTH];                        /**< 绑定IPPhone号码 */
    TUP_CHAR    eConsoleAddr[IM_D_IP_LENGTH];                       /**< eConsole地址 */
    TUP_CHAR    sipAccount[IM_D_GENEAL_LENGTH];                     /**< sip账号 */
    TUP_CHAR    sipPassword[IM_D_MAX_NAME_LENGTH];                  /**< sip账号密码 */
    TUP_CHAR    sipServer[IM_D_IP_LENGTH];                          /**< sip服务器地址 (含端口) */
    TUP_CHAR    sipicscfDomainName[IM_D_IP_LENGTH];                 /**< ICSCF域名 */
    TUP_CHAR    sipCountryCode[IM_D_GENEAL_LENGTH];                 /**< 国家码 */
    TUP_CHAR    sipOutgoingAccCode[IM_D_GENEAL_LENGTH];             /**< 外呼接入码 */
    TUP_CHAR    sipInfoAccCode[IM_D_GENEAL_LENGTH];                 /**< Info接入码 */
    TUP_CHAR    sipUcPassword[IM_D_MAX_NAME_LENGTH];                /**< UC密码  */
    TUP_CHAR    sipNetType[IM_D_GENEAL_LENGTH];                     /**< 组网类型（IMS/NGN） */
    TUP_S_LIST* funcIDList;                                         /**< 用户功能列表，用户本次登录使用的功能位 long long型 */
    TUP_S_LIST* configList;                                         /**< 配置信息列表  TUP_S_LIST中的*dada结构类型为IM_S_CONFIGINFO */
    TUP_S_LIST* panelList;                                          /**< 面板信息列表  TUP_S_LIST中的*dada结构类型为IM_S_PANELINFO */
    TUP_S_LIST* serverList;                                         /**< 插件服务器列表 TUP_S_LIST中的*dada结构类型为IM_S_SERVERINFO */
    TUP_S_LIST* componentList;                                      /**< 插件信息列表  TUP_S_LIST中的*dada结构类型为IM_S_COMPONETINFO*/
    TUP_S_LIST* componentParamList;                                 /**< 插件参数信息列表 TUP_S_LIST中的*dada结构类型为IM_S_COMPONETPARAMINFO */
    TUP_S_LIST* dataConfAddrList;                                   /**< 数据会议地址列表  TUP_S_LIST中的*dada结构类型为IM_S_DATACONFADDRINFO */
    TUP_S_LIST* umServerHttpList;                                   /**< UM 服务器 http列表  TUP_S_LIST中的*dada结构类型为IM_S_UMSERVERADDR */
    TUP_S_LIST* umServerHttpsList;                                  /**< UM 服务器 https列表  TUP_S_LIST中的*dada结构类型为IM_S_UMSERVERADDR */
    TUP_CHAR    dataConfAddrs[IM_D_MAX_PATH_LENGTH];                /**< 数据会议服务器地址列表，字符串形式 */
    TUP_CHAR    audioGWType;                                        /**< 客户端注册的语音网关类型 0:U1900; 1:USM */
}IM_S_SERVICEPROFILEACK;

/**
 *  配置信息列表
 */
typedef struct tagIM_S_CONFIGINFO
{
    TUP_CHAR    name[IM_D_GENEAL_LENGTH];                           /**< 名字 */
    TUP_CHAR    value[IM_D_GENEAL_LENGTH];                          /**< 对应的值 */
}IM_S_CONFIGINFO;

/**
 *  工作台面板信息
 */
typedef struct tagIM_S_PANELINFO
{
    TUP_INT64    id;                                                /**< 面板ID */
    TUP_INT64    indexNO;                                           /**< 面板图标序号 */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 名称 */
    IM_E_SYNC_TYPE    state;                                        /**< 状态 */
}IM_S_PANELINFO;

/**
 *  插件信息
 */
typedef struct tagIM_S_COMPONETINFO
{
    TUP_INT64    id;                                                /**< 插件ID */
    TUP_INT64    panelID;                                           /**< 对应面板ID */
    TUP_INT64    functionID;                                        /**< 对应功能位 */
    TUP_INT64    indexNO;                                           /**< 序号 */
    TUP_INT64    serverID;                                          /**< 对应服务ID */
    TUP_CHAR    progID[IM_D_MAX_PROGID_LENGTH];                     /**< progid */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 插件名称 */
    TUP_CHAR    type[IM_D_GENEAL_LENGTH];                           /**< 插件类型 */
    TUP_CHAR    path[IM_D_MAX_PATH_LENGTH];                         /**< 插件路径 */
    TUP_CHAR    icon[IM_D_ICON_LENGTH];                             /**< 插件图标*/
    TUP_CHAR    protocol[IM_D_GENEAL_LENGTH];                       /**< 协议类型 */
    IM_E_SYNC_TYPE    state;                                        /**< 插件状态 */
}IM_S_COMPONETINFO;

/**
 *  插件参数信息列表
 */
typedef struct tagIM_S_COMPONETPARAMINFO
{
    TUP_CHAR    progID[IM_D_MAX_PROGID_LENGTH];                     /**< progid */
    TUP_CHAR    key[IM_D_MAX_PLUGINPARAM_LENGTH];                   /**< progid对应的参数 */
    TUP_CHAR    value[IM_D_MAX_PLUGINPARAM_LENGTH];                 /**< progid对应的参数的值 */
}IM_S_COMPONETPARAMINFO;

/**
 *  服务器信息
 */
typedef struct tagIM_S_SERVERINFO
{
    TUP_INT64    id;                                                /**< 服务器ID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 服务器名称 */
    TUP_CHAR    address[IM_D_MAX_PLUGINURL_LENGTH];                 /**< 服务器地址 */
}IM_S_SERVERINFO;

/**
 *  数据会议服务器地址
 */
typedef struct tagIM_S_DATACONFADDRINFO
{
    TUP_CHAR    dataConfAddr[IM_D_IP_LENGTH];                       /**< 数据会议服务器地址 */
}IM_S_DATACONFADDRINFO;

/**
 *  UM服务器地址
 */
typedef struct tagIM_S_UMSERVERADDR
{
    TUP_CHAR    umServerAddr[IM_D_IP_LENGTH];                       /**< UM服务器地址 */
}IM_S_UMSERVERADDR;

/**
 *    查询用户请求（精确查询）
 *@    attention: account和staffID两个参数填写其中一个就可以开始查询
 */
typedef struct tarIM_S_GETUSERINFOARG
{
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 帐号 */
    TUP_INT64    staffID;                                           /**< staffID（创建账号时由服务器生成的唯一标示，新老工号切换也不会改变该值）*/
}IM_S_GETUSERINFOARG;

/**
 *  查询固定群请求（模糊查询，返回结果列表）
 */
typedef struct tagIM_S_GETIMGROUPLIST_ARG
 {
    TUP_BOOL    isNeedAmount;                                       /**< 是否需要返回总数 (必填) */ 
    TUP_INT32    offset;                                            /**< 查询偏移量 (选填) */ 
    TUP_INT32    count;                                             /**< 单次查询结果返回的数量(必填) */ 
    TUP_CHAR    queryKey[IM_D_GENEAL_LENGTH] ;                      /**< 关键字 (必填) */ 
    IM_E_IMGROUPQUERYTYPE    queryType;                             /**< 群组查询类型 (必填) */
 }IM_S_GETIMGROUPLIST_ARG;

/**
 *  查询固定群响应（模糊查询，返回结果列表）
 */
typedef struct tagIM_S_GETIMGROUPLIST_ACK
 {
    TUP_INT32    recordAmount;                                      /**< 总记录数 */ 
    TUP_INT32    offset;                                            /**< 查询偏移量 */ 
    TUP_INT32    count;                                             /**< 查询数目 */ 
    TUP_S_LIST*    imGroupList;                                     /**< 群组列表 TUP_S_LIST中的*dada结构类型为IM_S_IMGROUPINFO */ 
 }IM_S_GETIMGROUPLIST_ACK;

/**
 *  添加好友分组请求
 */
typedef struct tagIM_S_ADDUSERGROUP_ARG
 {
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 分组名称(必填) */
    TUP_INT32    index;                                             /**< 序号(必填，如果不需要分组排序，则默认填-1) */
 }IM_S_ADDUSERGROUP_ARG;

/**
 *  添加好友分组响应
 */
typedef struct tagIM_S_ADDUSERGROUP_ACK
 {
    TUP_BOOL    result;                                             /**< 操作结果 */
    TUP_INT64    id;                                                /**< 分组号 */
 }IM_S_ADDUSERGROUP_ACK;

/**
 *  修改好友分组请求
 */
typedef struct tagIM_S_MODUSERGROUP_ARG
 {
    TUP_INT64    id;                                                /**< 分组号(必填) */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 分组名称(必填) */
    TUP_INT32    index;                                             /**< 序号(必填，如果不需要分组排序，则默认填-1) */
 }IM_S_MODUSERGROUP_ARG;

/**
 *  添加账号用户为好友请求
 */
typedef struct tagIM_S_ADDFRIEND_ARG
 {
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 好友帐号 (必填)*/
    TUP_INT64    groupID;                                           /**< 好友分组ID(必填) */
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< 被加为好友的用户收到被添加通知中显示的添加者名字(可选) */
 }IM_S_ADDFRIEND_ARG;

/**
 *  添加账号用户为好友响应
 */
typedef struct tagIM_S_ADDFRIEND_ACK
 {
    TUP_BOOL    result;                                             /**< 操作结果 */
    TUP_INT64    contactID;                                         /**< 联系人在好友/联系人分组中的ID，即好友结构体：IM_S_CONTACTNFO中的id */
 }IM_S_ADDFRIEND_ACK;

/**
 *  添加自定义联系人为好友请求
 */
typedef struct tagIM_S_ADDCONTACT_ARG
 {
    IM_S_CONTACTNFO    contact;                                     /**< 自定义联系人信息，添加自定义联系人时id字段不用填写，添加成功后返回（staffID填写登录用户的staffID，必填) */
    TUP_INT64    groupID;                                           /**< 添加到的分组ID(必填) */
 }IM_S_ADDCONTACT_ARG;

/**
 *  添加自定义联系人响应
 */
typedef struct tagIM_S_ADDCONTACT_ACK
 {
    TUP_BOOL    result;                                             /**< 操作结果 */
    TUP_INT64    contactID;                                         /**< 好友ID */
 }IM_S_ADDCONTACT_ACK;

/**
 *  修改自定义联系人请求
 */
typedef struct tagIM_S_MODCONTACT_ARG
 {
    IM_S_CONTACTNFO        contact;                                 /**< 联系人信息（id必填） */
 }IM_S_MODCONTACT_ARG;

/**
 *  从某一个分组中删除好友或/联系人
 */
typedef struct tagIM_S_DELCONTACT_ARG
 {
    TUP_INT64    contactID;                                         /**< 联系人ID(必填) */
    TUP_INT64    groupID;                                           /**< 分组ID(必填) */
 }IM_S_DELCONTACT_ARG;

/**
 *  转移好友分组请求
 */
typedef struct tagIM_S_MODCONTACTGROUP_ARG
 {
    TUP_INT64    contactID;                                         /**< 联系人ID(必填) */ 
    TUP_INT64    oldGroupID;                                        /**< 原组ID(必填) */ 
    TUP_INT64    newGroupID;                                        /**< 新组ID(必填) */ 
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE    type;                   /**< 移动还是复制 */ 
 }IM_S_MODCONTACTGROUP_ARG;

/**
 *  发送文本消息请求
 */
typedef struct tagIM_S_SENDIM_ARG
{
    TUP_INT        regionID;                                        /**< 区域ID 服务器用 (可选) */
    IM_E_IM_CHAT_TYPE    chatType;                                  /**< IM消息类型(必填) */
    IM_E_IM_CHAT_SOURCE_FLAG    sourceFlag;                         /**< IM消息发自哪里(必填) */
    IM_E_IM_CHAT_CONTENT_TYPE    contentType;                       /**< IM消息内容格式(必填) */
    TUP_CHAR    origin[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 发送方账号(必填) */
    TUP_CHAR    target[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 接收方账号(必填) */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 群组ID（固定群和讨论组必填）*/
    TUP_CHAR    content[IM_D_MAX_MESSAGE_LENGTH];                   /**< IM消息内容(必填) */
    TUP_CHAR    displayname[IM_D_MAX_NAME_LENGTH];                  /**< 发送方名字(可选) */
    TUP_INT64    utcStamp;                                          /**< UTC时间 (可选) */
    TUP_INT64    clientChatID;                                      /**< 客户端生成的消息ID */
    IM_E_IM_CHATMEDIA_TYPE mediaType;                               /**< 媒体类型 */
}IM_S_SENDIM_ARG;


/**
 *  文本消息已读设置请求
 */
typedef struct tagIM_S_SETMESSAGEREAD_ARG
{
    TUP_S_LIST*    messageinfo;                                     /**< 已读消息设置消息格式 TUP_S_LIST中的*dada结构类型为IM_S_MESSAGEINFO */
}IM_S_SETMESSAGEREAD_ARG;

/**
 *  查询漫游消息请求
 */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ARG
{
    IM_E_IM_HISTORYMESSAGEOP_TYPE    opType;                        /**< 操作类型 */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE    msgType;                      /**< 请求的消息类型 */
    TUP_CHAR    sender[IM_D_MAX_PHONE_LENGTH];                      /**< 消息发送方，msgType为0时填写消息发送者账号，msgType为1时填写群组ID，msgType为2时填写短信号码，msgType为3时不填写 */
    TUP_INT64    msgID;                                             /**< 消息ID，首次查询忽略该字段 */
    TUP_INT        count;                                           /**< 查询的消息条数 */
}IM_S_QUERYHISTORYMESSAGE_ARG;

/**
 *  查询漫游消息响应
 */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ACK
{
    TUP_INT        totalCount;                                      /**< 消息总条数，首次查询时返回 */
    IM_E_IM_HISTORYMESSAGEOP_TYPE    opType;                        /**< 操作类型 */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE    msgType;                      /**< 请求的消息类型 */
    TUP_CHAR sender[IM_D_MAX_PHONE_LENGTH];                         /**< 消息发送方，msgType为0时是消息发送者账号，msgType为1是群ID，msgType为2时是短信号码，msgType为3时忽略 */
    TUP_S_LIST*    chatinfolist;                                    /**< 消息格式 TUP_S_LIST中的*dada结构类型为IM_S_CODECHAT_NOTIFY */
    TUP_S_LIST* smsList;                                            /**< 短信消息列表  TUP_S_LIST中的*dada结构类型为IM_S_SMSINFO */
}IM_S_QUERYHISTORYMESSAGE_ACK;

/**
 *  文本信息
 */
typedef struct tagIM_S_CHATINFO_NOTIFY
{
    IM_E_IM_CHAT_TYPE    chatType;                                  /**< IM消息类型 */
    TUP_INT     sourceFlag;                                         /**< IM消息发自哪里 */
    TUP_INT     contentType;                                        /**< IM消息内容格式*/
    TUP_INT64   utcStamp;                                           /**< UTC时间*/
    TUP_CHAR    origin[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 发送方账号*/
    TUP_CHAR    target[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 接收方账号*/
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 群组ID*/
    TUP_CHAR    content[IM_D_MAX_MESSAGE_LENGTH];                   /**< IM消息内容*/
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< 发送方名字*/
    TUP_INT     regionID;                                           /**< 区域ID 服务器用 */
    TUP_INT64   clientChatID;                                       /**< 客户端生成的消息ID */
    TUP_INT64   serverChatID;                                       /**< 服务器生成的消息ID，客户端发送时不填，接收时服务器填写 */
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 群组名 */
    IM_E_IM_CHATMEDIA_TYPE mediaType;                               /**< 媒体类型 */
    TUP_INT64   deliverTime;                                        /**< 服务器发送的时间*/
}IM_S_CHATINFO_NOTIFY;

/**
 *  短信消息
 */
typedef struct tagIM_S_SMSINFO
{
    TUP_CHAR    origin[IM_D_MAX_PHONE_LENGTH];                      /**< 发送方号码*/
    TUP_CHAR    target[IM_D_MAX_PHONE_LENGTH];                      /**< 接收方号码*/
    TUP_INT64   serverMsgID;                                        /**< 服务器消息ID*/
    TUP_CHAR    clientMsgID[IM_D_MAX_CHAR_LENGTH];                  /**< 客户端消息ID*/
    TUP_CHAR    content[IM_D_MAX_MESSAGE_LENGTH];                   /**< 消息内容*/
    TUP_CHAR    sendTime[IM_D_MAX_TIMESTAMP_LENGTH];                /**< 发送时间*/
    IM_E_SMS_NOTIFY_TYPE    smsType;                                /**< 接收到的短信消息的类型 */
}IM_S_SMSINFO;

/**
 *  设置消息已读
 */
typedef struct tagIM_S_MESSAGEINFO
{
    IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType;                         /**< 消息类型 */
    TUP_CHAR    sender[IM_D_MAX_PHONE_LENGTH];                      /**< 发送方 (个人账号、固定群、讨论组ID、短信号码) */
    TUP_INT64    msgId;                                             /**< 消息ID (serverChatID) */
}IM_S_MESSAGEINFO;

/**
 *  输入状态请求
 */
typedef struct tagIM_S_CHAT_STATUS_ARG
{
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 接收方账号(必填) */
    IM_E_IM_CHAT_STATUS    type;                                    /**< 输入状态(必填) */
}IM_S_CHAT_STATUS_ARG;

/**
 *  查询部门列表响应
 */
typedef struct tagIM_S_GETDEPTS_ACK
 {
    TUP_BOOL    result;                                             /**< 本次操作结果 */
    TUP_S_LIST*    deptList;                                        /**< 部门列表 TUP_S_LIST中的*dada结构类型为IM_S_DEPTINFO */
 }IM_S_GETDEPTS_ACK;

/**
 *  查询企业通讯录请求
 */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ARG
{
    TUP_BOOL    isNeedAmount;                                       /**< 是否需要返回总数(必填) */ 
    IM_E_ADDRBOOKQUERY_ORDERTYPE orderType;                         /**< 排序的关键字 */ 
    IM_E_ADDRBOOKQUERY_ORDERMODEL orderModel;                       /**< 排序的方式 */ 
    TUP_INT32 offset;                                               /**< 查询偏移量(必填) */ 
    TUP_INT32 count;                                                /**< 查询数目(必填) */ 
    TUP_INT64 deptID;                                               /**< 查询部门（必填，如果不指定部门，请填写-1） */ 
    TUP_CHAR queryKey[IM_D_MAX_DESC_LENGTH];                        /**< 关键字（可选） */ 
}IM_S_QUERY_ENTADDRESSBOOK_ARG;

/**
 *  查询企业通讯录结果响应
 */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ACK
{
    TUP_BOOL    result;                                             /**< 本次操作结果 */
    TUP_INT32    recordAmount;                                      /**< 总记录数 */ 
    TUP_S_LIST*    userList;                                        /**< 成员列表， TUP_S_LIST中的*dada结构类型为IM_S_USERINFO */ 
}IM_S_QUERY_ENTADDRESSBOOK_ACK;

/**
 *  查询用户信息请求（模糊查询）
 */
typedef struct tagIM_S_QUERY_USERINFO_ARG
{
    TUP_CHAR    key[IM_D_MAX_PHONE_LENGTH];                         /**< 关键词内容 */
    IM_E_IMUSERQUERYTYPE    type;                                   /**< 关键词类型 */
}IM_S_QUERY_USERINFO_ARG;

/**
 *  查询用户信息结果响应（模糊查询）
 */
typedef struct tagIM_S_QUERY_USERINFO_ACK
{
    TUP_S_LIST*    userList;                                        /**< 成员列表， TUP_S_LIST中的*dada结构类型为IM_S_USERINFO */ 
}IM_S_QUERY_USERINFO_ACK;

/**
 *  创建或修改固定群或讨论组请求
 */
typedef struct tagIM_S_IMGROUP_OP_ARG
{
    IM_S_IMGROUPINFO    fixedgroupInfo;                             /**< 固定群或讨论组信息（添加时id不填，在ack中返回；修改时需要填写id） */
}IM_S_IMGROUP_OP_ARG;

/**
 *  创建固定群或讨论组响应
 */
typedef struct tagIM_S_ADDIMGROUP_ACK
{
    TUP_BOOL    result;                                             /**< 操作结果 */
    TUP_CHAR    id[IM_D_GROUPID_LENGTH];                            /**< 创建的固定群或讨论组ID  */
    IM_E_FIXEDGROUP_OP_RESULT    reason;                            /**< 操作结果返回值，可以在result为TUP_FALSE时来判断失败原因 */
}IM_S_ADDIMGROUP_ACK;

/**
 *  修改固定群信息响应
 */
typedef struct tagIM_S_MODFIXEDGROUP_ACK
{
    TUP_BOOL    result;                                             /**< 操作结果 */
    IM_E_FIXEDGROUP_OP_RESULT    reason;                            /**< 操作结果返回值，可以在result为TUP_FALSE时来判断失败原因 */
}IM_S_MODFIXEDGROUP_ACK;

/**
 *  添加固定群成员请求
 */
typedef struct tagIM_S_ADDIMGROUPMEMBER_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 添加用户帐号 */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 固定群名称 */ 
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< 被添加用户收到通知中的显示名 （非必填）*/ 
}IM_S_ADDIMGROUPMEMBER_ARG;

/**
 *  获取固定群或讨论组成员请求
 */
typedef struct tagIM_S_REQUESTIMGROUPMEMBERS_ARG
{
    TUP_BOOL    isSyncAll;                                          /**< 是否全量同步 */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群或讨论组ID */
    TUP_CHAR    timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 同步时间戳，19000000000000（年月日时分秒)，不填写使用默认时间19000000000000 */
}IM_S_REQUESTIMGROUPMEMBERS_ARG;

/**
 *  删除固定群或讨论组成员请求
 */
typedef struct tagIM_S_DELIMGROUPMEMBER_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                        /**< 固定群ID （必填）*/ 
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 被删除的用户帐号 （必填）*/ 
}IM_S_DELIMGROUPMEMBER_ARG;

/**
 *  管理员审批用户申请加入固定群申请，或者用户审批管理员邀请加入固定群
 */
typedef struct tagIM_S_CONFIRM_JOINFIXEDGROUP_ARG
{
    TUP_BOOL    agreeJoin;                                          /**< 管理员是否同意成员的申请 */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 群组名ID */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< 申请加入成员帐号 */ 
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< 对方收到审批结果中的显示名 （非必填）*/ 
}IM_S_CONFIRM_JOINFIXEDGROUP_ARG;

/**
 *  用户申请加入固定群请求
 */
typedef struct tagIM_S_JOINFIXEDGROUP_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 固定群名 */ 
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< 显示申请者名称（非必填） */ 
}IM_S_JOINFIXEDGROUP_ARG;

/**
 *  转移固定群或讨论组管理员权限请求
 */
typedef struct tagIM_S_TRANSFERIMGROUP_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 被转移成管理员的成员帐号 */ 
}IM_S_TRANSFERIMGROUP_ARG;

/**
 *  固定群管理员收到被邀用户对加入固定群邀请的审批结果
 */
typedef struct tagIM_S_IMGROUP_OWNER_INVITE_RESULT_NOTIFY
{
    TUP_BOOL    agreeInvite;                                        /**< 用户是否同意管理员的邀请 */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 固定群群名称 */
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< 被邀请成员的帐号 */
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**< 被邀请成员的名称 */
}IM_S_IMGROUP_OWNER_INVITE_RESULT_NOTIFY;

/**
 *  用户主动离开固定群通知
 */
typedef struct tagIM_S_IMGROUP_LEAVE_RESULT_NOTIFY
{
    IM_E_FIXEDGROUP_OP_RESULT    resultCode;                        /**< 服务器返回码 */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 群ID */
}IM_S_IMGROUP_LEAVE_RESULT_NOTIFY;

/**
 *  用户收到被管理员踢出固定群通知
 */
typedef struct tagIM_S_IMGROUP_KICKOUT_NOTIFY
{
    IM_E_FIXEDGROUP_OP_RESULT    resultCode;                        /**< 服务器返回码 */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 群ID */
}IM_S_IMGROUP_KICKOUT_NOTIFY;

/**
 *   聊天消息未送达（如研发和非研）
 */
typedef struct tagIM_S_UNDELIVER_NOTIFY
{
    IM_S_CHATINFO_NOTIFY chatInfo;                                  /**< 聊天信息 */
    IM_E_UNDELIVER_MSG_TYPE type;                                   /**< 未送达消息类型 */
}IM_S_UNDELIVER_NOTIFY;

/**
 *   聊天消息已读通知（多端登录）    
 */
typedef struct tagIM_S_MSG_READ_NOTIFY
{
    TUP_CHAR from[IM_D_MAX_ACCOUNT_LENGTH];                         /**< 消息发送者 */
    TUP_CHAR target[IM_D_MAX_ACCOUNT_LENGTH];                       /**< 消息接受者 */
    TUP_INT64 msgID;                                                /**< 消息ID */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE   msgType;                       /**< 消息类型 */
}IM_S_MSG_READ_NOTIFY;
/**
 *   聊天消息发送结果通知
 */
typedef struct tagIM_S_SENDACK_NOTIFY
{
    TUP_CHAR origin[IM_D_MAX_ACCOUNT_LENGTH];                      /**< 消息发送者 */
    TUP_CHAR target[IM_D_MAX_ACCOUNT_LENGTH];                       /**< 消息接受者 */
	TUP_INT64 utcStamp;                                             /**< 时间戳 */
	TUP_INT64 chatID;                                               /**< 客户端侧消息ID */
    TUP_INT64 serverChatID;                                         /**< 服务器侧消息ID */
    TUP_BOOL  result;                                               /**< 发送结果 */
}IM_S_SENDACK_NOTIFY;
/**
 *   客户端与服务器或其他客户端通信的会话通知
 */
typedef struct tagIM_S_GENERAL_NOTIFY
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];                      /**< 消息发送者 */ 
    TUP_CHAR content[IM_D_MAX_ACCOUNT_LENGTH];                      /**< 消息接收者 */ 
    IM_E_IM_GENERAL_NOTIFY_TYPE    flag;                            /**< 消息通知类型 */ 
}IM_S_GENERAL_NOTIFY;
/**
 *  讨论组添加或删除语音用户请求
 */
typedef struct tagIM_S_IMGROUPPHONEMEMBER_OP_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_S_LIST*    phonelist;                                       /**< 号码列表  TUP_S_LIST中的*dada结构类型为TUP_CHAR*/ 
}IM_S_IMGROUPPHONEMEMBER_OP_ARG;

/** 
 * 退出讨论组响应
 */
typedef struct tagIM_S_LEAVE_DISCUSSGROUP_ACK
{
    TUP_CHAR    target[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 接受者账号 */
    TUP_CHAR    groupid[IM_D_GENEAL_LENGTH];                        /**< 讨论组ID */
    IM_E_LEAVEGROUP_FLAG    flag;                                   /**< 主动离开或者踢出群标识 */
    IM_E_LEAVEGROUP_RESULT    result;                               /**< 操作结果 */
    IM_E_IMGROUP_TYPE    grouptype;                                 /**< 群组类型 */
}IM_S_LEAVE_DISCUSSGROUP_ACK;

/**
 *  查询会议列表请求
 */
typedef struct tagIM_S_GETCONFERENCELISTARG
{
    TUP_INT16    count;                                             /**< 查询的数量 */
    TUP_INT16    pageNo;                                            /**< 查询第几页 */
}IM_S_GETCONFERENCELISTARG;

/**
 *  查询会议列表结果响应
 */
typedef struct tagIM_S_GETCONFERENCELISTACK
{
    TUP_INT        totalCount;                                      /**< 总记录数 */
    TUP_S_LIST*    meetingList;                                     /**< 会议列表  TUP_S_LIST中的*dada结构类型为IM_S_MEETINGINFO*/
}IM_S_GETCONFERENCELISTACK;

/**
 *  请求获取系统URL消息响应
 */
typedef struct tagIM_S_SYSURLS_NOTIFY
{
    TUP_CHAR    userPortalUrl[IM_D_IP_LENGTH];                      /**< 个人portal地址 */
    TUP_CHAR    updateServerAddr[IM_D_IP_LENGTH];                   /**< 自动升级服务器地址 */
    TUP_CHAR    establishAnAccountHelpUrl[IM_D_IP_LENGTH];          /**< 开户指导链接 */
    TUP_CHAR    userHelpUrl[IM_D_IP_LENGTH];                        /**< 用户帮助链接 */
    TUP_CHAR    forgetPwdUrl[IM_D_IP_LENGTH];                       /**< 忘记密码链接 */
    TUP_CHAR    loginFailedUrl[IM_D_IP_LENGTH];                     /**< 登陆失败链接 */
    TUP_CHAR    vpnNames[IM_D_IP_LENGTH];                           /**< 服务器提供的VPN接入名 */
    TUP_CHAR    downloadUrl[IM_D_IP_LENGTH];                        /**< 客户端直接下载链接 */
    TUP_CHAR    updateReportUrl[IM_D_IP_LENGTH];                    /**< 客户端上报服务器地址 */
    TUP_CHAR    netErrorUrl[IM_D_IP_LENGTH];                        /**< 网络错误链接 */
}IM_S_SYSURLS_NOTIFY;

/**
 *  退出登录响应
 */
typedef struct tagIM_S_LOGOUT_NOTIFY
{
    TUP_BOOL    LogOutRet;                                          /**< 用户退出结果 */
}IM_S_LOGOUT_NOTIFY;

/**
 *  其他用户添加自己为好友成功的通知
 */
typedef struct tagIM_S_ADDFRIEND_NOTIFY
 {
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 对方好友帐号 */
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< 对方显示名 */
    TUP_INT64    serverMsgID;                                       /**< 服务器消息ID */
 }IM_S_ADDFRIEND_NOTIFY;

/**
 *  好友状态变化通知
 */
typedef struct tagIM_S_USERSTATUS_NOTIFY
 {
    IM_E_USER_ONLINESTATUS    status;                               /**< 更新后的状态 */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**< 状态描述 */
    TUP_CHAR    origin[IM_D_MAX_ACCOUNT_LENGTH];                    /**< 状态变化成员帐号 */
    IM_E_CLIENT_TYPE    clientType;                                 /**< 客户端类型 */
    TUP_CHAR    clientDesc[IM_D_MAX_DESC_LENGTH];                   /**< 客户端描述 */
 }IM_S_USERSTATUS_NOTIFY;

/**
 *  好友信息变化通知
 */
typedef struct tagIM_S_USERINFOCHANGE_LIST_NOTIFY
{
    TUP_S_LIST* userInfoList;                                       /**< 用户列表 TUP_S_LIST中的*dada结构类型为IM_S_USERINFO */
}IM_S_USERINFOCHANGE_LIST_NOTIFY;

/**
 *  用户收到固定群管理员邀请加入固定群通知
 */
typedef struct tagIM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 群组名ID */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**< 管理员帐号 */ 
    TUP_CHAR    adminName[IM_D_MAX_NAME_LENGTH];                    /**< 管理员名称 */
    TUP_INT64    serverMsgID;                                       /**< 服务器消息ID */
}IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY;

/**
 *  管理员收到用户申请加入群组通知
 */
typedef struct tagIM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 群组名ID */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< 申请者帐号 */ 
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**< 申请者名称 */ 
    TUP_INT64    serverMsgID;                                       /**< 服务器消息ID */
}IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY;

/**
 *  获取固定群或讨论组详情响应消息（已废弃，不会使用）
 */
typedef struct tagIM_S_GETIMGROUPDETAIL_NOTIFY
{
    IM_S_IMGROUPINFO    imGroupInfo;                                /**< 固定群结构体 */
}IM_S_GETIMGROUPDETAIL_NOTIFY;


/**
 *  群成员收到管理员审批加入固定群通知的响应
 */
typedef struct tagIM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY
{
    TUP_BOOL    agreeJoin;                                          /**< 管理员是否同意成员的申请 */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 固定群ID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 固定群名ID */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**< 管理员的帐号  */ 
    TUP_CHAR    adminName[IM_D_MAX_NAME_LENGTH];                    /**< 管理员的名称 */ 
}IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY;

/**
 *  固定群变更通知
 */
typedef struct tagIM_S_IMGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**<  固定群ID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**<  固定群名 */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**<  管理员帐号 */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**<  新增或删除的成员帐号 */ 
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**<  新增或删除的成员姓名 */ 
    TUP_INT64    serverMsgID;                                       /**<  服务器消息ID */
}IM_S_IMGROUP_NOTIFY;

/**
 *  语音用户的号码
 */
typedef struct tagIM_S_PHONENUM
{
    TUP_CHAR    phoneNum[IM_D_GENEAL_LENGTH];                       /**<  号码内容 */        
}IM_S_PHONENUM;

/**
 *  讨论组变更通知
 */
typedef struct tagIM_S_DISCUSSGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 讨论组ID */ 
    TUP_S_LIST*    phonelist;                                       /**< 号码列表  TUP_S_LIST中的*dada结构类型为TUP_CHAR */            
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< 讨论组名称 */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**< 管理员帐号 */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< 新增或删除的成员帐号 */ 
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**< 新增或删除的成员姓名 */ 
}IM_S_DISCUSSGROUP_NOTIFY;


/**
 *  系统公告通知
 */
typedef struct tagIM_S_SYSTEMBULLETIN_NOTIFY
{
    IM_S_CHATINFO_NOTIFY chatInfo;                                  /**< 文本信息 */
}IM_S_SYSTEMBULLETIN_NOTIFY;

/**
 *  收到其他用户打字输入状态消息
 */
typedef struct tagIM_S_SENDIMINPUT_NOTIFY
{
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 发送者账号 */
    IM_E_IM_CHAT_STATUS    status;                                  /**< IM聊天输入状态 */
}IM_S_SENDIMINPUT_NOTIFY;

/**
 *  新即时文本消息通知
 */
typedef struct tagIM_S_CODECHAT_NOTIFY
{
    IM_S_CHATINFO_NOTIFY chatInfo;                                  /**< 文本信息 */
}IM_S_CODECHAT_NOTIFY;

/**
 *  新即时文本消息通知（批量） 
 */
typedef struct tagIM_S_CHATLIST_NOTIFY
{
    TUP_S_LIST*    chatList;                                        /**< 批量文本信息  TUP_S_LIST中的*dada结构类型为IM_S_CODECHAT_NOTIFY */
    TUP_INT        total;                                           /**< 未读消息总数 */
    TUP_INT64    minMsgID;                                          /**< 最小消息ID */
    TUP_INT64    maxMsgID;                                          /**< 最大消息ID */
}IM_S_CHATLIST_NOTIFY;

/**
 *  自定义头像的图片信息 
 */
typedef struct tagIM_S_IMAGEINFO
{
    TUP_INT        length;                                          /**< 头像图片文件内容长度，服务器没有大小限制，推荐阈值为2MB */
    TUP_CHAR*    data;                                              /**< 头像图片文件内容 */
}IM_S_IMAGEINFO;

/**
 *  获取其他用户自定义头像的图片信息响应 
 */
typedef struct tagIM_S_USERIMAGEINFO
{
    IM_S_IMAGEINFO    imagebits;                                    /**< 头像数据 */
    TUP_CHAR    id[IM_D_MAX_ACCOUNT_LENGTH];                        /**< 用户账号 */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 时间戳 */
}IM_S_USERIMAGEINFO;

/**
 *  获取其他用户的自定义头像请求
 */
typedef struct tagIM_S_IMAGEREQARG
{
    TUP_CHAR    id[IM_D_MAX_ACCOUNT_LENGTH];                        /**< 获取的用户账号 */
    TUP_CHAR    timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< 同步时间戳，19000000000000（年月日时分秒） */
}IM_S_IMAGEREQARG;

/**
 *  通知服务器自己的状态变化请求
 */
typedef struct tagIM_S_STATUSARG
{
    IM_E_USER_ONLINESTATUS    status;                                /**< 新状态 */
    TUP_CHAR    desc[IM_D_MAX_STATUS_DESCLEN];                       /**< 状态描述 */
}IM_S_STATUSARG;

/**
 *  用户多终端登录/退出通知
 */
typedef struct tagIM_S_MULTIDEVICE_NOTIFY
{
    TUP_CHAR    user[IM_D_MAX_ACCOUNT_LENGTH];                       /**< 用户账号 */
    TUP_INT64    eventTime;                                          /**< 用户登陆、退出时间：UTC格式，精确到毫秒 */
    IM_E_CLIENT_TYPE    clientType;                                  /**< 设备类型 */
    IM_E_CLIENT_OPT_TYPE    eventType;                               /**< 事件类型 */
    TUP_CHAR    appID[IM_D_GENEAL_LENGTH];                           /**< 该多终端的登录应用ID（缺省参数，暂不开放） */
}IM_S_MULTIDEVICE_NOTIFY;

/**
 *  用户被踢通知
 */
typedef struct tagIM_S_KICKOUT_NOTIFY
{
    TUP_CHAR    userAccount[IM_D_MAX_ACCOUNT_LENGTH];                /**< 用户账号 */
    IM_E_EXITSTATUS    exitFlag;                                     /**< 用户被踢下线原因 */
}IM_S_KICKOUT_NOTIFY;

/**
 *  多媒体会议信息
 */
typedef struct tagIM_S_MEETINGINFO
{
    TUP_CHAR    id[IM_D_GENEAL_LENGTH];                             /**< 会议ID */
    TUP_INT     status;                                             /**< 会议状态 */
    TUP_CHAR    subject[IM_D_MAX_DESC_LENGTH];                      /**< 会议主题 */
    TUP_CHAR    duration[IM_D_MAX_DESC_LENGTH];                     /**< 会议时段 */
    TUP_CHAR    startTime[IM_D_MAX_DESC_LENGTH];                    /**< 会议开始时间 */
    TUP_INT     holdTime;                                           /**< 会议持续时间 */
    TUP_CHAR    convenerAccount[IM_D_MAX_ACCOUNT_LENGTH];           /**< 会议召集人账号 */
    TUP_CHAR    convenerName[IM_D_MAX_NAME_LENGTH];                 /**< 会议召集人姓名 */
    TUP_INT     isForward;                                          /**< 是否是转发会议 */
    TUP_CHAR    forwarderAccount[IM_D_MAX_ACCOUNT_LENGTH];          /**< 转发会议人账号 */
    TUP_CHAR    forwarderName[IM_D_MAX_ACCOUNT_LENGTH];             /**< 转发会议人姓名 */
    TUP_S_LIST* attendees;                                          /**< 与会者姓名  TUP_S_LIST中的*dada结构类型为IM_S_USERINFO*/
    TUP_CHAR    agenda[IM_D_MAX_DESC_LENGTH];                       /**< 会议议程 */
    TUP_CHAR    accessNumber[IM_D_MAX_PASSWORD_LENGTH];             /**< 会议接入号 */
    TUP_CHAR    securityCode[IM_D_MAX_PASSWORD_LENGTH];             /**< 会议安全码 */
    TUP_CHAR    convenerTimezone[IM_D_MAX_DESC_LENGTH];             /**< 召集人预订会议时的时区 */
    TUP_INT     confType;                                           /**< 会议类型 （0：缺省值）*/
    TUP_CHAR    chairman[IM_D_MAX_NAME_LENGTH];                     /**< 会议主席名字 */
    TUP_CHAR    chairmanAccount[IM_D_MAX_ACCOUNT_LENGTH];           /**< 会议主席账号 */
    TUP_CHAR    meetingroom[IM_D_MAX_DESC_LENGTH];                  /**< 会议会场  */
    TUP_CHAR    translateAccessNumber[IM_D_MAX_PASSWORD_LENGTH];    /**< 会议接入码 */
    TUP_CHAR    mediaType[IM_D_MAX_STATUS_DESCLEN];                 /**< 媒体类型 */
}IM_S_MEETINGINFO;


/**
 *  最近会话信息
 */
typedef struct tagIM_S_RECENT_CONVERSATION_INFO
{
    IM_E_IM_RECENT_CONVERSATION_TYPE  type;                         /**< 会话类型 */
    TUP_CHAR    id[IM_D_GENEAL_LENGTH];                             /**< staffid/groupid */
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< 账号 */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< name/群名 */
    TUP_CHAR    nativeName[IM_D_MAX_NAME_LENGTH];                   /**< 本地名字 */
    TUP_INT64    imageID;                                           /**< 用户头像ID */
    TUP_INT64    utctTime;                                          /**< 该会话UTC时间 */
    TUP_INT8    code;                                               /**< 消息码*/
    TUP_BOOL    isRead;                                             /**< 消息是否已读*/
    IM_S_CHATINFO_NOTIFY    chatInfo;                               /**< chat消息 */  
    IM_S_SMSINFO            smsInfo;                                /**< sms消息 */ 
}IM_S_RECENT_CONVERSATION_INFO;


/**
 *  删除最近会话请求消息
 */
typedef struct tagIM_S_DEL_RECENT_CONVERSATION_ARG
{
    TUP_BOOL    isDelAll;                                           /**< 是否删除所有，删除所有: true, 删除单个: false*/
    TUP_CHAR    conversationID[IM_D_MAX_ACCOUNT_LENGTH];            /**< 最近会话标识：用户账号、群id或号码 */
    IM_E_IM_RECENT_CONVERSATION_TYPE  type;                         /**< 最近会话类型 */
}IM_S_DEL_RECENT_CONVERSATION_ARG;


/**
 *  获取最近会话请求消息
 */
typedef struct tagIM_S_GEL_RECENT_CONVERSATION_ARG
{
    TUP_INT64   timestamp;                                          /**< 时间戳，19000000000000（年月日时分秒） */
    TUP_INT32   count;                                              /**< 请求最近会话个数*/
}IM_S_GEL_RECENT_CONVERSATION_ARG;


/**
 *  获取最近会话响应消息
 */
typedef struct tagIM_S_GEL_RECENT_CONVERSATION_ACK
{
    TUP_INT64    timestamp;                                         /**< 时间戳，19000000000000（年月日时分秒） */
    TUP_S_LIST*    recentConversationList;                          /**< 最近会话信息列表，TUP_S_LIST中的*dada结构类型为IM_S_RECENT_CONVERSATION_INFO*/
}IM_S_GEL_RECENT_CONVERSATION_ACK;

/**
 *  更新联系人分组列表
 */
typedef struct tagIM_S_UPDATE_USERGROUP_ARG
{
    TUP_S_LIST*    usergrouplist;                                   /**< 好友分组号列表，TUP_S_LIST中的*dada结构类型为TUP_INT64 */
}IM_S_UPDATE_USERGROUP_ARG;

/**
 *  固化讨论组请求/响应
 */
typedef struct tagIM_S_SET_DISGROUP_POLICY_MSG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 群ID */ 
    IM_E_IMGROUP_ISFIXDISCUSS    policy;                            /**< 是否固化讨论组 */     
}IM_S_SET_DISGROUP_POLICY_MSG;

/**
 *  讨论组操作消息
 */
typedef struct tagIM_S_SEND_DISGROUP_OPT_MSG
{
    IM_E_DISGROUP_OP_TYPE    type;                                  /**< 操作类型 */ 
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< 讨论组ID */ 
    TUP_S_LIST* params;                                             /**< 参数列表 TUP_S_LIST中的*dada结构类型为TUP_CHAR*，长度为IM_D_MAX_NAME_LENGTH*/ 
}IM_S_SEND_DISGROUP_OPT_MSG;

//--------------------------------------------------------------参数结构体 end--------------------------------------------------------------

//--------------------------------------------------------------回调函数 begin--------------------------------------------------------------
/**
 * @brief 需要用户声明和实现的回调函数
 * @param [in]  eventID 事件ID
 * @param [in] body 消息体
 * @attention 回调消息在此函数中接收
 * @return TUP_VOID
 */
typedef TUP_BOOL (*TUP_IM_FN_CALLBACK_PTR)(IM_E_EVENT_ID eventID, void *body);
//--------------------------------------------------------------回调函数 end--------------------------------------------------------------

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif//_TUP_IM_BASEDEF_H_

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
