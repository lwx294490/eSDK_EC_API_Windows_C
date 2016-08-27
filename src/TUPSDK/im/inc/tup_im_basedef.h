/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM��ϵͳ�����ӿڽṹ�嶨��ͷ�ļ��� \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_BASEDEF_H_
#define _TUP_IM_BASEDEF_H_

#include "tup_def.h"
#include "tup_im_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

//--------------------------------------------------------------���ȶ��� begin--------------------------------------------------------------

#define IM_D_GENEAL_LENGTH    (32)                              /**< Ĭ�ϳ��� */

#define IM_D_URL_LENGTH    (2048)                               /**< URL��󳤶� */

#define IM_D_ICON_LENGTH    (1024)                              /**< ͼ�곤�� */

#define IM_D_MAX_ACCOUNT_LENGTH (32)                            /**< �ʺų��� */

#define IM_D_MAX_NAME_LENGTH (512)                              /**< �������� */

#define IM_D_MAX_DEPTNAME_LENGTH (1024)                         /**< ���������� */

#define IM_D_MAX_PASSWORD_LENGTH (512)                          /**< ���볤�� */

#define IM_D_MAX_VERSION_LENGTH (100)                           /**< �汾�ų��� */

#define IM_D_MAX_TIMESTAMP_LENGTH (15)                          /**< ʱ������� */

#define IM_D_MAX_PHONE_LENGTH (256)                             /**< ���볤�� */

#define IM_D_MAX_BIRTHDAY_LENGTH (64)                           /**< ���ճ��� */

#define IM_D_MAX_DESC_LENGTH (1024)                             /**< �������ֳ��� */

#define IM_D_MAX_STATUS_DESCLEN (50)                            /**< ״̬�������� */

#define IM_D_IP_LENGTH  (1024)                                  /**< IP��ַ���� */  

#define IM_D_AGE_LENGTH  (8)                                    /**< ���䳤�� */

#define IM_D_GROUPID_LENGTH  (64)                               /**< ȺID���� */

#define IM_D_MAX_MESSAGE_LENGTH (1024*10)                       /**< ��ʱ��Ϣ���ֳ��� */

#define IM_D_MAX_PROGID_LENGTH (1024)                           /**< ���PROGID */

#define IM_D_MAX_PLUGINPARAM_LENGTH (1024)                      /**< ����������� */

#define IM_D_MAX_PLUGINURL_LENGTH (1024)                        /**< �������URL���� */

#define IM_D_LOGIN_TOKEN_LENGTH (1024)                          /**< token ���� */

#define IM_D_MAX_PATH_LENGTH (1024)                             /**< ·������ */

#define IM_D_MAX_CHAR_LENGTH (1024*10)                          /**< �ַ���� ���� */

//--------------------------------------------------------------���ȶ��� end--------------------------------------------------------------

//--------------------------------------------------------------ö�� begin--------------------------------------------------------------
/**
 *  �ص���Ϣ��
 *    ע���е�NOTIFY�ǻص���Ϣ����Ϣ�ṹ��
 */
typedef enum tagIM_E_EVENT_ID
{
    IM_E_EVENT_IM_ORIGIN    = -1,                               /**< ��ʼ�� */
/*******************************************************************��¼��ע��***************************************************************************************/
    IM_E_EVENT_IM_HEARTBEAT_NOTIFY,                             /**< ����������������Ӧ */
    IM_E_EVENT_IM_SYSURLRET_NOTIFY,                             /**< �����ȡϵͳURL��Ϣ��Ӧ    ��Ϣ�ṹ��:IM_S_SYSURLS_NOTIFY */
    IM_E_EVENT_IM_LOGOUT_NOTIFY,                                /**< �û��˳�                    ��Ϣ�ṹ��:IM_S_LOGOUT_NOTIFY */
    IM_E_EVENT_IM_KICKOUT_NOTIFY,                               /**< �û�����֪ͨ                ��Ϣ�ṹ��:IM_S_KICKOUT_NOTIFY */
    IM_E_EVENT_IM_MULTIDEVICE_NOTIFY,                           /**< �û����ն˵�¼/�˳�֪ͨ    ��Ϣ�ṹ��:IM_S_MULTIDEVICE_NOTIFY */
    IM_E_EVENT_IM_GENERAL_NOTIFY,                               /**< �ͻ�����������������ͻ���ͨ�ŵĻỰ֪ͨ            ��Ϣ�ṹ��:IM_S_GENERAL_NOTIFY */

/*******************************************************************��ϵ�������*************************************************************************************/
    IM_E_EVENT_IM_ADDFRIEND_NOTIFY,                             /**< �Է�����Լ����ѳɹ�֪ͨ    ��Ϣ�ṹ��:IM_S_ADDFRIEND_NOTIFY */
    IM_E_EVENT_IM_USERSTATUS_NOTIFY,                            /**< ����״̬�仯֪ͨ            ��Ϣ�ṹ��:IM_S_USERSTATUS_NOTIFY */
    IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY,                        /**< ������Ϣ�仯֪ͨ            ��Ϣ�ṹ��:IM_S_USERINFOCHANGE_LIST_NOTIFY;ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_GETIMGROUPDETAIL,                             /**< ��ȡIMȺ��������Ӧ��Ϣ        ��Ϣ�ṹ��:IM_S_GETIMGROUPDETAIL_NOTIFY ���ѷ���������ʹ�ã�*/

/*******************************************************************�̶�Ⱥ��*****************************************************************************************/
    IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY,           /**< Ⱥ��Ա�յ�����Ա��������̶�Ⱥ֪ͨ����Ӧ    ��Ϣ�ṹ��:IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY,                        /**< �̶�Ⱥ��ӳ�Ա֪ͨ                            ��Ϣ�ṹ��:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY,                        /**< Ⱥ����ɾ����Ա֪ͨ                            ��Ϣ�ṹ��:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_INFOCHG_NOTIFY,                       /**< �̶�Ⱥ��Ϣ�޸�֪ͨ                            ��Ϣ�ṹ��:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_OWNERCHG_NOTIFY,                      /**< Ⱥ�����Ա���֪ͨ                            ��Ϣ�ṹ��:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY,            /**< �û��յ�����Ա����֪ͨ                        ��Ϣ�ṹ��:IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY */
    IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY,                /**< ����Ա�յ��û��������Ⱥ��֪ͨ                ��Ϣ�ṹ��:IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_WASADDEDTOGROUP_NOTIFY,               /**< ����ӵ��̶�Ⱥ֪ͨ                            ��Ϣ�ṹ��:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_DISMISS_NOTIFY,                       /**< �̶�Ⱥ��ɢ֪ͨ                                ��Ϣ�ṹ��:IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_OWNER_INVITE_RESULT_NOTIFY,           /**< ����Ա�յ��û����������̶�Ⱥ�������        ��Ϣ�ṹ��:IM_S_IMGROUP_OWNER_INVITE_RESULT_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_KICKOUT_NOTIFY,                       /**< �û��յ�������Ա����̶�Ⱥ֪ͨ                ��Ϣ�ṹ��:IM_S_IMGROUP_KICKOUT_NOTIFY*/
    IM_E_EVENT_FIXEDGROUP_LEAVE_RESULT_NOTIFY,                  /**< �û������뿪�̶�Ⱥ֪ͨ                        ��Ϣ�ṹ��:IM_S_IMGROUP_LEAVE_RESULT_NOTIFY*/

/*******************************************************************������*******************************************************************************************/
    IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY,        /**< �������Ա�б���ӳ�Ա�����Ϣ        ��Ϣ�ṹ��:IM_S_DISCUSSGROUP_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY,        /**< �������Ա�б�ɾ����Ա�����Ϣ        ��Ϣ�ṹ��:IM_S_DISCUSSGROUP_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY,               /**< ��������Ϣ����                        ��Ϣ�ṹ��:IM_S_DISCUSSGROUP_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY,          /**< ����ӵ�������֪ͨ                    ��Ϣ�ṹ��:IM_S_DISCUSSGROUP_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY,              /**< ���������Ա���                    ��Ϣ�ṹ��:IM_S_DISCUSSGROUP_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_DISCUSSGROUP_DISMISS_NOTIFY,                  /**< �������ɢ֪ͨ                        ��Ϣ�ṹ��:IM_S_DISCUSSGROUP_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_DISCUSSGROUP_OP_NOTIFY,                       /**< �㲥�����������Ϣ                    ��Ϣ�ṹ��:IM_S_SEND_DISGROUP_OPT_MSG, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */

/*******************************************************************�ļ�����****************************************************************************************/
    IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY,                      /**< �յ��ļ���������                    ��Ϣ�ṹ��:IM_S_P2PFILECHOOSE_NOTIFY */
    IM_E_EVENT_IM_FILEPROCESS_NOTIFY,                           /**< �ļ��������֪ͨ                    ��Ϣ�ṹ��:IM_S_FILEPROCESS_NOTIFY */
    IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY,                   /**< �ļ����俪ʼ���                    ��Ϣ�ṹ��:IM_S_P2PFILE_RESULT_NOTIFY */
    IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY,                   /**< �ļ�����ֹͣ���                    ��Ϣ�ṹ��:IM_S_P2PFILE_RESULT_NOTIFY */
    IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY,                          /**< �ļ�����ֹ֪ͣͨ                    ��Ϣ�ṹ��:IM_S_P2PFILESTATISTIC_NOTIFY */

/*********************************************************************IM��Ϣ****************************************************************************v*************/
    IM_E_EVENT_IM_SENDIMINPUT_NOTIFY,                           /**< �յ������û�����״̬��Ϣ        ��Ϣ�ṹ��:IM_S_SENDIMINPUT_NOTIFY */    
    IM_E_EVENT_IM_CODECHAT_NOTIFY,                              /**< �¼�ʱ��Ϣ֪ͨ                 ��Ϣ�ṹ��:IM_S_CODECHAT_NOTIFY */    
    IM_E_EVENT_IM_CHATLIST_NOTIFY,                              /**< �¼�ʱ��Ϣ����֪ͨ(����)         ��Ϣ�ṹ��:IM_S_CHATLIST_NOTIFY, ע��:��Ҫ����tup_im_release_tup_list�ͷŽṹ�е�TUP_S_LIST* �ڴ� */
    IM_E_EVENT_IM_SYSTEMBULLETIN_NOTIFY,                        /**< ϵͳ����֪ͨ                    ��Ϣ�ṹ��:IM_S_SYSTEMBULLETIN_NOTIFY */
    IM_E_EVENT_IM_SMS_NOTIFY,                                   /**< �¶���֪ͨ                        ��Ϣ�ṹ��:IM_S_SENDSMS_NOTIFY */
    IM_E_EVENT_IM_UNDELIVER_NOTIFY,                             /**< ������Ϣδ�ʹ���з��ͷ��У�    ��Ϣ�ṹ��:IM_S_UNDELIVER_NOTIFY */
    IM_E_EVENT_IM_MSG_READ_NOTIFY,                              /**< ������Ϣ�Ѷ�֪ͨ����˵�¼��		��Ϣ�ṹ��:IM_S_MSG_READ_NOTIFY */
	IM_E_EVENT_IM_MSG_SENDACK_NOTIFY,							/**< ������Ϣ���ͽ��֪ͨ				��Ϣ�ṹ��:IM_S_SENDACK_NOTIFY */

/*********************************************************************Ⱥ�����ļ�****************************************************************************v*************/
    IM_E_EVENT_IM_GROUPFILE_NOTIFY,                             /**< Ⱥ�����ļ����֪ͨ                ��Ϣ�ṹ��: IM_S_GROUPFILE_NOTIFY*/

}IM_E_EVENT_ID;




/**
 *  ��¼��Ȩ����
 */
typedef enum tagIM_E_LOGIN_AUTHTYPE
{
    IM_E_LOGIN_AUTHTYPE_BYPASSWORD                          = 1,    /**< �����Ȩ */
    IM_E_LOGIN_AUTHTYPE_BYFINGER                            = 2,    /**< ָ�Ƽ�Ȩ */
    IM_E_LOGIN_AUTHTYPE_BYTHIRDPARTY                        = 3     /**< ��������Ȩ */
}IM_E_LOGIN_AUTHTYPE;


/**
 *  ��¼���������0�����Ƿ���������С��0�ǿͻ����ڲ����� 
 */
