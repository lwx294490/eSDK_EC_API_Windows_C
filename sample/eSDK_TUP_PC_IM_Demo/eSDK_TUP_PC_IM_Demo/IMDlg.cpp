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

// IMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "eSDK_TUP_PC_IM_Demo.h"
#include "IMDlg.h"
#include "Tools.h"
#include "NotifyCallBack.h"
#include "IMManage.h"

const int WIDTH = 450;
const int HEITH = 550;

const int TOOLWIDTH = 400;
const int IMCONTENTBOTTOM = 418;

enum ImgQuery
{
	IMG_QUERY_ERR, 
	IMG_QUERY_TYPE_LOCAL, 
	IMG_QUERY_TYPE_BUFFER
};

// CIMDlg 对话框

IMPLEMENT_DYNAMIC(CIMDlg, CDialog)

CIMDlg::CIMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIMDlg::IDD, pParent)
	, m_strGroupID("")
	, m_strLoginAccount("")
	, m_strLoginName("")
	, m_DlgType(SIGNLE_CHAT)	
{

}

CIMDlg::~CIMDlg()
{
}

void CIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RECV_ZONE, m_edtIMContent);
	DDX_Control(pDX, IDC_EDIT_SEND_CONTENT, m_edtSend);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_stcName);
	DDX_Control(pDX, IDC_LIST_MEMBER, m_listMember);
	DDX_Control(pDX, IDC_STATIC_HEAD, m_stcHead);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
}


BEGIN_MESSAGE_MAP(CIMDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CIMDlg::OnBnClickedButtonAddUser)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CIMDlg::OnBnClickedButtonSendIM)
	ON_MESSAGE(WM_MENU_SEND_IM,&CIMDlg::OnSendIMMenuClick)
	ON_MESSAGE(WM_RECV_IM,&CIMDlg::OnRecvIM)
	ON_MESSAGE(WM_GROUP_NOTIFY,&CIMDlg::OnGroupNotify)
	ON_MESSAGE(WM_GROUP_INF_CHANGE,&CIMDlg::OnGroupInfoChange)
	ON_MESSAGE(WM_GROUP_MEM_ADD,&CIMDlg::OnGroupMemAdd)
	ON_MESSAGE(WM_GROUP_MEM_DEL,&CIMDlg::OnGroupMemDel)
	ON_MESSAGE(WM_GROUP_MEM_OWNER,&CIMDlg::OnGroupOwnerChange)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MEMBER, &CIMDlg::OnNMRClickListMember)
	ON_COMMAND_RANGE(ID_IM_GROUP_DEL_MEM_MENU, ID_IM_GROUP_RECALL_MEM_MENU, &CIMDlg::OnClickListMemMenuItem)
END_MESSAGE_MAP()


// CIMDlg 消息处理程序

