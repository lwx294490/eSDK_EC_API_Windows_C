/** 
* @file tup_im_baseapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* 描述：TUP IM子系统基础业务功能接口头文件。 \n
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
 * @brief 初始化im库
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 初始化im库是使用im业务必需的第一步，请最先执行
 * @see tup_im_uninit
 **/ 
TUP_API TUP_RESULT tup_im_init();

/**
 * @brief 卸载im库
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 请确保需要的im业务已经完成才能卸载im库
 * @see tup_im_init
 **/
TUP_API TUP_RESULT tup_im_uninit();

/**
 * @brief 设置服务器地址
 * @param [in]  ip 服务器地址
 * @param [in]  port 服务器端口
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 初始化后，登录前设置
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setserveraddress(IN const TUP_CHAR* ip, IN TUP_UINT16 port);

/**
 * @brief 登录（同步接口）
 * @param [in]  arg 登录请求
 * @param [out] ack 登录结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention NA
 * @see tup_im_logout
 * @see tup_im_sendheartbeat
 **/
TUP_API TUP_RESULT tup_im_login(IN const IM_S_LOGIN_ARG* arg, OUT IM_S_LOGIN_ACK* ack);

/**
 * @brief 退出登录（异步接口）
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 退出结果在回调通知中返回：IM_E_EVENT_IM_LOGOUT_NOTIFY
 * @see tup_im_login
 **/
TUP_API TUP_RESULT tup_im_logout();

/**
 * @brief 注册回调消息（异步接口）
 * @param [in]  callback IM业务回调处理函数地址,由用户声明和定义，处理IM业务相关的事件
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 正常流程下，callback返回值为TUP_TRUE;
 * @see TUP_IM_FN_CALLBACK_PTR
 **/
TUP_API TUP_RESULT tup_im_register_callback(IN TUP_IM_FN_CALLBACK_PTR callback);

/**
 * @brief brief 设置并通知输入/停止输入状态（异步接口）
 * @param[ in]  arg 当前用户键盘输入状态
 * @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 一段时间没有输入操作时，需要发送停止输入状态，避免用户一直处于输入状态；接收方收到发送方的输入状态变更通知：IM_E_EVENT_IM_SENDIMINPUT_NOTIFY 
 *            <br>该函数不关注服务器响应结果返回
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_notifyiminputting(IN const IM_S_CHAT_STATUS_ARG* arg);

/**
 * @brief 获取联系人列表（同步接口）
 * @param [in]  arg 查询联系人列表请求
 * @param [out] ack 查询联系人列表响应
 * @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *            <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_getcontactlist(IN const IM_S_GETCONTACTLIST_ARG* arg, OUT IM_S_GETCONTACTLIST_ACK* ack);

/**
* @brief 获取业务配置数据请求（同步接口）
* @param [in]  arg 查询业务配置数据请求
* @param [out] ack 查询业务配置数据结果响应
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
*        <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏
* @see tup_im_release_tup_list
*/
TUP_API TUP_RESULT tup_im_getserviceprofile(IN const IM_S_GETSERVICEPROFILEARG* arg, OUT IM_S_SERVICEPROFILEACK* ack);

/**
* @brief 获取系统链接请求（异步接口）
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention 获取系统链接的消息响应：IM_E_EVENT_IM_SYSURLRET_NOTIFY
* @see NA
*/
TUP_API TUP_RESULT tup_im_getsysurl();

/**
* @brief 获取用户信息请求（精确查询）
* @param [in]  arg 查询用户请求
* @param [out] ack 拥有账号的用户信息
* @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
*
* @attention arg中可以填写账号或staffID
* @see NA
*/
TUP_API TUP_RESULT tup_im_getuserinfo(IN const IM_S_GETUSERINFOARG* arg, OUT IM_S_USERINFO* ack);

