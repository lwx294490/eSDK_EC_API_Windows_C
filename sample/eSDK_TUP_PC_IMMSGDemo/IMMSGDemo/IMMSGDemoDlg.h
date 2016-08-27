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
#pragma once

#include "MyHtmlEditCtrl.h"
#include "offlinefile_def.h"
#include "offlinefile_interface.h"
#include "RichEditCtrlEx.h"

#include <map>
#include <vector>
#include <sstream>
#include <iosfwd>
#include <string>
#include "afxwin.h"
#include "afxcmn.h"
#include "Tools.h"

#define UMSERVERLENT 128

struct UMFileMsgInfo
{
	std::string umFilePath;
	std::string umFileUrl;
	std::string umFileType;
	std::string umFileSize;
	std::string umFileName;
	std::string umFileDuration;
	std::string umTransCode;
	std::string umExtraParam;
};

// 离线文件下载信息
struct UMDownLoadInfo
{
	std::string filename;
	std::string sessid;
};

struct FileTransInfo
{
	std::string convID_;
	std::string sessID_;
	std::string msgID_;
	std::string filePath_;
	std::string fileUrl_;
	std::string transType_;
	std::string receiverUri_;
	std::string receiverAcc_;
	std::string fileSize_;
	std::string msgbody_;
	int duration_;//语音、视频片段时长
	int purpose_; //用途，0：文件传输；1：图文混排消息；
	std::string startTime;//文件传输开始时间
	std::string GUISession;
};

//数字转化为字符串，第二个参数指定进制（默认十进制）
//使用时可以不指定模板参数类型；转换失败抛出runtime_error异常
template<class T> inline std::string num2str(
	const T & num, std::ios_base &(*f)(std::ios_base&) = std::dec)
{
	std::ostringstream oss;
	if ((oss << f << num).fail())
		throw std::runtime_error("invalid conversion : num = " + num);

	return oss.str();
}

// CIMMSGDemoDlg dialog
class CIMMSGDemoDlg : public CDialogEx
{
	// Construction
public:
	CIMMSGDemoDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CIMMSGDemoDlg();

	// Dialog Data
	enum { IDD = IDD_IMMSGDEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Implementation
protected:
	HICON m_hIcon;

	// 控件变量
public:
	CButton						m_btnEmotion;			// 表情控件
	CButton						m_btnExit;				// 退出按钮
	CButton						m_btnLogin;				// 登录按钮
	CButton						m_btnLogoff;			// 注销按钮
	CButton						m_btnScreenCatch;		// 截图控件
	CButton						m_btnSendMSG;			// 发送消息
	CButton						m_btnSendScreenCatch;	// 发送截图按钮
	CEdit						m_editAccount;			// 发送方账户
	CEdit						m_editOppsiteAccount;	// 接收方账户
	CEdit						m_editPort;				// 端口
	CEdit						m_editPSD;				// 密码
	CRichEditCtrlEx				m_editSendMSG;			// 发送编辑框
	CIPAddressCtrl				m_ipAddress;			// IP地址
	CComPtr<IHTMLDocument2>		m_pDocument;			// IHTMLDocument2
	CStatic						m_staticShowMSG;		// 用于被Html替换
	CStatic						m_stcInputStatic;		// 输入状态

	// 普通变量
public:
	BOOL						m_bLoginFlag;			// 登录状态
	BOOL						m_bLogOff;				// 注销时不退出对话框
	CString						m_cstrLoginAccount;		// 发送方账户
	CString						m_cstrOppositeAccount;	// 用来判断发送方账户有没有改变
	CString					   m_downloadImagePath;	// 下载图片路径
	std::map<CString, CString>	m_EmotionReplace;		// 用于表情和符号之间的替换
	std::vector<std::wstring>	m_imgList;				// 图片列表
	OFFLINE_LOGININFO			m_LoginInfo;			// 离线文件登录信息
	std::vector<CString>		m_MsgRecord;			// 消息记录，用来将最新消息显示在最上面
	IM_S_SENDIM_ARG				m_SendImArg;			// 发送参数
	IM_S_USERINFO				m_sendUserInfo;			// 发送方账户详细信息
	IM_S_CHAT_STATUS_ARG		m_statusArg;			// 聊天状态
	CString						m_strDefaultEmotionPath;// 默认表情路径
	CString						m_strEmotionPath;		// 单击表情按钮选择的路径
	OFFLINE_USERINFO			m_UserInfo;				// 离线文件用户信息
	TUP_INT64					m_UtcStamp;									/**< UTC时间*/
	TUP_CHAR					OriginAccount[IM_D_MAX_ACCOUNT_LENGTH];			/**< 发送方账号*/

	// 静态变量
public:
	static BOOL					s_bIsUpload;			// 用来判断是上传还是下载图片
	static CString				s_ImagePath;			// 截图路径
	static CString				s_SendMSG;				// 发送内容
	int                         m_ImagePosition;        //记录截图在本行代码中的位置/////

