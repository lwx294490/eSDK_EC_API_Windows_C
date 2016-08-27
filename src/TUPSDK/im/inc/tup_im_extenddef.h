/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM��ϵͳ��չҵ���ܽӿڽṹ�嶨��ͷ�ļ��� \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_EXTENDDEF_H_
#define _TUP_IM_EXTENDDEF_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#define IM_D_MAX_FILEPATH_LENGTH (260)						/**< �ļ�·����󳤶� */


#define IM_D_MAX_SMSID_LENGTH (16)							/**< ����ID��󳤶� */


#define IM_D_MAX_SMSCONENT_LENGTH (350)						/**< ����������󳤶� */


#define IM_D_MAX_SMSRECEIVEER_LENGTH (1000)					/**< �����ռ�����󳤶� */

/**
 *  �ļ�������ֹԭ��
 */
typedef enum tagIM_E_FILETRANSFER_P2PFILESTOP_REASON
{
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_UNKNOW		= -1,	/**< δ֪����ֹͣ */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_NORMAL		= 0,	/**< ����ֹͣ */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_TIMEOUT	= 1,	/**< ��ʱֹͣ */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_SENDERROR	= 2,	/**< ���ͷ�����������ֹͣ */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_ACCEPTERROR= 3,	/**< ���շ�����������ֹͣ */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_COMPLETED	= 4,	/**< �ļ��������ֹͣ */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_ABNORMAL	= 5		/**< �ļ�����δ���ֹͣ */
}IM_E_FILETRANSFER_P2PFILESTOP_REASON;

/**
 *  �ļ����俪ʼ���
 */
typedef enum tagIM_E_P2PFILE_START_RESLUT
{
	IM_E_P2PFILE_START_RESLUT_SUCCESS				= 0,	/**< �ɹ� */
	IM_E_P2PFILE_START_RESLUT_MODEDETECT_SUCCESS	= 1,    /**< ��ͨ�Լ��ɹ� */
	IM_E_P2PFILE_START_RESLUT_TIMEOUT				= -100,	/**< ��ʱ */
	IM_E_P2PFILE_START_RESLUT_TARGETOFFLINE         = -104,	/**< �Է����� */
	IM_E_P2PFILE_START_RESLUT_PEERREJECT			= -112, /**< �Է��ܾ� */
	IM_E_P2PFILE_START_RESLUT_NOFILETOSEND			= -116, /**< ��ǰ�ļ������� */
	IM_E_P2PFILE_START_RESLUT_SENDERROR				= -120, /**< ����ʧ�� */
	IM_E_P2PFILE_START_RESLUT_ACCEPTERROR			= -121, /**< ����ʧ�� */
	IM_E_P2PFILE_START_RESLUT_OPENFILEERROR			= -122, /**< ���ļ�ʧ�� */
	IM_E_P2PFILE_START_RESLUT_CANCELED				= -124, /**< ȡ���ļ����� */
	IM_E_P2PFILE_START_RESLUT_FILEBUSY				= -125, /**< �ļ������������ */
	IM_E_P2PFILE_START_RESLUT_FILEISEMPTY			= -128, /**< �ļ�����Ϊ�� */
	IM_E_P2PFILE_START_RESLUT_FILEMODE_MISMATCH		= -132, /**< �ļ��������粻ͨ */
	IM_E_P2PFILE_START_RESLUT_REGIONALISOLATION		= -136	/**< �ļ�������� */
}IM_E_P2PFILE_START_RESLUT;

/**
 *  Ⱥ�����ļ���ѯ����
 */
typedef enum tagIM_E_GROUPFILE_QUERY_TYPE
{
	IM_E_GROUPFILE_QUERY_TYPE_FILENAME				= 0,	/**< ���ļ������� */
	IM_E_GROUPFILE_QUERY_TYPE_FILETYPE				= 1,	/**< ���ļ��������� */
	IM_E_GROUPFILE_QUERY_TYPE_FILEID				= 2		/**< ���ļ�ID���� */
}IM_E_GROUPFILE_QUERY_TYPE;

/**
 *  Ⱥ�����ļ�֪ͨ��ʶ
 */
