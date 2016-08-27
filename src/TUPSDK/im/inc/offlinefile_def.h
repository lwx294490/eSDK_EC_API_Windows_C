/** 
* @file offlinefile_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM 离线文件子系统基础接口结构体定义头文件。 \n
*       对于内存使用原则，采用谁分配谁释放的原则        \n
*/

/**
*
*  @{
*/



#ifndef __OFFLINEFILE_DEF_H__
#define __OFFLINEFILE_DEF_H__

#include "tup_def.h"
#include "httpapi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#ifdef __cplusplus
#define OFFLINE_NULL    0
#else
#define OFFLINE_NULL    ((void *)0)
#endif

// 文件句柄
typedef unsigned long               OFFLINEHANDLE;

#define OFFLINE_D_MAX_FILENAME      255                     /**< 最长文件名长度 */
#define OFFLINE_D_DEFAULT_CTRL_NUM  100                     /**< 默认支持的控制块数量 */
#define OFFLINE_D_MAX_URL_NUM       6                       /**< 服务器地址列表最大值 */
#define OFFLINE_D_MAX_UPLOAD_NUM    3                       /**< 并行上传的最多文件数 */


#define EN_OFFLINE_ERR_STATR        0x08006100UL                    /**< 离线文件传输起始错误码：TUP_ERR_SECTION & TUP_IM_ERR_SUB_SECTION & IM子模块(0x01 << 8) */    
#define EN_OFFLINE_CURLE_ERR_START  (0x08006100UL + 0x64UL)         /**< HTTP中Curl错误码 */

/**
 * 离线文件模块错误码
 */
