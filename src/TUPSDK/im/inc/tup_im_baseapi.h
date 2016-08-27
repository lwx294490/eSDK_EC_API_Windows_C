/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM��ϵͳ����ҵ���ܽӿ�ͷ�ļ��� \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_BASEAPI_H_
#define _TUP_IM_BASEAPI_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
 * @brief ��ʼ��im��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��ʼ��im����ʹ��imҵ�����ĵ�һ����������ִ��
 * @see tup_im_uninit
 **/ 
TUP_API TUP_RESULT tup_im_init();

/**
 * @brief ж��im��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ��ȷ����Ҫ��imҵ���Ѿ���ɲ���ж��im��
 * @see tup_im_init
 **/
TUP_API TUP_RESULT tup_im_uninit();

/**
 * @brief ���÷�������ַ
 * @param [in]  ip ��������ַ
 * @param [in]  port �������˿�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ��ʼ���󣬵�¼ǰ����
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setserveraddress(IN const TUP_CHAR* ip, IN TUP_UINT16 port);

/**
 * @brief ��¼��ͬ���ӿڣ�
 * @param [in]  arg ��¼����
 * @param [out] ack ��¼���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention NA
 * @see tup_im_logout
 * @see tup_im_sendheartbeat
 **/
TUP_API TUP_RESULT tup_im_login(IN const IM_S_LOGIN_ARG* arg, OUT IM_S_LOGIN_ACK* ack);

/**
 * @brief �˳���¼���첽�ӿڣ�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �˳�����ڻص�֪ͨ�з��أ�IM_E_EVENT_IM_LOGOUT_NOTIFY
 * @see tup_im_login
 **/
TUP_API TUP_RESULT tup_im_logout();

/**
 * @brief ע��ص���Ϣ���첽�ӿڣ�
 * @param [in]  callback IMҵ��ص���������ַ,���û������Ͷ��壬����IMҵ����ص��¼�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ���������£�callback����ֵΪTUP_TRUE;
 * @see TUP_IM_FN_CALLBACK_PTR
 **/
TUP_API TUP_RESULT tup_im_register_callback(IN TUP_IM_FN_CALLBACK_PTR callback);

/**
 * @brief brief ���ò�֪ͨ����/ֹͣ����״̬���첽�ӿڣ�
 * @param[ in]  arg ��ǰ�û���������״̬
 * @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention һ��ʱ��û���������ʱ����Ҫ����ֹͣ����״̬�������û�һֱ��������״̬�����շ��յ����ͷ�������״̬���֪ͨ��IM_E_EVENT_IM_SENDIMINPUT_NOTIFY 
 *            <br>�ú�������ע��������Ӧ�������
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_notifyiminputting(IN const IM_S_CHAT_STATUS_ARG* arg);

/**
 * @brief ��ȡ��ϵ���б�ͬ���ӿڣ�
 * @param [in]  arg ��ѯ��ϵ���б�����
 * @param [out] ack ��ѯ��ϵ���б���Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *            <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_getcontactlist(IN const IM_S_GETCONTACTLIST_ARG* arg, OUT IM_S_GETCONTACTLIST_ACK* ack);

/**
* @brief ��ȡҵ��������������ͬ���ӿڣ�
* @param [in]  arg ��ѯҵ��������������
* @param [out] ack ��ѯҵ���������ݽ����Ӧ
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
*        <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©
* @see tup_im_release_tup_list
*/
TUP_API TUP_RESULT tup_im_getserviceprofile(IN const IM_S_GETSERVICEPROFILEARG* arg, OUT IM_S_SERVICEPROFILEACK* ack);

/**
* @brief ��ȡϵͳ���������첽�ӿڣ�
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention ��ȡϵͳ���ӵ���Ϣ��Ӧ��IM_E_EVENT_IM_SYSURLRET_NOTIFY
* @see NA
*/
TUP_API TUP_RESULT tup_im_getsysurl();

