/** 
* @file tup_im_util.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM子系统常用工具类接口头文件。 \n
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
 * @brief gzlib压缩
 * 
 * @param [in]  const TUP_CHAR *arg  <b>:</b> 待gzlib压缩的原始内容
 * @param [out] TUP_UCHAR **ack      <b>:</b> gzlib压缩后的内容，内存由接口内部分配
 * @param [in/out] TUP_PTR *len      <b>:</b> 作为入参时为待gzlib压缩的原始内容长度，出参时为gzlib压缩后的内容长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 存储压缩后内容的内存ack在使用完后需要调用者释放
 * @see tup_im_gzlib_uncomp
 **/
TUP_API TUP_RESULT tup_im_gzlib_comp(IN const TUP_CHAR* arg, OUT TUP_UCHAR** ack, IO TUP_PTR* len);


/**
 * @brief gzlib解压缩
 * 
 * @param [in] const TUP_CHAR* arg  <b>:</b> 待gzlib解压缩的原始内容
 * @param [out] TUP_CHAR* *ack      <b>:</b> gzlib解压缩后的内容，内存由接口内部分配
 * @param [in/out] TUP_PTR* len     <b>:</b> 作为入参时为待gzlib解压缩的原始内容长度，出参时为gzlib解压缩后的内容长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 存储解压缩后内容的内存ack在使用完后需要调用者释放
 * @see tup_im_gzlib_comp
 **/
TUP_API TUP_RESULT tup_im_gzlib_uncomp(IN const TUP_CHAR* arg, OUT TUP_CHAR** ack, IO TUP_PTR* len);


/**
 * @brief Base64编码
 * 
 * @param [in] const TUP_UCHAR* arg  <b>:</b> 待Base64编码的原始内容
 * @param [out] TUP_CHAR* ack        <b>:</b> Base64编码后的内容，内存由调用者分配
 * @param [in/out] TUP_UPTR* len     <b>:</b> 作为入参时为待Base64编码的原始内容长度，出参时为Base64编码后的内容长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 存储编码后内容的内存大小应不小于原始内容长度的"4/3倍+1"
 * @see tup_im_base64_decode
 **/
TUP_API TUP_RESULT tup_im_base64_encode(IN const TUP_UCHAR* arg, OUT TUP_CHAR* ack, IO TUP_UPTR* len);


/**
 * @brief  Base64解码
 * 
 * @param [in] const TUP_CHAR* arg   <b>:</b> 待Base64解码的原始内容
 * @param [out] TUP_UCHAR* ack       <b>:</b> Base64解码后的内容
 * @param [in/out] TUP_UPTR* len     <b>:</b> 作为入参时为待Base64编码的原始内容长度，出参时为Base64编码后的内容长度
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 存储解码后内容的内存大小应不小于原始内容长度的"3/4倍+1"
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
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/