typedef enum tagOFFLINE_E_ERRORCODE{
    EN_OFFLINE_OK = 0,
    EN_OFFLINE_INIT_FAIL = EN_OFFLINE_ERR_STATR + 1,    /**< 1 Init fail */
    EN_OFFLINE_UNINIT,                          /**< 2 uninit */
    EN_OFFLINE_INVALID_PARAM,                   /**< 3 invalid param */
    EN_OFFLINE_INVALID_HANDLE,                  /**< 4 invalid handle */ 
    EN_OFFLINE_HANDLE_INUSE,                    /**< 5 handle in using, can't be set*/ 
    EN_OFFLINE_HANDLE_STATE_ERROR,              /**< 6 current handle state not support this operation*/
    EN_OFFLINE_ALLOC_MEM_FAIL,                  /**< 7 alloc fail */
    EN_OFFLINE_CREATE_HANDLE_FAIL,              /**< 8 alloc handle fail */
    EN_OFFLINE_INVALID_TLS_MODE,                /**< 9 tls mode error */
    EN_OFFLINE_INVALID_URL,                     /**< 10 invalid URL */
    EN_OFFLINE_INVALID_HEAD_TYPE,               /**< 11 invalid head type */
    EN_OFFLINE_OPEN_LOG_FAIL,                   /**< 12 open log file fail */
    EN_OFFLINE_WRITE_LOG_FAIL,                  /**< 13 write log file fail */
    EN_OFFLINE_INVALID_FILEPATH,                /**< 14 invalid file path */
    EN_OFFLINE_HANDLE_RELEASED,                 /**< 15 handle has been released */
    EN_OFFLINE_CREATE_MUTEX_FAIL,               /**< 16 create mutex fail */
    EN_OFFLINE_LOCK_MUTEX_FAIL,                 /**< 17 lock mutex fail*/
    EN_OFFLINE_UNLOCK_MUTEX_FAIL,               /**< 18 unlock mutex fail */
    EN_OFFLINE_CREATE_THREAD_FAIL,              /**< 19 create thread fail */
    EN_OFFLINE_NOT_SUPPORT,                     /**< 20 not support this function */
    EN_OFFLINE_SVN_SOCKET_CREATE_FAIL,          /**< 21 svn socket create fail */
    EN_OFFLINE_SVN_SOCKET_CONNECT_FAIL,         /**< 22 svn socket connect fail */
    EN_OFFLINE_SVN_SOCKET_SLECET_FAIL,          /**< 23 svn socket select fail */
    EN_OFFLINE_SVN_SOCKET_SEND_FAIL,            /**< 24 svn socket send fail */
    EN_OFFLINE_SVN_SOCKET_RECV_FAIL,            /**< 25 svn socket recv fail */
    EN_OFFLINE_GETHOSTNAME_FAIL,                /**< 26 get hostname fail */
    EN_OFFLINE_NET_NTOA_FAIL,                   /**< 27 IP net transfer fail*/
    EN_OFFLINE_RESPONSE_PARSE_ERR,              /**< 28 response parse fail */
    EN_OFFLINE_INVALID_AUTH_MODE,               /**< 29.invalid auth mode */
    EN_OFFLINE_NOT_LOGIN,                       /**< 30 is not login  */
    EN_OFFLINE_LOGINING,                        /**< 31 is  logining  */
    EN_OFFLINE_UPLOAD_DOWNLOAD_TIMEOUT,         /**< 32 is  TIMEOUT  */
    EN_OFFLINE_LOGINED,                         /**< 33 is  logined  */
    EN_OFFLINE_INITED,                          /**< 34 is  inited  */
    EN_OFFLINE_LOGPATH_TOOLONG,                 /**< 35 is  LogPath is too long */
    EN_OFFLINE_LOGPATH_EMPTY,                   /**< 36 is  LogPath is empty */

    EN_OFFLINE_CURLE_UNSUPPORTED_PROTOCOL = EN_OFFLINE_CURLE_ERR_START + 1,    /**< 101 */
    EN_OFFLINE_CURLE_FAILED_INIT,             /**< 102 */
    EN_OFFLINE_CURLE_URL_MALFORMAT,           /**< 103 */
    EN_OFFLINE_CURLE_NOT_BUILT_IN,            /**< 104 */
    EN_OFFLINE_CURLE_COULDNT_RESOLVE_PROXY,   /**< 105 */
    EN_OFFLINE_CURLE_COULDNT_RESOLVE_HOST,    /**< 106 */
    EN_OFFLINE_CURLE_COULDNT_CONNECT,         /**< 107 */
    EN_OFFLINE_CURLE_FTP_WEIRD_SERVER_REPLY,  /**< 108 */
    EN_OFFLINE_CURLE_REMOTE_ACCESS_DENIED,    /**< 109 a service was denied by the server
                                                        <br>due to lack of access - when login fails
                                                        <br>this is not returned. */
    EN_OFFLINE_CURLE_FTP_ACCEPT_FAILED,       /**< 110 */
    EN_OFFLINE_CURLE_FTP_WEIRD_PASS_REPLY,    /**< 111 */
    EN_OFFLINE_CURLE_FTP_ACCEPT_TIMEOUT,      /**< 112 - timeout occurred accepting server*/
    EN_OFFLINE_CURLE_FTP_WEIRD_PASV_REPLY,    /**< 113 */
    EN_OFFLINE_CURLE_FTP_WEIRD_227_FORMAT,    /**< 114 */
    EN_OFFLINE_CURLE_FTP_CANT_GET_HOST,       /**< 115 */
    EN_OFFLINE_CURLE_OBSOLETE16,              /**< 116 - NOT USED */
    EN_OFFLINE_CURLE_FTP_COULDNT_SET_TYPE,    /**< 117 */
    EN_OFFLINE_CURLE_PARTIAL_FILE,            /**< 118 */
    EN_OFFLINE_CURLE_FTP_COULDNT_RETR_FILE,   /**< 119 */
    EN_OFFLINE_CURLE_OBSOLETE20,              /**< 120 - NOT USED */
    EN_OFFLINE_CURLE_QUOTE_ERROR,             /**< 121 - quote command failure */
    EN_OFFLINE_CURLE_OFFLINE_RETURNED_ERROR,     /**< 122 */
    EN_OFFLINE_CURLE_WRITE_ERROR,             /**< 123 */
    EN_OFFLINE_CURLE_OBSOLETE24,              /**< 124 - NOT USED */
    EN_OFFLINE_CURLE_UPLOAD_FAILED,           /**< 125 - failed upload "command" */
    EN_OFFLINE_CURLE_READ_ERROR,              /**< 126 - couldn't open/read from file */
    EN_OFFLINE_CURLE_OUT_OF_MEMORY,           /**< 127 - CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
                                                        <br>instead of a memory allocation error if CURL_DOES_CONVERSIONS is defined */
    EN_OFFLINE_CURLE_OPERATION_TIMEDOUT,      /**< 128 - the timeout time was reached */
    EN_OFFLINE_CURLE_OBSOLETE29,              /**< 129 - NOT USED */
    EN_OFFLINE_CURLE_FTP_PORT_FAILED,         /**< 130 - FTP PORT operation failed */
    EN_OFFLINE_CURLE_FTP_COULDNT_USE_REST,    /**< 131 - the REST command failed */
    EN_OFFLINE_CURLE_OBSOLETE32,              /**< 132 - NOT USED */
    EN_OFFLINE_CURLE_RANGE_ERROR,             /**< 133 - RANGE "command" didn't work */
    EN_OFFLINE_CURLE_OFFLINE_POST_ERROR,         /**< 134 */
    EN_OFFLINE_CURLE_SSL_CONNECT_ERROR,       /**< 135 - wrong when connecting with SSL */
    EN_OFFLINE_CURLE_BAD_DOWNLOAD_RESUME,     /**< 136 - couldn't resume download */
    EN_OFFLINE_CURLE_FILE_COULDNT_READ_FILE,  /**< 137 */
    EN_OFFLINE_CURLE_LDAP_CANNOT_BIND,        /**< 138 */
    EN_OFFLINE_CURLE_LDAP_SEARCH_FAILED,      /**< 139 */
    EN_OFFLINE_CURLE_OBSOLETE40,              /**< 140 - NOT USED */
    EN_OFFLINE_CURLE_FUNCTION_NOT_FOUND,      /**< 141 */
    EN_OFFLINE_CURLE_ABORTED_BY_CALLBACK,     /**< 142 */
    EN_OFFLINE_CURLE_BAD_FUNCTION_ARGUMENT,   /**< 143 */
    EN_OFFLINE_CURLE_OBSOLETE44,              /**< 144 - NOT USED */
    EN_OFFLINE_CURLE_INTERFACE_FAILED,        /**< 145 - CURLOPT_INTERFACE failed */
    EN_OFFLINE_CURLE_OBSOLETE46,              /**< 146 - NOT USED */
    EN_OFFLINE_CURLE_TOO_MANY_REDIRECTS ,     /**< 147 - catch endless re-direct loops */
    EN_OFFLINE_CURLE_UNKNOWN_OPTION,          /**< 148 - User specified an unknown option */
    EN_OFFLINE_CURLE_TELNET_OPTION_SYNTAX ,   /**< 149 - Malformed telnet option */
    EN_OFFLINE_CURLE_OBSOLETE50,              /**< 150 - NOT USED */
    EN_OFFLINE_CURLE_PEER_FAILED_VERIFICATION, /**< 151 - peer's certificate or fingerprint wasn't verified fine */
    EN_OFFLINE_CURLE_GOT_NOTHING,             /**< 152 - when this is a specific error */
    EN_OFFLINE_CURLE_SSL_ENGINE_NOTFOUND,     /**< 153 - SSL crypto engine not found */
    EN_OFFLINE_CURLE_SSL_ENGINE_SETFAILED,    /**< 154 - can not set SSL crypto engine as default */
    EN_OFFLINE_CURLE_SEND_ERROR,              /**< 155 - failed sending network data */
    EN_OFFLINE_CURLE_RECV_ERROR,              /**< 156 - failure in receiving network data */
    EN_OFFLINE_CURLE_OBSOLETE57,              /**< 157 - NOT IN USE */
    EN_OFFLINE_CURLE_SSL_CERTPROBLEM,         /**< 158 - problem with the local certificate */
    EN_OFFLINE_CURLE_SSL_CIPHER,              /**< 159 - couldn't use specified cipher */
    EN_OFFLINE_CURLE_SSL_CACERT,              /**< 160 - problem with the CA cert (path?) */
    EN_OFFLINE_CURLE_BAD_CONTENT_ENCODING,    /**< 161 - Unrecognized/bad encoding */
    EN_OFFLINE_CURLE_LDAP_INVALID_URL,        /**< 162 - Invalid LDAP URL */
    EN_OFFLINE_CURLE_FILESIZE_EXCEEDED,       /**< 163 - Maximum file size exceeded */
    EN_OFFLINE_CURLE_USE_SSL_FAILED,          /**< 164 - Requested FTP SSL level failed */
    EN_OFFLINE_CURLE_SEND_FAIL_REWIND,        /**< 165 - Sending the data requires a rewind that failed */
    EN_OFFLINE_CURLE_SSL_ENGINE_INITFAILED,   /**< 166 - failed to initialise ENGINE */
    EN_OFFLINE_CURLE_LOGIN_DENIED,            /**< 167 - user, password or similar was not accepted and we failed to login */
    EN_OFFLINE_CURLE_TFTP_NOTFOUND,           /**< 168 - file not found on server */
    EN_OFFLINE_CURLE_TFTP_PERM,               /**< 169 - permission problem on server */
    EN_OFFLINE_CURLE_REMOTE_DISK_FULL,        /**< 170 - out of disk space on server */
    EN_OFFLINE_CURLE_TFTP_ILLEGAL,            /**< 171 - Illegal TFTP operation */
    EN_OFFLINE_CURLE_TFTP_UNKNOWNID,          /**< 172 - Unknown transfer ID */
    EN_OFFLINE_CURLE_REMOTE_FILE_EXISTS,      /**< 173 - File already exists */
    EN_OFFLINE_CURLE_TFTP_NOSUCHUSER,         /**< 174 - No such user */
    EN_OFFLINE_CURLE_CONV_FAILED,             /**< 175 - conversion failed */
    EN_OFFLINE_CURLE_CONV_REQD,               /**< 176 - caller must register conversion
                                    <br>callbacks using curl_easy_setopt options
                                    <br>CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                                    <br>CURLOPT_CONV_TO_NETWORK_FUNCTION, and
                                    <br>CURLOPT_CONV_FROM_UTF8_FUNCTION */
    EN_OFFLINE_CURLE_SSL_CACERT_BADFILE,      /**< 177 - could not load CACERT file, missing or wrong format */
    EN_OFFLINE_CURLE_REMOTE_FILE_NOT_FOUND,   /**< 178 - remote file not found */
    EN_OFFLINE_CURLE_SSH,                     /**< 179 - error from the SSH layer, somewhat
                                    <br>generic so the error message will be of
                                    <br>interest when this has happened */
    EN_OFFLINE_CURLE_SSL_SHUTDOWN_FAILED,     /**< 180 - Failed to shut down the SSL connection */
    EN_OFFLINE_CURLE_AGAIN,                   /**< 181 - socket is not ready for send/recv, wait till it's ready and try again */
    EN_OFFLINE_CURLE_SSL_CRL_BADFILE,         /**< 182 - could not load CRL file, missing or wrong format */
    EN_OFFLINE_CURLE_SSL_ISSUER_ERROR,        /**< 183 - Issuer check failed. */
    EN_OFFLINE_CURLE_FTP_PRET_FAILED,         /**< 184 - a PRET command failed */
    EN_OFFLINE_CURLE_RTSP_CSEQ_ERROR,         /**< 185 - mismatch of RTSP CSeq numbers */
    EN_OFFLINE_CURLE_RTSP_SESSION_ERROR,      /**< 186 - mismatch of RTSP Session Ids */
    EN_OFFLINE_CURLE_FTP_BAD_FILE_LIST,       /**< 187 - unable to parse FTP file list */
    EN_OFFLINE_CURLE_CHUNK_FAILED,            /**< 188 - chunk callback reported error */

    EN_OFFLINE_CURL_RSP_200                 = 200, /**< 200 http/https成功响应*/
    EN_OFFLINE_CURL_CREATE_HANDLE_FAIL = (EN_OFFLINE_ERR_STATR + 201),   /**< 201 */
    EN_OFFLINE_CURL_SET_HEAD_FAIL,                     /**< 202 */


    EN_OFFLINE_LOGIN_FAILED,                /**< EN_OFFLINE_ERR_STATR+203: 登录失败 */
    EN_OFFLINE_LOAD_NSCALIB_FAIL,           /**< EN_OFFLINE_ERR_STATR+204: Load NscaMiniLib failed 核心资产校验库加载失败 */
    EN_OFFLINE_GET_NSCAFUNC_FAIL,           /**< EN_OFFLINE_ERR_STATR+205: Get NscaFunc failed 核心资产校验库接口获取失败 */
    EN_OFFLINE_CHECKLABEL_TRUE,             /**< EN_OFFLINE_ERR_STATR+206: The document has label 文档有核心资产标签 */
    EN_OFFLINE_INVALID_FILEINFO,            /**< EN_OFFLINE_ERR_STATR+207: Invalid file info 传输的文件信息错误 */
    EN_OFFLINE_INVALID_FILEMD5,             /**< EN_OFFLINE_ERR_STATR+208: Invalid file SHA1 传输的文件的MD5错误 */
    EN_OFFLINE_GETSHARELINK_FAIL,           /**< EN_OFFLINE_ERR_STATR+209: 获取外链失败*/
    EN_OFFLINE_INVALID_SERVERMODE,          /**< EN_OFFLINE_ERR_STATR+210: 错误的服务器类型*/
    EN_OFFLINE_PRUPLOAD_EXIST,              /**< EN_OFFLINE_ERR_STATR+211: 预上传文件已存在*/
    EN_OFFLINE_PRUPLOAD_FAIL,               /**< EN_OFFLINE_ERR_STATR+212: 预上传文件失败*/
    EN_OFFLINE_UPLOAD_FAIL,                 /**< EN_OFFLINE_ERR_STATR+213: 上传文件失败*/
    EN_OFFLINE_MORETHAN_TRANSMAX,           /**< EN_OFFLINE_ERR_STATR+214: 上传文件超过最大限制3G*/
    EN_OFFLINE_DELETEFILE_FAIL,             /**< EN_OFFLINE_ERR_STATR+215: 删除文件失败*/
    EN_OFFLINE_FINISHFILE_FAIL,             /**< EN_OFFLINE_ERR_STATR+216: 完成分片传输失败*/
    EN_OFFLINE_PARTCOUNT_LARGER,            /**< EN_OFFLINE_ERR_STATR+217: 分片的片数超过HTTP连接数*/
    EN_OFFLINE_OPENFILE_FAIL,               /**< EN_OFFLINE_ERR_STATR+218: 打开文件失败*/
    EN_OFFLINE_UPLOADFILE_FINISHING,        /**< EN_OFFLINE_ERR_STATR+219: 文件上传即将结束*/
    EN_OFFLINE_RESUMEURL_NULL,              /**< EN_OFFLINE_ERR_STATR+220: 续传的URL为空*/
    EN_OFFLINE_DISK_FULL,                   /**< EN_OFFLINE_ERR_STATR+221: 服务器空间满*/
    EN_OFFLINE_ERROR_EXPIREDAT,             /**< EN_OFFLINE_ERR_STATR+222: 错误刷新token值*/
    EN_OFFLINE_ERROR_INITPARTINFO,          /**< EN_OFFLINE_ERR_STATR+223: 云盘初始化分片信息失败*/  
    EN_OFFLINE_ERRORCODE_BUTT               /**< never used */
}OFFLINE_E_ERRORCODE;