/**
* @brief ��ȡ�û���Ϣ���󣨾�ȷ��ѯ��
* @param [in]  arg ��ѯ�û�����
* @param [out] ack ӵ���˺ŵ��û���Ϣ
* @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
*
* @attention arg�п�����д�˺Ż�staffID
* @see NA
*/
TUP_API TUP_RESULT tup_im_getuserinfo(IN const IM_S_GETUSERINFOARG* arg, OUT IM_S_USERINFO* ack);

/**
 * @brief ��Ӻ��Ѻ���ϵ�˷��� ��ͬ���ӿڣ�
 * @param [in]  arg ��Ӻ��ѷ�������
 * @param [out] ack ��Ӻ��ѷ�����Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addusergroup(IN const IM_S_ADDUSERGROUP_ARG* arg, OUT IM_S_ADDUSERGROUP_ACK* ack);

/**
 * @brief �޸ĺ��Ѻ���ϵ�˷��� ��ͬ���ӿڣ�
 * @param [in]  arg �޸ĺ��ѷ�������
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_modusergroup(IN const IM_S_MODUSERGROUP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief ɾ�����Ѻ���ϵ�˷��� ��ͬ���ӿڣ�
 * @param [in]  id ���Ѻ���ϵ�˷���ID
 * @param [out] result �������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ɾ���÷���ǰ����Ҫɾ�����ƶ�(����Ʒ����Ĭ�Ϸ��飬���ѡ���ƶ���Ĭ�Ϸ���)�����ڵ����к��ѣ���ո÷����ڳ�Ա����ɾ���÷���
 * @see tup_im_delfriendorcontact
 **/
TUP_API TUP_RESULT tup_im_delusergroup(IN TUP_INT64 id, OUT TUP_BOOL* result);

/**
 * @brief ������ϵ�˷����б�˳����������
 * 
 * @param [in]  arg    <b>:</b> ��ϵ�˷���ID˳���б�
 * @param [out] result <b>:</b> ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˺�������ע������������
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_update_usergroup(IN IM_S_UPDATE_USERGROUP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief ����˺��û�Ϊ���ѣ�ͬ���ӿڣ�
 * @param [in]  arg ����˺��û�Ϊ��������
 * @param [out] ack ����˺��û�Ϊ������Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ɹ���Ӻ󣬱�����߻��յ����ɹ����֪ͨ:IM_E_EVENT_IM_ADDFRIEND_NOTIFY
 * @see tup_im_delfriendorcontact
 **/
TUP_API TUP_RESULT tup_im_addfriend(IN const IM_S_ADDFRIEND_ARG* arg, OUT IM_S_ADDFRIEND_ACK* ack);

/**
 * @brief ɾ�����ѻ�����ϵ�ˣ�ͬ���ӿڣ�
 * @param [in]  arg ��ĳһ��������ɾ�����ѻ�/��ϵ��
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ɾ�������˺��û����͵ĺ��Ѻ��Զ�����ϵ�����͵ĺ���
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_delfriendorcontact(IN const IM_S_DELCONTACT_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief ����Զ�����ϵ��Ϊ���� ��ͬ���ӿڣ�
 * @param [in]  arg ����Զ�����ϵ��Ϊ��������
 * @param [out] ack ����Զ�����ϵ����Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ��ӳɹ���ack�᷵����ϵ�˵�id��arg������Ҫ��д�Լ���staffID
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addcontact(IN const IM_S_ADDCONTACT_ARG* arg, OUT IM_S_ADDCONTACT_ACK* ack);

/**
 * @brief �޸��Զ�����ϵ�˺��� ��ͬ���ӿڣ�
 * @param [in]  arg �޸��Զ�����ϵ������
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_modcontact(IN const IM_S_MODCONTACT_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief �ƶ�������ϵ��/�������������� ��ͬ���ӿڣ�
 * @param [in]  arg �ƶ�������ϵ��/������������������
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_movecontactgroup(IN const IM_S_MODCONTACTGROUP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief ̽���û�״̬ ���첽�ӿڣ�����û����ߣ�������IM_E_EVENT_USERSTATUS_NOTIFY�¼�֪ͨ���������û����������¼���������
 * @param [in]  arg �ʺ��б�����arg->data Ϊ�û��˺ţ�����ΪTUP_CHAR[]
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ɹ�̽��󣬻᷵���û���״̬��IM_E_EVENT_USERSTATUS_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_detectuserstatus(IN const TUP_S_LIST* arg);

/**
 * @brief ���ķǺ����û�״̬ ���첽�ӿڣ�
 * @param [in]  arg �ʺ��б�����arg->data Ϊ�û��˺ţ�����ΪTUP_CHAR[]
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ú�������ע��������Ӧ������أ�
 *          <br>���ĺ�ķǺ����û�״̬���ʱ�����յ��ص�֪ͨ��IM_E_EVENT_USERSTATUS_NOTIFY
 * @see tup_im_subscribeuserstatus 
 **/
