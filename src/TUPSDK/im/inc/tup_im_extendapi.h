/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM��ϵͳ��չҵ���ܽӿ�ͷ�ļ��� \n
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
 * @brief �����ļ����� ���첽�ӿڣ�
 * @param [in]  arg ���� 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �����ļ�������ɺ��յ���ʼ�ļ�����Ļص�֪ͨ��IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY
 *          <br>���շ����ջ�ܾ��ļ�����󣬷��ͷ��յ��ļ����俪ʼ�����IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY;
 *          <br>�û��յ������ļ�����ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY;
 *          <br>��ʼ�ļ�������յ�������Ȼص�֪ͨ��IM_E_EVENT_IM_FILEPROCESS_NOTIFY;
 *          <br>��ɴ�����յ�ֹͣ�ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY	
 * @see tup_im_acceptp2pfile
 * @see tup_im_rejectp2pfile
 * @see tup_im_cancelp2pfile
 **/
TUP_API TUP_RESULT tup_im_sendp2pfile(IN const IM_S_SENDP2PFILE_ARG* arg);

/**
 * @brief �����ļ����� ���첽�ӿڣ�
 * @param [in]  arg ���� 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �յ��ļ�����ص�֪ͨ�󣬿���ѡ������ļ�����
 *          <br>�û��յ������ļ�����ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY;
 *          <br>��ʼ�ļ�������յ�������Ȼص�֪ͨ��IM_E_EVENT_IM_FILEPROCESS_NOTIFY;
 *          <br>��ɴ�����յ�ֹͣ�ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY
 * @see tup_im_sendp2pfile
 * @see tup_im_rejectp2pfile
 * @see tup_im_cancelp2pfile
 **/
TUP_API TUP_RESULT tup_im_acceptp2pfile(IN const IM_S_ACCEPTP2PFILE_ARG* arg);

/**
 * @brief �����շ����ܾ��ļ����� ���첽�ӿڣ�
 * @param [in]  arg ���� 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �յ��ļ�����ص�֪ͨ�󣬿���ѡ��ܾ������ļ�����
 *          <br>�û��յ������ļ�����ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY;
 * @see tup_im_sendp2pfile
 * @see tup_im_acceptp2pfile
 * @see tup_im_cancelp2pfile
 **/
TUP_API TUP_RESULT tup_im_rejectp2pfile(IN const IM_S_REJECTP2PFILE_ARG* arg);

/**
 * @brief �����ͷ���ȡ���ļ����� ���첽�ӿڣ�
 * @param [in]  arg ���� 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ���ͷ������ļ������շ���δ����ʱ�����ͷ�����ȡ�������ļ�����
 *			<br>ȡ�����յ��ļ����俪ʼ����ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY;
 *			<br>������ȡ���ļ����䣬���Ż��յ�ֹͣ�ļ��������ص�֪ͨ��IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY
 * @see tup_im_sendp2pfile
 * @see tup_im_acceptp2pfile
 * @see tup_im_rejectp2pfile
 **/
TUP_API TUP_RESULT tup_im_cancelp2pfile(IN const IM_S_CANCELP2PFILE_ARG* arg);

/**
 * @brief ���Ͷ��� ���첽�ӿڣ�
 * @param [in]  arg ���� 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �û����յ����ŷ��ͽ�������Ż�ִ������յ��¶��ŵȶ�����Ϣ��������Ϣ�Ļص�֪ͨ��IM_E_EVENT_IM_SMS_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_sendsms(IN const IM_S_SENDSMS_ARG* arg);

/**
* @brief Ⱥ����Ԥ�ϴ��ļ� ��ͬ���ӿڣ�
* @param [in]  arg Ԥ�ϴ��ļ���Ϣ
* @param [out] ack Ԥ�ϴ��ļ�ID
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention Ԥ�ϴ��ļ�������С������
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_delete_result;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_pre_upload(IN const IM_S_GROUPFILE_PRE_UPLOAD_ARG* arg, OUT IM_S_GROUPFILE_PRE_UPLOAD_ACK* ack);

/**
* @brief Ⱥ�����ϴ��ļ����֪ͨ������ ��ͬ���ӿڣ�
* @param [in]  arg ���ϴ���Ⱥ������ļ���Ϣ
* @param [out] ack �ϴ��ɹ�����ļ�ID�Լ��ϴ��ɹ���ʱ���
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention NA
* @see tup_im_groupfile_pre_upload;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_delete_result;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_report_upload_result(IN const IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ARG* arg, OUT IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ACK* ack);

/**
* @brief Ⱥ����Ԥɾ���ļ� ��ͬ���ӿڣ�
* @param [in]  arg ��Ҫɾ�����ļ�ID
* @param [out] ack Ԥɾ�����ļ�ID
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention NA
* @see tup_im_groupfile_pre_upload
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_delete_result;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_pre_delete(IN const IM_S_GROUPFILE_PRE_DELETE_ARG* arg, OUT IM_S_GROUPFILE_PRE_DELETE_ACK* ack);

/**
* @brief Ⱥ����ɾ���ļ����֪ͨ������ ��ͬ���ӿڣ�
* @param [in]  arg    ��ɾ����Ⱥ������ļ���Ϣ
* @param [out] result ɾ��������ͺ���������ص���Ӧ���
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention NA
* @see tup_im_groupfile_pre_upload
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_query;
*/
TUP_API TUP_RESULT tup_im_groupfile_report_delete_result(IN const IM_S_GROUPFILE_REPORT_DELETE_RESULT_ARG* arg, OUT TUP_BOOL* result);

/**
* @brief Ⱥ�����Ѵ��ڵĹ����ļ���ѯ ��ͬ���ӿڣ�
* @param [in]  arg ��ѯ����
* @param [out] ack ��ѯ��Ӧ
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention NA

* @see tup_im_groupfile_pre_upload
* @see tup_im_groupfile_upload_result;
* @see tup_im_groupfile_pre_delete;
* @see tup_im_groupfile_delete_result;
*/
TUP_API TUP_RESULT tup_im_groupfile_query(IN const IM_S_GROUPFILE_QUERY_ARG* arg, OUT IM_S_GROUPFILE_QUERY_ACK* ack);


/**
 * @brief ���õ�ǰ�˻�������״̬ ��ͬ���ӿڣ�
 * 
 * @param [in] const IM_S_LINKAGE_STATUS* arg  <b>:</b> ����״̬
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_im_get_linkage_status
 **/
TUP_API TUP_RESULT tup_im_set_linkage_status(IN const IM_S_LINKAGE_STATUS* arg);


/**
 * @brief ��ȡ��ǰ�˻�������״̬ ��ͬ���ӿڣ�
 * 
 * @param [out] IM_S_LINKAGE_STATUS* ack  <b>:</b> ����״̬
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see tup_im_set_linkage_status
 **/
TUP_API TUP_RESULT tup_im_get_linkage_status(OUT IM_S_LINKAGE_STATUS* ack);

/**
 * @brief UI����׼���ú�֪ͨƽ̨��ʼ�ַ���Ϣ ���첽�ӿڣ�
 * @param [in] isDispatch �Ƿ�ʼ�ַ���Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ýӿ��ѷ���
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setdispatchmessage(TUP_BOOL isDispatch);

/**
 * @brief �˳��ͻ���ʱ������ͬ���ӿ������ڵȴ��С��ڶ����߳���֪ͨ�ͻ����Լ���Ҫ�ٵȴ��ӿڷ�����Ϣ ���첽�ӿڣ�
 * @param [in] ��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ýӿ��ѷ���
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setcancelsendingmessage();

/**
 * @brief ����������Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ýӿ��ѷ���
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
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
