#pragma once
#include "tup_im_baseapi.h"
#include "call_interface.h"
#include "call_advanced_interface.h"
#include "tup_conf_baseapi.h"
#include "tup_conf_otherapi.h"
#include "tup_conf_extendapi.h"

#define WM_MEET_CREATE_SUCCESS			(WM_USER+1000)			//��������ɹ�
#define WM_MEET_MANAGER_CONNECTED		(WM_USER+1001)			//��ϯ�������ɹ�
#define WM_MEET_INVITE					(WM_USER+1002)			//��������
#define WM_MEET_MEMBER_JOINED_SUCCESS	(WM_USER+1003)			//�ɹ�����һ������μ���
#define WM_MEET_MEMBER_REFRESH			(WM_USER+1004)			//ˢ�»����б�
#define WM_MEET_MEM_SPEAK				(WM_USER+1005)			//��ʾ������
#define WM_MEET_ENDED					(WM_USER+1006)			//��������
#define WM_DATACONF_CREAT				(WM_USER+1007)			//��������
#define WM_DATACONF_JOINSUCCESS			(WM_USER+1008)			//�ɹ��������ݻ���
#define WM_DATACONF_LOADCOM_SUCCESS		(WM_USER+1009)			//���������ɹ�
#define WM_USER_KICKOUT			(WM_USER+1010)		 // �û����߳�
#define WM_DATACONF_AS_STATE_NOTIFY	     (WM_USER+1011)	        //����״̬֪ͨ
#define WM_DATACONF_AS_OWNER_NOTIFY      (WM_USER+1012)		    //����ӵ����֪ͨ
#define WM_DATACONF_AS_SCREENDATA_NOTIFY (WM_USER+1013)	        //��������֪ͨ
#define WM_DATACONF_USER_ADD	         (WM_USER+1014)			//���ݻ����Ա����
#define WM_DATACONF_USER_DEL	         (WM_USER+1015)			//���ݻ����Ա�뿪
#define WM_DATACONF_UPDATE_PRESENTINFO   (WM_USER+1016)         //���±�����������Ϣ
#define WM_DATACONF_UPDATE_CHAIRMAININFO (WM_USER+1017)         //���±�����������Ϣ
#define WM_DATACONF_END                  (WM_USER+1018)         //�������֪ͨ/////

class NotifyCallBack
{
private:
	NotifyCallBack(void);
	~NotifyCallBack(void);
public:
	static TUP_BOOL IMNotify(IM_E_EVENT_ID eventID, void *body);
	static TUP_VOID CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody);
	static void APIENTRY ConfComASNotify(CONF_HANDLE confHandle, int nType, unsigned int nValue1, unsigned long nValue2, void* pVoid, int nSize);
	static TUP_VOID TUP_STDCALL ConfNotify(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);
};


