/** 
* @file call_advanced_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP 呼叫子系统高级业务定义头文件。 \n
*/


/**
*
*  @{
*/
 

#ifndef __CALL_ADVANCED_DEF_H__
#define __CALL_ADVANCED_DEF_H__

/*******************************************************************************
 *   本文件需要包含的其它头文件
 *******************************************************************************/
#include "tup_def.h"
#include "call_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#define CALL_D_MAX_STR_LENGTH                       (256)   /**< 通用字符串最大长度 */
#define CALL_D_512_STR_LENGTH                       (512)   /**< 512字节长度 */
#define CALL_D_256_STR_LENGTH                       (256)   /**< 256字节长度 */
#define CALL_D_128_STR_LENGTH                       (128)   /**< 128字节长度 */
#define CALL_D_64_STR_LENGTH                        (64)    /**< 64字节长度 */
#define CALL_D_32_STR_LENGTH                        (32)    /**< 32字节长度 */
#define CALL_D_16_STR_LENGTH                        (16)    /**< 16字节长度 */

#define CALL_D_AUDIO_EQ_MAX_BANDS                   (10)    /**< 音频EQ BAND最大数*/
#define CALL_D_MAX_LOCAL_CONFER_CALL_NUM            (5)     /**< 最大会议路数*/

#define CALL_D_MAXNUM_GET_MEETING_INFO_PER_PAGE     (10)    /**< GET CONF LIST 每次获得的最大MEETING 信息个数*/
#define CALL_D_CONF_MAX_PW_LEN                      (10)    /**< 会议与会者密码最大长度 */
#define CALL_D_MAX_BITFLAG_LEN                      (33)    /**< 会议扩展标识长度 */
#define CALL_D_MAX_SERVERCONF_ATTENDEE              (20)    /**< 与会者最大个数 */

#define CALL_D_MAX_HISTORY_NUM                      (5)     /**< 历史记录最大数，用于IMS前转*/
#define CALL_D_MAX_FOWARD_NUM                       (24)    /**< 最大前转控制块处理个数*/
#define CALL_D_MAX_UM_MSG_LENGTH                (4 * 1024)  /**< UM消息最大字节长度*/


#define CALL_D_MAX_PAGING_NUM                       (10)    /**< Paging组最大值 */
#define CALL_D_MAX_HUNTGROUP_NUM                    (10)    /**< HuntGroup组最大值 */

#define CALL_D_MAX_PRESET_MSG_LENGTH                (100)   /**< 预设消息字符串最大长度 */
#define CALL_D_MAX_NAMESPACE                        (12)    /**< APP名字空间最大长度 */

#define CALL_D_EADDR_ENTERPRISE_STAFFNO_LEN         (32)    /**< 工号最大长度*/
#define CALL_D_EADDR_ENTERPRISE_STAFFACCOUNT_LEN    (128)   /**< 账号最大长度*/
#define CALL_D_EADDR_ENTERPRISE_NAME_LEN            (128)   /**< 姓名最大长度*/
#define CALL_D_EADDR_ENTERPRISE_NUM_LEN             (33)    /**< 号码最大长度*/
#define CALL_D_EADDR_ENTERPRISE_DEPT_LEN            (256)   /**< 部门名字最大长度*/
#define CALL_D_EADDR_ENTERPRISE_COMMON_LEN          (128)   /**< 通用最大长度*/
#define CALL_D_EADDR_ENTERPRISE_EMAIL_LEN           (256)   /**< EMAIL最大长度*/
#define CALL_D_EADDR_ENTERPRISE_URI_LEN             (128)   /**< URI最大长度*/
#define CALL_D_EADDR_ENTERPRISE_AVATARID_LEN        (144)   /**< 头像ID最大长度 */
#define CALL_D_EADDR_ENTERPRISE_ADDRESS_LEN         (256)    /**< 地址最大长度*/

#define CALL_CONF_SUBJECT_MAX_STR_LEN               (1024)  /**< 会议主题最大长度*/


/**
 * 设置视频会议预览时，使用的结构体
 */
typedef struct tagCALL_S_VIDEOCONF_VIDEO_PARAM
{
    TUP_UINT32 xResolution;     /**< x分辨率(宽) */
    TUP_UINT32 yResolution;     /**< y分辨率(高) */
    TUP_UINT32 nBitRate;        /**< 码率*/
} CALL_S_VIDEOCONF_VIDEO_PARAM;


/**
 * 视频会议设备拔插
 */
typedef enum tagCALL_E_VIDEOCONF_DEVICE_INPUT_STATUS
{
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_START,     /**< 无效  */
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_INPUT,     /**< 插入  */
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_OUTPUT,    /**< 拔出  */
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_BUTT       /**< 无效值  */
} CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS;


/** 
 * 视频会议设备状态
 */
typedef enum tagCALL_E_VIDEOCONF_DEVICE_STATUS
{
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_CLOSE = 0, /**< 关闭状态  */
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_OPEN = 1,  /**< 打开状态  */
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_RESUME = 2,/**< 恢复  */
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_PAUSE = 4, /**< 暂停  */
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_ERROR = 5, /**< 错误状态  */
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_BUTT       /**< 无效值  */
} CALL_E_VIDEOCONF_DEVICE_STATUS;


/** 
 * 企业地址本类型
 */
typedef enum tagCALL_E_EUA_TYPE
{
    CALL_E_EUA_TYPE_INVALID = 0,                    /**< 无效类型 */
    CALL_E_EUA_TYPE_FTP,                            /**< FTP类型 */
    CALL_E_EUA_TYPE_LDAP                            /**< LDAP类型 */
}CALL_E_EUA_TYPE;


/** 
 * 视频会议双流状态
 */
typedef struct tagCALL_S_VIDEOCONF_DOUBLESTREAM_STATUS
{
    TUP_CHAR szAttendNum[CALL_D_MAX_STR_LENGTH];    /**< 与会者号码 */ 
    TUP_UINT32 xResolution;                         /**< x分辨率(宽)  */
    TUP_UINT32 yResolution;                         /**< y分辨率(高)  */
    TUP_UINT32 bHighOrLowChannel;                   /**< 当前加入到高流还是低流  */
    TUP_UINT32 bDoubleStream;                       /**< 是否双流  */
    TUP_BOOL bOwnLowStream;                         /**< 是否还拥有低流  */
    TUP_BOOL bFlowCtrl;                             /**< 是否是流控告警引起  */
} CALL_S_VIDEOCONF_DOUBLESTREAM_STATUS;


/** 
 * 通用IPT业务信息描述
 */
typedef struct tagCALL_S_SERVICE_INFO
{
    TUP_UINT32   ulRight;                                           /**< 业务权限状态 @see tagCALL_E_SEVICERIGHT_STATUS */
    TUP_UINT32   ulRegister;                                        /**< 业务登记状态 @see tagCALL_E_SEVICEREGISTER_STATUS */
    TUP_CHAR     acActiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];  /**< 登记特征码 */
    TUP_CHAR     acDeactiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];/**< 注销特征码 */
} CALL_S_SERVICE_INFO;



/**
 * IPT业务配置信息
 */
typedef struct tagCALL_S_SERVICE_PARAM
{
    TUP_CHAR         acCallForwardUnconditionNum[CALL_D_MAX_LENGTH_NUM];/**< 无条件前转号码 */
    TUP_CHAR         acCallForwardOnBusyNum[CALL_D_MAX_LENGTH_NUM];     /**< 遇忙前转号码 */ 
    TUP_CHAR         acCallForwardNoReplyNum[CALL_D_MAX_LENGTH_NUM];    /**< 无应答前转号码 */ 
    TUP_CHAR         acCallForwardOfflineNum[CALL_D_MAX_LENGTH_NUM];    /**< 离线前转号码 */ 
    TUP_CHAR         acVoiceMailGetNum[CALL_D_MAX_LENGTH_NUM];          /**< 语音邮箱提取号码 */
    TUP_CHAR         acTurnPhoneNum[CALL_D_MAX_LENGTH_NUM];             /**< 手机分机:转移到话机接入码 */
    TUP_CHAR         acTurnMobileNum[CALL_D_MAX_LENGTH_NUM];            /**< 手机分机:转移到手机接入码 */
    TUP_UINT32       ulEaddrSearchType;                                 /**< 企业地址薄查找类型，透传字段 */
    TUP_CHAR         acAbbrDial[CALL_D_ACCESSCODE_MAX_LENGTH];          /**< 缩位拨号业务特征码 */
    TUP_UINT32       ulVoiceMailSupportType;                            /**< 语音邮箱支持类型，预留字段，暂未使用 */
    TUP_CHAR         acVoiceMailNumber[CALL_D_MAX_LENGTH_NUM];          /**< 语音邮箱号码 */
    TUP_CHAR         acVoiceMailSPIN[CALL_D_MAX_LENGTH_NUM];            /**< 语音邮箱提取的SPIN号码 */
    TUP_UINT32       ulVVMHttpsSupport;                                 /**< vvm是否支持https */
    TUP_UINT32       ulCallLimitType;                                   /**< 密码限呼类型 */
    TUP_CHAR         acCallLimitCode[CALL_D_MAX_LENGTH_NUM];            /**< 密码限呼接入码 */
    TUP_UINT32       ulHotLineEnable;                                   /**< 热线使能标识 */
    TUP_CHAR         acHotLineNumber[CALL_D_128_STR_LENGTH];            /**< 热线号码 */
    TUP_UINT32       ulHotLineDelayTime;                                /**< 热线时延 */
    TUP_UINT32       ulHotLineType;                                     /**< 热线类型 */
    TUP_BOOL         bIsChangeCFUNum;                                   /**< 是否可配置无条件前转号码 */

} CALL_S_SERVICE_PARAM;


/** 
 * 呼控将接收到的message 解析出的meeting 消息转发给界面处理 TODO
 */