typedef enum tagIM_E_GROUPFILE_NOTIFE_TYPE
{
	IM_E_GROUPFILE_NOTIFE_TYPE_FILECHANGE			= 0		/**< Ⱥ�����ļ�֪ͨ */
}IM_E_GROUPFILE_NOTIFE_TYPE;

/**
 *  Ⱥ�����ļ��������
 */
typedef enum tagIM_E_GROUPFILE_OPT_TYPE
{
	IM_E_GROUPFILE_OPT_TYPE_ADD						= 0,	/**< ����Ⱥ�ļ� */
	IM_E_GROUPFILE_OPT_TYPE_DEL						= 1		/**< ɾ��Ⱥ�ļ� */
}IM_E_GROUPFILE_OPT_TYPE;

/**
 *  �ļ���Ϣ
 */
typedef struct tagIM_S_P2PFILE_INFO
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];				/**< �Է��˺� */ 
    TUP_CHAR filePath[IM_D_MAX_FILEPATH_LENGTH];			/**< �����ļ�·�� */ 
}IM_S_P2PFILE_INFO;


/**
 *  Ⱥ�����ļ���Ϣ
 */
typedef struct tagIM_S_GROUPFILE_INFO
{
    TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< �ļ�ID */
	TUP_CHAR	uploadTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< ���������ϴ��ɹ���ʱ�� */
	TUP_CHAR	uploadUserAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< �ϴ����˺� */
	TUP_CHAR	uploadUserName[IM_D_MAX_NAME_LENGTH];		/**< �ϴ������� */
	TUP_CHAR	fileURL[IM_D_URL_LENGTH];					/**< �ļ�URL */
	TUP_CHAR	fileName[IM_D_MAX_NAME_LENGTH];				/**< �ļ��� */
	TUP_INT64	fileSize;									/**< �ļ���С */
	TUP_CHAR	prefileId[IM_D_MAX_PASSWORD_LENGTH];		/**< �ļ�Ӧ�Ե�Ԥ�ϴ�ID */
}IM_S_GROUPFILE_INFO;

/**
 *  �����ļ�����
 */
typedef struct tagIM_S_SENDP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**< �ļ���Ϣ */
    TUP_UINT32	timeoutSeconds;								/**< �ļ�����ȴ���ʱʱ�� */ 
    TUP_BOOL	isEncrypt;									/**< �Ƿ���м��ܣ����ܻ�Ӱ�촫���ٶȣ� */ 
}IM_S_SENDP2PFILE_ARG;


/**
 *  �����ļ�
 */
typedef struct tagIM_S_ACCEPTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**< �ļ���Ϣ */
}IM_S_ACCEPTP2PFILE_ARG;

/**
 *  �ܾ��ļ�����
 */
typedef struct tagIM_S_REJECTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**< �ļ���Ϣ */
}IM_S_REJECTP2PFILE_ARG;

/**
 *  ȡ���ļ�����
 */
typedef struct tagIM_S_CANCELP2PFILE_ARG
{
    IM_S_P2PFILE_INFO	fileInfo;							/**<  �ļ���Ϣ */
}IM_S_CANCELP2PFILE_ARG;

/**
 *  �ļ�������֪ͨ
 */
typedef struct tagIM_S_P2PFILE_RESULT_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/**< �Է��˺� */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< �ļ��� */
	IM_E_P2PFILE_START_RESLUT	startresult;				/**< ��ʼ�ļ�����Ľ�� */
	TUP_INT32	stopresult;									/**< ��ͣ�ļ�����Ľ�� */
}IM_S_P2PFILE_RESULT_NOTIFY;


/**
 *  �ļ��������֪ͨ
 */
typedef struct tagIM_S_FILEPROCESS_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/**< �Է��˺� */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< �ļ��� */
	TUP_INT64	current;									/**< ��ǰ�Ѵ����С */
	TUP_INT64	total;										/**< �ļ��ܴ�С */
	TUP_CHAR	dir[IM_D_MAX_DESC_LENGTH];					/**< �ļ������� */
	TUP_INT64	totalFileCount;								/**< �ļ����� */
	TUP_INT32	currentFileIndex;							/**< ��ǰ�ļ���� */
	TUP_INT64	currentFileSize;							/**< �ļ����Ѿ�����Ĵ�С */
	TUP_INT64	totalFileSize;								/**< �ļ��������ļ��ܴ�С */
}IM_S_FILEPROCESS_NOTIFY;