/**
 * @brief 添加好友和联系人分组 （同步接口）
 * @param [in]  arg 添加好友分组请求
 * @param [out] ack 添加好友分组响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addusergroup(IN const IM_S_ADDUSERGROUP_ARG* arg, OUT IM_S_ADDUSERGROUP_ACK* ack);

/**
 * @brief 修改好友和联系人分组 （同步接口）
 * @param [in]  arg 修改好友分组请求
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_modusergroup(IN const IM_S_MODUSERGROUP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief 删除好友和联系人分组 （同步接口）
 * @param [in]  id 好友和联系人分组ID
 * @param [out] result 操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 删除该分组前，需要删除或移动(若产品定义默认分组，则可选择移动至默认分组)该组内的所有好友，清空该分组内成员，再删除该分组
 * @see tup_im_delfriendorcontact
 **/
TUP_API TUP_RESULT tup_im_delusergroup(IN TUP_INT64 id, OUT TUP_BOOL* result);

/**
 * @brief 更新联系人分组列表顺序至服务器
 * 
 * @param [in]  arg    <b>:</b> 联系人分组ID顺序列表
 * @param [out] result <b>:</b> 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此函数不关注服务器处理结果
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_update_usergroup(IN IM_S_UPDATE_USERGROUP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief 添加账号用户为好友（同步接口）
 * @param [in]  arg 添加账号用户为好友请求
 * @param [out] ack 添加账号用户为好友响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 成功添加后，被添加者会收到被成功添加通知:IM_E_EVENT_IM_ADDFRIEND_NOTIFY
 * @see tup_im_delfriendorcontact
 **/
TUP_API TUP_RESULT tup_im_addfriend(IN const IM_S_ADDFRIEND_ARG* arg, OUT IM_S_ADDFRIEND_ACK* ack);

/**
 * @brief 删除好友或者联系人（同步接口）
 * @param [in]  arg 从某一个分组中删除好友或/联系人
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 删除包括账号用户类型的好友和自定义联系人类型的好友
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_delfriendorcontact(IN const IM_S_DELCONTACT_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief 添加自定义联系人为好友 （同步接口）
 * @param [in]  arg 添加自定义联系人为好友请求
 * @param [out] ack 添加自定义联系人响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 添加成功后，ack会返回联系人的id；arg请求需要填写自己的staffID
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addcontact(IN const IM_S_ADDCONTACT_ARG* arg, OUT IM_S_ADDCONTACT_ACK* ack);

/**
 * @brief 修改自定义联系人好友 （同步接口）
 * @param [in]  arg 修改自定义联系人请求
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_modcontact(IN const IM_S_MODCONTACT_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief 移动或复制联系人/好友至其他分组 （同步接口）
 * @param [in]  arg 移动或复制联系人/好友至其他分组请求
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_movecontactgroup(IN const IM_S_MODCONTACTGROUP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief 探测用户状态 （异步接口，如果用户在线，则会产生IM_E_EVENT_USERSTATUS_NOTIFY事件通知结果，如果用户离线则无事件产生。）
 * @param [in]  arg 帐号列表，其中arg->data 为用户账号，类型为TUP_CHAR[]
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 成功探测后，会返回用户的状态：IM_E_EVENT_USERSTATUS_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_detectuserstatus(IN const TUP_S_LIST* arg);

/**
 * @brief 订阅非好友用户状态 （异步接口）
 * @param [in]  arg 帐号列表，其中arg->data 为用户账号，类型为TUP_CHAR[]
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该函数不关注服务器响应结果返回；
 *          <br>订阅后的非好友用户状态变更时，会收到回调通知：IM_E_EVENT_USERSTATUS_NOTIFY
 * @see tup_im_subscribeuserstatus 
 **/
TUP_API TUP_RESULT tup_im_subscribeuserstatus(IN const TUP_S_LIST* arg);

/**
 * @brief 取消订阅非好友用户状态 （异步接口）
 * @param [in]  arg 帐号列表，其中arg->data 为用户账号，类型为TUP_CHAR[]
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 注销前需要取消订阅，避免下次上线前被推送过多的用户状态消息导致登录耗时过长；该函数不关注服务器响应结果返回
 * @see tup_im_subscribeuserstatus 
 **/