/**
 * 文件传输服务器类型
 */
typedef enum OFFLINE_SERVER_MODE
{
    OFFLINE_TRANSFER_NONE           = 0,
    OFFLINE_TRANSFER_CLOUDSTORE     = 1,        /**< 华为UC（云盘） */
    OFFLINE_TRANSFER_UM             = 2,        /**< 基线UM */
    OFFLINE_TRANSFER_BUIT
}OFFLINE_SERVER_MODE;

/**
 * 日志级别
 */
typedef enum
{
    OFFLINE_LOG_NONE        = 0,    /**< 日志关闭 */
    OFFLINE_LOG_ERROR       = 1,    /**< ERROR 级别 */
    OFFLINE_LOG_WARNING     = 2,    /**< WARNING 级别 */
    OFFLINE_LOG_INFO        = 3,    /**< INFOMATION 级别 */
    OFFLINE_LOG_DEBUG       = 4,    /**< DEBUG 级别 */
    OFFLINE_LOG_BUIT
}OFFLINE_LOG_LEVEL;

/**
 * 日志配置
 */
typedef struct tagST_OFFLINE_LOGCONFIG
{
    OFFLINE_LOG_LEVEL       enLevel;            /**< 日志级别 */
    TUP_UINT32              uiLogFileSize;      /**< 日志文件最大size (单位：M，取值范围[1,50]） */
    TUP_CHAR*               pcFilePath;         /**< 日志保存路径 */

    tagST_OFFLINE_LOGCONFIG()
    {
        enLevel         = OFFLINE_LOG_NONE;
        uiLogFileSize   = 3;
        pcFilePath      = OFFLINE_NULL;        
    }
}OFFLINE_LOGCONFIG;

