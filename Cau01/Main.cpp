#include"File.h"
int main() {
	AppUser* User;
	string name;
	cout << "nhap ten user:";
	cin >> name;
	User = new AppUser(name);
	User->AddMail();
	//ddd

}