typedef enum tagIM_E_LOGIN_RESUL
{
    IM_E_LOGING_RESULT_TIMEOUT                              = -100,  /**< ��Ϣ��ʱ */
    IM_E_LOGING_RESULT_SERVERNOTALLOW                       = -2,    /**< �������¼�÷����� */
    IM_E_LOGING_RESULT_INTERNAL_ERROR                       = -1,    /**< �����ڲ����� */
    IM_E_LOGING_RESULT_SUCCESS                              = 0,     /**< ��¼�ɹ� */
    IM_E_LOGING_RESULT_FAILED                               = 1,     /**< ��¼ʧ�� */
    IM_E_LOGING_RESULT_PASSWORD_ERROR                       = 2,     /**< ������� */
    IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST                    = 3,     /**< �ʺŲ����� */
    IM_E_LOGING_RESULT_ALREADY_LOGIN                        = 4,     /**< �û��ѵ�¼ ����¼��Ȼ�ɹ��������Ѿ���¼���ն���ʾ�������ߣ�*/          
    IM_E_LOGING_RESULT_ACCOUNT_LOCKED                       = 5,     /**< �ʺű����� */
    IM_E_LOGING_RESULT_NEED_NEW_VERSION                     = 6,     /**< ��Ҫ�����°汾�������¼ */
    IM_E_LOGING_RESULT_NOT_ACTIVE                           = 7,     /**< �û�δ���� */
    IM_E_LOGING_RESULT_ACCOUNT_SUSPEND                      = 8,     /**< �û��˺ű���ͣʹ�� */
    IM_E_LOGING_RESULT_ACCOUNT_EXPIRE                       = 9,     /**< �û��˺Ź��� */
    IM_E_LOGING_RESULT_DECRYPT_FAILED                       = 10,    /**< ��Ϣ����ʧ�� */
    IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED                 = 11,    /**< ֤������ʧ�� */
    IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED                 = 12,    /**< ֤��У��ʧ�� */
    IM_E_LOGING_RESULT_DNS_ERROR                            = 13,    /**< ������������ */
    IM_E_LOGING_RESULT_SYSTEM_ERROR                         = 14,    /**< ϵͳ���� */
    IM_E_LOGING_RESULT_TICKET_EXPIRE                        = 15,    /**< ���ƹ��ڣ�������ָ��������Ȩ��¼��ticket��*/
    IM_E_LOGING_RESULT_TICKET_NOT_EXIST                     = 16,    /**< ���Ʋ����ڣ�������ָ��������Ȩ��¼��ticket�� */
    IM_E_LOGING_RESULT_TICKET_SUSPEND                       = 17,    /**< �����ѽ��� ��������ָ��������Ȩ��¼��ticket��*/
    IM_E_LOGING_RESULT_TICKET_ERROR                         = 18,    /**< ������֤���� ��������ָ��������Ȩ��¼��ticket��*/
    IM_E_LOGING_RESULT_TICKET_FLUID_EXCEED                  = 19,    /**< ������������ */
    IM_E_LOGING_RESULT_TICKET_FLUID_ERROR                   = 20,    /**< ���������쳣 */
    IM_E_LOGING_RESULT_TICKET_REDIRECT_ERROR                = 21     /**< �ض����쳣 */
}IM_E_LOGIN_RESULT;

/**
 *  ���ܷ�ʽ 
 */
typedef enum tagIM_E_LOGIN_ENCRYPT_TYPE
{
    IM_E_LOGIN_ENCRYPT_TYPE_NONE = 0,   /**< ������ */
    IM_E_LOGIN_ENCRYPT_TYPE_NORMAL = 1, /**< ��������λ��ʽ���� */
    IM_E_LOGIN_ENCRYPT_TYPE_PKI = 2,    /**< PKI���� */
    IM_E_LOGIN_ENCRYPT_TYPE_AES_ECB = 3,/**< PKI+AES����(ECB) */
    IM_E_LOGIN_ENCRYPT_TYPE_AES_CBC = 4, /**< PKI+AES����(CBC) */
} IM_E_LOGIN_ENCRYPT_TYPE;

/**
 *  �Ա�����
 */
typedef enum tagIM_E_GENDER_TYPE
{
    IM_E_GENDER_MALE                                        = 0,    /**< �� */
    IM_E_GENDER_FEMAIL                                      = 1,    /**< Ů*/
    IM_E_GENDER_UNKNOWN                                     = 2     /**< δ֪ */
}IM_E_GENDER_TYPE;


/**
 *  ����Ⱥ����֤��ʽ
 */
typedef enum tagIM_E_IMGROUP_JOIN_AUTH_FLAG
{
    IM_E_IMGROUP_JOIN_AUTO                                  = 0,    /**< �Զ����� */
    IM_E_IMGROUP_JOIN_NEED_APPROVE                          = 1,    /**< ��Ҫ����Ա���� */
    IM_E_IMGROUP_JOIN_DENY                                  = 2     /**< ��������� */
}IM_E_IMGROUP_JOIN_AUTH_FLAG;


/**
 *  Ⱥ����Ϣ��ʾ����
 */
typedef enum  tagIM_E_IMGROUP_MSGPOLICY_TYPE 
{
    IM_E_IMGROUP_NOSHOW_GROUPMSG_TIP                        = 0,    /**< ���յ��ǲ���ʾȺ����Ϣ*/
    IM_E_IMGROUP_SHOW_GROUPMSG_TIP                          = 1,    /**< ���ղ���ʾȺ����Ϣ*/
    IM_E_IMGROUP_SHOW_GROUPMSG_NOREAD                       = 2     /**< ���ղ���ʾδ��*/
}IM_E_IMGROUP_MSGPOLICY_TYPE; 
 

/**
 *  Ⱥ������
 */
typedef enum tagIM_E_IMGROUP_TYPE
{
    IM_E_IMGROUP_FIXGROUP_TYPE                              = 0,    /**< �̶�Ⱥ */
    IM_E_IMGROUP_DISCUSSIONGROUP_TYPE                       = 1     /**< ������ */
}IM_E_IMGROUP_TYPE;


/**
 *  �Ƿ�̻�Ⱥ����
 */
typedef enum tagIM_E_IMGROUP_ISFIXDISCUSS 
{
    IM_E_IMGROUP_NOTSAVETOLIST                              = 0,    /**< ����̻�Ⱥ�� */
    IM_E_IMGROUP_SAVETOLIST                                 = 1,    /**< �̻�Ⱥ�� */
}IM_E_IMGROUP_ISFIXDISCUSS;

/**
 *  �������������
 */
typedef enum tagIM_E_DISGROUP_OP_TYPE
{
    IM_E_DISGROUP_OP_TYPE_ADD                               = 0,    /**< ��ӳ�Ա */
    IM_E_DISGROUP_OP_TYPE_DEL                               = 1,    /**< ɾ����Ա */
}IM_E_DISGROUP_OP_TYPE;

/**
 *  �û�����״̬
 */
typedef enum tagIM_E_USER_ONLINESTATUS
{
    IM_E_STATUS_INIT                                        = -1,   /**< ��ʼ״̬ */
    IM_E_STATUS_OFFLINE                                     = 0,    /**< ���� */
    IM_E_STATUS_ONLINE                                      = 1,    /**< ���� */
    IM_E_STATUS_HIDDEN                                      = 2,    /**< ���� */
    IM_E_STATUS_BUSY                                        = 3,    /**< æµ */
    IM_E_STATUS_LEAVE                                       = 4,    /**< �뿪 */
    IM_E_STATUS_DONTDISTURB                                 = 5     /**< ������� */
}IM_E_USER_ONLINESTATUS;


/**
 *  �ͻ������� */
typedef enum tagIM_E_CLIENT_TYPE 
{
    IM_E_CLIENT_TYPE_PC                                     = 0,    /**< PC�ն� */
    IM_E_CLIENT_TYPE_MOBILE                                 = 1,    /**< �ƶ��ֻ��ն� */
    IM_E_CLIENT_TYPE_WEB                                    = 2,    /**< web�ͻ��� */
    IM_E_CLIENT_TYPE_MOBLIEHD                               = 3     /**< �ƶ�PC�ն� */
}IM_E_CLIENT_TYPE;

/**
 *  �ͻ��˲����¼����� */
typedef enum tagIM_E_CLIENT_OPT_TYPE 
{
    IM_E_CLIENT_OPT_LOGIN                                   = 1,    /**< ��¼ */
    IM_E_CLIENT_OPT_LOGOUT                                  = 2,    /**< ע�� */
}IM_E_CLIENT_OPT_TYPE ;

/**
 *  IM��Ϣ���ʹ�����
 */
typedef enum tagIM_E_IM_CHAT_SOURCE_FLAG
{
    IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG                      = 0,    /**< IM���촰�� */
    IM_E_IM_CHAT_SOURCE_FLAG_MULTIMEETING                   = 1     /**< ���ݻ������촰�� */
}IM_E_IM_CHAT_SOURCE_FLAG;

/**
 *  IM��Ϣ���ݸ�ʽ
 */
typedef enum tagIM_E_IM_CHAT_CONTENT_TYPE 
{
    IM_E_IM_CHAT_CONTENT_TYPE_TEXT                          = 0,    /**< ���ı� */
    IM_E_IM_CHAT_CONTENT_TYPE_RICHTEXT                      = 1     /**< ���ı� */
}IM_E_IM_CHAT_CONTENT_TYPE;

/**
 *  IM��������״̬
 */
typedef enum tagIM_E_IM_CHAT_STATUS
{
    IM_E_IM_CHAT_STATUS_CHATTING                            = 0,    /**< �������� */
    IM_E_IM_CHAT_STATUS_STOPPED                             = 1     /**< ֹͣ���� */
}IM_E_IM_CHAT_STATUS;

/**
 *  IM��Ϣ����
 */
typedef enum tagIM_E_IM_CHAT_TYPE
{
    IM_E_IM_CHAT_TYPE_SINGLE                                = 0,    /**< ���� */
    IM_E_IM_CHAT_TYPE_TEMP                                  = 1,    /**< ��ʱ���� */
    IM_E_IM_CHAT_TYPE_FIXEDGROUP                            = 2,    /**< �̶�Ⱥ�� */
    IM_E_IM_CHAT_TYPE_TEMPGROUP                             = 3,    /**< ��ʱȺ�� */
    IM_E_IM_CHAT_TYPE_HELP                                  = 4,    /**< ���߿ͷ� */
    IM_E_IM_CHAT_TYPE_APPNOTIFY                             = 5,    /**< ������Ϣ */
    IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP                       = 6,    /**< ���˻Ự������ */
    IM_E_IM_CHAT_TYPE_FILETRANSFER                          = 7,    /**< �ļ�����֪ͨ */
    IM_E_IM_CHAT_TYPE_SYSTEMNOTIFY                          = 10,   /**< ϵͳ֪ͨ */
    IM_E_IM_CHAT_TYPE_SYSTEMAD                              = 11,   /**< ϵͳ��� */
    IM_E_IM_CHAT_TYPE_MULTIMEETINGS                         = 14,   /**< �ںϻ���֪ͨ */
    IM_E_IM_CHAT_TYPE_IMNOTIFY                              = 20,   /**< IM֪ͨ��Ϣ */
    IM_E_IM_CHAT_TYPE_AUTOREPLAY                            = 101   /**< �Զ��ظ� */
}IM_E_IM_CHAT_TYPE;

/**
 *  IMý���ʽ
 */
typedef enum tagIM_E_IM_CHATMEDIA_TYPE
{
    tagIM_E_IM_CHATMEDIA_TYPE_TEXT                          = 0,    /**< ���ı� */
    tagIM_E_IM_CHATMEDIA_TYPE_AUDIO                         = 1,    /**< ��ý�� ���� */
    tagIM_E_IM_CHATMEDIA_TYPE_VIDEO                         = 2,    /**< ��ý�� ��Ƶ */
    tagIM_E_IM_CHATMEDIA_TYPE_IMAGE                         = 3,    /**< ��ý�� ͼƬ */
    tagIM_E_IM_CHATMEDIA_TYPE_FILE                          = 4,    /**< ��ý�� �ļ� */
    tagIM_E_IM_CHATMEDIA_TYPE_PUBLIC                        = 5,    /**< ��ý�� ���ں� */
    tagIM_E_IM_CHATMEDIA_TYPE_CARDSHARE                     = 7,    /**< ��ý�� ��Ƭ���� */
    tagIM_E_IM_CHATMEDIA_TYPE_IMAGETEXT                     = 8     /**< ��ý�� ��ͼ�Ļ��� */
}IM_E_IM_CHATMEDIA_TYPE;

