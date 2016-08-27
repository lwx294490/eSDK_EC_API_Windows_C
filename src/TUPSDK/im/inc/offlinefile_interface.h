/** 
* @file offlinefile_interface.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM 离线文件传输模块基础接口结构体定义头文件。 \n
*/

/**
*
*  @{
*/

#ifndef __OFFLINEFILE_INTERFACE_H__
#define __OFFLINEFILE_INTERFACE_H__

// 本文件需要包含的头文件
#include "offlinefile_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



/**
 * @brief 文件传输登录初始化
 * 
 * @param [in] const OFFLINE_INITCONFIG* pstConfig    <b>:</b> 初始化配置信息
 * @param [in] const OFFLINE_LOGININFO* pstLoginInfo  <b>:</b> 登录信息
 * @param [in] const OFFLINE_USERINFO* pstUserInfo    <b>:</b> 登录用户信息
 * @param [out] TUP_ULONG* pLogInResult               <b>:</b> 登录结果（服务器返回码）
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 废弃接口，推荐使用tup_offlinefile_init&tup_offlinefile_login
 * @see tup_offlinefile_uninitlogout
 **/
TUP_API TUP_RESULT tup_offlinefile_initlogin(IN const OFFLINE_INITCONFIG* pstConfig, 
                                             IN const OFFLINE_LOGININFO* pstLoginInfo, 
                                             IN const OFFLINE_USERINFO* pstUserInfo, 
                                             OUT TUP_ULONG* pLogInResult);
/**
 * @brief 文件传输初始化
 * 
 * @param [in] OFFLINE_INITCONFIG* config <b>:</b> 初始化配置信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_offlinefile_uninit
 **/
TUP_API TUP_RESULT tup_offlinefile_init(IN const OFFLINE_INITCONFIG* config);


/**
 * @brief 开启日志
 * 
 * @param [in] const OFFLINE_LOGCONFIG* config 日志配置参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 已经初始化，支持动态开启或关闭日志，默认关闭
 * @see tup_offlinefile_closelog
 **/
TUP_API TUP_RESULT tup_offlinefile_openlog(IN const OFFLINE_LOGCONFIG* config);

/**
 * @brief 关闭日志
 * 
 * @param [in] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 已经初始化，支持动态开启或关闭日志，默认关闭
 * @see tup_offlinefile_openlog
 **/
TUP_API TUP_RESULT tup_offlinefile_closelog();

/**
 * @brief 文件传输登录
 * 
 * @param [in] const OFFLINE_LOGININFO * pstLogInfo <b>:</b> 登录信息
 * @param [in] const OFFLINE_USERINFO * pstUserInfo  <b>:</b> 登录用户信息
 * @param [out] TUP_ULONG * pLogInResult <b>:</b> 登录结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_offlinefile_logout
 **/
TUP_API TUP_RESULT tup_offlinefile_login(IN const OFFLINE_LOGININFO* pstLoginInfo, 
                                         IN const OFFLINE_USERINFO* pstUserInfo, 
                                         OUT TUP_ULONG* pLogInResult);


/**
 * @brief 文件上传（异步接口，调用后直接返回，通过回调通知上层进度和传输结果）
 * 
 * @param [in] OFFLINE_UP_FILEINFO* pUpFileInfo <b>:</b> 文件上传信息，支持传输一个文件
 * @param [out] OFFLINEHANDLE* pFileHandle <b>:</b> 文件句柄（出参）
 * @param [in] OffLineTransProgressNotify offLineProgNotifyFunc  <b>:</b> 过程回调函数，通知上层文件传输进度
 * @param [in] OffLineFileRspNotify offLineRspNotifyFunc  <b>:</b> 上传结束响应回调，可获取错误码、状态、外链等信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_offlinefile_downloadfile
 * @see tup_offlinefile_deletefile
 * @see tup_offlinefile_release
 * @see tup_offlinefile_cancel
 **/
TUP_API TUP_RESULT tup_offlinefile_uploadfile(IN const OFFLINE_UP_FILEINFO* pUpFileInfo, 
                                              OUT OFFLINEHANDLE* pFileHandle, 
                                              IN OffLineTransProgressNotify offLineProgNotifyFunc, 
                                              IN OffLineFileRspNotify offLineRspNotifyFunc);


