//
//
//Courier.h
//��User��������Courier��Ķ���
//
//
#include <fstream>
#include <vector>
#include <string>
#include "User.h"
#include "Express.h"
#include "TempInquireResultsList.h"
using namespace std;

#ifndef COURIER_H
#define COURIER_H

class Courier : public User
{

public:
	Courier(User user) { userName = user.unOfCurrentUser(); passWord = user.pwOfCurrentUser(); permissionLevel = "2"; hasBeenDeleted = user.dsOfCurrentUser(); }
	int addACourier();												//���ҵ��Աע��ʱ�����ҵ��Ա
	int haveSentExpress(string expressNumber);						//��ҵ��Ա�����ʹ�Ŀ�ݽ��б�ǡ�ִ����������0�����򷵻�1��
	int courierListExpress(string courierName);						//��ҵ��Ա�鿴�Լ��Ŀ�ݣ������ڲ���ʵ��������ѯ��ִ����������0�����򷵻�1��

};

int Courier::addACourier()
{
	
	ofstream addNew("../SupportingFiles/UserInfo.txt", ios::app);

	if (!addNew){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	addNew << *this << "\n";										//���ļ�����ӵ�ǰ���ҵ��Ա

	cout << "��ϲ����ע��ɹ���" << endl;
	addNew.close();

	return 0;

}

int Courier :: haveSentExpress(string expressNumber)
{

	ifstream readExpress("../SupportingFiles/ExpressInfo.txt", ios::in);
	vector<string> expressVector;
	
	if (!readExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	Express checkedExpress(expressNumber);
	if (!checkedExpress.expressExists()){
		cout << "�ÿ����δ��������б�" << endl;
		return 1;
	}

	Express tempExpress;

	while (readExpress >> tempExpress){
		if (tempExpress.numberOfCurrentExpress() == expressNumber){		//���˵�Ϊ��Ҫ�޸�����״̬�Ķ���
			if (tempExpress.courierOfCurrentExpress() == userName){
				if (tempExpress.statusOfCurrentExpress() == "unsent"){
					expressVector.push_back(tempExpress.numberOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.addressOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.receiverOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.senderOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.receiverPhoneOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.senderPhoneOfCurrentExpress()); expressVector.push_back(" ");
					expressVector.push_back("sent"); expressVector.push_back(" ");
					expressVector.push_back(tempExpress.courierOfCurrentExpress()); expressVector.push_back("\n");
				}else if (tempExpress.statusOfCurrentExpress() == "sent"){
					cout << "�ÿ���ѱ����Ϊ�ʹ�����ظ����" << endl;
					return 1;
				}
			}else{
				cout << "����Ȩ��δ���Ÿ����Ŀ�����в���" << endl;
				return 1;
			}
		}else{														//���˵�����Ҫ���޸�
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

	cout << "�ÿ���ѱ��ɹ����Ϊ���ʹ�" << endl;

	return 0;

}

int Courier :: courierListExpress(string courierName)
{

	Express tempExpress;

	ifstream listExpress("../SupportingFiles/ExpressInfo.txt", ios::in);

	if (!listExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	//��ȥ������
	char title[300];
	listExpress.getline(title, 300);

	string expressNumber, expressAddress, receiverName, senderName, receiverPhone, senderPhone, status, courier;

	int countUnSentExpress = 0;

	//����ҵ��Ա��ȫ����ݴ�������
	TempInquireResults *head = NULL;
	while (listExpress >> expressNumber >> expressAddress >> receiverName >> senderName >> receiverPhone >> senderPhone >> status >> courier){
		if (courierName == courier){
			if (status == "unsent"){
				countUnSentExpress++;
			}
			TempInquireResults *newNode = new TempInquireResults;
			newNode->expressNumber = expressNumber; newNode->expressAddress = expressAddress; newNode->receiverName = receiverName; newNode->senderName = senderName; newNode->receiverPhone = receiverPhone; newNode->senderPhone = senderPhone; newNode->status = status; newNode->courier = courier;
			TempInquireResults::addFront(head, newNode);
			countExpress++;
		}
	}

	if (countExpress){													//�п�ݱ��������ǰ���Ա
		string choice;
		cout << "�Ƿ����������ѯ������Y�����ǣ�N�����" << endl;
		cin >> choice;
		cout << "\n";

		if ((choice == "N") || (choice == "n")){
			//��ȡ��ҵ��Ա���͵����п����Ϣ
			cout << "ҵ��Ա" << courierName << "���ã������Ƿ��������ȫ�������\n" << endl;
			TempInquireResults::showList(head);
			cout << "\nȫ���������Ϊ��" << countExpress << "��" << endl;

			//�����г��ÿ��Ա��δ�ʹ�Ŀ��
			cout << "��������δ�ʹ�Ŀ���У�" << endl;
			TempInquireResults::showUnSentExpress(head);
			cout << "\n����δ�ʹ�Ŀ������Ϊ��" << countUnSentExpress << "��" << endl;

		}
		else if ((choice == "Y") || (choice == "y")){
			string keyWord;												//������ѯ�ؼ���

			do{
				cout << "������������ѯ�Ĺؼ��֣��������˵��š��ļ���ַ���ռ����������ļ����������ռ�����ϵ�绰���ļ�����ϵ�绰�����״̬������ˣ�" << endl;
				cin >> keyWord;

				TempInquireResults::deleteNode(head, keyWord);							//��һ�Ƚ�keyWord�������ĸ�����Ϣ��������ƥ����ɾ���ÿ�����ڵ㣩

				if (!countExpress){
					cout << "û�з��������Ŀ��" << endl;
					return 1;
				}

				cout << "��ѯ������£�" << endl;
				TempInquireResults::showList(head);
				cout << "���������Ŀ������Ϊ��" << countExpress << "��" << endl;

				cout << "�Ƿ�Ҫ������С��Χ��ѯ������Y�����ǣ�N�����" << endl;
				cin >> choice;
			} while ((choice == "Y") || (choice == "y"));
		}
	}else{																		//û�п�ݱ��������ǰ���Ա
		cout << "��û�п�ݱ����������" << endl;
	}

	countExpress = 0;														//���ü�����
	listExpress.close();
	return 0;

}

#endif