/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM子系统扩展业务功能接口结构体定义头文件。 \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_EXTENDDEF_H_
#define _TUP_IM_EXTENDDEF_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#define IM_D_MAX_FILEPATH_LENGTH (260)						/**< 文件路径最大长度 */


#define IM_D_MAX_SMSID_LENGTH (16)							/**< 短信ID最大长度 */


#define IM_D_MAX_SMSCONENT_LENGTH (350)						/**< 短信内容最大长度 */


#define IM_D_MAX_SMSRECEIVEER_LENGTH (1000)					/**< 短信收件人最大长度 */

/**
 *  文件传输终止原因
 */
typedef enum tagIM_E_FILETRANSFER_P2PFILESTOP_REASON
{
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_UNKNOW		= -1,	/**< 未知错误停止 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_NORMAL		= 0,	/**< 正常停止 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_TIMEOUT	= 1,	/**< 超时停止 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_SENDERROR	= 2,	/**< 发送方发生错误导致停止 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_ACCEPTERROR= 3,	/**< 接收方发生错误导致停止 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_COMPLETED	= 4,	/**< 文件发送完成停止 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_ABNORMAL	= 5		/**< 文件传输未完成停止 */
}IM_E_FILETRANSFER_P2PFILESTOP_REASON;

/**
 *  文件传输开始结果
 */
typedef enum tagIM_E_P2PFILE_START_RESLUT
{
	IM_E_P2PFILE_START_RESLUT_SUCCESS				= 0,	/**< 成功 */
	IM_E_P2PFILE_START_RESLUT_MODEDETECT_SUCCESS	= 1,    /**< 连通性检测成功 */
	IM_E_P2PFILE_START_RESLUT_TIMEOUT				= -100,	/**< 超时 */
	IM_E_P2PFILE_START_RESLUT_TARGETOFFLINE         = -104,	/**< 对方离线 */
	IM_E_P2PFILE_START_RESLUT_PEERREJECT			= -112, /**< 对方拒绝 */
	IM_E_P2PFILE_START_RESLUT_NOFILETOSEND			= -116, /**< 当前文件不存在 */
	IM_E_P2PFILE_START_RESLUT_SENDERROR				= -120, /**< 发送失败 */
	IM_E_P2PFILE_START_RESLUT_ACCEPTERROR			= -121, /**< 接收失败 */
	IM_E_P2PFILE_START_RESLUT_OPENFILEERROR			= -122, /**< 打开文件失败 */
	IM_E_P2PFILE_START_RESLUT_CANCELED				= -124, /**< 取消文件传输 */
	IM_E_P2PFILE_START_RESLUT_FILEBUSY				= -125, /**< 文件被其他层序打开 */
	IM_E_P2PFILE_START_RESLUT_FILEISEMPTY			= -128, /**< 文件内容为空 */
	IM_E_P2PFILE_START_RESLUT_FILEMODE_MISMATCH		= -132, /**< 文件传输网络不通 */
	IM_E_P2PFILE_START_RESLUT_REGIONALISOLATION		= -136	/**< 文件区域隔离 */
}IM_E_P2PFILE_START_RESLUT;

/**
 *  群共享文件查询类型
 */
typedef enum tagIM_E_GROUPFILE_QUERY_TYPE
{
	IM_E_GROUPFILE_QUERY_TYPE_FILENAME				= 0,	/**< 按文件名搜索 */
	IM_E_GROUPFILE_QUERY_TYPE_FILETYPE				= 1,	/**< 按文件类型搜索 */
	IM_E_GROUPFILE_QUERY_TYPE_FILEID				= 2		/**< 按文件ID搜索 */
}IM_E_GROUPFILE_QUERY_TYPE;

/**
 *  群共享文件通知标识
 */
typedef enum tagIM_E_GROUPFILE_NOTIFE_TYPE
{
	IM_E_GROUPFILE_NOTIFE_TYPE_FILECHANGE			= 0		/**< 群共享文件通知 */
}IM_E_GROUPFILE_NOTIFE_TYPE;

/**
 *  群共享文件变更类型
 */
typedef enum tagIM_E_GROUPFILE_OPT_TYPE
{
	IM_E_GROUPFILE_OPT_TYPE_ADD						= 0,	/**< 新增群文件 */
	IM_E_GROUPFILE_OPT_TYPE_DEL						= 1		/**< 删除群文件 */
}IM_E_GROUPFILE_OPT_TYPE;

/**
 *  文件信息
 */
typedef struct tagIM_S_P2PFILE_INFO
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];				/**< 对方账号 */ 
    TUP_CHAR filePath[IM_D_MAX_FILEPATH_LENGTH];			/**< 本地文件路径 */ 
}IM_S_P2PFILE_INFO;


/**
 *  群共享文件信息
 */
