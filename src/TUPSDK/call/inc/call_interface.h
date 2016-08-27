/** 
* @file call_def.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP ������ϵͳ����ҵ��ӿ�ͷ�ļ��� \n
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
 * @brief ��ʼ������ҵ�����
 * 
 * @param [in] TUP_VOID  
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��ʼ��ǰ��Ҫ������־������������־
 * @see tup_call_uninit
 * @see tup_call_log_start
 **/
TUP_API TUP_RESULT tup_call_init(TUP_VOID);


/**
 * @brief ȥ��ʼ������ҵ�����
 * 
 * @param [in] TUP_VOID  
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����˳�ǰ���ã�����ǰֹͣ���ҵ��
 * @see tup_call_init
 **/
TUP_API TUP_RESULT tup_call_uninit(TUP_VOID);


/**
 * @brief ע�����ҵ����֪ͨ�ص�����
 * 
 * @param [in] CALL_FN_CALLBACK_PTR callback_process_notify <b>:</b> ����ҵ���¼�֪ͨ�ص�������ַ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��ʼ���ɹ�����ã��ڲ��ᴴ��һ����Ӧ�Ĵ����̡߳�
 *            <br>������Ҫʵ�ֻص����������ص���Ϣ����ָ����������������ʹ�ã��������������ܻ��ͷţ����³������
 * @see tup_call_init
 **/
TUP_API TUP_RESULT tup_call_register_process_notifiy(IN CALL_FN_CALLBACK_PTR callback_process_notify);


/**
 * @brief ע����־�ص�����
 * 
 * @param [in] CALL_FN_DEBUG_CALLBACK_PTR callback_log   <b>:</b> �������Զ�����־������ַ
 * @retval TUP_API TUP_VOID
 * 
 * @attention �˺��������������ã���ΪԤ���ӿ�
 * @see tup_call_log_start
 **/
TUP_API TUP_VOID   tup_call_register_logfun(IN CALL_FN_DEBUG_CALLBACK_PTR callback_log);


/**
 * @brief SIP�˺�ע��
 * 
 * @param [in] const TUP_CHAR* number     <b>:</b> �û����룬��󳤶�32
 * @param [in] const TUP_CHAR* name       <b>:</b> �û�������󳤶�255
 * @param [in] const TUP_CHAR* password   <b>:</b> ���룬��󳤶�255
 * @retval TUP_API TUP_RESULT : �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ע��ǰ��Ҫ���ע���������
 * @see tup_call_deregister
 * @see tup_call_set_cfg
 **/
TUP_API TUP_RESULT tup_call_register(IN const TUP_CHAR* number, IN const TUP_CHAR* name, IN const TUP_CHAR* password);


/**
 * @brief SIP�˺�ע��
 * 
 * @param [in] const TUP_CHAR* number   <b>:</b> �û����룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ӧ���û���ע��
 * @see tup_call_register
 **/
TUP_API TUP_RESULT tup_call_deregister(IN const TUP_CHAR* number);


/**
 * @brief ����һ·��ͨVOIP����
 * 
 * @param [out] TUP_UINT32 *callid             <b>:</b> ���е�id����ʶΨһ�ĺ���
 * @param [in] CALL_E_CALL_TYPE call_type      <b>:</b> ��������
 * @param [in] const TUP_CHAR* callee_number   <b>:</b> ���к��룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_start_call(OUT TUP_UINT32 *callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief ����һ·����VOIP���У���������tup_call_start_anonymous_call�滻
 * 
 * @param [out] TUP_UINT32 *callid             <b>:</b> ���е�id����ʶΨһ�ĺ���
 * @param [in] const TUP_CHAR* callee_number   <b>:</b> ���к��룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��������ֻ֧����Ƶ����
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 * @see tup_call_start_anonymous_call
 **/
TUP_API TUP_RESULT tup_call_anonymous_call(OUT TUP_UINT32* callid, IN const TUP_CHAR* callee_number);

/**
 * @brief ����һ·����VOIP����
 * 
 * @param [out] TUP_UINT32 *callid             <b>:</b> ���е�id����ʶΨһ�ĺ���
 * @param [in] CALL_E_CALL_TYPE call_type      <b>:</b> ��������
 * @param [in] const TUP_CHAR* callee_number   <b>:</b> ���к��룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_start_anonymous_call(OUT TUP_UINT32* callid, IN CALL_E_CALL_TYPE call_type, IN const TUP_CHAR* callee_number);


/**
 * @brief ����һ·ָ����ʽ��VOIP���У���CTD����
 * 
 * @param [in] CALL_S_CALL_PARAMS* call_params  <b>:</b> ���в���������ulCallIdΪ�������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_accept_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 * @tup_call_ctd_get_list
 **/
TUP_API TUP_RESULT tup_call_start_call_ex(IN CALL_S_CALL_PARAMS* call_params);


/**
 * @brief ��������
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @param [in] TUP_BOOL is_video  <b>:</b> �Ƿ������Ƶ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_alerting_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_accept_call(IN TUP_UINT32 callid, IN TUP_BOOL is_video);


/**
 * @brief �����������û���ͨ����������
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_alerting_call
 * @see tup_call_accept_call
 **/
TUP_API TUP_RESULT tup_call_end_call(IN TUP_UINT32 callid);


/**
 * @brief ֪ͨ�Է�������������
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_start_call
 * @see tup_call_accept_call
 * @see tup_call_end_call
 **/