typedef struct tagCALL_S_UM_MEETING_MSG
{
    TUP_CHAR acMeetingTopic[CALL_D_MAX_STR_LENGTH];         /**< 会议主题*/
    TUP_CHAR acMeetingTime[CALL_D_64_STR_LENGTH];           /**< 会议时间*/
    TUP_CHAR acConvener[CALL_D_64_STR_LENGTH];              /**< 会议召集人*/
    TUP_CHAR acAttendee[CALL_D_MAX_SERVERCONF_ATTENDEE* CALL_D_64_STR_LENGTH];  /** 会议与会者,最大20人*/
    TUP_CHAR acHost[CALL_D_64_STR_LENGTH];                  /**< 主持人*/
    TUP_CHAR acHostID[CALL_D_64_STR_LENGTH];                /**< 主持人id*/
    TUP_CHAR acConfID[CALL_D_128_STR_LENGTH];               /**< 会议id*/
    TUP_CHAR acAccessNumber[CALL_D_64_STR_LENGTH];          /**< 会议接入码*/
    TUP_CHAR acSecurityCode[CALL_D_64_STR_LENGTH];          /**< 会议安全号，主席密码*/
    TUP_CHAR acStartDate[CALL_D_64_STR_LENGTH];             /**< 会议开始时间*/
    TUP_CHAR acValidityPeriodDate[CALL_D_64_STR_LENGTH];    /**< 会议有效时间*/
    TUP_CHAR acIMContent[CALL_D_MAX_STR_LENGTH * 2];        /**< 会议内容*/
} CALL_S_UM_MEETING_MSG;

/**
 * 业务权限能力集
 */
typedef struct tagCALL_S_SERVICERIGHT_CFG
{
    CALL_S_SERVICE_INFO   astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_BUTT];  /**< IPT业务信息描述表，与CALL_E_SERVICE_RIGHT_TYPE 对应 */
    CALL_S_SERVICE_PARAM  stServiceParam;           /**< IPT业务配置信息 */
    TUP_CHAR acIntercomNum[CALL_D_MAX_LENGTH_NUM];  /**< intercom号码 */
} CALL_S_SERVICERIGHT_CFG;


/**
 * 共享线路状态
 */
typedef enum tagCALL_E_SCASTATE
{
    CALL_E_SCASTATE_IDLE,                /**< 空闲状态 */
    CALL_E_SCASTATE_SEIZED,              /**< 占用状态 */
    CALL_E_SCASTATE_ALERTING,            /**< 来电振铃中 */
    CALL_E_SCASTATE_ACTIVE,              /**< 通话中 */
    CALL_E_SCASTATE_PROGRESSING,         /**< 呼出中 */
    CALL_E_SCASTATE_HELD,                /**< 保持状态 */
    CALL_E_SCASTATE_HELD_PRIVATE,        /**< 私人保持状态 */
    CALL_E_SCASTATE_BRIDGE_ACTIVE,       /**< bridge会议状态 */
    CALL_E_SCASTATE_LOCK,                /**< 私有化状态 */
    CALL_E_SCASTATE_TERM,                /**< 订阅终结*/
    CALL_E_SCASTATE_BUTT                 /**< 无效值  */
} CALL_E_SCASTATE;


/**
 * 本地会议会场状态
 */
typedef enum tagCALL_E_LOCAL_CONF_STATE
{
    CALL_E_LOCAL_CONF_STATE_IDLE,        /**< 会议空闲态 */
    CALL_E_LOCAL_CONF_STATE_INIT,        /**< 会议初始态 */
    CALL_E_LOCAL_CONF_STATE_LIVE,        /**< 会议激活态 */
    CALL_E_LOCAL_CONF_STATE_HOLD,        /**< 会议保持态 */
    CALL_E_LOCAL_CONF_STATE_END,         /**< 会议结束态 */
    CALL_E_LOCAL_CONF_STATE_BUTT         /**< 会议无效态 */
} CALL_E_LOCAL_CONF_STATE;


/**
 * 本地会议的会议类型
 */
typedef enum tagCALL_E_LOCAL_CONF_TYPE
{
    CALL_E_LOCAL_CONFTYPE_HOLD,         /**< 添加与会者时会场被保持*/
    CALL_E_LOCAL_CONFTYPE_NOHOLD,       /**< 添加与会者时会场照常开会(无需保持会场)*/
    CALL_E_LOCAL_CONF_BUTT              /**< 无效值  */
} CALL_E_LOCAL_CONF_TYPE_ENUM;


/**
 * 与会者发言状态
 */
typedef enum tagCALL_E_LOCAL_CONFREE_TALK_STATE
{
    CALL_E_LOCAL_CONFREE_TALK_STATE_IDLE,       /**< 空闲态 */
    CALL_E_LOCAL_CONFREE_TALK_STATE_SPEAKING,   /**< 发言态 */
    CALL_E_LOCAL_CONFREE_STATE_BUTT             /**< 无效态 */
} CALL_E_LOCAL_CONFREE_TALK_STATE;


/** 
 * 密码限呼类型
 */
typedef enum tagCALL_E_CALL_LIMIT_TYPE
{
    CALL_E_CALL_LIMIT_NONE,                     /**< 不受限 */
    CALL_E_CALL_LIMIT_HOME,                     /**< 国内限呼 */
    CALL_E_CALL_LIMIT_INTERNATIONAL,            /**< 国际限呼 */
    CALL_E_CALL_LIMIT_BOTH,                     /**< 国内限呼+国际限呼 */
    CALL_E_CALL_LIMIT_BUTT                      /**< 无效值  */
} CALL_E_CALL_LIMIT_TYPE;


/**
 * 联系人状态
 */
typedef enum  tagCALL_E_CONTACT_STATUS
{
    CALL_E_CONTACT_STATUS_OFFLINE,       /**< 离线，出现场景---软终端、硬终端、CC上报、BLF(Subscription-State: terminated;reason=probation) */
    CALL_E_CONTACT_STATUS_ONLINE,        /**< 空闲，出现场景---软终端、硬终端、BLF(terminated) */
    CALL_E_CONTACT_STATUS_BUSY,          /**< 忙碌，出现场景---软终端 */
    CALL_E_CONTACT_STATUS_LEAVE,         /**< 离开，出现场景---软终端 */
    CALL_E_CONTACT_STATUS_DND,           /**< DND ，出现场景---软终端、硬终端 */
    CALL_E_CONTACT_STATUS_CALLING,       /**< 通话中，出现场景---软终端、硬终端、CC上报、BLF(confirmed) */
    CALL_E_CONTACT_STATUS_BUSY_CALLING,  /**< 呼叫中，出现场景---待定 */
    CALL_E_CONTACT_STATUS_BUSY_MEETING,  /**< 服务器会议中 */

    CALL_E_CONTACT_STATUS_RINGING,       /**< 振铃响铃，出现场景---CC上报、BLF(early) */
    CALL_E_CONTACT_STATUS_DAILNUM,       /**< 摘机拨号，出现场景---CC上报 */
    CALL_E_CONTACT_STATUS_OFFHOOK,       /**< 摘机，出现场景---CC上报 */
    CALL_E_CONTACT_STATUS_ONHOOK,        /**< 挂机，出现场景---CC上报 */

    CALL_E_CONTACT_STATUS_UNDND,         /**< 取消DND ，出现场景---软终端、硬终端，不用于发布! */
    CALL_E_CONTACT_STATUS_UNBUSY,        /**< 取消忙碌，不用与发布! */

    CALL_E_CONTACT_STATUS_UNKNOWN,       /**< 未知状态  */
    CALL_E_CONTACT_STATUS_PHONE_ONLINE,  /**< 话机在线  */
    CALL_E_CONTACT_STATUS_PROCEEDING,    /**< 呼出中,对接USM新增状态 */
    CALL_E_CONTACT_STATUS_BUTT           /**< 无效状态 */
} CALL_E_CONTACT_STATUS;


/** 
 * 服务器会议类型
 */
typedef enum tagCALL_E_CONFTYPE
{
    CALL_E_CONFTYPE_PRERECE_VOICE = 10,  /**< 融合会议语音*/
    CALL_E_CONFTYPE_PRERECE_VIDEO,       /**< 融合会议视频*/
    CALL_E_CONFTYPE_PRERECE_MULTIMEDIA,  /**< 融合会议多媒体*/
    CALL_E_CONFTYPE_UC_VOICE,            /**< UC语音会议*/
    CALL_E_CONFTYPE_UC_VIDEO,            /**< UC及时视频会议*/
    CALL_E_CONFTYPE_UC_MULTIMEDIA,       /**< UC多媒体会议*/
    CALL_E_CONFTYPE_BUTT                 /**< 无效值  */
} CALL_E_CONFTYPE;


/** 
 * 是否显示软终端号码
 */
typedef enum tagCALL_E_LINKAGE_STATE 
{
    CALL_E_LINKAGE_STATE_DISPSOFTTEL,      /**< 显示 */
    CALL_E_LINKAGE_STATE_NOT_DISPSOFTTEL,  /**< 不显示 */
    CALL_E_LINKAGE_STATE_BUTT              /**< 无效值  */
}CALL_E_LINKAGE_STATE;


/**
 * 认证方式
 */
typedef enum tagCALL_E_AUTH_TYPE 
{
    CALL_E_AUTH_TYPE_NO,        /**< 动态注册未认证 */
    CALL_E_AUTH_TYPE_LOCAL,     /**< 本地注册 */
    CALL_E_AUTH_TYPE_EXTERNAL,  /**< 外部注册 */     
    CALL_E_AUTH_TYPE_BUTT       /**< 无效值  */
}CALL_E_AUTH_TYPE;


/**
 * 联系人信息
 */
