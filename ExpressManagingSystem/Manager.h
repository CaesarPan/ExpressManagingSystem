//
//
//Manager.h
//��User��������Manager��Ķ���
//
//
#include <fstream>
#include <vector>
#include <string>
#include "User.h"
#include "Express.h"
#include "TempInquireResultsList.h"
using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

class Manager : public User
{

public:
	Manager(User user) { userName = user.unOfCurrentUser(); passWord = user.pwOfCurrentUser(); permissionLevel = "1"; hasBeenDeleted = user.dsOfCurrentUser(); }
	int deleteAUser(string);														//ɾ��ĳָ���û����޸�ɾ��״̬��־�֣�
	int addAnExpress(Express);														//��ҵ����������Ϣ�б�������µĴ��Ϳ�ݣ����״̬�Զ���Ϊδ�ʹ�ɼ�����Ϊ�ޡ��ɹ�����0�����򷵻�1��
	int managerListExpress();														//������鿴ȫ����ݣ������ڲ���ʵ��������ѯ��ִ����������0�����򷵻�1��
	int assignExpress(string, string);												//��ҵ����δ����Ŀ�ݷ�������Ա��ִ����������0�����򷵻�1��
	int showUsers();																//���ھ���鿴�û���Ϣ���ɹ�����0�����ɹ�����1

};