/**
 * 文件传输初始化配置
 */
typedef struct tagST_OFFLINE_INITCONFIG
{
    OFFLINE_LOGCONFIG       stLogConfig;        /**< 日志配置信息 */
    TUP_UINT                uiHandleNum;        /**< （支持的控制块数，不超过OFFLINE_D_MAX_MUTI_TRANS） */
    TUP_BOOL                bUseSvn;            /**< 是否开启svn，默认关闭*/
    TUP_BOOL                bUseSvnFile;        /**< 是否传输的时候读写文件采用svn加解密方式，默认关闭 */
    
    tagST_OFFLINE_INITCONFIG()
    {
        uiHandleNum     = 0;
        bUseSvn         = TUP_FALSE;
        bUseSvnFile     = TUP_FALSE;
    }

}OFFLINE_INITCONFIG;

/**
 * 服务器地址
 */
typedef struct tagST_OFFLINE_SERVERINFO
{
    TUP_CHAR*           pcHostIP;        /**< 服务器IP地址，暂不支持IPV6 */
    TUP_UINT            uiHostPort;      /**< 服务器端口号 */
    TUP_CHAR*           pcUrl;           /**< 整个请求的url，长度不超过256 */
    EN_TLS_MODE         enTlsMode;       /**< https请求的TLS模式 */

    tagST_OFFLINE_SERVERINFO()
    {
        pcHostIP        = OFFLINE_NULL;
        uiHostPort      = 0;
        pcUrl           = OFFLINE_NULL;
        enTlsMode       = EN_TLS_CLOSE;
    }
}OFFLINE_SERVERINFO;

