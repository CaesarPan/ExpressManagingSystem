#include "Controller.h"
using namespace std;

int main()
{

	Controller controller;												//�����������������е�controller��
	string choice;

	WELCOME_PAGE:														//��ӭҳ��
	cout << "*********************��ӭʹ����Caesar�����Ŀ�ݹ���ϵͳ***********************\n\n"
		<< "~~                         ������ѡ��ǰ��Ӧ����ţ�                          ~~\n\n"
		<< "~~                            1�����û���¼                                 ~~\n\n"
		<< "~~                            2���¿��Աע��                                 ~~\n\n";
	cin >> choice;
	system("cls");

	if (choice == "1"){
		string userName;
		string passWord;
		cout << "�����룺\n�û�����";
		cin >> userName;
		cout << "���룺";
		cin >> passWord;
		cout << '\n';

		controller.login(userName, passWord);

	}else if (choice == "2"){
		REGISTER:
		string userName;
		string passWord1;
		string passWord2;

		cout << "�����룺\n�û�����";
		cin >> userName;
		cout << "���룺";
		cin >> passWord1;
		cout << "��ȷ�����룺";
		cin >> passWord2;

		if (controller.confirmPassWord(passWord1, passWord2)){
			User registerUser(userName, passWord1);
			if (!controller.ifRegisterSucceeds(userName, passWord1, passWord2)){
				Courier registerCourier = registerUser;
				registerCourier.addACourier();
				goto WELCOME_PAGE;
				return 0;
			}else{
				cout << "���û��Ѵ��ڣ�������û���" << endl;
				goto REGISTER;
			}
		}else{
			cout << "�������벻һ�£�����������" << endl;
			goto REGISTER;
		}

	}else{
		cout << "�޴�ѡ�����������" << endl;
		goto WELCOME_PAGE;
	}

	if (currentUserName == ""){											//�˳���¼�����½��뻶ӭҳ��
		goto WELCOME_PAGE;
	}

	return 0;

}