TUP_API TUP_RESULT tup_im_subscribeuserstatus(IN const TUP_S_LIST* arg);

/**
 * @brief ȡ�����ķǺ����û�״̬ ���첽�ӿڣ�
 * @param [in]  arg �ʺ��б�����arg->data Ϊ�û��˺ţ�����ΪTUP_CHAR[]
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ע��ǰ��Ҫȡ�����ģ������´�����ǰ�����͹�����û�״̬��Ϣ���µ�¼��ʱ�������ú�������ע��������Ӧ�������
 * @see tup_im_subscribeuserstatus 
 **/
TUP_API TUP_RESULT tup_im_unsubscribeuserstatus(IN const TUP_S_LIST* arg);


/**
 * @brief �����ı���Ϣ ���첽�ӿڣ�
 * @param [in]  arg �����ı���Ϣ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ���͵���Ϣ���ݹ���ʱ��������ֵΪ500������ʹ��ѹ����base64����ӿڴ�����ٷ��ͣ�
 *          <br>���շ����յ��¼�ʱ��Ϣ֪ͨ��IM_E_EVENT_IM_CODECHAT_NOTIFY��
 *          <br>�ڽ��շ�����״̬�·��͵���Ϣ�����շ����ߺ���յ��¼�ʱ��Ϣ����֪ͨ��IM_E_EVENT_IM_CHATLIST_NOTIFY
 * @see tup_im_gzlib_comp;
 * @see    tup_im_base64_encode;
 **/
TUP_API TUP_RESULT tup_im_sendim(IN const IM_S_SENDIM_ARG* arg);