typedef struct tagCALL_S_CONTACT_INFO
{
    TUP_UINT32  ulIndex;                                            /**< 当前查找线路标识 */
    TUP_INT8    StaffAccount[CALL_D_EADDR_ENTERPRISE_STAFFACCOUNT_LEN]; /**< UC账号 */
    TUP_INT8    PersonName[CALL_D_EADDR_ENTERPRISE_NAME_LEN];       /**< 姓名 */
    TUP_UINT32  Sex;                                                /**< 性别 */
    TUP_INT8    Staffno[CALL_D_EADDR_ENTERPRISE_STAFFNO_LEN] ;      /**< 工号 */
    TUP_INT8    IPNum[CALL_D_EADDR_ENTERPRISE_NUM_LEN];             /**< IP号码 */
    TUP_INT8    DeptName[CALL_D_EADDR_ENTERPRISE_DEPT_LEN];         /**< 部门名字 */
    TUP_INT8    Title[CALL_D_EADDR_ENTERPRISE_COMMON_LEN];          /**< 职务 */
    TUP_INT8    CellPhone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];         /**< 手机号码 */
    TUP_INT8    Seatphone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];         /**< 座机号码 */
    TUP_INT8    Otherphone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];        /**< 其余号码 */
    TUP_INT8    Otherphone2[CALL_D_EADDR_ENTERPRISE_NUM_LEN];       /**< 其余号码2 */
    TUP_INT8    homephone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];         /**< 家庭号码 */
    TUP_INT8    Email[CALL_D_EADDR_ENTERPRISE_EMAIL_LEN];           /**< email */
    TUP_INT8    Address[CALL_D_EADDR_ENTERPRISE_ADDRESS_LEN];       /**< 地址 */
    TUP_UINT32  ulState;                                            /**< 在线状态 TODO */
    TUP_INT8    acuriDomain[CALL_D_EADDR_ENTERPRISE_URI_LEN];       /**< 用户URI */
    TUP_INT8    acAvatarID[CALL_D_EADDR_ENTERPRISE_AVATARID_LEN];   /**< 头像ID */
    CALL_E_LINKAGE_STATE    enLinkageState;                         /**< 软终端号码显示状态 */
} CALL_S_CONTACT_INFO, *CALL_S_CONTACT_INFO_PTR;

/**
 * 联系人及其状态信息
 */
typedef struct tagCALL_S_CONTACT_STATUS
{
    TUP_UINT32 ulSipAccountID;                      /**< 账号ID */
    TUP_CHAR acNo[CALL_D_EADDR_ENTERPRISE_NUM_LEN]; /**< 号码 */
    CALL_E_CONTACT_STATUS enContactStatus;          /**< 状态 */
} CALL_S_CONTACT_STATUS, *CALL_S_CONTACT_STATUS_PTR;


/** 
 * 状态信息
 */
typedef struct tagCALL_S_STATUS
{
    TUP_UINT32 ulNum;                       /**< 联系人及其状态信息个数 */
    CALL_S_CONTACT_STATUS* pstStatus;       /**< 联系人及其状态信息数组 */
} CALL_S_STATUS, *CALL_S_STATUS_PTR;


/**
 * 联系人状态通知
 */
typedef struct tagCALL_S_CONTACT_NTF
{
    TUP_UINT8  ucContactNameLen;            /**< 联系人别名长度 */
    TUP_UINT8  ucOnlineState;               /**< 在线状态: 1-空闲，其他-繁忙 */
    TUP_UINT8  ucProtocolType;              /**< 协议类型 0-H323, 2-SIP */
    TUP_CHAR   acContactName[CALL_D_256_STR_LENGTH]; /**< 联系人别名 */
}CALL_S_CONTACT_NTF, *CALL_S_CONTACT_NTF_PTR;


/**
 * 在线状态订阅通知(智真huawei_ido)
 */
typedef struct tagCALL_S_IDO_ONLINE
{
    TUP_UINT32 ulErrCode;               /**< 错误码定义:0-成功，0x1-未开启在线功能 0x2-在线终端数过多 0xffffffff-系统内部错误 */
    TUP_BOOL bIsLastPack;               /**< 是否最后一包 */
    TUP_UINT16 uContactCount;           /**< 账号个数 */
    CALL_S_CONTACT_NTF *pstContactInfo; /**< 联系人信息 */
}CALL_S_IDO_ONLINE, *CALL_S_IDO_ONLINE_PTR;


/**
 * 网络地址本订阅通知(智真huawei_ido)
 */
typedef struct tagCALL_S_IDO_NETADDRESS
{
    CALL_E_EUA_TYPE eEUAType;                       /**< EUA类型 ftp 或者 ldap */
    TUP_CHAR  acAddress[CALL_D_512_STR_LENGTH];     /**< 服务器地址，多个地址用“;”隔开 */
    TUP_CHAR  acUserName[CALL_D_MAX_STR_LENGTH];    /**< 用户名 */
    TUP_UINT32 uiPasswordLen;                       /**< 口令长度 */
    TUP_CHAR  acPassword[CALL_D_MAX_STR_LENGTH];    /**< 口令 */
    TUP_CHAR  acFilePath[CALL_D_MAX_STR_LENGTH];    /**< 地址本文件路径 */
    TUP_CHAR  acDNValue[CALL_D_MAX_STR_LENGTH];     /**< DN值 */
    TUP_CHAR  acVersion[CALL_D_MAX_STR_LENGTH];     /**< 版本信息 */
}CALL_S_IDO_NETADDRESS, *CALL_S_IDO_NETADDRESS_PTR;


/** 账号被踢(智真huawei_ido) */
typedef struct tagCALL_S_IDO_FORCEUNREG
{
    TUP_BOOL   bIsKickOff;                              /**< 是否被踢，4字节 */
    TUP_UINT8  ucIpType;                                /**< 地址类型，1字节 */
    TUP_UINT8  acIpAddress[CALL_D_16_STR_LENGTH + 1];   /**< 地址，16字节*/
}CALL_S_IDO_FORCEUNREG, *CALL_S_IDO_FORCEUNREG_PTR;


/**
 * 同组代答通知上报消息携带的数据
*/
typedef struct tagCALL_S_TIPINFO
{
    TUP_CHAR acCallerNo[CALL_D_MAX_STR_LENGTH];   /**< 主叫号码 */
    TUP_CHAR acRingNo[CALL_D_MAX_STR_LENGTH];     /**< 振铃号码 */
} CALL_S_TIPINFO, *CALL_S_TIPINFO_PTR;


/**
 * 联动命令信息
 */
typedef struct tagCALL_S_JOINT_CMD_INFOS
{
    TUP_UINT32 ulSipAccountID;                  /**< 账号ID */
    TUP_UINT32 ulCallID;                        /**< 呼叫ID */
    TUP_UINT32 ulTransferOriginID;              /**< 联动中用于一键切换的呼叫ID */
    TUP_UINT32 ulConfID;                        /**< 会议ID */
    TUP_UINT32 ulLineID;                        /**< 线路ID */
    CALL_E_CALL_EVENT enJointCmdMsg;            /**< 消息类型 */
    TUP_CHAR acCallNum[CALL_D_MAX_STR_LENGTH];  /**< 电话号码 */
    TUP_UINT32  ulCallNumLen;                   /**< 电话号码长度 */
    TUP_UINT32 ulResult;                        /**< 0 : 成功，其他: 失败*/
} CALL_S_JOINT_CMD_INFOS;


/**
 * 联动加入融合会议上报通知消息结构
 */
typedef struct tagCALL_S_JOINMSCONF_INFO
{
    TUP_UINT32 ulSipAccountID;                      /**< 账号ID */
    TUP_UINT32 ulCallID;                            /**< 呼叫ID */
    TUP_UINT32 ulConfID;                            /**< 会议ID */
    CALL_E_CONFTYPE enConfType;                     /**< 会议类型 */
    TUP_CHAR acConfId[CALL_D_MAX_PASSCODE_LENGTH];  /**< 会议接入码 */ 
} CALL_S_JOINMSCONF_INFO;


#define CALL_D_CTD_BIND_NUM_MAX_LEN 255             /**< CTD绑定号码最大长度 */
#define CALL_D_CTD_ATTENDEE_MAX_NUM 64              /**< CTD与会者最大数 */


/**
 * CTD 通知消息结构
 */
typedef struct tagCALL_S_CTD_INFO_BODY
{
    TUP_UINT32   ulServiceType;     /**< 业务类型，对外暂无作用 */
    TUP_UINT32   ulCmdType;         /**< 命令类型，对外暂无作用 */
    TUP_UINT32   ulCtdCallId;       /**< CTD呼叫ID */
    TUP_CHAR     acAttendeeEid[CALL_D_CTD_ATTENDEE_MAX_NUM][CALL_D_CTD_BIND_NUM_MAX_LEN + 1]; /**< 预留，暂未使用 */
    TUP_UINT32   ulAttendeeNum;     /**< 预留，暂未使用 */
    TUP_CHAR     acCtdCallerNum[CALL_D_CTD_BIND_NUM_MAX_LEN + 1];   /**< CTD主叫号码 */
    TUP_CHAR     acCtdCalleeNum[CALL_D_CTD_BIND_NUM_MAX_LEN + 1];   /**< CTD被叫号码 */
}CALL_S_CTD_INFO_BODY;


/**
 * 音频EQ参数方向
 */
typedef enum tagCALL_E_EQ_PARAMS_DIRECTION
{
    CALL_E_EQ_PARAMS_DIRECTION_NONE = 0x00,
    CALL_E_EQ_PARAMS_DIRECTION_UP   = 0x01,       /**< 上行方向参数 */
    CALL_E_EQ_PARAMS_DIRECTION_DOWN = 0x02,       /**< 下行方向参数 */

    CALL_E_EQ_PARAMS_DIRECTION_INVALID = 0xff
}CALL_E_EQ_PARAMS_DIRECTION;


/**
 * 音频EQ参数
 */