TUP_API TUP_RESULT tup_call_alerting_call(IN TUP_UINT32 callid);


/**
 * @brief ��ȡ����״̬��Ϣ
 * 
 * @param [out] CALL_S_STREAM_INFO* state  <b>:</b> ����״̬��Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_callstatics(OUT CALL_S_STREAM_INFO* state);


/**
 * @brief ��ͨ���з��Ͷ��β�����Ϣ
 * 
 * @param [in] TUP_UINT32 callid      <b>:</b> ����ID
 * @param [in] CALL_E_DTMF_TONE tone  <b>:</b> DTMF��Ϣֵ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ͨ���вſ��Է���
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_send_DTMF(IN TUP_UINT32 callid, IN CALL_E_DTMF_TONE tone);


/**
 * @brief ����ͨ��
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ����ͨ��״̬�ſ��Ե���
 * @see tup_call_unhold_call
 **/
TUP_API TUP_RESULT tup_call_hold_call(IN TUP_UINT32 callid);


/**
 * @brief ȡ������ͨ��(�ָ�ͨ��)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ����ͨ������״̬�ſ��Ե���
 * @see tup_call_hold_call
 **/
TUP_API TUP_RESULT tup_call_unhold_call(IN TUP_UINT32 callid);


/**
 * @brief �������ƫת����
 * 
 * @param [in] TUP_UINT32 callid              <b>:</b> ����ID
 * @param [in] const TUP_CHAR* divert_number  <b>:</b> ƫתĿ�ĺ��룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_divert_call(IN TUP_UINT32 callid, IN const TUP_CHAR* divert_number);


/**
 * @brief �������äת����
 * 
 * @param [in] TUP_UINT32 callid               <b>:</b> ����ID
 * @param [in] const TUP_CHAR* transto_number  <b>:</b> äתĿ�ĺ��룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_consult_transfer
 **/
TUP_API TUP_RESULT tup_call_blind_transfer(IN TUP_UINT32 callid, IN const TUP_CHAR* transto_number);


/**
 * @brief ���������ѯת/����ѯת����
 * 
 * @param [in] TUP_UINT32 callid                <b>:</b> ������ת�Ƶĺ���ID
 * @param [in] const TUP_UINT32 transto_callid  <b>:</b> ����ת�Ƶ�Ŀ�ĺ���ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_blind_transfer
 **/
TUP_API TUP_RESULT tup_call_consult_transfer(IN TUP_UINT32 callid, IN const TUP_UINT32 transto_callid);


/**
 * @brief ������Ƶ������Ϣ(���ھ��)
 * 
 * @param [in] TUP_UINT32 Count                    <b>:</b> ���ڸ�����һ��Ϊ2
 * @param [in] const CALL_S_VIDEOWND_INFO* window  <b>:</b> �������� 
 * @param [in] TUP_UINT32 callid                   <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���д���ʱ��callid��д��Ӧ����Чֵ�����в�����(δ���������к���ʱ)��callid��д�Ƿ�ֵ
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_video_window(IN TUP_UINT32 count, IN const CALL_S_VIDEOWND_INFO * window, IN TUP_UINT32 callid);


/**
 * @brief �Է�������Ƶת��Ƶ����ʱ������ѡ��ͬ����߾ܾ�
 * 
 * @param [in] TUP_UINT32 callid   <b>:</b> ����ID
 * @param [in] TUP_BOOL is_accept  <b>:</b> �Ƿ�ͬ��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_add_video
 * @see tup_call_del_video
 **/
TUP_API TUP_RESULT tup_call_reply_add_video(IN TUP_UINT32 callid, IN TUP_BOOL is_accept);



/**
 * @brief ������Ƶת��Ƶ��������
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_reply_add_video
 * @see tup_call_del_video
 * @see tup_call_reply_del_video
 **/
TUP_API TUP_RESULT tup_call_add_video(IN TUP_UINT32 callid);


/**
 * @brief ������Ƶת��Ƶ����(ɾ����Ƶ)����
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_add_video
 * @see tup_call_reply_add_video
 **/
TUP_API TUP_RESULT tup_call_del_video(IN TUP_UINT32 callid);


/**
 * @brief �������򿪱���Ԥ������
 * 
 * @param [in] TUP_UPTR handle   <b>:</b> ���ھ��
 * @param [in] TUP_UINT32 index  <b>:</b> ����ͷ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_close_preview
 **/
TUP_API TUP_RESULT tup_call_open_preview(IN TUP_UPTR handle, IN TUP_UINT32 index);


/**
 * @brief �رղ�ɾ������Ԥ������
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_open_preview
 **/
TUP_API TUP_RESULT tup_call_close_preview(TUP_VOID);


/**
 * @brief �������������С
 * 
 * @param [in] CALL_E_AO_DEV dev  <b>:</b> �豸����
 * @param [in] TUP_UINT32 volume  <b>:</b> ������С��ȡֵ��Χ[0, 100]
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_media_mute_mic
 * @see tup_call_media_mute_video
 **/
TUP_API TUP_RESULT tup_call_media_set_speak_volume(IN CALL_E_AO_DEV dev, IN TUP_UINT32 volume);


