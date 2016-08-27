/** 
* @file tup_cloud_record_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM 云录子系统基础接口结构体定义头文件。 \n
*/

/**
*
*  @{
*/

#ifndef __TUP_CLOUD_RECORD_DEF_H__
#define __TUP_CLOUD_RECORD_DEF_H__

#include "tup_def.h"
#include "httpapi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#ifdef __cplusplus
#define CLOUD_RECORD_NULL              0
#else
#define CLOUD_RECORD_NULL              ((void *)0)
#endif


typedef unsigned long CLOUDRECORDHANDLE;         /**< 文件句柄 */
#define CLOUD_RECORD_MAX_FILE_PATH_LEN 511       /**< filepath最大长度 */
#define CLOUD_RECORD_MAX_URL_LEN       511       /**< url最大长度 */
#define CLOUD_RECORD_MAX_TOKEN_LEN     127       /**< token最大长度 */
#define CLOUD_RECORD_MAX_USER_ID_LEN   127       /**< user id最大长度 */
#define CLOUD_RECORD_MAX_RSP_MSG_LEN   511       /**< 最大响应消息长度 */
#define CLOUD_RECORD_MAX_USER_HWID_LEN 63        /**< 最大用户华为ID长度 */
#define CLOUD_RECORD_MAX_USER_NUM_LEN  63        /**< 最大用户号码长度 */

/**
 * 日志级别
 */
typedef enum
{
    CLOUD_RECORD_LOG_NONE        = 0,    /**<  日志关闭 */
    CLOUD_RECORD_LOG_ERROR       = 1,    /**<  ERROR 级别 */
    CLOUD_RECORD_LOG_WARNING     = 2,    /**<  WARNING  级别 */
    CLOUD_RECORD_LOG_INFO        = 3,    /**<  INFOMATION  级别 */
    CLOUD_RECORD_LOG_DEBUG       = 4,    /**<  DEBUG  级别 */
    CLOUD_RECORD_LOG_BUTT
} CLOUD_RECORD_LOG_LEVEL;

/**
 * TLS MODE
 */
typedef enum
{
    EN_CHOUD_RECORD_TLS_CLOSE                = 0, /**< HTTP 模式 */
    EN_CHOUD_RECORD_TLS_VERIFY_NONE          = 1, /**< HTTPS 模式 */
    EN_CHOUD_RECORD_TLS_MODE_BUTT
} EN_CHOUD_RECORD_TLS_MODE;

/**
 * 云录模块错误码
 */