/**
 *  ��ѯ��ʷ��¼��Ϣ����
 */
typedef enum tagIM_E_IM_HISTORYMESSAGEMSG_TYPE 
{
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_SINGLECHAT               = 0,    /**< ������Ϣ */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_GROUPCHAT                = 1,    /**< ������/�̶�Ⱥ��Ϣ */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_SMS                      = 2,    /**< ������Ϣ */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_BULLETIN                 = 3,    /**< ϵͳ���� */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE_NOTIFY                   = 4     /**< ������P2P�ļ����䣬�������룬Ⱥ�����룬Ⱥ��֪ͨ�� */
}IM_E_IM_HISTORYMESSAGEMSG_TYPE;

/** 
 * �ͻ�����������������ͻ���ͨ�ŵĻỰ֪ͨ ��100+Ϊ�ͻ����Զ��壩
 */
typedef enum tagIM_E_IM_GENERAL_NOTIFY_TYPE
{
    IM_E_IM_GENERAL_NOTIFY_TYPE_UNALLOWED                   = 1,    /**< û��Ȩ��*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_SESSION_NOTFOUND            = 2,    /**< ����������ĻỰ�����ڣ�ע��״̬��*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_CONFIG_CHANGED              = 10,   /**< ������������Ϣ���*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_MULTIMEDIA_INFO             = 100,  /**< ���ݻ���ʹ�õ�֪ͨ��Ϣ */
    IM_E_IM_GENERAL_NOTIFY_TYPE_DISGROUP_NOTIFY             = 101,  /**< ��������ص�֪ͨ��Ϣ����ת����*/
    IM_E_IM_GENERAL_NOTIFY_TYPE_AUDIO_STATUS                = 102,  /**< ����״̬֪ͨ��Ϣ */
}IM_E_IM_GENERAL_NOTIFY_TYPE;

/**
 *  ���յ��Ķ�����Ϣ������
 */
typedef enum tagIM_E_SMS_NOTIFY_TYPE
{
    IM_E_SMS_NOTIFY_TYPE_RECVSMS                            = 0,    /**< �յ�����֪ͨ*/
    IM_E_SMS_NOTIFY_TYPE_SENDSMSSUCCESS                     = 1,    /**< ���Ͷ��ųɹ�֪ͨ*/
    IM_E_SMS_NOTIFY_TYPE_SMSRECEIPT                         = 3,    /**< ���Ż�ִ�ɹ�֪ͨ*/
    IM_E_SMS_NOTIFY_TYPE_SMSSENDFAIL                        = 4,    /**< ���ŷ���ʧ��*/
    IM_E_SMS_NOTIFY_TYPE_SMSRECEIPTFAIL                     = 5,    /**< ���Ż�ִʧ��֪ͨ*/
    IM_E_SMS_NOTIFY_TYPE_SMSSEND                            = 6     /**< ���Ͷ��ţ���������ʱʹ�ã�*/
}IM_E_SMS_NOTIFY_TYPE;

/**
 *  ��ʷ��Ϣ��������
 */
typedef enum tagIM_E_IM_HISTORYMESSAGEOP_TYPE 
{
    IM_E_IM_HISTORYMESSAGEOP_TYPE_QUERYBEFORE               = 0,    /**< ��ѯMsgID֮ǰ����Ϣ */
    IM_E_IM_HISTORYMESSAGEOP_TYPE_FIRSTQUERY                = 1        /**< �״β�ѯ������ҪMsgID */
}IM_E_IM_HISTORYMESSAGEOP_TYPE ;

/**
 *  Ⱥ���ѯ����
 */
typedef enum tagIM_E_IMGROUPQUERYTYPE
{
    IM_E_IMGROUPQUERYTYPE_BY_NAME                           = 0,    /**< �����Ʋ�ѯ */
    IM_E_IMGROUPQUERYTYPE_BY_ID                             = 1,    /**< ��Ⱥ��ID��ѯ */
    IM_E_IMGROUPQUERYTYPE_BY_NAME_ID                        = 2     /**< �����ƺ�ID��ѯ */
}IM_E_IMGROUPQUERYTYPE;

/**
 *  ��ѯ�û���Ϣ�Ĺؼ�������
 */
typedef enum tagIM_E_IMUSERQUERYTYPE
{
    IM_E_IMUSERQUERYTYPE_BY_PHONE                           = 0,    /**< ���� */
    IM_E_IMUSERQUERYTYPE_BY_ACCOUNT                         = 1,    /**< �ʺ� */
    IM_E_IMUSERQUERYTYPE_BY_BINDNO                          = 2,    /**< �󶨺��� */
    IM_E_IMUSERQUERYTYPE_BY_EMAIL                           = 3,    /**< ���� */
    IM_E_IMUSERQUERYTYPE_BY_STAFFNO                         = 4     /**< ���� */
}IM_E_IMUSERQUERYTYPE;

/**
 *  Ⱥ��������
 */
typedef enum tagIM_E_FIXEDGROUP_OP_RESULT
{
    IM_E_FIXEDGROUP_OP_RESULT_SUCCESS                       = 0,    /**< �����ɹ� */
    IM_E_FIXEDGROUP_OP_RESULT_FAILED                        = 1,    /**< ����ʧ�� */
    IM_E_FIXEDGROUP_OP_RESULT_NOT_EXIST                     = 3,    /**< Ⱥ�鲻���� */
    IM_E_FIXEDGROUP_OP_RESULT_REACH_MAXIMUM                 = 32,   /**< ��ԱȺ����Ŀ�Ѿ��ﵽ��� */            
    IM_E_FIXEDGROUP_OP_RESULT_MEMBER_REACH_MAXIMUM          = 33,   /**< ���ڳ�Ա�ﵽ�����Ŀ */            
    IM_E_FIXEDGROUP_OP_RESULT_DB_ERROR                      = 34,   /**< ���ݿ��쳣�ķ����� */        
    IM_E_FIXEDGROUP_OP_RESULT_DISCUSSIONGROUP_REACH_MAXIMUM = 35    /**< ��Ա��������Ŀ�Ѿ��ﵽ��� */        
}IM_E_FIXEDGROUP_OP_RESULT;

/**
 *  ת�ƺ���/��ϵ�˲�������
 */
typedef enum tagIM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE
{
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_MOVE               = 0,    /**< �ƶ����·��� */
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_COPY               = 1     /**< ���Ƶ��·��� */
}IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE;

/**
 *  ��ҵͨѶ¼��ѯ�����������
 */
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERTYPE
{
    IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN                  = 0,    /**< ��ƴ������ */
    IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_STAFFNO                 = 1,    /**< �����ź����� */
    IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_NATIVENAME              = 3     /**< ��nativename����  */
}IM_E_ADDRBOOKQUERY_ORDERTYPE;

/**
 *  ��ҵͨѶ¼��ѯ�������ʽ
 */
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERMODEL
{
    IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC                    = 0,    /**< ���� */
    IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_DESC                   = 1     /**< ���� */
}IM_E_ADDRBOOKQUERY_ORDERMODEL;

/**
 *  �û���������ԭ��
 */
typedef enum tagIM_E_EXITSTATUS
{
    IM_E_EXITSTATUS_NORMALOFFLINE                           = 0,    /**<�������ն��ϵ�¼�����˱������� */
    IM_E_EXITSTATUS_PAUSEOFFLINE                            = 2,    /**<�˺ű��������ͣ������ */
    IM_E_EXITSTATUS_OVERDUEOFFLINE                          = 3     /**<�˺Ź������� */
}IM_E_EXITSTATUS;

/**
 *  ���/����̨��嵱ǰ״̬
 */
typedef enum tagIM_E_SYNC_TYPE
{
    IM_E_SYNC_TYPE_VALID                                    = 0,    /**< ��Ч */
    IM_E_SYNC_TYPE_INVALID                                  = 1     /**< ��Ч */
}IM_E_SYNC_TYPE;

/**
 * �뿪Ⱥ�鷽ʽ
 */
typedef enum  tagIM_E_LEAVEGROUP_FLAG 
{
    IM_E_LEAVEGROUP                                         = 0,    /**< �����뿪 */
    IM_E_KICKEDOUT                                          = 1     /**< ���� */
}IM_E_LEAVEGROUP_FLAG;

/**
 * δ�ʹ���Ϣ����
 */
typedef enum tagIM_E_UNDELIVER_MSG_TYPE
{
    IM_E_UNDELIVER_MSG_NOTALLOW                             = 1,    /**< �з������з������ܻ�ͨ */
    IM_E_UNDELIVER_MSG_EXCEEDLIMIT                          = 2     /**< ��������Ϣ���ͳ�����С���� */
}IM_E_UNDELIVER_MSG_TYPE;

/**
 * �뿪Ⱥ����
 */
typedef enum tagIM_E_LEAVEGROUP_RESULT 
{
    IM_E_LEAVEGROUP_SUCCESS                                 = 0,    /**< �ɹ� */
    IM_E_LEAVEGROUP_FAILED                                  = 1,    /**< ʧ�� */
    IM_E_LEAVEGROUP_ACCOUNT_NOT_EXIST                       = 3     /**< �˺Ų����� */
}IM_E_LEAVEGROUP_RESULT;

   
/**
 *  ����Ự����
 */
typedef enum tagIM_E_IM_RECENT_CONVERSATION_TYPE 
{
    IM_E_IM_RECENT_CONVERSATION_TYPE_SINGLE_CHAT            = 0,    /**< ������Ϣ */
    IM_E_IM_RECENT_CONVERSATION_TYPE_AUDIO                  = 1,    /**< ���� */
    IM_E_IM_RECENT_CONVERSATION_TYPE_GROUP_CHAT             = 2,    /**< �̶�Ⱥ��Ϣ */
    IM_E_IM_RECENT_CONVERSATION_TYPE_BULLETIN               = 3,    /**< ϵͳ���� */
    IM_E_IM_RECENT_CONVERSATION_TYPE_OFFICAL_ACCOUNTS       = 4,    /**< ���ں�*/
    IM_E_IM_RECENT_CONVERSATION_TYPE_SMS                    = 5,    /**< ������Ϣ */
    IM_E_IM_RECENT_CONVERSATION_TYPE_DISSUCSS_CHAT          = 6     /**< ������Ⱥ��*/
}IM_E_IM_RECENT_CONVERSATION_TYPE;

//--------------------------------------------------------------ö�� end--------------------------------------------------------------

//--------------------------------------------------------------�����ṹ�� begin--------------------------------------------------------------

/**
 *  �����˺���Ϣ���û�
 */
typedef struct tagIM_S_USERINFO
{
    TUP_INT64    staffID;                                           /**< staffID */
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< ��Ա�˺� */ 
    TUP_CHAR    staffNO[IM_D_MAX_ACCOUNT_LENGTH];                   /**< ��Ա���� */ 
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< �û��� */
    TUP_CHAR    nativeName[IM_D_MAX_NAME_LENGTH];                   /**< �������� */
    TUP_CHAR    qPinYin[IM_D_MAX_NAME_LENGTH];                      /**< ȫƴ    */
    IM_E_GENDER_TYPE    gender;                                     /**< �Ա� */
    TUP_CHAR    birthday[IM_D_MAX_BIRTHDAY_LENGTH];                 /**< ���� */
    TUP_CHAR    age[IM_D_AGE_LENGTH];                               /**< ���� */
    TUP_CHAR    bindNO[IM_D_MAX_PHONE_LENGTH];                      /**< �󶨺��� */
    TUP_CHAR    mobile[IM_D_MAX_PHONE_LENGTH];                      /**< �ֻ����� */
    TUP_CHAR    homePhone[IM_D_MAX_PHONE_LENGTH];                   /**< ��ͥ�绰 */
    TUP_CHAR    officePhone[IM_D_MAX_PHONE_LENGTH];                 /**< �칫�绰 */
    TUP_CHAR    shortPhone[IM_D_MAX_PHONE_LENGTH];                  /**< �̺� */
    TUP_CHAR    otherPhone[IM_D_MAX_PHONE_LENGTH];                  /**< �����绰 */
    TUP_CHAR    voip[IM_D_MAX_PHONE_LENGTH];                        /**< VOIP���� */
    TUP_CHAR    ipPhone[IM_D_MAX_PHONE_LENGTH];                     /**< ��IPPhone���� */
    TUP_CHAR    fax[IM_D_MAX_PHONE_LENGTH];                         /**< ���� */
    TUP_CHAR    email[IM_D_MAX_DESC_LENGTH];                        /**< email��ַ */
    TUP_CHAR    webSite[IM_D_MAX_DESC_LENGTH];                      /**< ������վ */
    TUP_CHAR    signature[IM_D_MAX_DESC_LENGTH];                    /**< �û�ǩ�� */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**< ���� */
    TUP_CHAR    address[IM_D_MAX_DESC_LENGTH];                      /**< ��ַ */
    TUP_CHAR    imageID[IM_D_MAX_DESC_LENGTH];                      /**< ͷ��ID */
    TUP_CHAR    postalcode[IM_D_MAX_DESC_LENGTH];                   /**< �������� */
    TUP_BOOL    isSecrecy;                                          /**< �Ƿ��Ǳ��ܳ�Ա */
    TUP_CHAR    title[IM_D_MAX_DESC_LENGTH];                        /**< ְ�� */
    TUP_CHAR    deptID[IM_D_MAX_DEPTNAME_LENGTH];                   /**< ����ID */
    TUP_CHAR    deptNameEn[IM_D_MAX_NAME_LENGTH];                   /**< ����Ӣ������ */
    TUP_CHAR    deptNameCn[IM_D_MAX_NAME_LENGTH];                   /**< ������������ */
    TUP_CHAR    imageSyncTime[IM_D_MAX_TIMESTAMP_LENGTH];           /**< ͷ��ͬ��ʱ��� */
    TUP_CHAR    oldAccount[IM_D_MAX_ACCOUNT_LENGTH];                /**< ���˺� */
    TUP_CHAR    state[IM_D_MAX_DESC_LENGTH];                        /**< ��ְ״̬ 0����ְ��1����ְ */
    TUP_CHAR    modifyTime[IM_D_MAX_TIMESTAMP_LENGTH];              /**< ������ʱ�� */
}IM_S_USERINFO;

