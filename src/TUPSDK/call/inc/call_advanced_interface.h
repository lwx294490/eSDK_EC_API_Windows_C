
/** 
* @file call_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP 呼叫子系统高级业务接口头文件。 \n
*/


/**
*
*  @{
*/


#ifndef __CALL_ADVANCED_INTERFACE_H__
#define __CALL_ADVANCED_INTERFACE_H__


/*******************************************************************************
 *   本文件需要包含的其它头文件
 *******************************************************************************/

#include "call_advanced_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/*******************************************************************************
 *   宏常量定义区
*******************************************************************************/

#define IN
#define OUT



/**tup_call_digitmap_create_handle 第一个参数type取值范围*/
#define TUP_COMMON_DIGITMAP_INDEX   (0)    //立即匹配数图索引
#define TUP_REPLACE_DIGITMAP_INDEX  (1)    //替换匹配数图索引



/**
 * @brief 创建数图句柄
 * 
 * @param [in] const TUP_INT32 type       <b>:</b> 数图类型，0 立即匹配数图索引，1 替换匹配数图索引
 * @param [in] const TUP_CHAR *digit_map  <b>:</b> 数图
 * @param [out] TUP_INT32 *handle         <b>:</b> 创建的数图句柄
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_digitmap_match
 * @see tup_call_digitmap_destroy_handle
 **/
TUP_API TUP_RESULT tup_call_digitmap_create_handle(IN const TUP_INT32 type, IN const TUP_CHAR *digit_map, OUT TUP_INT32 *handle);


/**
 * @brief 销毁数图句柄
 * 
 * @param [in] const TUP_INT32 handle  <b>:</b> 待销毁的数图句柄
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_digitmap_create_handle
 * @see tup_call_digitmap_match
 **/
TUP_API TUP_RESULT tup_call_digitmap_destroy_handle(IN const TUP_INT32 handle);


/**
 * @brief 数图匹配处理
 * 
 * @param [in] const TUP_INT32 handle  <b>:</b> 数图句柄
 * @param [in] const char *input_num   <b>:</b> 原始待数图处理号码
 * @param [out] DMRESULT *dm_result     <b>:</b> 数图处理结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_digitmap_create_handle
 * @see tup_call_digitmap_destroy_handle
 **/
TUP_API TUP_RESULT tup_call_digitmap_match(IN const TUP_INT32 handle, IN const char *input_num, OUT DMRESULT *dm_result);


/**
 * @brief RSA加密
 * 
 * @param [in] const TUP_CHAR *src_data         <b>:</b> 待加密处理的数据
 * @param [in] const TUP_CHAR *public_key_path  <b>:</b> 公钥路径
 * @param [out] TUP_CHAR **encrypt_data         <b>:</b> 加密后的数据
 * @param [out] TUP_INT *encrypt_len            <b>:</b> 加密后的数据长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 加密后的数据内容需要释放，释放函数tup_rsa_free_public_encrypt_data
 * @see tup_rsa_free_public_encrypt_data
 **/
TUP_API TUP_RESULT tup_rsa_public_encrypt(IN const TUP_CHAR *src_data, IN const TUP_CHAR *public_key_path, OUT TUP_CHAR **encrypt_data, OUT TUP_INT *encrypt_len);


/**
 * @brief 释放RSA加密数据
 * 
 * @param [in] TUP_CHAR *encrypt_data  <b>:</b> 待释放的加密数据
 * @retval TUP_API TUP_VOID <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_rsa_public_encrypt
 **/
TUP_API TUP_VOID tup_rsa_free_public_encrypt_data(IN TUP_CHAR *encrypt_data);


/**
 * @brief 获取指定业务的业务特征码(注册码或注销码)
 * 
 * @param [in] TUP_UINT32 account_id            <b>:</b> 账号ID
 * @param [in] CALL_S_IPT_DATA *ipt_data        <b>:</b> 待获取业务特征码的业务描述信息
 * @param [out] TUP_CHAR code[]                 <b>:</b> 保存特征码的内存，由应用层分配，建议长度不小于32字节
 * @param [in] TUP_UINT32 size                  <b>:</b> 保存特征码的内存长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_service_code(IN TUP_UINT32 account_id, IN CALL_S_IPT_DATA *ipt_data, OUT TUP_CHAR code[], IN TUP_UINT32 size);


/**
 * @brief 注册指定账号
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 待注册的账号id
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_deregister_for_account
 **/
TUP_API TUP_RESULT tup_call_register_for_account(IN TUP_UINT32 account_id);


/**
 * @brief 注销指定账号
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 待注销的账号id
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_register_for_account
 **/
TUP_API TUP_RESULT tup_call_deregister_for_account(IN TUP_UINT32 account_id);


/**
 * @brief 开始指定账号的刷新注册
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号id
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_stop_refreshregister_for_account
 **/
TUP_API TUP_RESULT tup_call_start_refreshregister_for_account(IN TUP_UINT32 account_id);


/**
 * @brief 停止指定账号的刷新注册
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号id
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_start_refreshregister_for_account
 **/
TUP_API TUP_RESULT tup_call_stop_refreshregister_for_account(IN TUP_UINT32 account_id);


/**
 * @brief 从RLS列表中移除联系人
 * 
 * @param [in] TUP_UINT32 account_id           <b>:</b> 账号id
 * @param [in] const TUP_CHAR* contact_number  <b>:</b> 联系人号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_contact_removed_indicate(IN TUP_UINT32 account_id, IN const TUP_CHAR* contact_number);


/**
 * @brief 获取SIP服务器连接状态信息
 * 
 * @param [in] TUP_UINT8 server_index  <b>:</b> 服务器索引
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_sipserver_link_status(IN TUP_UINT8 server_index);


/**
 * @brief 获取账户信息
 * 
 * @param [out] CALL_S_SIP_ACCOUNT_INFO* account_info <b>:</b> 保存账号信息的结构数组
 * @param [out] TUP_UINT32* count                     <b>:</b> 实际获取的账号信息个数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention account_info的内存由应用层分配，大小为siaeof(CALL_S_SIP_ACCOUNT_INFO) * 最大账号数
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_account_info(OUT CALL_S_SIP_ACCOUNT_INFO* account_info, OUT TUP_UINT32* count);


/**
 * @brief 获取指定账户下的呼叫信息
 * 
 * @param [in] TUP_UINT32 account_id        <b>:</b> 账号ID
 * @param [out] TUP_UINT32* callids         <b>:</b> 保存账号下呼叫ID的数组
 * @param [in/out] TUP_UINT32* callsnum     <b>:</b> 输入时为callids数组的大小，输出时为实际的呼叫ID数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 保存账号下呼叫ID的数组建议为最大并发呼叫数(当前为24)
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_account_callids(IN TUP_UINT32 account_id, OUT TUP_UINT32* callids, IO TUP_UINT32* callsnum);


/**
 * @brief 创建呼叫ID
 * 
 * @param [in] TUP_UINT32 account_id       <b>:</b> 账号ID
 * @param [in] CALL_E_LINE_TYPE line_type  <b>:</b> 线路类型
 * @param [in] TUP_UINT32 lineid           <b>:</b> 线路ID
 * @param [out] TUP_UINT32* callid         <b>:</b> 创建成功的呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 根据呼叫ID进行后继调用的函数(*_bycallid)，都需要调用此函数
 * @see tup_call_start_call_bycallid
 * @see tup_call_anonymous_call_bycallid
 * @see tup_call_emergency_call
 **/
TUP_API TUP_RESULT tup_call_create_callid(IN TUP_UINT32 account_id,  IN CALL_E_LINE_TYPE line_type, IN TUP_UINT32 lineid, OUT TUP_UINT32* callid);


/**
 * @brief 根据呼叫ID发起一路音视频呼叫
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] CALL_E_CALL_TYPE call_type     <b>:</b> 呼叫类型，音频或视频
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_create_callid
 **/
