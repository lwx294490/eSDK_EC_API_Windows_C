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

class CIMDlg;
class CConfDlg;
class CGroupInviteDlg;
class CIMManage
{
private:
	CIMManage(void);
	~CIMManage(void);
public:
	static CIMManage& GetIntance()
	{
		static CIMManage inst;
		return inst;
	}

public:
	typedef std::vector<CIMDlg*> VEC_IMDLG;
	VEC_IMDLG m_vecIMDlg;
	typedef std::vector<CConfDlg*> VEC_CONFDLG;
	VEC_CONFDLG m_vecConfDlg;

	typedef std::vector<CGroupInviteDlg*> VEC_CGROUPNOTIFY;
	VEC_CGROUPNOTIFY m_vecGroupNotifyDlg;
public:
	CIMDlg* GetIMDlgByAccount(const std::string& strAccount);
	CIMDlg* GetIMDlgByCallID(TUP_UINT32 uiCallID);
	CIMDlg* GetIMDlgByConfID(TUP_UINT32 uiConflID);
	CConfDlg* GetConfDlgByConfID(TUP_UINT32 uiConfID);
	CIMDlg* GetIMDlgByGroupID(const std::string& strKey);
	CGroupInviteDlg* GetGroupNotifyDlgByID(const std::string& strGroupID);

	CIMDlg* CreateIMDlgByAccount(const std::string& strAccount);
	CIMDlg* CreateIMDlgByGroupID(const std::string& strKey);
	CIMDlg* CreateIMDlgByCallID(TUP_UINT32 uiCallID);
	CConfDlg* CreateConfDlgByConfID(TUP_UINT32 uiConfID);
	CGroupInviteDlg* CreateGroupNotifyDlgByID(const std::string& strGroupID);

	void DeleteIMDlgByIMDlg(CIMDlg* pIMDlg);
	void DeleteConfDlgByConfDlg(CConfDlg* pConfDlg);	
	void DelGroupNotifyDlgByDlg(CGroupInviteDlg* pGroupNotifyDlg);
	
	void DeleteAllConfDlg();
	void DeleteAllIMDlg();
	void DelAllGroupNotifyDlg();

	int GetConfVectorSize(){return m_vecConfDlg.size();};
	int GetConfCallNUmber();
	int GetImDlgCallNumber();
};


