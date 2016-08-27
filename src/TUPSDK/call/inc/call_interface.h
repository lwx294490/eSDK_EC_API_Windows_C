/** 
* @file call_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP 呼叫子系统基础业务接口头文件。 \n
*/


/**
*
*  @{
*/


#ifndef __CALL_INTERFACE_H__
#define __CALL_INTERFACE_H__

#include "tup_def.h"
#include "call_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



/**
 * @brief 初始化呼叫业务组件
 * 
 * @param [in] TUP_VOID  
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 初始化前需要设置日志参数并启动日志
 * @see tup_call_uninit
 * @see tup_call_log_start
 **/
TUP_API TUP_RESULT tup_call_init(TUP_VOID);


/**
 * @brief 去初始化呼叫业务组件
 * 
 * @param [in] TUP_VOID  
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 程序退出前调用，调用前停止相关业务
 * @see tup_call_init
 **/
TUP_API TUP_RESULT tup_call_uninit(TUP_VOID);


/**
 * @brief 注册呼叫业务处理通知回调函数
 * 
 * @param [in] CALL_FN_CALLBACK_PTR callback_process_notify <b>:</b> 呼叫业务事件通知回调函数地址
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 初始化成功后调用，内部会创建一个对应的处理线程。
 *            <br>开发者要实现回调函数，若回调消息存在指针参数，则需深拷贝后使用，否则呼叫组件可能会释放，导致程序崩溃
 * @see tup_call_init
 **/
TUP_API TUP_RESULT tup_call_register_process_notifiy(IN CALL_FN_CALLBACK_PTR callback_process_notify);


/**
 * @brief 注册日志回调函数
 * 
 * @param [in] CALL_FN_DEBUG_CALLBACK_PTR callback_log   <b>:</b> 开发者自定义日志函数地址
 * @retval TUP_API TUP_VOID
 * 
 * @attention 此函数对外暂无作用，作为预留接口
 * @see tup_call_log_start
 **/
TUP_API TUP_VOID   tup_call_register_logfun(IN CALL_FN_DEBUG_CALLBACK_PTR callback_log);


/**
 * @brief SIP账号注册
 * 
 * @param [in] const TUP_CHAR* number     <b>:</b> 用户号码，最大长度32
 * @param [in] const TUP_CHAR* name       <b>:</b> 用户名，最大长度255
 * @param [in] const TUP_CHAR* password   <b>:</b> 密码，最大长度255
 * @retval TUP_API TUP_RESULT : 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 注册前需要完成注册参数设置
 * @see tup_call_deregister
 * @see tup_call_set_cfg
 **/
TUP_API TUP_RESULT tup_call_register(IN const TUP_CHAR* number, IN const TUP_CHAR* name, IN const TUP_CHAR* password);


/**
 * @brief SIP账号注销
 * 
 * @param [in] const TUP_CHAR* number   <b>:</b> 用户号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 对应的用户已注册
 * @see tup_call_register
 **/
TUP_API TUP_RESULT tup_call_deregister(IN const TUP_CHAR* number);


/**
 * @brief 发起一路普通VOIP呼叫
 * 
 * @param [out] TUP_UINT32 *callid             <b>:</b> 呼叫的id，标识唯一的呼叫
 * @param [in] CALL_E_CALL_TYPE call_type      <b>:</b> 呼叫类型
 * @param [in] const TUP_CHAR* callee_number   <b>:</b> 被叫号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_start_call(OUT TUP_UINT32 *callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief 发起一路匿名VOIP呼叫，废弃，由tup_call_start_anonymous_call替换
 * 
 * @param [out] TUP_UINT32 *callid             <b>:</b> 呼叫的id，标识唯一的呼叫
 * @param [in] const TUP_CHAR* callee_number   <b>:</b> 被叫号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 匿名呼叫只支持音频呼叫
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 * @see tup_call_start_anonymous_call
 **/
TUP_API TUP_RESULT tup_call_anonymous_call(OUT TUP_UINT32* callid, IN const TUP_CHAR* callee_number);

/**
 * @brief 发起一路匿名VOIP呼叫
 * 
 * @param [out] TUP_UINT32 *callid             <b>:</b> 呼叫的id，标识唯一的呼叫
 * @param [in] CALL_E_CALL_TYPE call_type      <b>:</b> 呼叫类型
 * @param [in] const TUP_CHAR* callee_number   <b>:</b> 被叫号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_start_anonymous_call(OUT TUP_UINT32* callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief 发起一路指定方式的VOIP呼叫，如CTD呼叫
 * 
 * @param [in] CALL_S_CALL_PARAMS* call_params  <b>:</b> 呼叫参数，其中ulCallId为输出参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 * @tup_call_ctd_get_list
 **/
TUP_API TUP_RESULT tup_call_start_call_ex(IN CALL_S_CALL_PARAMS* call_params);


/**
 * @brief 接听呼叫
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_video  <b>:</b> 是否接听视频呼叫
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_accept_call(IN TUP_UINT32 callid, IN TUP_BOOL is_video);


/**
 * @brief 结束和其他用户的通话或者来电
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_alerting_call
 * @see tup_call_accept_call
 **/
