/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#ifndef DATA_H
#define DATA_H

#include "call_interface.h"
#include "call_advanced_interface.h"
#include "offlinefile_def.h"
#include "offlinefile_interface.h"
#include "tup_im_baseapi.h"
#include "tup_im_extendapi.h"
#include "tup_im_util.h"
#include "tup_conf_baseapi.h"
#include "tup_conf_otherapi.h"
#include "tup_conf_extendapi.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

enum GROUPLIST_COLUMNID
{
	COL_MEM_Compere, 
	COL_MEM_Status, 
	COL_MEM_Name, 
	COL_MEM_ACCOUNT,
	COL_MEM_CALLNO,
	COL_MEM_CALLSTATE,
	COL_MEM_SPK,
	COL_MEM_MUTE
};

enum STAFFLIST_COLUMNID
{
	COL_Status, 
	COL_Name, 
	COL_ACCOUNT, 
	COL_DptName,
	COL_Email,
	COL_BINDNO1,
	COL_BINDNO2,
	COL_MOBILE,
	COL_OFFICENUM,
	COL_OFFICENUM2,
	COL_HOMENUM,
	COL_OTHERNUM,
	COL_OTHERNUM2,
	COL_FAX,
	COL_TITLE
};

#define WM_HEARTBEAT_NOTIFY	(WM_USER+999)			//����
#define WM_MENU_SEND_IM		(WM_USER+1000)			//���ͼ�ʱ��Ϣ
#define WM_SHOW_DETAIL		(WM_USER+1001)			//��ʾ��ϵ������
#define WM_CLOSE_IM_WND		(WM_USER+1002)			//�رռ�ʱ��Ϣ�Ի���
#define WM_RECV_IM			(WM_USER+1003)			//�رռ�ʱ��Ϣ�Ի���
#define WM_HANGUP			(WM_USER+1004)			//�Ҷϵ绰
#define WM_UPDATE_CONTACT	(WM_USER+1005)			//ˢ����ϵ��
#define WM_CAll_CONNECTED	(WM_USER+1006)			//ͨ������
#define WM_CAll_END			(WM_USER+1007)			//ͨ������
#define WM_CAll_INCMING		(WM_USER+1008)			//����
#define WM_CAll_HOLD		(WM_USER+1009)			//����
#define WM_CAll_UNHOLD		(WM_USER+1010)			//ȡ������
#define WM_CALL_MIC_MUTE	(WM_USER+1011)			//��˷羲��
#define WM_CALL_MIC_UNMUTE	(WM_USER+1012)			//ȡ����˷羲��
#define WM_CALL_SPK_MUTE	(WM_USER+1013)			//����������
#define WM_CALL_SPK_UNMUTE	(WM_USER+1014)			//ȡ������������
#define WM_CALL_START_REC	(WM_USER+1015)			//��ʼ¼��
#define WM_CALL_END_REC		(WM_USER+1016)			//����¼��
#define WM_CALL_BLIND_TRAN	(WM_USER+1017)			//����ת��-äת
#define WM_CALL_SHOW_WND	(WM_USER+1018)			//��ʾ����������Ƶ����
#define WM_CLOSE_SET_DLG	(WM_USER+1019)			//�ر����öԻ���
#define WM_CLOSE_ENT_DLG	(WM_USER+1020)			//�ر���ҵͨѶ¼�Ի���
#define WM_CLOSE_DETAIL_DLG	(WM_USER+1021)			//�ر�����Ի���
#define WM_CAll_ADD_VIDEO	(WM_USER+1022)			//�յ�����ת��Ƶ����
#define WM_CAll_DEL_VIDEO	(WM_USER+1023)			//�յ���Ƶת��������
#define WM_NET_LEVEL		(WM_USER+1024)			//����������Ϣͨ��
#define WM_NET_INFO			(WM_USER+1025)			//����ͳ����Ϣ
#define WM_CAll_RGE_RESLUT	(WM_USER+1026)			//ע����
#define WM_CALL_BETRANSFER_CONF	     (WM_USER+1027)		   //ͨ����ת��������
#define WM_CALL_HOLE_RESULT	         (WM_USER+1028)		       //���б��ֳɹ�
#define WM_CALL_UNHOLE_RESULT	     (WM_USER+1029)		   //ȡ�����б��ֳɹ�
#define WM_CALL_BLIND_RESULT	     (WM_USER+1030)		   //����ת��-äת���
#define WM_CALL_OUTGOING	         (WM_USER+1031)		   //�����¼�////
#define WM_CALL_INFOCHANGE	         (WM_USER+1032)		   //������Ϣ�仯////