BOOL CIMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_DlgType = SIGNLE_CHAT;
	RefreshWindow();

	//获取屏幕中间的位置
	int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
	int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);

	MoveWindow((cxFrame-WIDTH)/2,(cyFrame-HEITH)/2,WIDTH,HEITH);

	m_listMember.ModifyStyle(0,LVS_SINGLESEL);
	m_listMember.InsertColumn(COL_MEM_Compere, _T("主席"), LVCFMT_LEFT, 40);
	m_listMember.InsertColumn(COL_MEM_Status, _T("状态"), LVCFMT_LEFT, 40);
	m_listMember.InsertColumn(COL_MEM_Name, _T("姓名"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_ACCOUNT, _T("账号"), LVCFMT_LEFT, 70);
	m_listMember.InsertColumn(COL_MEM_CALLNO, _T("号码"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_CALLSTATE, _T("呼叫状态"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_SPK, _T("发言"), LVCFMT_LEFT, 60);
	DWORD dwStyle = m_listMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listMember.SetExtendedStyle(dwStyle); //设置扩展风格

	//////限制IM消息输入最大长度  c00327158 Start//////
	m_edtSend.LimitText(10240);
	//////限制IM消息输入最大长度  c00327158 End//////
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CIMDlg::OnBnClickedButtonSendIM()
{
	// TODO: 在此添加控件通知处理程序代码

	CString cstrContent;
	m_edtSend.GetWindowText(cstrContent);
	// cstrShow用来更新聊天内容，cstrContent用来生成发送格式
	CString cstrShow = cstrContent;
	CString strSend(_T(""));
	if(cstrContent.IsEmpty())
	{
		AfxMessageBox(_T("Target Account is empty"));
		CEdit *pEdit=(CEdit *)GetDlgItem(IDC_EDIT_SEND_CONTENT);
		pEdit->SetFocus();
		return;
	}
	else
	{
		// eSpace发送消息长度如果超出500会进行压缩，而UC没有压缩功能
		// 所以UC消息内容长度控制在500以下，超出500直接返回并进行提示
		int nLength = CTools::UNICODE2UTF(cstrContent).length();

		if (nLength <= 500)
		{
			// 未压缩的消息格式
			UnCompMsgFormat(cstrContent, strSend);
		}
// 		else if (nLength <= 1000)
// 		{
// 			// 压缩的消息格式
// 			ComMsgFormat(cstrContent, strSend);
// 		}
		else
		{
			AfxMessageBox(_T("Message is too long, please re-enter!"));
			CEdit *pEdit=(CEdit *)GetDlgItem(IDC_EDIT_SEND_CONTENT);
			pEdit->SetWindowText(_T(""));
			pEdit->SetFocus();
			return;
		}
	}

	IM_S_SENDIM_ARG SendImArg;
	if(m_DlgType == SIGNLE_CHAT)
	{
		if(0 == strlen(m_targetUserInfo.account))
		{
			AfxMessageBox(_T("Targrt Account is Empty"));
			return;
		}
		SendImArg.chatType = IM_E_IM_CHAT_TYPE_SINGLE;
		SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
		SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
		memcpy(SendImArg.target,m_targetUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH);	
		memcpy(SendImArg.origin,m_strLoginAccount.c_str(),IM_D_MAX_ACCOUNT_LENGTH);
		memcpy(SendImArg.displayname,m_strLoginName.c_str(),IM_D_MAX_NAME_LENGTH);	
//		CTools::CString2Char(cstrContent,SendImArg.content,IM_D_MAX_MESSAGE_LENGTH);
		CTools::CString2Char(strSend,SendImArg.content,IM_D_MAX_MESSAGE_LENGTH);
		SendImArg.utcStamp = CTools::GetCurUTCTime();
		SendImArg.regionID = 0;
	}
	else
	{
		SendImArg.chatType = IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP;
		SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
		SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
		memcpy(SendImArg.origin,m_strLoginAccount.c_str(),IM_D_MAX_ACCOUNT_LENGTH);	
		memcpy(SendImArg.target,"",IM_D_MAX_ACCOUNT_LENGTH);	
		memcpy(SendImArg.displayname,m_strLoginName.c_str(),IM_D_MAX_NAME_LENGTH);
		//CTools::CString2Char(cstrContent,SendImArg.content,IM_D_MAX_MESSAGE_LENGTH);
		CTools::CString2Char(strSend,SendImArg.content,IM_D_MAX_MESSAGE_LENGTH);
		SendImArg.utcStamp = CTools::GetCurUTCTime();
		SendImArg.regionID = 0;
		memcpy(SendImArg.groupID,m_strGroupID.c_str(),IM_D_GROUPID_LENGTH);
	}

	//发送即时消息
	TUP_RESULT tRet = tup_im_sendim(&SendImArg);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_sendim failed."));
	}

	m_edtSend.SetWindowText(L"");

	//消息显示区域更新显示
	CString curContent;
	m_edtIMContent.GetWindowText(curContent);
	m_edtIMContent.SetWindowText(curContent
		+(curContent.IsEmpty()? L"" : L"\r\n")
		+CTools::UTF2UNICODE(SendImArg.displayname)
		+L"("
		+CTools::UTF2UNICODE(SendImArg.origin)
		+L") "
		+CTools::FormatUTCTime(SendImArg.utcStamp)
		+L"\r\n"
		+cstrShow)/*CTools::UTF2UNICODE(SendImArg.content))*/;	//自动换行
	m_edtIMContent.PostMessage(WM_VSCROLL, SB_BOTTOM);

	UpdateData(TRUE);

	//设置光标位置
	CEdit *pEdit=(CEdit *)GetDlgItem(IDC_EDIT_SEND_CONTENT);
	pEdit->SetFocus();
}

//主对话框中右键某个联系人，弹出发送消息对话框时调用
LRESULT CIMDlg::OnSendIMMenuClick(WPARAM wParam,LPARAM lParam)
{
	IM_S_USERINFO* pUserInfo = (IM_S_USERINFO *)lParam;
	if(NULL == pUserInfo)
	{
		return -1L;
	}

	memcpy(&m_targetUserInfo,pUserInfo,sizeof(IM_S_USERINFO));
	//消息接收方的用户名
	m_stcName.SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.name));
	SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.name));

	//Modified by w00321336 to code refactoring at 2015-1-21 begin
	//设置头像
	SetUserHeadImg(m_targetUserInfo);
	//Modified by w00321336 end

	ShowWindow(SW_SHOW);

	SAFE_DELETE(pUserInfo);
	return 0L;
}