TUP_API TUP_RESULT tup_call_end_call(IN TUP_UINT32 callid);


/**
 * @brief 通知对方本方正在振铃
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_accept_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_alerting_call(IN TUP_UINT32 callid);


/**
 * @brief 获取呼叫状态信息
 * 
 * @param [out] CALL_S_STREAM_INFO* state  <b>:</b> 呼叫状态信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_callstatics(OUT CALL_S_STREAM_INFO* state);


/**
 * @brief 在通话中发送二次拨号信息
 * 
 * @param [in] TUP_UINT32 callid      <b>:</b> 呼叫ID
 * @param [in] CALL_E_DTMF_TONE tone  <b>:</b> DTMF信息值
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 通话中才可以发送
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_send_DTMF(IN TUP_UINT32 callid, IN CALL_E_DTMF_TONE tone);


/**
 * @brief 保持通话
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 处于通话状态才可以调用
 * @see tup_call_unhold_call
 **/
TUP_API TUP_RESULT tup_call_hold_call(IN TUP_UINT32 callid);


/**
 * @brief 取消保持通话(恢复通话)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 处于通话保持状态才可以调用
 * @see tup_call_hold_call
 **/
TUP_API TUP_RESULT tup_call_unhold_call(IN TUP_UINT32 callid);


/**
 * @brief 发起呼叫偏转请求
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* divert_number  <b>:</b> 偏转目的号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_divert_call(IN TUP_UINT32 callid, IN const TUP_CHAR* divert_number);


/**
 * @brief 发起呼叫盲转请求
 * 
 * @param [in] TUP_UINT32 callid               <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* transto_number  <b>:</b> 盲转目的号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_consult_transfer
 **/
TUP_API TUP_RESULT tup_call_blind_transfer(IN TUP_UINT32 callid, IN const TUP_CHAR* transto_number);


/**
 * @brief 发起呼叫咨询转/半咨询转请求
 * 
 * @param [in] TUP_UINT32 callid                <b>:</b> 待操作转移的呼叫ID
 * @param [in] const TUP_UINT32 transto_callid  <b>:</b> 操作转移的目的呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_blind_transfer
 **/
TUP_API TUP_RESULT tup_call_consult_transfer(IN TUP_UINT32 callid, IN const TUP_UINT32 transto_callid);


/**
 * @brief 设置视频窗口信息(窗口句柄)
 * 
 * @param [in] TUP_UINT32 Count                    <b>:</b> 窗口个数，一般为2
 * @param [in] const CALL_S_VIDEOWND_INFO* window  <b>:</b> 窗口数据 
 * @param [in] TUP_UINT32 callid                   <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 呼叫存在时，callid填写对应的有效值，呼叫不存在(未建立，主叫呼出时)，callid填写非法值
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_video_window(IN TUP_UINT32 count, IN const CALL_S_VIDEOWND_INFO * window, IN TUP_UINT32 callid);


/**
 * @brief 对方请求音频转视频呼叫时，本方选择同意或者拒绝
 * 
 * @param [in] TUP_UINT32 callid   <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_accept  <b>:</b> 是否同意
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_add_video
 * @see tup_call_del_video
 **/
TUP_API TUP_RESULT tup_call_reply_add_video(IN TUP_UINT32 callid, IN TUP_BOOL is_accept);



/**
 * @brief 发起音频转视频呼叫请求
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_reply_add_video
 * @see tup_call_del_video
 * @see tup_call_reply_del_video
 **/
TUP_API TUP_RESULT tup_call_add_video(IN TUP_UINT32 callid);


/**
 * @brief 发起视频转音频呼叫(删除视频)请求
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_add_video
 * @see tup_call_reply_add_video
 **/
TUP_API TUP_RESULT tup_call_del_video(IN TUP_UINT32 callid);


/**
 * @brief 创建并打开本地预览窗口
 * 
 * @param [in] TUP_UPTR handle   <b>:</b> 窗口句柄
 * @param [in] TUP_UINT32 index  <b>:</b> 摄相头索引
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_close_preview
 **/
TUP_API TUP_RESULT tup_call_open_preview(IN TUP_UPTR handle, IN TUP_UINT32 index);


/**
 * @brief 关闭并删除本地预览窗口
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_open_preview
 **/
TUP_API TUP_RESULT tup_call_close_preview(TUP_VOID);


/**
 * @brief 设置输出音量大小
 * 
 * @param [in] CALL_E_AO_DEV dev  <b>:</b> 设备类型
 * @param [in] TUP_UINT32 volume  <b>:</b> 音量大小，取值范围[0, 100]
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_mute_mic
 * @see tup_call_media_mute_video
 **/
TUP_API TUP_RESULT tup_call_media_set_speak_volume(IN CALL_E_AO_DEV dev, IN TUP_UINT32 volume);