/**
 *  �յ��ļ���������֪ͨ
 */
typedef struct tagIM_S_P2PFILECHOOSE_NOTIFY
{
	TUP_CHAR	targetAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< �Է��˺� */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< �ļ��� */
	TUP_INT64	totalSize;									/**< �ļ��ܴ�С */
	TUP_BOOL	bIsPic;										/**< �Ƿ���ͼƬ */
	TUP_BOOL	bisDir;										/**< �Ƿ����ļ��� */
}IM_S_P2PFILECHOOSE_NOTIFY;

/**
 *  �ļ������ϱ��ļ���Ϣ
 */
typedef struct tagIM_S_P2PFILESTATISTIC_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/**< �Է��˺� */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/**< �ļ��� */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON	reason;			/**< ֹͣԭ�� */
}IM_S_P2PFILESTATISTIC_NOTIFY;


/**
 *  ���ŷ���
 */
typedef struct tagIM_S_SENDSMS_ARG
{
    TUP_CHAR	msgID[IM_D_MAX_SMSID_LENGTH];				/**< �ͻ��˲�������ϢID */ 
    TUP_CHAR	bindNo[IM_D_MAX_PHONE_LENGTH];				/**< ��ǰ�û��İ󶨺��� */ 
    TUP_CHAR	content[IM_D_MAX_SMSCONENT_LENGTH];			/**< �������� */ 
    TUP_CHAR	receiverList[IM_D_MAX_SMSRECEIVEER_LENGTH];	/**< �������б��԰�Ƿֺŷָ� */ 
    TUP_CHAR	sendTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< ���ŷ���ʱ�� 19000000000000��������ʱ���룩 */ 
	TUP_BOOL	needReceipt;								/**< �Ƿ���Ҫ��ִ */ 
}IM_S_SENDSMS_ARG;

/**
 *  ����֪ͨ
 */
typedef struct tagIM_S_SENDSMS_NOTIFY
{
    TUP_CHAR	msgID[IM_D_MAX_SMSID_LENGTH];				/**< �ͻ��˲�������ϢID */ 
    TUP_CHAR	origin[IM_D_MAX_PHONE_LENGTH];				/**< ���ͷ����� */ 
	TUP_CHAR	target[IM_D_MAX_PHONE_LENGTH];				/**< ���շ�����*/
    TUP_CHAR	content[IM_D_MAX_SMSCONENT_LENGTH];			/**< �������� */ 
    TUP_CHAR	sendTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< ���ŷ���ʱ�� 19000000000000��������ʱ���룩 */ 
    IM_E_SMS_NOTIFY_TYPE	smsType;						/**< ���յ��Ķ�����Ϣ������ */
	TUP_INT64	serverMsgID;								/**< ��������ϢID */
}IM_S_SENDSMS_NOTIFY;


/**
 * Ԥ�ϴ��ļ���Ϣ
 */
typedef struct tagIM_S_GROUPFILE_PRE_UPLOAD_ARG
{
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID */
	TUP_CHAR	fileName[IM_D_MAX_NAME_LENGTH];				/**< �ļ��� */
	TUP_INT64	fileSize;									/**< �ļ���С */
}IM_S_GROUPFILE_PRE_UPLOAD_ARG;

/**
 * Ԥ�ϴ��ļ�ID
 */
typedef struct tagIM_S_GROUPFILE_PRE_UPLOAD_ACK
{
	TUP_CHAR	prefileId[IM_D_MAX_PASSWORD_LENGTH];		/**< Ԥ�ϴ��ļ�ID */
}IM_S_GROUPFILE_PRE_UPLOAD_ACK;

/**
 * Ⱥ�����ļ��ϴ����֪ͨ����
 */
typedef struct tagIM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ARG
{
	TUP_CHAR	prefileId[IM_D_MAX_PASSWORD_LENGTH];		/**< Ԥ�ϴ��ļ�ID */
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID */
	TUP_CHAR	uploadUserAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< �ϴ����˺� */
	TUP_CHAR	fileName[IM_D_MAX_NAME_LENGTH];				/**< �ļ��� */
	TUP_INT64	fileSize;									/**< �ļ���С */
	TUP_CHAR	fileURL[IM_D_URL_LENGTH];					/**< �ļ�URL */
	TUP_BOOL	result;										/**< �ϴ���� */
}IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ARG;