typedef struct tagIM_S_GROUPFILE_INFO
{
    TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< 文件ID */
	TUP_CHAR	uploadTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< 服务器侧上传成功的时间 */
	TUP_CHAR	uploadUserAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< 上传者账号 */
	TUP_CHAR	uploadUserName[IM_D_MAX_NAME_LENGTH];		/**< 上传者姓名 */
	TUP_CHAR	fileURL[IM_D_URL_LENGTH];					/**< 文件URL */
	TUP_CHAR	fileName[IM_D_MAX_NAME_LENGTH];				/**< 文件名 */
	TUP_INT64	fileSize;									/**< 文件大小 */
	TUP_CHAR	prefileId[IM_D_MAX_PASSWORD_LENGTH];		/**< 文件应对的预上传ID */
}IM_S_GROUPFILE_INFO;

/**
 *  发送文件请求
 */
typedef struct tagIM_S_SENDP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**< 文件信息 */
    TUP_UINT32	timeoutSeconds;								/**< 文件传输等待超时时间 */ 
    TUP_BOOL	isEncrypt;									/**< 是否进行加密（加密会影响传输速度） */ 
}IM_S_SENDP2PFILE_ARG;


/**
 *  接收文件
 */
typedef struct tagIM_S_ACCEPTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**< 文件信息 */
}IM_S_ACCEPTP2PFILE_ARG;

/**
 *  拒绝文件传输
 */
typedef struct tagIM_S_REJECTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**< 文件信息 */
}IM_S_REJECTP2PFILE_ARG;

/**
 *  取消文件传输
 */
typedef struct tagIM_S_CANCELP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**<  文件信息 */
}IM_S_CANCELP2PFILE_ARG;

/**
 *  文件传输结果通知
 */
typedef struct tagIM_S_P2PFILE_RESULT_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/**< 对方账号 */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< 文件名 */
	IM_E_P2PFILE_START_RESLUT	startresult;				/**< 开始文件传输的结果 */
	TUP_INT32	stopresult;									/**< 暂停文件传输的结果 */
}IM_S_P2PFILE_RESULT_NOTIFY;


/**
 *  文件传输进度通知
 */
typedef struct tagIM_S_FILEPROCESS_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/**< 对方账号 */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< 文件名 */
	TUP_INT64	current;									/**< 当前已传输大小 */
	TUP_INT64	total;										/**< 文件总大小 */
	TUP_CHAR	dir[IM_D_MAX_DESC_LENGTH];					/**< 文件夹名称 */
	TUP_INT64	totalFileCount;								/**< 文件总数 */
	TUP_INT32	currentFileIndex;							/**< 当前文件序号 */
	TUP_INT64	currentFileSize;							/**< 文件夹已经传输的大小 */
	TUP_INT64	totalFileSize;								/**< 文件夹所有文件总大小 */
}IM_S_FILEPROCESS_NOTIFY;

/**
 *  收到文件传输请求通知
 */
typedef struct tagIM_S_P2PFILECHOOSE_NOTIFY
{
	TUP_CHAR	targetAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< 对方账号 */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< 文件名 */
	TUP_INT64	totalSize;									/**< 文件总大小 */
	TUP_BOOL	bIsPic;										/**< 是否是图片 */
	TUP_BOOL	bisDir;										/**< 是否是文件夹 */
}IM_S_P2PFILECHOOSE_NOTIFY;

/**
 *  文件传输上报文件信息
 */
typedef struct tagIM_S_P2PFILESTATISTIC_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/**< 对方账号 */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< 文件名 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON	reason;			/**< 停止原因 */
}IM_S_P2PFILESTATISTIC_NOTIFY;


/**
 *  短信发送
 */
typedef struct tagIM_S_SENDSMS_ARG
{
    TUP_CHAR	msgID[IM_D_MAX_SMSID_LENGTH];				/**< 客户端产生的消息ID */ 
    TUP_CHAR	bindNo[IM_D_MAX_PHONE_LENGTH];				/**< 当前用户的绑定号码 */ 
    TUP_CHAR	content[IM_D_MAX_SMSCONENT_LENGTH];			/**< 短信内容 */ 
    TUP_CHAR	receiverList[IM_D_MAX_SMSRECEIVEER_LENGTH];	/**< 收信人列表，以半角分号分割 */ 
    TUP_CHAR	sendTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< 短信发送时间 19000000000000（年月日时分秒） */ 
	TUP_BOOL	needReceipt;								/**< 是否需要回执 */ 
}IM_S_SENDSMS_ARG;

/**
 *  短信通知
 */
typedef struct tagIM_S_SENDSMS_NOTIFY
{
    TUP_CHAR	msgID[IM_D_MAX_SMSID_LENGTH];				/**< 客户端产生的消息ID */ 
    TUP_CHAR	origin[IM_D_MAX_PHONE_LENGTH];				/**< 发送方号码 */ 
	TUP_CHAR	target[IM_D_MAX_PHONE_LENGTH];				/**< 接收方号码*/
    TUP_CHAR	content[IM_D_MAX_SMSCONENT_LENGTH];			/**< 短信内容 */ 
    TUP_CHAR	sendTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< 短信发送时间 19000000000000（年月日时分秒） */ 
    IM_E_SMS_NOTIFY_TYPE	smsType;						/**< 接收到的短信消息的类型 */
	TUP_INT64	serverMsgID;								/**< 服务器消息ID */
}IM_S_SENDSMS_NOTIFY;