/**
 * @brief 设置音频输出设备
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE route_dev  <b>:</b> 音频输入输出设备类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention IP Phone使用
 * @see tup_call_media_set_audio_indev
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_outdev(IN CALL_E_AUDDEV_ROUTE route_dev);


/**
 * @brief 设置音频输入设备
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE route_dev  <b>:</b> 音频输入输出设备类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention IP Phone使用
 * @see tup_call_media_set_audio_outdev
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_indev(IN CALL_E_AUDDEV_ROUTE route_dev);


/**
 * @brief 设置(或取消)扬声器静音
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_on     <b>:</b> 静音或取消静音  TRUE 为静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_mute_mic
 **/
TUP_API TUP_RESULT tup_call_media_mute_speak(IN TUP_UINT32 callid, IN TUP_BOOL is_on);


/**
 * @brief 设置(或取消)麦克风静音
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_on     <b>:</b> 是否静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_mute_video
 **/
TUP_API TUP_RESULT tup_call_media_mute_mic(IN TUP_UINT32 callid, IN TUP_BOOL is_on);


/**
 * @brief 设置(或取消)暂停视频设备输入(视频采集)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @param [in] TUP_BOOL is_on     <b>:</b> 是否暂停视频输入
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_mute_mic
 **/
TUP_API TUP_RESULT tup_call_media_mute_video(IN TUP_UINT32 callid, IN TUP_BOOL is_on);


/**
 * @brief 开启本地记录语音或视频(录*音或录*像)
 * 
 * @param [in] TUP_UINT32 callid           <b>:</b> 呼叫ID
 * @param [in] const TUP_CHAR* file_name   <b>:</b> 录音保存的文件，一般为*.wav文件
 * @param [in] TUP_BOOL is_video           <b>:</b> 是否为视频
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 暂不支持音视频混音录制
 * @see tup_call_media_stoprecord
 **/
TUP_API TUP_RESULT tup_call_media_startrecord(IN TUP_UINT32 callid, IN const TUP_CHAR* file_name, IN TUP_BOOL is_video);


/**
 * @brief 停止本地记录语音或视频(录*音或录*像)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_startrecord
 **/
TUP_API TUP_RESULT tup_call_media_stoprecord(IN TUP_UINT32 callid);


/**
 * @brief 播放本地音频文件(振铃音、回铃音、拨号(提示)音、DTMF音、忙碌提示音和本地按健音等) 
 * 
 * @param [in] TUP_UINT32 loops           <b>:</b> 循环次数（0表示循环播放）
 * @param [in] const TUP_CHAR* play_file  <b>:</b> 播放铃声文件名播放铃音路径（目前支持wav格式）
 * @param [out] TUP_INT32* play_handle    <b>:</b> 播放句柄(用于停止播放时的参数)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention WAV文件，目前支持PCMA、PCMU、G.729格式或采样精度为8或16位、采样率8k～48K的PCM数据，支持双声道
 * @see tup_call_media_startTcplay
 * @see tup_call_media_startLocalplay
 * @see tup_call_media_stopplay
 **/
TUP_API TUP_RESULT tup_call_media_startplay(IN TUP_UINT32 loops, IN const TUP_CHAR* play_file, OUT TUP_INT32* play_handle);


/**
 * @brief 播放音频文件
 * 
 * @param [in] CALL_S_MEDIA_PLAY_PARAM* media_play_param  <b>:</b> 播放参数，包含循环次数，播放文件路径，媒体类型，播放模式等信息
 * @param [out] TUP_INT32* play_handle                    <b>:</b> 播放句柄(用于停止播放时的参数)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 可用于振铃音、回铃音、拨号(提示)音、DTMF音、忙碌提示音、本地按健音、TC模式铃音、TC模式本地铃音和其他本地媒体等
 * @see tup_call_media_startplay 
 * @see tup_call_media_stopplay
 **/
TUP_API TUP_RESULT tup_call_media_startplay_ex(IN CALL_S_MEDIA_PLAY_PARAM* media_play_param, OUT TUP_INT32* play_handle);


/**
 * @brief 停止铃音播放
 * 
 * @param [in] TUP_INT32 play_handle  <b>:</b> 播放句柄
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_media_startplay
 * @see tup_call_media_startTcplay
 * @see tup_call_media_startLocalplay
 **/
TUP_API TUP_RESULT tup_call_media_stopplay(IN TUP_INT32 play_handle);


/**
 * @brief 设置使用的麦克风设备序号
 * 
 * @param [in] TUP_UINT32 index  <b>:</b> 麦克风设备序号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 设备序号一般在系统初始化后通过tup_call_media_get_devices获取，用于PC
 * @see tup_call_media_get_mic_index
 * @see tup_call_media_get_devices
 **/
TUP_API TUP_RESULT tup_call_media_set_mic_index(IN TUP_UINT32 index);


/**
 * @brief 设置使用的扬声器设备序号
 * 
 * @param [in] TUP_UINT32 index  <b>:</b> 扬声器设备序号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 设备序号一般在系统初始化后通过tup_call_media_get_devices获取，用于PC
 * @see tup_call_media_get_speak_index
 * @see tup_call_media_get_devices
 **/