/**
 * @brief ������Ϣ�Ѷ���ͬ���ӿڣ�
 * @param [in]  arg �ı���Ϣ�Ѷ��������� ����arg->messageinfo->data IM_S_MESSAGEINFO
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ������Ϣ�Ѷ�����ɺ�������ֵ����
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setmessageread(IN IM_S_SETMESSAGEREAD_ARG* arg);

/**
 * @brief ��ȡ������Ϣ ��ͬ���ӿڣ�
 * @param [in]  arg ��ѯ������Ϣ����
 * @param [out] ack ��ѯ������Ϣ��Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *          <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_queryHistoryMessage(IN const IM_S_QUERYHISTORYMESSAGE_ARG* arg, OUT IM_S_QUERYHISTORYMESSAGE_ACK* ack);

/**
 * @brief ��ȡ�����б� ��ͬ���ӿڣ�
 * @param [in]  deptid ����ID����ȡһ������ʱ��-1
 * @param [out] ack ��ѯ�����б���Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *         <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_getdepts(IN TUP_INT64 deptID, OUT IM_S_GETDEPTS_ACK* ack);

/**
 * @brief ��ѯ��ҵͨѶ¼ ��ͬ���ӿڣ�
 * @param [in]  arg ��ѯ��ҵͨѶ¼����
 * @param [out] ack ��ѯ��ҵͨѶ¼�����Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *      <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©;
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_queryentaddressbook(IN const IM_S_QUERY_ENTADDRESSBOOK_ARG* arg, OUT IM_S_QUERY_ENTADDRESSBOOK_ACK* ack);

/**
 * @brief ��ѯ�û���Ϣ��ģ����ѯ�� ��ͬ���ӿڣ�
 * @param [in]  arg ��ѯ�û���Ϣ����
 * @param [out] ack ��ѯ�û���Ϣ�����Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *            <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©;
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_queryuserinfo(IN const IM_S_QUERY_USERINFO_ARG* arg, OUT IM_S_QUERY_USERINFO_ACK* ack);

/**
 * @brief ��ӹ̶�Ⱥ ��ͬ���ӿڣ�
 * @param [in]  arg �������޸Ĺ̶�Ⱥ������������
 * @param [out] ack �����̶�Ⱥ����������Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ���ʱȺID������д���ɹ���Ӻ�ȺID����ack�з��أ�������Զ���Ϊ�̶�Ⱥ�Ĺ���Ա
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addfixedgroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT IM_S_ADDIMGROUP_ACK* ack);

/**
 * @brief �޸Ĺ̶�Ⱥ��Ϣ ��ͬ���ӿڣ�
 * @param [in]  arg �������޸Ĺ̶�Ⱥ����
 * @param [out] ack �޸Ĺ̶�Ⱥ��Ϣ��Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ֻ�й̶�Ⱥ����Ա����ʹ�ô˹���;�޸���ɺ������̶�Ⱥ��Ա���յ��ص�֪ͨ��IM_E_EVENT_FIXEDGROUP_INFOCHG_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_modfixedgroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT IM_S_MODFIXEDGROUP_ACK* ack);

/**
 * @brief ɾ���̶�Ⱥ ��ͬ���ӿڣ�
 * @param [in]  id �̶�ȺID
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ò���ֻ��Ⱥ����Ա��Ȩ�޲���
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_delfixedgroup(IN const TUP_CHAR* id,  OUT TUP_BOOL* result);

/**
 * @brief �̶�Ⱥ��ӳ�Ա ���첽�ӿڣ�
 * @param [in]  arg ��ӹ̶�Ⱥ��Ա����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ò���ֻ��Ⱥ����Ա��Ȩ�޲���;�յ�������û����յ��ص���Ϣ��IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addfixedgroupmember(IN const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * @brief �̶�Ⱥɾ����Ա ���첽�ӿڣ�
 * @param [in]  arg ɾ���̶�Ⱥ��Ա����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ò���ֻ��Ⱥ����Ա��Ȩ�޲���;�̶�Ⱥ��Ա���յ��ص�֪ͨ��IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_delfixedgroupmember(IN const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * @brief ����Ա�����û��������̶�Ⱥ���� ���첽�ӿڣ�
 * @param [in]  arg ����Ա�����û��������̶�Ⱥ��������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ֻ�й̶�Ⱥ����Ա����ʹ�ô˹��ܣ�
 *            <br>�̶�Ⱥ����Ա�����յ��������̶�Ⱥ������IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY
 *            <br>�̶�Ⱥ����Ա���������������û��յ���������ص�֪ͨ��IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_confirmfixedgroupapply(IN const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * @brief �û���������Ա�������̶�Ⱥ ���첽�ӿڣ�
 * @param [in]  arg �û���������Ա�������̶�Ⱥ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �û��յ��̶�Ⱥ����Ա�������̶�Ⱥ�Ļص�֪ͨ��Ϣ��IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_confirmfixedgroupinvite(IN const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * @brief �û������������̶�Ⱥ ���첽�ӿڣ�
 * @param [in]  arg �û��������̶�Ⱥ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention Ⱥ��Ա�յ�����Ա��������̶�Ⱥ֪ͨ����Ӧ��IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_joinfixedgroup(IN const IM_S_JOINFIXEDGROUP_ARG* arg);

/**
 * @brief �û��˳�����̶�Ⱥ ���첽�ӿڣ�
 * @param [in]  arg �˳��Ĺ̶�ȺID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �̶�Ⱥ����Աֻ�ܽ�ɢ�̶�Ⱥ�������˳��̶�Ⱥ���ú�������ע��������Ӧ�������
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_leavefixedgroup(IN const TUP_CHAR* arg);

/**
 * @brief ת�ƹ̶�Ⱥ����ԱȨ�� ���첽�ӿڣ�
 * @param [in]  arg ת�ƹ̶�Ⱥ����ԱȨ������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ֻ�й̶�Ⱥ����Ա����ʹ�ô˹��ܣ���ת��Ϊ�̶�Ⱥ����Ա���û����յ��ص�֪ͨ��IM_E_EVENT_FIXEDGROUP_OWNERCHG_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_transferfixedgroup(IN const IM_S_TRANSFERIMGROUP_ARG* arg);

/**
 * @brief ��ȡȺ������ ��ͬ���ӿڣ�
 * @param [in]  arg ���� Ⱥ��ID
 * @param [out] ack �̶�Ⱥ��ϸ��Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_getfixedgroupdetail(IN const TUP_CHAR* arg, OUT IM_S_IMGROUPINFO* ack);

/**
 * @brief ��ȡ�̶�Ⱥ���������Ա ��ͬ���ӿڣ�
 * 
 * @param [in]  arg  <b>:</b> ��ȡ�̶�Ⱥ���������Ա����
 * @param [out] ack  <b>:</b> ��ȡ�̶�Ⱥ���������Ա�б���Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *            <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_getfixedgroupmembers(IN const IM_S_REQUESTIMGROUPMEMBERS_ARG* arg, OUT IM_S_GROUPUSERLIST* ack);

/**
 * @brief ��ѯ�̶�Ⱥ��ģ����ѯ����ͬ���ӿڣ�
 * @param [in]  arg ��ѯ�̶�Ⱥ����
 * @param [out] ack ��ѯ�̶�Ⱥ��Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b>�ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *        <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©;
 * @see tup_im_release_tup_list
*/
TUP_API TUP_RESULT tup_im_getfixedgroups(IN const IM_S_GETIMGROUPLIST_ARG* arg, OUT IM_S_GETIMGROUPLIST_ACK* ack);