typedef enum
{
    EN_CLOUD_RECORD_OK = 0,
    EN_CLOUD_RECORD_INIT_FAIL,                       /**< 1 Init fail */
    EN_CLOUD_RECORD_UNINIT,                          /**< 2 uninit */
    EN_CLOUD_RECORD_INVALID_PARAM,                   /**< 3 invalid param */
    EN_CLOUD_RECORD_INVALID_HANDLE,                  /**< 4 invalid handle */
    EN_CLOUD_RECORD_HANDLE_INUSE,                    /**< 5 handle in using, can't be set*/
    EN_CLOUD_RECORD_HANDLE_STATE_ERROR,              /**< 6 current handle state not support this operation*/
    EN_CLOUD_RECORD_ALLOC_MEM_FAIL,                  /**< 7 alloc fail */
    EN_CLOUD_RECORD_CREATE_HANDLE_FAIL,              /**< 8 alloc handle fail */
    EN_CLOUD_RECORD_INVALID_TLS_MODE,                /**< 9 tls mode error */
    EN_CLOUD_RECORD_INVALID_URL,                     /**< 10 invalid URL */
    EN_CLOUD_RECORD_INVALID_HEAD_TYPE,               /**< 11 invalid head type */
    EN_CLOUD_RECORD_OPEN_LOG_FAIL,                   /**< 12 open log file fail */
    EN_CLOUD_RECORD_WRITE_LOG_FAIL,                  /**< 13 write log file fail */
    EN_CLOUD_RECORD_INVALID_FILEPATH,                /**< 14 invalid file path */
    EN_CLOUD_RECORD_HANDLE_RELEASED,                 /**< 15 handle has been released */
    EN_CLOUD_RECORD_CREATE_MUTEX_FAIL,               /**< 16 create mutex fail */
    EN_CLOUD_RECORD_LOCK_MUTEX_FAIL,                 /**< 17 lock mutex fail*/
    EN_CLOUD_RECORD_UNLOCK_MUTEX_FAIL,               /**< 18 unlock mutex fail */
    EN_CLOUD_RECORD_CREATE_THREAD_FAIL,              /**< 19 create thread fail */
    EN_CLOUD_RECORD_NOT_SUPPORT,                     /**< 20 not support this function */
    EN_CLOUD_RECORD_SVN_SOCKET_CREATE_FAIL,          /**< 21 svn socket create fail */
    EN_CLOUD_RECORD_SVN_SOCKET_CONNECT_FAIL,         /**< 22 svn socket connect fail */
    EN_CLOUD_RECORD_SVN_SOCKET_SLECET_FAIL,          /**< 23 svn socket select fail */
    EN_CLOUD_RECORD_SVN_SOCKET_SEND_FAIL,            /**< 24 svn socket send fail */
    EN_CLOUD_RECORD_SVN_SOCKET_RECV_FAIL,            /**< 25 svn socket recv fail */
    EN_CLOUD_RECORD_GETHOSTNAME_FAIL,                /**< 26 get hostname fail */
    EN_CLOUD_RECORD_NET_NTOA_FAIL,                   /**< 27 IP net transfer fail*/
    EN_CLOUD_RECORD_RESPONSE_PARSE_ERR,              /**< 28 response parse fail */
    EN_CLOUD_RECORD_INVALID_AUTH_MODE,               /**< 29.invalid auth mode */
    EN_CLOUD_RECORD_NOT_LOGIN,                       /**< 30 is not login  */
    EN_CLOUD_RECORD_LOGINING,                        /**< 31 is  logining  */
    EN_CLOUD_RECORD_UPLOAD_DOWNLOAD_TIMEOUT,         /**< 32 is  TIMEOUT  */
    EN_CLOUD_RECORD_LOGINED,                         /**< 33 is  logined  */
    EN_CLOUD_RECORD_INITED,                          /**< 34 is  inited  */
    EN_CLOUD_RECORD_LOGPATH_TOOLONG,                 /**< 35 is  LogPath is too long */
    EN_CLOUD_RECORD_LOGPATH_EMPTY,                   /**< 36 is  LogPath is empty */

    EN_CLOUD_RECORD_CURLE_UNSUPPORTED_PROTOCOL = 101,    /**< 101 */
    EN_CLOUD_RECORD_CURLE_FAILED_INIT,                   /**< 102 */
    EN_CLOUD_RECORD_CURLE_URL_MALFORMAT,                 /**< 103 */
    EN_CLOUD_RECORD_CURLE_NOT_BUILT_IN,                  /**< 104 */
    EN_CLOUD_RECORD_CURLE_COULDNT_RESOLVE_PROXY,         /**< 105 */
    EN_CLOUD_RECORD_CURLE_COULDNT_RESOLVE_HOST,          /**< 106 */
    EN_CLOUD_RECORD_CURLE_COULDNT_CONNECT,               /**< 107 */
    EN_CLOUD_RECORD_CURLE_FTP_WEIRD_SERVER_REPLY,        /**< 108 */
    EN_CLOUD_RECORD_CURLE_REMOTE_ACCESS_DENIED,    /**< 109 a service was denied by the server
                                                   <br>due to lack of access - when login fails this is not returned. */
    EN_CLOUD_RECORD_CURLE_FTP_ACCEPT_FAILED,               /**< 110 */
    EN_CLOUD_RECORD_CURLE_FTP_WEIRD_PASS_REPLY,            /**< 111 */
    EN_CLOUD_RECORD_CURLE_FTP_ACCEPT_TIMEOUT,              /**< 112 - timeout occurred accepting server*/
    EN_CLOUD_RECORD_CURLE_FTP_WEIRD_PASV_REPLY,            /**< 113 */
    EN_CLOUD_RECORD_CURLE_FTP_WEIRD_227_FORMAT,            /**< 114 */
    EN_CLOUD_RECORD_CURLE_FTP_CANT_GET_HOST,               /**< 115 */
    EN_CLOUD_RECORD_CURLE_OBSOLETE16,                      /**< 116 - NOT USED */
    EN_CLOUD_RECORD_CURLE_FTP_COULDNT_SET_TYPE,            /**< 117 */
    EN_CLOUD_RECORD_CURLE_PARTIAL_FILE,                    /**< 118 */
    EN_CLOUD_RECORD_CURLE_FTP_COULDNT_RETR_FILE,           /**< 119 */
    EN_CLOUD_RECORD_CURLE_OBSOLETE20,                      /**< 120 - NOT USED */
    EN_CLOUD_RECORD_CURLE_QUOTE_ERROR,                     /**< 121 - quote command failure */
    EN_CLOUD_RECORD_CURLE_CLOUD_RECORD_RETURNED_ERROR,     /**< 122 */
    EN_CLOUD_RECORD_CURLE_WRITE_ERROR,                     /**< 123 */
    EN_CLOUD_RECORD_CURLE_OBSOLETE24,                      /**< 124 - NOT USED */
    EN_CLOUD_RECORD_CURLE_UPLOAD_FAILED,                   /**< 125 - failed upload "command" */
    EN_CLOUD_RECORD_CURLE_READ_ERROR,                      /**< 126 - couldn't open/read from file */
    EN_CLOUD_RECORD_CURLE_OUT_OF_MEMORY,                   /**< 127 CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
                                                                <br>instead of a memory allocation error if CURL_DOES_CONVERSIONS is defined  */
    EN_CLOUD_RECORD_CURLE_OPERATION_TIMEDOUT,              /**< 128 - the timeout time was reached */
    EN_CLOUD_RECORD_CURLE_OBSOLETE29,                      /**< 129 - NOT USED */
    EN_CLOUD_RECORD_CURLE_FTP_PORT_FAILED,                 /**< 130 - FTP PORT operation failed */
    EN_CLOUD_RECORD_CURLE_FTP_COULDNT_USE_REST,            /**< 131 - the REST command failed */
    EN_CLOUD_RECORD_CURLE_OBSOLETE32,                      /**< 132 - NOT USED */
    EN_CLOUD_RECORD_CURLE_RANGE_ERROR,                     /**< 133 - RANGE "command" didn't work */
    EN_CLOUD_RECORD_CURLE_CLOUD_RECORD_POST_ERROR,         /**< 134 */
    EN_CLOUD_RECORD_CURLE_SSL_CONNECT_ERROR,               /**< 135 - wrong when connecting with SSL */
    EN_CLOUD_RECORD_CURLE_BAD_DOWNLOAD_RESUME,             /**< 136 - couldn't resume download */
    EN_CLOUD_RECORD_CURLE_FILE_COULDNT_READ_FILE,          /**< 137 */
    EN_CLOUD_RECORD_CURLE_LDAP_CANNOT_BIND,                /**< 138 */
    EN_CLOUD_RECORD_CURLE_LDAP_SEARCH_FAILED,              /**< 139 */
    EN_CLOUD_RECORD_CURLE_OBSOLETE40,                      /**< 140 - NOT USED */
    EN_CLOUD_RECORD_CURLE_FUNCTION_NOT_FOUND,              /**< 141 */
    EN_CLOUD_RECORD_CURLE_ABORTED_BY_CALLBACK,             /**< 142 */
    EN_CLOUD_RECORD_CURLE_BAD_FUNCTION_ARGUMENT,           /**< 143 */
    EN_CLOUD_RECORD_CURLE_OBSOLETE44,                      /**< 144 - NOT USED */
    EN_CLOUD_RECORD_CURLE_INTERFACE_FAILED,                /**< 145 - CURLOPT_INTERFACE failed */
    EN_CLOUD_RECORD_CURLE_OBSOLETE46,                      /**< 146 - NOT USED */
    EN_CLOUD_RECORD_CURLE_TOO_MANY_REDIRECTS,              /**< 147 - catch endless re-direct loops */
    EN_CLOUD_RECORD_CURLE_UNKNOWN_OPTION,                  /**< 148 - User specified an unknown option */
    EN_CLOUD_RECORD_CURLE_TELNET_OPTION_SYNTAX,            /**< 149 - Malformed telnet option */
    EN_CLOUD_RECORD_CURLE_OBSOLETE50,                      /**< 150 - NOT USED */
    EN_CLOUD_RECORD_CURLE_PEER_FAILED_VERIFICATION, /**< 151 - peer's certificate or fingerprint wasn't verified fine */
    EN_CLOUD_RECORD_CURLE_GOT_NOTHING,             /**< 152 - when this is a specific error */
    EN_CLOUD_RECORD_CURLE_SSL_ENGINE_NOTFOUND,     /**< 153 - SSL crypto engine not found */
    EN_CLOUD_RECORD_CURLE_SSL_ENGINE_SETFAILED,    /**< 154 - can not set SSL crypto engine as default */
    EN_CLOUD_RECORD_CURLE_SEND_ERROR,              /**< 155 - failed sending network data */
    EN_CLOUD_RECORD_CURLE_RECV_ERROR,              /**< 156 - failure in receiving network data */
    EN_CLOUD_RECORD_CURLE_OBSOLETE57,              /**< 157 - NOT IN USE */
    EN_CLOUD_RECORD_CURLE_SSL_CERTPROBLEM,         /**< 158 - problem with the local certificate */
    EN_CLOUD_RECORD_CURLE_SSL_CIPHER,              /**< 159 - couldn't use specified cipher */
    EN_CLOUD_RECORD_CURLE_SSL_CACERT,              /**< 160 - problem with the CA cert (path?) */
    EN_CLOUD_RECORD_CURLE_BAD_CONTENT_ENCODING,    /**< 161 - Unrecognized/bad encoding */
    EN_CLOUD_RECORD_CURLE_LDAP_INVALID_URL,        /**< 162 - Invalid LDAP URL */
    EN_CLOUD_RECORD_CURLE_FILESIZE_EXCEEDED,       /**< 163 - Maximum file size exceeded */
    EN_CLOUD_RECORD_CURLE_USE_SSL_FAILED,          /**< 164 - Requested FTP SSL level failed */
    EN_CLOUD_RECORD_CURLE_SEND_FAIL_REWIND,        /**< 165 - Sending the data requires a rewind that failed */
    EN_CLOUD_RECORD_CURLE_SSL_ENGINE_INITFAILED,   /**< 166 - failed to initialise ENGINE */
    EN_CLOUD_RECORD_CURLE_LOGIN_DENIED,            /**< 167 - user, password or similar was not accepted and we failed to login */
    EN_CLOUD_RECORD_CURLE_TFTP_NOTFOUND,           /**< 168 - file not found on server */
    EN_CLOUD_RECORD_CURLE_TFTP_PERM,               /**< 169 - permission problem on server */
    EN_CLOUD_RECORD_CURLE_REMOTE_DISK_FULL,        /**< 170 - out of disk space on server */
    EN_CLOUD_RECORD_CURLE_TFTP_ILLEGAL,            /**< 171 - Illegal TFTP operation */
    EN_CLOUD_RECORD_CURLE_TFTP_UNKNOWNID,          /**< 172 - Unknown transfer ID */
    EN_CLOUD_RECORD_CURLE_REMOTE_FILE_EXISTS,      /**< 173 - File already exists */
    EN_CLOUD_RECORD_CURLE_TFTP_NOSUCHUSER,         /**< 174 - No such user */
    EN_CLOUD_RECORD_CURLE_CONV_FAILED,             /**< 175 - conversion failed */
    EN_CLOUD_RECORD_CURLE_CONV_REQD,               /**< 176 - caller must register conversion callbacks using curl_easy_setopt options
                                                   <br>CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                                                   <br>CURLOPT_CONV_TO_NETWORK_FUNCTION, and
                                                   <br>CURLOPT_CONV_FROM_UTF8_FUNCTION */
    EN_CLOUD_RECORD_CURLE_SSL_CACERT_BADFILE,      /**< 177 - could not load CACERT file, missing or wrong format */
    EN_CLOUD_RECORD_CURLE_REMOTE_FILE_NOT_FOUND,   /**< 178 - remote file not found */
    EN_CLOUD_RECORD_CURLE_SSH,                     /**< 179 - error from the SSH layer, somewhat
                                                   <br>generic so the error message will be or interest when this has happened */
    EN_CLOUD_RECORD_CURLE_SSL_SHUTDOWN_FAILED,     /**< 180 - Failed to shut down the SSL connection */
    EN_CLOUD_RECORD_CURLE_AGAIN,                   /**< 181 - socket is not ready for send/recv,wait till it's ready and try again */
    EN_CLOUD_RECORD_CURLE_SSL_CRL_BADFILE,         /**< 182 - could not load CRL file, missing or wrong format */
    EN_CLOUD_RECORD_CURLE_SSL_ISSUER_ERROR,        /**< 183 - Issuer check failed. */
    EN_CLOUD_RECORD_CURLE_FTP_PRET_FAILED,         /**< 184 - a PRET command failed */
    EN_CLOUD_RECORD_CURLE_RTSP_CSEQ_ERROR,         /**< 185 - mismatch of RTSP CSeq numbers */
    EN_CLOUD_RECORD_CURLE_RTSP_SESSION_ERROR,      /**< 186 - mismatch of RTSP Session Ids */
    EN_CLOUD_RECORD_CURLE_FTP_BAD_FILE_LIST,       /**< 187 - unable to parse FTP file list */
    EN_CLOUD_RECORD_CURLE_CHUNK_FAILED,            /**< 188 - chunk callback reported error */

    EN_CLOUD_RECORD_CURL_CREATE_HANDLE_FAIL = 201,   /**< 201 */
    EN_CLOUD_RECORD_CURL_SET_HEAD_FAIL,              /**< 202 */

    EN_CLOUD_RECORD_ERRORCODE_BUTT               /**< never used */
} CLOUD_RECORD_E_ERRORCODE;