//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 begin
BOOL CIMDlg::GetUserDefHeadImg(const TUP_CHAR imageID[], IM_S_IMAGEINFO& imgInfo)
{
	IM_S_IMAGEREQARG ImageArg;
	IM_S_USERIMAGEINFO ImageAck;
	strcpy_s(ImageArg.id, IM_D_MAX_ACCOUNT_LENGTH, imageID);
	//从服务器获取自定义的头像数据
	TUP_RESULT tRet = tup_im_getuserdefineimage(&ImageArg, &ImageAck);
	if(TUP_FAIL == tRet)
	{
		return false;
	}

	imgInfo = ImageAck.imagebits;
	return true;
}

CString CIMDlg::GetLocalHeadImg(const TUP_CHAR imageID[])
{
	CString strImgPath;
	CString strPath = CTools::getCurrentPath();
	strImgPath.Format(_T("%s\\face\\%s.png"), strPath, CTools::UTF2UNICODE(imageID));
	return strImgPath;
}

CString CIMDlg::GetDefaultHeadImg()
{
	CString strImgPath;
	CString strPath = CTools::getCurrentPath();
	strImgPath.Format(_T("%s\\face\\0.png"), strPath);
	return strImgPath;
}

int CIMDlg::GetUserHeadImg(const IM_S_USERINFO& userInfo, IM_S_IMAGEINFO& imgeInfo, CString& strImgPath)
{
	int nRet = IMG_QUERY_ERR;

	if(0 != strlen(userInfo.imageID))
	{	
		if(strcmp(userInfo.imageID, userInfo.account) == 0)
		{
			//自定义头像
			if (GetUserDefHeadImg(userInfo.imageID, imgeInfo))
			{
				nRet = IMG_QUERY_TYPE_BUFFER;
			}
			//Modified by w00321336 to draw byte image for DTS2015010701095 at 2015-1-21 end
		}
		else
		{
			//系统头像
			strImgPath = GetLocalHeadImg(userInfo.imageID);
			nRet = IMG_QUERY_TYPE_LOCAL;
		}
	}
	else
	{
		//默认头像
		strImgPath = GetDefaultHeadImg();
		nRet = IMG_QUERY_TYPE_LOCAL;
	}

	return nRet;
}

void CIMDlg::SetGroupHeadImg()
{
	CString strPath = CTools::getCurrentPath();
	CString strFullPath;
	strFullPath.Format(_T("%s\\image\\group.png"), strPath);
	m_stcHead.SetImageFile(strFullPath);
}

BOOL CIMDlg::SetUserHeadImg(const IM_S_USERINFO& userInfo)
{
	BOOL bRet = FALSE;

	IM_S_IMAGEINFO imgInfo;
	CString strImgPath;
	int nRet = GetUserHeadImg(userInfo, imgInfo, strImgPath);
	if (IMG_QUERY_TYPE_BUFFER == nRet)
	{//自定义头像
		m_stcHead.SetImgBuffer(imgInfo.data, imgInfo.length);
		bRet = TRUE;
	}
	else if (IMG_QUERY_TYPE_LOCAL == nRet)
	{//本地头像
		m_stcHead.SetImageFile(strImgPath);
		bRet = TRUE;
	}

	return bRet;
}
//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 end

