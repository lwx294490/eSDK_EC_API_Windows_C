/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM子系统扩展业务功能接口头文件。 \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_EXTENDAPI_H_
#define _TUP_IM_EXTENDAPI_H_

#include "tup_im_extenddef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
 * @brief 发送文件传输 （异步接口）
 * @param [in]  arg 请求 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 发送文件传输完成后，收到开始文件传输的回调通知：IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY
 *          <br>接收方接收或拒绝文件传输后，发送方收到文件传输开始结果：IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY;
 *          <br>用户收到有新文件传输回调通知：IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY;
 *          <br>开始文件传输后，收到传输进度回调通知：IM_E_EVENT_IM_FILEPROCESS_NOTIFY;
 *          <br>完成传输后，收到停止回调通知：IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY	
 * @see tup_im_acceptp2pfile
 * @see tup_im_rejectp2pfile
 * @see tup_im_cancelp2pfile
 **/
TUP_API TUP_RESULT tup_im_sendp2pfile(IN const IM_S_SENDP2PFILE_ARG* arg);

/**
 * @brief 接收文件传输 （异步接口）
 * @param [in]  arg 请求 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 收到文件传输回调通知后，可以选择接收文件传输
 *          <br>用户收到有新文件传输回调通知：IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY;
 *          <br>开始文件传输后，收到传输进度回调通知：IM_E_EVENT_IM_FILEPROCESS_NOTIFY;
 *          <br>完成传输后，收到停止回调通知：IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY
 * @see tup_im_sendp2pfile
 * @see tup_im_rejectp2pfile
 * @see tup_im_cancelp2pfile
 **/
TUP_API TUP_RESULT tup_im_acceptp2pfile(IN const IM_S_ACCEPTP2PFILE_ARG* arg);

/**
 * @brief （接收方）拒绝文件传输 （异步接口）
 * @param [in]  arg 请求 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 收到文件传输回调通知后，可以选择拒绝接收文件传输
 *          <br>用户收到有新文件传输回调通知：IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY;
 * @see tup_im_sendp2pfile
 * @see tup_im_acceptp2pfile
 * @see tup_im_cancelp2pfile
 **/
TUP_API TUP_RESULT tup_im_rejectp2pfile(IN const IM_S_REJECTP2PFILE_ARG* arg);

/**
 * @brief （发送方）取消文件传输 （异步接口）
 * @param [in]  arg 请求 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 发送方发送文件但接收方并未接收时，发送方可以取消发送文件传输
 *			<br>取消后收到文件传输开始结果回调通知：IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY;
 *			<br>由于是取消文件传输，接着会收到停止文件传输结果回调通知：IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY
 * @see tup_im_sendp2pfile
 * @see tup_im_acceptp2pfile
 * @see tup_im_rejectp2pfile
 **/
TUP_API TUP_RESULT tup_im_cancelp2pfile(IN const IM_S_CANCELP2PFILE_ARG* arg);

/**
 * @brief 发送短信 （异步接口）
 * @param [in]  arg 请求 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 用户会收到短信发送结果，短信回执结果，收到新短信等短信消息，此类消息的回调通知：IM_E_EVENT_IM_SMS_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_sendsms(IN const IM_S_SENDSMS_ARG* arg);

/**
* @brief 群共享预上传文件 （同步接口）
* @param [in]  arg 预上传文件信息
* @param [out] ack 预上传文件ID
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention 预上传文件单个大小有限制
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_delete_result;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_pre_upload(IN const IM_S_GROUPFILE_PRE_UPLOAD_ARG* arg, OUT IM_S_GROUPFILE_PRE_UPLOAD_ACK* ack);

/**
* @brief 群共享上传文件结果通知服务器 （同步接口）
* @param [in]  arg 已上传到群共享的文件信息
* @param [out] ack 上传成功后的文件ID以及上传成功的时间戳
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention NA
* @see tup_im_groupfile_pre_upload;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_delete_result;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_report_upload_result(IN const IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ARG* arg, OUT IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ACK* ack);

/**
* @brief 群共享预删除文件 （同步接口）
* @param [in]  arg 需要删除的文件ID
* @param [out] ack 预删除的文件ID
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention NA
* @see tup_im_groupfile_pre_upload
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_delete_result;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_pre_delete(IN const IM_S_GROUPFILE_PRE_DELETE_ARG* arg, OUT IM_S_GROUPFILE_PRE_DELETE_ACK* ack);

/**
* @brief 群共享删除文件结果通知服务器 （同步接口）
* @param [in]  arg    已删除的群共享的文件信息
* @param [out] result 删除结果发送后服务器返回的响应结果
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention NA
* @see tup_im_groupfile_pre_upload
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_report_delete_result(IN const IM_S_GROUPFILE_REPORT_DELETE_RESULT_ARG* arg, OUT TUP_BOOL* result);

/**
* @brief 群共享已存在的共享文件查询 （同步接口）
* @param [in]  arg 查询请求
* @param [out] ack 查询响应
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention NA

* @see tup_im_groupfile_pre_upload
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_delete_result;
*/
TUP_API TUP_RESULT tup_im_groupfile_query(IN const IM_S_GROUPFILE_QUERY_ARG* arg, OUT IM_S_GROUPFILE_QUERY_ACK* ack);


/**
 * @brief 设置当前账户的联动状态 （同步接口）
 * 
 * @param [in] const IM_S_LINKAGE_STATUS* arg  <b>:</b> 联动状态
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_im_get_linkage_status
 **/
TUP_API TUP_RESULT tup_im_set_linkage_status(IN const IM_S_LINKAGE_STATUS* arg);


/**
 * @brief 获取当前账户的联动状态 （同步接口）
 * 
 * @param [out] IM_S_LINKAGE_STATUS* ack  <b>:</b> 联动状态
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_im_set_linkage_status
 **/
TUP_API TUP_RESULT tup_im_get_linkage_status(OUT IM_S_LINKAGE_STATUS* ack);

/**
 * @brief UI界面准备好后通知平台开始分发消息 （异步接口）
 * @param [in] isDispatch 是否开始分发消息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该接口已废弃
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setdispatchmessage(TUP_BOOL isDispatch);

/**
 * @brief 退出客户端时，还有同步接口请求在等待中。在独立线程中通知客户端自己不要再等待接口返回消息 （异步接口）
 * @param [in] 无
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该接口已废弃
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setcancelsendingmessage();

/**
 * @brief 发送心跳消息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该接口已废弃
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_sendheartbeat();

#ifdef __cplusplus
#if __cplusplus
}

#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#endif //_TUP_IM_EXTENDAPI_H_

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