/**
 * @brief ������Ƶ����豸
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE route_dev  <b>:</b> ��Ƶ��������豸����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention IP Phoneʹ��
 * @see tup_call_media_set_audio_indev
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_outdev(IN CALL_E_AUDDEV_ROUTE route_dev);


/**
 * @brief ������Ƶ�����豸
 * 
 * @param [in] CALL_E_AUDDEV_ROUTE route_dev  <b>:</b> ��Ƶ��������豸����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention IP Phoneʹ��
 * @see tup_call_media_set_audio_outdev
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_indev(IN CALL_E_AUDDEV_ROUTE route_dev);


/**
 * @brief ����(��ȡ��)����������
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @param [in] TUP_BOOL is_on     <b>:</b> ������ȡ������  TRUE Ϊ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_media_mute_mic
 **/
TUP_API TUP_RESULT tup_call_media_mute_speak(IN TUP_UINT32 callid, IN TUP_BOOL is_on);


/**
 * @brief ����(��ȡ��)��˷羲��
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @param [in] TUP_BOOL is_on     <b>:</b> �Ƿ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_media_mute_video
 **/
TUP_API TUP_RESULT tup_call_media_mute_mic(IN TUP_UINT32 callid, IN TUP_BOOL is_on);


/**
 * @brief ����(��ȡ��)��ͣ��Ƶ�豸����(��Ƶ�ɼ�)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @param [in] TUP_BOOL is_on     <b>:</b> �Ƿ���ͣ��Ƶ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_media_mute_mic
 **/
TUP_API TUP_RESULT tup_call_media_mute_video(IN TUP_UINT32 callid, IN TUP_BOOL is_on);


/**
 * @brief �������ؼ�¼��������Ƶ(¼*����¼*��)
 * 
 * @param [in] TUP_UINT32 callid           <b>:</b> ����ID
 * @param [in] const TUP_CHAR* file_name   <b>:</b> ¼��������ļ���һ��Ϊ*.wav�ļ�
 * @param [in] TUP_BOOL is_video           <b>:</b> �Ƿ�Ϊ��Ƶ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �ݲ�֧������Ƶ����¼��
 * @see tup_call_media_stoprecord
 **/
TUP_API TUP_RESULT tup_call_media_startrecord(IN TUP_UINT32 callid, IN const TUP_CHAR* file_name, IN TUP_BOOL is_video);


/**
 * @brief ֹͣ���ؼ�¼��������Ƶ(¼*����¼*��)
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_media_startrecord
 **/
TUP_API TUP_RESULT tup_call_media_stoprecord(IN TUP_UINT32 callid);


/**
 * @brief ���ű�����Ƶ�ļ�(��������������������(��ʾ)����DTMF����æµ��ʾ���ͱ��ذ�������) 
 * 
 * @param [in] TUP_UINT32 loops           <b>:</b> ѭ��������0��ʾѭ�����ţ�
 * @param [in] const TUP_CHAR* play_file  <b>:</b> ���������ļ�����������·����Ŀǰ֧��wav��ʽ��
 * @param [out] TUP_INT32* play_handle    <b>:</b> ���ž��(����ֹͣ����ʱ�Ĳ���)
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention WAV�ļ���Ŀǰ֧��PCMA��PCMU��G.729��ʽ���������Ϊ8��16λ��������8k��48K��PCM���ݣ�֧��˫����
 * @see tup_call_media_startTcplay
 * @see tup_call_media_startLocalplay
 * @see tup_call_media_stopplay
 **/
TUP_API TUP_RESULT tup_call_media_startplay(IN TUP_UINT32 loops, IN const TUP_CHAR* play_file, OUT TUP_INT32* play_handle);


/**
 * @brief ������Ƶ�ļ�
 * 
 * @param [in] CALL_S_MEDIA_PLAY_PARAM* media_play_param  <b>:</b> ���Ų���������ѭ�������������ļ�·����ý�����ͣ�����ģʽ����Ϣ
 * @param [out] TUP_INT32* play_handle                    <b>:</b> ���ž��(����ֹͣ����ʱ�Ĳ���)
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��������������������������(��ʾ)����DTMF����æµ��ʾ�������ذ�������TCģʽ������TCģʽ������������������ý���
 * @see tup_call_media_startplay 
 * @see tup_call_media_stopplay
 **/
TUP_API TUP_RESULT tup_call_media_startplay_ex(IN CALL_S_MEDIA_PLAY_PARAM* media_play_param, OUT TUP_INT32* play_handle);


/**
 * @brief ֹͣ��������
 * 
 * @param [in] TUP_INT32 play_handle  <b>:</b> ���ž��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_media_startplay
 * @see tup_call_media_startTcplay
 * @see tup_call_media_startLocalplay
 **/
TUP_API TUP_RESULT tup_call_media_stopplay(IN TUP_INT32 play_handle);


/**
 * @brief ����ʹ�õ���˷��豸���
 * 
 * @param [in] TUP_UINT32 index  <b>:</b> ��˷��豸���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �豸���һ����ϵͳ��ʼ����ͨ��tup_call_media_get_devices��ȡ������PC
 * @see tup_call_media_get_mic_index
 * @see tup_call_media_get_devices
 **/
TUP_API TUP_RESULT tup_call_media_set_mic_index(IN TUP_UINT32 index);


/**
 * @brief ����ʹ�õ��������豸���
 * 
 * @param [in] TUP_UINT32 index  <b>:</b> �������豸���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �豸���һ����ϵͳ��ʼ����ͨ��tup_call_media_get_devices��ȡ������PC
 * @see tup_call_media_get_speak_index
 * @see tup_call_media_get_devices
 **/