typedef struct tagCALL_S_AUDIO_EQ_PARAMS
{
    TUP_INT32 iSampleRate;                           /**< 采样率，支持8000、16000、48000三种采样率*/

    TUP_INT32 iBand_Q[CALL_D_AUDIO_EQ_MAX_BANDS];    /**< 频率宽度，此数值为滤波器Q值对应的Q26定点值，要求如下
                                                        <br> 1、第一个滤波器与最后一个滤波器必须为搁架滤波器，中间为峰值滤波器
                                                        <br> 2、搁架滤波器Q值设置范围[0.03125, 0.70711]，对应Q26定点值[94906266, 2147483647]
                                                        <br> 3、峰值滤波器Q值设置范围[0.03125, 64]，对应Q26定点值[1048576, 2147483647]*/
    TUP_INT16 sBand_f0[CALL_D_AUDIO_EQ_MAX_BANDS];   /**< 可调频段中心频率，不同采样率、不同滤波器范围不同，要求如下:
                                                        <br> 采样率8K:低频搁架滤波器（第一频段）中心频率范围为:10Hz~2000Hz
                                                        <br> 峰值滤波器（中间频段）中心频率范围为:60Hz~3000Hz
                                                        <br> 高频搁架滤波器（最后频段）中心频率范围为:1000Hz~3800Hz
                                                        <br> 采样率16K:低频搁架滤波器（第一频段）中心频率范围为:10Hz~4000Hz
                                                        <br> 峰值滤波器（中间频段）中心频率范围为:60Hz~6000Hz
                                                        <br> 高频搁架滤波器（最后频段）中心频率范围为:1000Hz~7800Hz
                                                        <br> 采样率48K:低频搁架滤波器（第一频段）中心频率范围为:10Hz~8000Hz
                                                        <br> 峰值滤波器（中间频段）中心频率范围为:60Hz~16000Hz
                                                        <br> 高频搁架滤波器（最后频段）中心频率范围为:1000Hz~22000Hz */
    TUP_INT16 sDBgain[CALL_D_AUDIO_EQ_MAX_BANDS];    /**< 可调频段增益，设置范围[-24, 24]dB*/
                                                          
    TUP_INT32 iNBand;                                /**< 频段数，设置范围[0, 10]，0代表关闭EQ*/

    TUP_INT32 iACLPEnabled;                          /**< 削波模块标志: 1表示开启，0表示关闭*/

}CALL_S_AUDIO_EQ_PARAMS;


/**
 * 音频AEC参数
 */
typedef struct tagCALL_S_AUDIO_AEC_PARAMS
{
    TUP_UINT8   ucCngMode;              /**< 舒适噪声模式: 零关闭，非零打开，默认打开, */  
    TUP_UINT8   ucPureDelay;            /**< 纯迟延, 取值<br>0:0ms, 1:10ms, 2:20ms, 3:30ms, 4:40ms, 5:50ms, 6:60ms, 默认为0ms*/
    TUP_UINT16  usNearAllPassEnergy;    /**< 判断近端是否透传的远端能量阈值, 取值<br>0:-59dBm0, 1:-49dBm0, 2:-39dBm0, 默认为1 */
    TUP_UINT8   ucNearCleanSupEnergy;   /**< 判断近端是否为纯回声帧的阈值, 取值<br>0:12dB, 1:15dB, 2:18dB, 默认为2,  */
    TUP_UINT8   ucMode;                 /**< 话机模式，取值<br>0:听筒, 1:免提, 默认为听筒模式 */
    TUP_UINT8   ucSampleRate;           /**< 采样率, 取值<br>0:8K,1:16K,2:24K,3:48K, 默认为48K, 目前不支持24K采样率 */
}CALL_S_AUDIO_AEC_PARAMS;


/**
 * 音频EQ配置参数
 */
typedef struct tagCALL_S_AUDIO_EQ_CONFIG
{
    CALL_E_EQ_PARAMS_DIRECTION   eParamsDirection;  /**< 参数标志位，上行or下行 CALL_E_EQ_PARAMS_DIRECTION*/
    TUP_INT32 iMode;                                /**< EQ状态，非0表示打开EQ，0表示关闭EQ */
    CALL_S_AUDIO_EQ_PARAMS stEqCfg_8K;              /**< 采样率为8K时，EQ参数列表 */
    CALL_S_AUDIO_EQ_PARAMS stEqCfg_16K;             /**< 采样率为16K时，EQ参数列表 */
    CALL_S_AUDIO_EQ_PARAMS stEqCfg_48K;             /**< 采样率为48K时，EQ参数列表 */
    TUP_CHAR acVolMap[CALL_D_MAX_STR_LENGTH];       /**< 输出音量的调节范围映射表，用逗号分开每个值 */
    TUP_UINT32 ulMicVolume;                         /**< MIC音量设置[0-10000] */
}CALL_S_AUDIO_EQ_CONFIG;




/**
 * 当前服务器信息
 */
typedef struct tagCALL_S_CURRENT_SIPSERVER
{
    TUP_CHAR acCurrentRegAddress[CALL_D_MAX_STR_LENGTH];    /**< 当前使用的SIP注册服务器地址 */
    TUP_UINT32 ulCurrentRegPort;                            /**< 当前使用的SIP注册服务器端口 */

    TUP_CHAR acCurrentProxyAddress[CALL_D_MAX_STR_LENGTH];  /**< 当前使用的代理服务器地址 */
    TUP_UINT32 ulCurrentProxyPort;                          /**< 当前使用的代理服务器端口 */
} CALL_S_CURRENT_SIPSERVER;


/**
 * SIP地址信息
 */
typedef struct tagCALL_S_SIP_ADDR_INFO
{
    TUP_CHAR acSipAddress[CALL_D_64_STR_LENGTH];
    TUP_INT32 iPort;
} CALL_S_SIP_ADDR_INFO;


/**
 * 与会者信息
 */
typedef struct tagCALL_S_CONFEREE_INFO
{
    TUP_UINT32 ulCallID;                              /**< 与会者线路通话ID，无效ID为0xFFFFFFFF */
    TUP_BOOL bIsMuted;                                /**< 与会者是否被静音 */
    CALL_E_LOCAL_CONFREE_TALK_STATE enTalkState;      /**< 与会者说话状态 */
} CALL_S_CONFEREE_INFO;



/**
 * 与会者线路列表
 */
typedef struct tagCALL_S_CONFER_CALLID_LIST
{
    CALL_S_CONFEREE_INFO astConfereeList[CALL_D_MAX_LOCAL_CONFER_CALL_NUM];    /**< 与会者列表，*/
    TUP_UINT32 ulCnt;                                                          /**< 与会者人数 */
} CALL_S_CONFER_CALLID_LIST;



/**
 * 本地会议信息
 */
typedef struct tagCALL_S_CONFER_LOCAL_INFO
{
    TUP_UINT32 ulConfID;                          /**< 本地会议会场ID */
    TUP_UINT32 ulSipAccountID;                    /**< 本地会议主席SipID */
    TUP_UINT32 ulCreatorCallID;                   /**< 创建会场线路的CallID */
    TUP_UINT32 ulCreatorLineID;                   /**< 会议创建线路的ID */
    CALL_E_LOCAL_CONF_STATE   enConfState;        /**< 会场状态 */
    CALL_E_LOCAL_CONF_TYPE_ENUM enLocConfType;    /**< 本地会议类型*/
    CALL_S_CONFER_CALLID_LIST stConfCallIDList;   /**< 与会者CallID列表*/
} CALL_S_CONFER_LOCAL_INFO;



/**
 * Desktop菜单配置
 */
typedef struct tagCALL_S_SERVICE_EXTENSION_CFG
{
    TUP_UINT32 ulMessageButton;
    TUP_UINT32 ulEnableLogout;
} CALL_S_SERVICE_EXTENSION_CFG;


/** 
 * 代答主叫方信息
 */
typedef struct tagCALL_S_PICKUP_REMOTE_INFO
{
    TUP_CHAR acTelNum[CALL_D_MAX_STR_LENGTH];   /**<  指定代答主叫方号码 */
    TUP_CHAR acDisplayName[CALL_D_64_STR_LENGTH];  /**< 指定代答主叫方显示名称 */
} CALL_S_PICKUP_REMOTE_INFO;


/** 
 * 共享线状态(呼入 OR 呼出)
 */
typedef enum tagCALL_E_CALLINFO_ORIGINATE
{
    CALL_E_CALLINFO_ORIGINATE_FROM,                      /**< 共享线状态为外线呼入 */
    CALL_E_CALLINFO_ORIGINATE_TO,                        /**< 共享线状态为共享线呼出 */
    CALL_E_CALLINFO_ORIGINATE_BUTT,                      /**< 共享线状态来源未知 */
}CALL_E_CALLINFO_ORIGINATE;


/** 
 * 共享线呼叫信息
 */
typedef struct tagCALL_S_SCA_CALLINFO
{
    TUP_UINT32 ulSipAccountID;                      /**< 账户ID */
    TUP_UINT32 ulAppearanceIndex;                   /**< 线路号 */
    TUP_UINT32 ulAppearanceState;                   /**< 线路状态，
                                                         <br>0:空闲 1:占用 2:来电振铃 3:通话中 4:呼出中 5:保持中 
                                                         <br>6:私人保持中 7:bridge会议 8:私有化状态 9: 订阅终结 */
    CALL_E_CALLINFO_ORIGINATE enOriginateType;      /**< 共享线状态来源 */
    TUP_CHAR acDisplayName[CALL_D_MAX_DISPLAY_NAME];/**< 共享线通话信息显示名称 */
    TUP_CHAR acDisplayNum[CALL_D_MAX_LENGTH_NUM];   /**< 共享线通话信息显示号码 */
} CALL_S_SCA_CALLINFO;



/** 
 * Reinvite事件上报
 */
typedef enum
{
    CALL_E_REINVITE_PNOTIFICATION_NONE,             /**< 无效事件 */
    CALL_E_REINVITE_PNOTIFICATION_HOLD,             /**< 保持事件 */
    CALL_E_REINVITE_PNOTIFICATION_UNHOLD,           /**< 取消保持事件 */
    CALL_E_REINVITE_PNOTIFICATION_BUTT              /**< 无效值  */
} CALL_E_REINVITE_TYPE;


