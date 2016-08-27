/** 
* @file tup_cloud_record_interface.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM ��¼��ϵͳ�����ӿڽṹ�嶨��ͷ�ļ��� \n
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
 * @brief �Խ���¼��ʼ��
 * 
 * @param [in] const CLOUD_RECORD_INIT_CONFIG *config  <b>:</b> ��ʼ��������Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_im_cloud_record_uninit
 **/
TUP_API TUP_RESULT tup_im_cloud_record_init(IN const CLOUD_RECORD_INIT_CONFIG *config);


/**
 * @brief �Խ���¼ȥ��ʼ��
 * 
 * @param [out] NA
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_im_cloud_record_init
 **/
TUP_API TUP_RESULT tup_im_cloud_record_uninit();


/**
 * @brief ��ȡ��¼����
 * 
 * @param [in] CLOUDRECORDHANDLE *handle                                <b>:</b> ���
 * @param [in] CLOUD_RECORD_GET_CFG_REQ *get_cfg_req                    <b>:</b> ��ȡ��¼������������Ϣ
 * @param [in] CLOUD_RECORD_GET_CFG_RSP_NOTIFY get_cfg_rsp_notify_func  <b>:</b> ��ȡ��¼������������Ϣ�ص�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention  NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_cloud_record_get_config_info(IN CLOUDRECORDHANDLE *handle, 
                    IN CLOUD_RECORD_GET_CFG_REQ *get_cfg_req, IN CLOUD_RECORD_GET_CFG_RSP_NOTIFY get_cfg_rsp_notify_func);


/**
 * @brief �ϴ�ͨ����Ϣ
 * 
 * @param [in] CLOUDRECORDHANDLE *handle                                              <b>:</b> ���
 * @param [in] CLOUD_RECORD_SEND_CALL_INFO_REQ *send_call_info_req                    <b>:</b> �ϴ���¼������ͨ����Ϣ
 * @param [in] CLOUD_RECORD_SEND_CALL_INFO_RSP_NOTIFY send_call_info_rsp_notify_func  <b>:</b> �ϴ���¼������ͨ����Ϣ�ص�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
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
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/