/**
 * @brief ��������飨ͬ���ӿڣ�
 * @param [in]  arg �������޸Ĺ̶�Ⱥ������������
 * @param [out] ack �������޸Ĺ̶�Ⱥ����������Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ���ʱ������ID������д���ɹ���Ӻ�������ID����ack�з��أ�������Զ���Ϊ���������Ա
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_adddiscussiongroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT IM_S_ADDIMGROUP_ACK* ack);

/**
 * @brief �޸������� ��ͬ���ӿڣ�
 * @param [in]  arg �������޸Ĺ̶�Ⱥ������������
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �������Ա���յ���������Ϣ����ص�֪ͨ��IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_moddiscussiongroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief ɾ�������� ��ͬ���ӿڣ�
 * @param [in]  id ��Ҫɾ����������ID
 * @param [out] result ���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ֻ�����������Ա����ʹ�ô˹���
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_deldiscussiongroup(IN const TUP_CHAR* id, OUT TUP_BOOL* result);

/**
 * @brief ��������ӳ�Ա ���첽�ӿڣ�
 * @param [in]  arg ����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ��ӳ�Ա��ɺ�������������Ա���յ��³�Ա����֪ͨ��IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY;
 *            <br>������߻��յ��ص���Ϣ��IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_adddiscussiongroupmember(IN const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * @brief ������ɾ����Ա ���첽�ӿڣ�
 * @param [in]  arg ɾ���̶�Ⱥ���������Ա����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ֻ�����������Ա����ʹ�ô˹��ܣ���ӳ�Ա��ɺ�������������Ա���յ�ɾ����Ա֪ͨ��IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_deldiscussiongroupmember(IN const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * @brief �����������������������Ա ���첽�ӿڣ�
 * @param [in]  arg ��������ӻ�ɾ�������û�����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ������Ա���ᱣ���ڷ��������������Ա�б��У��ú�������ע��������Ӧ������أ��������Ա���յ�ɾ���������û��Ļص�֪ͨ��IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_adddiscussiongroupphonemember(IN const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * @brief ������ɾ��������Ա ���첽�ӿڣ�
 * @param [in]  arg ��������ӻ�ɾ�������û����� 
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ú�������ע��������Ӧ������أ�������������Ա���յ�ɾ����Ա�ص�֪ͨ��IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_deldiscussiongroupphonemember(IN const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * @brief �˳������� ���첽�ӿڣ�
 * @param [in]  arg ���� ������ID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ú�������ע��������Ӧ�������
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_leavediscussiongroup(IN const TUP_CHAR* arg);

 
/**
 * @brief �˳����������� ��ͬ���ӿڣ�
 * @param [in]  arg ���� ������ID
 * @param [out] ack ��Ӧ �˳���������Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ӿڻ᷵���������Ա�����Ա�˳��Ľ��
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_leave_discussion_group(IN const TUP_CHAR* arg, OUT IM_S_LEAVE_DISCUSSGROUP_ACK* ack);

/**
 * @brief ת�����������ԱȨ�� ���첽�ӿڣ�
 * @param [in]  arg ת�ƹ̶�Ⱥ�����������ԱȨ������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ֻ�����������Ա����ʹ�ô˹��ܣ�ת����ɺ����г�Ա�յ����������Ա���֪ͨIM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_transferdiscussiongroup(IN const IM_S_TRANSFERIMGROUP_ARG* arg);


/**
 * @brief �̻�������
 *
 * @param [in] const  IM_S_SET_DISGROUP_POLICY_MSG* arg  <b>:</b> �̻�����������
 * @param [out] IM_S_SET_DISGROUP_POLICY_MSG* ack        <b>:</b> �̻���������Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_set_disgroup_policy(IN const IM_S_SET_DISGROUP_POLICY_MSG* arg, OUT IM_S_SET_DISGROUP_POLICY_MSG* ack);


/**
 * @brief �㲥�����������Ϣ
 *
 * @param [in]  IM_S_SEND_DISGROUP_OPT_MSG* arg  <b>:</b> �����������Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see IM_E_EVENT_IM_DISCUSSGROUP_OP_NOTIFY
 **/