TUP_API TUP_RESULT tup_call_media_set_speak_index(IN TUP_UINT32 index);


/**
 * @brief ����ʹ�õ���Ƶ�豸���
 * 
 * @param [in] TUP_UINT32 index  <b>:</b> ��Ƶ�豸���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �豸���һ����ϵͳ��ʼ����ͨ��tup_call_media_get_devices��ȡ
 * @see tup_call_media_get_video_index
 * @see tup_call_media_get_devices
 **/
TUP_API TUP_RESULT tup_call_media_set_video_index(IN TUP_UINT32 index);


/**
 * @brief ��ȡʹ�õ���˷��豸���
 * 
 * @param [out] TUP_UINT32* index  <b>:</b> ��˷��豸���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ڽӿڲ��Ի��Ʒ���ԣ�ʵ�ʲ�Ʒҵ�񳡾����������
 * @see tup_call_media_set_mic_index
 **/
TUP_API TUP_RESULT tup_call_media_get_mic_index(OUT TUP_UINT32* index);


/**
 * @brief ��ȡʹ�õ��������豸���
 * 
 * @param [out] TUP_UINT32* index  <b>:</b> �������豸���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ڽӿڲ��Ի��Ʒ���ԣ�ʵ�ʲ�Ʒҵ�񳡾����������
 * @see tup_call_media_set_speak_index
 **/
TUP_API TUP_RESULT tup_call_media_get_speak_index(OUT TUP_UINT32* index);


/**
 * @brief ��ȡʹ�õ���Ƶ�豸���
 * 
 * @param [out] TUP_UINT32* index  <b>:</b> ��Ƶ�豸���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ڽӿڲ��Ի��Ʒ���ԣ�ʵ�ʲ�Ʒҵ�񳡾����������
 * @see tup_call_media_set_video_index
 **/
TUP_API TUP_RESULT tup_call_media_get_video_index(OUT TUP_UINT32* index);


/**
 * @brief ����������������
 * 
 * @param [in] TUP_FLOAT in_gain  <b>:</b> ���棬ȡֵ��Χ [0,1)����˥����1������Ҳ��˥����(1,10]����Ŵ�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ó���:TCģʽ������С����Ҫ����/�������
 * @see tup_call_media_get_audio_ingain
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_ingain(IN TUP_FLOAT in_gain);


/**
 * @brief ��ȡ������������
 * 
 * @param [out] TUP_FLOAT* in_gain  <b>:</b> ���棬[0,1)����˥����1������Ҳ��˥����(1,10]����Ŵ�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ó���:TCģʽ������С����Ҫ����/�������
 * @see tup_call_media_set_audio_ingain
 **/
TUP_API TUP_RESULT tup_call_media_get_audio_ingain(OUT TUP_FLOAT* in_gain);


/**
 * @brief ���������������
 * 
 * @param [in] TUP_FLOAT out_gain  <b>:</b> ���棬ȡֵ��Χ [0,1)����˥����1������Ҳ��˥����(1,10]����Ŵ�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ó���:TCģʽ������С����Ҫ����/�������
 * @see tup_call_media_get_audio_outgain
 **/
TUP_API TUP_RESULT tup_call_media_set_audio_outgain(IN TUP_FLOAT out_gain);


/**
 * @brief ��ȡ�����������
 * 
 * @param [out] TUP_FLOAT* pfOutGain  <b>:</b> ���棬[0,1)����˥����1������Ҳ��˥����(1,10]����Ŵ�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ó���:TCģʽ������С����Ҫ����/�������
 * @see tup_call_media_set_audio_outgain
 **/
TUP_API TUP_RESULT tup_call_media_get_audio_outgain(OUT TUP_FLOAT* out_gain);


/**
 * @brief ��ȡ��Ƶ��Ƶ�豸�б�
 * 
 * @param [in/out] TUP_UINT32* num               <b>:</b> ����ʱ��ʾ�ϲ������豸���������ʱ��ʾ��ȡ�����豸�ĸ���
 * @param [in] CALL_S_DEVICEINFO* device_info    <b>:</b> �豸��Ϣ����ָ��
 * @param [in] CALL_E_DEVICE_TYPE device_type    <b>:</b> �豸����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_media_get_devices(IO TUP_UINT32* num, IN CALL_S_DEVICEINFO* device_info, IN CALL_E_DEVICE_TYPE device_type);


/**
 * @brief �ǼǺ���IPTҵ��
 * 
 * @param [in] CALL_E_SERVICE_CALL_TYPE type  <b>:</b> ҵ������
 * @param [in] void* data                     <b>:</b> �Ǽ�ҵ����Ҫ�Ĳ������ݣ���ǰ��ǰת��ҵ����Ҫ(ǰת��Ŀ�ĺ��룬�ַ���)
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �������IPTҵ���Ӧ��Ȩ�޺����������������
 * @see tagCALL_S_SERVICE_RIGHT_CFG
 **/
TUP_API TUP_RESULT tup_call_set_IPTservice(IN CALL_E_SERVICE_CALL_TYPE type, IN void* data);


/**
 * @brief ��ȡctd�����б�
 * 
 * @param [in] NA
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_start_call_ex
 **/
TUP_API TUP_RESULT tup_call_ctd_get_list(TUP_VOID);


