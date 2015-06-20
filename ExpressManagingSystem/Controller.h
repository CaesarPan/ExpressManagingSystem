//
//
//Controller.h
//�Դ����û������ĺ�̨������Controller�ඨ��
//
//
#include <iostream>
#include <string>
#include "User.h"
#include "Manager.h"
#include "Courier.h"
#include "Express.h"
using namespace std;

#ifndef CONTROLLER_H
#define CONTROLLER_H

//����ȫ�ֱ���currentUserName
static string currentUserName;

class Controller
{
public:
	bool confirmPassWord(string passWord1, string passWord2);										//������ע�����û�ʱȷ�����룬��������һ���򷵻�1����һ���򷵻�0��
	bool ifRegisterSucceeds(string userName, string passWord1, string passWord2);					//�����ж����û�ע���Ƿ�ɹ����ɹ�����0�����ɹ�����1��
	int login(string userName, string passWord);													//�û���¼ʱ�жϵ�¼�Ƿ�ɹ������ɹ��򷵻�1�����ɹ����û������ڻ���������򷵻�0�������쳣���󷵻�-1
	void logOut();																					//�����û��ǳ�
};

bool Controller::confirmPassWord(string passWord1, string passWord2)
{

	if (passWord1 == passWord2){
		return 1;
	}else{
		return 0;
	}

}

bool Controller::ifRegisterSucceeds(string userName, string passWord1, string passWord2)
{
	
	bool unJudgingResult, pwJudingResult;															//���ڴ����û����������Ƿ����Ҫ��Ĳ������ͱ���

	pwJudingResult = confirmPassWord(passWord1, passWord2);
	
	if (!pwJudingResult){
		cout << "�������벻һ��" << endl;
		return 1;
	}

	User newUser(userName, passWord1, "2");

	unJudgingResult = newUser.userExists();

	if (unJudgingResult){
		return 1;
	}

	return 0;

}

int Controller :: login(string userName, string passWord)
{

	User currentUser(userName, passWord);
	
	if (!currentUser.login()){
		system("cls");																				//����
		if (currentUser.plOfCurrentUser() == "1"){
			cout << "������ӭ������������ѡ��\n1������¿��\n2���鿴���п��\n3���������п��\n4���鿴�û���Ϣ\n5��ɾ���û�\n6���˳���¼\n������ѡ��ǰ��Ӧ����" << endl;
			Manager currentManager = currentUser;
			currentUserName = currentManager.unOfCurrentUser();

			string choice;

			MANAGER_CHOOSE:
			cin >> choice;
			cout << "\n";

			if (choice == "1"){
				cout << "����������Ҫ��ӿ�����˵��ţ�����Ϊ10λ���֣����ļ���ַ���ռ����������ļ����������ռ�����ϵ�绰���ļ�����ϵ�绰���м��Իس��ָ�" << endl;
				string expressNumber, address, receiverName, senderName, receiverPhone, senderPhone;
				cin >> expressNumber >> address >> receiverName >> senderName >> receiverPhone >> senderPhone;

				Express newExpress(expressNumber, address, receiverName, senderName, receiverPhone, senderPhone);		//�����¿��
				currentManager.addAnExpress(newExpress);

				cout << "\n";
				cout << "�����ѡ��\n1������¿��\n2���鿴���п��\n3���������п��\n4���鿴�û���Ϣ\n5��ɾ���û�\n6���˳���¼\n������ѡ��ǰ��Ӧ����" << endl;
				goto MANAGER_CHOOSE;
			}else if (choice == "2"){
				currentManager.managerListExpress();

				cout << "\n";
				cout << "�����ѡ��\n1������¿��\n2���鿴���п��\n3���������п��\n4���鿴�û���Ϣ\n5��ɾ���û�\n6���˳���¼\n������ѡ��ǰ��Ӧ����" << endl;
				goto MANAGER_CHOOSE;
			}else if (choice == "3"){
				cout << "������Ҫ���������˵��źͷ������ҵ��Ա������" << endl;
				string expressNumber, courierName;
				cin >> expressNumber >> courierName;
				currentManager.assignExpress(expressNumber, courierName);

				cout << "\n";
				cout << "�����ѡ��\n1������¿��\n2���鿴���п��\n3���������п��\n4���鿴�û���Ϣ\n5��ɾ���û�\n6���˳���¼\n������ѡ��ǰ��Ӧ����" << endl;
				goto MANAGER_CHOOSE;
			}else if (choice == "4"){
				currentManager.showUsers();

				cout << "\n";
				cout << "�����ѡ��\n1������¿��\n2���鿴���п��\n3���������п��\n4���鿴�û���Ϣ\n5��ɾ���û�\n6���˳���¼\n������ѡ��ǰ��Ӧ����" << endl;
				goto MANAGER_CHOOSE;
			}else if (choice == "5"){
				cout << "������Ҫɾ�����û����û�����" << endl;
				string userName;
				cin >> userName;
				currentManager.deleteAUser(userName);

				cout << "\n";
				cout << "�����ѡ��\n1������¿��\n2���鿴���п��\n3���������п��\n4���鿴�û���Ϣ\n5��ɾ���û�\n6���˳���¼\n������ѡ��ǰ��Ӧ����" << endl;
				goto MANAGER_CHOOSE;
			}else if (choice == "6"){
				cout << "\n";
				logOut();
				system("cls");
			}else{
				cout << "\n";
				cout << "�޴�ѡ�����������" << endl;
				goto MANAGER_CHOOSE;
			}
		}else{
			Courier currentCourier = currentUser;
			cout << "ҵ��Ա" << currentCourier.unOfCurrentUser() << ",���ã�����ѡ��\n1���鿴�Լ������͵Ŀ��\n2��������ʹ���\n3���˳���¼\n������ѡ��ǰ��Ӧ������" << endl;

			string choice;

			COURIER_CHOOSE:
			cin >> choice;
			cout << "\n" << endl;

			if (choice == "1"){
				currentCourier.courierListExpress(currentCourier.unOfCurrentUser());
				
				cout << "\n";
				cout << "�����ѡ��\n1���鿴�Լ������͵Ŀ��\n2��������ʹ���\n3���˳���¼\n������ѡ��ǰ��Ӧ������" << endl;
				goto COURIER_CHOOSE;
			}else if (choice == "2"){
				cout << "����������Ҫ���Ϊ���ʹ�Ŀ���˵���" << endl;
				string expressNumber;
				cin >> expressNumber;
				currentCourier.haveSentExpress(expressNumber);
				
				cout << "\n";
				cout << "�����ѡ��\n1���鿴�Լ������͵Ŀ��\n2��������ʹ���\n3���˳���¼\n������ѡ��ǰ��Ӧ������" << endl;
				goto COURIER_CHOOSE;
			}else if (choice == "3"){
				cout << "\n";
				logOut();
				system("cls");
			}else{
				cout << "\n";
				cout << "�޴�ѡ�����������" << endl;
				goto COURIER_CHOOSE;
			}
		}
		return 0;
	}

	return 1;

}

void Controller :: logOut()
{

	currentUserName = "";

}

#endif