TUP_API TUP_RESULT tup_call_media_set_speak_index(IN TUP_UINT32 index);


/**
 * @brief 设置使用的视频设备序号
 * 
 * @param [in] TUP_UINT32 index  <b>:</b> 视频设备序号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 设备序号一般在系统初始化后通过tup_call_media_get_devices获取
 * @see tup_call_media_get_video_index
 * @see tup_call_media_get_devices
 **/
TUP_API TUP_RESULT tup_call_media_set_video_index(IN TUP_UINT32 index);


/**
 * @brief 获取使用的麦克风设备序号
 * 
 * @param [out] TUP_UINT32* index  <b>:</b> 麦克风设备序号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于接口测试或产品调试，实际产品业务场景中无需调用
 * @see tup_call_media_set_mic_index
 **/
TUP_API TUP_RESULT tup_call_media_get_mic_index(OUT TUP_UINT32* index);


/**
 * @brief 获取使用的扬声器设备序号
 * 
 * @param [out] TUP_UINT32* index  <b>:</b> 扬声器设备序号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于接口测试或产品调试，实际产品业务场景中无需调用
 * @see tup_call_media_set_speak_index
 **/
TUP_API TUP_RESULT tup_call_media_get_speak_index(OUT TUP_UINT32* index);


/**
 * @brief 获取使用的视频设备序号
 * 
 * @param [out] TUP_UINT32* index  <b>:</b> 视频设备序号
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于接口测试或产品调试，实际产品业务场景中无需调用
 * @see tup_call_media_set_video_index
 **/
TUP_API TUP_RESULT tup_call_media_get_video_index(OUT TUP_UINT32* index);


/**
 * @brief 设置输入音量增益
 * 
 * @param [in] TUP_FLOAT in_gain  <b>:</b> 增益，取值范围 [0,1)增益衰减，1不增大也不衰减，(1,10]增益放大
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 适用场景:TC模式音量过小，需要输入/输出增益
 * @see tup_call_media_get_audio_ingain
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_ingain(IN TUP_FLOAT in_gain);


/**
 * @brief 获取输入音量增益
 * 
 * @param [out] TUP_FLOAT* in_gain  <b>:</b> 增益，[0,1)增益衰减，1不增大也不衰减，(1,10]增益放大
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 适用场景:TC模式音量过小，需要输入/输出增益
 * @see tup_call_media_set_audio_ingain
 **/
TUP_API TUP_RESULT tup_call_media_get_audio_ingain(OUT TUP_FLOAT* in_gain);


/**
 * @brief 设置输出音量增益
 * 
 * @param [in] TUP_FLOAT out_gain  <b>:</b> 增益，取值范围 [0,1)增益衰减，1不增大也不衰减，(1,10]增益放大
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 适用场景:TC模式音量过小，需要输入/输出增益
 * @see tup_call_media_get_audio_outgain
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_outgain(IN TUP_FLOAT out_gain);


/**
 * @brief 获取输出音量增益
 * 
 * @param [out] TUP_FLOAT* pfOutGain  <b>:</b> 增益，[0,1)增益衰减，1不增大也不衰减，(1,10]增益放大
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 适用场景:TC模式音量过小，需要输入/输出增益
 * @see tup_call_media_set_audio_outgain
 **/
TUP_API TUP_RESULT tup_call_media_get_audio_outgain(OUT TUP_FLOAT* out_gain);


/**
 * @brief 获取音频视频设备列表
 * 
 * @param [in/out] TUP_UINT32* num               <b>:</b> 输入时表示上层分配的设备个数，输出时表示获取到得设备的个数
 * @param [in] CALL_S_DEVICEINFO* device_info    <b>:</b> 设备信息数组指针
 * @param [in] CALL_E_DEVICE_TYPE device_type    <b>:</b> 设备类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_media_get_devices(IO TUP_UINT32* num, IN CALL_S_DEVICEINFO* device_info, IN CALL_E_DEVICE_TYPE device_type);


/**
 * @brief 登记呼叫IPT业务
 * 
 * @param [in] CALL_E_SERVICE_CALL_TYPE type  <b>:</b> 业务类型
 * @param [in] void* data                     <b>:</b> 登记业务需要的参数数据，当前仅前转类业务需要(前转的目的号码，字符串)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 各类呼叫IPT业务对应的权限和特征码已完成配置
 * @see tagCALL_S_SERVICE_RIGHT_CFG
 **/
TUP_API TUP_RESULT tup_call_set_IPTservice(IN CALL_E_SERVICE_CALL_TYPE type, IN void* data);


/**
 * @brief 获取ctd号码列表
 * 
 * @param [in] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_start_call_ex
 **/
TUP_API TUP_RESULT tup_call_ctd_get_list(TUP_VOID);