/**
 * @brief ���ú���ҵ�����
 * 
 * @param [in] TUP_UINT32 cfgid  <b>:</b> ����ID,��call_def.h���壬ǰ׺ΪCALL_D_CFG_
 * @param [in] TUP_VOID * val    <b>:</b> ����ֵ���������õĲ���IDȷ����������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention 1 ʵ��������ĺ���ҵ�񣬱�����ô˽ӿڷֱ�����:
             <br>CALL_D_CFG_ENV_PRODUCT_TYPE����Ʒ���ͣ���
             <br>CALL_D_CFG_NET_NETADDRESS�����ص�ַ����
             <br>CALL_D_CFG_SERVER_REG_PRIMARY��sipע����������� CALL_D_CFG_SERVER_PROXY_PRIMARY��sip�����������
             <br>������Ҫ���ô˽ӿڷֱ�����:
             <br>CALL_D_CFG_SIP_TRANS_MODE��SIP����ģʽ����
             <br> 
             <br>2 ��IMϵͳ���ʹ��ʱ������ýӿڵ����ֱ��ͨ��tup_im_getserviceprofile�ӿڻ�ȡ��
 * @see tup_call_get_cfg
 **/
TUP_API TUP_RESULT tup_call_set_cfg(IN TUP_UINT32 cfgid, IN TUP_VOID * val);


/**
 * @brief ��ȡ����ҵ�����
 * 
 * @param [in] TUP_UINT32 cfgid  <b>:</b> ����ID,��call_def.h���壬ǰ׺ΪCALL_D_CFG_
 * @param [out] TUP_VOID* val    <b>:</b> ����ֵ���������õĲ���IDȷ����������
 * @param [in] TUP_UINT32 size   <b>:</b> ����ֵ��С���������õĲ���IDȷ����������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_set_cfg
 **/
TUP_API TUP_RESULT tup_call_get_cfg(IN TUP_UINT32 cfgid, OUT TUP_VOID* val,  IN TUP_UINT32 size);



/**
 * @brief ʹ����Ƶ����
 * 
 * @param [in] TUP_BOOL enable  <b>:</b> ״̬������0��ʾ���ã���0��ʾʹ�ܣ�Ĭ��ʹ��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention Ŀǰ������ʹ����Ƶ�����豸ˢ��
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_media_enable_audioengine(IN TUP_BOOL enable);



/**
 * @brief ������������
 * 
 * @param [in] TUP_UINT32 accountid        <b>:</b> �˺�ID
 * @param [in] TUP_BOOL right              <b>:</b> ����Ȩ��
 * @param [in] const char* linkage_number  <b>:</b> ������Ŀ�껰�����룬��󳤶�32
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �ڿ�������ǰ����
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_joint_setting(IN TUP_UINT32 accountid, IN TUP_BOOL right, IN const char* linkage_number);


/**
 * @brief ��������
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ����ǰ�����������������
 * @see tup_call_joint_stop
 **/
TUP_API TUP_RESULT tup_call_joint_start(TUP_VOID);


/**
 * @brief �ر�����
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_joint_start
 **/
TUP_API TUP_RESULT tup_call_joint_stop(TUP_VOID);


/**
 * @brief ����ͨ��Desktop��IP Phone�л�
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_joint_switch(TUP_VOID);


/**
 * @brief ͨ��ת����
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_joint_conf_result
 **/
TUP_API TUP_RESULT tup_call_joint_uptoconference(TUP_VOID);


/**
 * @brief ����������֪ͨ������
 * 
 * @param [in] TUP_UINT32 result  <b>:</b> ������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_joint_uptoconference
 **/
TUP_API TUP_RESULT tup_call_joint_conf_result(IN TUP_UINT32 result);


/**
 * @brief �½�����
 * 
 * @param [out] TUP_UINT32 *confid        <b>:</b> ����(���ƿ�)ID
 * @param [out] TUP_UINT32 *callid        <b>:</b> ����(���ƿ�)ID
 * @param [in] const TUP_CHAR *groupuri   <b>:</b> Ⱥ��URI�������Ⱥ�����ʱ��д
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_create(OUT TUP_UINT32 *confid, OUT TUP_UINT32 *callid, IN const TUP_CHAR *groupuri);


/**
 * @brief ���������
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> ����(���ƿ�)ID
 * @param [in] TUP_UINT32 count        <b>:</b> ����߸���
 * @param [in] const TUP_CHAR *number  <b>:</b> ����ߺ����б�(�����ַ)
 * @param [in] TUP_UINT32 persize      <b>:</b> �洢����ߺ����BUF����(�����Ա����)
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˲���ֻ�л�����ϯ���ܵ���
 * @see tup_call_serverconf_kick_attendee
 **/
TUP_API TUP_RESULT tup_call_serverconf_add_attendee(IN TUP_UINT32 confid, IN TUP_UINT32 count, IN const TUP_CHAR *number, IN TUP_UINT32 persize);


/**
 * @brief ɾ�������
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> ����(���ƿ�)ID
 * @param [in] const TUP_CHAR* number  <b>:</b> ����ߺ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˲���ֻ�л�����ϯ���ܵ���
 * @see tup_call_serverconf_add_attendee
 **/
TUP_API TUP_RESULT tup_call_serverconf_kick_attendee(IN TUP_UINT32 confid, IN const TUP_CHAR* number);