TUP_API TUP_RESULT tup_im_send_disgroup_op_message(IN IM_S_SEND_DISGROUP_OPT_MSG* arg);

/**
 * @brief �����Լ��Զ���ͷ�� ���첽�ӿڣ�
 * @param [in] image ���� �Զ���ͷ��ͼƬ��Ϣ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ú�������ע��������Ӧ�������
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setselfdefineimage(IN const IM_S_IMAGEINFO* image);

/**
 * @brief �����Լ�ϵͳĬ��ͷ�� ���첽�ӿڣ�
 * @param [in] imageID ���� ϵͳĬ��ͷ��ͼƬID
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention UI�����ж�ӦID��ͼƬ�����ڱ��أ����Һͷ������ϵ�ϵͳͷ��ID���룻�ú�������ע��������Ӧ�������
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setsystemimage(IN const TUP_CHAR* imageID);

/**
 * @brief ���ø�����Ϣ���첽�ӿڣ�
 * @param [in] arg ���� �����˺���Ϣ���û�
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention ĳЩ������Ϣ�޸�û��Ȩ���޸ģ���������������ã��ú�������ע��������Ӧ�������
 *            <br>���ĸ��û��������û����յ��û���Ϣ���֪ͨ��IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setuserinfo(IN IM_S_USERINFO* arg);

/**
 * @brief ��ȡ�û��Զ���ͷ�� ��ͬ���ӿڣ�
 * @param [in] arg ��ȡ�����û����Զ���ͷ������
 * @param [out] ack ��ȡ�����û��Զ���ͷ���ͼƬ��Ϣ��Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention arg�е��˺��������û���Ϣ�е�account����
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_getuserdefineimage(IN const IM_S_IMAGEREQARG* arg, OUT IM_S_USERIMAGEINFO* ack);


/**
 * @brief ֪ͨ�������Լ�״̬�仯 ���첽�ӿڣ�
 * @param [in] arg ֪ͨ�������Լ���״̬�仯����
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �ú�������ע��������Ӧ������أ�
 *            <br>���ж��ı����û��Լ���ӱ����û�Ϊ���ѵ������û����յ�״̬�仯�ص�֪ͨ��IM_E_EVENT_IM_USERSTATUS_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_publishstatus(IN const IM_S_STATUSARG* arg);

/**
 * @brief �����б��ѯ��ͬ���ӿڣ�
 * @param [in] arg ��ѯ�����б�����
 * @param [out] ack ��ѯ�����б�����Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �����سɹ�����ack�ṹ�е���Ϣʹ����ɺ���Ҫ����tup_im_release_tup_list
 *            <br>�ͷ�ack�ṹ�е�TUP_S_LIST* �ڴ棬��������ڴ�й©
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_GetConferenceList(IN const IM_S_GETCONFERENCELISTARG* arg, OUT IM_S_GETCONFERENCELISTACK* ack);

/**
 * @brief �ͷ�TUP_S_LIST�ṹ����
 * 
 * @param [in] TUP_S_LIST* list_head  <b>:</b> TUP_S_LIST����ͷ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ����ҵ��API�ӿڷ��ص�*_ACK�ṹ�У����¼�֪ͨIM_E_EVENT_IM_*��Ӧ�����ݽṹ�У�
 *        <br>���ڷǿյ�TUP_S_LIST*��������Ҫ���ô˺���(������ʵ��)������Դ�ͷţ������
 *        <br>���ڴ�й©
 * @see tup_im_getfixedgroupmembers
 * @see tup_im_getcontactlist
 * @see tup_im_getserviceprofile
 * @see tup_im_getfixedgroups
 * @see tup_im_queryHistoryMessage
 * @see tup_im_getdepts
 * @see tup_im_queryentaddressbook
 * @see tup_im_queryuserinfo
 * @see tup_im_GetConferenceList
 * @see IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY 
 * @see IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY
 * @see IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY 
 * @see IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY 
 * @see IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY 
 * @see IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY
 * @see IM_E_EVENT_IM_CHATLIST_NOTIFY 
 **/
