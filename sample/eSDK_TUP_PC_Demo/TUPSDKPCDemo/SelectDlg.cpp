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

// SelectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "SelectDlg.h"
#include "Tools.h"


// CSelectDlg 对话框

IMPLEMENT_DYNAMIC(CSelectDlg, CDialog)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{

}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtFind);
	DDX_Control(pDX, IDC_LIST_FRIEND, m_listContact);
	DDX_Control(pDX, IDC_LIST_SELECT, m_listSelect);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_FRIEND, &CSelectDlg::OnLvnGetdispinfoListFriend)
	ON_EN_UPDATE(IDC_EDIT1, &CSelectDlg::OnEnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CSelectDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CSelectDlg::OnBnClickedButtonDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FRIEND, &CSelectDlg::OnNMDblclkListFriend)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SELECT, &CSelectDlg::OnNMDblclkListSelect)
	ON_BN_CLICKED(IDOK, &CSelectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectDlg 消息处理程序

BOOL CSelectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listContact.ModifyStyle(0,LVS_SINGLESEL);
	m_listContact.InsertColumn(COL_Status, _T(" "), LVCFMT_LEFT, 25);
	m_listContact.InsertColumn(COL_Name, _T("姓名"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_ACCOUNT, _T("账号"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_DptName, _T("部门"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_Email, _T("电子邮件"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_BINDNO1, _T("软终端电话"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_BINDNO2, _T("软终端电话2"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_MOBILE, _T("移动电话"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_OFFICENUM, _T("办公电话"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_OFFICENUM2, _T("办公电话2"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_HOMENUM, _T("家庭电话"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_OTHERNUM, _T("其他电话"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_OTHERNUM2, _T("其他电话2"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_FAX, _T("传真"), LVCFMT_LEFT, 100);
	m_listContact.InsertColumn(COL_TITLE, _T("职务"), LVCFMT_LEFT, 100);

	DWORD dwStyle = m_listContact.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listContact.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listSelect.ModifyStyle(0,LVS_SINGLESEL);
	m_listSelect.InsertColumn(COL_Status, _T(" "), LVCFMT_LEFT, 25);
	m_listSelect.InsertColumn(COL_Name, _T("姓名"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_ACCOUNT, _T("账号"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_DptName, _T("部门"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_Email, _T("电子邮件"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_BINDNO1, _T("软终端电话"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_BINDNO2, _T("软终端电话2"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_MOBILE, _T("移动电话"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_OFFICENUM, _T("办公电话"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_OFFICENUM2, _T("办公电话2"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_HOMENUM, _T("家庭电话"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_OTHERNUM, _T("其他电话"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_OTHERNUM2, _T("其他电话2"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_FAX, _T("传真"), LVCFMT_LEFT, 100);
	m_listSelect.InsertColumn(COL_TITLE, _T("职务"), LVCFMT_LEFT, 100);

	dwStyle = m_listSelect.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listSelect.SetExtendedStyle(dwStyle); //设置扩展风格

	ShowFriendList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CSelectDlg::ShowFriendList(void)
{	
	m_listContact.DeleteAllItems();
	m_mapStaff.clear();

	MAP_USER::iterator it =  g_mapUser.begin();
	MAP_USER::iterator itEnd =  g_mapUser.end();

	for(int i=0;it!=itEnd;it++,i++)
	{
		IM_S_USERINFO srcUserInfo = it->second;
		IM_S_USERINFO userInfo;		
		memcpy(&userInfo,&srcUserInfo,sizeof(IM_S_USERINFO));
		m_mapStaff[i] = userInfo;
		m_listContact.InsertItem(i,L"");
	}
}
const TUP_INT32 MAXSIZE = 50;
void CSelectDlg::ShowEntContactList(CString cstrKey)
{	
	m_listContact.DeleteAllItems();
	m_mapStaff.clear();

	std::string strKey = CTools::UNICODE2UTF(cstrKey);

	IM_S_QUERY_ENTADDRESSBOOK_ARG entArg;
	entArg.isNeedAmount = TUP_TRUE;
	entArg.deptID = -1;
	entArg.orderType = IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN;
	entArg.orderModel = IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC;
	entArg.offset = 0;
	entArg.count = MAXSIZE;
	CTools::CString2Char(cstrKey,entArg.queryKey,IM_D_MAX_DESC_LENGTH);
	IM_S_QUERY_ENTADDRESSBOOK_ACK entAck;

	TUP_RESULT tRet = tup_im_queryentaddressbook(&entArg,&entAck);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_queryentaddressbook failed"));
		return;
	}

	TUP_S_LIST* pUserItem = entAck.userList;
	int i = 0;
	while(NULL != pUserItem)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserItem->data;
		if(NULL == pUser)
		{
			break;
		}
		IM_S_USERINFO user;
		memcpy(&user,pUser,sizeof(IM_S_USERINFO));
		m_mapStaff[i]=user;
		m_listContact.InsertItem(i++,L"");

		pUserItem = pUserItem->next;
	}
	////释放IM_S_QUERY_ENTADDRESSBOOK_ACK结构体中TUPLIST内存/////
	tup_im_release_tup_list(entAck.userList);

}


void CSelectDlg::OnLvnGetdispinfoListFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LV_ITEM *pItem = &(pDispInfo->item);
	if(NULL == pItem)
	{
		return;
	}
	unsigned int iItem = pItem->iItem;

	if (iItem >= m_mapStaff.size())
	{
		return;
	}

	IM_S_USERINFO contact = m_mapStaff[iItem];
	CString itemText;
	switch (pItem->iSubItem)
	{
	case COL_Status:
		break;
	case COL_Name:
		itemText = CTools::UTF2UNICODE(contact.name);
		break;
	case COL_ACCOUNT:		
		itemText = CTools::UTF2UNICODE(contact.account);
		break;
	case COL_DptName:
		itemText =  CTools::UTF2UNICODE(contact.deptNameEn);
		break;
	case COL_Email:
		itemText =  CTools::UTF2UNICODE(contact.email);
		break;
	case COL_BINDNO1:
		itemText =  CTools::UTF2UNICODE(contact.bindNO);
		break;
	case COL_BINDNO2:
		break;
	case COL_MOBILE:
		itemText =  CTools::UTF2UNICODE(contact.mobile);
		break;
	case COL_OFFICENUM:
		itemText =  CTools::UTF2UNICODE(contact.officePhone);
		break;
	case COL_OFFICENUM2:
		break;
	case COL_HOMENUM:
		itemText =  CTools::UTF2UNICODE(contact.homePhone);
		break;
	case COL_OTHERNUM:
		itemText =  CTools::UTF2UNICODE(contact.otherPhone);
		break;
	case COL_OTHERNUM2:
		itemText =  CTools::UTF2UNICODE(contact.shortPhone);
		break;
	case COL_FAX:
		itemText =  CTools::UTF2UNICODE(contact.fax);
		break;
	case COL_TITLE:
		itemText =  CTools::UTF2UNICODE(contact.title);
		break;
	}

	::lstrcpyn(pItem->pszText, itemText, pItem->cchTextMax);

	*pResult = 0;
}

void CSelectDlg::OnEnUpdateEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。
	// TODO:  在此添加控件通知处理程序代码
	CString cstrKey;
	m_edtFind.GetWindowText(cstrKey);
	if(cstrKey.IsEmpty())
	{
		ShowFriendList();
	}
	else
	{
		ShowEntContactList(cstrKey);
	}	
}
void CSelectDlg::DelSelectUser(int iSelect)
{
	m_listSelect.DeleteItem(iSelect);
}
void CSelectDlg::AddSelectUser(int iSelect)
{
	CString cstrAccount = m_listContact.GetItemText(iSelect,COL_ACCOUNT);

	bool bFind = false;
	int iSelSize =  m_listSelect.GetItemCount();
	for(int i = 0; i< iSelSize; i++)
	{
		if(cstrAccount.Compare(m_listSelect.GetItemText(i,COL_ACCOUNT)) == 0)
		{
			bFind = true;
			break;
		}
	}
	if(bFind)
	{
		return;
	}

	CString cstrName = m_listContact.GetItemText(iSelect,COL_Name);			
	CString cstrDptName = m_listContact.GetItemText(iSelect,COL_DptName);
	CString cstrEmail = m_listContact.GetItemText(iSelect,COL_Email);
	CString cstrBindNo1 = m_listContact.GetItemText(iSelect,COL_BINDNO1);
	CString cstrBindNo2 = m_listContact.GetItemText(iSelect,COL_BINDNO2);
	CString cstrMobile = m_listContact.GetItemText(iSelect,COL_MOBILE);
	CString cstrOfficeNum = m_listContact.GetItemText(iSelect,COL_OFFICENUM);
	CString cstrOfficeNum2 = m_listContact.GetItemText(iSelect,COL_OFFICENUM2);
	CString cstrHomeNum = m_listContact.GetItemText(iSelect,COL_HOMENUM);
	CString cstrOtherNum = m_listContact.GetItemText(iSelect,COL_OTHERNUM);
	CString cstrOtherNum2 = m_listContact.GetItemText(iSelect,COL_OTHERNUM2);
	CString cstrFax = m_listContact.GetItemText(iSelect,COL_FAX);
	CString cstrTitle = m_listContact.GetItemText(iSelect,COL_TITLE);


	int iInsert = m_listSelect.InsertItem(iSelSize,L"");
	m_listSelect.SetItemText(iInsert,COL_Name,cstrName);
	m_listSelect.SetItemText(iInsert,COL_ACCOUNT,cstrAccount);
	m_listSelect.SetItemText(iInsert,COL_DptName,cstrDptName);
	m_listSelect.SetItemText(iInsert,COL_Email,cstrEmail);
	m_listSelect.SetItemText(iInsert,COL_BINDNO1,cstrBindNo1);
	m_listSelect.SetItemText(iInsert,COL_BINDNO2,cstrBindNo2);
	m_listSelect.SetItemText(iInsert,COL_MOBILE,cstrMobile);
	m_listSelect.SetItemText(iInsert,COL_OFFICENUM,cstrOfficeNum);
	m_listSelect.SetItemText(iInsert,COL_OFFICENUM2,cstrOfficeNum2);
	m_listSelect.SetItemText(iInsert,COL_HOMENUM,cstrHomeNum);
	m_listSelect.SetItemText(iInsert,COL_OTHERNUM,cstrOtherNum);
	m_listSelect.SetItemText(iInsert,COL_OTHERNUM2,cstrOtherNum2);
	m_listSelect.SetItemText(iInsert,COL_FAX,cstrFax);
	m_listSelect.SetItemText(iInsert,COL_TITLE,cstrTitle);

}
void CSelectDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSelect = -1;
	POSITION pos = m_listContact.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	else
	{
		while (pos)
		{
			iSelect = m_listContact.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", iSelect);
			AddSelectUser(iSelect);			
		}
	}
}

void CSelectDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSelect = -1;
	POSITION pos = m_listSelect.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	else
	{
		while (pos)
		{
			iSelect = m_listSelect.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", iSelect);
			DelSelectUser(iSelect);			
		}
	}

}

void CSelectDlg::OnNMDblclkListFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	if(nItem>=0 && nItem<m_listContact.GetItemCount())	
	{
		AddSelectUser(nItem);
	}

	*pResult = 0;
}


void CSelectDlg::OnNMDblclkListSelect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	if(nItem>=0 && nItem<m_listContact.GetItemCount())	
	{
		DelSelectUser(nItem);
	}
	*pResult = 0;
}

void CSelectDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mapSelectAccount.clear();
	int iSelSize =  m_listSelect.GetItemCount();
	for(int i = 0; i< iSelSize; i++)
	{
		CString cstrAccount = m_listSelect.GetItemText(i,COL_ACCOUNT);
		CString cstrName = m_listSelect.GetItemText(i,COL_Name);
		CString cstrCallNum = m_listSelect.GetItemText(i,COL_BINDNO1);
		CALL_MEMBER member;
		strcpy_s(member.account,IM_D_MAX_ACCOUNT_LENGTH,CTools::UNICODE2UTF(cstrAccount).c_str());
		strcpy_s(member.name,IM_D_MAX_NAME_LENGTH,CTools::UNICODE2UTF(cstrName).c_str());
		strcpy_s(member.CallNo,IM_D_MAX_PHONE_LENGTH,CTools::UNICODE2UTF(cstrCallNum).c_str());

		m_mapSelectAccount[member.account] = member;
	}
	
	OnOK();
}
void CSelectDlg::GetSelectUser(MAP_SELECT_USER& selUser)
{
	selUser = m_mapSelectAccount;
}
