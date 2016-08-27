/** 
* @file tup_im_base.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM子系统数据类型基本定义头文件。 \n
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
 * 链表信息
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
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
