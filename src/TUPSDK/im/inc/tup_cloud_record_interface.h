/** 
* @file tup_cloud_record_interface.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM 云录子系统基础接口结构体定义头文件。 \n
*/

/**
*
*  @{
*/

#ifndef __TUP_CLOUD_RECORD_INTERFACE_H__
#define __TUP_CLOUD_RECORD_INTERFACE_H__

#include "tup_cloud_record_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
 * @brief 对接云录初始化
 * 
 * @param [in] const CLOUD_RECORD_INIT_CONFIG *config  <b>:</b> 初始化配置信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_im_cloud_record_uninit
 **/
TUP_API TUP_RESULT tup_im_cloud_record_init(IN const CLOUD_RECORD_INIT_CONFIG *config);


/**
 * @brief 对接云录去初始化
 * 
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_im_cloud_record_init
 **/
TUP_API TUP_RESULT tup_im_cloud_record_uninit();


/**
 * @brief 获取云录配置
 * 
 * @param [in] CLOUDRECORDHANDLE *handle                                <b>:</b> 句柄
 * @param [in] CLOUD_RECORD_GET_CFG_REQ *get_cfg_req                    <b>:</b> 获取云录服务器配置信息
 * @param [in] CLOUD_RECORD_GET_CFG_RSP_NOTIFY get_cfg_rsp_notify_func  <b>:</b> 获取云录服务器配置信息回调
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention  NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_cloud_record_get_config_info(IN CLOUDRECORDHANDLE *handle, 
                    IN CLOUD_RECORD_GET_CFG_REQ *get_cfg_req, IN CLOUD_RECORD_GET_CFG_RSP_NOTIFY get_cfg_rsp_notify_func);


/**
 * @brief 上传通话信息
 * 
 * @param [in] CLOUDRECORDHANDLE *handle                                              <b>:</b> 句柄
 * @param [in] CLOUD_RECORD_SEND_CALL_INFO_REQ *send_call_info_req                    <b>:</b> 上传云录服务器通话信息
 * @param [in] CLOUD_RECORD_SEND_CALL_INFO_RSP_NOTIFY send_call_info_rsp_notify_func  <b>:</b> 上传云录服务器通话信息回调
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_cloud_record_send_call_info(IN CLOUDRECORDHANDLE *handle, 
                    IN CLOUD_RECORD_SEND_CALL_INFO_REQ *send_call_info_req, IN CLOUD_RECORD_SEND_CALL_INFO_RSP_NOTIFY send_call_info_rsp_notify_func);

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

#endif  // __TUP_CLOUD_RECORD_INTERFACE_H__

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/