/**
 * 服务器地址列表
 */
typedef struct tagST_OFFLINE_SERVERLIST
{
    OFFLINE_SERVERINFO stServerUrl[OFFLINE_D_MAX_URL_NUM];  /**< 服务器url列表*/
    TUP_UINT32 ulCnt;                                       /**< 服务器数量 */
}OFFLINE_SERVERLIST;

/**
 * 文件传输登录服务器信息
 */
typedef struct tagST_OFFLINE_LOGININFO
{
    EN_TLS_MODE                 enTlsMode;          /**< TLS 模式(default value is EN_TLS_VERIFY_NONE) */
    ST_HTTP_TLS_PARA            stTlsPara;          /**< TLS 参数信息(default set pcCaCertPath for CA Path) */
    TUP_CHAR*                   pcLocalIP;          /**< 本地IP，必填，暂不支持IPV6 */
    TUP_UINT                    timeout;            /**< 连接超时时间，默认为0，单位:秒 */
    TUP_UINT                    tryConnectTimeout;  /**< 尝试连接超时时间，单位:秒 */

    TUP_BOOL                    bEncryTrans;        /**< 是否加密传输（上传、下载文件是否加密-值为真表示使用https加密） */
    OFFLINE_SERVER_MODE         enServerMode;       /**< 服务器类型 */
    OFFLINE_SERVERLIST          stHttpSerList;      /**< HTTP服务器列表 */
    OFFLINE_SERVERLIST          stHttpsSerList;     /**< HTTPS服务器列表 */
    TUP_LONG                    lServerExpiredAt;   /**< 探测服务器刷新时间，单位毫秒 */

    TUP_UINT64                  ulMaxFileSize;      /**< 文件大小最大限制，默认3G，单位：字节 */
    TUP_BOOL                    bPartTrans;         /**< 是否支持分片传输，默认值TUP_FALSE(不支持) */
    TUP_UINT64                  ulMinPartSize;      /**< 分片传输文件的最小限制（小于此size，不进行分片），默认40M，单位：字节 */
    TUP_UINT64                  ulPartTransSize;    /**< 分片传输每片大小，默认5M，单位：字节 */

    tagST_OFFLINE_LOGININFO()
    {
        enTlsMode           = EN_TLS_CLOSE;
        pcLocalIP           = OFFLINE_NULL;
        timeout             = 0;
        tryConnectTimeout   = 0;

        bEncryTrans         = TUP_TRUE;
        enServerMode        = OFFLINE_TRANSFER_NONE;
        lServerExpiredAt    = 0;

        ulMaxFileSize       = 0;
        bPartTrans          = TUP_FALSE;
        ulMinPartSize       = 0;
        ulPartTransSize     = 0;        
    }
}OFFLINE_LOGININFO;

