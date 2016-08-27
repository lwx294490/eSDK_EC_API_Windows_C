#pragma once
#include <string>

using namespace std;

class CTools
{
private:
	CTools(void);
	~CTools(void);
public:
	static CString UTF2UNICODE(const std::string& str);
	static std::string UNICODE2UTF(const CString& cstr);
	static void CString2Char(const CString &str,char* ch,unsigned int lenth);
	static CString getCurrentPath();
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);
	//static std::string CTools::GetLocalIPAddress();
	static bool GetBestHostip(std::string& ip, const std::string& serverip);
};