/**
 * @brief 设置呼叫业务参数
 * 
 * @param [in] TUP_UINT32 cfgid  <b>:</b> 参数ID,由call_def.h定义，前缀为CALL_D_CFG_
 * @param [in] TUP_VOID * val    <b>:</b> 参数值，根据配置的参数ID确定数据类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 1 实现最基本的呼叫业务，必须调用此接口分别设置:
             <br>CALL_D_CFG_ENV_PRODUCT_TYPE（产品类型）、
             <br>CALL_D_CFG_NET_NETADDRESS（本地地址）、
             <br>CALL_D_CFG_SERVER_REG_PRIMARY（sip注册服务器）或 CALL_D_CFG_SERVER_PROXY_PRIMARY（sip代理服务器）
             <br>根据需要调用此接口分别设置:
             <br>CALL_D_CFG_SIP_TRANS_MODE（SIP传输模式）、
             <br> 
             <br>2 与IM系统配合使用时，建议该接口的入参直接通过tup_im_getserviceprofile接口获取。
 * @see tup_call_get_cfg
 **/
TUP_API TUP_RESULT tup_call_set_cfg(IN TUP_UINT32 cfgid, IN TUP_VOID * val);


/**
 * @brief 获取呼叫业务参数
 * 
 * @param [in] TUP_UINT32 cfgid  <b>:</b> 参数ID,由call_def.h定义，前缀为CALL_D_CFG_
 * @param [out] TUP_VOID* val    <b>:</b> 参数值，根据配置的参数ID确定数据类型
 * @param [in] TUP_UINT32 size   <b>:</b> 参数值大小，根据配置的参数ID确定数据类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_cfg
 **/
TUP_API TUP_RESULT tup_call_get_cfg(IN TUP_UINT32 cfgid, OUT TUP_VOID* val,  IN TUP_UINT32 size);



/**
 * @brief 使能音频引擎
 * 
 * @param [in] TUP_BOOL enable  <b>:</b> 状态参数，0表示禁用，非0表示使能，默认使能
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 目前仅用于使能音频引擎设备刷新
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_media_enable_audioengine(IN TUP_BOOL enable);



/**
 * @brief 设置联动号码
 * 
 * @param [in] TUP_UINT32 accountid        <b>:</b> 账号ID
 * @param [in] TUP_BOOL right              <b>:</b> 联动权限
 * @param [in] const char* linkage_number  <b>:</b> 联动的目标话机号码，最大长度32
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 在开启联动前调用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_joint_setting(IN TUP_UINT32 accountid, IN TUP_BOOL right, IN const char* linkage_number);


/**
 * @brief 开启联动
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 开启前需完成联动号码设置
 * @see tup_call_joint_stop
 **/
TUP_API TUP_RESULT tup_call_joint_start(TUP_VOID);


/**
 * @brief 关闭联动
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_joint_start
 **/
TUP_API TUP_RESULT tup_call_joint_stop(TUP_VOID);


/**
 * @brief 联动通话Desktop与IP Phone切换
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_joint_switch(TUP_VOID);


/**
 * @brief 通话转会议
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_joint_conf_result
 **/
TUP_API TUP_RESULT tup_call_joint_uptoconference(TUP_VOID);


/**
 * @brief 向联动话机通知创会结果
 * 
 * @param [in] TUP_UINT32 result  <b>:</b> 创会结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_joint_uptoconference
 **/
TUP_API TUP_RESULT tup_call_joint_conf_result(IN TUP_UINT32 result);


/**
 * @brief 新建会议
 * 
 * @param [out] TUP_UINT32 *confid        <b>:</b> 会议(控制块)ID
 * @param [out] TUP_UINT32 *callid        <b>:</b> 呼叫(控制块)ID
 * @param [in] const TUP_CHAR *groupuri   <b>:</b> 群组URI，如果是群组会议时填写
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_create(OUT TUP_UINT32 *confid, OUT TUP_UINT32 *callid, IN const TUP_CHAR *groupuri);


/**
 * @brief 邀请与会者
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> 会议(控制块)ID
 * @param [in] TUP_UINT32 count        <b>:</b> 与会者个数
 * @param [in] const TUP_CHAR *number  <b>:</b> 与会者号码列表(数组地址)
 * @param [in] TUP_UINT32 persize      <b>:</b> 存储与会者号码的BUF长度(数组成员长度)
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此操作只有会议主席才能调用
 * @see tup_call_serverconf_kick_attendee
 **/
TUP_API TUP_RESULT tup_call_serverconf_add_attendee(IN TUP_UINT32 confid, IN TUP_UINT32 count, IN const TUP_CHAR *number, IN TUP_UINT32 persize);


/**
 * @brief 删除与会者
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> 会议(控制块)ID
 * @param [in] const TUP_CHAR* number  <b>:</b> 与会者号码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此操作只有会议主席才能调用
 * @see tup_call_serverconf_add_attendee
 **/
TUP_API TUP_RESULT tup_call_serverconf_kick_attendee(IN TUP_UINT32 confid, IN const TUP_CHAR* number);


/**
 * @brief 修改与会者发言权限
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> 会议(控制块)ID
 * @param [in] const TUP_CHAR* number  <b>:</b> 与会者号码
 * @param [in] TUP_UINT32 right        <b>:</b> 是否允许发言
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此操作只有会议主席才能调用
 * @see tup_call_serverconf_mute
 **/