/**
 * 登录的用户信息
 */
typedef struct tagST_OFFLINE_USERINFO
{
    TUP_CHAR*   pcLoginName;        /**< 用户名，必填 */
    TUP_CHAR*   pcPassword;         /**< 用户密码，必填 */
    TUP_CHAR*   pcAppName;          /**< 应用名称（如：eSpace），可选 */
    TUP_CHAR*   pcLoginType;        /**< 登录类型，针对UM服务器：1为密码鉴权，2为指纹鉴权，3为ticket委托鉴权，云盘不支持（暂未支持） */

    TUP_CHAR*   pcDeviceType;       /**< pc android ios web，必填 */
    TUP_CHAR*   pcDeviceName;       /**< 客户端名称,PC机器名,手机型号，必填 */
    TUP_CHAR*   pcDeviceOS;         /**< 客户端 操作系统，必填 */
    TUP_CHAR*   pcDeviceSN;         /**< 客户端唯一序列号，必填 */
    TUP_CHAR*   pcDeviceVersion;    /**< 客户端版本，必填  */

    tagST_OFFLINE_USERINFO()
    {
        pcLoginName     = OFFLINE_NULL;
        pcPassword      = OFFLINE_NULL;
        pcAppName       = OFFLINE_NULL;
        pcLoginType     = OFFLINE_NULL;

        pcDeviceType    = OFFLINE_NULL;
        pcDeviceName    = OFFLINE_NULL;
        pcDeviceOS      = OFFLINE_NULL;
        pcDeviceSN      = OFFLINE_NULL;
        pcDeviceVersion = OFFLINE_NULL;
    }
}OFFLINE_USERINFO;