/**
 * 日志配置
 */
typedef struct tagST_CLOUD_RECORD_LOG_CONFIG
{
    CLOUD_RECORD_LOG_LEVEL level;                                            /**<  日志解包 */
    TUP_UINT32             log_file_size;                                    /**<  日志文件大小 (单位：M，范围【1,60】） */
    TUP_CHAR               file_path[CLOUD_RECORD_MAX_FILE_PATH_LEN + 1];    /**<  日志路径 */
} CLOUD_RECORD_LOG_CONFIG;

/**
 * 云录初始化配置
 */
typedef struct tagST_CLOUD_RECORD_INIT_CONFIG
{
    CLOUD_RECORD_LOG_CONFIG log_config;           /**<  日志配置文件 */
    TUP_UINT32              handle_num;           /**<  （支持的控制块数，不超过OFFLINE_D_MAX_MUTI_TRANS） */
} CLOUD_RECORD_INIT_CONFIG;

/**
 * 获取云录服务器配置信息请求结构体
 */
typedef struct tagST_CLOUD_RECORD_GET_CFG_REQ
{
    EN_CHOUD_RECORD_TLS_MODE tls_mode;    /**<   0表示 http  1表示 https */
    TUP_UINT32               time_out;    /**<   请求超时时间,单位:s(秒),取值范围[1,60],默认:10(不在取值范围内取默认值) */
    TUP_UINT32               retry_num;   /**<   请求重试次数,取值范围[0,3],默认:0(不重试) */
    void *                   user_data;   /**<   用户自定义数据,对应CLOUD_RECORD_GET_CFG_RSP_NOTIFY参数void* user_data，组件不作任何处理，仅传递数据 */

    TUP_CHAR                 url[CLOUD_RECORD_MAX_URL_LEN + 1];         /**<  url */
    TUP_CHAR                 user_id[CLOUD_RECORD_MAX_USER_ID_LEN + 1]; /**<  userid */
    TUP_CHAR                 token[CLOUD_RECORD_MAX_TOKEN_LEN + 1];     /**<  token */
} CLOUD_RECORD_GET_CFG_REQ;

