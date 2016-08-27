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

// EntAddrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_VIDEO_Demo.h"
#include "EntAddrDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include "Data.h"

#include <utility>

const unsigned int SIZEPAGE = 20;


// CEntAddrDlg dialog

IMPLEMENT_DYNAMIC(CEntAddrDlg, CDialog)

CEntAddrDlg::CEntAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntAddrDlg::IDD, pParent)
	, m_iCurDptID(-1)
	, m_ulStaffSize(0)
	, m_uiMaxPage(1)
	, m_uiMinPage(1)
{

}
//************************************************************************
CEntAddrDlg::~CEntAddrDlg()
{
}
//************************************************************************
void CEntAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DEPT, m_treeDpt);
	DDX_Control(pDX, IDC_STATIC_SUMSIZE, m_stcSumPage);
	DDX_Control(pDX, IDC_LIST_MEMBER, m_listMember);
	DDX_Control(pDX, IDC_EDIT_PAGE, m_editCurPage);
	DDX_Control(pDX, IDC_EDIT_FIND, m_editSearch);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_btnPrev);
	DDX_Control(pDX, IDC_BUTTON_END, m_btnEnd);
}
//************************************************************************
BEGIN_MESSAGE_MAP(CEntAddrDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START, &CEntAddrDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CEntAddrDlg::OnBnClickedButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CEntAddrDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_END, &CEntAddrDlg::OnBnClickedButtonEnd)
	ON_EN_UPDATE(IDC_EDIT_FIND, &CEntAddrDlg::OnEnUpdateEditFind)
	ON_EN_UPDATE(IDC_EDIT_PAGE, &CEntAddrDlg::OnEnUpdateEditPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEPT, &CEntAddrDlg::OnTvnSelchangedTreeDept)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_MEMBER, &CEntAddrDlg::OnLvnGetdispinfoListMember)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEMBER, &CEntAddrDlg::OnNMClickListMember)
	ON_COMMAND(ID_32771, &CEntAddrDlg::OnClickedMenuItem)
END_MESSAGE_MAP()
//************************************************************************

// CEntAddrDlg message handlers


BOOL CEntAddrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	RefreshControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//************************************************************************
void CEntAddrDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	SetPageSize(m_uiMinPage);
}


void CEntAddrDlg::OnBnClickedButtonLast()
{
	// TODO: Add your control notification handler code here
	int i = GetPageSize();
	i--;
	SetPageSize(i);
}
//************************************************************************
void CEntAddrDlg::OnBnClickedButtonNext()
{
	// TODO: Add your control notification handler code here
	int i = GetPageSize();
	i++;
	SetPageSize(i);
}
//************************************************************************
void CEntAddrDlg::OnBnClickedButtonEnd()
{
	// TODO: Add your control notification handler code here
	SetPageSize(m_uiMaxPage);
}


void CEntAddrDlg::OnEnUpdateEditFind()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	ShowDptMember(m_iCurDptID, 0);
}
//************************************************************************
void CEntAddrDlg::OnEnUpdateEditPage()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	CString cstrPage;
	m_editCurPage.GetWindowText(cstrPage);
	std::string strPage = CTools::UNICODE2UTF(cstrPage);
	unsigned int iPage = atoi(strPage.c_str());
	if(iPage > m_uiMaxPage)
	{
		char maxPage[5] = {0};
		_itoa_s(m_uiMaxPage,maxPage,10);
		CString cstrMaxPage = CTools::UTF2UNICODE(maxPage);
		m_editCurPage.SetWindowText(cstrMaxPage);
		iPage = m_uiMaxPage;

	}
	else if(iPage < m_uiMinPage)
	{
		m_editCurPage.SetWindowText(_T("1"));
		iPage = m_uiMinPage;
	}

	ShowDptMember(m_iCurDptID,iPage);
}
//************************************************************************
void CEntAddrDlg::OnTvnSelchangedTreeDept(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	TVITEMW *pItem = &(pNMTreeView->itemNew);
	HTREEITEM item = pItem->hItem;
	m_iCurDptID = (TUP_INT64)m_treeDpt.GetItemData(item);
	ShowDptMember(m_iCurDptID, 0);

	*pResult = 0;
}
//************************************************************************
void CEntAddrDlg::OnLvnGetdispinfoListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
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
//************************************************************************
BOOL CEntAddrDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
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
//************************************************************************
void CEntAddrDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_CLOSE_ENT_DLG, NULL, NULL);
	//CDialog::OnClose();
}
//************************************************************************
void CEntAddrDlg::OnNMClickListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_listMember.ScreenToClient(&pt);

	UINT uFlag = 0;
	int hSelectedItem = m_listMember.HitTest(pt, &uFlag);
	if (0 <= hSelectedItem)
	{
		m_listMember.ClientToScreen(&pt);
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CMenu *pop = menu.GetSubMenu(0);
		pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}