/**
 * 密码限呼登记原因码
 */
typedef enum tagCALL_E_CAUSE_RESON
{
    CALL_E_CAUSE_NORMAL = 0,        /**< 成功 */
    CALL_E_CAUSE_FAILURE,           /**< 失败 */
    CALL_E_CAUSE_LOCKED,            /**< 锁定 */
    CALL_E_CAUSE_NOLINE,            /**< 无可用线路 */
    CALL_E_CAUSE_BUSY,              /**< 用户忙 */
    CALL_E_CAUSE_BUTT               /**< 无效值  */
} CALL_E_CAUSE_RESON;


/**
 * 自动回呼信息结构
 */
typedef struct tagCALL_S_ACB_INFO
{
    TUP_UINT32 ulTime1;                             /**< 服务设置的回呼超时时间*/
    TUP_CHAR acCalleeNum[CALL_D_MAX_STR_LENGTH];    /**< 回呼号码 */
    TUP_UINT32 ulOverTime;                          /**< 回呼剩余时间 */
} CALL_S_ACB_INFO;


/**
 * 记录语音(录*音)结果通知信息结构
 */   
typedef struct tagCALL_S_RECORD_INFO
{
    TUP_BOOL bRecordStatus;         /**< 是否处于(录*音)状态 */
    TUP_BOOL bRecordRight;          /**< 是否有(录*音)权限 */
}CALL_S_RECORD_INFO;


/**
 * 业务登记状态
 */   
typedef enum tagCALL_E_SEVICEREGISTER_STATUS
{
    CALL_E_SEVICEREGISTER_LACK = 0,     /**< 没登记 */
    CALL_E_SEVICEREGISTER_HAVE          /**< 有登记 */
} CALL_E_SEVICEREGISTER_STATUS;


/**
 * 订阅状态
 */
typedef enum tagCALL_E_SUB_STATE
{
    CALL_E_SUB_STATE_UNSUB,     /**< 未订阅 */
    CALL_E_SUB_STATE_SUBING,    /**< 订阅中 */
    CALL_E_SUB_STATE_DESUBING,  /**< 去订阅中 */
    CALL_E_SUB_STATE_SUBED,     /**< 已订阅 */
    CALL_E_SUB_STATE_BUTT       /**< 订阅无效状态 */
} CALL_E_SUB_STATE;


/**
 * 线路类型
 */
typedef enum tagCALL_E_LINETYPE
{
    CALL_E_LINETYPE_NORMAL,     /**< 普通呼叫线路 */
    CALL_E_LINETYPE_SCA,        /**< 共享线线路 */
    CALL_E_LINETYPE_BUTT        /**< 无效值  */
} CALL_E_LINE_TYPE;


/**
 * 硬件(摄象头)参数
 */
typedef struct tagCALL_S_HARDWARE_PARAMS
{
    TUP_UINT32 ulBright;                /**< 亮度 [1,100]默认50 */
    TUP_UINT32 ulContrast;              /**< 对比度 [1,100]默认50 */
    TUP_UINT32 ulDigitalZoom;           /**< 数字变倍 [1,100]默认50 */

} CALL_S_HARDWARE_PARAMS;


/**
 * 自动回呼(ACB)登记业务数据
 */
typedef struct tagCALL_S_ACB_SERVICE_DATA
{
    TUP_CHAR   acACBCallNum[CALL_D_MAX_STR_LENGTH];      /**< 回呼号码 */
    TUP_UINT32 ulACBCallNumLenl;                         /**< 回呼号码长度 */
} CALL_S_ACB_SERVICE_DATA;


/**
 * 密码限呼登记业务数据
 */
typedef struct tagCALL_S_CALL_BARRING_SERVICE_DATA
{
    TUP_CHAR   aszPassword[CALL_D_MAX_STR_LENGTH];    /**< 密码限呼的密码 */
    TUP_UINT32 ulPasswordLen;                         /**< 密码长度 */
    TUP_UINT32 ulLimitType;                           /**< 密码限呼的类型 */
} CALL_S_CALL_BARRING_SERVICE_DATA;



/** 被前转的目的号码结果通知结构(用于IMS组网下) */
typedef struct tagCALL_S_HISTORY_INFO
{
    TUP_UINT32 ulCnt;           /**< 号码个数 */
    TUP_CHAR   aszHistoryNum[CALL_D_MAX_HISTORY_NUM][CALL_D_128_STR_LENGTH]; /**< 号码信息数组 */
} CALL_S_HISTORY_INFO;


/**
 * Paging 业务来电通知结构
 */
typedef struct tagCALL_S_PAGING_GROUP
{
    TUP_CHAR aszGroupName[CALL_D_MAX_LENGTH_NUM];   /**< Paging 组名 */
    TUP_CHAR aszGroupNumber[CALL_D_MAX_LENGTH_NUM]; /**< Paging 组号 */
}CALL_S_PAGING_GROUP;


/**
 * DND模式
 */
typedef enum tagCALL_E_DND_TYPE
{
    CALL_E_DND_TYPE_SERVER = 0,    /**< 服务器DND */
    CALL_E_DND_TYPE_LOCAL,         /**< 本地DND */
    CALL_E_DND_TYPE_BUTT           /**< 无效值  */
} CALL_E_DND_TYPE;


/**
 * LOCAL DND处理模式
 */
typedef enum tagCALL_E_LOCALDND_TYPE
{
    CALL_E_LOCALDND_TYPE_REJECT = 0,      /**< 来电拒接 */
    CALL_E_LOCALDND_TYPE_RINGOFF,         /**< 来电不振铃 */
    CALL_E_LOCALDND_TYPE_BUTT             /**< 无效值  */
} CALL_E_LOCALDND_TYPE;


/** 
 * DND数据结构
 */
typedef struct tagCALL_S_CALL_DND_DATA
{
    TUP_BOOL bSwitch;                       /**< 是否是切换DND而发起的批量登记 */
    TUP_BOOL bNeedStartLocalDND;            /**< 批量发起成功后是否需要发起本地DND登记 */
    TUP_BOOL bSetenableLocalDND;            /**< 是否需要设置enableLocalDND */
    CALL_E_LOCALDND_TYPE enLocalDNDType;    /**< 本地DND类型 */
    TUP_CHAR acRecvNotifyApp[CALL_D_MAX_NAMESPACE];  /**< 发送结果的目的地模块ID*/
} CALL_S_CALL_DND_DATA;


/**
 * 前转类型
 */
typedef enum tatCALL_E_FORWARD_TYPE
{
    CALL_E_FORWARD_TYPE_UNCONDITION,        /**< 无条件前转*/
    CALL_E_FORWARD_TYPE_ONBUSY,             /**< 遇忙前转*/
    CALL_E_FORWARD_TYPE_NOREPLY,            /**< 无应答前转*/
    CALL_E_FORWARD_TYPE_OFFLINE,            /**< 离线前转*/
    CALL_E_FORWARD_TYPE_BUTT                /**< 无效值  */
} CALL_E_FORWARD_TYPE;


/**
 * 前转目的类型定义
 */
typedef enum tagCALL_E_FORWARD_DEST_TYPE
{
    CALL_E_FORWARD_DEST_TYPE_PHONENUM = 0,  /**< 前转至其他号码*/
    CALL_E_FORWARD_DEST_TYPE_VOICEMAIL,     /**< 前转至语音邮箱*/
    CALL_E_FORWARD_DEST_TYPE_BUTT           /**< 无效值  */
} CALL_E_FORWARD_DEST_TYPE;


/**
 * 前转开启关闭
 */
typedef enum tagCALL_E_FORWARD_ONOFF_TYPE
{
    CALL_E_FORWARD_ONOFF_TYPE_ON = 0,       /**< 前转功能开 */
    CALL_E_FORWARD_ONOFF_TYPE_OFF,          /**< 前转功能关 */
    CALL_E_FORWARD_ONOFF_TYPE_BUTT          /**< 无效值  */
} CALL_E_FORWARD_ONOFF_TYPE;

/**
 * 前转信息结构体
 */
typedef struct tagCALL_S_FORWARD_INFO
{
    TUP_UINT32 ulSipAccountID;                      /**< 账户ID*/
    CALL_E_FORWARD_TYPE  enFwdType;                 /**< 前转类型*/
    CALL_E_FORWARD_ONOFF_TYPE enOnOff;              /**< 开启或关闭    0开启 1关闭*/
    CALL_E_FORWARD_DEST_TYPE enDstType;             /**< 目的类型  0号码  1语音邮箱*/
    TUP_CHAR    acDestNum[CALL_D_MAX_LENGTH_NUM];   /**< 前转目的号码 如果为语音邮箱，此项为空*/
    TUP_UINT32  ulResult;                           /**< 前传结果，0成功，1失败，1初始值*/
} CALL_S_FORWARD_INFO, *CALL_S_FORWARD_INFO_PTR;


/**
 * 服务器订阅/取消前转呼叫结果信息结构
 */
typedef struct tagCALL_S_FORWARD_RESULT_INFO
{
    TUP_UINT32 ulSipAccountID;                      /**< 账户ID */
    TUP_UINT32 ulCallId;                            /**< 呼叫ID */
    CALL_E_FORWARD_TYPE  enFwdType;                 /**< 前转类型 */
    CALL_E_FORWARD_DEST_TYPE enDstType;             /**< 目的类型 */
    CALL_E_FORWARD_ONOFF_TYPE enOnOff;              /**< 开启或关闭, 0开启 1关闭 */
    TUP_CHAR    acDestNum[CALL_D_MAX_LENGTH_NUM];   /**< 前转目的号码 如果为语音邮箱，此项为空 */
    TUP_UINT32  ulResult;                           /**< 前传结果，0成功，1失败，1初始值 */
} CALL_S_FORWARD_RESULT_INFO;


/**
 * 服务器前转结果通知数据结构
 */