/**
 * 预上传文件信息
 */
typedef struct tagIM_S_GROUPFILE_PRE_UPLOAD_ARG
{
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< 群组ID */
	TUP_CHAR	fileName[IM_D_MAX_NAME_LENGTH];				/**< 文件名 */
	TUP_INT64	fileSize;									/**< 文件大小 */
}IM_S_GROUPFILE_PRE_UPLOAD_ARG;

/**
 * 预上传文件ID
 */
typedef struct tagIM_S_GROUPFILE_PRE_UPLOAD_ACK
{
	TUP_CHAR	prefileId[IM_D_MAX_PASSWORD_LENGTH];		/**< 预上传文件ID */
}IM_S_GROUPFILE_PRE_UPLOAD_ACK;

/**
 * 群共享文件上传结果通知请求
 */
typedef struct tagIM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ARG
{
	TUP_CHAR	prefileId[IM_D_MAX_PASSWORD_LENGTH];		/**< 预上传文件ID */
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< 群组ID */
	TUP_CHAR	uploadUserAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< 上传者账号 */
	TUP_CHAR	fileName[IM_D_MAX_NAME_LENGTH];				/**< 文件名 */
	TUP_INT64	fileSize;									/**< 文件大小 */
	TUP_CHAR	fileURL[IM_D_URL_LENGTH];					/**< 文件URL */
	TUP_BOOL	result;										/**< 上传结果 */
}IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ARG;

/**
 * 群共享文件上传结果通知请求
 */
typedef struct tagIM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ACK
{
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< 文件ID */
	TUP_CHAR	uploadTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< 服务器侧上传成功的时间 */
}IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ACK;

/**
 * 群共享文件预删除请求
 */
typedef struct tagIM_S_GROUPFILE_PRE_DELETE_ARG
{
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< 文件ID */
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< 群组ID */
}IM_S_GROUPFILE_PRE_DELETE_ARG;

/**
 * 群共享文件预删除响应
 */
typedef struct tagIM_S_GROUPFILE_PRE_DELETE_ACK
{
	TUP_CHAR	preDeleteFileID[IM_D_MAX_PASSWORD_LENGTH];	/**< 预删除文件ID */
}IM_S_GROUPFILE_PRE_DELETE_ACK;

/**
 * 群共享文件删除结果通知请求
 */
typedef struct tagIM_S_GROUPFILE_REPORT_DELETE_RESULT_ARG
{
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< 文件ID */
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< 群组ID */
}IM_S_GROUPFILE_REPORT_DELETE_RESULT_ARG;

/**
 * 群共享文件查询请求
 */
typedef struct tagIM_S_GROUPFILE_QUERY_ARG
{
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< 群组ID */
	TUP_CHAR	queryKey[IM_D_GENEAL_LENGTH] ;				/**< 关键字 (必填) */
	IM_E_GROUPFILE_QUERY_TYPE	queryType;					/**< 群共享文件查询类型 */
	TUP_INT32	offset;										/**< 查询偏移量 (选填) */ 
	TUP_INT32	count;										/**< 单次查询结果返回的数量(必填) */ 
}IM_S_GROUPFILE_QUERY_ARG;

/**
 * 群共享文件查询响应
 */
typedef struct tagIM_S_GROUPFILE_QUERY_ACK
{
	TUP_INT32	recordAmount;								/**< 总记录数 */ 
    TUP_S_LIST*	groupFileList;					/**< 群共享文件列表 TUP_S_LIST中的*dada结构类型为 IM_S_GROUPFILE_INFO*/ 
}IM_S_GROUPFILE_QUERY_ACK;

/**
 *  群共享文件变更通知
 */
typedef struct tagIM_S_GROUPFILE_NOTIFY
{
	TUP_CHAR	origin[IM_D_MAX_ACCOUNT_LENGTH];			/**< 发送方账号*/
	TUP_CHAR	target[IM_D_MAX_ACCOUNT_LENGTH];			/**< 接收方账号*/
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< 群组ID */
	IM_E_GROUPFILE_NOTIFE_TYPE	type;						/**< 通知标识*/
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< 文件ID */
	IM_E_GROUPFILE_OPT_TYPE	opttype;						/**< 群空间文件变更类型 */
	TUP_CHAR	timeStamp[IM_D_MAX_TIMESTAMP_LENGTH];		/**< 群空间表更新时间戳ID */
	TUP_INT64	totalSize;									/**< 总空间大小 */
	TUP_INT64	remainSize;									/**< 剩余空间大小 */
}IM_S_GROUPFILE_NOTIFY;


/**
 * 联动状态
 */
typedef struct tagIM_S_LINKAGE_STATUS
{
    TUP_BOOL  bisLinkage;   /**< 联动状态，联动开启: true, 联动关闭: false */
}IM_S_LINKAGE_STATUS;


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#endif //_TUP_IM_EXTENDDEF_H_

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