/**
 * 获取云录服务器配置信息响应结构体
 */
typedef struct tagST_CLOUD_RECORD_GET_CFG_RSP
{
    TUP_UINT32 status_code;                                /**<  HTTP链接响应码,xxx */
    TUP_UINT32 rsp_code;                                   /**<  服务器响应码,xxx */
    TUP_CHAR   rsp_msg[CLOUD_RECORD_MAX_RSP_MSG_LEN + 1];  /**<  响应消息字符 */

    TUP_CHAR   espace_token[CLOUD_RECORD_MAX_TOKEN_LEN + 1];          /**<   上传到云录带的token，现为一个特定的值 */
    TUP_ULONG  upload_time;                                           /**<   收到服务器响应的uploadtime，现有功能TUP没有用到该数据，和服务器交互不带该参数 */
    TUP_ULONG  hotline_time;                                          /**<   收到服务器响应的hotlinetime，现有功能TUP没有用到该数据，和服务器交互不带该参数 */
    TUP_ULONG  server_time;                                           /**<   收到服务器响应的servertime */
    TUP_ULONG  export_count;                                          /**<   收到服务器响应的exportcount，现有功能TUP没有用到该数据，和服务器交互不带该参数 */
    TUP_ULONG  hw_upload_time;                                        /**<   收到服务器响应的hwuploadtime，现有功能TUP没有用到该数据，和服务器交互不带该参数 */
} CLOUD_RECORD_GET_CFG_RSP;