TUP_API TUP_RESULT tup_im_release_tup_list(IN TUP_S_LIST* list_head);


/**
 * @brief �ͷ�TUP�ڲ�������ڴ�
 * @param [in] pData ��Ҫ�ͷŵ�ָ��
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 *
 * @attention �������ͷ�TUP IM����ӿڷ��ص��ڴ�
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_release_tup_mem(IN TUP_VOID* pData);

/**
 * @brief ��ȡ����Ự��¼(ͬ���ӿ�)
 * 
 * @param [in] const IM_S_GEL_RECENT_CONVERSATION_ARG* arg  <b>:</b> ��ȡ����Ự����
 * @param [out] IM_S_GEL_RECENT_CONVERSATION_ACK* ack        <b>:</b> ��ȡ����Ự��Ӧ
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ����ҵ��API�ӿڷ��ص�*_ACK�ṹ�У����¼�֪ͨIM_E_EVENT_IM_*��Ӧ�����ݽṹ�У�
 *        <br>���ڷǿյ�TUP_S_LIST*��������Ҫ���ô˺���(������ʵ��)������Դ�ͷţ������
 *        <br>���ڴ�й©
 * @see tup_im_del_recent_conversation
 **/
TUP_API TUP_RESULT tup_im_gel_recent_conversation(IN const IM_S_GEL_RECENT_CONVERSATION_ARG* arg, OUT IM_S_GEL_RECENT_CONVERSATION_ACK* ack);


/**
 * @brief ɾ������Ự(�첽�ӿ�)
 * 
 * @param [in] const IM_S_DEL_RECENT_CONVERSATION_ARG* arg  <b>:</b> ɾ�����»Ự������Ϣ
 * @param [out] result                                      <b>:</b>���β������
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �˺�������ע������������
 * @see tup_im_gel_recent_conversation
 **/
TUP_API TUP_RESULT tup_im_del_recent_conversation(IN const IM_S_DEL_RECENT_CONVERSATION_ARG* arg, OUT TUP_BOOL* result);


#ifdef __cplusplus
#if __cplusplus
}

#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif //_TUP_IM_BASEAPI_H_

/** @}*/

/*
* History: \n
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