///�������鲿��
#define WM_CONF_CREATE_RET	(WM_USER+1050)			//��������ɹ�
#define WM_CONF_ADD_MEM_SUC	(WM_USER+1051)			//���ӳ�Ա�ɹ�
#define WM_CONF_ADD_MEM_FAIL (WM_USER+1052)			//���ӳ�Աʧ��
#define WM_CONF_MEM_SPK		(WM_USER+1053)			//��Ա����
#define WM_CONF_MEM_QUIT	(WM_USER+1054)			//��Ա����
#define WM_CONF_INCMING		(WM_USER+1055)			//��������
#define WM_CONF_CONNECTED	(WM_USER+1056)			//�������
#define WM_CONF_SUBJECT		(WM_USER+1057)			//����������
#define WM_CLOSE_CONF_WND	(WM_USER+1058)			//�رջ���Ի���
#define WM_CONF_REFESH_SIGNLE	(WM_USER+1059)		//ˢ�»��鵥����Ա
#define WM_CONF_REFESH_LIST	(WM_USER+1060)			//ˢ�»������г�Ա
#define WM_CONF_END			(WM_USER+1061)          //�����������


////�����ļ����/////
#define WM_SHOW_DOWNLOADIMAGE_IM		(WM_USER+1046) //ͼƬ�������֪ͨ
#define WM_SEND_IMAGEINFO_IM			(WM_USER+1047) //����ͼƬ��Ϣ
#define WM_RECV_OFFLINE_IM				(WM_USER+1048) // ������Ϣ

//�̶�Ⱥ��
#define WM_FIXGROUP_IDENTIFY_NOTIFY            (WM_USER+1101)   //�̶�Ⱥ����֤֪ͨ
#define WM_CONFIRM_JOINFIXEDGROUP_NOTIFY       (WM_USER+1102)   //��������̶�Ⱥ����
#define WM_MENU_GROUP_CHAT                     (WM_USER+1103)   //����Ⱥ�鼴ʱ��Ϣ
#define WM_FIXGROUP_DELETE_NOTIFY              (WM_USER+1104)   //ɾ��Ⱥ���Ա֪ͨ
#define WM_DISMISS_FIXEDGROUP_NOTIFY           (WM_USER+1105)   //�̶�Ⱥ���ɢ֪ͨ
#define WM_GROUP_INVITEDLG_CLOSE               (WM_USER+1106)   //�ر�Ⱥ��֪ͨ�Ի���
#define WM_GROUP_NOTIFY		                   (WM_USER+1107)	//Ⱥ��֪ͨ
#define WM_GROUP_INF_CHANGE	                   (WM_USER+1108)	//Ⱥ����Ϣ���
#define WM_GROUP_MEM_ADD	                   (WM_USER+1109)	//Ⱥ���Ա����
#define WM_GROUP_MEM_DEL	                   (WM_USER+1110)	//Ⱥ��֪ͨ
#define WM_GROUP_MEM_OWNER 	                   (WM_USER+1111)	//Ⱥ�����Ա���



//���ݻ������
#define WM_DATACONF_CREAT	             (WM_USER+1999)			//�������ݻ���ɹ�
#define WM_DATACONF_JOINSUCCESS          (WM_USER+2000)			//�������ݻ���ɹ�
#define WM_DATACONF_LOADCOM_SUCCESS      (WM_USER+2001)		    //���������ɹ�
#define WM_DATACONF_USER_ADD	         (WM_USER+2002)			//���ݻ����Ա����
#define WM_DATACONF_USER_DEL	         (WM_USER+2003)			//���ݻ����Ա�뿪
#define WM_DATACONF_AS_OWNER_NOTIFY      (WM_USER+2005)		    //����ӵ����֪ͨ
#define WM_DATACONF_AS_SCREENDATA_NOTIFY (WM_USER+2006)	        //��������֪ͨ
#define WM_DATACONF_AS_STATE_NOTIFY	     (WM_USER+2007)	        //����״̬֪ͨ
#define WM_DATACONF_UPDATE_PRESENTINFO   (WM_USER+2008)         //���±�����������Ϣ
#define WM_DATACONF_UPDATE_CHAIRMAININFO (WM_USER+2009)         //���±�����������Ϣ
#define WM_DATACONF_UPDATE_MUTE          (WM_USER+2010)         //���¾�����ȡ��������֪ͨ
#define WM_DATACONF_END                  (WM_USER+2011)         //�������֪ͨ/////
#define WM_IM_KICKOUT_NOTIFY			 (WM_USER+2012)         //�û���������֪ͨ/////
#define WM_DATACONF_DOCUMENT_WND	     (WM_USER+2013)	        //��ʾ����������Ƶ����
#define WM_DATACONF_LAYOUT_CHANGE	     (WM_USER+2014)	        //����ӵ���߱任����////
#define WM_CLOSE_DATACONF_WND		     (WM_USER+2015)	        //�رն�ý��Ự��

//��Ƶ���
#define WM_DATACONF_ADD_VIDEO	         (WM_USER+2100)	       //���ӱ�����Ƶ
#define WM_DATACONF_DEL_VIDEO	         (WM_USER+2101)	       //���ٱ�����Ƶ
//����װ����
#define WM_DATACONF_WB_DOC_NEW           (WM_USER+2130)	       //�½��װ��ĵ� 
#define WM_DATACONF_WB_PAG_NEW           (WM_USER+2131)	       //�½��װ�ҳ
#define WM_DATACONF_WB_DRAW              (WM_USER+2132)	       //ˢ�½�������
#define WM_DATACONF_WB_PAGE_IND          (WM_USER+2133)	       //ͬ������ҳ��
#define WM_DATACONF_WB_REFRESH_INFO      (WM_USER+2134)	       //���±����ĵ���Ϣ
#define WM_DATACONF_WB_DOC_DEL           (WM_USER+2135)	       //ɾ���װ��ĵ�
#define WM_DATACONF_WB_PAG_DEL           (WM_USER+2136)	       //ɾ���װ�ҳ
#define WM_DATACONF_WB_PAG_CPY           (WM_USER+2137)	       //������ǰҳ


//Menu ID
//Private Group
#define ID_PRIGROUP_MODIFY_MENU         32100
#define ID_PRIGROUP_DEL_MENU            32101
#define ID_PRIGROUP_ADD_MENU            32102
#define ID_PRIGROUP_ADD_CONTACT_MENU    32103
#define ID_PRIGROUP_ADD_UC_CONTACT_MENU 32104

#define ID_MAIN_SETTING_MENU			32201
#define ID_MAIN_PORTAL_MENU				32202
#define ID_MAIN_HELP_MENU				32203
#define ID_MAIN_LOGOUT_MENU				32204
#define ID_MAIN_EXIT_MENU				32205

//Private Contact
#define ID_PRIGROUP_DEL_CONTACT_MENU    32301
#define ID_PRIGROUP_MODIFY_CONTACT_MENU 32302
#define ID_PRIGROUP_CONTACT_DETAIL_MENU 32303
#define ID_PRIGROUP_INSTANTMSG_MENU     32304
#define ID_PRIGROUP_AUDIOCONF_MENU      32305

//Move Group List
#define ID_PRIGROUP_CONTACT_MOVE_MENU_START 32320
#define ID_PRIGROUP_CONTACT_MOVE_MENU_END	32399

//EntAddr Menu
#define ID_ENTADDR_ADD_CONTACT			32400
#define ID_ENTADDR_GROUP_ADD_MENU_START 32500
#define ID_ENTADDR_GROUP_ADD_MENU_END	32700