TUP_API TUP_RESULT tup_call_serverconf_modify_right(IN TUP_UINT32 confid, IN const TUP_CHAR* number, IN TUP_UINT32 right);


/**
 * @brief 设置会场静音
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @param [in] TUP_BOOL is_mute   <b>:</b> 是否静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此操作只有会议主席才能调用，若调车，除主席外，其他人只听
 * @see tup_call_serverconf_modify_right
 **/
TUP_API TUP_RESULT tup_call_serverconf_mute(IN TUP_UINT32 confid, IN TUP_BOOL is_mute);


/**
 * @brief 设置会场锁定(不允许加入会议)
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @param [in] TUP_BOOL locked    <b>:</b> 是否锁定
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此操作只有会议主席才能调用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_lock(IN TUP_UINT32 confid, IN TUP_BOOL locked);


/**
 * @brief 退出会议
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若主席退出会议，会议主席权限不转移(即没有主席，不支持进行主席相关会控，待所有与会人退出后，会议结束)
 * @see tup_call_serverconf_end
 **/
TUP_API TUP_RESULT tup_call_serverconf_leave(IN TUP_UINT32 confid);


/**
 * @brief 结束会议
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此操作只有会议主席才能调用
 * @see tup_call_serverconf_leave
 **/
TUP_API TUP_RESULT tup_call_serverconf_end(IN TUP_UINT32 confid);


/**
 * @brief 接听会议来电
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_accept(IN TUP_UINT32 confid); 


/**
 * @brief 保持会议
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_unhold
 **/
TUP_API TUP_RESULT tup_call_serverconf_hold(IN TUP_UINT32 confid); 


/**
 * @brief 取消保持会议
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_hold
 **/
TUP_API TUP_RESULT tup_call_serverconf_unhold(IN TUP_UINT32 confid);


/**
 * @brief 两方通话转会议(Refer流程)
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @param [in] TUP_UINT32 callid  <b>:</b> 待转为会议的呼叫(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 调用此接口需要先调用tup_call_serverconf_create完成会议创建
 * @see tup_call_serverconf_create
 * @see tup_call_serverconf_transferto_conf_non_refer
 **/
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf(IN TUP_UINT32 confid, IN TUP_UINT32 callid);


/**
 * @brief 两方通话转会议(非Refer流程)
 * 
 * @param [in] TUP_UINT32 callid         <b>:</b> 待转为会议的呼叫(控制块)ID
 * @param [out] TUP_UINT32 *confid       <b>:</b> 会议(控制块)ID
 * @param [in] const TUP_CHAR *groupuri  <b>:</b> 群组URI，如果是群组会议时填写
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 不建议使用
 * @see tup_call_serverconf_transferto_conf
 **/
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf_non_refer(IN TUP_UINT32 callid, OUT TUP_UINT32 *confid, IN const TUP_CHAR *groupuri);


/**
 * @brief 语音会议转数据会议
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> 会议(控制块)ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_serverconf_p2p_transferto_dataconf
 **/
TUP_API TUP_RESULT tup_call_serverconf_transferto_dataconf(IN TUP_UINT32 confid);


/**
 * @brief 点对点直接转多媒体会议
 * 
 * @param [out] TUP_UINT32* confid        <b>:</b> 转成多媒体会议后对应的会议(控制块)ID
 * @param [out] TUP_UINT32* callid        <b>:</b> 转成多媒体会议后对应的呼叫(控制块)ID
 * @param [in] TUP_UINT32 p2p_callid      <b>:</b> 原P2P呼叫(控制块)ID
 * @param [in] const TUP_CHAR* groupuri   <b>:</b> 群组URI，如果是群组会议时填写
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 转会议后，原点对点的音频处于保持。TODO
 * @see tup_call_serverconf_transferto_dataconf
 **/
TUP_API TUP_RESULT tup_call_serverconf_p2p_transferto_dataconf(OUT TUP_UINT32* confid, OUT TUP_UINT32* callid, IN TUP_UINT32 p2p_callid, IN const TUP_CHAR* groupuri);


/**
 * @brief 接入预约会议
 * 
 * @param [out] TUP_UINT32 *callid         <b>:</b> 接入预约会议后，对应的呼叫ID
 * @param [in] const TUP_CHAR *accesscode  <b>:</b> 会议接入码
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_access_reservedconf(OUT TUP_UINT32 *callid, IN const TUP_CHAR *accesscode);


/**
 * @brief 设置CALL组件日志参数，启动日志
 * 
 * @param [in] TUP_INT32 log_level        <b>:</b> 日志级别，取值:枚举类CALL_E_LOG_LEVEL
 * @param [in] TUP_INT32 max_size         <b>:</b> 每个日志文件的最大值，单位: KB，最大值为TUP_INT32所能取到的最大值
 * @param [in] TUP_INT32 file_count       <b>:</b> 日志文件个数，最大值为TUP_INT32所能取到的最大值 
 * @param [in] const TUP_CHAR* log_path   <b>:</b> 日志存放路径 
 * @retval TUP_API TUP_VOID <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 必须在初始化之前调用
 * @see tup_call_log_stop
 **/