typedef struct tagCALL_S_FORWARD_SERVICE
{
    TUP_CHAR acRecvNotifyApp[CALL_D_MAX_NAMESPACE];                 /**< 发送结果的目的地模块ID */
    TUP_UINT32  ulFwdNum;                                           /**< 前转呼叫的个数 */
    CALL_S_FORWARD_RESULT_INFO  pstFwdResult[CALL_D_MAX_FOWARD_NUM];/**< 前转结果 */
} CALL_S_FORWARD_SERVICE , *CALL_S_FORWARD_SERVICE_PTR;


/**
 * 自动回呼(ACB)请求信息数据
 */
typedef struct tagCALL_S_ACBCALL_REQ_INFO
{
    TUP_UINT32 ulSipAccountID;                      /**< 账户ID */
    TUP_CHAR acRemoteNum[CALL_D_MAX_STR_LENGTH];    /**< 远端号码 */
}CALL_S_ACB_REQ_INFO;

 
/** 
 * 前转业务数据结构
 */
typedef struct tagCALL_S_CALL_FORWARD_SERVICE_DATA
{
    TUP_CHAR    astDestNum[CALL_D_MAX_LENGTH_NUM]; /**< 前转号码*/
    TUP_UINT32 ulDestNumLen;                       /**< 前转号码长度*/
} CALL_S_CALL_FORWARD_SERVICE_DATA;


/** 
 * HuntGroup业务数据结构
 */
typedef struct tagCALL_S_HUNTGROUP_DATA
{
    TUP_CHAR   aszGroupNumber[CALL_D_MAX_LENGTH_NUM];  /**< HuntGroup组号*/
}CALL_S_HUNTGROUP_DATA;



/** 
 * IPT业务数据联合体
 */
typedef union tagCALL_U_IPT_DATA
{
    CALL_S_ACB_SERVICE_DATA stACBData;                  /**< 自动回呼业务数据*/
    CALL_S_CALL_BARRING_SERVICE_DATA stCallBarringData; /**< 密码限呼业务数据*/
    CALL_S_CALL_FORWARD_SERVICE_DATA stCallForwardData; /**< 呼叫前转业务数据*/
    CALL_S_CALL_DND_DATA stDNDData;                     /**< DND呼业务数据*/
    CALL_S_HUNTGROUP_DATA stHuntGroupData;              /**< HuntGroup业务数据*/
} CALL_U_IPT_DATA;

/** IPT业务数据 */
typedef struct tagCALL_S_IPT_DATA
{
    TUP_CHAR  acRecvNotifyApp[CALL_D_MAX_NAMESPACE];    /**< 发送结果的目的地模块ID */
    CALL_E_SERVICE_CALL_TYPE enIPTServiceType;          /**< IPT业务类型 */
    CALL_U_IPT_DATA unIPTData;                          /**< 业务数据联合体 */
    TUP_BOOL bCancelNextOpIfFail;                       /**< 登记失败时是否取消下一个IPT业务 */
} CALL_S_IPT_DATA;


/**
 * 可视化语音邮箱查询消息结构 
 */
typedef struct tagCALL_VVM_QUERY_MSG
{
    TUP_UINT32 ulSipAccountID;                  /**< 账户ID */
    TUP_UINT32 ulPageLimit;                     /**< 查询语言留言 每页个数 */
    TUP_UINT32 ulOrderType;                     /**< 预留，暂不使用 */
    TUP_CHAR acPrevMsgID[CALL_D_64_STR_LENGTH]; /**< 前一消息ID */
} CALL_S_VVM_QUERY_MSG;


/**
 * 可视化语音邮箱转发消息结构 
 */
typedef struct tagCALL_VVM_FWD_MSG
{
    TUP_UINT32 ulSipAccountID;                  /**< 账户ID */
    TUP_CHAR acMsgID[CALL_D_64_STR_LENGTH];     /**< 消息ID */
    TUP_CHAR acDstNum[CALL_D_MAX_LENGTH_NUM];   /**< 目的号码 */
} CALL_S_VVM_FWD_MSG;


/**
 * 可视化语音邮箱删除消息结构 
 */
typedef struct tagCALL_VVM_DEL_MSG
{
    TUP_UINT32 ulSipAccountID;                  /**< 账户ID */
    TUP_BOOL bIsDelAllMsg;                      /**< 是否删除所有消息 */
    TUP_CHAR acMsgID[CALL_D_64_STR_LENGTH];     /**< 消息ID */
} CALL_S_VVM_DEL_MSG;


 /**
  * 信号音类型
  */
typedef enum tagCALL_E_SIGTONE_TYPE
{
    CALL_E_SIGNAL_DIAL,    /**< 拨号音 */
    CALL_E_SIGNAL_BACK,    /**< 回铃音 */
    CALL_E_SIGNAL_BUSY,    /**< 忙音 */
    CALL_E_SIGNAL_ALERT,   /**< 告警音 */
    CALL_E_SIGNAL_WAIT,    /**< 呼等提示音 */
    CALL_E_SIGNAL_BUTT     /**< 未知类型 */
} CALL_E_SIGTONE_TYPE;
 

/**
 * UM消息类型
 */
typedef enum tagCALL_E_UM_MSG_TYPE
{
    CALL_E_UM_TYPE_IM,      /**< IM信息*/
    CALL_E_UM_TYPE_CONF,    /**< 会议信息*/
    CALL_E_UM_TYPE_BUTT     /**< 无效值  */
} CALL_E_UM_MSG_TYPE;


/**
 * UM消息信息内容
 */
typedef struct tagCALL_S_UM_MSG
{
    CALL_E_UM_MSG_TYPE  eMsgType;                       /**< 该消息类型, 此类型可能以后会扩展*/
    TUP_UINT32 ulSipAccountID;                          /**< 接收该IM消息的账号ID */
    TUP_UINT32 ulUMContextLen;                          /**< UM 消息Context长度 */
    TUP_CHAR szFromUserNum[CALL_D_MAX_STR_LENGTH];      /**< UM 消息来源号码  */
    TUP_CHAR szSrcPrority[CALL_D_MAX_STR_LENGTH];       /**< MsgExt.SrcPrority 字段*/
    TUP_CHAR szHasAttachment[CALL_D_MAX_STR_LENGTH];    /**< MsgExt.HasAttachment 字段*/
    TUP_CHAR szHistoryMsgNotify[CALL_D_MAX_STR_LENGTH]; /**< HistoryMsgNotify 字段*/
    TUP_CHAR acLocalMsgID [CALL_D_MAX_STR_LENGTH];      /**< MsgExt.localMsgID 字段*/
    TUP_CHAR acMsgSvcType [CALL_D_MAX_STR_LENGTH];      /**< MsgExt.msgSvcType 值 */
    TUP_CHAR acMsgSort [CALL_D_MAX_STR_LENGTH];         /**< MsgExt.msgSort 值 */
    TUP_CHAR acMsgExt [CALL_D_MAX_STR_LENGTH];          /**< MsgExt字段 */
    TUP_CHAR acValidTime[CALL_D_MAX_STR_LENGTH];        /**< ValidTime字段 */
    TUP_CHAR acSubmitTime [CALL_D_MAX_STR_LENGTH];      /**< submitTime字段 */
    TUP_CHAR acAnonMsg [CALL_D_MAX_STR_LENGTH];         /**< anonMsg字段 */
    TUP_CHAR acNsImdn [CALL_D_MAX_STR_LENGTH];          /**< Ns:Imdn字段 */
    TUP_CHAR acMessageID [CALL_D_MAX_STR_LENGTH];       /**< imdn.Message-ID字段 */
    TUP_CHAR acContentType [CALL_D_MAX_STR_LENGTH];     /**< content-type字段*/
    TUP_CHAR acEncode[CALL_D_MAX_STR_LENGTH];           /**< content-transfer-encoding字段 */
    TUP_CHAR acUMContext[CALL_D_MAX_UM_MSG_LENGTH];     /**< UM内容*/
} CALL_S_UM_MSG;



/**
 * 呼叫拒接回复信令类型
 */
typedef enum tagCALL_E_REJECTCALL_TYPE
{
    CALL_D_REJECTTYPE_486 = 1,  /**< 486 */
    CALL_D_REJECTTYPE_603,      /**< 603 */
    CALL_D_REJECTTYPE_404,      /**< 404 */
    CALL_D_REJECTTYPE_480,      /**< 480 */
    CALL_D_REJECTTYPE_403,      /**< 403 */
    CALL_D_REJECTTYPE_BUTT      /**< 无效值  */
}CALL_E_REJECTCALL_TYPE;


/**
 * 携带的REFRESHER信令类型
 */
typedef enum tagCALL_E_SESSION_REFRESHER
{
    CALL_E_REFRESHER_UAC,       /**< uac */
    CALL_E_REFRESHER_UAS,       /**< uas */
    CALL_E_REFRESHER_UNDEFINED, /**< 未定义 */
    CALL_E_REFRESHER_BUIT       /**< 无效值  */
}CALL_E_SESSION_REFRESHER;


/**
 * 视频拒接回复信令类型
 */
typedef enum tagCALL_E_REJECTVIDEO_TYPE
{
    CALL_D_REJECTVIDEOTYPE_200, /**< 200 */
    CALL_D_REJECTVIDEOTYPE_603, /**< 603 */
    CALL_D_REJECTVIDEOTYPE_BUTT /**< 无效值  */    
}CALL_E_REJECTVIDEO_TYPE;


/**
 * 会议主题信息
 */
typedef struct tagCALL_S_CONF_SUBJECT
{
    TUP_UINT32 ulConfID;        /**< 会议ID */
    TUP_CHAR acSubject[CALL_CONF_SUBJECT_MAX_STR_LEN];  /**< 会议主题 */
}CALL_S_CONF_SUBJECT;


/**
 * 加入会议结果
 */