LRESULT CIMDlg::OnRecvIM(WPARAM wParam,LPARAM)
{
	IM_S_CODECHAT_NOTIFY *notify  = (IM_S_CODECHAT_NOTIFY *)wParam;
	if(NULL == notify)
	{
		return -1L;
	}

	if(notify->chatInfo.chatType == IM_E_IM_CHAT_TYPE_SINGLE)
	{
		m_stcName.SetWindowText(CTools::UTF2UNICODE(notify->chatInfo.name));

		strcpy_s(m_targetUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH,notify->chatInfo.origin);
		strcpy_s(m_targetUserInfo.name,IM_D_MAX_ACCOUNT_LENGTH,notify->chatInfo.name);		

		SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.account));

		//设置头像
		//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 begin
		IM_S_GETUSERINFOARG sefInfoarg;
		IM_S_USERINFO userInfoAck;
		strcpy_s(sefInfoarg.account, IM_D_MAX_ACCOUNT_LENGTH, notify->chatInfo.origin);
		//精确查找某个用户的信息
		TUP_RESULT tRet = tup_im_getuserinfo(&sefInfoarg, &userInfoAck);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_getuserinfo fail."));
		}

		m_stcName.SetWindowText(CTools::UTF2UNICODE(userInfoAck.name));
		SetWindowText(CTools::UTF2UNICODE(userInfoAck.name));

		strcpy_s(m_targetUserInfo.bindNO,IM_D_MAX_ACCOUNT_LENGTH,userInfoAck.bindNO);

		//Set head image
        SetUserHeadImg(userInfoAck);
		//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 end
	}
	else
	{
		strcpy_s(m_targetUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH,"");
		strcpy_s(m_targetUserInfo.name,IM_D_MAX_ACCOUNT_LENGTH,"");
		m_DlgType = MULTI_CHAT;
		RefreshWindow();

		RefreshMemberList(notify->chatInfo.groupID);

		IM_S_IMGROUPINFO info;
		//用户获取某个固定群组的详情
		TUP_RESULT tRet = tup_im_getfixedgroupdetail(m_strGroupID.c_str(),&info);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_getfixedgroupdetail fail"));
		}

		RefershChairMan(info.owner);

		SetWindowText(CTools::UTF2UNICODE(info.name));	
		m_stcName.SetWindowText(CTools::UTF2UNICODE(info.name));

		//设置群组头像
		SetGroupHeadImg();
	}

	ShowWindow(SW_SHOW);
	
	// TEST
	// 解析收到的eSpace纯文本消息
	string strMSG(notify->chatInfo.content);

	// 处理从eSpace或UC传过来的消息内容（判断是否压缩，是否进行相应解压等操作）
	ProcessCotentFromeSpaceOrUC(strMSG);

	// 将字符串转换为宽字符
	wstring comment = CTools::string2wstring(strMSG);
	CString strComment(comment.c_str());

	switch (notify->chatInfo.contentType)
	{
	case IM_E_IM_CHAT_CONTENT_TYPE_TEXT:
		{
			ParseStringFromUCoreSpase(strComment);
		}
		break;
	default:break;
	}
	// TEST
	CString curContent;
	m_edtIMContent.GetWindowText(curContent);
	m_edtIMContent.SetWindowText(curContent
		+(curContent.IsEmpty()? L"" : L"\r\n")
		+CTools::UTF2UNICODE(notify->chatInfo.name)
		+L"("
		+CTools::UTF2UNICODE(notify->chatInfo.origin)
		+L") "
		+CTools::FormatUTCTime(notify->chatInfo.utcStamp)
		+L"\r\n"
		+strComment/*CTools::UTF2UNICODE(notify->chatInfo.content)*/);	//自动换行
	m_edtIMContent.PostMessage(WM_VSCROLL, SB_BOTTOM);

	UpdateData(TRUE);

	return 0L;
}


void CIMDlg::SetDefualtHeadImg()
{
	CString strDefImg = GetDefaultHeadImg();
	m_stcHead.SetImageFile(strDefImg);
}


BOOL CIMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_RETURN)   
		{   
			return TRUE;   
		}   
		if(nVirtKey == VK_ESCAPE)   
		{   
			return TRUE;
		}   
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CIMDlg::OnBnClickedButtonAddUser()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CIMDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_DlgType == SIGNLE_CHAT)
	{
		::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_IM_WND,(WPARAM)this,NULL);
	}
	else if(m_DlgType == MULTI_CHAT)
	{
/*
		IM_S_IMGROUPINFO info;
		TUP_RESULT tRet = tup_im_getfixedgroupdetail(m_strGroupID.c_str(),&info);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_getfixedgroupdetail fail"));
		}
		else
		{
			if(strcmp(m_strLoginAccount.c_str(), info.owner) == 0)
			{
				TUP_BOOL result = TUP_FAIL;
				tup_im_deldiscussiongroup(m_strGroupID.c_str(), &result);
				if(TUP_FAIL == tRet)
				{
					AfxMessageBox(L"tup_im_deldiscussiongroup failed.");
				}
				else
				{
					m_strGroupID.clear();
				}
			}	
		}

		::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_IM_WND,(WPARAM)this,NULL);
*/
		ShowWindow(SW_HIDE);
	}
	CDialog::OnClose();
}


