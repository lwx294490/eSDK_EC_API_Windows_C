/** 
* @file tup_im_util.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM��ϵͳ���ù�����ӿ�ͷ�ļ��� \n
*/


/**
*
*  @{
*/


#ifndef __TUP_IM_UTIL_H__
#define __TUP_IM_UTIL_H__


#include "tup_im_basedef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/**
 * @brief gzlibѹ��
 * 
 * @param [in]  const TUP_CHAR *arg  <b>:</b> ��gzlibѹ����ԭʼ����
 * @param [out] TUP_UCHAR **ack      <b>:</b> gzlibѹ��������ݣ��ڴ��ɽӿ��ڲ�����
 * @param [in/out] TUP_PTR *len      <b>:</b> ��Ϊ���ʱΪ��gzlibѹ����ԭʼ���ݳ��ȣ�����ʱΪgzlibѹ��������ݳ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �洢ѹ�������ݵ��ڴ�ack��ʹ�������Ҫ�������ͷ�
 * @see tup_im_gzlib_uncomp
 **/
TUP_API TUP_RESULT tup_im_gzlib_comp(IN const TUP_CHAR* arg, OUT TUP_UCHAR** ack, IO TUP_PTR* len);


/**
 * @brief gzlib��ѹ��
 * 
 * @param [in] const TUP_CHAR* arg  <b>:</b> ��gzlib��ѹ����ԭʼ����
 * @param [out] TUP_CHAR* *ack      <b>:</b> gzlib��ѹ��������ݣ��ڴ��ɽӿ��ڲ�����
 * @param [in/out] TUP_PTR* len     <b>:</b> ��Ϊ���ʱΪ��gzlib��ѹ����ԭʼ���ݳ��ȣ�����ʱΪgzlib��ѹ��������ݳ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �洢��ѹ�������ݵ��ڴ�ack��ʹ�������Ҫ�������ͷ�
 * @see tup_im_gzlib_comp
 **/
TUP_API TUP_RESULT tup_im_gzlib_uncomp(IN const TUP_CHAR* arg, OUT TUP_CHAR** ack, IO TUP_PTR* len);


/**
 * @brief Base64����
 * 
 * @param [in] const TUP_UCHAR* arg  <b>:</b> ��Base64�����ԭʼ����
 * @param [out] TUP_CHAR* ack        <b>:</b> Base64���������ݣ��ڴ��ɵ����߷���
 * @param [in/out] TUP_UPTR* len     <b>:</b> ��Ϊ���ʱΪ��Base64�����ԭʼ���ݳ��ȣ�����ʱΪBase64���������ݳ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �洢��������ݵ��ڴ��СӦ��С��ԭʼ���ݳ��ȵ�"4/3��+1"
 * @see tup_im_base64_decode
 **/
TUP_API TUP_RESULT tup_im_base64_encode(IN const TUP_UCHAR* arg, OUT TUP_CHAR* ack, IO TUP_UPTR* len);


/**
 * @brief  Base64����
 * 
 * @param [in] const TUP_CHAR* arg   <b>:</b> ��Base64�����ԭʼ����
 * @param [out] TUP_UCHAR* ack       <b>:</b> Base64����������
 * @param [in/out] TUP_UPTR* len     <b>:</b> ��Ϊ���ʱΪ��Base64�����ԭʼ���ݳ��ȣ�����ʱΪBase64���������ݳ���
 * @retval TUP_API TUP_RESULT <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �洢��������ݵ��ڴ��СӦ��С��ԭʼ���ݳ��ȵ�"3/4��+1"
 * @see tup_im_base64_encode
 **/
TUP_API TUP_RESULT tup_im_base64_decode(IN const TUP_CHAR* arg, OUT TUP_UCHAR* ack, IO TUP_UPTR* len);




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif  /* __TUP_IM_UTIL_H__ */

/** @}*/

/*
* History: \n
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/