/**
 * @brief �޸�����߷���Ȩ��
 * 
 * @param [in] TUP_UINT32 confid       <b>:</b> ����(���ƿ�)ID
 * @param [in] const TUP_CHAR* number  <b>:</b> ����ߺ���
 * @param [in] TUP_UINT32 right        <b>:</b> �Ƿ�������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˲���ֻ�л�����ϯ���ܵ���
 * @see tup_call_serverconf_mute
 **/
TUP_API TUP_RESULT tup_call_serverconf_modify_right(IN TUP_UINT32 confid, IN const TUP_CHAR* number, IN TUP_UINT32 right);


/**
 * @brief ���û᳡����
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @param [in] TUP_BOOL is_mute   <b>:</b> �Ƿ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˲���ֻ�л�����ϯ���ܵ��ã�������������ϯ�⣬������ֻ��
 * @see tup_call_serverconf_modify_right
 **/
TUP_API TUP_RESULT tup_call_serverconf_mute(IN TUP_UINT32 confid, IN TUP_BOOL is_mute);


/**
 * @brief ���û᳡����(������������)
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @param [in] TUP_BOOL locked    <b>:</b> �Ƿ�����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˲���ֻ�л�����ϯ���ܵ���
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_lock(IN TUP_UINT32 confid, IN TUP_BOOL locked);


/**
 * @brief �˳�����
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ����ϯ�˳����飬������ϯȨ�޲�ת��(��û����ϯ����֧�ֽ�����ϯ��ػ�أ�������������˳��󣬻������)
 * @see tup_call_serverconf_end
 **/
TUP_API TUP_RESULT tup_call_serverconf_leave(IN TUP_UINT32 confid);


/**
 * @brief ��������
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˲���ֻ�л�����ϯ���ܵ���
 * @see tup_call_serverconf_leave
 **/
TUP_API TUP_RESULT tup_call_serverconf_end(IN TUP_UINT32 confid);


/**
 * @brief ������������
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_accept(IN TUP_UINT32 confid); 


/**
 * @brief ���ֻ���
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_serverconf_unhold
 **/
TUP_API TUP_RESULT tup_call_serverconf_hold(IN TUP_UINT32 confid); 


/**
 * @brief ȡ�����ֻ���
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_serverconf_hold
 **/
TUP_API TUP_RESULT tup_call_serverconf_unhold(IN TUP_UINT32 confid);


/**
 * @brief ����ͨ��ת����(Refer����)
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @param [in] TUP_UINT32 callid  <b>:</b> ��תΪ����ĺ���(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ô˽ӿ���Ҫ�ȵ���tup_call_serverconf_create��ɻ��鴴��
 * @see tup_call_serverconf_create
 * @see tup_call_serverconf_transferto_conf_non_refer
 **/
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf(IN TUP_UINT32 confid, IN TUP_UINT32 callid);


/**
 * @brief ����ͨ��ת����(��Refer����)
 * 
 * @param [in] TUP_UINT32 callid         <b>:</b> ��תΪ����ĺ���(���ƿ�)ID
 * @param [out] TUP_UINT32 *confid       <b>:</b> ����(���ƿ�)ID
 * @param [in] const TUP_CHAR *groupuri  <b>:</b> Ⱥ��URI�������Ⱥ�����ʱ��д
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ������ʹ��
 * @see tup_call_serverconf_transferto_conf
 **/
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf_non_refer(IN TUP_UINT32 callid, OUT TUP_UINT32 *confid, IN const TUP_CHAR *groupuri);


/**
 * @brief ��������ת���ݻ���
 * 
 * @param [in] TUP_UINT32 confid  <b>:</b> ����(���ƿ�)ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_serverconf_p2p_transferto_dataconf
 **/
TUP_API TUP_RESULT tup_call_serverconf_transferto_dataconf(IN TUP_UINT32 confid);


/**
 * @brief ��Ե�ֱ��ת��ý�����
 * 
 * @param [out] TUP_UINT32* confid        <b>:</b> ת�ɶ�ý�������Ӧ�Ļ���(���ƿ�)ID
 * @param [out] TUP_UINT32* callid        <b>:</b> ת�ɶ�ý�������Ӧ�ĺ���(���ƿ�)ID
 * @param [in] TUP_UINT32 p2p_callid      <b>:</b> ԭP2P����(���ƿ�)ID
 * @param [in] const TUP_CHAR* groupuri   <b>:</b> Ⱥ��URI�������Ⱥ�����ʱ��д
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ת�����ԭ��Ե����Ƶ���ڱ��֡�TODO
 * @see tup_call_serverconf_transferto_dataconf
 **/
TUP_API TUP_RESULT tup_call_serverconf_p2p_transferto_dataconf(OUT TUP_UINT32* confid, OUT TUP_UINT32* callid, IN TUP_UINT32 p2p_callid, IN const TUP_CHAR* groupuri);


/**
 * @brief ����ԤԼ����
 * 
 * @param [out] TUP_UINT32 *callid         <b>:</b> ����ԤԼ����󣬶�Ӧ�ĺ���ID
 * @param [in] const TUP_CHAR *accesscode  <b>:</b> ���������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_serverconf_access_reservedconf(OUT TUP_UINT32 *callid, IN const TUP_CHAR *accesscode);


/**
 * @brief ����CALL�����־������������־
 * 
 * @param [in] TUP_INT32 log_level        <b>:</b> ��־����ȡֵ:ö����CALL_E_LOG_LEVEL
 * @param [in] TUP_INT32 max_size         <b>:</b> ÿ����־�ļ������ֵ����λ: KB�����ֵΪTUP_INT32����ȡ�������ֵ
 * @param [in] TUP_INT32 file_count       <b>:</b> ��־�ļ����������ֵΪTUP_INT32����ȡ�������ֵ 
 * @param [in] const TUP_CHAR* log_path   <b>:</b> ��־���·�� 
 * @retval TUP_API TUP_VOID <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����ڳ�ʼ��֮ǰ����
 * @see tup_call_log_stop
 **/