/**
 * Ⱥ�����ļ��ϴ����֪ͨ����
 */
typedef struct tagIM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ACK
{
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< �ļ�ID */
	TUP_CHAR	uploadTime[IM_D_MAX_TIMESTAMP_LENGTH];		/**< ���������ϴ��ɹ���ʱ�� */
}IM_S_GROUPFILE_REPORT_UPLOAD_RESULT_ACK;

/**
 * Ⱥ�����ļ�Ԥɾ������
 */
typedef struct tagIM_S_GROUPFILE_PRE_DELETE_ARG
{
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< �ļ�ID */
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID */
}IM_S_GROUPFILE_PRE_DELETE_ARG;

/**
 * Ⱥ�����ļ�Ԥɾ����Ӧ
 */
typedef struct tagIM_S_GROUPFILE_PRE_DELETE_ACK
{
	TUP_CHAR	preDeleteFileID[IM_D_MAX_PASSWORD_LENGTH];	/**< Ԥɾ���ļ�ID */
}IM_S_GROUPFILE_PRE_DELETE_ACK;

/**
 * Ⱥ�����ļ�ɾ�����֪ͨ����
 */
typedef struct tagIM_S_GROUPFILE_REPORT_DELETE_RESULT_ARG
{
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< �ļ�ID */
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID */
}IM_S_GROUPFILE_REPORT_DELETE_RESULT_ARG;

/**
 * Ⱥ�����ļ���ѯ����
 */
typedef struct tagIM_S_GROUPFILE_QUERY_ARG
{
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID */
	TUP_CHAR	queryKey[IM_D_GENEAL_LENGTH] ;				/**< �ؼ��� (����) */
	IM_E_GROUPFILE_QUERY_TYPE	queryType;					/**< Ⱥ�����ļ���ѯ���� */
	TUP_INT32	offset;										/**< ��ѯƫ���� (ѡ��) */ 
	TUP_INT32	count;										/**< ���β�ѯ������ص�����(����) */ 
}IM_S_GROUPFILE_QUERY_ARG;

/**
 * Ⱥ�����ļ���ѯ��Ӧ
 */
typedef struct tagIM_S_GROUPFILE_QUERY_ACK
{
	TUP_INT32	recordAmount;								/**< �ܼ�¼�� */ 
    TUP_S_LIST*	groupFileList;					/**< Ⱥ�����ļ��б� TUP_S_LIST�е�*dada�ṹ����Ϊ IM_S_GROUPFILE_INFO*/ 
}IM_S_GROUPFILE_QUERY_ACK;

/**
 *  Ⱥ�����ļ����֪ͨ
 */
typedef struct tagIM_S_GROUPFILE_NOTIFY
{
	TUP_CHAR	origin[IM_D_MAX_ACCOUNT_LENGTH];			/**< ���ͷ��˺�*/
	TUP_CHAR	target[IM_D_MAX_ACCOUNT_LENGTH];			/**< ���շ��˺�*/
	TUP_CHAR	groupId[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID */
	IM_E_GROUPFILE_NOTIFE_TYPE	type;						/**< ֪ͨ��ʶ*/
	TUP_CHAR	fileId[IM_D_MAX_PASSWORD_LENGTH];			/**< �ļ�ID */
	IM_E_GROUPFILE_OPT_TYPE	opttype;						/**< Ⱥ�ռ��ļ�������� */
	TUP_CHAR	timeStamp[IM_D_MAX_TIMESTAMP_LENGTH];		/**< Ⱥ�ռ�����ʱ���ID */
	TUP_INT64	totalSize;									/**< �ܿռ��С */
	TUP_INT64	remainSize;									/**< ʣ��ռ��С */
}IM_S_GROUPFILE_NOTIFY;


/**
 * ����״̬
 */
typedef struct tagIM_S_LINKAGE_STATUS
{
    TUP_BOOL  bisLinkage;   /**< ����״̬����������: true, �����ر�: false */
}IM_S_LINKAGE_STATUS;


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#endif //_TUP_IM_EXTENDDEF_H_

/** @}*/

/*
* History: \n
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