/**
 * 上报云录服务器通话信息结构体
 */
typedef struct tagST_CLOUD_RECORD_SEND_CALL_INFO_REQ
{
    EN_CHOUD_RECORD_TLS_MODE tls_mode;    /**<   TLS模式，取值参见EN_CHOUD_RECORD_TLS_MODE */
    TUP_UINT32               time_out;    /**<   请求超时时间,单位:s(秒),取值范围[1,60],默认:10(不在取值范围内取默认值) */
    TUP_UINT32               retry_num;   /**<   请求重试次数,取值范围[0,3],默认:0(不重试) */
    void *                   user_data;   /**<   用户自定义数据,对应CLOUD_RECORD_SEND_CALL_INFO_RSP_NOTIFY参数void* user_data,组件不作任何处理,仅传递数据 */

    TUP_CHAR                 url[CLOUD_RECORD_MAX_URL_LEN + 1];           /**<  url */
    TUP_CHAR                 user_id[CLOUD_RECORD_MAX_USER_ID_LEN + 1];   /**<  userid */
    TUP_CHAR                 token[CLOUD_RECORD_MAX_TOKEN_LEN + 1];       /**<  token */

    TUP_CHAR                 from_id[CLOUD_RECORD_MAX_USER_HWID_LEN + 1];    /**<   fromid 比如工号 */
    TUP_CHAR                 from_number[CLOUD_RECORD_MAX_USER_NUM_LEN + 1]; /**<    fromnumber  类似电话号码 */
    TUP_CHAR                 to_id[CLOUD_RECORD_MAX_USER_HWID_LEN + 1];      /**<   toid  比如工号 */
    TUP_CHAR                 to_number[CLOUD_RECORD_MAX_USER_NUM_LEN + 1];   /**<    tonumber 类似电话号码 */
    TUP_UINT32               status;                                         /**<   状态  用 0，1，2，3，4,不同来区分通话的不同状态
                                                                             <br>0表示 eSpace电话，主叫方开始发起呼叫 
                                                                             <br>1表示 eSpace电话，主叫通话正常通话结束 
                                                                             <br>2表示 eSpace电话，主叫通话未接通 
                                                                             <br>3表示 eSpace电话，被叫收到电话后，正常通话结束 */

    TUP_ULONG                long_talk_time;                                 /**<   通话时长 */
    TUP_ULONG                in_time;                                        /**<   服务器响应的servertime加上本地校正时间 */
} CLOUD_RECORD_SEND_CALL_INFO_REQ;