//************************************************************************
void CEntAddrDlg::RefreshControl()
{
	SetWindowText(_T("企业通讯录"));
	m_editSearch.SetWindowText(_T(""));

	// 获取部门
	IM_S_GETDEPTS_ACK rootDptAck;
	TUP_RESULT tRet = tup_im_getdepts(-1, &rootDptAck);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getdepts failed!"));
		return;
	}

	// 插入根部门
	HTREEITEM rootItem = NULL;
	if (TUP_TRUE == rootDptAck.result)
	{
		CString deptRootName(_T("企业通讯录"));
		m_treeDpt.DeleteAllItems();
		rootItem = m_treeDpt.InsertItem(deptRootName, TVI_ROOT);
	}

	TUP_S_LIST *listItem = rootDptAck.deptList;
	if (NULL == listItem) return;
	IM_S_DEPTINFO *rootDeptInfo = (IM_S_DEPTINFO*)listItem->data;
	InsertDpt(rootDeptInfo->deptID, rootItem);
	m_treeDpt.Expand(rootItem, TVE_EXPAND);

	m_listMember.ModifyStyle(0,LVS_SINGLESEL);
	m_listMember.InsertColumn(COL_Status, _T(" "), LVCFMT_LEFT, 25);
	m_listMember.InsertColumn(COL_Name, _T("姓名"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_ACCOUNT, _T("账号"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_DptName, _T("部门"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_Email, _T("电子邮件"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_BINDNO1, _T("软终端电话"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_BINDNO2, _T("软终端电话2"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_MOBILE, _T("移动电话"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OFFICENUM, _T("办公电话"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OFFICENUM2, _T("办公电话2"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_HOMENUM, _T("家庭电话"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OTHERNUM, _T("其他电话"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OTHERNUM2, _T("其他电话2"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_FAX, _T("传真"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_TITLE, _T("职务"), LVCFMT_LEFT, 100);

	// 设置ListCtrl控件风格
	LONG lStyle = GetWindowLong(m_listMember.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_SINGLESEL;
	lStyle |= LVS_REPORT;

	// 设置ListCtrl控件扩展风格
	DWORD dwStyle = m_listMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_listMember.SetExtendedStyle(dwStyle);

	m_stcSumPage.SetWindowText(_T("1"));
	m_editCurPage.SetWindowText(_T("1"));
}
//************************************************************************
void CEntAddrDlg::InsertDpt(TUP_INT64 dptID,HTREEITEM parentItem)
{
	IM_S_GETDEPTS_ACK SubDeptAck;
	TUP_RESULT tRet = tup_im_getdepts(dptID, &SubDeptAck);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_getdepts failed!"));
		return;
	}

	TUP_S_LIST *listItem = SubDeptAck.deptList;
	while (NULL != listItem)
	{
		IM_S_DEPTINFO *DeptInfo = (IM_S_DEPTINFO*)listItem->data;
		if (NULL == DeptInfo) break;

		CString deptName;
		CTools::string2CString(DeptInfo->deptName, deptName);
		HTREEITEM subItem = m_treeDpt.InsertItem(deptName, parentItem);
		m_treeDpt.SetItemData(subItem, (DWORD)DeptInfo->deptID);
		TUP_INT64 subID = DeptInfo->deptID;
		InsertDpt(subID, subItem);
		listItem = listItem->next;
	}
}
//************************************************************************
void CEntAddrDlg::ShowDptMember(TUP_INT64 dptID,unsigned int uiPage)
{
	m_listMember.DeleteAllItems();

	CString cstrKey;
	m_editSearch.GetWindowText(cstrKey);

	IM_S_QUERY_ENTADDRESSBOOK_ARG entArg;
	entArg.isNeedAmount = TUP_TRUE;
	entArg.deptID = dptID;
	entArg.orderType = IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN;
	entArg.orderModel = IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC;
	entArg.offset = (uiPage-1) * SIZEPAGE;
	entArg.count = SIZEPAGE;
	CTools::CString2Char(cstrKey,entArg.queryKey,IM_D_MAX_DESC_LENGTH);
	IM_S_QUERY_ENTADDRESSBOOK_ACK entAck;
	memset(&entAck,0,sizeof(IM_S_QUERY_ENTADDRESSBOOK_ACK));

	TUP_RESULT tRet = tup_im_queryentaddressbook(&entArg,&entAck);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_queryentaddressbook failed"));
	}

	m_ulStaffSize = entAck.recordAmount;
	RefreshPageSize();

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
		m_listMember.InsertItem(i++,_T(""));

		pUserItem = pUserItem->next;
	}
	//////释放IM_S_QUERY_ENTADDRESSBOOK_ACK中的tuplist指针////
	tup_im_release_tup_list(entAck.userList);
}
//************************************************************************
void CEntAddrDlg::SetPageSize(int iPage)
{
	char chPage[5] = {0};
	_itoa_s(iPage,chPage,10);
	CString cstrMaxPage = CTools::UTF2UNICODE(chPage);
	m_editCurPage.SetWindowText(cstrMaxPage);
}
//************************************************************************
int CEntAddrDlg::GetPageSize()
{
	CString cstrSize;
	m_editCurPage.GetWindowText(cstrSize);
	std::string strPage = CTools::UNICODE2UTF(cstrSize);
	return atoi(strPage.c_str());
}
//************************************************************************
void CEntAddrDlg::ShowPageCtrl(int iSumPage)
{
	char chPageSize[5] = {0};
	_itoa_s(iSumPage,chPageSize,10);
	CString cstrPage = CTools::UTF2UNICODE(chPageSize);
	m_stcSumPage.SetWindowText(cstrPage);

	if(1 >= iSumPage)
	{
		m_stcSumPage.SetWindowText(_T("1"));
		m_stcSumPage.EnableWindow(FALSE);
		m_editCurPage.EnableWindow(FALSE);
		m_btnStart.EnableWindow(FALSE);
		m_btnEnd.EnableWindow(FALSE);
		m_btnNext.EnableWindow(FALSE);
		m_btnPrev.EnableWindow(FALSE);
		return;
	}

	m_stcSumPage.EnableWindow(TRUE);
	m_editCurPage.EnableWindow(TRUE);
	m_btnStart.EnableWindow(TRUE);
	m_btnEnd.EnableWindow(TRUE);
	m_btnNext.EnableWindow(TRUE);
	m_btnPrev.EnableWindow(TRUE);
}
//************************************************************************
void CEntAddrDlg::RefreshPageSize()
{
	int iPageSize = m_ulStaffSize / SIZEPAGE;
	int iRemain = m_ulStaffSize % SIZEPAGE;

	if(iRemain > 0)
	{
		iPageSize++;
	}
	m_uiMaxPage = iPageSize;
	m_uiMinPage = 1;

	ShowPageCtrl(iPageSize);
}
//************************************************************************
bool CEntAddrDlg::IsContactMenber(std::string _account)
{
	//////检查是不是联系人/////
	MAP_USER::iterator ibeg = g_mapUser.begin();
	MAP_USER::iterator iend = g_mapUser.end();

	for (;ibeg != iend;ibeg++)
	{
		if (ibeg->second.account == _account)
		{
			return true;
		}
	}

	STAFF_MAP::iterator itemBegin = m_mapStaff.begin();
	STAFF_MAP::iterator itemEnd = m_mapStaff.end();
	for (; itemBegin != itemEnd; itemBegin++)
	{
		if (itemBegin->second.account == _account)
		{
			g_mapUser.insert(std::make_pair(itemBegin->second.staffID, itemBegin->second));
		}
	}
	return false;
}
//************************************************************************
void CEntAddrDlg::OnClickedMenuItem()
{
	// TODO: Add your command handler code here
	int nItem = -1;
	POSITION pos = m_listMember.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
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
	CString cstrAccount = m_listMember.GetItemText(nItem,COL_ACCOUNT);
	std::string m_Account;
	m_Account = CTools::UNICODE2UTF(cstrAccount);

	if (IsContactMenber(m_Account))
	{
		AfxMessageBox(_T("This member is already exist"));
	}
	::SetWindowPos(this->m_hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);// 添加成员窗口置顶
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_UPDATE_CONTACT, NULL, NULL);// 刷新成员列表
}