/**
 *  ��ϵ����Ϣ
 *  @brief ��ϵ�˰�����1.ӵ���˺���Ϣ���û�;2.û���˺ŵ��Զ�����ϵ��
 *  @attention �Զ�����ϵ�˵�staffIDΪ0��ӵ���˺���Ϣ���û�����Ч��staffID
 */
typedef struct tagIM_S_CONTACTNFO
{    
    TUP_INT64    id;                                                /**< ����ID */
    TUP_INT64    staffID;                                           /**< staffID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ���� */
    TUP_CHAR    nickName[IM_D_MAX_NAME_LENGTH];                     /**< �ǳ� */
    TUP_CHAR    foreignName[IM_D_MAX_NAME_LENGTH];                  /**< Ӣ���� */
    TUP_CHAR    birthday[IM_D_MAX_BIRTHDAY_LENGTH];                 /**< ���� */
    IM_E_GENDER_TYPE gender;                                        /**< �Ա� */
    TUP_CHAR    corpName[IM_D_MAX_NAME_LENGTH];                     /**< ��˾�� */
    TUP_CHAR    deptName[IM_D_MAX_NAME_LENGTH];                     /**< �������� */
    TUP_CHAR    title[IM_D_MAX_DESC_LENGTH];                        /**< ͷ�� */
    TUP_CHAR    mobile[IM_D_MAX_PHONE_LENGTH];                      /**< �ֻ��� */
    TUP_CHAR    officePhone[IM_D_MAX_PHONE_LENGTH];                 /**< �칫���� */
    TUP_CHAR    homePhone[IM_D_MAX_PHONE_LENGTH];                   /**< ��ͥ�绰 */
    TUP_CHAR    otherPhone[IM_D_MAX_PHONE_LENGTH];                  /**< �������� */
    TUP_CHAR    fax[IM_D_MAX_PHONE_LENGTH];                         /**< ���� */
    TUP_CHAR    email[IM_D_MAX_DESC_LENGTH];                        /**< �������� */
    TUP_CHAR    webSite[IM_D_MAX_DESC_LENGTH];                      /**< ��ҳ */
    TUP_CHAR    imNO[IM_D_MAX_DESC_LENGTH];                         /**< ���칤�ߺ��� */
    TUP_CHAR    address[IM_D_MAX_DESC_LENGTH];                      /**< ��ַ */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**< ���� */
    TUP_CHAR    postalcode[IM_D_MAX_DESC_LENGTH];                   /**< �ʱ� */
    TUP_CHAR    state;                                              /**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_CONTACTNFO;

/**
 *  ���ѷ�����Ϣ
 */
typedef struct tagIM_S_USERGROUPINFO
{
    TUP_INT64    id;                                                /**< ��ID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ������ */
    TUP_INT64    index;                                             /**< ����� */
    TUP_CHAR    state;                                              /**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_USERGROUPINFO;

/**
 *  ���ѷ�������ڳ�Ա��Ӧ��ϵ
 */
typedef struct tagIM_S_USERGROUPMEMBERINFO
{
    TUP_INT64    groupID;                                           /**< ���ѷ���ID */
    TUP_INT64    contactID;                                         /**< ���ѷ����ԱID�����ṹ��IM_S_CONTACTNFO��id�ֶ� */
    TUP_CHAR    state;                                              /**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_USERGROUPMEMBERINFO;

/**
 *  �̶�Ⱥ��ϸ��Ϣ
 */
typedef struct tagIM_S_IMGROUPINFO
{
    TUP_CHAR    id[IM_D_GROUPID_LENGTH];                            /**<  ȺID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**<  Ⱥ���� */
    TUP_INT32    capacity;                                          /**<  Ⱥ��С */
    TUP_CHAR    manifesto[IM_D_MAX_DESC_LENGTH];                    /**<  ���� */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**<  ��� */
    TUP_CHAR    owner[IM_D_MAX_ACCOUNT_LENGTH];                     /**<  ����Ա */
    IM_E_IMGROUP_JOIN_AUTH_FLAG    autoJoinFlag;                    /**<  ����Ⱥ�Ƿ�������� */
    IM_E_IMGROUP_MSGPOLICY_TYPE msgpolicyType;                      /**<  Ⱥ����Ϣ���� */
    IM_E_IMGROUP_TYPE groupType;                                    /**<  �̶�Ⱥ���������� */
    IM_E_IMGROUP_ISFIXDISCUSS fixdiscuss;                           /**<  �������Ƿ�̻� */
    TUP_CHAR    state[IM_D_GENEAL_LENGTH];                          /**<  ״̬:'0'��Ч����1����Ч*/
}IM_S_IMGROUPINFO;

/**
 *  ��ȡ�̶�Ⱥ���������Ա�б���Ӧ
 */
typedef struct tagIM_S_GROUPUSERLIST
{
    TUP_BOOL  isSyncAll;                                            /**<  �Ƿ�ȫ��ͬ�� */
    TUP_CHAR  timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];                 /**<  ͬ��ʱ�����19000000000000��������ʱ���룩 */
    TUP_CHAR  groupID[IM_D_GROUPID_LENGTH];                         /**<  ȺID */
    TUP_S_LIST*    memberInfo;                                      /**<  ��Ա��Ϣ TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERINFO */
}IM_S_GROUPUSERLIST;

/**
 *  ������Ϣ
 */
typedef struct tagIM_S_DEPTINFO
{
    TUP_INT64    deptID;                                            /**< ����ID */
    TUP_INT64    parentDeptID;                                      /**< �ϼ�����ID */
    TUP_INT64    deptLevel;                                         /**< ���Ų㼶 */
    TUP_CHAR    deptName[IM_D_MAX_DEPTNAME_LENGTH];                 /**< �������� */
    TUP_CHAR    fullDeptName[IM_D_MAX_DEPTNAME_LENGTH];             /**< ����ȫ�� */
}IM_S_DEPTINFO;

/**
 *  ��¼����
 */
typedef struct tagIM_S_LOGIN_ARG
 {
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< �ʺ�(�˺ŵ�½ʱ����) */
    TUP_CHAR    password[IM_D_MAX_PASSWORD_LENGTH];                 /**< ����(�˺ŵ�½ʱ����) */
    TUP_CHAR    version[IM_D_MAX_VERSION_LENGTH];                   /**< �汾��(���Ĭ��ֵ"0.0.0.0") */
    IM_E_LOGIN_AUTHTYPE    authType;                                /**< ��½ʹ�õļ�Ȩ���� (ѡ�Ĭ��Ϊ�˺ŵ�½)*/
    TUP_CHAR    language[IM_D_GENEAL_LENGTH];                       /**< ��¼���� (ѡ� Ĭ��ֵ"zh-cn")*/
    TUP_CHAR    clientDesc[IM_D_GENEAL_LENGTH];                     /**< �ͻ�������(PC/VDI) (ѡ�Ĭ��ֵ"PC")*/
    TUP_CHAR    ticket[IM_D_MAX_DESC_LENGTH];                       /**< ��������Ȩticket (��Ȩ��½ʱ����)*/
 }IM_S_LOGIN_ARG;

/**
 *  ��¼��Ӧ
 */
typedef struct tagIM_S_LOGIN_ACK
 {
    TUP_BOOL    result;                                             /**< ��¼��� */
    IM_E_LOGIN_RESULT    reason;                                    /**< ��¼������飨������resultΪfalse��ʱ���ȡʧ��ԭ�� */
    TUP_INT32    retryTimes;                                        /**< ��¼����ʣ�����(resultΪIM_E_LOGING_RESULT_ACCOUNT_LOCKED��Ч) */
    TUP_INT32    lockInterval;                                      /**< �ʺű�����ʣ��ʱ�䣨��λ�����ӣ� (resultΪIM_E_LOGING_RESULT_ACCOUNT_LOCKED��Ч*/
    TUP_CHAR    token[IM_D_MAX_DESC_LENGTH];                        /**< �ͻ��˽���HTTP����ļ�Ȩ�ַ��� */
    TUP_INT32    regionID;                                          /**< ����ID */
    TUP_CHAR    lastLoginIP[IM_D_IP_LENGTH];                        /**< ��һ�ε�¼�ķ�����IP */
    TUP_CHAR    lastLoginTime[IM_D_MAX_TIMESTAMP_LENGTH];           /**< ��һ�ε�¼�ķ�����ʱ�� */
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< ���������ص��ʺ���Ϣ */
    TUP_INT64    sessionID;                                         /**< ��¼�ɹ�����������صĻỰID */
    IM_E_LOGIN_ENCRYPT_TYPE encryptType;                            /**< ���ܷ�ʽ */
 }IM_S_LOGIN_ACK;

/**
 *  ��ѯ�����б�����
 */
typedef struct tagIM_S_GETCONTACTLIST_ARG
 {
    TUP_BOOL    isSyncAll;                                          /**< �Ƿ�ȫ��ͬ�������β�ѯ�Ƿ������к����б���Ϣ�����߷���ĳ��ʱ��ε����������ĺ����б��Լ�����(����) */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ����ͬ��ʱ�����ʱ���ʽ��19000000000000��������ʱ���룩 (isSyncAllΪTUP_FALSEʱ����) */
 }IM_S_GETCONTACTLIST_ARG;

/**
 *  ��ѯ��ϵ���б���Ӧ
 */
typedef struct tagIM_S_GETCONTACTLIST_ACK
 {
    TUP_BOOL    result;                                             /**< ������� */
    TUP_BOOL    isSyncAll;                                          /**< ����ͬ���Ƿ�������ͬ�� */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ����ͬ��ʱ�������ʽΪ��19000000000000��������ʱ���룩��isSyncAllΪTUP_TRUEʱʱ�����Ч */
    TUP_S_LIST*    userList;                                        /**< ���˺ŵ��û������б�ӵ���˺���Ϣ���û����б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERINFO */
    TUP_S_LIST* contactList;                                        /**< �����б����Ѱ����˺��û����Զ�����ϵ�ˣ� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_CONTACTNFO */
    TUP_S_LIST* userGroupList;                                      /**< ���ѷ��飬 TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERGROUPINFO */
    TUP_S_LIST* userGroupMemberList;                                /**< ���ѷ������ϵ�˶�Ӧ��ϵ�� TUP_S_LIST�е�*dada�ṹ����ΪM_S_USERGROUPMEMBERINFO */
    TUP_S_LIST* imGroupList;                                        /**< �̶�Ⱥ�б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_IMGROUPINFO*/
 }IM_S_GETCONTACTLIST_ACK;

/**
 *  ��ѯҵ��������������
 */
typedef struct tagIM_S_GETSERVICEPROFILEARG
{
    TUP_BOOL    isSyncAll;                                          /**< �Ƿ�ȫ��ͬ�� */
    TUP_BOOL    needIcon;                                           /**< �Ƿ���Ҫ�����Ϣ��ͼ�� */
    TUP_BOOL    isVpnAccess;                                        /**< �Ƿ�VPN����  */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ����ͬ��ʱ�������ʽΪ��19000000000000��������ʱ���룩��isSyncAllΪTUP_TRUEʱ��Ч */
    TUP_CHAR    localIP[IM_D_IP_LENGTH];                            /**< ����IP��ַ */
}IM_S_GETSERVICEPROFILEARG;

/**
 *  ��ѯҵ���������ݽ����Ӧ
 */
typedef struct tagIM_S_SERVICEPROFILEACK
{
    TUP_BOOL    syncType;                                           /**< �Ƿ�ȫ��ͬ�� */
    TUP_BOOL    isSetIpphone;                                       /**< �Ƿ�������IPPhone */
    TUP_BOOL    isJointUser;                                        /**< �Ƿ��������� */
    TUP_BOOL    bindChange;                                         /**< IP�仯�Ƿ���л� */
    TUP_INT32   sipExpires;                                         /**< sipע������ʱ�� */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ������ʱ��� */    
    TUP_CHAR    ipPhone[IM_D_GENEAL_LENGTH];                        /**< ��IPPhone���� */
    TUP_CHAR    eConsoleAddr[IM_D_IP_LENGTH];                       /**< eConsole��ַ */
    TUP_CHAR    sipAccount[IM_D_GENEAL_LENGTH];                     /**< sip�˺� */
    TUP_CHAR    sipPassword[IM_D_MAX_NAME_LENGTH];                  /**< sip�˺����� */
    TUP_CHAR    sipServer[IM_D_IP_LENGTH];                          /**< sip��������ַ (���˿�) */
    TUP_CHAR    sipicscfDomainName[IM_D_IP_LENGTH];                 /**< ICSCF���� */
    TUP_CHAR    sipCountryCode[IM_D_GENEAL_LENGTH];                 /**< ������ */
    TUP_CHAR    sipOutgoingAccCode[IM_D_GENEAL_LENGTH];             /**< ��������� */
    TUP_CHAR    sipInfoAccCode[IM_D_GENEAL_LENGTH];                 /**< Info������ */
    TUP_CHAR    sipUcPassword[IM_D_MAX_NAME_LENGTH];                /**< UC����  */
    TUP_CHAR    sipNetType[IM_D_GENEAL_LENGTH];                     /**< �������ͣ�IMS/NGN�� */
    TUP_S_LIST* funcIDList;                                         /**< �û������б��û����ε�¼ʹ�õĹ���λ long long�� */
    TUP_S_LIST* configList;                                         /**< ������Ϣ�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_CONFIGINFO */
    TUP_S_LIST* panelList;                                          /**< �����Ϣ�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_PANELINFO */
    TUP_S_LIST* serverList;                                         /**< ����������б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_SERVERINFO */
    TUP_S_LIST* componentList;                                      /**< �����Ϣ�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_COMPONETINFO*/
    TUP_S_LIST* componentParamList;                                 /**< ���������Ϣ�б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_COMPONETPARAMINFO */
    TUP_S_LIST* dataConfAddrList;                                   /**< ���ݻ����ַ�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_DATACONFADDRINFO */
    TUP_S_LIST* umServerHttpList;                                   /**< UM ������ http�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_UMSERVERADDR */
    TUP_S_LIST* umServerHttpsList;                                  /**< UM ������ https�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_UMSERVERADDR */
    TUP_CHAR    dataConfAddrs[IM_D_MAX_PATH_LENGTH];                /**< ���ݻ����������ַ�б��ַ�����ʽ */
    TUP_CHAR    audioGWType;                                        /**< �ͻ���ע��������������� 0:U1900; 1:USM */
}IM_S_SERVICEPROFILEACK;

/**
 *  ������Ϣ�б�
 */
typedef struct tagIM_S_CONFIGINFO
{
    TUP_CHAR    name[IM_D_GENEAL_LENGTH];                           /**< ���� */
    TUP_CHAR    value[IM_D_GENEAL_LENGTH];                          /**< ��Ӧ��ֵ */
}IM_S_CONFIGINFO;

/**
 *  ����̨�����Ϣ
 */
typedef struct tagIM_S_PANELINFO
{
    TUP_INT64    id;                                                /**< ���ID */
    TUP_INT64    indexNO;                                           /**< ���ͼ����� */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ���� */
    IM_E_SYNC_TYPE    state;                                        /**< ״̬ */
}IM_S_PANELINFO;

/**
 *  �����Ϣ
 */
typedef struct tagIM_S_COMPONETINFO
{
    TUP_INT64    id;                                                /**< ���ID */
    TUP_INT64    panelID;                                           /**< ��Ӧ���ID */
    TUP_INT64    functionID;                                        /**< ��Ӧ����λ */
    TUP_INT64    indexNO;                                           /**< ��� */
    TUP_INT64    serverID;                                          /**< ��Ӧ����ID */
    TUP_CHAR    progID[IM_D_MAX_PROGID_LENGTH];                     /**< progid */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ������� */
    TUP_CHAR    type[IM_D_GENEAL_LENGTH];                           /**< ������� */
    TUP_CHAR    path[IM_D_MAX_PATH_LENGTH];                         /**< ���·�� */
    TUP_CHAR    icon[IM_D_ICON_LENGTH];                             /**< ���ͼ��*/
    TUP_CHAR    protocol[IM_D_GENEAL_LENGTH];                       /**< Э������ */
    IM_E_SYNC_TYPE    state;                                        /**< ���״̬ */
}IM_S_COMPONETINFO;

/**
 *  ���������Ϣ�б�
 */
typedef struct tagIM_S_COMPONETPARAMINFO
{
    TUP_CHAR    progID[IM_D_MAX_PROGID_LENGTH];                     /**< progid */
    TUP_CHAR    key[IM_D_MAX_PLUGINPARAM_LENGTH];                   /**< progid��Ӧ�Ĳ��� */
    TUP_CHAR    value[IM_D_MAX_PLUGINPARAM_LENGTH];                 /**< progid��Ӧ�Ĳ�����ֵ */
}IM_S_COMPONETPARAMINFO;

/**
 *  ��������Ϣ
 */
typedef struct tagIM_S_SERVERINFO
{
    TUP_INT64    id;                                                /**< ������ID */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ���������� */
    TUP_CHAR    address[IM_D_MAX_PLUGINURL_LENGTH];                 /**< ��������ַ */
}IM_S_SERVERINFO;

/**
 *  ���ݻ����������ַ
 */
typedef struct tagIM_S_DATACONFADDRINFO
{
    TUP_CHAR    dataConfAddr[IM_D_IP_LENGTH];                       /**< ���ݻ����������ַ */
}IM_S_DATACONFADDRINFO;

/**
 *  UM��������ַ
 */
typedef struct tagIM_S_UMSERVERADDR
{
    TUP_CHAR    umServerAddr[IM_D_IP_LENGTH];                       /**< UM��������ַ */
}IM_S_UMSERVERADDR;

/**
 *    ��ѯ�û����󣨾�ȷ��ѯ��
 *@    attention: account��staffID����������д����һ���Ϳ��Կ�ʼ��ѯ
 */
typedef struct tarIM_S_GETUSERINFOARG
{
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< �ʺ� */
    TUP_INT64    staffID;                                           /**< staffID�������˺�ʱ�ɷ��������ɵ�Ψһ��ʾ�����Ϲ����л�Ҳ����ı��ֵ��*/
}IM_S_GETUSERINFOARG;

/**
 *  ��ѯ�̶�Ⱥ����ģ����ѯ�����ؽ���б�
 */
typedef struct tagIM_S_GETIMGROUPLIST_ARG
 {
    TUP_BOOL    isNeedAmount;                                       /**< �Ƿ���Ҫ�������� (����) */ 
    TUP_INT32    offset;                                            /**< ��ѯƫ���� (ѡ��) */ 
    TUP_INT32    count;                                             /**< ���β�ѯ������ص�����(����) */ 
    TUP_CHAR    queryKey[IM_D_GENEAL_LENGTH] ;                      /**< �ؼ��� (����) */ 
    IM_E_IMGROUPQUERYTYPE    queryType;                             /**< Ⱥ���ѯ���� (����) */
 }IM_S_GETIMGROUPLIST_ARG;

/**
 *  ��ѯ�̶�Ⱥ��Ӧ��ģ����ѯ�����ؽ���б�
 */
typedef struct tagIM_S_GETIMGROUPLIST_ACK
 {
    TUP_INT32    recordAmount;                                      /**< �ܼ�¼�� */ 
    TUP_INT32    offset;                                            /**< ��ѯƫ���� */ 
    TUP_INT32    count;                                             /**< ��ѯ��Ŀ */ 
    TUP_S_LIST*    imGroupList;                                     /**< Ⱥ���б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_IMGROUPINFO */ 
 }IM_S_GETIMGROUPLIST_ACK;

/**
 *  ��Ӻ��ѷ�������
 */
typedef struct tagIM_S_ADDUSERGROUP_ARG
 {
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ��������(����) */
    TUP_INT32    index;                                             /**< ���(����������Ҫ����������Ĭ����-1) */
 }IM_S_ADDUSERGROUP_ARG;

/**
 *  ��Ӻ��ѷ�����Ӧ
 */
typedef struct tagIM_S_ADDUSERGROUP_ACK
 {
    TUP_BOOL    result;                                             /**< ������� */
    TUP_INT64    id;                                                /**< ����� */
 }IM_S_ADDUSERGROUP_ACK;

/**
 *  �޸ĺ��ѷ�������
 */
typedef struct tagIM_S_MODUSERGROUP_ARG
 {
    TUP_INT64    id;                                                /**< �����(����) */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ��������(����) */
    TUP_INT32    index;                                             /**< ���(����������Ҫ����������Ĭ����-1) */
 }IM_S_MODUSERGROUP_ARG;

/**
 *  ����˺��û�Ϊ��������
 */
typedef struct tagIM_S_ADDFRIEND_ARG
 {
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< �����ʺ� (����)*/
    TUP_INT64    groupID;                                           /**< ���ѷ���ID(����) */
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< ����Ϊ���ѵ��û��յ������֪ͨ����ʾ�����������(��ѡ) */
 }IM_S_ADDFRIEND_ARG;

/**
 *  ����˺��û�Ϊ������Ӧ
 */
typedef struct tagIM_S_ADDFRIEND_ACK
 {
    TUP_BOOL    result;                                             /**< ������� */
    TUP_INT64    contactID;                                         /**< ��ϵ���ں���/��ϵ�˷����е�ID�������ѽṹ�壺IM_S_CONTACTNFO�е�id */
 }IM_S_ADDFRIEND_ACK;

/**
 *  ����Զ�����ϵ��Ϊ��������
 */
typedef struct tagIM_S_ADDCONTACT_ARG
 {
    IM_S_CONTACTNFO    contact;                                     /**< �Զ�����ϵ����Ϣ������Զ�����ϵ��ʱid�ֶβ�����д����ӳɹ��󷵻أ�staffID��д��¼�û���staffID������) */
    TUP_INT64    groupID;                                           /**< ��ӵ��ķ���ID(����) */
 }IM_S_ADDCONTACT_ARG;

/**
 *  ����Զ�����ϵ����Ӧ
 */
typedef struct tagIM_S_ADDCONTACT_ACK
 {
    TUP_BOOL    result;                                             /**< ������� */
    TUP_INT64    contactID;                                         /**< ����ID */
 }IM_S_ADDCONTACT_ACK;

/**
 *  �޸��Զ�����ϵ������
 */
typedef struct tagIM_S_MODCONTACT_ARG
 {
    IM_S_CONTACTNFO        contact;                                 /**< ��ϵ����Ϣ��id��� */
 }IM_S_MODCONTACT_ARG;

/**
 *  ��ĳһ��������ɾ�����ѻ�/��ϵ��
 */
typedef struct tagIM_S_DELCONTACT_ARG
 {
    TUP_INT64    contactID;                                         /**< ��ϵ��ID(����) */
    TUP_INT64    groupID;                                           /**< ����ID(����) */
 }IM_S_DELCONTACT_ARG;

/**
 *  ת�ƺ��ѷ�������
 */
typedef struct tagIM_S_MODCONTACTGROUP_ARG
 {
    TUP_INT64    contactID;                                         /**< ��ϵ��ID(����) */ 
    TUP_INT64    oldGroupID;                                        /**< ԭ��ID(����) */ 
    TUP_INT64    newGroupID;                                        /**< ����ID(����) */ 
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE    type;                   /**< �ƶ����Ǹ��� */ 
 }IM_S_MODCONTACTGROUP_ARG;

/**
 *  �����ı���Ϣ����
 */
typedef struct tagIM_S_SENDIM_ARG
{
    TUP_INT        regionID;                                        /**< ����ID �������� (��ѡ) */
    IM_E_IM_CHAT_TYPE    chatType;                                  /**< IM��Ϣ����(����) */
    IM_E_IM_CHAT_SOURCE_FLAG    sourceFlag;                         /**< IM��Ϣ��������(����) */
    IM_E_IM_CHAT_CONTENT_TYPE    contentType;                       /**< IM��Ϣ���ݸ�ʽ(����) */
    TUP_CHAR    origin[IM_D_MAX_ACCOUNT_LENGTH];                    /**< ���ͷ��˺�(����) */
    TUP_CHAR    target[IM_D_MAX_ACCOUNT_LENGTH];                    /**< ���շ��˺�(����) */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< Ⱥ��ID���̶�Ⱥ����������*/
    TUP_CHAR    content[IM_D_MAX_MESSAGE_LENGTH];                   /**< IM��Ϣ����(����) */
    TUP_CHAR    displayname[IM_D_MAX_NAME_LENGTH];                  /**< ���ͷ�����(��ѡ) */
    TUP_INT64    utcStamp;                                          /**< UTCʱ�� (��ѡ) */
    TUP_INT64    clientChatID;                                      /**< �ͻ������ɵ���ϢID */
    IM_E_IM_CHATMEDIA_TYPE mediaType;                               /**< ý������ */
}IM_S_SENDIM_ARG;


/**
 *  �ı���Ϣ�Ѷ���������
 */
typedef struct tagIM_S_SETMESSAGEREAD_ARG
{
    TUP_S_LIST*    messageinfo;                                     /**< �Ѷ���Ϣ������Ϣ��ʽ TUP_S_LIST�е�*dada�ṹ����ΪIM_S_MESSAGEINFO */
}IM_S_SETMESSAGEREAD_ARG;

/**
 *  ��ѯ������Ϣ����
 */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ARG
{
    IM_E_IM_HISTORYMESSAGEOP_TYPE    opType;                        /**< �������� */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE    msgType;                      /**< �������Ϣ���� */
    TUP_CHAR    sender[IM_D_MAX_PHONE_LENGTH];                      /**< ��Ϣ���ͷ���msgTypeΪ0ʱ��д��Ϣ�������˺ţ�msgTypeΪ1ʱ��дȺ��ID��msgTypeΪ2ʱ��д���ź��룬msgTypeΪ3ʱ����д */
    TUP_INT64    msgID;                                             /**< ��ϢID���״β�ѯ���Ը��ֶ� */
    TUP_INT        count;                                           /**< ��ѯ����Ϣ���� */
}IM_S_QUERYHISTORYMESSAGE_ARG;

/**
 *  ��ѯ������Ϣ��Ӧ
 */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ACK
{
    TUP_INT        totalCount;                                      /**< ��Ϣ���������״β�ѯʱ���� */
    IM_E_IM_HISTORYMESSAGEOP_TYPE    opType;                        /**< �������� */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE    msgType;                      /**< �������Ϣ���� */
    TUP_CHAR sender[IM_D_MAX_PHONE_LENGTH];                         /**< ��Ϣ���ͷ���msgTypeΪ0ʱ����Ϣ�������˺ţ�msgTypeΪ1��ȺID��msgTypeΪ2ʱ�Ƕ��ź��룬msgTypeΪ3ʱ���� */
    TUP_S_LIST*    chatinfolist;                                    /**< ��Ϣ��ʽ TUP_S_LIST�е�*dada�ṹ����ΪIM_S_CODECHAT_NOTIFY */
    TUP_S_LIST* smsList;                                            /**< ������Ϣ�б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_SMSINFO */
}IM_S_QUERYHISTORYMESSAGE_ACK;

/**
 *  �ı���Ϣ
 */
typedef struct tagIM_S_CHATINFO_NOTIFY
{
    IM_E_IM_CHAT_TYPE    chatType;                                  /**< IM��Ϣ���� */
    TUP_INT     sourceFlag;                                         /**< IM��Ϣ�������� */
    TUP_INT     contentType;                                        /**< IM��Ϣ���ݸ�ʽ*/
    TUP_INT64   utcStamp;                                           /**< UTCʱ��*/
    TUP_CHAR    origin[IM_D_MAX_ACCOUNT_LENGTH];                    /**< ���ͷ��˺�*/
    TUP_CHAR    target[IM_D_MAX_ACCOUNT_LENGTH];                    /**< ���շ��˺�*/
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< Ⱥ��ID*/
    TUP_CHAR    content[IM_D_MAX_MESSAGE_LENGTH];                   /**< IM��Ϣ����*/
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< ���ͷ�����*/
    TUP_INT     regionID;                                           /**< ����ID �������� */
    TUP_INT64   clientChatID;                                       /**< �ͻ������ɵ���ϢID */
    TUP_INT64   serverChatID;                                       /**< ���������ɵ���ϢID���ͻ��˷���ʱ�������ʱ��������д */
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< Ⱥ���� */
    IM_E_IM_CHATMEDIA_TYPE mediaType;                               /**< ý������ */
    TUP_INT64   deliverTime;                                        /**< ���������͵�ʱ��*/
}IM_S_CHATINFO_NOTIFY;

/**
 *  ������Ϣ
 */
typedef struct tagIM_S_SMSINFO
{
    TUP_CHAR    origin[IM_D_MAX_PHONE_LENGTH];                      /**< ���ͷ�����*/
    TUP_CHAR    target[IM_D_MAX_PHONE_LENGTH];                      /**< ���շ�����*/
    TUP_INT64   serverMsgID;                                        /**< ��������ϢID*/
    TUP_CHAR    clientMsgID[IM_D_MAX_CHAR_LENGTH];                  /**< �ͻ�����ϢID*/
    TUP_CHAR    content[IM_D_MAX_MESSAGE_LENGTH];                   /**< ��Ϣ����*/
    TUP_CHAR    sendTime[IM_D_MAX_TIMESTAMP_LENGTH];                /**< ����ʱ��*/
    IM_E_SMS_NOTIFY_TYPE    smsType;                                /**< ���յ��Ķ�����Ϣ������ */
}IM_S_SMSINFO;

/**
 *  ������Ϣ�Ѷ�
 */
typedef struct tagIM_S_MESSAGEINFO
{
    IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType;                         /**< ��Ϣ���� */
    TUP_CHAR    sender[IM_D_MAX_PHONE_LENGTH];                      /**< ���ͷ� (�����˺š��̶�Ⱥ��������ID�����ź���) */
    TUP_INT64    msgId;                                             /**< ��ϢID (serverChatID) */
}IM_S_MESSAGEINFO;

/**
 *  ����״̬����
 */
typedef struct tagIM_S_CHAT_STATUS_ARG
{
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< ���շ��˺�(����) */
    IM_E_IM_CHAT_STATUS    type;                                    /**< ����״̬(����) */
}IM_S_CHAT_STATUS_ARG;

/**
 *  ��ѯ�����б���Ӧ
 */
typedef struct tagIM_S_GETDEPTS_ACK
 {
    TUP_BOOL    result;                                             /**< ���β������ */
    TUP_S_LIST*    deptList;                                        /**< �����б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_DEPTINFO */
 }IM_S_GETDEPTS_ACK;

/**
 *  ��ѯ��ҵͨѶ¼����
 */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ARG
{
    TUP_BOOL    isNeedAmount;                                       /**< �Ƿ���Ҫ��������(����) */ 
    IM_E_ADDRBOOKQUERY_ORDERTYPE orderType;                         /**< ����Ĺؼ��� */ 
    IM_E_ADDRBOOKQUERY_ORDERMODEL orderModel;                       /**< ����ķ�ʽ */ 
    TUP_INT32 offset;                                               /**< ��ѯƫ����(����) */ 
    TUP_INT32 count;                                                /**< ��ѯ��Ŀ(����) */ 
    TUP_INT64 deptID;                                               /**< ��ѯ���ţ���������ָ�����ţ�����д-1�� */ 
    TUP_CHAR queryKey[IM_D_MAX_DESC_LENGTH];                        /**< �ؼ��֣���ѡ�� */ 
}IM_S_QUERY_ENTADDRESSBOOK_ARG;

/**
 *  ��ѯ��ҵͨѶ¼�����Ӧ
 */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ACK
{
    TUP_BOOL    result;                                             /**< ���β������ */
    TUP_INT32    recordAmount;                                      /**< �ܼ�¼�� */ 
    TUP_S_LIST*    userList;                                        /**< ��Ա�б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERINFO */ 
}IM_S_QUERY_ENTADDRESSBOOK_ACK;

/**
 *  ��ѯ�û���Ϣ����ģ����ѯ��
 */
typedef struct tagIM_S_QUERY_USERINFO_ARG
{
    TUP_CHAR    key[IM_D_MAX_PHONE_LENGTH];                         /**< �ؼ������� */
    IM_E_IMUSERQUERYTYPE    type;                                   /**< �ؼ������� */
}IM_S_QUERY_USERINFO_ARG;

/**
 *  ��ѯ�û���Ϣ�����Ӧ��ģ����ѯ��
 */
typedef struct tagIM_S_QUERY_USERINFO_ACK
{
    TUP_S_LIST*    userList;                                        /**< ��Ա�б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERINFO */ 
}IM_S_QUERY_USERINFO_ACK;

/**
 *  �������޸Ĺ̶�Ⱥ������������
 */
typedef struct tagIM_S_IMGROUP_OP_ARG
{
    IM_S_IMGROUPINFO    fixedgroupInfo;                             /**< �̶�Ⱥ����������Ϣ�����ʱid�����ack�з��أ��޸�ʱ��Ҫ��дid�� */
}IM_S_IMGROUP_OP_ARG;

/**
 *  �����̶�Ⱥ����������Ӧ
 */
typedef struct tagIM_S_ADDIMGROUP_ACK
{
    TUP_BOOL    result;                                             /**< ������� */
    TUP_CHAR    id[IM_D_GROUPID_LENGTH];                            /**< �����Ĺ̶�Ⱥ��������ID  */
    IM_E_FIXEDGROUP_OP_RESULT    reason;                            /**< �����������ֵ��������resultΪTUP_FALSEʱ���ж�ʧ��ԭ�� */
}IM_S_ADDIMGROUP_ACK;

/**
 *  �޸Ĺ̶�Ⱥ��Ϣ��Ӧ
 */
typedef struct tagIM_S_MODFIXEDGROUP_ACK
{
    TUP_BOOL    result;                                             /**< ������� */
    IM_E_FIXEDGROUP_OP_RESULT    reason;                            /**< �����������ֵ��������resultΪTUP_FALSEʱ���ж�ʧ��ԭ�� */
}IM_S_MODFIXEDGROUP_ACK;

/**
 *  ��ӹ̶�Ⱥ��Ա����
 */
typedef struct tagIM_S_ADDIMGROUPMEMBER_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< ����û��ʺ� */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< �̶�Ⱥ���� */ 
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< ������û��յ�֪ͨ�е���ʾ�� ���Ǳ��*/ 
}IM_S_ADDIMGROUPMEMBER_ARG;

/**
 *  ��ȡ�̶�Ⱥ���������Ա����
 */
typedef struct tagIM_S_REQUESTIMGROUPMEMBERS_ARG
{
    TUP_BOOL    isSyncAll;                                          /**< �Ƿ�ȫ��ͬ�� */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�Ⱥ��������ID */
    TUP_CHAR    timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ͬ��ʱ�����19000000000000��������ʱ����)������дʹ��Ĭ��ʱ��19000000000000 */
}IM_S_REQUESTIMGROUPMEMBERS_ARG;

