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
#include "IMDlg.h"
#include "IMManage.h"
#include "Tools.h"


CIMManage::CIMManage(void)
{
}

CIMManage::~CIMManage(void)
{
}

CIMDlg* CIMManage::GetIMDlgByAccount(const std::string& strAccount)
{
	if (m_vecIMDlg.empty()) return NULL;
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		//modify by lwx294490 at 2015-6-27 start
		//when A and B is in a discuss group, A and B can also chat whith eah other secretly.
		if( NULL != pIMDlg
			&& (strAccount.compare(pIMDlg->m_targetUserInfo.account) == 0)
			&& (pIMDlg->GetDlgType() == SIGNLE_CHAT) )
		//modify by lwx294490 at 2015-6-27 end
		{
			return pIMDlg;
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

CIMDlg* CIMManage::GetIMDlgByGroupName(const std::string& strGroupName)
{
	VEC_IMDLG::iterator it = m_vecIMDlg.begin();
	VEC_IMDLG::iterator itEnd = m_vecIMDlg.end();
	for(;it!=itEnd;it++)
	{
		CIMDlg* pIMDlg = *it;
		CString GroupName;
		pIMDlg->GetWindowText(GroupName);
		if(NULL != pIMDlg && strGroupName.compare(CTools::UNICODE2UTF(GroupName)) == 0)
		{
			return pIMDlg;
		}
	}
	return NULL;
}