TUP_API TUP_RESULT tup_call_start_call_bycallid(IN TUP_UINT32 callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief 根据CALLID发起一路指定方式的VOIP呼叫
 * 
 * @param [in] const CALL_S_CALL_PARAMS* call_params  <b>:</b> 呼叫参数，其中ulCallId为输入参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_anonymous_call
 * @see tup_call_start_call_ex
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 * @see tup_call_hold_call
 * @see tup_call_unhold_call
 **/
TUP_API TUP_RESULT tup_call_start_call_bycallid_ex(IN const CALL_S_CALL_PARAMS* call_params);



/**
 * @brief 根据呼叫ID发起一路匿名呼叫
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 匿名呼叫为音频呼叫
 * @see tup_call_create_callid
 **/
TUP_API TUP_RESULT tup_call_anonymous_call_bycallid(IN TUP_UINT32 callid, IN const TUP_CHAR* callee_number);


/**
 * @brief 根据呼叫ID发起一路匿名呼叫
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
  * @param [in] CALL_E_CALL_TYPE call_type     <b>:</b> 呼叫类型，音频或视频
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 匿名呼叫为音频呼叫
 * @see tup_call_create_callid
 **/
TUP_API TUP_RESULT tup_call_start_anonymous_call_bycallid(IN TUP_UINT32 callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief 根据呼叫ID发起一路紧急呼叫
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 紧急呼叫为音频呼叫
 * @see tup_call_create_callid
 **/
TUP_API TUP_RESULT tup_call_emergency_call(IN TUP_UINT32 callid, IN const TUP_CHAR* callee_number);


/**
 * @brief 登记指定账号的DND业务
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 业务特征码需要已正确配置
 * @see tup_call_cancel_DND_for_account
 **/
TUP_API TUP_RESULT tup_call_set_DND_for_account(IN TUP_UINT32 account_id);

 
/**
 * @brief 注销指定账号的DND业务
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 业务特征码需要已正确配置
 * @see tup_call_set_DND_for_account
 **/
TUP_API TUP_RESULT tup_call_cancel_DND_for_account(IN TUP_UINT32 account_id);


/**
 * @brief 登记指定账号的来电静铃业务
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 业务特征码需要已正确配置
 * @see tup_call_set_alertsilence_off
 **/
TUP_API TUP_RESULT tup_call_set_alertsilence_on(IN TUP_UINT32 account_id);


/**
 * @brief 注销指定账号的来电静铃业务
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 业务特征码需要已正确配置
 * @see tup_call_set_alertsilence_off
 **/
TUP_API TUP_RESULT tup_call_set_alertsilence_off(IN TUP_UINT32 account_id);


/**
 * @brief 登记privacy业务(私人呼叫)
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_privacy_off
 **/
TUP_API TUP_RESULT tup_call_set_privacy_on(IN TUP_UINT32 account_id);


/**
 * @brief 注销privacy业务(私人呼叫)
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_privacy_on
 **/
TUP_API TUP_RESULT tup_call_set_privacy_off(IN TUP_UINT32 account_id);


/**
 * @brief 发起reinvite重协商
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_reinvite(IN TUP_UINT32 callid);


/**
 * @brief 接听指定线路的呼叫
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_UINT32 lineid  <b>:</b> 线路ID
 * @param [in] TUP_BOOL is_video  <b>:</b> 是否接听视频呼叫
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_accept_call_with_lineid(IN TUP_UINT32 callid, IN TUP_UINT32 lineid, IN TUP_BOOL is_video);


/**
 * @brief 根据原因结束呼叫
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_UINT32 cause   <b>:</b> 结束呼叫的原因
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_end_call_with_cause(IN TUP_UINT32 callid, IN TUP_UINT32 cause);


/**
 * @brief 结束所有呼叫
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_end_call
 * @see tup_call_end_call_with_cause
 **/
TUP_API TUP_RESULT tup_call_end_allcall(TUP_VOID);



/**
 * @brief 根据呼叫ID销毁CTD呼叫
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 废弃接口，请调用tup_call_end_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_ctd_destroy_call(IN TUP_UINT32 callid);


/**
 * @brief 对方请求视频转音频呼叫(删除视频)时，本方选择同意或者拒绝
 * 
 * @param [in] TUP_UINT32 callid   <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_accept  <b>:</b> 是否同意
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 无实际使用场景，用户无法拒绝
 * @see tup_call_add_video
 * @see tup_call_reply_add_video
 * @see tup_call_del_video
 **/
TUP_API TUP_RESULT tup_call_reply_del_video(IN TUP_UINT32 callid, IN TUP_BOOL is_accept);



/**
 * @brief 根据账号ID获取流通道信息
 * 
 * @param [in] TUP_UINT32 accountid            <b>:</b> 账号ID
 * @param [in] CALL_S_STREAM_INFO* streaminfo  <b>:</b> 流通道信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_get_callstatics
 **/
TUP_API TUP_RESULT tup_call_get_channelinfo(IN TUP_UINT32 accountid, IN CALL_S_STREAM_INFO* streaminfo);


/**
 * @brief 播放拨号音
 * 
 * @param [in] TUP_UINT32 callid         <b>:</b> 呼叫ID
 * @param [in] CALL_E_SIGTONE_TYPE tone  <b>:</b> 信号音类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_stop_signaltone
 **/
TUP_API TUP_RESULT tup_call_play_signaltone(IN TUP_UINT32 callid, IN CALL_E_SIGTONE_TYPE tone);


/**
 * @brief 停止播放拨号音
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_play_signaltone
 **/
TUP_API TUP_RESULT tup_call_stop_signaltone(IN TUP_UINT32 callid);


/**
 * @brief 主被叫控业务中保持呼叫
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_pnotification_unholdcall
 **/
TUP_API TUP_RESULT tup_call_pnotification_holdcall(IN TUP_UINT32 callid);

 
/**
 * @brief 主被叫控业务中取消保持呼叫
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_pnotification_holdcall
 **/
TUP_API TUP_RESULT tup_call_pnotification_unholdcall(IN TUP_UINT32 callid);


/**
 * @brief 开启服务器录/音
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_server_recordcall_off
 **/
TUP_API TUP_RESULT tup_call_server_recordcall_on(IN TUP_UINT32 callid);


/**
 * @brief 关闭服务器录/音
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_server_recordcall_on
 **/
TUP_API TUP_RESULT tup_call_server_recordcall_off(IN TUP_UINT32 callid);


/**
 * @brief 登记自动回呼业务
 * 
 * @param [in] TUP_UINT32 account_id       <b>:</b> 账号ID
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 业务特征码需要已正确配置
 * @see tup_call_cancel_callback
 **/
TUP_API TUP_RESULT tup_call_callback(IN TUP_UINT32 account_id, IN const TUP_CHAR* callee_number);

 
/**
 * @brief 注销自动回呼业务
 * 
 * @param [in] TUP_UINT32 account_id       <b>:</b> 账号ID
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 业务特征码需要已正确配置
 * @see tup_call_callback
 **/
TUP_API TUP_RESULT tup_call_cancel_callback(IN TUP_UINT32 account_id, IN const TUP_CHAR* callee_number);


/**
 * @brief 取回直接呼叫驻留业务
 * 
 * @param [in] TUP_UINT32 callid           <b>:</b> 呼叫ID
 * @param [in] CALL_E_CALL_TYPE call_type  <b>:</b> 呼叫类型，音频或视频
 * @param [in] const TUP_CHAR* pszparknum  <b>:</b> 呼叫驻留号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_callpark
 * @see tup_call_set_direct_callpark
 **/
TUP_API TUP_RESULT tup_call_get_callpark(IN TUP_UINT32 callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* pszparknum);


/**
 * @brief 获取当前呼叫的SIP服务器信息
 * 
 * @param [in] TUP_UINT32 callid                        <b>:</b> 呼叫ID
 * @param [in] CALL_S_CURRENT_SIPSERVER* server_info  <b>:</b> SIP服务器信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_sipserver_info(IN TUP_UINT32 callid, IN CALL_S_CURRENT_SIPSERVER* server_info);


/**
 * @brief 获取指定账号的服务器地址列表
 * 
 * @param [in] TUP_UINT32 account_id                <b>:</b> 账号ID
 * @param [out] TUP_UINT32* addr_num                <b>:</b> 地址信息个数
 * @param [out] CALL_S_SIP_ADDR_INFO* addr_info     <b>:</b> 保存地址信息的数组
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention addr_info内存由应用层分配，数组大小为服务器最大个数，建议为5
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_sipserver_addrlist(IN TUP_UINT32 account_id, 
                        OUT TUP_UINT32* addr_num,  OUT CALL_S_SIP_ADDR_INFO* addr_info);


/**
 * @brief 共享线加入bridge会议 
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_SCA_in_bridgeconf(IN TUP_UINT32 callid);


/**
 * @brief 可编程键/扩展板按键配置变更通知
 * 
 * @param [in] TUP_INT32 broad_id     <b>:</b> 0:话机可编程键、1:扩展板一、2:扩展板二、3:扩展板三
 * @param [in] const TUP_INT32* keys  <b>:</b> 配置发生变化的按键Loc编号数组, 即可一次传多个发生变化的按键编号，按键Loc编号是从1开始计数的
 * @param [in] TUP_INT32 number       <b>:</b> 按键Loc编号数组大小。
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_progkey_modify_ind(IN TUP_INT32 broad_id, IN const TUP_INT32* keys, IN TUP_INT32 number);


/**
 * @brief 获取联系人状态，可一次获取多个联系人状态
 * 
 * @param [in] TUP_UINT32 number               <b>:</b> 联系人个数，即pastStatus数组大小
 * @param [in/out] CALL_S_CONTACT_STATUS status[]  <b>:</b> 联系人状态数组，输入包含号码，输出包含对应号码的状态
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_contact_status(IN TUP_UINT32 number, IO CALL_S_CONTACT_STATUS status[]);


/**
 * @brief 订阅联系人状态
 * 
 * @param [in] TUP_UINT32 account_id        <b>:</b> 账号ID
 * @param [in] TUP_UINT32 contact_type      <b>:</b> 联系人类型:0 普通联系人，1 HUNTGROUP 联系人
 * @param [in] const TUP_CHAR* contact_num  <b>:</b> 联系人号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_unsubscribe_contact
 **/
TUP_API TUP_RESULT tup_call_subscribe_contact(IN TUP_UINT32 account_id, IN TUP_UINT32 contact_type, IN const TUP_CHAR* contact_num);


/**
 * @brief 取消对联系人状态的订阅
 * 
 * @param [in] TUP_UINT32 account_id        <b>:</b> 账号ID
 * @param [in] const TUP_CHAR* contact_num  <b>:</b> 联系人号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_subscribe_contact
 **/
TUP_API TUP_RESULT tup_call_unsubscribe_contact(IN TUP_UINT32 account_id, IN const TUP_CHAR* contact_num);


/**
 * @brief 订阅RLS(Resource List Server)列表
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_unsubscriber_RLS
 **/
TUP_API TUP_RESULT tup_call_subscriber_RLS(IN TUP_UINT32 accountid);


/**
 * @brief 取消订阅RLS(Resource List Server)列表
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_subscriber_RLS
 **/
TUP_API TUP_RESULT tup_call_unsubscriber_RLS(IN TUP_UINT32 accountid);


/**
 * @brief 设置共享线路私人呼叫
 * 
 * @param [in] TUP_UINT32 accountid               <b>:</b> 账号ID
 * @param [in] CALL_E_SERVICE_CALL_TYPE calltype  <b>:</b> 呼叫类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_SCA_private(IN TUP_UINT32 accountid, IN CALL_E_SERVICE_CALL_TYPE calltype);


/**
 * @brief 同步配置项的业务权限
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 硬终端使用，在配置项发生变更( 如"分机携带"或"网管下发配置")时，由产品调用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_sync_service_right(TUP_VOID);


/**
 * @brief 重新加载业务权限
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_update_serviceright
 **/
TUP_API TUP_RESULT tup_call_reload_serviceright(TUP_VOID);


/**
 * @brief 更新指定业务权限
 * 
 * @param [in] TUP_UINT32 accountid                       <b>:</b> 账号ID
 * @param [in] const CALL_S_SERVICERIGHT_CFG* servicecfg  <b>:</b> 待更新的业务权限
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_reload_serviceright
 **/
TUP_API TUP_RESULT tup_call_update_serviceright(IN TUP_UINT32 accountid, IN const CALL_S_SERVICERIGHT_CFG* servicecfg);


/**
 * @brief 界面登记业务成功后通知更新业务权限登记情况
 * 
 * @param [in] TUP_UINT32 accountid                    <b>:</b> 账号ID
 * @param [in] CALL_E_SERVICE_RIGHT_TYPE service_type  <b>:</b> 业务类型
 * @param [in] TUP_UINT32 reg                          <b>:</b> 登记情况，CALL_E_SEVICEREGISTER_STATUS
 * @param [in] const TUP_CHAR* param                   <b>:</b> 业务参数，如前转的目的号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_service_register(IN TUP_UINT32 accountid, 
                    IN CALL_E_SERVICE_RIGHT_TYPE service_type, IN TUP_UINT32 reg, IN const TUP_CHAR* param);


/**
 * @brief 获取业务权限
 * 
 * @param [in] TUP_UINT32 accountid                 <b>:</b> 账号ID
 * @param [out] CALL_S_SERVICERIGHT_CFG* servicecfg  <b>:</b> 业务权限信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_serviceright(IN TUP_UINT32 accountid, OUT CALL_S_SERVICERIGHT_CFG* servicecfg);


/**
 * @brief 发起SIP账户鉴权
 * 
 * @param [in] const TUP_CHAR* number    <b>:</b> 用户号码
 * @param [in] const TUP_CHAR* name      <b>:</b> 用户名
 * @param [in] const TUP_CHAR* password  <b>:</b> 鉴权密码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_authorize_account(IN const TUP_CHAR* number, IN const TUP_CHAR* name, IN const TUP_CHAR* password);


/**
 * @brief 创建会议所需的控制块
 * 
 * @param [out] TUP_UINT32 *confid  <b>:</b> 会议(控制块)ID
 * @param [out] TUP_UINT32 *callid  <b>:</b> 呼叫(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 供话机使用，在创会之前调用，创建会议所需的控制块
 * @see tup_call_serverconf_set_type
 * @see tup_call_serverconf_create_by_confid
 **/
TUP_API TUP_RESULT tup_call_serverconf_create_confid(OUT TUP_UINT32 *confid, OUT TUP_UINT32 *callid);


/**
 * @brief 设置会议类型
 * 
 * @param [in] TUP_UINT32 confid            <b>:</b> 会议(控制块)ID
 * @param [in] CALL_E_SERVERCONF_TYPE type  <b>:</b> 会议类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 供话机使用，在创会之前调用,以控制创建会议的类型
 * @see tup_call_serverconf_create_confid
 * @see tup_call_serverconf_create_by_confid
 **/
TUP_API TUP_RESULT tup_call_serverconf_set_type(IN TUP_UINT32 confid, IN CALL_E_SERVERCONF_TYPE type);


/**
 * @brief 根据会议id新建会议
 * 
 * @param [in] TUP_UINT32 confid         <b>:</b> 会议(控制块)ID
 * @param [in] const TUP_CHAR *groupuri  <b>:</b> 群组URI，如果是群组会议时填写
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 供话机使用，在创会之前需要创建会议控制块和设置会议类型, 
 * @see tup_call_serverconf_create_confid
 * @see tup_call_serverconf_set_type
 **/
TUP_API TUP_RESULT tup_call_serverconf_create_by_confid(IN TUP_UINT32 confid, IN const TUP_CHAR *groupuri);


/**
 * @brief 根据指定账户已有的callid创建会议所需的控制块
 * 
 * @param [in] TUP_UINT32 accountid    <b>:</b> 账号ID
 * @param [in] TUP_UINT32 incallid     <b>:</b> 原有呼叫ID
 * @param [out] TUP_UINT32* confid     <b>:</b> 会议(控制块)ID
 * @param [out] TUP_UINT32* outcallid  <b>:</b> 会议相对应的呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_create_confid
 **/
TUP_API TUP_RESULT tup_call_serverconf_create_confid_ex (IN TUP_UINT32 accountid, 
                    IN TUP_UINT32 incallid , OUT TUP_UINT32* confid, OUT TUP_UINT32* outcallid);


/**
 * @brief 接听指定线路的会议来电
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @param [in] TUP_UINT32 lineid  <b>:</b> 线路ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_accept
 **/
TUP_API TUP_RESULT tup_call_serverconf_accept_with_lineid(IN TUP_UINT32 confid, IN TUP_UINT32 lineid);


/**
 * @brief 需额外邀入CTD话机
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> 会议ID
 * @param [in] const TUP_CHAR *number  <b>:</b> 外邀入CTD号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于华为UC中转会议
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_add_extra_num(IN TUP_UINT32 confid, IN const TUP_CHAR *number);


/**
 * @brief 拒绝点对点数据会议 
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_reject_p2pdataconf(IN TUP_UINT32 confid);


/**
 * @brief 直接接入预约会议
 * 
 * @param [in] TUP_UINT32 callid           <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR *accesscode  <b>:</b> 会议接入码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 直接接入预约会议，需要创建callid，提供给话机多帐号的情况下使用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_access_reserved_conf_directly(IN TUP_UINT32 callid, IN const TUP_CHAR *accesscode);


/**
 * @brief 设置会议主题
 * 
 * @param [in] TUP_UINT32 confid            <b>:</b> 会议(控制块)ID
 * @param [in] const TUP_CHAR* confsubject  <b>:</b> 会议主题
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 暂仅硬终端使用，在创建会议后设置本地会议主题，用于会议窗口创建立即显示
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_set_confsubject(IN TUP_UINT32 confid, IN const TUP_CHAR* confsubject);


/**
 * @brief 获取用户所有账号预约会议列表
 * 
 * @param [in] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 暂仅话机使用
 * @see tup_call_get_conf_list_for_account
 **/
TUP_API TUP_RESULT tup_call_get_all_conf_list(TUP_VOID);


/**
 * @brief 获取用户指定账号预约会议列表
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 待获取会议列表的账号ID
 * @param [in] TUP_UINT32 pagesize   <b>:</b> 最大会议列表页数 
 * @param [in] TUP_UINT32 curpage    <b>:</b> 当前会议列表页面索引 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 暂仅话机使用
 * @see tup_call_get_all_conf_list
 **/
TUP_API TUP_RESULT tup_call_get_conf_list_for_account(IN TUP_UINT32 accountid, IN TUP_UINT32 pagesize, IN TUP_UINT32 curpage);




/**
 * @brief 获取本地会议会场状态
 * 
 * @param [in] CALL_S_CONFER_LOCAL_INFO* confinfo  <b>:</b> 本地会议会场信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_localconf_get_conferstate(IN CALL_S_CONFER_LOCAL_INFO* confinfo);


/**
 * @brief 本地会议中静音自己
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_unmute_self
 **/
TUP_API TUP_RESULT tup_call_localconf_mute_self(IN TUP_UINT32 callid);


/**
 * @brief 本地会议中取消静音自己
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_mute_self
 **/
TUP_API TUP_RESULT tup_call_localconf_unmute_self(IN TUP_UINT32 callid);


/**
 * @brief 保持本地会议会场
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_unhold
 **/
TUP_API TUP_RESULT tup_call_localconf_hold(TUP_VOID);


/**
 * @brief 取消保持本地会议会场
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_hold
 **/
TUP_API TUP_RESULT tup_call_localconf_unhold(TUP_VOID);


/**
 * @brief 发起群组代答
 * 
 * @param [in] TUP_UINT32 callid           <b>:</b> 呼叫ID
 * @param [in] CALL_E_CALL_TYPE call_type  <b>:</b> 呼叫类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_group_pickup(IN TUP_UINT32 callid, IN CALL_E_CALL_TYPE call_type);


/**
 * @brief 设置呼叫前转
 * 
 * @param [in] const CALL_S_FORWARD_INFO* fwdconfig  <b>:</b> 前转参数配置数组
 * @param [in] TUP_UINT32 configcount                <b>:</b> 前转参数配置数组个数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_forward_config(IN const CALL_S_FORWARD_INFO* fwdconfig , IN TUP_UINT32 configcount);


/**
 * @brief 发起intercom呼叫
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_intercom_call(IN TUP_UINT32 callid, IN const TUP_CHAR* callee_number);


/**
 * @brief 收听留言
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码(VVM接入号码)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_query
 * @see tup_call_VVM_forward
 * @see tup_call_VVM_delete
 * @see tup_call_VVM_pausal
 * @see tup_call_VVM_fast_forward
 * @see tup_call_VVM_rewind
 **/
TUP_API TUP_RESULT tup_call_VVM_listen(IN TUP_UINT32 callid,  IN const TUP_CHAR* callee_number);


/**
 * @brief 下载留言
 * 
 * @param [in] const CALL_S_VVM_QUERY_MSG* query  <b>:</b> VVM请求下载留言数据结构
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_listen
 * @see tup_call_VVM_forward
 * @see tup_call_VVM_delete
 * @see tup_call_VVM_pausal
 * @see tup_call_VVM_fast_forward
 * @see tup_call_VVM_rewind
 **/
TUP_API TUP_RESULT tup_call_VVM_query(IN const CALL_S_VVM_QUERY_MSG* query);


/**
 * @brief 转发留言
 * 
 * @param [in] const CALL_S_VVM_FWD_MSG* fwd  <b>:</b> VVM转发留言数据结构
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_listen
 * @see tup_call_VVM_query
 * @see tup_call_VVM_delete
 * @see tup_call_VVM_pausal
 * @see tup_call_VVM_fast_forward
 * @see tup_call_VVM_rewind
 **/
 
TUP_API TUP_RESULT tup_call_VVM_forward(IN const CALL_S_VVM_FWD_MSG* fwd);


/**
 * @brief 删除留言
 * 
 * @param [in] const CALL_S_VVM_DEL_MSG* del  <b>:</b> VVM转发留言数据结构
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_listen
 * @see tup_call_VVM_query
 * @see tup_call_VVM_forward
 * @see tup_call_VVM_pausal
 * @see tup_call_VVM_fast_forward
 * @see tup_call_VVM_rewind
 **/
TUP_API TUP_RESULT tup_call_VVM_delete(IN const CALL_S_VVM_DEL_MSG* del);


/**
 * @brief 留言播放(暂停)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_listen
 * @see tup_call_VVM_query
 * @see tup_call_VVM_forward
 * @see tup_call_VVM_delete
 * @see tup_call_VVM_fast_forward
 * @see tup_call_VVM_rewind
 **/
TUP_API TUP_RESULT tup_call_VVM_pausal(IN TUP_UINT32 callid);


/**
 * @brief 留言快进
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_listen
 * @see tup_call_VVM_query
 * @see tup_call_VVM_forward
 * @see tup_call_VVM_delete
 * @see tup_call_VVM_pausal
 * @see tup_call_VVM_rewind
 **/
TUP_API TUP_RESULT tup_call_VVM_fast_forward(IN TUP_UINT32 callid);


/**
 * @brief 留言快退
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_VVM_listen
 * @see tup_call_VVM_query
 * @see tup_call_VVM_forward
 * @see tup_call_VVM_delete
 * @see tup_call_VVM_pausal
 * @see tup_call_VVM_fast_forward
 **/
TUP_API TUP_RESULT tup_call_VVM_rewind(IN TUP_UINT32 callid);


/**
 * @brief 登录过程中取消登录
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_cancel_login(TUP_VOID);


/**
 * @brief 设置会议联动
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL islink    <b>:</b> 是否联动
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_set_linked(IN TUP_UINT32 callid, IN TUP_BOOL islink);


/**
 * @brief 服务器会议二次拨号
 * 
 * @param [in] TUP_UINT32 confid        <b>:</b> 会议ID
 * @param [in] CALL_E_DTMF_TONE keyevt  <b>:</b> DTMF键值
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_send_DTMF(IN TUP_UINT32 confid, IN CALL_E_DTMF_TONE keyevt);


/**
 * @brief 邀请点对点方加入数据会议
 * 
 * @param [in] TUP_UINT32 confid           <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* p2p_number  <b>:</b> 被邀请的P2P号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 华为UC组网下，CTD的情况下才需要调用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_add_p2p_to_dataconf(IN TUP_UINT32 confid, IN const TUP_CHAR* p2p_number);


/**
 * @brief 创建联动会议
 * 
 * @param [in] TUP_UINT32 confid              <b>:</b> 会议ID
 * @param [in] TUP_UINT32 attendcount         <b>:</b> 与会者数量
 * @param [in] const  TUP_CHAR* attendnumber  <b>:</b> 与会者号码数组
 * @param [in] TUP_UINT32 pernumsize          <b>:</b> 每个号码最大长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_create_linkage_conf(IN TUP_UINT32 confid, 
                    IN TUP_UINT32 attendcount, IN const  TUP_CHAR* attendnumber, IN TUP_UINT32 pernumsize);


/**
 * @brief 设置拒绝前转来电开关
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 账号ID
 * @param [in] TUP_BOOL switches     <b>:</b> 1 开启，0 关闭
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_DICF_switct(IN TUP_UINT32 accountid, IN TUP_BOOL switches);



/**
 * @brief 开启所有账号DND
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_all_account_DND_off
 **/
TUP_API TUP_RESULT tup_call_set_all_account_DND_on(TUP_VOID);


/**
 * @brief 关闭所有账号DND
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_all_account_DND_on
 **/
TUP_API TUP_RESULT tup_call_set_all_account_DND_off(TUP_VOID);


/**
 * @brief 设置所有账号缺席业务
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_all_account_absent_off
 **/
TUP_API TUP_RESULT tup_call_set_all_account_absent_on(TUP_VOID);


/**
 * @brief 设置所有账号取消缺席
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_all_account_absent_on
 **/
TUP_API TUP_RESULT tup_call_set_all_account_absent_off(TUP_VOID);


/**
 * @brief 设置MCID(恶意呼叫跟*踪)
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_MCID(IN TUP_UINT32 accountid);


/**
 * @brief 批量登记所有账号IPT业务
 * 
 * @param [in] const CALL_S_IPT_DATA* IPTdata  <b>:</b> 待登记的IPT业务配置数据
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_IPTservice_batch(IN const CALL_S_IPT_DATA* IPTdata);


/**
 * @brief 批量登记指定账号IPT业务
 * 
 * @param [in] TUP_UINT32 accountid      <b>:</b> 账号ID
 * @param [in] CALL_S_IPT_DATA* IPTdata  <b>:</b> 待登记的IPT业务配置数据
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_IPTservice_for_accout(IN TUP_UINT32 accountid, IN CALL_S_IPT_DATA* IPTdata);


/**
 * @brief 开启指定账号密码限呼
 * 
 * @param [in] TUP_UINT32 accountid            <b>:</b> 账号ID
 * @param [in] const CALL_S_IPT_DATA* IPTdata  <b>:</b> 密码限呼业务配置数据
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_cancel_callbarring_for_account
 **/
TUP_API TUP_RESULT tup_call_set_callbarring_for_account(IN TUP_UINT32 accountid, IN const CALL_S_IPT_DATA* IPTdata);


/**
 * @brief 关闭指定账号密码限呼
 * 
 * @param [in] TUP_UINT32 accountid            <b>:</b> 账号ID
 * @param [in] const CALL_S_IPT_DATA* IPTdata  <b>:</b> 密码限呼业务配置数据
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_callbarring_for_account
 **/
TUP_API TUP_RESULT tup_call_cancel_callbarring_for_account(IN TUP_UINT32 accountid, IN const CALL_S_IPT_DATA* IPTdata);


/**
 * @brief 合并会议
 * 
 * @param [in] TUP_UINT32 confid                  <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* security_conf_num  <b>:</b> 安全会议号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_split
 **/
TUP_API TUP_RESULT tup_call_serverconf_merger(IN TUP_UINT32 confid, IN const TUP_CHAR* security_conf_num);


/**
 * @brief 拆分会议
 * 
 * @param [in] TUP_UINT32 confid                  <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* security_conf_num  <b>:</b> 安全会议号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_merger
 **/
TUP_API TUP_RESULT tup_call_serverconf_split(IN TUP_UINT32 confid, IN const TUP_CHAR* security_conf_num);


/**
 * @brief 创建视频窗口
 * 
 * @param [in] TUP_UINT32 count                    <b>:</b> 窗口个数，一般为2
 * @param [in] const CALL_S_VIDEOWND_INFO* window  <b>:</b> 窗口数据 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于呼叫未建立(主叫呼出)时，预先创建(设置)视频窗口
             <br>被tup_call_set_video_window接口替代，已废弃
 * @see tup_call_destroy_video_window
 * @see tup_call_set_video_window
 **/
TUP_API TUP_RESULT tup_call_create_video_window(IN TUP_UINT32 count, IN const CALL_S_VIDEOWND_INFO* window);



/**
 * @brief 更新视频窗口信息
 * 
 * @param [in] TUP_UINT32 Count                    <b>:</b> 窗口个数，一般为2
 * @param [in] const CALL_S_VIDEOWND_INFO* window  <b>:</b> 窗口数据 
 * @param [in] TUP_UINT32 callid                   <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 被tup_call_set_video_window接口替代，已废弃
 * @see tup_call_set_video_window
 **/
TUP_API TUP_RESULT tup_call_update_video_window(IN TUP_UINT32 count, IN const CALL_S_VIDEOWND_INFO * window, IN TUP_UINT32 callid);




/**
 * @brief 销毁视频窗口
 * 
 * @param [in] CALL_E_VIDEOWND_TYPE wndtype  <b>:</b> 窗口类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 硬终端需要使用
 * @see tup_call_create_video_window
 * @see tup_call_set_video_window
 **/
TUP_API TUP_RESULT tup_call_destroy_video_window(IN CALL_E_VIDEOWND_TYPE wndtype);



/**
 * @brief 更新视频窗口
 * 
 * @param [in] TUP_UINT32 ctrl_type                <b>:</b> 视频窗口控制类型，对应CALL_E_VIDEOWND_CTRL_TYPE
 * @param [in] const CALL_S_VIDEOWND_INFO* window  <b>:</b> 视频窗口信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 硬终端需要使用
 * @see tup_call_destroy_video_window
 **/
TUP_API TUP_RESULT tup_call_change_video_window(IN TUP_UINT32 ctrl_type, IN const CALL_S_VIDEOWND_INFO* window);



/**
 * @brief 通话中打开本地预览
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_close_local_preview_in_dialog
 **/
TUP_API TUP_RESULT tup_call_open_local_preview_in_dialog(IN TUP_UINT32 callid);


/**
 * @brief 通话中关闭本地预览
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_open_local_preview_in_dialog
 **/
TUP_API TUP_RESULT tup_call_close_local_preview_in_dialog(IN TUP_UINT32 callid);


/**
 * @brief 通话中打开远端预览
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_close_remote_preview_in_dialog
 **/
TUP_API TUP_RESULT tup_call_open_remote_preview_in_dialog(IN TUP_UINT32 callid);


/**
 * @brief 通话中关闭远端预览
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_open_remote_preview_in_dialog
 **/
TUP_API TUP_RESULT tup_call_close_remote_preview_in_dialog(IN TUP_UINT32 callid);


/**
 * @brief 开启音频回环，用于测试本地MIC和Speaker
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_close_audio_preview
 **/
TUP_API TUP_RESULT tup_call_open_audio_preview(TUP_VOID);


/**
 * @brief 关闭音频回环，用于测试本地MIC和Speaker
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_open_audio_preview
 **/
TUP_API TUP_RESULT tup_call_close_audio_preview(TUP_VOID);


/**
 * @brief 设置指定账号的缺席业务
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_cancel_absent_for_account
 **/
TUP_API TUP_RESULT tup_call_set_absent_for_account(IN TUP_UINT32 accountid);


/**
 * @brief 取消指定账号的缺席业务
 * 
 * @param [in] TUP_UINT32 accountid  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_absent_for_account
 **/
TUP_API TUP_RESULT tup_call_cancel_absent_for_account(IN TUP_UINT32 accountid);

/**
 * @brief 发布账号状态
 * 
 * @param [in] IN TUP_UINT32 account_id     <b>:</b> 账号ID
 * @param [in] IN TUP_UINT32 status_type    <b>:</b> 状态信息，对应CALL_E_CONTACT_STATUS
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_publish_setting_status(IN TUP_UINT32 account_id, IN TUP_UINT32 status_type);


/**
 * @brief 会话内手机分机切换
 * 
 * @param [in] TUP_UINT32 callid      <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* MPnum  <b>:</b> 手机分机号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_mobile_extend_call(IN TUP_UINT32 callid, IN const TUP_CHAR* pszMPNum);


/**
 * @brief 发起intercom双向通话请求
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_answer_intercom_call(IN TUP_UINT32 callid);


/**
 * @brief 设置直接呼叫驻留业务
 * 
 * @param [in] TUP_UINT32 callid             <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR*  direct_num   <b>:</b> 呼叫驻留号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 
 * @attention NA
 * @see tup_call_set_callpark
 * @see tup_call_get_callpark
 **/
TUP_API TUP_RESULT tup_call_direct_callpark(IN TUP_UINT32 callid, IN const TUP_CHAR* direct_num);


/**
 * @brief 设置呼叫驻留业务
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_direct_callpark
 * @see tup_call_get_callpark
 **/
TUP_API TUP_RESULT tup_call_callpark(IN TUP_UINT32 callid);


/**
 * @brief 发起私人保持
 * 
 * @param [in] TUP_UINT32 ulCallID  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_private_hold_call (IN TUP_UINT32 callid);


/**
 * @brief 发起缩位拨号
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 账号ID
 * @param [in] CALL_E_CALL_TYPE call_type     <b>:</b> 呼叫类型
 * @param [in] const TUP_CHAR* callee_number  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_abbrdial_Call(IN TUP_UINT32 callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);

/**
 * @brief 发起指定代答
 * 
 * @param [in] TUP_UINT32 callid             <b>:</b> 呼叫ID
 * @param [in] CALL_E_CALL_TYPE call_type    <b>:</b> 呼叫类型
 * @param [in] const TUP_CHAR* calleenumber  <b>:</b> 被叫号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_point_pickup(IN TUP_UINT32 callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief 创建本地会议
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_join
 * @see tup_call_localconf_drop_conferee
 * @see tup_call_localconf_mute_conferee
 * @see tup_call_localconf_unmute_conferee
 * @see tup_call_localconf_end
 **/
TUP_API TUP_RESULT tup_call_localconf_create(IN TUP_UINT32 call_id);


/**
 * @brief 加入本地会议
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_create
 * @see tup_call_localconf_drop_conferee
 * @see tup_call_localconf_mute_conferee
 * @see tup_call_localconf_unmute_conferee
 * @see tup_call_localconf_end
 **/
TUP_API TUP_RESULT tup_call_localconf_join(IN TUP_UINT32 call_id);


/**
 * @brief 剔除与会者
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_create
 * @see tup_call_localconf_join
 * @see tup_call_localconf_mute_conferee
 * @see tup_call_localconf_unmute_conferee
 * @see tup_call_localconf_end
 **/
TUP_API TUP_RESULT tup_call_localconf_drop_conferee(IN TUP_UINT32 call_id);

/**
 * @brief 静音与会者
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_create
 * @see tup_call_localconf_join
 * @see tup_call_localconf_drop_conferee
 * @see tup_call_localconf_unmute_conferee
 * @see tup_call_localconf_end
 **/
TUP_API TUP_RESULT tup_call_localconf_mute_conferee(IN TUP_UINT32 call_id);


/**
 * @brief 取消静音与会者
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_create
 * @see tup_call_localconf_join
 * @see tup_call_localconf_drop_conferee
 * @see tup_call_localconf_mute_conferee
 * @see tup_call_localconf_end
 **/
TUP_API TUP_RESULT tup_call_localconf_unmute_conferee(IN TUP_UINT32 call_id);


/**
 * @brief 结束本地会议
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_localconf_create
 * @see tup_call_localconf_join
 * @see tup_call_localconf_drop_conferee
 * @see tup_call_localconf_mute_conferee
 * @see tup_call_localconf_unmute_conferee
 **/
TUP_API TUP_RESULT tup_call_localconf_end(TUP_VOID);


/**
 * @brief 发起共享线路强插
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_SCA_retrieve
 * @see tup_call_SCA_sub_state
 * @see tup_call_SCA_offhook
 **/
TUP_API TUP_RESULT tup_call_SCA_insert (IN TUP_UINT32 call_id);


/**
 * @brief 发起共享线路拾起
 * 
 * @param [in] TUP_UINT32 call_id  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_SCA_insert
 * @see tup_call_SCA_sub_state
 * @see tup_call_SCA_offhook
 **/
TUP_API TUP_RESULT tup_call_SCA_retrieve (IN TUP_UINT32 call_id);


/**
 * @brief 发起共享线订阅
 * 
 * @param [in] TUP_UINT32 account_id  <b>:</b> 账号ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_SCA_insert
 * @see tup_call_SCA_retrieve
 * @see tup_call_SCA_offhook
 **/
TUP_API TUP_RESULT tup_call_SCA_sub_state(IN TUP_UINT32 account_id);


/**
 * @brief 共享线路摘机
 * 
 * @param [in] TUP_UINT32 account_id   <b>:</b> 账号ID
 * @param [in] TUP_UINT32 sca_line_id  <b>:</b> 共享线线路ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_SCA_insert
 * @see tup_call_SCA_retrieve
 * @see tup_call_SCA_sub_state
 **/
TUP_API TUP_RESULT tup_call_SCA_offhook (IN TUP_UINT32 account_id, IN TUP_UINT32 sca_line_id);


/**
 * @brief 播放TC铃音 
 * 
 * @param [in] TUP_INT32 tc_file_value   <b>:</b> 文件对应的值
 * @param [out] TUP_INT32* play_handle   <b>:</b> 播放句柄(用于停止播放时的参数)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 废弃接口，被tup_call_media_startplay_ex替代
 * @see tup_call_media_startplay
 * @see tup_call_media_startplay_ex
 * @see tup_call_media_startLocalplay
 * @see tup_call_media_stopplay
 **/
TUP_API TUP_RESULT tup_call_media_startTcplay(IN TUP_INT32 tc_file_value, OUT TUP_INT32* play_handle);


/**
 * @brief 强制本地播放铃音(用于在TC模式下播放本地文件) 
 * 
 * @param [in] TUP_UINT32 loops           <b>:</b> 循环次数
 * @param [in] const TUP_CHAR* play_file  <b>:</b> 播放铃声文件名
 * @param [out] TUP_INT32* play_handle    <b>:</b> 播放句柄(用于停止播放时的参数)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 废弃接口，被tup_call_media_startplay_ex替代
 * @see tup_call_media_startplay
 * @see tup_call_media_startplay_ex
 * @see tup_call_media_startTcplay
 * @see tup_call_media_stopplay
 **/
TUP_API TUP_RESULT tup_call_media_startLocalplay(IN TUP_UINT32 loops, IN const TUP_CHAR* play_file, OUT TUP_INT32* play_handle);


/**
 * @brief 停止播放信号音
 * 
 * @param [in] TUP_UINT32 sender_handle  <b>:</b> 信号音发送方的处理模块ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_play_signal_tone
 **/
TUP_API TUP_RESULT tup_call_media_stop_signal_tone(IN TUP_UINT32 sender_handle);


/**
 * @brief 播放信号音
 * 
 * @param [in] TUP_UINT32 toneid         <b>:</b> 信号音ID
 * @param [in] TUP_BOOL is_cycle         <b>:</b> 是否循环播放
 * @param [in] TUP_UINT32 sender_handle  <b>:</b> 信号音发送方的处理模块ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_stop_signal_tone
 **/
TUP_API TUP_RESULT tup_call_media_play_signal_tone(IN TUP_UINT32 toneid, IN TUP_BOOL is_cycle, IN TUP_UINT32 sender_handle);


/**
 * @brief 播放会场信号音
 * 
 * @param [in] TUP_UINT32 toneid         <b>:</b> 信号音ID
 * @param [in] TUP_BOOL is_cycle         <b>:</b> 是否循环播放
 * @param [in] TUP_UINT32 sender_handle  <b>:</b> 信号音发送方的处理模块ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_stop_signal_tone_to_conf
 **/
TUP_API TUP_RESULT tup_call_media_play_signal_tone_to_conf(IN TUP_UINT32 toneid, IN TUP_BOOL iscycle, IN TUP_UINT32 sender_handle);


/**
 * @brief 停止播放会场信号音
 * 
 * @param [in] TUP_UINT32 sender_handle  <b>:</b> 信号音发送方的处理模块ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_play_signal_tone_to_conf
 **/
TUP_API TUP_RESULT tup_call_media_stop_signal_tone_to_conf(IN TUP_UINT32 senderhandle);


/**
 * @brief 获取输出音量
 * 
 * @param [out] TUP_UINT32* volume  <b>:</b> 音量值
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_set_speak_volume
 * @see tup_call_media_get_speak_level
 **/
TUP_API TUP_RESULT tup_call_media_get_speak_volume(OUT TUP_UINT32* volume);


/**
 * @brief 获取输出音量级别
 * 
 * @param [out] TUP_UINT32* level  <b>:</b> 音量级别
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_set_speak_volume
 * @see tup_call_media_get_speak_volume
 **/
TUP_API TUP_RESULT tup_call_media_get_speak_level(OUT TUP_UINT32* level);


/**
 * @brief 设置输入音量
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE aud_direction  <b>:</b> 音频输入输出设备类型(硬终端使用)
 * @param [in] TUP_UINT32 volume                  <b>:</b> 音量值，取值范围[0, 100]
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_get_mic_volume
 * @see tup_call_media_get_mic_level
 **/
TUP_API TUP_RESULT tup_call_media_set_mic_volume(IN CALL_E_AUDDEV_ROUTE aud_direction, IN TUP_UINT32 volume);


/**
 * @brief 获取输入音量
 * 
 * @param [out] TUP_UINT32* volume  <b>:</b> 音量值
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_set_mic_volume
 * @see tup_call_media_get_mic_level
 **/
TUP_API TUP_RESULT tup_call_media_get_mic_volume(OUT TUP_UINT32* volume);


/**
 * @brief 获取输入音量级别
 * 
 * @param [out] TUP_UINT32* level  <b>:</b> 音量级别
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_set_mic_volume
 * @see tup_call_media_get_mic_volume
 **/
TUP_API TUP_RESULT tup_call_media_get_mic_level(OUT TUP_UINT32* level);


/**
 * @brief 获取系统杨声器静音状态
 * 
 * @param [out] TUP_BOOL* is_mute  <b>:</b> 是否静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_get_sys_mic_mute
 **/
TUP_API TUP_RESULT tup_call_media_get_sys_spk_mute(OUT TUP_BOOL* is_mute);

 
/**
 * @brief 获取系统麦克风静音状态
 * 
 * @param [out] TUP_BOOL* is_mute  <b>:</b> 是否静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_get_sys_spk_mute
 **/
TUP_API TUP_RESULT tup_call_media_get_sys_mic_mute(OUT TUP_BOOL* is_mute);


/**
 * @brief 获取硬件加速能力
 * 
 * @param [out] CALL_S_VIDEO_HDACCELERATE *hd_accelerate  <b>:</b> 视频编解码器加速信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_media_get_hdaccelerate(OUT CALL_S_VIDEO_HDACCELERATE *hd_accelerate);


/**
 * @brief 开始播放铃音
 * 
 * @param [in] const TUP_INT8* ringfile  <b>:</b> 铃音文件
 * @param [in] TUP_UINT32 senderhandler  <b>:</b> 铃音播放方的处理模块ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_stop_ring_tone
 **/
TUP_API TUP_RESULT tup_call_media_play_ring_tone(IN const TUP_INT8* ringfile, IN TUP_UINT32 senderhandler);


/**
 * @brief 停止播放铃音
 * 
 * @param [in] TUP_UINT32 senderhandler  <b>:</b> 铃音播放方的处理模块ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_play_ring_tone
 **/
TUP_API TUP_RESULT tup_call_media_stop_ring_tone(IN TUP_UINT32 senderhandler);


/**
 * @brief 设置硬件(摄像头)参数
 * 
 * @param [in] const CALL_S_HARDWARE_PARAMS* hardwareparams  <b>:</b> 硬件(摄像头)参数结构
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_get_hardware_params
 **/
TUP_API TUP_RESULT tup_call_set_hardware_params(IN const CALL_S_HARDWARE_PARAMS* hardwareparams);


/**
 * @brief 获取硬件(摄像头)参数
 * 
 * @param [in] CALL_S_HARDWARE_PARAMS* hardwareparams  <b>:</b> 硬件(摄像头)参数结构
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_hardware_params
 **/
TUP_API TUP_RESULT tup_call_get_hardware_params(IN CALL_S_HARDWARE_PARAMS* hardwareparams);


/**
 * @brief 改变视频窗口显示位置
 * 
 * @param [in] CALL_E_VIDEOWND_TYPE wndtype                        <b>:</b> 窗口类型
 * @param [in] const TUP_INT32 coordinate[CALL_E_COORDINATE_BUTT]  <b>:</b> 目标坐标信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 暂仅硬终端需要使用
 * @see tup_call_change_video_window_type
 **/
TUP_API TUP_RESULT tup_call_change_video_window_pos(IN CALL_E_VIDEOWND_TYPE wndtype, IN const TUP_INT32 coordinate[CALL_E_COORDINATE_BUTT]);


/**
 * @brief 改变视频窗口显示类型
 * 
 * @param [in] CALL_E_VIDEOWND_TYPE wndtype  <b>:</b> 窗口类型
 * @param [in] TUP_UINT32 displaytype        <b>:</b> 目标显示类型，0:拉伸模式 1:(不拉伸)黑边模式 2:(不拉伸)裁剪模式)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 暂仅硬终端需要使用
 * @see tup_call_change_video_window_pos
 **/
TUP_API TUP_RESULT tup_call_change_video_window_type(IN CALL_E_VIDEOWND_TYPE wndtype, IN TUP_UINT32 displaytype);


/**
 * @brief 获取安全会议号请求
 * 
 * @param [in] TUP_UINT32 confid         <b>:</b> 会议ID
 * @param [out] TUP_CHAR*  security_num  <b>:</b> 安全会议号
 * @param [in] TUP_UINT32 numsize        <b>:</b> 存储安全会议号内存的大小
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_get_securitynum(IN TUP_UINT32 confid, OUT TUP_CHAR* security_num, IN TUP_UINT32 numsize);


/**
 * @brief 一键转语音邮箱
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* divert_number  <b>:</b> 呼叫驻留
 * @param [in] TUP_BOOL is_callpicked         <b>:</b> 通话是否已经建立
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_onekey_transferto_VM(IN TUP_UINT32 callid, IN const TUP_CHAR* divert_number, IN TUP_BOOL is_callpicked);


/**
 * @brief 创建视频会议窗口
 * 
 * @param [in] TUP_UINT32 confid                         <b>:</b> 会议ID
 * @param [in] const CALL_S_VIDEOWND_INFO* videowndinfo  <b>:</b> 视频窗口信息
 * @param [in] TUP_UINT32 wndnum                         <b>:</b> 窗口数量，取值[1,20]
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_destroy_wnd
 **/
TUP_API TUP_RESULT tup_call_videoconf_create_wnd(IN TUP_UINT32 confid, IN const CALL_S_VIDEOWND_INFO* videowndinfo, IN TUP_UINT32 wndnum);


/**
 * @brief 销毁视频会议窗口
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_create_wnd
 **/
TUP_API TUP_RESULT tup_call_videoconf_destroy_wnd(IN TUP_UINT32 confid);


/**
 * @brief 打开视频会议自己的视频
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_close_self_video
 **/
TUP_API TUP_RESULT tup_call_videoconf_open_self_video(IN TUP_UINT32 confid);


/**
 * @brief 关闭视频会议自己的视频
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_close_self_video
 **/
TUP_API TUP_RESULT tup_call_videoconf_close_self_video(IN TUP_UINT32 confid);


/**
 * @brief 通知视频会议与会者打开视频
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_notify_attend_close_video
 **/
TUP_API TUP_RESULT tup_call_videoconf_notify_attend_open_video(IN TUP_UINT32 confid, IN const TUP_CHAR* attendnum);


/**
 * @brief 通知视频会议与会者打开视频
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_notify_attend_open_video
 **/
TUP_API TUP_RESULT tup_call_videoconf_notify_attend_close_video(IN TUP_UINT32 confid, IN const TUP_CHAR* attendnum);



/**
 * @brief 显示与会者视频到窗口
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @param [in] TUP_UINT32 wndid           <b>:</b> 窗口ID
 * @param [in] TUP_UINT32 ishighstream    <b>:</b> 是否是高(清晰)流
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_detach_attend_video_from_wnd
 **/
TUP_API TUP_RESULT tup_call_videoconf_attach_attend_video_to_wnd(IN TUP_UINT32 confid, 
                    IN const TUP_CHAR* attendnum, IN TUP_UINT32 wndid, IN TUP_UINT32 ishighstream);


/**
 * @brief 取消显示与会者视至窗口
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @param [in] TUP_UINT32 wndid           <b>:</b> 窗口ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_attach_attend_video_to_wnd
 **/
TUP_API TUP_RESULT tup_call_videoconf_detach_attend_video_from_wnd(IN TUP_UINT32 confid, 
                    IN const TUP_CHAR* attendnum, IN TUP_UINT32 wndid);

/**
 * @brief 改变视频会议与会者视频窗口大小
 * 
 * @param [in] TUP_UINT32 confid                    <b>:</b> 会议ID
 * @param [in] TUP_UINT32 wndid                     <b>:</b> 窗口ID
 * @param [in] const CALL_S_VIDEOWND_INFO* wndinfo  <b>:</b> 窗口信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_change_wnd_size(IN TUP_UINT32 confid, IN TUP_UINT32 wndid, IN const CALL_S_VIDEOWND_INFO* wndinfo);


/**
 * @brief 切换视频会议与会者视频分辨率，高流和低流
 * 
 * @param [in] TUP_UINT32 confid            <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum    <b>:</b> 与会者号码
 * @param [in] TUP_UINT32 ishighresolution  <b>:</b> 是否是高(清晰)流
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_switch_attend_video_resolution(IN TUP_UINT32 confid, IN const TUP_CHAR* attendnum, IN TUP_UINT32 ishighresolution);


/**
 * @brief 关闭视频会议所有与会者视频
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_close_self_all_video(IN TUP_UINT32 confid);


/**
 * @brief 暂停视频会议本地视频
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_resume_attend_local_video
 **/
TUP_API TUP_RESULT tup_call_videoconf_pause_attend_local_video(IN TUP_UINT32 confid, IN const TUP_CHAR* attendnum);


/**
 * @brief 恢复视频会议本地视频
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_pause_attend_local_video
 **/
TUP_API TUP_RESULT tup_call_videoconf_resume_attend_local_video(IN TUP_UINT32 confid, IN const TUP_CHAR* attendnum);


/**
 * @brief 改变视频会议与会者视频窗口"Z"序
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @param [in] TUP_UINT32 zorder  <b>:</b> "Z"序
 * @param [in] TUP_UINT32 wndid   <b>:</b> 窗口ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_change_wnd_zorder(IN TUP_UINT32 confid, IN TUP_UINT32 zorder, IN TUP_UINT32 wndid);


/**
 * @brief 音频会议转视频会议
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_voiceconf_tranfto_videoconf(IN TUP_UINT32 confid);


/**
 * @brief 改变视频会议多个与会者视频窗口大小和窗口Z序
 * 
 * @param [in] TUP_UINT32 confid                      <b>:</b> 会议ID
 * @param [in] const CALL_S_VIDEOWND_INFO* videoinfo  <b>:</b> 窗口信息
 * @param [in] TUP_UINT32 infocount                   <b>:</b> 窗口信息个数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_change_wnd_pos(IN TUP_UINT32 confid, IN const CALL_S_VIDEOWND_INFO* videoinfo, IN TUP_UINT32 infocount);


/**
 * @brief 打开视频会议预览
 * 
 * @param [in] TUP_UINT32 confid                               <b>:</b> 会议ID
 * @param [in] TUP_UINT32 wndid                                <b>:</b> 窗口ID
 * @param [in] const CALL_S_VIDEOCONF_VIDEO_PARAM* videoparam  <b>:</b> 视频会议预览参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_videoconf_close_preview
 **/
TUP_API TUP_RESULT tup_call_videoconf_open_preview(IN TUP_UINT32 confid, IN TUP_UINT32 wndid, IN const CALL_S_VIDEOCONF_VIDEO_PARAM* videoparam);


/**
 * @brief 关闭视频会议预览
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_close_preview(IN TUP_UINT32 confid);


/**
 * @brief 获取视频会议与会者视频状态
 * 
 * @param [in] TUP_UINT32 confid          <b>:</b> 会议ID
 * @param [in] const TUP_CHAR* attendnum  <b>:</b> 与会者号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_videoconf_get_video_device_status(IN TUP_UINT32 confid, IN const TUP_CHAR* attendnum);


/**
 * @brief  装备测试开始同步保存
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE audioinputdev  <b>:</b> 音频输入设备
 * @param [in] TUP_UINT32 volume                  <b>:</b> 音量
 * @param [in] TUP_UINT32 samplefreq              <b>:</b> 采样率
 * @param [in] TUP_UINT32 bitwide                 <b>:</b> 带宽
 * @param [in] TUP_UINT32 recordtime              <b>:</b> 同步保存时间
 * @param [in] TUP_UINT32 audiotype               <b>:</b> 音频类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_eqpt_test_stop_record
 **/
TUP_API TUP_RESULT tup_call_eqpt_test_start_record(IN CALL_E_AUDDEV_ROUTE audioinputdev, IN TUP_UINT32 volume, 
                    IN TUP_UINT32 samplefreq, IN TUP_UINT32 bitwide, IN TUP_UINT32 recordtime, IN TUP_UINT32 audiotype);


/**
 * @brief 装备测试停止同步保存
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE audioinputdev  <b>:</b> 音频输入设备
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_eqpt_test_start_record
 **/
TUP_API TUP_RESULT tup_call_eqpt_test_stop_record(IN CALL_E_AUDDEV_ROUTE audioinputdev);


/**
 * @brief 装备测试开始播放
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE audioinputdev  <b>:</b> 音频输入设备
 * @param [in] TUP_UINT32 volume                  <b>:</b> 音量
 * @param [in] TUP_UINT32 samplefreq              <b>:</b> 采样率
 * @param [in] TUP_UINT32 bitwide                 <b>:</b> 带宽
 * @param [in] TUP_UINT32 AMPtype                 <b>:</b> AMP类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_eqpt_test_stop_play
 **/
TUP_API TUP_RESULT tup_call_eqpt_test_start_play(IN CALL_E_AUDDEV_ROUTE audiooutputdev, 
                    IN TUP_UINT32 volume, IN TUP_UINT32 samplefreq, IN TUP_UINT32 bitwide, IN TUP_UINT32 AMPtype);


/**
 * @brief 装备测试开始播放
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE audiooutputdev  <b>:</b> 音频输入设备
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_eqpt_test_start_play
 **/
TUP_API TUP_RESULT tup_call_eqpt_test_stop_play(IN CALL_E_AUDDEV_ROUTE audiooutputdev);


/**
 * @brief 切换DND类型(本地/服务器)
 * 
 * @param [in] TUP_UINT32 DNDtype       <b>:</b> DND模式，对应CALL_E_DND_TYPE
 * @param [in] TUP_UINT32 localDNDtype  <b>:</b> DND类型，对应CALL_E_LOCALDND_TYPE
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_switch_DND_type(IN TUP_UINT32 DNDtype, IN TUP_UINT32 localDNDtype);


/**
 * @brief 设置音频设备参数
 * 
 * @param [in] TUP_UINT32 anc  <b>:</b> 噪声抑制
 * @param [in] TUP_UINT32 aec  <b>:</b> 回声消除
 * @param [in] TUP_UINT32 agc  <b>:</b> 自动增益
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_AEC_params
 **/
TUP_API TUP_RESULT tup_call_set_audio_dev_options(IN TUP_UINT32 anc, IN TUP_UINT32 aec, IN TUP_UINT32 agc);


/**
 * @brief 设置音频AEC参数
 * 
 * @param [in] const CALL_S_AUDIO_AEC_PARAMS* pstAecParams  <b>:</b> 音频AEC参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_audio_dev_options
 **/
TUP_API TUP_RESULT tup_call_set_AEC_params(IN const CALL_S_AUDIO_AEC_PARAMS* aec_params);


/**
 * @brief 设置音频EQ参数
 * 
 * @param [in] const CALL_S_AUDIO_EQ_CONFIG* pstEqConfig  <b>:</b> 音频EQ参数
 * @param [in] CALL_E_AO_DEV enAudDirection               <b>:</b> 音频输入输出设备类型(软终端使用)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_get_EQ_param
 * @see tup_call_set_preset_EQ_param
 **/
TUP_API TUP_RESULT tup_call_set_EQ_param(IN const CALL_S_AUDIO_EQ_CONFIG* pstEqConfig, IN CALL_E_AO_DEV enAudDirection);


/**
 * @brief 获取音频EQ参数
 * 
 * @param [out] CALL_S_AUDIO_EQ_CONFIG* pstEqConfig  <b>:</b> 音频EQ参数
 * @param [in] CALL_E_AO_DEV enAudDirection          <b>:</b> 音频输入输出设备类型(软终端使用)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @see tup_call_set_EQ_param
 * @see tup_call_set_preset_EQ_param
 **/
TUP_API TUP_RESULT tup_call_get_EQ_param(IN CALL_S_AUDIO_EQ_CONFIG* pstEqConfig, IN CALL_E_AO_DEV enAudDirection);


/**
 * @brief 设置预置音频EQ参数
 * 
 * @param [in] CALL_E_PRESET_EQ_TYPE enPresetEqType  <b>:</b> 预置音频EQ类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @see tup_call_set_EQ_param
 * @see tup_call_get_EQ_param
 **/
TUP_API TUP_RESULT tup_call_set_preset_EQ_param(IN CALL_E_PRESET_EQ_TYPE enPresetEqType);


/**
 * @brief 关闭指定账户刷新注册
 * 
 * @param [in] const TUP_CHAR* number  <b>:</b> 账户号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 账户号码必须是鉴权号码
 * @see tup_call_start_refreshregister
 **/
TUP_API TUP_RESULT tup_call_stop_refreshregister(IN const TUP_CHAR* number);


/**
 * @brief 开启指定账户刷新注册
 * 
 * @param [in] const TUP_CHAR* number  <b>:</b> 账户号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 账户号码必须是鉴权号码
 * @see tup_call_stop_refreshregister
 **/
TUP_API TUP_RESULT tup_call_start_refreshregister(IN const TUP_CHAR* number);


/**
 * @brief 根据消息体获取原始消息
 * 
 * @param [in] TUP_UINT8* msgbody  <b>:</b> 消息体
 * @retval TUP_API TUP_VOID* <b>:</b> 成功返回原始消息指针，失败返回空
 * 
 * @attention 这个函数不安全，禁止再使用(兼容产品历史版本暂保留的接口)
 * @see NA
 **/
TUP_API TUP_VOID* tup_call_get_notifiy_msg_by_msgbody(IN TUP_UINT8* msgbody);


/**
 * @brief 设置客户端名
 * 
 * @param [in] const TUP_CHAR* client_name  <b>:</b> 客户端名字符串，长度不超过11个字节
 * @retval TUP_API TUP_VOID <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_VOID tup_call_set_client_name(IN const TUP_CHAR* client_name);


/**
 * @brief 设置(CALL进程)应用层消息队列名字
 * 
 * @param [in] const TUP_CHAR* client_name  <b>:</b> 消息队列名字
 * @param [in] TUP_BOOL bIsUI               <b>:</b> 是否UI
 * @param [in] TUP_BOOL bIsReg              <b>:</b> 是否注册
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_notify_client_name(IN const TUP_CHAR* client_name, IN TUP_BOOL bIsUI, IN TUP_BOOL bIsReg);


/**
 * @brief 注册回调函数(非主回调函数) 
 * 
 * @param [in] CALL_FN_CALLBACK_PTR callback_process_notify  <b>:</b> 回调函数地址
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_deregister_process_notifiy_ex
 **/
TUP_API TUP_RESULT tup_call_register_process_notifiy_ex(IN CALL_FN_CALLBACK_PTR callback_process_notify);


/**
 * @brief 注销回调函数(非主回调函数) 
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_register_process_notifiy_ex
 **/
TUP_API TUP_RESULT tup_call_deregister_process_notifiy_ex(TUP_VOID);


/**
 * @brief huntgroup签入
 * 
 * @param [in] TUP_UINT32 callid             <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR *group_number  <b>:</b> HuntGroup号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see  tup_call_huntgroup_signout
 **/
TUP_API TUP_RESULT tup_call_huntgroup_signin(IN TUP_UINT32 callid, IN const TUP_CHAR *group_number);


/**
 * @brief huntgroup签出
 * 
 * @param [in] TUP_UINT32 callid             <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR *group_number  <b>:</b> HuntGroup号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_huntgroup_signin
 **/
TUP_API TUP_RESULT tup_call_huntgroup_signout(IN TUP_UINT32 callid, IN const TUP_CHAR *group_number);


/**
 * @brief 获取HuntGroup状态
 * 
 * @param [in] TUP_UINT32 ulSipAccountID          <b>:</b> 账号ID
 * @param [out] CALL_S_CONTACT_STATUS *pstStatus  <b>:</b> 联系人状态
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_huntgroup_getstatus(IN TUP_UINT32 ulSipAccountID, OUT CALL_S_CONTACT_STATUS *pstStatus);


/**
 * @brief 播放paging组
 * 
 * @param [in] TUP_UINT32 ulGroupID  <b>:</b> Paging组ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see CALL_E_EVT_PAGING_INCOMING
 * @see tup_call_paging_end
 **/
TUP_API TUP_RESULT tup_call_paging_accept(IN TUP_UINT32 ulGroupID);


/**
 * @brief 结束paging组播放
 * 
 * @param [in] TUP_UINT32 ulGroupID  <b>:</b> Paging组ID
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see  CALL_E_EVT_PAGING_ENDED
 * @see  tup_call_paging_accept
 **/
TUP_API TUP_RESULT tup_call_paging_end(IN TUP_UINT32 ulGroupID);


/**
 * @brief 设置账号的用户名信息
 * 
 * @param [in] CALL_S_ACCOUNT_USER_NAME* user_name  <b>:</b> 账号用户名信息数组
 * @param [in] TUP_UINT32 data_num                  <b>:</b> 账号用户名信息数组个数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_user_name(IN CALL_S_ACCOUNT_USER_NAME* user_name, IN TUP_UINT32 data_num);


/**
 * @brief 设置是否支持H264 cabca编码方式
 * 
 * @param [in] TUP_UINT32 callid            <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_enable           <b>:</b> 是否开启
 * @param [in] CALL_E_MEDIATYPE media_type  <b>:</b> 媒体类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_enable_cabac_encode(IN TUP_UINT32 callid, IN TUP_BOOL is_enable, IN CALL_E_MEDIATYPE media_type);


/**
 * @brief 刷新uportal的token
 * 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 建议在用token请求服务失败时使用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_uportal_refresh_token();


/**
 * @brief 设置自动化测试功能
 * 
 * @param [in] TUP_BOOL bEnable  <b>:</b> 是否启用
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_enable_test_callback(IN TUP_BOOL bEnable);

/**
 * @brief  获取账号注册的服务器
 
 * 
 * @param [in] TUP_UINT32 ulSipAccountId  <b>:</b>账号id
 * @param [out] CALL_S_SERVER_CFG * pstServerInfo  <b>:</b> 服务器信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * @attention 注册成功才有返回值，否则服务器为空
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_registered_server(IN TUP_UINT32 ulSipAccountId, OUT CALL_S_SERVER_CFG *pstServerInfo);




#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_ADVANCED_INTERFACE_H__ */
/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
*
* vi: set expandtab ts=4 sw=4 tw=80:
*/