/**
 *  ɾ���̶�Ⱥ���������Ա����
 */
typedef struct tagIM_S_DELIMGROUPMEMBER_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                        /**< �̶�ȺID �����*/ 
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                    /**< ��ɾ�����û��ʺ� �����*/ 
}IM_S_DELIMGROUPMEMBER_ARG;

/**
 *  ����Ա�����û��������̶�Ⱥ���룬�����û���������Ա�������̶�Ⱥ
 */
typedef struct tagIM_S_CONFIRM_JOINFIXEDGROUP_ARG
{
    TUP_BOOL    agreeJoin;                                          /**< ����Ա�Ƿ�ͬ���Ա������ */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< Ⱥ����ID */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< ��������Ա�ʺ� */ 
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< �Է��յ���������е���ʾ�� ���Ǳ��*/ 
}IM_S_CONFIRM_JOINFIXEDGROUP_ARG;

/**
 *  �û��������̶�Ⱥ����
 */
typedef struct tagIM_S_JOINFIXEDGROUP_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< �̶�Ⱥ�� */ 
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< ��ʾ���������ƣ��Ǳ�� */ 
}IM_S_JOINFIXEDGROUP_ARG;

/**
 *  ת�ƹ̶�Ⱥ�����������ԱȨ������
 */
typedef struct tagIM_S_TRANSFERIMGROUP_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< ��ת�Ƴɹ���Ա�ĳ�Ա�ʺ� */ 
}IM_S_TRANSFERIMGROUP_ARG;