void CIMDlg::RefreshWindow(void)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rc;
	rc.top = IMCONTENTBOTTOM+3;
	rc.bottom = IMCONTENTBOTTOM+57;
	rc.left = rcClient.left+13;
	rc.right = rcClient.left+TOOLWIDTH;
	m_edtSend.MoveWindow(&rc,TRUE);

	switch (m_DlgType)
	{
	case SIGNLE_CHAT:
		{
			CRect rc;
			rc.top = 50;
			rc.bottom = IMCONTENTBOTTOM;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			//消息接收区域
			m_edtIMContent.MoveWindow(&rc,TRUE);
			m_edtIMContent.ShowWindow(SW_SHOW);
			//讨论组成员区域显示
			m_listMember.ShowWindow(SW_HIDE);	
		}
		break;
	case MULTI_CHAT:
		{
			CRect rc;
			rc.top = 105;
			rc.bottom = 185;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_listMember.MoveWindow(&rc,TRUE);
			m_listMember.ShowWindow(SW_SHOW);

			rc.top = 185;
			rc.bottom = IMCONTENTBOTTOM;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_edtIMContent.MoveWindow(&rc,TRUE);
			m_edtIMContent.ShowWindow(SW_SHOW);
		}
		break;
	}
}

void CIMDlg::RefreshMemberList(const std::string& groupID)
{
	m_listMember.DeleteAllItems();

	IM_S_REQUESTIMGROUPMEMBERS_ARG groupMembArg;
	IM_S_GROUPUSERLIST groupList;

	strcpy_s(groupMembArg.groupID,IM_D_GROUPID_LENGTH,groupID.c_str());
	groupMembArg.isSyncAll = TUP_TRUE;
	strcpy_s(groupMembArg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");

	//用户查询某个固定群组的所有成员
	tup_im_getfixedgroupmembers(&groupMembArg,&groupList);
	TUP_S_LIST* list =  groupList.memberInfo;
	while(list != NULL)
	{
		IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
		if(NULL != groupUser)
		{
			CString cstrAccount = CTools::UTF2UNICODE(groupUser->account);
			bool bFind = false;
			int iSize = m_listMember.GetItemCount();
			for(int i = 0; i< iSize; i++)
			{
				if(cstrAccount.Compare(m_listMember.GetItemText(i,COL_ACCOUNT)) == 0)
				{
					bFind = true;
					break;
				}
			}
			if(!bFind)
			{
				m_listMember.InsertItem(iSize,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Compere,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Status,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Name,CTools::UTF2UNICODE(groupUser->name));
				m_listMember.SetItemText(iSize,COL_MEM_ACCOUNT,cstrAccount);
				m_listMember.SetItemText(iSize,COL_MEM_CALLNO,CTools::UTF2UNICODE(groupUser->bindNO));
				m_listMember.SetItemText(iSize,COL_MEM_CALLSTATE,L"");
				m_listMember.SetItemText(iSize,COL_MEM_SPK,L"");
			}
		}
		list = list->next;
	}
	/////释放IM_S_GROUPUSERLIST中的指针////
	tup_im_release_tup_list(groupList.memberInfo);
}


void CIMDlg::OnNMRClickListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_listMember.ScreenToClient(&pt);

	UINT uFlag = 0;
	int hSelectedItem = m_listMember.HitTest(pt,&uFlag);
	if (0 <= hSelectedItem)
	{
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_IM_GROUP_DEL_MEM_MENU, _T("移除与会者"));

		//modify by lwx294490 at 2015-6-27 start
		//1.manager can delete all members in the discuss group.
		//2.nomal member can only delete self.
		int iFind = -1;
		CString cstrFindStr(_T("主席"));
		CString cstrManagerAccount;
		if(!FindColum(cstrFindStr, COL_MEM_Compere, iFind))
		{
			AfxMessageBox(L"the discuss group has no manager!");
			return;
		}
		else
		{
			cstrManagerAccount = m_listMember.GetItemText(iFind, COL_MEM_ACCOUNT);
		}

		CString cstrAccount = m_listMember.GetItemText(hSelectedItem, COL_MEM_ACCOUNT);
		if( (cstrAccount.Compare(CTools::UTF2UNICODE(m_strLoginAccount)) != 0)
			&& (cstrManagerAccount.Compare(CTools::UTF2UNICODE(m_strLoginAccount)) != 0) )
		{
			menu.EnableMenuItem(ID_IM_GROUP_DEL_MEM_MENU, MF_DISABLED|MF_GRAYED);
		}

		////Modified by w00321336 to disable this item when it's a chairman at 2015-1-20 begin
		//CString strCompere = m_listMember.GetItemText(hSelectedItem, COL_MEM_Compere);
		//if (strCompere.Compare(L"主席") == 0)
		//{
		//	menu.EnableMenuItem(ID_IM_GROUP_DEL_MEM_MENU, MF_DISABLED|MF_GRAYED);
		//}
		////Modified by w00321336 end
		//modify by lwx294490 at 2015-6-27 end

		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);		                 
	}

	*pResult = 0;
}