/**
 * @brief 获取续传的URL
 * 
 * @param [in] OFFLINEHANDLE fileHandle <b>:</b> 文件句柄
 * @param [out] TUP_CHAR** ppcResumeUpURL <b>:</b> 续传的上传URL
 * @param [out] TUP_CHAR** ppcFileId <b>:</b> 续传的文件id
 * @param [out] TUP_CHAR** ppcResumeDownURL <b>:</b> 续传的下载URL
 * @param [out] TUP_CHAR** ppcMd5 <b>:</b> 续传的md5
 * @param [out] TUP_CHAR** ppcSignature <b>:</b> 续传的提取码信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 
 * @see tup_offlinefile_downloadfile
 **/
TUP_API TUP_RESULT tup_offlinefile_getresumeupurl(IN OFFLINEHANDLE fileHandle, OUT TUP_CHAR** ppcFileId,
                                                  OUT TUP_CHAR** ppcResumeUpURL, 
                                                  OUT TUP_CHAR** ppcResumeDownURL,
                                                  OUT TUP_CHAR** ppcMd5,
                                                  OUT TUP_CHAR** ppcSignature);


/**
 * @brief 文件下载（异步接口，调用后直接返回，通过回调来通知上层进度和传输结果）
 * 
 * @param [in] const OFFLINE_DOWN_FILEINFO* pDownFileInfo <b>:</b> 文件下载信息
 * @param [out] OFFLINEHANDLE* pFileHandle <b>:</b> 文件句柄（出参）
 * @param [in] OffLineTransProgressNotify offLineProgNotifyFunc  <b>:</b> 过程回调函数，通知上层文件传输进度
 * @param [in] OffLineFileRspNotify offLineRspNotifyFunc  <b>:</b> 响应回调，可获取错误码、状态等信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_offlinefile_uploadfile
 * @see tup_offlinefile_getresumeupurl
 * @see tup_offlinefile_deletefile
 * @see tup_offlinefile_release
 * @see tup_offlinefile_cancel
 **/
TUP_API TUP_RESULT tup_offlinefile_downloadfile(IN const OFFLINE_DOWN_FILEINFO* pDownFileInfo, 
                                                OUT OFFLINEHANDLE* pcFileHandle,         
                                                IN OffLineTransProgressNotify offLineProgNotifyFunc, 
                                                IN OffLineFileRspNotify offLineRspNotifyFunc);


/**
 * @brief 删除上传的文件
 * 
 * @param [in] OFFLINE_DELETEFILE* pcDeleteFile <b>:</b> 删除文件的信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_offlinefile_uploadfile
 * @see tup_offlinefile_downloadfile
 * @see tup_offlinefile_release
 * @see tup_offlinefile_cancel
 **/
TUP_API TUP_RESULT tup_offlinefile_deletefile(IN OFFLINE_DELETEFILE* pcDeleteFile);


/**
 * @brief 删除上传的文件
 * 
 * @param [in] TUP_CHAR* pcChar <b>:</b> 对接云盘对应fileID， 对接UM对应downloadurl
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 废弃接口，建议使用tup_offlinefile_deletefile
 *            
 * @see tup_offlinefile_delete
 **/
TUP_API TUP_RESULT tup_offlinefile_delete(IN TUP_CHAR* pcChar);



/**
 * @brief 取消文件传输
 * 
 * @param [in] OFFLINEHANDLE fileHandle <b>:</b> 文件句柄
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 
 * @see tup_offlinefile_uploadfile
 * @see tup_offlinefile_downloadfile
 * @see tup_offlinefile_deletefile
 * @see tup_offlinefile_cancel
 **/
TUP_API TUP_RESULT tup_offlinefile_release(IN OFFLINEHANDLE fileHandle);


/**
 * @brief 开启分片传输后取消文件传输，此时如果是下载则会删除已经下载的文件
 * 
 * @param [in] OFFLINEHANDLE fileHandle <b>:</b> 文件句柄
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_offlinefile_uploadfile
 * @see tup_offlinefile_downloadfile
 * @see tup_offlinefile_deletefile
 * @see tup_offlinefile_release
 **/
TUP_API TUP_RESULT tup_offlinefile_cancel(IN OFFLINEHANDLE fileHandle);


/**
 * @brief 文件传输登出并去初始化
 * 
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 废弃接口，推荐使用tup_offlinefile_uninit&tup_offlinefile_logout
 * @see tup_offlinefile_initlogin
 **/
TUP_API TUP_RESULT tup_offlinefile_uninitlogout();

/**
 * @brief 登出
 * 
 * @param [in] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 *            
 * @see tup_offlinefile_login
 **/
TUP_API TUP_RESULT tup_offlinefile_logout();


/**
 * @brief 去初始化
 * 
 * @param [in] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 *            
 * @see tup_offlinefile_init
 **/
TUP_API TUP_RESULT tup_offlinefile_uninit();

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  // __OFFLINEFILE_INTERFACE_H__

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