/**
 *  �̶�Ⱥ����Ա�յ������û��Լ���̶�Ⱥ������������
 */
typedef struct tagIM_S_IMGROUP_OWNER_INVITE_RESULT_NOTIFY
{
    TUP_BOOL    agreeInvite;                                        /**< �û��Ƿ�ͬ�����Ա������ */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< �̶�ȺȺ���� */
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< �������Ա���ʺ� */
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**< �������Ա������ */
}IM_S_IMGROUP_OWNER_INVITE_RESULT_NOTIFY;

/**
 *  �û������뿪�̶�Ⱥ֪ͨ
 */
typedef struct tagIM_S_IMGROUP_LEAVE_RESULT_NOTIFY
{
    IM_E_FIXEDGROUP_OP_RESULT    resultCode;                        /**< ������������ */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< ȺID */
}IM_S_IMGROUP_LEAVE_RESULT_NOTIFY;

/**
 *  �û��յ�������Ա�߳��̶�Ⱥ֪ͨ
 */
typedef struct tagIM_S_IMGROUP_KICKOUT_NOTIFY
{
    IM_E_FIXEDGROUP_OP_RESULT    resultCode;                        /**< ������������ */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< ȺID */
}IM_S_IMGROUP_KICKOUT_NOTIFY;

/**
 *   ������Ϣδ�ʹ���з��ͷ��У�
 */