TUP_API TUP_RESULT tup_im_unsubscribeuserstatus(IN const TUP_S_LIST* arg);


/**
 * @brief 发送文本消息 （异步接口）
 * @param [in]  arg 发送文本消息请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 发送的消息内容过长时（建议阈值为500），请使用压缩和base64编码接口处理后再发送；
 *          <br>接收方会收到新即时消息通知：IM_E_EVENT_IM_CODECHAT_NOTIFY；
 *          <br>在接收方离线状态下发送的消息，接收方上线后会收到新即时消息批量通知：IM_E_EVENT_IM_CHATLIST_NOTIFY
 * @see tup_im_gzlib_comp;
 * @see    tup_im_base64_encode;
 **/
TUP_API TUP_RESULT tup_im_sendim(IN const IM_S_SENDIM_ARG* arg);

/**
 * @brief 设置消息已读（同步接口）
 * @param [in]  arg 文本消息已读设置请求 其中arg->messageinfo->data IM_S_MESSAGEINFO
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 设置消息已读结果由函数返回值返回
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setmessageread(IN IM_S_SETMESSAGEREAD_ARG* arg);

/**
 * @brief 获取漫游消息 （同步接口）
 * @param [in]  arg 查询漫游消息请求
 * @param [out] ack 查询漫游消息响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *          <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_queryHistoryMessage(IN const IM_S_QUERYHISTORYMESSAGE_ARG* arg, OUT IM_S_QUERYHISTORYMESSAGE_ACK* ack);

/**
 * @brief 获取部门列表 （同步接口）
 * @param [in]  deptid 部门ID，获取一级部门时传-1
 * @param [out] ack 查询部门列表响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *         <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_getdepts(IN TUP_INT64 deptID, OUT IM_S_GETDEPTS_ACK* ack);

/**
 * @brief 查询企业通讯录 （同步接口）
 * @param [in]  arg 查询企业通讯录请求
 * @param [out] ack 查询企业通讯录结果响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *      <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏;
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_queryentaddressbook(IN const IM_S_QUERY_ENTADDRESSBOOK_ARG* arg, OUT IM_S_QUERY_ENTADDRESSBOOK_ACK* ack);

/**
 * @brief 查询用户信息（模糊查询） （同步接口）
 * @param [in]  arg 查询用户信息请求
 * @param [out] ack 查询用户信息结果响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *            <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏;
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_queryuserinfo(IN const IM_S_QUERY_USERINFO_ARG* arg, OUT IM_S_QUERY_USERINFO_ACK* ack);

/**
 * @brief 添加固定群 （同步接口）
 * @param [in]  arg 创建或修改固定群或讨论组请求
 * @param [out] ack 创建固定群或讨论组响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 添加时群ID不用填写，成功添加后，群ID会在ack中返回；添加者自动成为固定群的管理员
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addfixedgroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT IM_S_ADDIMGROUP_ACK* ack);

/**
 * @brief 修改固定群信息 （同步接口）
 * @param [in]  arg 创建或修改固定群请求
 * @param [out] ack 修改固定群信息响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 只有固定群管理员可以使用此功能;修改完成后其他固定群成员会收到回调通知：IM_E_EVENT_FIXEDGROUP_INFOCHG_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_modfixedgroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT IM_S_MODFIXEDGROUP_ACK* ack);

/**
 * @brief 删除固定群 （同步接口）
 * @param [in]  id 固定群ID
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该操作只有群管理员有权限操作
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_delfixedgroup(IN const TUP_CHAR* id,  OUT TUP_BOOL* result);

/**
 * @brief 固定群添加成员 （异步接口）
 * @param [in]  arg 添加固定群成员请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该操作只有群管理员有权限操作;收到邀请的用户会收到回调消息：IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_addfixedgroupmember(IN const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * @brief 固定群删除成员 （异步接口）
 * @param [in]  arg 删除固定群成员请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该操作只有群管理员有权限操作;固定群成员会收到回调通知：IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_delfixedgroupmember(IN const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * @brief 管理员审批用户申请加入固定群申请 （异步接口）
 * @param [in]  arg 管理员审批用户申请加入固定群申请请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 只有固定群管理员可以使用此功能；
 *            <br>固定群管理员首先收到申请加入固定群的申请IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY
 *            <br>固定群管理员审批结束，申请用户收到审批结果回调通知：IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_confirmfixedgroupapply(IN const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * @brief 用户审批管理员邀请加入固定群 （异步接口）
 * @param [in]  arg 用户审批管理员邀请加入固定群请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 用户收到固定群管理员邀请加入固定群的回调通知消息：IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_confirmfixedgroupinvite(IN const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * @brief 用户主动申请加入固定群 （异步接口）
 * @param [in]  arg 用户申请加入固定群请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 群成员收到管理员审批加入固定群通知的响应：IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_joinfixedgroup(IN const IM_S_JOINFIXEDGROUP_ARG* arg);

/**
 * @brief 用户退出加入固定群 （异步接口）
 * @param [in]  arg 退出的固定群ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 固定群管理员只能解散固定群，不能退出固定群；该函数不关注服务器响应结果返回
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_leavefixedgroup(IN const TUP_CHAR* arg);

/**
 * @brief 转移固定群管理员权限 （异步接口）
 * @param [in]  arg 转移固定群管理员权限请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 只有固定群管理员可以使用此功能；被转移为固定群管理员的用户会收到回调通知：IM_E_EVENT_FIXEDGROUP_OWNERCHG_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_transferfixedgroup(IN const IM_S_TRANSFERIMGROUP_ARG* arg);

/**
 * @brief 获取群组详情 （同步接口）
 * @param [in]  arg 请求 群组ID
 * @param [out] ack 固定群详细信息
 * @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_getfixedgroupdetail(IN const TUP_CHAR* arg, OUT IM_S_IMGROUPINFO* ack);

/**
 * @brief 获取固定群或讨论组成员 （同步接口）
 * 
 * @param [in]  arg  <b>:</b> 获取固定群或讨论组成员请求
 * @param [out] ack  <b>:</b> 获取固定群或讨论组成员列表响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *            <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏
 * @see tup_im_release_tup_list
 **/