TUP_API TUP_VOID tup_call_log_start(IN TUP_INT32 log_level, IN TUP_INT32 max_size, IN TUP_INT32 file_count, IN const TUP_CHAR* log_path);


/**
 * @brief 设置CALL组件HME模块日志参数
 * 
 * @param [in] TUP_INT32 audio_log_level   <b>:</b> HME-Audio 日志级别(设置值来源:枚举类CALL_E_LOG_LEVEL)
 * @param [in] TUP_INT32 audio_max_size    <b>:</b> HME-Audio 日志阀值(单位为M, 建议设置为10, 最小1M, 最大100M; 默认为1M)
 * @param [in] TUP_INT32 video_log_level   <b>:</b> HME-Video 日志级别(设置值来源:枚举类CALL_E_LOG_LEVEL)
 * @param [in] TUP_INT32 video_max_size    <b>:</b> HME-Video 日志阀值(单位M, 建议设置为50, 最小1M, 最大512M; 默认为5M)
 * @retval TUP_API TUP_VOID <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于单独设置媒体引擎的日志参数，不调用则使用默认值
 * @see NA
 **/
TUP_API TUP_VOID tup_call_hme_log_info(IN TUP_INT32 audio_log_level, 
            IN TUP_INT32 audio_max_size, IN TUP_INT32 video_log_level, IN TUP_INT32 video_max_size);


/**
 * @brief 停止CALL组件日志
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_VOID <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_log_start
 **/
TUP_API TUP_VOID tup_call_log_stop(TUP_VOID);


/**
 * @brief 根据呼叫子系统错误码获取错误描述
 * 
 * @param [in] TUP_UINT32 errornum  <b>:</b> 错误码，取值tagCALL_E_ERR_ID
 * @retval TUP_API const TUP_CHAR*  <b>:</b> 成功返回错误描述字串，失败NULL
 * 
 * @attention 暂只支持呼叫子系统定义的错误描述
 * @see NA
 **/
TUP_API const TUP_CHAR* tup_call_get_err_description(IN TUP_UINT32 errornum);


/**
 * @brief 获取协商后辅流编码的最大分辨率
 * 
 * @param [in]  TUP_UINT32 callid           <b>:</b> 呼叫(控制块)ID
 * @param [out] TUP_UINT32 *max_frame_size  <b>:</b> 最大分辨率
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_data_maxframesize(IN TUP_UINT32 callid, OUT TUP_UINT32 *max_frame_size);


/**
 * @brief 开启IP呼叫功能
 * 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_disable_ipaddr_call
 **/
TUP_API TUP_RESULT tup_call_enable_ipaddr_call();


/**
 * @brief 关闭IP呼叫功能
 * 
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_enable_ipaddr_call
 **/
TUP_API TUP_RESULT tup_call_disable_ipaddr_call();


/**
 * @brief 视频控制
 * 
 * @param [in] CALL_S_VIDEOCONTROL *video_control  <b>:</b> 视频控制参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_data_control
 **/
TUP_API TUP_RESULT tup_call_video_control(IN CALL_S_VIDEOCONTROL *video_control);


/**
 * @brief 辅流(数据)控制
 * 
 * @param [in] CALL_S_VIDEOCONTROL *data_control  <b>:</b> 辅流(数据)控制参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_video_control
 **/
TUP_API TUP_RESULT tup_call_data_control(IN CALL_S_VIDEOCONTROL *data_control);


/**
 * @brief 设置移动音频路由设备
 * 
 * @param [in] CALL_E_MOBILE_AUIDO_ROUTE route  <b>:</b> 移动音频路由设备类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于移动设备
 * @see tup_call_get_mobile_audio_route
 **/
TUP_API TUP_RESULT tup_call_set_mobile_audio_route(IN CALL_E_MOBILE_AUIDO_ROUTE route);


/**
 * @brief 获取移动音频路由设备
 * 
 * @param [out] CALL_E_MOBILE_AUIDO_ROUTE *route  <b>:</b> 移动音频路由设备类型
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 用于移动设备
 * @see tup_call_set_mobile_audio_route
 **/
TUP_API TUP_RESULT tup_call_get_mobile_audio_route(OUT CALL_E_MOBILE_AUIDO_ROUTE *route);


/**
 * @brief 启动辅流
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_stop_data
 **/
TUP_API TUP_RESULT tup_call_start_data(IN TUP_UINT32 callid);


/**
 * @brief 停止辅流
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> 呼叫ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_stop_data
 **/
TUP_API TUP_RESULT tup_call_stop_data(IN TUP_UINT32 callid);


/**
 * @brief 设置视频方向(横竖屏)
 * 
 * @param [in] TUP_UINT32 callid                        <b>:</b> 呼叫ID
 * @param [in] TUP_UINT32 index                         <b>:</b> 设备(摄相头)索引
 * @param [in] const CALL_S_VIDEO_ORIENT *video_orient  <b>:</b> 视频方向(横竖屏)参数
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 主要用于移动设备
 * @see tup_call_set_video_render
 **/