TUP_API TUP_VOID tup_call_log_start(IN TUP_INT32 log_level, IN TUP_INT32 max_size, IN TUP_INT32 file_count, IN const TUP_CHAR* log_path);


/**
 * @brief ����CALL���HMEģ����־����
 * 
 * @param [in] TUP_INT32 audio_log_level   <b>:</b> HME-Audio ��־����(����ֵ��Դ:ö����CALL_E_LOG_LEVEL)
 * @param [in] TUP_INT32 audio_max_size    <b>:</b> HME-Audio ��־��ֵ(��λΪM, ��������Ϊ10, ��С1M, ���100M; Ĭ��Ϊ1M)
 * @param [in] TUP_INT32 video_log_level   <b>:</b> HME-Video ��־����(����ֵ��Դ:ö����CALL_E_LOG_LEVEL)
 * @param [in] TUP_INT32 video_max_size    <b>:</b> HME-Video ��־��ֵ(��λM, ��������Ϊ50, ��С1M, ���512M; Ĭ��Ϊ5M)
 * @retval TUP_API TUP_VOID <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ���ڵ�������ý���������־��������������ʹ��Ĭ��ֵ
 * @see NA
 **/
TUP_API TUP_VOID tup_call_hme_log_info(IN TUP_INT32 audio_log_level, 
            IN TUP_INT32 audio_max_size, IN TUP_INT32 video_log_level, IN TUP_INT32 video_max_size);


/**
 * @brief ֹͣCALL�����־
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_VOID <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_log_start
 **/
TUP_API TUP_VOID tup_call_log_stop(TUP_VOID);


/**
 * @brief ���ݺ�����ϵͳ�������ȡ��������
 * 
 * @param [in] TUP_UINT32 errornum  <b>:</b> �����룬ȡֵtagCALL_E_ERR_ID
 * @retval TUP_API const TUP_CHAR*  <b>:</b> �ɹ����ش��������ִ���ʧ��NULL
 * 
 * @attention ��ֻ֧�ֺ�����ϵͳ����Ĵ�������
 * @see NA
 **/
TUP_API const TUP_CHAR* tup_call_get_err_description(IN TUP_UINT32 errornum);


/**
 * @brief ��ȡЭ�̺�����������ֱ���
 * 
 * @param [in]  TUP_UINT32 callid           <b>:</b> ����(���ƿ�)ID
 * @param [out] TUP_UINT32 *max_frame_size  <b>:</b> ���ֱ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_data_maxframesize(IN TUP_UINT32 callid, OUT TUP_UINT32 *max_frame_size);


/**
 * @brief ����IP���й���
 * 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_disable_ipaddr_call
 **/
TUP_API TUP_RESULT tup_call_enable_ipaddr_call();


/**
 * @brief �ر�IP���й���
 * 
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_enable_ipaddr_call
 **/
TUP_API TUP_RESULT tup_call_disable_ipaddr_call();


/**
 * @brief ��Ƶ����
 * 
 * @param [in] CALL_S_VIDEOCONTROL *video_control  <b>:</b> ��Ƶ���Ʋ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_data_control
 **/
TUP_API TUP_RESULT tup_call_video_control(IN CALL_S_VIDEOCONTROL *video_control);


/**
 * @brief ����(����)����
 * 
 * @param [in] CALL_S_VIDEOCONTROL *data_control  <b>:</b> ����(����)���Ʋ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_video_control
 **/
TUP_API TUP_RESULT tup_call_data_control(IN CALL_S_VIDEOCONTROL *data_control);


/**
 * @brief �����ƶ���Ƶ·���豸
 * 
 * @param [in] CALL_E_MOBILE_AUIDO_ROUTE route  <b>:</b> �ƶ���Ƶ·���豸����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����ƶ��豸
 * @see tup_call_get_mobile_audio_route
 **/
TUP_API TUP_RESULT tup_call_set_mobile_audio_route(IN CALL_E_MOBILE_AUIDO_ROUTE route);


/**
 * @brief ��ȡ�ƶ���Ƶ·���豸
 * 
 * @param [out] CALL_E_MOBILE_AUIDO_ROUTE *route  <b>:</b> �ƶ���Ƶ·���豸����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����ƶ��豸
 * @see tup_call_set_mobile_audio_route
 **/
TUP_API TUP_RESULT tup_call_get_mobile_audio_route(OUT CALL_E_MOBILE_AUIDO_ROUTE *route);


/**
 * @brief ��������
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_stop_data
 **/
TUP_API TUP_RESULT tup_call_start_data(IN TUP_UINT32 callid);


/**
 * @brief ֹͣ����
 * 
 * @param [in] TUP_UINT32 callid  <b>:</b> ����ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_stop_data
 **/
TUP_API TUP_RESULT tup_call_stop_data(IN TUP_UINT32 callid);