/**
 * 文件传输文件模式
 */
typedef enum OFFLINE_FILE_TYPE
{
    OFFLINE_TYPE_FILE    = 0,               /**< 文件模式 */
    OFFLINE_TYPE_FOLDER  = 1,               /**< 文件夹模式 */
    OFFLINE_TYPE_BUTT
}OFFLINE_FILE_TYPE;

/**
 * 文件传输上层回调类型
 */
typedef enum OFFLINE_CALLBACK_TYPE
{
    OFFLINE_CALLBACK_PREUPLOAD     = 0,        /**< 预上传回调 */
    OFFLINE_CALLBACK_UPLOAD        = 1,        /**< 上传回调 */
    OFFLINE_CALLBACK_DOWNLOAD      = 2,        /**< 下载回调 */
    OFFLINE_CALLBACK_UPLOAD_PART   = 3,        /**< 上传分片回调 */
    OFFLINE_CALLBACK_BUTT
}OFFLINE_CALLBACK_TYPE;


/**
 * 上传文件信息
 */
typedef struct tagST_OFFLINE_UP_FILEINFO
{
    TUP_CHAR*               pcFilePath;         /**< 传输的文件绝对路径，包括文件名（入参） */
    TUP_CHAR*               pcFileName;         /**< 传输的文件名（入参）  */ 
    TUP_CHAR*               pcResumeFileId;     /**< 续传的fileid，第一次上传，为空 */
    TUP_CHAR*               pcResumeUpURL;      /**< 续传的UploadURL，第一次上传，为空 */
    TUP_CHAR*               pcResumeDownURL;    /**< 续传的DownloadURL，第一次上传，为空 */
    TUP_CHAR*               pcResumeMd5;        /**< 续传的文件md5，第一次上传，为空 */
    TUP_CHAR*               pcResumeSignature;  /**< UM续传的文件提取码，第一次上传，为空 */
    void *                  userInfo;           /**< 用户信息（入参），可为空 */
    TUP_BOOL                bDeleteFile;        /**< 是否允许删除文件（true or false） */
    TUP_BOOL                bUseSvnFile;        /**< 是否采用MDM加密（true or false） */
    
    TUP_CHAR*               pcFileType;         /**< 文件类型,normal或不填：普通个人文件；group：群文件；circle：工作圈文件 */
    TUP_CHAR*               pcOperationToken;   /**< 用做operationToken使用 */
    TUP_CHAR*               pcGroupId;          /**< 群ID，如果上传的是群文件必须指定 */

    tagST_OFFLINE_UP_FILEINFO()
    {
        pcFilePath          = OFFLINE_NULL;
        pcFileName          = OFFLINE_NULL;
        pcResumeFileId      = OFFLINE_NULL;
        pcResumeUpURL       = OFFLINE_NULL;
        pcResumeDownURL     = OFFLINE_NULL;
        pcResumeMd5         = OFFLINE_NULL;
        pcResumeSignature   = OFFLINE_NULL;
        userInfo            = OFFLINE_NULL;
        bDeleteFile         = TUP_FALSE;
        bUseSvnFile         = TUP_FALSE;
        pcFileType          = OFFLINE_NULL;
        pcOperationToken    = OFFLINE_NULL;
        pcGroupId           = OFFLINE_NULL;
    }
}OFFLINE_UP_FILEINFO;

/**
 * 外链下载信息
 */
typedef struct tagST_OFFLINE_PlainAccess
{
    TUP_CHAR*   pcplainAccessCode;          /**< 外链提取码（可选） */
    TUP_CHAR*   pctype;                     /**< 外链下载的文件类型。original 原始文件，thumbnail 缩略图（可选） */
    TUP_CHAR*   pcheight;                   /**< 缩略图高度。type为thumbnail时必选；type不是thumbnail，没有实际意义，可以不设置 */
    TUP_CHAR*   pcwidth;                    /**< 缩略图宽度。type为thumbnail时必选；type不是thumbnail，没有实际意义，可以不设置 */

    tagST_OFFLINE_PlainAccess()
    {
        pcplainAccessCode = HTTP_NULL;
        pctype = HTTP_NULL;
        pcheight = HTTP_NULL;
        pcwidth = HTTP_NULL;
    }

}OFFLINE_PlainAccess;

/**
 * 下载文件信息
 */
