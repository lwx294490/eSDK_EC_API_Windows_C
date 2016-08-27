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

#include "StdAfx.h"
#include "resource.h"
#include "IMDlg.h"
#include "ConfDlg.h"
#include "GroupInviteDlg.h"
#include "IMManage.h"



CIMManage::CIMManage(void)
{
}

CIMManage::~CIMManage(void)
{
}

CIMDlg* CIMManage::GetIMDlgByAccount(const std::string& strAccount)
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg && strAccount.compare(pIMDlg->m_targetUserInfo.account) == 0)
		{
			return pIMDlg;
		}
	}
	return NULL;
}

CIMDlg* CIMManage::GetIMDlgByCallID(TUP_UINT32 uiCallID)
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg && uiCallID == pIMDlg->m_uiCallID)
		{
			return pIMDlg;
		}
	}
	return NULL;
}
CIMDlg* CIMManage::GetIMDlgByConfID(TUP_UINT32 uiConflID)
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg && uiConflID == pIMDlg->m_uiConfID)
		{
			return pIMDlg;
		}
	}
	return NULL;
}

CConfDlg* CIMManage::GetConfDlgByConfID(TUP_UINT32 uiConfID)
{
	VEC_CONFDLG::iterator it = m_vecConfDlg.begin();
	VEC_CONFDLG::iterator itEnd = m_vecConfDlg.end();
	for(;it!=itEnd;it++)
	{
		CConfDlg* pConfDlg = *it;
		if(NULL != pConfDlg && uiConfID == pConfDlg->m_uiConfID)
		{
			return pConfDlg;
		}
	}

	return NULL;
}
CGroupInviteDlg* CIMManage::GetGroupNotifyDlgByID(const std::string& strGroupID)
{
	VEC_CGROUPNOTIFY::iterator itBegin = m_vecGroupNotifyDlg.begin();
	VEC_CGROUPNOTIFY::iterator itEnd = m_vecGroupNotifyDlg.end();
	for(;itBegin!=itEnd;itBegin++)
	{
		CGroupInviteDlg* pGroupNotifyDlg = *itBegin;
		if(NULL != pGroupNotifyDlg && strGroupID == pGroupNotifyDlg->m_groupId)
		{
			return pGroupNotifyDlg;
		}
	}
	return NULL;
}

CIMDlg* CIMManage::GetIMDlgByGroupID(const std::string& strGroupID)
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg && strGroupID.compare(pIMDlg->m_strGroupID) == 0)
		{
			return pIMDlg;
		}
	}
	return NULL;
}

CIMDlg* CIMManage::CreateIMDlgByAccount(const std::string& strAccount)
{
	CIMDlg* pIMDlg = new CIMDlg;
	pIMDlg->Create(CIMDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));

	strcpy_s(pIMDlg->m_targetUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());

	m_vecIMDlg.push_back(pIMDlg);

	return pIMDlg;

}
CIMDlg* CIMManage::CreateIMDlgByGroupID(const std::string& strGroupID)
{
	CIMDlg* pIMDlg = new CIMDlg;
	pIMDlg->Create(CIMDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));

	pIMDlg->m_strGroupID = strGroupID;

	m_vecIMDlg.push_back(pIMDlg);

	return pIMDlg;
}

CIMDlg* CIMManage::CreateIMDlgByCallID(TUP_UINT32 uiCallID)
{
	CIMDlg* pIMDlg = new CIMDlg;
	pIMDlg->Create(CIMDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));

	pIMDlg->m_uiCallID = uiCallID;

	m_vecIMDlg.push_back(pIMDlg);

	return pIMDlg;
}

CConfDlg* CIMManage::CreateConfDlgByConfID(TUP_UINT32 uiConfID)
{
	CConfDlg* pConfDlg = new CConfDlg;
	pConfDlg->Create(CConfDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));

	pConfDlg->m_uiConfID = uiConfID;

	m_vecConfDlg.push_back(pConfDlg);

	return pConfDlg;
}