void CIMDlg::OnClickListMemMenuItem(UINT nID)
{
	int nItem = -1;
	POSITION pos = m_listMember.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	else
	{
		while (pos)
		{
			nItem = m_listMember.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			break;
		}
	}
	CString cstrAccount = m_listMember.GetItemText(nItem,COL_MEM_ACCOUNT);

	if(nID == ID_IM_GROUP_DEL_MEM_MENU)
	{
		//modify by lwx294490 at 2015-6-27 start
		//if the command is manager sent,then the command means delete one member in discuss group.
		//if the command is nomal member sent,then the command means leave discuss group.
		int iFind = -1;
		CString cstrFindStr(_T("主席"));
		CString cstrManagerAccount;
		if(!FindColum(cstrFindStr, COL_MEM_Compere, iFind))
		{
			AfxMessageBox(L"the discuss group has no manager!");
			return;
		}
		else
		{
			cstrManagerAccount = m_listMember.GetItemText(iFind, COL_MEM_ACCOUNT);
		}

		if( 0 == cstrManagerAccount.Compare(CTools::UTF2UNICODE(m_strLoginAccount)))
		{
			IM_S_DELIMGROUPMEMBER_ARG arg;
			CTools::CString2Char(cstrAccount,arg.account,IM_D_MAX_ACCOUNT_LENGTH);
			strcpy_s(arg.groupID,IM_D_GROUPID_LENGTH,m_strGroupID.c_str());
			TUP_RESULT tRet = tup_im_deldiscussiongroupmember(&arg);
			if(tRet == TUP_FAIL)
			{
				AfxMessageBox(L"tup_im_deldiscussiongroupmember failed");
			}
			else
			{
				m_listMember.DeleteItem(nItem);
			}
		}
		else
		{
			TUP_RESULT tRet = tup_im_leavediscussiongroup(m_strGroupID.c_str());
			if(TUP_FAIL == tRet)
			{
				AfxMessageBox(L"tup_im_deldiscussiongroup failed.");
			}
		}

		if(m_listMember.GetItemCount() <= 0)
		{
			CIMManage::GetIntance().DeleteIMDlgByIMDlg(this);
		}
		//modify by lwx294490 at 2015-6-27 end
	}
}

LRESULT CIMDlg::OnGroupNotify(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	m_DlgType = MULTI_CHAT;
	RefreshWindow();

	if(strcmp(pNotify->adminAccount,g_Account.c_str()) != 0)
	{
		m_btnAdd.EnableWindow(FALSE);
	}

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	//Add by w00321336 to fix group title & image issue at 2015-1-22 begin
	m_stcName.SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
	SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
	SetGroupHeadImg();
	//Add by w00321336 to fix group title issue at 2015-1-22 end

	////释放IM_S_DISCUSSGROUP_NOTIFY结构体中申请的TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);

	SAFE_DELETE(pNotify);

	ShowWindow(SW_SHOW);
	return 0L;
}

LRESULT CIMDlg::OnGroupInfoChange(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}

LRESULT CIMDlg::OnGroupMemAdd(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	/////释放IM_S_DISCUSSGROUP_NOTIFY结构体中TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);

	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}

LRESULT CIMDlg::OnGroupMemDel(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	//CString memberAccount = CTools::UTF2UNICODE(pNotify->memberAccount);
	//int iFind;
	//if(FindColum(memberAccount,COL_MEM_ACCOUNT,iFind))
	//{
	//	m_listMember.DeleteItem(iFind);
	//}
	

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	/////释放IM_S_DISCUSSGROUP_NOTIFY结构体中TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);

	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}

LRESULT CIMDlg::OnGroupOwnerChange(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}	

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	/////释放IM_S_DISCUSSGROUP_NOTIFY结构体中TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);

	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}

BOOL CIMDlg::FindColum(const CString& cstrKey,int iColnum,int& iFind)
{
	int iSize = m_listMember.GetItemCount();
	for(int i = 0; i< iSize; i++)
	{
		if(cstrKey.Compare(m_listMember.GetItemText(i,iColnum)) == 0)
		{
			iFind = i;
			return TRUE;
		}
	}
	return FALSE;
}

