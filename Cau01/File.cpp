#include"File.h"
list<string> Files::ReadFile(string FileName)
{
	list<string> lines;
	string line = "";
	fstream f;
	if (f.is_open()) {
		f.close();
	}
	f.open(FileName);
	if (f.is_open()) {
		cout << "Ket Noi Thanh Cong" << endl;
		do {
			getline(f, line);
			lines.push_back(line);
		} while (!f.eof());
	}
	else {
		cout << "Ket Noi that bai" << endl;
	}
	f.close();
	return lines;
}

void Files::WriteFile(string FileName, list<string> data)
{
	fstream f;
	if (f.is_open()) {
		f.close();
	}
	f.open(FileName, fstream::app);
	if (f.is_open()) {
		cout << " Mo Thanh Cong" << endl;
		for (list<string>::iterator i = data.begin();i != data.end();++i) {
			f << *i;
		}
	}
	else {
		cout << "Mo that bai" << endl;
	}
	f.close();
}

list<string> Files::split(string data, char ch)
{
	list<string> features;
	string fea = "";
	stringstream line;
	if (data != "") {
		line << data;
		while (getline(line, fea, ch)) {
			features.push_back(fea);
		}
	}
	return features;
}



Mail::Mail()
{
}

Mail::Mail(string id, string pass)
{
	this->ID = id;
	this->Pass = pass;
}

void Mail::ganIDVaPass(string id, string pass)
{
	this->ID = id;
	this->Pass = pass;
}


int Mail::DanhSachMail()
{
	cout << "LIST Mail" << endl;
	cout << "1.Gmail" << endl;
	cout << "2.Yahoo" << endl;
	return 2;
}

string Mail::LuaChonMail(int n)
{
	int x;
	do {
		//system("cls");
		cout << "lua chon Tai Khoang Mail: ";
		cin >> x;
		if (x<0 || x>n) {
			cout << "Loi!!";

		}
		else {
			if (x == 1)return "Gmail";
		}
	} while (x<0 || x>n);
	return "";
}


Mail::~Mail()
{
}

Gmail::Gmail()
{
}

Gmail::Gmail(string id, string pass):Mail(id,pass)
{
}

string Gmail::toStringMail()
{
	stringstream ss;
	ss << "Gmail|" << this->ID << "|" << this->Pass << endl;
	return ss.str();
}



bool Gmail::KiemTraMail(string id, string pass)
{
	list<string>feature;
	list<string>AccountMail;
	AccountMail = Files::ReadFile(this->api);
	for (list<string>::iterator i = AccountMail.begin();i != AccountMail.end();++i) {
		
			feature = Files::split(*i,'|');
			list<string>::iterator i0 = next(feature.begin(), 0);
			list<string>::iterator i1 = next(feature.begin(), 1);
			if (*i0 == id && *i1 == pass) {
				return true;
			
		}
	}
	return false;
}

AppUser::AppUser()
{
}

AppUser::AppUser(string name)
{
	UserName = name;
}

string AppUser::toStringFileName()
{
	stringstream ss;
	ss << "User" << this->UserName << ".txt";
	return ss.str();
}

list<string> AppUser::DanhSachMail()
{
	list<string>DanhSachMail;
	for (list<Mail*>::iterator i = this->DanhSach.begin();i != this->DanhSach.end();++i) {
		Mail* Temp = *i;
		string line=Temp->toStringMail();
		DanhSachMail.push_back(line);
	}
	return DanhSachMail;
}

void AppUser::LuuUser()
{
	string FileName = this->toStringFileName();
	Files::WriteFile(FileName, this->DanhSachMail());

}

void AppUser::TaiUser()
{
	cout << "nhap user name:";
	cin >> this->UserName;
	string FileName = this->toStringFileName();
	list<string>feature;
	list<string>DanhSachMail=Files::ReadFile(FileName);
	for (list<string>::iterator i = DanhSachMail.begin();i != DanhSachMail.end();++i) {
		feature = Files::split(*i, '|');
		list<string>::iterator i0 = next(feature.begin(), 0);
		list<string>::iterator i1 = next(feature.begin(), 1);
		list<string>::iterator i2 = next(feature.begin(), 2);
		Mail* mail;
		mail = CreatMail::TaoMail(*i0);
		if (mail->KiemTraMail(*i1, *i2) == true) {
			mail->ganIDVaPass(*i1, *i2);
			this->DanhSach.push_back(mail);
		}
		else {
			cout << "ACCOUNT NOT EXIST !!!" << endl;
		}
	}
}

AppUser::~AppUser()
{
}

void AppUser::AddMail()
{
	string id = "";
	string pass = "";
	Mail* mail;
	cout << "LINK MAIL" << endl;
	mail = CreatMail::TaoMail(Mail::LuaChonMail(Mail::DanhSachMail()));
	cout << "input id: ";
	cin >> id;
	cout << "input pass: ";
	cin >> pass;
	if(mail->KiemTraMail(id, pass) == true) {
		mail->ganIDVaPass(id, pass);
		this->DanhSach.push_back(mail);
	}
	else {
		cout << "ACCOUNT NOT EXIST !!!" << endl;
	}
}

Mail* CreatMail::TaoMail(string MailName)
{
	Mail* mail=NULL;
	if (MailName == "Gmail") {
		mail = new Gmail();
	}
	if (MailName == "Yahoo") {
		mail = new Yahoo();
	}
	return mail;
}

Yahoo::Yahoo()
{
}

Yahoo::Yahoo(string id, string pass):Mail(id,pass)
{
}

string Yahoo::toStringMail()
{
	stringstream ss;
	ss << "Yahoo|" << this->ID << "|" << this->Pass << endl;
	return ss.str();
}

bool Yahoo::KiemTraMail(string id, string pass)
{
	return false;
}