typedef struct tagIM_S_UNDELIVER_NOTIFY
{
    IM_S_CHATINFO_NOTIFY chatInfo;                                  /**< ������Ϣ */
    IM_E_UNDELIVER_MSG_TYPE type;                                   /**< δ�ʹ���Ϣ���� */
}IM_S_UNDELIVER_NOTIFY;

/**
 *   ������Ϣ�Ѷ�֪ͨ����˵�¼��    
 */
typedef struct tagIM_S_MSG_READ_NOTIFY
{
    TUP_CHAR from[IM_D_MAX_ACCOUNT_LENGTH];                         /**< ��Ϣ������ */
    TUP_CHAR target[IM_D_MAX_ACCOUNT_LENGTH];                       /**< ��Ϣ������ */
    TUP_INT64 msgID;                                                /**< ��ϢID */
    IM_E_IM_HISTORYMESSAGEMSG_TYPE   msgType;                       /**< ��Ϣ���� */
}IM_S_MSG_READ_NOTIFY;
/**
 *   ������Ϣ���ͽ��֪ͨ
 */
typedef struct tagIM_S_SENDACK_NOTIFY
{
    TUP_CHAR origin[IM_D_MAX_ACCOUNT_LENGTH];                      /**< ��Ϣ������ */
    TUP_CHAR target[IM_D_MAX_ACCOUNT_LENGTH];                       /**< ��Ϣ������ */
	TUP_INT64 utcStamp;                                             /**< ʱ��� */
	TUP_INT64 chatID;                                               /**< �ͻ��˲���ϢID */
    TUP_INT64 serverChatID;                                         /**< ����������ϢID */
    TUP_BOOL  result;                                               /**< ���ͽ�� */
}IM_S_SENDACK_NOTIFY;
/**
 *   �ͻ�����������������ͻ���ͨ�ŵĻỰ֪ͨ
 */
typedef struct tagIM_S_GENERAL_NOTIFY
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];                      /**< ��Ϣ������ */ 
    TUP_CHAR content[IM_D_MAX_ACCOUNT_LENGTH];                      /**< ��Ϣ������ */ 
    IM_E_IM_GENERAL_NOTIFY_TYPE    flag;                            /**< ��Ϣ֪ͨ���� */ 
}IM_S_GENERAL_NOTIFY;
/**
 *  ��������ӻ�ɾ�������û�����
 */
typedef struct tagIM_S_IMGROUPPHONEMEMBER_OP_ARG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_S_LIST*    phonelist;                                       /**< �����б�  TUP_S_LIST�е�*dada�ṹ����ΪTUP_CHAR*/ 
}IM_S_IMGROUPPHONEMEMBER_OP_ARG;

/** 
 * �˳���������Ӧ
 */
typedef struct tagIM_S_LEAVE_DISCUSSGROUP_ACK
{
    TUP_CHAR    target[IM_D_MAX_ACCOUNT_LENGTH];                    /**< �������˺� */
    TUP_CHAR    groupid[IM_D_GENEAL_LENGTH];                        /**< ������ID */
    IM_E_LEAVEGROUP_FLAG    flag;                                   /**< �����뿪�����߳�Ⱥ��ʶ */
    IM_E_LEAVEGROUP_RESULT    result;                               /**< ������� */
    IM_E_IMGROUP_TYPE    grouptype;                                 /**< Ⱥ������ */
}IM_S_LEAVE_DISCUSSGROUP_ACK;

/**
 *  ��ѯ�����б�����
 */
typedef struct tagIM_S_GETCONFERENCELISTARG
{
    TUP_INT16    count;                                             /**< ��ѯ������ */
    TUP_INT16    pageNo;                                            /**< ��ѯ�ڼ�ҳ */
}IM_S_GETCONFERENCELISTARG;

/**
 *  ��ѯ�����б�����Ӧ
 */
typedef struct tagIM_S_GETCONFERENCELISTACK
{
    TUP_INT        totalCount;                                      /**< �ܼ�¼�� */
    TUP_S_LIST*    meetingList;                                     /**< �����б�  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_MEETINGINFO*/
}IM_S_GETCONFERENCELISTACK;

/**
 *  �����ȡϵͳURL��Ϣ��Ӧ
 */
typedef struct tagIM_S_SYSURLS_NOTIFY
{
    TUP_CHAR    userPortalUrl[IM_D_IP_LENGTH];                      /**< ����portal��ַ */
    TUP_CHAR    updateServerAddr[IM_D_IP_LENGTH];                   /**< �Զ�������������ַ */
    TUP_CHAR    establishAnAccountHelpUrl[IM_D_IP_LENGTH];          /**< ����ָ������ */
    TUP_CHAR    userHelpUrl[IM_D_IP_LENGTH];                        /**< �û��������� */
    TUP_CHAR    forgetPwdUrl[IM_D_IP_LENGTH];                       /**< ������������ */
    TUP_CHAR    loginFailedUrl[IM_D_IP_LENGTH];                     /**< ��½ʧ������ */
    TUP_CHAR    vpnNames[IM_D_IP_LENGTH];                           /**< �������ṩ��VPN������ */
    TUP_CHAR    downloadUrl[IM_D_IP_LENGTH];                        /**< �ͻ���ֱ���������� */
    TUP_CHAR    updateReportUrl[IM_D_IP_LENGTH];                    /**< �ͻ����ϱ���������ַ */
    TUP_CHAR    netErrorUrl[IM_D_IP_LENGTH];                        /**< ����������� */
}IM_S_SYSURLS_NOTIFY;

/**
 *  �˳���¼��Ӧ
 */
typedef struct tagIM_S_LOGOUT_NOTIFY
{
    TUP_BOOL    LogOutRet;                                          /**< �û��˳���� */
}IM_S_LOGOUT_NOTIFY;

/**
 *  �����û�����Լ�Ϊ���ѳɹ���֪ͨ
 */
typedef struct tagIM_S_ADDFRIEND_NOTIFY
 {
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< �Է������ʺ� */
    TUP_CHAR    displayName[IM_D_MAX_NAME_LENGTH];                  /**< �Է���ʾ�� */
    TUP_INT64    serverMsgID;                                       /**< ��������ϢID */
 }IM_S_ADDFRIEND_NOTIFY;

/**
 *  ����״̬�仯֪ͨ
 */
typedef struct tagIM_S_USERSTATUS_NOTIFY
 {
    IM_E_USER_ONLINESTATUS    status;                               /**< ���º��״̬ */
    TUP_CHAR    desc[IM_D_MAX_DESC_LENGTH];                         /**< ״̬���� */
    TUP_CHAR    origin[IM_D_MAX_ACCOUNT_LENGTH];                    /**< ״̬�仯��Ա�ʺ� */
    IM_E_CLIENT_TYPE    clientType;                                 /**< �ͻ������� */
    TUP_CHAR    clientDesc[IM_D_MAX_DESC_LENGTH];                   /**< �ͻ������� */
 }IM_S_USERSTATUS_NOTIFY;

/**
 *  ������Ϣ�仯֪ͨ
 */
typedef struct tagIM_S_USERINFOCHANGE_LIST_NOTIFY
{
    TUP_S_LIST* userInfoList;                                       /**< �û��б� TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERINFO */
}IM_S_USERINFOCHANGE_LIST_NOTIFY;

/**
 *  �û��յ��̶�Ⱥ����Ա�������̶�Ⱥ֪ͨ
 */
typedef struct tagIM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< Ⱥ����ID */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**< ����Ա�ʺ� */ 
    TUP_CHAR    adminName[IM_D_MAX_NAME_LENGTH];                    /**< ����Ա���� */
    TUP_INT64    serverMsgID;                                       /**< ��������ϢID */
}IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY;

/**
 *  ����Ա�յ��û��������Ⱥ��֪ͨ
 */
typedef struct tagIM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< Ⱥ����ID */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< �������ʺ� */ 
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**< ���������� */ 
    TUP_INT64    serverMsgID;                                       /**< ��������ϢID */
}IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY;

/**
 *  ��ȡ�̶�Ⱥ��������������Ӧ��Ϣ���ѷ���������ʹ�ã�
 */
typedef struct tagIM_S_GETIMGROUPDETAIL_NOTIFY
{
    IM_S_IMGROUPINFO    imGroupInfo;                                /**< �̶�Ⱥ�ṹ�� */
}IM_S_GETIMGROUPDETAIL_NOTIFY;


/**
 *  Ⱥ��Ա�յ�����Ա��������̶�Ⱥ֪ͨ����Ӧ
 */
typedef struct tagIM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY
{
    TUP_BOOL    agreeJoin;                                          /**< ����Ա�Ƿ�ͬ���Ա������ */
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< �̶�ȺID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< �̶�Ⱥ��ID */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**< ����Ա���ʺ�  */ 
    TUP_CHAR    adminName[IM_D_MAX_NAME_LENGTH];                    /**< ����Ա������ */ 
}IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY;

/**
 *  �̶�Ⱥ���֪ͨ
 */
typedef struct tagIM_S_IMGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**<  �̶�ȺID */ 
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**<  �̶�Ⱥ�� */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**<  ����Ա�ʺ� */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**<  ������ɾ���ĳ�Ա�ʺ� */ 
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**<  ������ɾ���ĳ�Ա���� */ 
    TUP_INT64    serverMsgID;                                       /**<  ��������ϢID */
}IM_S_IMGROUP_NOTIFY;

/**
 *  �����û��ĺ���
 */
typedef struct tagIM_S_PHONENUM
{
    TUP_CHAR    phoneNum[IM_D_GENEAL_LENGTH];                       /**<  �������� */        
}IM_S_PHONENUM;

/**
 *  ��������֪ͨ
 */