TUP_API TUP_RESULT tup_im_getfixedgroupmembers(IN const IM_S_REQUESTIMGROUPMEMBERS_ARG* arg, OUT IM_S_GROUPUSERLIST* ack);

/**
 * @brief 查询固定群（模糊查询）（同步接口）
 * @param [in]  arg 查询固定群请求
 * @param [out] ack 查询固定群响应
 * @retval TUP_API TUP_RESULT <b>:</b>成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *        <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏;
 * @see tup_im_release_tup_list
*/
TUP_API TUP_RESULT tup_im_getfixedgroups(IN const IM_S_GETIMGROUPLIST_ARG* arg, OUT IM_S_GETIMGROUPLIST_ACK* ack);

/**
 * @brief 添加讨论组（同步接口）
 * @param [in]  arg 创建或修改固定群或讨论组请求
 * @param [out] ack 创建或修改固定群或讨论组响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 添加时讨论组ID不用填写，成功添加后，讨论组ID会在ack中返回；添加者自动成为讨论组管理员
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_adddiscussiongroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT IM_S_ADDIMGROUP_ACK* ack);

/**
 * @brief 修改讨论组 （同步接口）
 * @param [in]  arg 创建或修改固定群或讨论组请求
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 讨论组成员会收到讨论组信息变更回调通知：IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_moddiscussiongroup(IN const IM_S_IMGROUP_OP_ARG* arg, OUT TUP_BOOL* result);

/**
 * @brief 删除讨论组 （同步接口）
 * @param [in]  id 需要删除的讨论组ID
 * @param [out] result 本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 只有讨论组管理员可以使用此功能
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_deldiscussiongroup(IN const TUP_CHAR* id, OUT TUP_BOOL* result);

/**
 * @brief 讨论组添加成员 （异步接口）
 * @param [in]  arg 请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 添加成员完成后，讨论组其他成员会收到新成员加入通知：IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY;
 *            <br>被添加者会收到回调消息：IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_adddiscussiongroupmember(IN const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * @brief 讨论组删除成员 （异步接口）
 * @param [in]  arg 删除固定群或讨论组成员请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 只有讨论组管理员可以使用此功能；添加成员完成后，讨论组其他成员会收到删除成员通知：IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_deldiscussiongroupmember(IN const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * @brief 讨论组语音会议添加语音成员 （异步接口）
 * @param [in]  arg 讨论组添加或删除语音用户请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 语音成员不会保存在服务器的讨论组成员列表中；该函数不关注服务器响应结果返回；讨论组成员会收到删除讨论组用户的回调通知：IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_adddiscussiongroupphonemember(IN const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * @brief 讨论组删除语音成员 （异步接口）
 * @param [in]  arg 讨论组添加或删除语音用户请求 
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该函数不关注服务器响应结果返回；讨论组其他成员会收到删除成员回调通知：IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_deldiscussiongroupphonemember(IN const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * @brief 退出讨论组 （异步接口）
 * @param [in]  arg 请求 讨论组ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该函数不关注服务器响应结果返回
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_leavediscussiongroup(IN const TUP_CHAR* arg);

 
/**
 * @brief 退出加入讨论组 （同步接口）
 * @param [in]  arg 请求 讨论组ID
 * @param [out] ack 响应 退出讨论组响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 接口会返回讨论组成员或管理员退出的结果
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_leave_discussion_group(IN const TUP_CHAR* arg, OUT IM_S_LEAVE_DISCUSSGROUP_ACK* ack);

/**
 * @brief 转移讨论组管理员权限 （异步接口）
 * @param [in]  arg 转移固定群或讨论组管理员权限请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 只有讨论组管理员可以使用此功能；转移完成后所有成员收到讨论组管理员变更通知IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_transferdiscussiongroup(IN const IM_S_TRANSFERIMGROUP_ARG* arg);


/**
 * @brief 固化讨论组
 *
 * @param [in] const  IM_S_SET_DISGROUP_POLICY_MSG* arg  <b>:</b> 固化讨论组请求
 * @param [out] IM_S_SET_DISGROUP_POLICY_MSG* ack        <b>:</b> 固化讨论组响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_set_disgroup_policy(IN const IM_S_SET_DISGROUP_POLICY_MSG* arg, OUT IM_S_SET_DISGROUP_POLICY_MSG* ack);


/**
 * @brief 广播讨论组操作消息
 *
 * @param [in]  IM_S_SEND_DISGROUP_OPT_MSG* arg  <b>:</b> 讨论组操作消息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention NA
 * @see IM_E_EVENT_IM_DISCUSSGROUP_OP_NOTIFY
 **/