void CIMDlg::RefershChairMan(const std::string& strAccount)
{
	CString Chairman = CTools::UTF2UNICODE(strAccount);
	int iFind = -1;
	if(FindColum(Chairman,COL_MEM_ACCOUNT,iFind))
	{
		m_listMember.SetItemText(iFind,COL_MEM_Compere,L"主席");
	}
}

void CIMDlg::ComMsgFormat(CString& cotent, CString& sendContent)
{
	sendContent = _T("<r><g>1</g><c>");
	CString cstrTemp = _T("<imbody><imagelist/><html><![CDATA[<FONT style='font-size:14px'>");
	cstrTemp += cotent;
/*	cstrTemp.Replace(_T("\r\n"), _T("<BR>"));*/
	cstrTemp += _T("</FONT>]]></html><content>");
	cstrTemp += cotent;
	cstrTemp += _T("</content></imbody>");

	std::string strTmpContent = CTools::UNICODE2UTF(cstrTemp);
	int nLength = strTmpContent.length();
	// 压缩
	TUP_UCHAR *ack = NULL;
	TUP_INT nMsgLength = strTmpContent.length();
	tup_im_gzlib_comp(strTmpContent.c_str(), &ack, &nMsgLength);

	// 编码n
	TUP_UINT nLen = (TUP_UINT)(nMsgLength);
	TUP_CHAR *pEncode = new TUP_CHAR[sizeof(TUP_CHAR) * (nLength + 1)];
	memcpy(pEncode, strTmpContent.c_str(), nLength);
	pEncode[nLength] = '\0';
	tup_im_base64_encode(ack, pEncode, &nLen);
	std::string strTemp = pEncode;
	cstrTemp = CTools::UTF2UNICODE(strTemp);
	sendContent += cstrTemp;
	sendContent += _T("</c></r>");
	SAFE_DELETE_ARRAY(pEncode);
	tup_im_release_tup_mem((TUP_VOID*)ack);
}

void CIMDlg::UnCompMsgFormat(CString& content, CString& sendContent)
{
	sendContent = _T("<r><g>0</g><c>");
	content.Replace(_T(" "), _T("&nbsp;"));
	content.Replace(_T("\r\n"), _T("&lt;BR&gt;"));
	content.Replace(_T("&"), _T("&amp;"));
	content.Replace(_T("<"),_T("&lt;"));
	content.Replace(_T(">"), _T("&gt;"));
	content.Replace(_T("\'"), _T("&apos;"));
	content.Replace(_T("\""),  _T("&quot;"));
	CString strTemp(_T("&lt;imbody&gt;&lt;imagelist/&gt;&lt;html&gt;&lt;![CDATA[&lt;FONT style=&apos;font-size:14px&apos; face=&apos;Segoe UI&apos;&gt;"));
	strTemp += content;
	strTemp += _T("&lt;/FONT&gt;]]&gt;&lt;/html&gt;&lt;content&gt;");
	strTemp += content;
	strTemp += _T("&lt;/content&gt;&lt;/imbody&gt;");

	sendContent += strTemp;
	sendContent += _T("</c></r>");
}

void CIMDlg::ProcessCotentFromeSpaceOrUC(std::string& cotent)
{
	size_t pos1 = cotent.find("<g>");
	size_t pos2 = cotent.find("</g>");
	std::string compValue = cotent.substr(pos1 + 3, pos2 - pos1 - 3);
	if (compValue == "1")
	{
		pos1 = cotent.find("<c>");
		pos2 = cotent.find("</c>");
		cotent = cotent.substr(pos1 + 3, pos2 - pos1 - 3);

		// 解码
		TUP_UINT nmsgLen = cotent.length() + 1;
		TUP_UCHAR *pDecodeMsg = new TUP_UCHAR[nmsgLen];
		memset(pDecodeMsg, 0, nmsgLen);
		tup_im_base64_decode(cotent.c_str(), pDecodeMsg,&nmsgLen);

		// 解压缩
		TUP_CHAR *unCompSzbuffer = NULL;
		TUP_INT nLength = TUP_INT(nmsgLen);
		tup_im_gzlib_uncomp((TUP_CHAR*)pDecodeMsg, &unCompSzbuffer, &nLength);
		cotent = unCompSzbuffer;
		delete []pDecodeMsg;
		pDecodeMsg = NULL;
		tup_im_release_tup_mem((TUP_VOID*)unCompSzbuffer);
	}
	else
	{
		CTools::ReplaceSpecialTag(cotent);
		CTools::ReplaceParagraphTag(cotent);
	}
}

