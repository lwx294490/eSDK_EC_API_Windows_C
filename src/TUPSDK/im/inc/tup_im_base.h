/** 
* @file tup_im_base.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM��ϵͳ�������ͻ�������ͷ�ļ��� \n
*/


/**
*
*  @{
*/


#ifndef _TUP_IM_BASE_H_
#define _TUP_IM_BASE_H_

#include "tup_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

/**
 * ������Ϣ
 */
typedef struct tagTUP_S_LIST{
  TUP_VOID *data; 
  struct tagTUP_S_LIST *next;
}TUP_S_LIST;


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif //_TUP_IM_BASE_H_

/** @}*/

/*
* History: \n
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