int Manager::deleteAUser(string userName)
{
	
	if (userName == "manager"){
		cout << "����Ȩ�������˻�" << endl;
		return 1;
	}

	ifstream readUser("../SupportingFiles/UserInfo.txt", ios::in);
	vector<string> userVector;

	if (!readUser){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	//��鱻ɾ���û��Ƿ����
	User checkedUser(userName);
	if (!checkedUser.userExists()){
		cout << "���û���δע��" << endl;
		return 1;
	}

	User tempUser;

	while (readUser >> tempUser){
		if (userName == tempUser.unOfCurrentUser()){								//���û�Ϊ��Ҫ��ɾ�����û�
			userVector.push_back(tempUser.unOfCurrentUser()); userVector.push_back(" ");
			userVector.push_back(tempUser.pwOfCurrentUser()); userVector.push_back(" ");
			userVector.push_back(tempUser.plOfCurrentUser()); userVector.push_back(" ");
			userVector.push_back("true"); userVector.push_back("\n");
		}else{																		//���û�����Ҫ��ɾ��
			userVector.push_back(tempUser.unOfCurrentUser()); userVector.push_back(" ");
			userVector.push_back(tempUser.pwOfCurrentUser()); userVector.push_back(" ");
			userVector.push_back(tempUser.plOfCurrentUser()); userVector.push_back(" ");
			userVector.push_back(tempUser.dsOfCurrentUser()); userVector.push_back("\n");
		}
	}

	readUser.close();

	ofstream putEmpty("../SupportingFiles/UserInfo.txt", ios::out);
	
	if (!putEmpty){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	putEmpty << "";

	putEmpty.close();

	ofstream inputAgain("../SupportingFiles/UserInfo.txt", ios::app);
	
	if (!inputAgain){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	for (int i = 0; i < userVector.size(); i++){
		inputAgain << userVector[i];
	}

	inputAgain.close();

	cout << "���û��ѱ��ɹ�ɾ����" << endl;

	return 0;

}

int Manager :: addAnExpress(Express express)
{
	
	ofstream addExpress("../SupportingFiles/ExpressInfo.txt", ios::app);

	if (!addExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	//��鵱ǰ����Ƿ��ѱ�������б�
	Express checkedExpress(express.numberOfCurrentExpress());
	if (checkedExpress.expressExists()){
		cout << "�ÿ���ѱ����,�����ظ����" << endl;
		return 1;
	}

	//�ж��˵����Ƿ���ʮλ��
	int bitCount = 1;																//��¼�˵��ŵ�λ��
	int tempNumber = atoi(express.numberOfCurrentExpress().c_str());

	while (tempNumber / 10){
		tempNumber /= 10;
		bitCount++;
	}

	if (bitCount == 10){
		addExpress << express << "\n";
	}else{
		cout << "�˵��ű���Ϊ10λ����" << endl;
		return 1;
	}

	addExpress.close();
	return 0;

}

int Manager::managerListExpress()													//������鿴ȫ����ݣ������ڲ���ʵ��������ѯ��ִ����������0�����򷵻�1��
{

	ifstream listExpress("../SupportingFiles/ExpressInfo.txt", ios::in);

	if (!listExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	Express tempExpress;

	//��ȥ������
	char title[300];
	listExpress.getline(title, 300);

	string expressNumber, expressAddress, receiverName, senderName, receiverPhone, senderPhone, status, courier;
	
	//�Ƚ�ȫ�������Ϣ��������
	TempInquireResults *head = NULL;
	while(listExpress >> expressNumber >> expressAddress >> receiverName >> senderName >> receiverPhone >> senderPhone >> status >> courier){
		TempInquireResults *newNode = new TempInquireResults;
		newNode->expressNumber = expressNumber; newNode->expressAddress = expressAddress; newNode->receiverName = receiverName; newNode->senderName = senderName; newNode->receiverPhone = receiverPhone; newNode->senderPhone = senderPhone; newNode->status = status; newNode->courier = courier;
		TempInquireResults :: addFront(head, newNode);
		countExpress++;
	}

	//�Ƿ����������ѯ
	string choice;
	cout << "�Ƿ���Ҫ����������ѯ������Y�����ǣ�N�����" << endl;
	cin >> choice;
	cout << "\n";

	if ((choice == "N") || (choice == "n")){										//������������ѯ��ȡ��ȫ�������Ϣ
		TempInquireResults :: showList(head);
		cout << "\nȫ���������Ϊ��" << countExpress << "��" << endl;
	}else if ((choice == "Y") || (choice == "y")){									//����������ѯ
		string keyWord;																//������ѯ�ؼ���
		do{
			cout << "������������ѯ�Ĺؼ��֣��������˵��š��ļ���ַ���ռ����������ļ����������ռ�����ϵ�绰���ļ�����ϵ�绰�����״̬������ˣ�" << endl;
			cin >> keyWord;
			cout << "\n";

			TempInquireResults :: deleteNode(head, keyWord);						//��һ�Ƚ�keyWord�������ĸ�����Ϣ��������ƥ����ɾ���ÿ�����ڵ㣩

			if (!countExpress){ 
				cout << "û�з��������Ŀ��" << endl;
				return 1;
			}

			cout << "��ѯ������£�" << endl;
			TempInquireResults :: showList(head);
			cout << "���������Ŀ������Ϊ��" << countExpress << "��" << endl;

			cout << "�Ƿ�Ҫ������С��Χ��ѯ������Y�����ǣ�N�����" << endl;
			cin >> choice;
			cout << "\n";
		} while ((choice == "Y") || (choice == "y"));
	}

	countExpress = 0;																//���ü�����
	listExpress.close();
	return 0;

}

int Manager :: assignExpress(string expressNumber, string courierName)
{
	
	ifstream readExpress("../SupportingFiles/ExpressInfo.txt", ios::in);
	vector<string> expressVector;

	if (!readExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	Express tempExpress;
	
	//������Ŀ��Ա������
	User tempUser(courierName);
	if (!tempUser.userExists()){
		cout << "�ÿ��Ա��δע��" << endl;
		return 1;
	}

	//�ÿ��Ա�ѱ�ɾ��
	if (tempUser.dsOfCurrentUser() == "true"){
		cout << "�ÿ��Ա�ѱ�ɾ��" << endl;
		return 1;
	}

	//�ÿ����δ�����
	Express checkedExpress(expressNumber);
	if (!checkedExpress.expressExists()){
		cout << "�ÿ����δ��������б�" << endl;
		return 1;
	}

	while (readExpress >> tempExpress){
		if (expressNumber == tempExpress.numberOfCurrentExpress()){					//�ö���Ϊ��Ҫ������Ķ���
			//�ظ������ͬһ���Ա
			if (courierName == tempExpress.courierOfCurrentExpress()){
				cout << "�ÿ���ѱ�������ÿ��Ա�������ظ����䣡" << endl;
				return 1;
			}
			//���ʼ��ѱ�������������Ա����δ���ʹ�
			else if ((tempExpress.courierOfCurrentExpress() != "none") && (tempExpress.statusOfCurrentExpress() == "unsent")){
				cout << "�ÿ���ѱ���������Ա��" << tempExpress.courierOfCurrentExpress() << "������δ���ʹ�Ƿ�ȷ��Ҫ��������Ա��(Y/N)" << endl;
				string choice;
				cin >> choice;
				if ((choice == "Y") || (choice == "y")){
					expressVector.push_back(tempExpress.numberOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.addressOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.receiverOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.senderOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.receiverPhoneOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.senderPhoneOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.statusOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(courierName); expressVector.push_back("\n");
				}else if((choice == "N") || (choice == "n")){
					return 1;
				}
			}else if ((tempExpress.courierOfCurrentExpress() != "none") && (tempExpress.statusOfCurrentExpress() == "sent")){
				cout << "�ÿ�������������Ա�ʹ�" << endl;
				return 1;
			}else{
				expressVector.push_back(tempExpress.numberOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(tempExpress.addressOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(tempExpress.receiverOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(tempExpress.senderOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(tempExpress.receiverPhoneOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(tempExpress.senderPhoneOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(tempExpress.statusOfCurrentExpress()); expressVector.push_back(" ");
				expressVector.push_back(courierName); expressVector.push_back("\n");
			}
		}else{																		//�ö�������Ҫ������
			expressVector.push_back(tempExpress.numberOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.addressOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.receiverOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.senderOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.receiverPhoneOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.senderPhoneOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.statusOfCurrentExpress()); expressVector.push_back(" ");
			expressVector.push_back(tempExpress.courierOfCurrentExpress()); expressVector.push_back("\n");
		}
	}

	readExpress.close();

	ofstream putEmpty("../SupportingFiles/ExpressInfo.txt", ios::out);

	if (!putEmpty){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	putEmpty << "";

	putEmpty.close();

	ofstream writeExpress("../SupportingFiles/ExpressInfo.txt", ios::app);

	if (!writeExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	for (int i = 0; i < expressVector.size(); i++){
		writeExpress << expressVector[i];
	}

	writeExpress.close();

	cout << "�ÿ���ѱ��ɹ����䣡" << endl;
	
	return 0;

}

int Manager :: showUsers()
{

	char title[300];
	string un, pw, pl;																//�û��������룬Ȩ�޼���

	ifstream inquireUser("../SupportingFiles/UserInfo.txt", ios::in);

	if (!inquireUser){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	inquireUser.getline(title, 300);

	User tempUser;

	cout << "�����û����£�\n" << endl;

	while (inquireUser >> tempUser){
		if (tempUser.dsOfCurrentUser() == "false"){
			cout << tempUser.unOfCurrentUser() << endl;
		}
	}

	inquireUser.close();

	return 0;

}

#endif