//IM 
#define ID_IM_GROUP_DEL_MEM_MENU        33100
#define ID_IM_GROUP_RECALL_MEM_MENU     33101

//CONF
#define ID_CONF_DEL_MEM_MENU        33100
#define ID_CONF_RECALL_MEM_MENU     33101
#define ID_CONF_MUTE_MEM_MENU		33102
#define ID_CONF_UNMUTE_MEM_MENU		33103

//DATACONF
#define ID_DATACONF_DEL_MEM_MENU               34100    //�Ƴ����ݻ����Ա////
#define ID_DATACONF_RECALL_MEM_MENU            34101      
#define ID_DATACONF_SETPRESENT_MEM_MENU        34102
#define ID_DATACONF_INVITEDTOSHARE_MEM_MENU    34103

//GROUP
#define ID_GROUP_RELEASE_MEM_MENU		34500		//��ɢȺ��
#define ID_GROUP_ADD_MEMBER_MENU		34501		//��ӳ�Ա
#define ID_GROUP_EXIT_MENU				34502		//�˳�Ⱥ��
#define ID_GROUP_ADD_MENU				34503     //���Ⱥ��



//ͨѶ¼
typedef std::map<TUP_INT64,IM_S_USERGROUPINFO> MAP_GROUP;
extern MAP_GROUP g_mapGroup;
typedef std::multimap<TUP_INT64,TUP_INT64> MAP_USER_GROUP;
extern MAP_USER_GROUP g_mapUserGroup;
typedef std::map<TUP_INT64,IM_S_CONTACTNFO> MAP_CONTACT;
extern MAP_CONTACT g_mapContact;
typedef std::map<TUP_INT64,IM_S_USERINFO> MAP_USER;
extern MAP_USER g_mapUser;
typedef std::map<TUP_INT64,IM_S_IMGROUPINFO> MAP_IMGROUP;
extern MAP_IMGROUP g_mapImGroup;

//ý������
typedef std::map<int,std::string> MAP_DEVICE;
extern MAP_DEVICE g_mapInDevice;
extern MAP_DEVICE g_mapOutDevice;
extern MAP_DEVICE g_mapVideoDevice;
extern int g_iIndeviceIndex;
extern int g_iOutdeviceIndex;
extern int g_iVideodeviceIndex;
extern int g_iMicLevel;
extern int g_iSpeakerLevel;

//������Ϣ
extern std::string g_Account;
extern std::string g_SipAccount;
extern std::string g_DataConfAddr;
extern std::string g_Name;
extern std::string g_BindNO;
extern TUP_INT64 g_UserID;

typedef struct tagCall_Member
{
	TUP_CHAR name[IM_D_MAX_NAME_LENGTH];				/**< �û��� */
	TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];			/**< ��Ա�˺� */ 
	TUP_CHAR CallNo[IM_D_MAX_PHONE_LENGTH];			/**< ���еĺ��� */
}CALL_MEMBER;
typedef std::map<std::string,CALL_MEMBER> MAP_SELECT_USER;


//call

#define USER_AGENT				"Huawei SoftCoPCA"

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}

#define SAFE_DELETE_ARRAY(pPoint) 	if(NULL != pPoint)\
{\
	delete[] pPoint;\
	pPoint = NULL;\
}

#define CHECK_POINTER(pPoint) if(NULL == pPoint)\
{\
	return;\
}

#define CHECK_POINTER_RETURN(pPoint,ret) if(NULL == pPoint)\
{\
	return ret;\
}

class map_value_finder
{
public:
	map_value_finder(const int &cmp_int):m_s_cmp_int(cmp_int){}
	bool operator ()(const std::map<int, int>::value_type &pair)
	{
		return pair.second == m_s_cmp_int;
	}
private:
	const int m_s_cmp_int;                    
};

//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 begin
class CUserQueryHelper
{
public:
	bool GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack
		, const TUP_INT8 acTelNum[]
	, IM_S_USERINFO& userInfo
		);

	bool GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo);
};
//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 end
#endif