typedef struct tagIM_S_DISCUSSGROUP_NOTIFY
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< ������ID */ 
    TUP_S_LIST*    phonelist;                                       /**< �����б�  TUP_S_LIST�е�*dada�ṹ����ΪTUP_CHAR */            
    TUP_CHAR    groupName[IM_D_MAX_NAME_LENGTH];                    /**< ���������� */ 
    TUP_CHAR    adminAccount[IM_D_MAX_ACCOUNT_LENGTH];              /**< ����Ա�ʺ� */ 
    TUP_CHAR    memberAccount[IM_D_MAX_ACCOUNT_LENGTH];             /**< ������ɾ���ĳ�Ա�ʺ� */ 
    TUP_CHAR    memberName[IM_D_MAX_NAME_LENGTH];                   /**< ������ɾ���ĳ�Ա���� */ 
}IM_S_DISCUSSGROUP_NOTIFY;


/**
 *  ϵͳ����֪ͨ
 */
typedef struct tagIM_S_SYSTEMBULLETIN_NOTIFY
{
    IM_S_CHATINFO_NOTIFY chatInfo;                                  /**< �ı���Ϣ */
}IM_S_SYSTEMBULLETIN_NOTIFY;

/**
 *  �յ������û���������״̬��Ϣ
 */
typedef struct tagIM_S_SENDIMINPUT_NOTIFY
{
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< �������˺� */
    IM_E_IM_CHAT_STATUS    status;                                  /**< IM��������״̬ */
}IM_S_SENDIMINPUT_NOTIFY;

/**
 *  �¼�ʱ�ı���Ϣ֪ͨ
 */
typedef struct tagIM_S_CODECHAT_NOTIFY
{
    IM_S_CHATINFO_NOTIFY chatInfo;                                  /**< �ı���Ϣ */
}IM_S_CODECHAT_NOTIFY;

/**
 *  �¼�ʱ�ı���Ϣ֪ͨ�������� 
 */
typedef struct tagIM_S_CHATLIST_NOTIFY
{
    TUP_S_LIST*    chatList;                                        /**< �����ı���Ϣ  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_CODECHAT_NOTIFY */
    TUP_INT        total;                                           /**< δ����Ϣ���� */
    TUP_INT64    minMsgID;                                          /**< ��С��ϢID */
    TUP_INT64    maxMsgID;                                          /**< �����ϢID */
}IM_S_CHATLIST_NOTIFY;

/**
 *  �Զ���ͷ���ͼƬ��Ϣ 
 */
typedef struct tagIM_S_IMAGEINFO
{
    TUP_INT        length;                                          /**< ͷ��ͼƬ�ļ����ݳ��ȣ�������û�д�С���ƣ��Ƽ���ֵΪ2MB */
    TUP_CHAR*    data;                                              /**< ͷ��ͼƬ�ļ����� */
}IM_S_IMAGEINFO;

/**
 *  ��ȡ�����û��Զ���ͷ���ͼƬ��Ϣ��Ӧ 
 */
typedef struct tagIM_S_USERIMAGEINFO
{
    IM_S_IMAGEINFO    imagebits;                                    /**< ͷ������ */
    TUP_CHAR    id[IM_D_MAX_ACCOUNT_LENGTH];                        /**< �û��˺� */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ʱ��� */
}IM_S_USERIMAGEINFO;

/**
 *  ��ȡ�����û����Զ���ͷ������
 */
typedef struct tagIM_S_IMAGEREQARG
{
    TUP_CHAR    id[IM_D_MAX_ACCOUNT_LENGTH];                        /**< ��ȡ���û��˺� */
    TUP_CHAR    timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];               /**< ͬ��ʱ�����19000000000000��������ʱ���룩 */
}IM_S_IMAGEREQARG;

/**
 *  ֪ͨ�������Լ���״̬�仯����
 */
typedef struct tagIM_S_STATUSARG
{
    IM_E_USER_ONLINESTATUS    status;                                /**< ��״̬ */
    TUP_CHAR    desc[IM_D_MAX_STATUS_DESCLEN];                       /**< ״̬���� */
}IM_S_STATUSARG;

/**
 *  �û����ն˵�¼/�˳�֪ͨ
 */
typedef struct tagIM_S_MULTIDEVICE_NOTIFY
{
    TUP_CHAR    user[IM_D_MAX_ACCOUNT_LENGTH];                       /**< �û��˺� */
    TUP_INT64    eventTime;                                          /**< �û���½���˳�ʱ�䣺UTC��ʽ����ȷ������ */
    IM_E_CLIENT_TYPE    clientType;                                  /**< �豸���� */
    IM_E_CLIENT_OPT_TYPE    eventType;                               /**< �¼����� */
    TUP_CHAR    appID[IM_D_GENEAL_LENGTH];                           /**< �ö��ն˵ĵ�¼Ӧ��ID��ȱʡ�������ݲ����ţ� */
}IM_S_MULTIDEVICE_NOTIFY;

/**
 *  �û�����֪ͨ
 */
typedef struct tagIM_S_KICKOUT_NOTIFY
{
    TUP_CHAR    userAccount[IM_D_MAX_ACCOUNT_LENGTH];                /**< �û��˺� */
    IM_E_EXITSTATUS    exitFlag;                                     /**< �û���������ԭ�� */
}IM_S_KICKOUT_NOTIFY;

/**
 *  ��ý�������Ϣ
 */
typedef struct tagIM_S_MEETINGINFO
{
    TUP_CHAR    id[IM_D_GENEAL_LENGTH];                             /**< ����ID */
    TUP_INT     status;                                             /**< ����״̬ */
    TUP_CHAR    subject[IM_D_MAX_DESC_LENGTH];                      /**< �������� */
    TUP_CHAR    duration[IM_D_MAX_DESC_LENGTH];                     /**< ����ʱ�� */
    TUP_CHAR    startTime[IM_D_MAX_DESC_LENGTH];                    /**< ���鿪ʼʱ�� */
    TUP_INT     holdTime;                                           /**< �������ʱ�� */
    TUP_CHAR    convenerAccount[IM_D_MAX_ACCOUNT_LENGTH];           /**< �����ټ����˺� */
    TUP_CHAR    convenerName[IM_D_MAX_NAME_LENGTH];                 /**< �����ټ������� */
    TUP_INT     isForward;                                          /**< �Ƿ���ת������ */
    TUP_CHAR    forwarderAccount[IM_D_MAX_ACCOUNT_LENGTH];          /**< ת���������˺� */
    TUP_CHAR    forwarderName[IM_D_MAX_ACCOUNT_LENGTH];             /**< ת������������ */
    TUP_S_LIST* attendees;                                          /**< ���������  TUP_S_LIST�е�*dada�ṹ����ΪIM_S_USERINFO*/
    TUP_CHAR    agenda[IM_D_MAX_DESC_LENGTH];                       /**< ������� */
    TUP_CHAR    accessNumber[IM_D_MAX_PASSWORD_LENGTH];             /**< �������� */
    TUP_CHAR    securityCode[IM_D_MAX_PASSWORD_LENGTH];             /**< ���鰲ȫ�� */
    TUP_CHAR    convenerTimezone[IM_D_MAX_DESC_LENGTH];             /**< �ټ���Ԥ������ʱ��ʱ�� */
    TUP_INT     confType;                                           /**< �������� ��0��ȱʡֵ��*/
    TUP_CHAR    chairman[IM_D_MAX_NAME_LENGTH];                     /**< ������ϯ���� */
    TUP_CHAR    chairmanAccount[IM_D_MAX_ACCOUNT_LENGTH];           /**< ������ϯ�˺� */
    TUP_CHAR    meetingroom[IM_D_MAX_DESC_LENGTH];                  /**< ����᳡  */
    TUP_CHAR    translateAccessNumber[IM_D_MAX_PASSWORD_LENGTH];    /**< ��������� */
    TUP_CHAR    mediaType[IM_D_MAX_STATUS_DESCLEN];                 /**< ý������ */
}IM_S_MEETINGINFO;


/**
 *  ����Ự��Ϣ
 */
typedef struct tagIM_S_RECENT_CONVERSATION_INFO
{
    IM_E_IM_RECENT_CONVERSATION_TYPE  type;                         /**< �Ự���� */
    TUP_CHAR    id[IM_D_GENEAL_LENGTH];                             /**< staffid/groupid */
    TUP_CHAR    account[IM_D_MAX_ACCOUNT_LENGTH];                   /**< �˺� */
    TUP_CHAR    name[IM_D_MAX_NAME_LENGTH];                         /**< name/Ⱥ�� */
    TUP_CHAR    nativeName[IM_D_MAX_NAME_LENGTH];                   /**< �������� */
    TUP_INT64    imageID;                                           /**< �û�ͷ��ID */
    TUP_INT64    utctTime;                                          /**< �ûỰUTCʱ�� */
    TUP_INT8    code;                                               /**< ��Ϣ��*/
    TUP_BOOL    isRead;                                             /**< ��Ϣ�Ƿ��Ѷ�*/
    IM_S_CHATINFO_NOTIFY    chatInfo;                               /**< chat��Ϣ */  
    IM_S_SMSINFO            smsInfo;                                /**< sms��Ϣ */ 
}IM_S_RECENT_CONVERSATION_INFO;


/**
 *  ɾ������Ự������Ϣ
 */
typedef struct tagIM_S_DEL_RECENT_CONVERSATION_ARG
{
    TUP_BOOL    isDelAll;                                           /**< �Ƿ�ɾ�����У�ɾ������: true, ɾ������: false*/
    TUP_CHAR    conversationID[IM_D_MAX_ACCOUNT_LENGTH];            /**< ����Ự��ʶ���û��˺š�Ⱥid����� */
    IM_E_IM_RECENT_CONVERSATION_TYPE  type;                         /**< ����Ự���� */
}IM_S_DEL_RECENT_CONVERSATION_ARG;


/**
 *  ��ȡ����Ự������Ϣ
 */
typedef struct tagIM_S_GEL_RECENT_CONVERSATION_ARG
{
    TUP_INT64   timestamp;                                          /**< ʱ�����19000000000000��������ʱ���룩 */
    TUP_INT32   count;                                              /**< ��������Ự����*/
}IM_S_GEL_RECENT_CONVERSATION_ARG;


/**
 *  ��ȡ����Ự��Ӧ��Ϣ
 */
typedef struct tagIM_S_GEL_RECENT_CONVERSATION_ACK
{
    TUP_INT64    timestamp;                                         /**< ʱ�����19000000000000��������ʱ���룩 */
    TUP_S_LIST*    recentConversationList;                          /**< ����Ự��Ϣ�б�TUP_S_LIST�е�*dada�ṹ����ΪIM_S_RECENT_CONVERSATION_INFO*/
}IM_S_GEL_RECENT_CONVERSATION_ACK;

/**
 *  ������ϵ�˷����б�
 */
typedef struct tagIM_S_UPDATE_USERGROUP_ARG
{
    TUP_S_LIST*    usergrouplist;                                   /**< ���ѷ�����б�TUP_S_LIST�е�*dada�ṹ����ΪTUP_INT64 */
}IM_S_UPDATE_USERGROUP_ARG;

/**
 *  �̻�����������/��Ӧ
 */
typedef struct tagIM_S_SET_DISGROUP_POLICY_MSG
{
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< ȺID */ 
    IM_E_IMGROUP_ISFIXDISCUSS    policy;                            /**< �Ƿ�̻������� */     
}IM_S_SET_DISGROUP_POLICY_MSG;

/**
 *  �����������Ϣ
 */
typedef struct tagIM_S_SEND_DISGROUP_OPT_MSG
{
    IM_E_DISGROUP_OP_TYPE    type;                                  /**< �������� */ 
    TUP_CHAR    groupID[IM_D_GROUPID_LENGTH];                       /**< ������ID */ 
    TUP_S_LIST* params;                                             /**< �����б� TUP_S_LIST�е�*dada�ṹ����ΪTUP_CHAR*������ΪIM_D_MAX_NAME_LENGTH*/ 
}IM_S_SEND_DISGROUP_OPT_MSG;

//--------------------------------------------------------------�����ṹ�� end--------------------------------------------------------------

//--------------------------------------------------------------�ص����� begin--------------------------------------------------------------
/**
 * @brief ��Ҫ�û�������ʵ�ֵĻص�����
 * @param [in]  eventID �¼�ID
 * @param [in] body ��Ϣ��
 * @attention �ص���Ϣ�ڴ˺����н���
 * @return TUP_VOID
 */
typedef TUP_BOOL (*TUP_IM_FN_CALLBACK_PTR)(IM_E_EVENT_ID eventID, void *body);
//--------------------------------------------------------------�ص����� end--------------------------------------------------------------

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif//_TUP_IM_BASEDEF_H_

/** @}*/

/*
* History: \n
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