typedef struct tagST_OFFLINE_DOWN_FILEINFO
{    
    TUP_CHAR*   pcFilePath;                 /**< 下载文件存储的绝对路径 */
    TUP_CHAR*   pcFileDownUrl;              /**< 下载URL */
    void*       userInfo;                   /**< 用户信息（入参） */
    TUP_BOOL    bDownDelete;                /**< 下载后是否删除 */
    TUP_BOOL                bUseSvnFile;    /**< 是否采用MDM加密（true or false） */
    OFFLINE_PlainAccess*    pPlainAccess;   /**< 外链下载信息（如没有则为空） */

    tagST_OFFLINE_DOWN_FILEINFO()
    {
        pcFilePath      = OFFLINE_NULL;
        pcFileDownUrl   = OFFLINE_NULL;
        userInfo        = OFFLINE_NULL;
        bDownDelete     = TUP_FALSE;
        pPlainAccess    = OFFLINE_NULL;
        bUseSvnFile     = TUP_FALSE;
    }

}OFFLINE_DOWN_FILEINFO;

/**
 * 文件传输响应信息
 */
typedef struct tagST_OFFLINE_RSPFILEINFO
{
    OFFLINE_CALLBACK_TYPE   enCallbackType;     /**< 文件传输上层回调类型, @see OFFLINE_CALLBACK_TYPE */

    TUP_CHAR*               pcFileId;           /**< 文件ID信息 */
    TUP_CHAR*               pcPlainAccessCode;  /**< 文件外链提取码 */
    TUP_CHAR*               pcUrl;              /**< 文件下载URL */
    OFFLINEHANDLE           ulHandle;           /**< 文件句柄信息 */

    TUP_ULONG               ulStatusCode;       /**< 服务器返回码 */
    TUP_CHAR*               pcCodeMsg;          /**< 错误码消息 */

    tagST_OFFLINE_RSPFILEINFO()
    {
        enCallbackType      = OFFLINE_CALLBACK_BUTT;
        pcFileId            = OFFLINE_NULL;
        pcPlainAccessCode   = OFFLINE_NULL;
        pcUrl               = OFFLINE_NULL;
        ulHandle            = 0;

        ulStatusCode        = 0;
        pcCodeMsg           = OFFLINE_NULL;
    }

}OFFLINE_RSPFILEINFO;


/** 
 *文件传输响应信息
 */
typedef struct tagST_OFFLINE_DELETEFILE
{
    TUP_CHAR*          pcChar;             /**< 对接云盘对应fileID， 对接UM对应downloadurl */
    TUP_CHAR*          pcOperationToken;   /**< 用做operationToken使用 */
    TUP_CHAR*          pcSignature;        /**< UM提取码 */

    tagST_OFFLINE_DELETEFILE()
    {
        pcChar              = OFFLINE_NULL;
        pcOperationToken    = OFFLINE_NULL;
        pcSignature         = OFFLINE_NULL;
    }

}OFFLINE_DELETEFILE;


/**
 * @brief 文件传输结果响应通知
 * 
 * @param [in] OFFLINEHANDLE fileHandle         <b>:</b> 文件句柄
 * @param [in] TUP_ULONG enCode                 <b>:</b> 传输结果，0表示成功，非0表示异常
 * @param [in] OFFLINE_RSPFILEINFO *pstFileRsp  <b>:</b> 传输响应，其中ulStatusCode表示HTTP/HTTPS响应，200表示成功，非200表示异常
 * @param [in] void *userInfo                   <b>:</b> 用户自定义信息
 * @param [out] NA
 * @retval typedef int (* <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see 
 **/
typedef int (*OffLineFileRspNotify)(OFFLINEHANDLE fileHandle, TUP_ULONG enCode, OFFLINE_RSPFILEINFO *pstFileRsp, void *userInfo);


/**
 * @brief 文件传输过程(进度)通知
 * 
 * @param [in] OFFLINEHANDLE fileHandle  <b>:</b> 文件句柄
 * @param [in] TUP_UINT64 ulTotal        <b>:</b> 需要传输的完整大小
 * @param [in] TUP_UINT64 ulNow          <b>:</b> 已经传输的大小
 * @param [in] void *userInfo            <b>:</b> 用户自定义信息
 * @param [out] NA
 * @retval typedef void (* <b>:</b> 
 * 
 * @attention NA
 * @see 
 **/
typedef void (*OffLineTransProgressNotify)(OFFLINEHANDLE fileHandle, TUP_UINT64 ulTotal, TUP_UINT64 ulNow, void *userInfo);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif  /* __OFFLINEFILE_DEF_H__ */

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/