void CIMDlg::ParseStringFromUCoreSpase(CString& content)
{
	int beginPos = 0;
	int endPos = content.Find(_T("<IMG"));

	// endPos值为-1，表示是纯文本，直接插入即可
	if (-1 == endPos)
	{
		endPos = content.Find(_T("</FONT>"));
		CString strTemp = content.Left(endPos);
		beginPos = strTemp.Find(_T("<FONT"));
		strTemp = strTemp.Mid(beginPos);
		beginPos = strTemp.Find(_T(">"));
		strTemp = strTemp.Mid(beginPos + 1);
		// 转义字符二次替换
		strTemp.Replace(_T("&amp;"), _T("&"));
		strTemp.Replace(_T("&lt;"), _T("<"));
		strTemp.Replace(_T("&gt;"), _T(">"));
		strTemp.Replace(_T("<BR>"),_T("\r\n"));
		// 转义字符二次替换
		content = strTemp;
		return;
	}
// 	else
// 	{
// 		CString cstrShowMsg(_T(""));
// 		while (-1 != endPos)
// 		{
// 			CString strTemp = content.Left(endPos);
// 			beginPos = strTemp.ReverseFind(_T('>'));
// 			if (-1 != beginPos)
// 			{
// 				strTemp = strTemp.Mid(beginPos + 1);
// 				// 转义字符二次替换
// 				strTemp.Replace(_T("&amp;"), _T("&"));
// 				strTemp.Replace(_T("&lt;"), _T("<"));
// 				strTemp.Replace(_T("&gt;"), _T(">"));
// 				// 转义字符二次替换
// 				cstrShowMsg += strTemp;
// 				//UpdataChatContent(account, utcStamp, strTemp);
// 			}
// 
// 			beginPos = content.Find(_T("UC.InternalImg//emotion/"));
// 			if (-1 != beginPos)
// 			{
// 				content = content.Mid(beginPos);
// 				endPos = content.Find(_T('>'));
// 				strTemp = content.Left(endPos);
// 				beginPos = strTemp.ReverseFind(_T('/'));
// 				endPos = strTemp.ReverseFind(_T('\"'));
// 				strTemp = strTemp.Mid(beginPos + 1, endPos - beginPos - 1);
// 				for (map<CString, CString>::iterator item = m_EmotionReplace.begin(); item != m_EmotionReplace.end(); ++item)
// 				{
// 					if (item->first.IsEmpty()) continue;// 为空则跳过
// 					if (strTemp == item->second)
// 					{
// 						m_strDefaultEmotionPath += item->second;
// 						CImage image;
// 						image.Load(m_strDefaultEmotionPath);
// 						CSize imageSize = CTools::GetImageSize(image.GetHeight(), image.GetWidth());
// 						//InsertImage(m_strDefaultEmotionPath, imageSize.cx, imageSize.cy, TRUE, CTools::GetFileName(m_strDefaultEmotionPath, FALSE), TRUE);
// 						m_pDocument->clear();
// 						CString strHtmlCont;
// 						strHtmlCont.Format(_T("<img src=%s WIDTH=%dpx HEIGHT=%dpx />"), m_strDefaultEmotionPath.GetString(), imageSize.cx, imageSize.cy);
// 						cstrShowMsg += strHtmlCont;
// 						// 						UpdataChatContent(account, utcStamp, strHtmlCont);
// 						int pos = m_strDefaultEmotionPath.ReverseFind(_T('\\'));
// 						if (-1 != pos)
// 						{
// 							m_strDefaultEmotionPath = m_strDefaultEmotionPath.Left(pos + 1);
// 						}
// 						break;
// 					}
// 				}
// 			}
// 
// 			content = content.Mid(beginPos);
// 			endPos = content.Find(_T("<IMG"));
// 		}
// 		if (-1 == endPos)
// 		{
// 			endPos = content.Find(_T("</FONT>"));
// 			CString strTemp = content.Left(endPos);
// 			beginPos = strTemp.ReverseFind(_T('>'));
// 			strTemp = strTemp.Mid(beginPos + 1);
// 			// 转义字符二次替换
// 			strTemp.Replace(_T("&amp;"), _T("&"));
// 			strTemp.Replace(_T("&lt;"), _T("<"));
// 			strTemp.Replace(_T("&gt;"), _T(">"));
// 			// 转义字符二次替换
// 			cstrShowMsg += strTemp;
// 		}
// 	}
}
