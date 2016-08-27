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

// EntAddrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eSDK_TUP_PC_IM_Demo.h"
#include "EntAddrDlg.h"
#include "Tools.h"

const unsigned int SIZEPPAGE = 20;

// CEntAddrDlg �Ի���

IMPLEMENT_DYNAMIC(CEntAddrDlg, CDialog)

CEntAddrDlg::CEntAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntAddrDlg::IDD, pParent)
	, m_iCurDptID(-1)
	, m_ulStaffSize(0)
	, m_uiMaxPage(1)
	, m_uiMinPage(1)
	, m_cstrLoginAccount(_T(""))
{
}

CEntAddrDlg::~CEntAddrDlg()
{
}

void CEntAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DEPT, m_treeDpt);
	DDX_Control(pDX, IDC_EDIT_FIND, m_edtSearch);
	DDX_Control(pDX, IDC_LIST_MEMBER, m_listMember);
	DDX_Control(pDX, IDC_EDIT_PAGE, m_edtCurPage);
	DDX_Control(pDX, IDC_STATIC_SUMSIZE, m_stcSumPage);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_END, m_btnEnd);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_btnPrev);
}


BEGIN_MESSAGE_MAP(CEntAddrDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEPT, &CEntAddrDlg::OnTvnSelchangedTreeDept)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_MEMBER, &CEntAddrDlg::OnLvnGetdispinfoListMember)
	ON_EN_UPDATE(IDC_EDIT_FIND, &CEntAddrDlg::OnEnUpdateEditFind)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CEntAddrDlg::OnBnClickedButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CEntAddrDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_START, &CEntAddrDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_END, &CEntAddrDlg::OnBnClickedButtonEnd)
	ON_EN_UPDATE(IDC_EDIT_PAGE, &CEntAddrDlg::OnEnUpdateEditPage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MEMBER, &CEntAddrDlg::OnNMRClickListMember)
	ON_COMMAND_RANGE(ID_ENTADDR_GROUP_ADD_MENU_START, ID_ENTADDR_GROUP_ADD_MENU_END, &CEntAddrDlg::OnClickEntAddrMenuItem)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CEntAddrDlg ��Ϣ�������

BOOL CEntAddrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	RefreshControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CEntAddrDlg::RefreshControl(void)
{
	SetWindowText(L"��ҵͨѶ¼");

	m_edtSearch.SetWindowText(L"");

	//get department
	//�ӷ�������ȡ���в�����Ϣ
	IM_S_GETDEPTS_ACK rootDptAck;
	tup_im_getdepts(-1,&rootDptAck);

	//���������
	HTREEITEM rootItem;
	if(rootDptAck.result == TUP_TRUE)
	{
		CString dptRootName(L"��ҵͨѶ¼");
		m_treeDpt.DeleteAllItems();
		rootItem = m_treeDpt.InsertItem(dptRootName,TVI_ROOT);
	}
	//�����б�
	TUP_S_LIST* listItem = rootDptAck.deptList;
	if(NULL == listItem)
	{
		return;
	}
	IM_S_DEPTINFO* RootDptInfo = (IM_S_DEPTINFO*)listItem->data;

	InsertDpt(RootDptInfo->deptID,rootItem);

	//չ�������б���Ϣ
	m_treeDpt.Expand(rootItem, TVE_EXPAND);	

	//���listctrl�ؼ�
	m_listMember.ModifyStyle(0,LVS_SINGLESEL);
	m_listMember.InsertColumn(COL_Status, _T(" "), LVCFMT_LEFT, 25);
	m_listMember.InsertColumn(COL_Name, _T("����"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_ACCOUNT, _T("�˺�"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_DptName, _T("����"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_Email, _T("�����ʼ�"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_BINDNO1, _T("���ն˵绰"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_BINDNO2, _T("���ն˵绰2"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_MOBILE, _T("�ƶ��绰"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OFFICENUM, _T("�칫�绰"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OFFICENUM2, _T("�칫�绰2"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_HOMENUM, _T("��ͥ�绰"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OTHERNUM, _T("�����绰"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_OTHERNUM2, _T("�����绰2"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_FAX, _T("����"), LVCFMT_LEFT, 100);
	m_listMember.InsertColumn(COL_TITLE, _T("ְ��"), LVCFMT_LEFT, 100);

	DWORD dwStyle = m_listMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;		//�����ߣ�ֻ������report����listctrl��
	m_listMember.SetExtendedStyle(dwStyle); //������չ���

	m_stcSumPage.SetWindowText(_T("1"));
	m_edtCurPage.SetWindowText(_T("1"));
	/////�ͷ�IM_S_GETDEPTS_ACK�е�TUP_S_LISTָ��/////
	tup_im_release_tup_list(rootDptAck.deptList);
}

void CEntAddrDlg::InsertDpt(TUP_INT64 dptID,HTREEITEM parentItem)
{
	//�ӷ�������ȡָ��������Ϣ
	IM_S_GETDEPTS_ACK SubdptAck;
	tup_im_getdepts(dptID,&SubdptAck);

	TUP_S_LIST* listItem = SubdptAck.deptList;	
	while(NULL != listItem)
	{		
		IM_S_DEPTINFO* DptInfo = (IM_S_DEPTINFO*)listItem->data;
		if(NULL == DptInfo)
		{
			break;
		}	
		CString dptName;
		CTools::string2CString(DptInfo->deptName,dptName);
		HTREEITEM subItem = m_treeDpt.InsertItem(dptName,parentItem);
		m_treeDpt.SetItemData(subItem,(DWORD)DptInfo->deptID);
		TUP_INT64 subId = DptInfo->deptID;

		InsertDpt(subId,subItem);

		listItem = listItem->next;
	}
	/////�ͷ�IM_S_GETDEPTS_ACK�е�TUP_S_LISTָ��/////
	tup_im_release_tup_list(SubdptAck.deptList);
}

void CEntAddrDlg::OnTvnSelchangedTreeDept(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TVITEMW *pItem = &(pNMTreeView->itemNew);
	HTREEITEM pitem = pItem->hItem;
	m_iCurDptID = (TUP_INT64)m_treeDpt.GetItemData(pitem);
	ShowDptMember(m_iCurDptID,0);	
	

	*pResult = 0;
}

void CEntAddrDlg::RefreshPageSize()
{
	int iPageSize = m_ulStaffSize/SIZEPPAGE;
	int iRemain = m_ulStaffSize%SIZEPPAGE;

	if(iRemain > 0)
	{
		iPageSize++;
	}
	m_uiMaxPage = iPageSize;
	m_uiMinPage = 1;

	ShowPageCtrl(iPageSize);
}

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
		m_edtCurPage.EnableWindow(FALSE);
		m_btnStart.EnableWindow(FALSE);
		m_btnEnd.EnableWindow(FALSE);
		m_btnNext.EnableWindow(FALSE);
		m_btnPrev.EnableWindow(FALSE);
		return;
	}

	m_stcSumPage.EnableWindow(TRUE);
	m_edtCurPage.EnableWindow(TRUE);
	m_btnStart.EnableWindow(TRUE);
	m_btnEnd.EnableWindow(TRUE);
	m_btnNext.EnableWindow(TRUE);
	m_btnPrev.EnableWindow(TRUE);
}

int CEntAddrDlg::GetPageSize()
{
	CString cstrSize;
	m_edtCurPage.GetWindowText(cstrSize);
	std::string strPage = CTools::UNICODE2UTF(cstrSize);
	return atoi(strPage.c_str());
}

void CEntAddrDlg::SetPageSize(int iPage)
{
	char chPage[5] = {0};
	_itoa_s(iPage,chPage,10);
	CString cstrMaxPage = CTools::UTF2UNICODE(chPage);
	m_edtCurPage.SetWindowText(cstrMaxPage);
}

void CEntAddrDlg::ShowDptMember(TUP_INT64 dptID,unsigned int uiPage)
{
	m_listMember.DeleteAllItems();

	CString cstrKey;
	m_edtSearch.GetWindowText(cstrKey);

	IM_S_QUERY_ENTADDRESSBOOK_ARG entArg;
	entArg.isNeedAmount = TUP_TRUE;
	entArg.deptID = dptID;
	entArg.orderType = IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN;
	entArg.orderModel = IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC;
	entArg.offset = (uiPage-1)*SIZEPPAGE;
	entArg.count = SIZEPPAGE;
	CTools::CString2Char(cstrKey,entArg.queryKey,IM_D_MAX_DESC_LENGTH);
	IM_S_QUERY_ENTADDRESSBOOK_ACK entAck;

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
		m_listMember.InsertItem(i++,L"");

		pUserItem = pUserItem->next;
	}
	///�ͷ�IM_S_QUERY_ENTADDRESSBOOK_ACK�ṹ����TUPLIST�ڴ�////
	tup_im_release_tup_list(entAck.userList);
}

void CEntAddrDlg::OnLvnGetdispinfoListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

void CEntAddrDlg::OnEnUpdateEditFind()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	ShowDptMember(m_iCurDptID,0);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CEntAddrDlg::OnBnClickedButtonLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = GetPageSize();
	i--;
	SetPageSize(i);
}

void CEntAddrDlg::OnBnClickedButtonNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = GetPageSize();
	i++;
	SetPageSize(i);
}

void CEntAddrDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetPageSize(m_uiMinPage);
}

void CEntAddrDlg::OnBnClickedButtonEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetPageSize(m_uiMaxPage);
}

void CEntAddrDlg::OnEnUpdateEditPage()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�
	CString cstrPage;
	m_edtCurPage.GetWindowText(cstrPage);
	std::string strPage = CTools::UNICODE2UTF(cstrPage);
	unsigned int iPage = atoi(strPage.c_str());
	if(iPage > m_uiMaxPage)
	{
		char maxPage[5] = {0};
		_itoa_s(m_uiMaxPage,maxPage,10);
		CString cstrMaxPage = CTools::UTF2UNICODE(maxPage);
		m_edtCurPage.SetWindowText(cstrMaxPage);
		iPage = m_uiMaxPage;

	}
	else if(iPage < m_uiMinPage)
	{
		m_edtCurPage.SetWindowText(_T("1"));
		iPage = m_uiMinPage;
	}

	ShowDptMember(m_iCurDptID,iPage);


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CEntAddrDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

void CEntAddrDlg::OnNMRClickListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

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
		CMenu submenu;
		submenu.CreatePopupMenu();

		m_mapGroup.clear();
		MAP_GROUP::iterator itGroup = g_mapGroup.begin();
		MAP_GROUP::iterator itEnd = g_mapGroup.end();
		UINT umenuid = ID_ENTADDR_GROUP_ADD_MENU_START;
		for(;itGroup!=itEnd;itGroup++)
		{
			IM_S_USERGROUPINFO group = (IM_S_USERGROUPINFO)itGroup->second;
			CString strGroupName = CTools::UTF2UNICODE(group.name);
			submenu.AppendMenu(MF_STRING, umenuid,  strGroupName);
			m_mapGroup[umenuid] = group.id;
			umenuid++;
		}

		menu.AppendMenu(MF_BYPOSITION | MF_POPUP, (UINT)submenu.m_hMenu,  _T("��Ϊ��ϵ��"));
		///DTS2015112001707  /by c00327158//�������Ϊ�Լ�������ʹ�øù���//////
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

		/////�Ѿ�������ѵĳ�Ա���ܹ��������   Start////////

		if (m_Account == g_Account || IsContactMenber(m_Account))
		{
			menu.EnableMenuItem((UINT)submenu.m_hMenu, MF_DISABLED|MF_GRAYED);
		}
		//////�Ѿ�������ѵĳ�Ա���ܹ��������  End//////////
		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);		                 
	}
}

void CEntAddrDlg::OnClickEntAddrMenuItem(UINT nID)
{
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

	if(m_cstrLoginAccount.Compare(cstrAccount) == 0)
	{
		AfxMessageBox(_T("Add yourself to your friends is not allowed"));
		return;
	}

	if(nID >= ID_ENTADDR_GROUP_ADD_MENU_START && nID <= ID_ENTADDR_GROUP_ADD_MENU_END)
	{
		IM_S_ADDFRIEND_ARG arg;
		CTools::CString2Char(cstrAccount,arg.account,IM_D_MAX_ACCOUNT_LENGTH);
		CTools::CString2Char(L"111",arg.displayName,IM_D_MAX_NAME_LENGTH);
		arg.groupID = m_mapGroup[nID];
		IM_S_ADDFRIEND_ACK ack;
		TUP_RESULT tRet = tup_im_addfriend(&arg,&ack);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(L"tup_im_addfriend failed.");
		}

		::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_UPDATE_CONTACT,NULL,NULL);
	}
}

void CEntAddrDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_ENT_DLG,NULL,NULL);

	//CDialog::OnClose();
}

void CEntAddrDlg::SetCurLoginAccount(CString& cstrAccount)
{
	m_cstrLoginAccount = cstrAccount;
}

bool CEntAddrDlg::IsContactMenber(std::string _account)
{
	//////����ǲ�����ϵ��/////
	MAP_USER::iterator ibeg = g_mapUser.begin();
	MAP_USER::iterator iend = g_mapUser.end();
	for (;ibeg != iend;ibeg++)
	{
		IM_S_USERINFO m_User = ibeg->second;
		std::string m_account = m_User.account;
		if (m_account == _account)
		{
			return true;
		}

	}
	return false;
}