TUP_API TUP_RESULT tup_im_send_disgroup_op_message(IN IM_S_SEND_DISGROUP_OPT_MSG* arg);

/**
 * @brief 设置自己自定义头像 （异步接口）
 * @param [in] image 请求 自定义头像图片信息
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该函数不关注服务器响应结果返回
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setselfdefineimage(IN const IM_S_IMAGEINFO* image);

/**
 * @brief 设置自己系统默认头像 （异步接口）
 * @param [in] imageID 请求 系统默认头像图片ID
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention UI必须有对应ID的图片保存在本地，并且和服务器上的系统头像ID对齐；该函数不关注服务器响应结果返回
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setsystemimage(IN const TUP_CHAR* imageID);

/**
 * @brief 设置个人信息（异步接口）
 * @param [in] arg 请求 存在账号信息的用户
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 某些个人信息修改没有权限修改，具体见服务器配置；该函数不关注服务器响应结果返回
 *            <br>订阅该用户的其他用户会收到用户信息变更通知：IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_setuserinfo(IN IM_S_USERINFO* arg);

/**
 * @brief 获取用户自定义头像 （同步接口）
 * @param [in] arg 获取其他用户的自定义头像请求
 * @param [out] ack 获取其他用户自定义头像的图片信息响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention arg中的账号来自与用户信息中的account参数
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_getuserdefineimage(IN const IM_S_IMAGEREQARG* arg, OUT IM_S_USERIMAGEINFO* ack);


/**
 * @brief 通知服务器自己状态变化 （异步接口）
 * @param [in] arg 通知服务器自己的状态变化请求
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 该函数不关注服务器响应结果返回；
 *            <br>所有订阅本端用户以及添加本端用户为好友的其他用户会收到状态变化回调通知：IM_E_EVENT_IM_USERSTATUS_NOTIFY
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_publishstatus(IN const IM_S_STATUSARG* arg);

/**
 * @brief 会议列表查询（同步接口）
 * @param [in] arg 查询会议列表请求
 * @param [out] ack 查询会议列表结果响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 若返回成功，在ack结构中的信息使用完成后，需要调用tup_im_release_tup_list
 *            <br>释放ack结构中的TUP_S_LIST* 内存，否则存在内存泄漏
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_GetConferenceList(IN const IM_S_GETCONFERENCELISTARG* arg, OUT IM_S_GETCONFERENCELISTACK* ack);

/**
 * @brief 释放TUP_S_LIST结构链表
 * 
 * @param [in] TUP_S_LIST* list_head  <b>:</b> TUP_S_LIST链表头
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若在业务API接口返回的*_ACK结构中，或事件通知IM_E_EVENT_IM_*对应的数据结构中，
 *        <br>存在非空的TUP_S_LIST*链表，则需要调用此函数(或自行实现)进行资源释放，否则存
 *        <br>在内存泄漏
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
 * @brief 释放TUP内部分配的内存
 * @param [in] pData 需要释放的指针
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 *
 * @attention 仅用于释放TUP IM组件接口返回的内存
 * @see NA
 **/