CGroupInviteDlg* CIMManage::CreateGroupNotifyDlgByID(const std::string& strGroupID)
{
	CGroupInviteDlg* pGroupNotifyDlg = new CGroupInviteDlg;
	pGroupNotifyDlg->Create(CGroupInviteDlg::IDD,CWnd::FromHandle(::GetDesktopWindow()));
	pGroupNotifyDlg->m_groupId = strGroupID;
	m_vecGroupNotifyDlg.push_back(pGroupNotifyDlg);
	return pGroupNotifyDlg;
}
void CIMManage::DelGroupNotifyDlgByDlg(CGroupInviteDlg* pGroupNotifyDlg)
{
	VEC_CGROUPNOTIFY::iterator it = m_vecGroupNotifyDlg.begin();
	VEC_CGROUPNOTIFY::iterator itEnd = m_vecGroupNotifyDlg.end();
	for(;it!=itEnd;it++)
	{
		CGroupInviteDlg* pNotifyDlg = *it;
		if(NULL != pNotifyDlg && pNotifyDlg == pGroupNotifyDlg)
		{
			m_vecGroupNotifyDlg.erase(it);
			SAFE_DELETE(pGroupNotifyDlg);
			break;
		}
	}
}

void CIMManage::DeleteIMDlgByIMDlg(CIMDlg* pDlg)
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg && pDlg == pIMDlg)
		{
			m_vecIMDlg.erase(it);
			SAFE_DELETE(pIMDlg);
			break;
		}
	}
}
void CIMManage::DeleteConfDlgByConfDlg(CConfDlg* pDlg)
{
	VEC_CONFDLG::iterator it = m_vecConfDlg.begin();
	VEC_CONFDLG::iterator itEnd = m_vecConfDlg.end();
	for(;it!=itEnd;it++)
	{
		CConfDlg* pConfDlg = *it;
		if(NULL != pConfDlg && pDlg == pConfDlg)
		{
			m_vecConfDlg.erase(it);
			SAFE_DELETE(pConfDlg);
			break;
		}
	}

}
//Add by lWX294490 to fix DTS2015082706818 at 2015-08-27 begin
void CIMManage::DeleteAllIMDlg()
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg)
		{
			::PostMessage(pIMDlg->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
		}
	}
}

void CIMManage::DelAllGroupNotifyDlg()
{
	VEC_CGROUPNOTIFY::iterator it = m_vecGroupNotifyDlg.begin();
	VEC_CGROUPNOTIFY::iterator itEnd = m_vecGroupNotifyDlg.end();
	for(;it!=itEnd;it++)
	{
		CGroupInviteDlg* pNotifyDlg = *it;
		if(NULL != pNotifyDlg)
		{
			pNotifyDlg->DestroyWindow();
			SAFE_DELETE(pNotifyDlg);
		}
	}
	m_vecGroupNotifyDlg.clear();
}

void CIMManage::DeleteAllConfDlg()
{
	VEC_CONFDLG::iterator it = m_vecConfDlg.begin();
	VEC_CONFDLG::iterator itEnd = m_vecConfDlg.end();
	for(;it!=itEnd;it++)
	{
		CConfDlg* pConfDlg = *it;
		if(NULL != pConfDlg)
		{
			::PostMessage(pConfDlg->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
		}
	}
}
//Add by lWX294490 to fix DTS2015082706818 at 2015-08-27 end


//Add by c00327158 to fix DTS2015090702660  at 2015-09-07 Start
int CIMManage::GetConfCallNUmber()
{
	int ConfCallNumber = 0;
	VEC_CONFDLG::iterator it = m_vecConfDlg.begin();
	VEC_CONFDLG::iterator itEnd = m_vecConfDlg.end();
	for(;it!=itEnd;it++)
	{
		CConfDlg* pConfDlg = *it;
		if(NULL != pConfDlg)
		{
			if (0 != pConfDlg->m_uiConfID)
			{
				ConfCallNumber ++ ;
			}

		}
	}

	return ConfCallNumber;
}

int CIMManage::GetImDlgCallNumber()
{
	int IMCallNumber = 0;
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		if(NULL != pIMDlg)
		{
			if (0 != pIMDlg->GetCallid())
			{
				IMCallNumber ++ ;
			}

		}
	}

	return IMCallNumber;
}

//Add by c00327158 to fix DTS2015090702660  at 2015-09-07 End