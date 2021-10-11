#ifndef _FILE_H
#define _FILE_H
#include<iostream>
#include<fstream>
#include<sstream>
#include <list>
using namespace std;
class Files {
public:
	static list<string> ReadFile(string FileName);
	static void WriteFile(string FileName, list<string> data);
	static list<string> split(string data, char ch);
};

//
class Mail {
protected:
	string ID="";
	string Pass="";
public:
	Mail();
	Mail(string id, string pass );
	void ganIDVaPass(string id, string pass);
	static int DanhSachMail();
	static string LuaChonMail(int n);
	virtual bool KiemTraMail(string id, string pass) = 0;
	virtual string toStringMail() = 0;
	virtual~Mail();

};

class Gmail:public Mail{
protected:
	string api = "Gmail.txt";
public:
	Gmail();
	Gmail(string id, string pass);
	virtual string toStringMail();
	virtual bool KiemTraMail(string id, string pass);
};


//
class CreatMail {
public:
	static Mail* TaoMail(string MailName);
};
//
class AppUser {
protected:
	string UserName = "";
	list<Mail*>DanhSach;
public:
	AppUser();
	AppUser(string name);
	string toStringFileName();
	list<string>DanhSachMail();
	void LuuUser();
	virtual~AppUser();
	void AddMail();
};


#endif