typedef struct tagCALL_S_CONF_CONNECT_RESULT
{
    TUP_UINT32 ulConfID;            /**< 会议ID */
    TUP_UINT32 ulCallID;            /**< 呼叫ID */
    TUP_UINT32 ulResult;            /**< 加入会议结果 */
    CALL_E_CONF_MODE enConfMode;    /**< 会议模式 */
    CALL_E_CALL_TYPE enCallType;    /**< 呼叫类型 */
}CALL_S_CONF_CONNECT_RESULT;


/**
 * 邀请与会者结果
 */
typedef struct tagCALL_S_CONF_ADDATTENDEE_RESULT
{
    TUP_UINT32 ulConfID;            /**< 会议ID */
    TUP_UINT32 ulResult;            /**< 邀请加入与会者结果 */
    TUP_UINT32 ulAttendeeCount;     /**< 与会者个数 */
    TUP_CHAR *pcAttendee;           /**< 与会者列表 */
}CALL_S_CONF_ADDATTENDEE_RESULT;


/**
 * 通话被转入会议通知
 */
typedef struct tagCALL_S_CONF_BETRANSFERTOCONF
{
    TUP_UINT32 ulConfID;        /**< 会议ID */
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_INT8 acGroupUri[CALL_D_MAX_LENGTH_NUM];     /**< 组URI */
    TUP_INT8 acConfIndex[CALL_D_MAX_LENGTH_NUM];    /**< 会议索引 */
    CALL_E_SERVERCONF_TYPE eConfType;               /**< 会议类型 */
    CALL_E_CONF_MODE eConfMode;                     /**< 会议模式 */
}CALL_S_CONF_BETRANSFERTOCONF;


/**
 * 通话转会议结果(成功或失败)
 */
typedef struct tagCALL_S_CONF_TRANSFERTOCONF_RESULT
{
    TUP_UINT32 ulConfID;        /**< 会议ID */
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_UINT32 ulResult;        /**< 结果:0成功，其他 失败 */
}CALL_S_CONF_TRANSFERTOCONF_RESULT;


/**
 * 一键加入会议结果
 */
typedef struct tagCALL_S_ONEKEY_TO_CONF_RESULT
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_UINT32 ulResult;        /**< 结果:0成功，其他 失败 */
    CALL_E_CONFTYPE eConfType;  /**< 会议类型 */
}CALL_S_ONEKEY_TO_CONF_RESULT,CALL_S_CONF_CONNECT_ONEKEY_TO_CONF_RESULT;


/**
 * 音频媒体模式
 */
typedef enum tagCALL_E_AUDIO_MODE
{
    CALL_AUDIO_MODE_NONE     =   0x00,  /**< 无效模式 */
    CALL_AUDIO_MODE_LOCAL    =   0x01,  /**< pc本地模式 */
    CALL_AUDIO_MODE_VM_LOCAL =   0x02,  /**< 云上本地音频模式 */
    CALL_AUDIO_MODE_TC       =   0x04,  /**< TC模式 */

    CALL_AUDIO_MODE_INVALID  =   0xFF
}CALL_E_AUDIO_MODE;


/**
 * TC文件值，每个值对应一个固定的文件，与瘦客户端值一一对应
 */
typedef enum tagCALL_E_TC_FILE_VALUE
{
    CALL_TC_FILE_INCOMINGIM,        /**< 来IM消息声音 incomingim */
    CALL_TC_FILE_INCOMINGCALL,      /**< 来电本地放音 incomingcall */
    CALL_TC_FILE_CALLHOLD,          /**< 保持本地放音 callhold */
    CALL_TC_FILE_RINGBACKTONE,      /**< ringbacktone */
    CALL_TC_FILE_NUM0,              /**< num0 0 */
    CALL_TC_FILE_NUM1,              /**< num1 1 */
    CALL_TC_FILE_NUM2,              /**< num2 2 */
    CALL_TC_FILE_NUM3,              /**< num3 3 */
    CALL_TC_FILE_NUM4,              /**< num4 4 */
    CALL_TC_FILE_NUM5,              /**< num5 5 */
    CALL_TC_FILE_NUM6,              /**< num6 6 */
    CALL_TC_FILE_NUM7,              /**< num7 7 */
    CALL_TC_FILE_NUM8,              /**< num8 8 */
    CALL_TC_FILE_NUM9,              /**< num9 9 */
    CALL_TC_FILE_STAR,              /**< star * */
    CALL_TC_FILE_POUND,             /**< pound # */
    CALL_TC_FILE_CALLOUT,           /**< callout, */
    CALL_TC_FILE_ROLLBACK           /**< rollback 回铃音 */
}CALL_E_TC_FILE_VALUE;
#define CALL_TC_FILE_NUMXING    CALL_TC_FILE_STAR
#define CALL_TC_FILE_NUMJING    CALL_TC_FILE_POUND

#define DM_MAX_DIALNUMBER_LEN  32   /**< 数图号码最大长度 */


/**
 * 数图转换结果
 */
typedef struct tagDMRESULT
{
    TUP_UINT32 uiLength;                    /**< 匹配的长度或者替换后的号码长度 */
    TUP_CHAR pszNUM[DM_MAX_DIALNUMBER_LEN]; /**< 替换后的号码 */
}DMRESULT;



/**
 * 网络质量改变通知消息结构
 */
typedef struct tagCALL_S_NETQUALITY_CHANGE
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */   
    TUP_UINT32 uLNetError;      /**< 网络错误 0 : 没有错误 1 : 网络发端错误 2 : 网络收端错误 3 : 网络收发均错误。 */
    TUP_UINT32 ulNetLevel;      /**< 网络质量等级，当net-error为0此值有效 [0,5]  */
}CALL_S_NETQUALITY_CHANGE;


/**
 * 网络质量统计信息
 */
typedef struct tagCALL_S_STATISTIC_NETINFO
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */  
    TUP_UINT32 ulLost;          /**< 丢包率，单位% */
    TUP_UINT32 ulDelay;         /**< 时延 毫秒 */
    TUP_UINT32 ulJitter;        /**< 抖动 毫秒 */
}CALL_S_STATISTIC_NETINFO;


/**
 * 文件格式 
 */
typedef enum  tagCALL_E_FILE_FORMAT
{
    CALL_FILE_FORMAT_PCM = 0,   /**< PCM文件格式 */  
    CALL_FILE_FORMAT_WAV = 1,   /**< WAV文件格式，目前支持PCM_ALAW、PCM_ULAW、PCM */  
    CALL_FILE_FORMAT_AMR = 2,   /**< AMR文件格式，目前支持单通道AMR-NB */  
}CALL_E_FILE_FORMAT;


/**
 * 播放音频文件附加信息
 */
typedef struct tagCALL_S_AUDIO_PLAYFILE_ADDITIONINFO
{
    CALL_E_FILE_FORMAT enFileFormat;    /**< 文件格式 */
} CALL_S_AUDIO_PLAYFILE_ADDITIONINFO;


/**
 * 预设EQ类型
 */
typedef enum tagCALL_E_PRESET_EQ_TYPE
{
    CALL_E_PRESET_EQ_TYPE_RECOMMEND,    /**< 推荐音效 */
    CALL_E_PRESET_EQ_TYPE_NORTHAMERICA, /**< 北美音效 */
    CALL_E_PRESET_EQ_TYPE_AUSTRALIA,    /**< 澳洲音效 */
    CALL_E_PRESET_EQ_TYPE_TIA920,       /**< TIA920音效 */
    CALL_E_PRESET_EQ_TYPE_BUTT
}CALL_E_PRESET_EQ_TYPE;


/**
 * 视频操作
 */
typedef struct tagCALL_S_VIDEO_OPERATION
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_UINT32 ulOperation;     /**< 操作，取值:
                                 <br>open 0x01，close 0x02，start 0x04，stop 0x08 */
    TUP_UPTR   ulRenderHanle;   /**< 被操作的视频窗口句柄  */
    TUP_UINT32 ulType;          /**< 远端或者本地 1：本地 2：远端  */
}CALL_S_VIDEO_OPERATION;


/**
 * 视频(辅流)大小变更
 */
typedef struct tagCALL_S_VIDEO_FRAMESIZE_CHANGE
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_UINT32 ulWidth;         /**< 解码宽 */
    TUP_UINT32 ulHeight;        /**< 解码高 */
}CALL_S_VIDEO_FRAMESIZE_CHANGE;


/**
 * 媒体错误信息
 */
typedef struct tagCALL_S_MEDIA_ERRORINFO
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_UINT32 ulMediaType;     /**< 媒体类型：  0 : 未知类型。1 : 音频。  2 : 视频。 3 : 辅流  */
    TUP_UINT32 ulErrorType;     /**< 错误类型:   0 : 未知类型 1 : 启动发送错误 2 : 启动接收错误  */
}CALL_S_MEDIA_ERRORINFO;


/**
 * 会话正在使用的编解码器信息
 */
typedef struct tagCALL_S_SESSION_CODEC
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_UINT32 ulMediaType;     /**< 媒体类型：  0 : 未知类型。1 : 音频。  2 : 视频。 3 : 辅流 */
    TUP_UINT32 ulCodecType;     /**< 编解码器类型： 0 : 未知类型。 1 : 编码器。2 : 解码器。 */
    TUP_CHAR   acCodecName[CALL_MAX_CODEC_NAME_LEN]; /**< 编解码名称 */
}CALL_S_SESSION_CODEC;


/**
 *  设备信息
 */
typedef struct tagCALL_S_DEVICE_INFO
{
    TUP_UINT8 uiIndex;          /**< 设备对应的index */
    TUP_UINT8 uiOrienation;     /**< 视频设备信息专用，硬终端可以不需要此项，个别移动设备特殊 */
    TUP_CHAR  strName[CALL_D_MAX_LENGTH_NUM]; /**< 设备名称 */
}CALL_S_DEVICE_INFO;


/**
 * 音频输入/输出设备信息
 */