/**
 * 上报云录服务器通话信息响应结构体
 */
typedef struct tagST_CLOUD_RECORD_SEND_CALL_INFO_RSP
{
    TUP_UINT32 status_code;                                /**<  HTTP链接响应码,xxx */
    TUP_UINT32 rsp_code;                                   /**<  服务器响应码,xxx */
    TUP_CHAR   rsp_msg[CLOUD_RECORD_MAX_RSP_MSG_LEN + 1];  /**<  响应消息字符 */
} CLOUD_RECORD_SEND_CALL_INFO_RSP;


/**
 * @brief 获取云录服务器配置信息回调
 * 
 * @param [in] CLOUDRECORDHANDLE handle            <b>:</b> 句柄
 * @param [in] CLOUD_RECORD_GET_CFG_RSP *rsp_body  <b>:</b> 获取云录服务器配置信息响应
 * @param [in] void *user_data                     <b>:</b> 用户自定义信息
 * @param [out] NA
 * @retval typedef int (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see 
 **/
typedef int (*CLOUD_RECORD_GET_CFG_RSP_NOTIFY)(CLOUDRECORDHANDLE handle, CLOUD_RECORD_GET_CFG_RSP *rsp_body, void *user_data);


/**
 * @brief 上报云录服务器通话信息回调
 * 
 * @param [in] CLOUDRECORDHANDLE handle                   <b>:</b> 句柄
 * @param [in] CLOUD_RECORD_SEND_CALL_INFO_RSP *rsp_body  <b>:</b> 上报云录服务器通话信息响应
 * @param [in] void *user_data                            <b>:</b> 用户自定义信息
 * @param [out] NA
 * @retval typedef int (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see 
 **/
typedef int (*CLOUD_RECORD_SEND_CALL_INFO_RSP_NOTIFY)(CLOUDRECORDHANDLE handle, CLOUD_RECORD_SEND_CALL_INFO_RSP *rsp_body, void *user_data);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif  // __TUP_CLOUD_RECORD_DEF_H__

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