TUP_API TUP_RESULT tup_call_set_video_orient(IN TUP_UINT32 callid, IN TUP_UINT32 index, IN const CALL_S_VIDEO_ORIENT *video_orient);


/**
 * @brief 设置视频显示窗口属性
 * 
 * @param [in] TUP_UINT32 callid                        <b>:</b> 呼叫ID
 * @param [in] const CALL_S_VIDEO_RENDER_INFO* render   <b>:</b> 视频显示窗口属性
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_video_orient
 **/
TUP_API TUP_RESULT tup_call_set_video_render(IN TUP_UINT32 callid, IN const CALL_S_VIDEO_RENDER_INFO* render);


/**
 * @brief 设置摄像头采集方向
 * 
 * @param [in] TUP_UINT32 callid            <b>:</b> 呼叫ID
 * @param [in] TUP_UINT32 capture_index     <b>:</b> 采集设备(摄像头)索引
 * @param [in] TUP_UINT32 capture_rotation  <b>:</b> 摄像头采集角度 {0,1,2,3} 仅对移动平台有效，默认为0
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_display_rotation
 **/
TUP_API TUP_RESULT tup_call_set_capture_rotation(IN TUP_UINT32 callid, IN TUP_UINT32 capture_index, IN TUP_UINT32 capture_rotation);


/**
 * @brief 设置窗口显示方向
 * 
 * @param [in] TUP_UINT32 callid            <b>:</b> 呼叫ID
 * @param [in] TUP_UINT32 render_type       <b>:</b> 视频窗口类型，取值CALL_E_VIDEOWND_TYPE
 * @param [in] TUP_UINT32 rotation          <b>:</b> 视频显示方向
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see tup_call_set_capture_rotation
 **/
TUP_API TUP_RESULT tup_call_set_display_rotation(IN TUP_UINT32 callid, IN TUP_UINT32 render_type, IN TUP_UINT32 rotation);


/**
 * @brief 设置摄像头图片
 * 
 * @param [in] TUP_UINT32 callid    <b>:</b> 呼叫ID
 * @param [in] TUP_CHAR *file_name  <b>:</b> 文件名
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_video_capture_file(IN TUP_UINT32 callid, IN TUP_CHAR *file_name);


/**
 * @brief 设置H.264视频B帧开关
 * 
 * @param [in] TUP_BOOL is_enable  <b>:</b> 是否开启
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_vpuorder_enable(IN TUP_BOOL is_enable);


/**
 * @brief 发送会话内INFO消息
 * 
 * @param [in] TUP_UINT32 callid 呼叫ID
 * @param [in] CALL_S_DIALOG_INFO *dialog_info 会话内INFO消息结构 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 产品在需要时使用此函数发送定制的SIP INFO消息，以实现特定业务
 * @see NA
 **/ 
TUP_API TUP_RESULT tup_call_send_diaglog_info(IN TUP_UINT32 callid, IN CALL_S_DIALOG_INFO *dialog_info);


/**
 * @brief 连接华为TC
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 初始化后注册前调用，尝试连接TC或IE云，若返回成功，则处于云环境
 * @see tup_call_disconnect_tc
 **/
TUP_API TUP_RESULT tup_call_connect_tc(TUP_VOID);


/**
 * @brief 断开华为TC的连接
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 华为云TC设备使用
 * @see tup_call_connect_tc
 **/
TUP_API TUP_RESULT tup_call_disconnect_tc(TUP_VOID);


/**
 * @brief 获取TC的IP地址
 * 
 * @param [out] CALL_S_IF_INFO* inetaddr  <b>:</b> IP地址信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see 华为云TC设备使用
 **/
TUP_API TUP_RESULT tup_call_get_tc_ipaddr(OUT CALL_S_IF_INFO* inetaddr);


/**
 * @brief 获取音频模式
 * 
 * @param [out] TUP_UINT32* auido_mode  <b>:</b> 音频模式 @enum tagCALL_E_AUDIO_MODE
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 华为云TC设备使用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_audio_mode(OUT TUP_UINT32* auido_mode);


/**
 * @brief 获取TC日志
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 华为云TC设备使用
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_tc_log(TUP_VOID);


/**
 * @brief 设置TC侧MIC静音
 * 
 * @param [out] TUP_INT32 is_mute  <b>:</b> 是否静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 华为云TC设备使用
 * @see tup_call_set_spkdev_mute
 **/
TUP_API TUP_RESULT tup_call_set_micdev_mute(OUT TUP_INT32 is_mute);


/**
 * @brief 设置TC侧杨声器静音
 * 
 * @param [in] TUP_INT32 is_mute  <b>:</b> 是否静音
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 华为云TC设备使用
 * @see tup_call_set_micdev_mute
 **/
TUP_API TUP_RESULT tup_call_set_spkdev_mute(IN TUP_INT32 is_mute);


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_INTERFACE_H__ */

/** @}*/

/*
* History: \n
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/