typedef struct tagCALL_S_AUDIO_DEVICE_INFO
{
    TUP_UINT8 uiInputNum;         /**< 输入设备数目 */
    TUP_UINT8 uiOutputNum;        /**< 输出设备数目 */
    CALL_S_DEVICE_INFO stInputDevice[CALL_D_MAX_DEVICE_NUM];   /**< 音频输入设备 */
    CALL_S_DEVICE_INFO stOutPutDevice[CALL_D_MAX_DEVICE_NUM];  /**< 音频输出设备 */
}CALL_S_AUDIO_DEVICE_INFO;


/**
 * 视频输入/输出设备信息
 */
typedef struct tagCALL_S_VIDEO_DEVICE_INFO
{
    TUP_UINT8 uiCaptureNum;                             /**< 摄像头数目 */
    CALL_S_DEVICE_INFO stCapture[CALL_D_MAX_DEVICE_NUM];/**< 视频设备信息 */
}CALL_S_VIDEO_DEVICE_INFO;


/**
 * 录*制文件附加信息
 */
typedef struct tagCALL_S_RECORDFILE_INFO
{
    TUP_UINT32 ulCaptureIndex;  /**< 本地输入设备索引 */
    TUP_UINT32 ulFileSize;      /**< 文件大小提示告警，如果文件超过改大小，会上抛通知，不影响功能，默认100M,视频功能需要 */
    TUP_UINT32 ulSampleFreq;    /**< 采样率 */
    TUP_UINT32 ulRate;          /**< 码率 */
    TUP_INT8   acCodecName[CALL_MAX_CODEC_NAME_LEN];   /**< 编码名称 */
}CALL_S_RECORDFILE_INFO;


/**
 * QoS上报配置信息
 */
typedef struct tagCALL_S_SETQOS_INFO
{
    TUP_BOOL   bIsNotifyQos;    /**< 是否开启Qos上报，默认false不开启，true开启  */
    TUP_UINT32 ulQosTime;       /**< 上报间隔  */
    TUP_FLOAT  fMosVal;         /**< mos阀值 */
    TUP_UINT32 ulLostVal;       /**< 丢包率阀值 */
    TUP_UINT32 ulJitterVal;     /**< 抖动阀值 */
    TUP_UINT32 ulDelayVal;      /**< 时延阀值 */
}CALL_S_SETQOS_INFO;


/**
 * QoS上报信息(上报至服务器)
 */
typedef struct tagCALL_S_NOTIFYQOS_INFO
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_FLOAT  fMosValue;       /**< mos平均值 */
    TUP_UINT32 ulLostValue;     /**< JB丢包率平均值 */
    TUP_UINT32 ulNetLostValue;  /**< 网络丢包率平均值 */
    TUP_UINT32 ulJitterValue;   /**< 抖动平均值 */
    TUP_UINT32 ulDelayValue;    /**< 时延平均值 */
    TUP_UINT32 ulabnormityTime; /**< 异常时间 */
    TUP_UINT32 uiTcErrorNum;    /**< TC 异常码 */
    
    TUP_CHAR acAudioCodec[CALL_D_MAX_AUDIO_CODEC_LEN]; /**< 音频编解码 "G722,PCMA,PCMU,G729,iLBC,telephone-event,red"*/
    TUP_CHAR acLocalIP[CALL_D_IP_LENGTH];              /**< 本端IP*/
    TUP_CHAR acRemoteIP[CALL_D_IP_LENGTH];             /**< 远端IP*/
    TUP_CHAR acHMEVersion[CALL_D_HMEVERSION_LENGTH];   /**< HME版本*/
    TUP_CHAR acTCVersion[CALL_D_HMEVERSION_LENGTH];    /**< TC版本,没有的话为空*/
}CALL_S_NOTIFYQOS_INFO;


/**
 * QoS上报信息(上报本地UI)
 */
typedef struct tagCALL_S_NOTIFYLOACLQOS_INFO
{
    TUP_UINT32 ulCallID;        /**< 呼叫ID */
    TUP_FLOAT  fMosValue;       /**< mos平均值 */
    TUP_UINT32 ulLostValue;     /**< JB丢包率平均值 */
    TUP_UINT32 ulNetLostValue;  /**< 网络丢包率平均值 */
    TUP_UINT32 ulJitterValue;   /**< 抖动平均值 */
    TUP_UINT32 ulDelayValue;    /**< 时延平均值 */
}CALL_S_NOTIFYLOACLQOS_INFO;


/**
 * 会话修改完成结果信息
 */
typedef struct tagCALL_S_SESSION_MODIFIED
{
    TUP_UINT32 ulCallID;                                /**< 呼叫ID */
    TUP_BOOL bIsFocus;                                  /**< 是否带isfoucs标识，移动会议场景使用*/  
    TUP_INT8 acServerConfType[CALL_D_MAX_LENGTH_NUM];   /**< 会议类型，移动会议场景使用*/  
    TUP_INT8 acServerConfID[CALL_D_MAX_LENGTH_NUM];     /**< 会议ID, 移动会议场景使用*/
    TUP_UINT32 ulOrientType;                            /**< 移动视频横竖屏情况*/
    TUP_INT8 acLocalAddr[CALL_D_IP_LENGTH];             /**< 移动上报本地地址*/
    TUP_INT8 acRemoteAddr[CALL_D_IP_LENGTH];            /**< 移动上报远端地址*/
    CALL_E_REINVITE_TYPE enHoldType;                    /**< 主被叫控业务中Reinvite消息指示的事件类型*/
    CALL_E_MEDIA_SENDMODE enAudioSendMode;              /**< 音频媒体方向*/
    CALL_E_MEDIA_SENDMODE enVideoSendMode;              /**< 视频媒体方向*/
    CALL_E_MEDIA_SENDMODE enDataSendMode;               /**< 辅流媒体方向*/
}CALL_S_SESSION_MODIFIED;


/**
 * 账号的用户名
 */
typedef struct tagCALL_S_ACCOUNT_USER_NAME
{
    TUP_UINT32 ulAccountID;                         /**< 账户ID */
    TUP_CHAR acUserName[CALL_D_128_STR_LENGTH];     /**< 用户名,用于入会时,没有UC账号的情况下上报 */
}CALL_S_ACCOUNT_USER_NAME;


/**
 * BFCP参数
 */
typedef struct tagCALL_S_BFCP_PARAM
{
    TUP_UINT32 uiTransType; /**< 辅流传输类型，1表示UDP，2表示TCP, 协商的结果以主动invite方为准，@see CALL_E_BFCPTRANS_TYPE*/
    TUP_UINT32 uiFloorCtrl; /**< 辅流控制类型，1表示c-only,2表示s-only， @see CALL_E_BFCP_FLOOR_CTRL*/
    TUP_UINT32 uiSetup;     /**< 用户在TCP传输BFCP信令时规定主动连接的一方，1表示active，2表示passive， @see CALL_E_BFCP_SETUP*/
}CALL_S_BFCP_PARAM;



#define CALL_NTF_TEST_BASE     CALL_E_EVT_BUTT                      /**< 自动化测试通知事件起始ID */
#define CALL_NTF_VIDEO_FIRST_PACKET_TEST    (CALL_NTF_TEST_BASE+1)  /**< 收到第一个视频包信息 */
#define CALL_NTF_AUDIO_FIRST_PACKET_TEST    (CALL_NTF_TEST_BASE+2)  /**< 收到第一个音频包信息 */

#define CALL_DEC_PT_NUM_MAX 18      /**< 解码PT值最大个数 */


/**
 * 视频基本信息
 */
typedef struct tagCALL_VIDEO_BASE_INFO
{
    TUP_UINT32  uiCallID;                                   /**< 呼叫ID */    
    TUP_CHAR    acCodecName[CALL_MAX_CODEC_NAME_LEN+1];     /**< 编解码名 */ 
    TUP_UINT16  usEncPt;                                    /**< 编码PT值 */ 
    TUP_UINT16  ausDecPt[CALL_DEC_PT_NUM_MAX];              /**< 解码PT值列表 */ 
    TUP_UINT16  usDecPtNum;                                 /**< 解码PT值列表个数 */ 
}CALL_VIDEO_BASE_INFO;


/**
 * 音频基本信息
 */
typedef struct tagCALL_AUDIO_BASE_INFO
{
    TUP_UINT32  uiCallID;                                   /**< 呼叫ID */    
    TUP_CHAR    acCodecName[CALL_MAX_CODEC_NAME_LEN+1];     /**< 编解码名 */ 
    TUP_UINT16  usEncPt;                                    /**< 编码PT值 */
    TUP_UINT16  usDecPt;                                    /**< 解码PT值 */
}CALL_AUDIO_BASE_INFO;


/**
 * 呼叫自动化测试基本信息
 */
typedef union tagCALL_U_TEST_INFO
{
    CALL_AUDIO_BASE_INFO stAudioBaseInfo;                   /**< 音频基本信息 */    
    CALL_VIDEO_BASE_INFO stVideoBaseInfo;                   /**< 视频基本信息 */   
}CALL_U_TEST_INFO;


/**
 * 呼叫自动化测试基本信息通知
 */
typedef struct tagCALL_S_TEST_NOTIFY
{
    TUP_UINT32 uiNotifyType;    /* 通知类型，音频或视频 */
    CALL_U_TEST_INFO unInfo;    /* 呼叫自动化测试基本信息 */
} CALL_S_TEST_NOTIFY;


/**
 * @brief 自动化测试回调函数
 * 
 * @param [in] TUP_VOID* pUserContext         <b>:</b> 用户信息
 * @param [in] CALL_S_TEST_NOTIFY* punNotify  <b>:</b> 呼叫自动化测试基本信息通知结构
 * @param [out] NA
 * @retval typedef TUP_VOID (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 预留，暂没有使用
 * @see NA
 **/
typedef TUP_VOID (*TEST_CALL_BACK)(TUP_VOID* pUserContext, CALL_S_TEST_NOTIFY* punNotify); 



#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_ADVANCED_DEF_H__*/

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
*
* vi: set expandtab ts=4 sw=4 tw=80:
*/