	// Common functions
public:
	// 压缩的消息格式
	void ComMsgFormat(CString& cotent, CString& sendCotent);
	void ComCodeMsg(std::string& m_strSource, std::string& m_strTarget);

	// 登录成功则禁用相关登录控件
	void DisableLoginRelativeControls();

	// 从UM服务器下载图片并返回本地存储路径////
	CString DownloadImageFromServerce(UMINFo& m_UMinfo);

	// 注销账户则重新启用相关登录控件
	void EnableLoginRelativeControls();

	// 获取系统的相关信息
	BOOL GetDeviceInfo (std::string& sys, std::string& ver, std::string& sn);

	// 插入发送（接收）方的账户信息
	void InsertAccountTime(TUP_CHAR account[], TUP_INT64 utcStamp) const;

	// 插入纯文本
	void InsertHTMLText(const CString& sendContext) const;

	// 插入图片
	void InsertImage(CString imagePath, UINT width, UINT height, BOOL isImage, const CString& imageid,BOOL bIsPerc) const;

	// 获取即将发送的消息类型 0表示文本消息，>0表示截图图像数量,m_strScrathURI返回截图URL////
	int GetScrachPicNum(MsgToSend& msgTxtPic,std::string& m_strScrathURI);

	// 解析从eSpace或UC传过来的文本
	void ParseStringFromUCoreSpase(CString originText, TUP_CHAR account[], TUP_INT64 utcStamp);

	// 处理从eSpace或UC传过来的消息内容（判断是否压缩，是否进行相应解压等操作）
	void ProcessCotentFromeSpaceOrUC(std::string& cotent);

	// 进度回调
	static void ProgressCallBack(OFFLINEHANDLE fileHandle, TUP_UINT64 ulTotal, TUP_UINT64 ulNow, void *userInfo);

	// 调整图片大小
	void ResizeImage(LONG& lWidth, LONG& lHeight);

	// 设置离线文件登录参数
	void SetOffLineLoginInfo(OFFLINE_LOGININFO& loginInfo,TUP_CHAR* umServerHttpsList,TUP_CHAR* umServerHttpList);

	// 设置离线文件用户参数
	void SetOffLineUserInfo(OFFLINE_USERINFO& userInfo);

	// 解析字符串
	void Splitstring(const std::string& srcString, const std::string& spiltchar, std::vector<std::string>& list_);

	// 离线文件传输结果回调
	static int UMMsgTransResultCallback(OFFLINEHANDLE fileHandle, TUP_ULONG enCode, OFFLINE_RSPFILEINFO *pstFileRsp, void *userInfo);

	// 未压缩的消息格式
	void UnCompMsgFormat(CString& content, CString& sendContent);
	void UNComCodeMsg(std::string& content, std::string& sendContent);

	// 更新聊天内容
	int  UpdataChatContent(TUP_CHAR account[], TUP_INT64 utcStamp, const CString& chatContent);

	// 插入图片信息
	void  InsertEmotion(vector<PicPathInfo>& OutImagelist,int Pos);

	// Generated message map functions
public:
	afx_msg void OnBnClickedButtonExit();// 退出
	afx_msg void OnBnClickedButtonLogin();// 登录
	afx_msg void OnBnClickedButtonLogoff();// 注销账户
	afx_msg void OnBnClickedButtonEmotion();// 表情按钮单击事件
	afx_msg void OnBnClickedButtonScreencatch();// 截图
	afx_msg void OnBnClickedButtonSendCatch();// 发送截图
	afx_msg void OnBnClickedButtonSendMsg();// 发送消息按钮
	afx_msg void OnEnKillfocusEditOppsiteAccount();// 接收方账户编辑框失去焦点
	afx_msg LRESULT OnInputStatus(WPARAM, LPARAM);// 显示接收方的输入状态
	virtual BOOL OnInitDialog(); // 对话框初始化按钮
	afx_msg LRESULT OnKickOutUser(WPARAM, LPARAM);// 用户被踢出
	afx_msg void OnKillfocusEditMsg();// 消息内容编辑框获得焦点
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvIM(WPARAM, LPARAM);// 聊天记录显示
	afx_msg LRESULT OnRecvOfflineIM(WPARAM, LPARAM);
	afx_msg void OnSetfocusEditMsg();// 消息内容编辑框失去焦点
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowDownloadImage(WPARAM, LPARAM);
	afx_msg LRESULT OnSendImageInfo(WPARAM, LPARAM);
	afx_msg void OnTimer(UINT_PTR nIDEvent);// 设置心跳定时器
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);// 消息预处理
	DECLARE_MESSAGE_MAP()
	CButton m_sendPic;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CRichEditCtrlEx m_editRecvMSG;
	private:
		std::string m_strScrathURI;      //////截图URL////
		std::string m_strContent  ;      //////生成消息结构体中Content内容/////
		std::string m_strHTML ;         ///////组装生成消息结构体的HTML字段内容/////
};