/**
 * @brief ������Ƶ����(������)
 * 
 * @param [in] TUP_UINT32 callid                        <b>:</b> ����ID
 * @param [in] TUP_UINT32 index                         <b>:</b> �豸(����ͷ)����
 * @param [in] const CALL_S_VIDEO_ORIENT *video_orient  <b>:</b> ��Ƶ����(������)����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ҫ�����ƶ��豸
 * @see tup_call_set_video_render
 **/
TUP_API TUP_RESULT tup_call_set_video_orient(IN TUP_UINT32 callid, IN TUP_UINT32 index, IN const CALL_S_VIDEO_ORIENT *video_orient);


/**
 * @brief ������Ƶ��ʾ��������
 * 
 * @param [in] TUP_UINT32 callid                        <b>:</b> ����ID
 * @param [in] const CALL_S_VIDEO_RENDER_INFO* render   <b>:</b> ��Ƶ��ʾ��������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_set_video_orient
 **/
TUP_API TUP_RESULT tup_call_set_video_render(IN TUP_UINT32 callid, IN const CALL_S_VIDEO_RENDER_INFO* render);


/**
 * @brief ��������ͷ�ɼ�����
 * 
 * @param [in] TUP_UINT32 callid            <b>:</b> ����ID
 * @param [in] TUP_UINT32 capture_index     <b>:</b> �ɼ��豸(����ͷ)����
 * @param [in] TUP_UINT32 capture_rotation  <b>:</b> ����ͷ�ɼ��Ƕ� {0,1,2,3} �����ƶ�ƽ̨��Ч��Ĭ��Ϊ0
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_set_display_rotation
 **/
TUP_API TUP_RESULT tup_call_set_capture_rotation(IN TUP_UINT32 callid, IN TUP_UINT32 capture_index, IN TUP_UINT32 capture_rotation);


/**
 * @brief ���ô�����ʾ����
 * 
 * @param [in] TUP_UINT32 callid            <b>:</b> ����ID
 * @param [in] TUP_UINT32 render_type       <b>:</b> ��Ƶ�������ͣ�ȡֵCALL_E_VIDEOWND_TYPE
 * @param [in] TUP_UINT32 rotation          <b>:</b> ��Ƶ��ʾ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_call_set_capture_rotation
 **/
TUP_API TUP_RESULT tup_call_set_display_rotation(IN TUP_UINT32 callid, IN TUP_UINT32 render_type, IN TUP_UINT32 rotation);


/**
 * @brief ��������ͷͼƬ
 * 
 * @param [in] TUP_UINT32 callid    <b>:</b> ����ID
 * @param [in] TUP_CHAR *file_name  <b>:</b> �ļ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_video_capture_file(IN TUP_UINT32 callid, IN TUP_CHAR *file_name);


/**
 * @brief ����H.264��ƵB֡����
 * 
 * @param [in] TUP_BOOL is_enable  <b>:</b> �Ƿ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_set_vpuorder_enable(IN TUP_BOOL is_enable);


/**
 * @brief ���ͻỰ��INFO��Ϣ
 * 
 * @param [in] TUP_UINT32 callid ����ID
 * @param [in] CALL_S_DIALOG_INFO *dialog_info �Ự��INFO��Ϣ�ṹ 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ʒ����Ҫʱʹ�ô˺������Ͷ��Ƶ�SIP INFO��Ϣ����ʵ���ض�ҵ��
 * @see NA
 **/ 
TUP_API TUP_RESULT tup_call_send_diaglog_info(IN TUP_UINT32 callid, IN CALL_S_DIALOG_INFO *dialog_info);


/**
 * @brief ���ӻ�ΪTC
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��ʼ����ע��ǰ���ã���������TC��IE�ƣ������سɹ��������ƻ���
 * @see tup_call_disconnect_tc
 **/
TUP_API TUP_RESULT tup_call_connect_tc(TUP_VOID);


/**
 * @brief �Ͽ���ΪTC������
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ϊ��TC�豸ʹ��
 * @see tup_call_connect_tc
 **/
TUP_API TUP_RESULT tup_call_disconnect_tc(TUP_VOID);


/**
 * @brief ��ȡTC��IP��ַ
 * 
 * @param [out] CALL_S_IF_INFO* inetaddr  <b>:</b> IP��ַ��Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see ��Ϊ��TC�豸ʹ��
 **/
TUP_API TUP_RESULT tup_call_get_tc_ipaddr(OUT CALL_S_IF_INFO* inetaddr);


/**
 * @brief ��ȡ��Ƶģʽ
 * 
 * @param [out] TUP_UINT32* auido_mode  <b>:</b> ��Ƶģʽ @enum tagCALL_E_AUDIO_MODE
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ϊ��TC�豸ʹ��
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_audio_mode(OUT TUP_UINT32* auido_mode);


/**
 * @brief ��ȡTC��־
 * 
 * @param [in] TUP_VOID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ϊ��TC�豸ʹ��
 * @see NA
 **/
TUP_API TUP_RESULT tup_call_get_tc_log(TUP_VOID);


/**
 * @brief ����TC��MIC����
 * 
 * @param [out] TUP_INT32 is_mute  <b>:</b> �Ƿ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ϊ��TC�豸ʹ��
 * @see tup_call_set_spkdev_mute
 **/
TUP_API TUP_RESULT tup_call_set_micdev_mute(OUT TUP_INT32 is_mute);


/**
 * @brief ����TC������������
 * 
 * @param [in] TUP_INT32 is_mute  <b>:</b> �Ƿ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ϊ��TC�豸ʹ��
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
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/