TUP_API TUP_RESULT tup_im_release_tup_mem(IN TUP_VOID* pData);

/**
 * @brief 获取最近会话记录(同步接口)
 * 
 * @param [in] const IM_S_GEL_RECENT_CONVERSATION_ARG* arg  <b>:</b> 获取最近会话请求
 * @param [out] IM_S_GEL_RECENT_CONVERSATION_ACK* ack        <b>:</b> 获取最近会话响应
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 若在业务API接口返回的*_ACK结构中，或事件通知IM_E_EVENT_IM_*对应的数据结构中，
 *        <br>存在非空的TUP_S_LIST*链表，则需要调用此函数(或自行实现)进行资源释放，否则存
 *        <br>在内存泄漏
 * @see tup_im_del_recent_conversation
 **/
TUP_API TUP_RESULT tup_im_gel_recent_conversation(IN const IM_S_GEL_RECENT_CONVERSATION_ARG* arg, OUT IM_S_GEL_RECENT_CONVERSATION_ACK* ack);


/**
 * @brief 删除最近会话(异步接口)
 * 
 * @param [in] const IM_S_DEL_RECENT_CONVERSATION_ARG* arg  <b>:</b> 删除最新会话请求消息
 * @param [out] result                                      <b>:</b>本次操作结果
 * @retval TUP_API TUP_RESULT <b>:</b> 成功返回TUP_SUCCESS，失败返回相应错误码
 * 
 * @attention 此函数不关注服务器处理结果
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
* 2012-12-10, 初始化该文件。 \n
* 2015-12-30, TUP V100R001C50 TR5 发布，更新此文件。 \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
