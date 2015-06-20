//
//
//TempInquireResultsList.h
//���ļ������˴����ݴ������������ض���
//
//
#include <iostream>
#include <iomanip>
#include <string>
#include "Express.h"
using namespace std;
#ifndef TempInquireResultsLIST_H
#define TempInquireResultsLIST_H

static int countExpress = 0;																//����ͳ�ƿ��������

//�����ݴ�����ɸѡ�����������classʵ��
class TempInquireResults
{
	
public:
	string expressNumber;
	string expressAddress;
	string receiverName;
	string senderName;
	string receiverPhone;
	string senderPhone;
	string status;
	string courier;
	TempInquireResults *next;

	//������������ز���
	TempInquireResults(){};
	TempInquireResults & operator = (Express &);											//���ظ�ֵ��ʹ��ͨ��һ��Express����󹹽�TempInquireResults�����Ϊ����
	static void addFront(TempInquireResults *& head, TempInquireResults *& node);			//�ڱ�ͷ�����½ڵ�
	static void deleteNode(TempInquireResults *& head, string keyWord);						//�ж�������ɾ���ڵ�
	static void showList(TempInquireResults * head);										//�������������
	static void showUnSentExpress(TempInquireResults * head);								//��ӡҵ��Աδ�ʹ�Ŀ��

};


//��������
TempInquireResults & TempInquireResults :: operator = (Express & ex)
{
	
	expressNumber = ex.expressNumber;
	expressAddress = ex.address;
	receiverName = ex.receiverName;
	senderName = ex.senderName;
	receiverPhone = ex.receiverPhone;
	senderPhone = ex.senderPhone;
	status = ex.status;
	courier = ex.courier;
	next = NULL;

	return *this;

}

void TempInquireResults :: addFront(TempInquireResults *& head, TempInquireResults *& node)
{

	node->next = head;
	head = node;

}

void TempInquireResults :: deleteNode(TempInquireResults *& head, string keyWord)			//��һ�Ƚ�keyWord�������ĸ�����Ϣ��������ƥ����ɾ���ÿ�����ڵ㣩
{

	//��ɾ�ڵ���ͷ�ڵ�
	while ((head->expressNumber != keyWord) && (head->expressAddress != keyWord) && (head->receiverName != keyWord) && (head->senderName != keyWord) && (head->receiverPhone != keyWord) && (head->senderPhone != keyWord) && (head->status != keyWord) && (head->courier != keyWord)){												//��ɾ�ڵ���ͷ�ڵ�
		TempInquireResults *tempNode;
		tempNode = head;
		if (head->next){
			head = head->next;
			countExpress--;
		}else{
			countExpress--;
			break;
		}
		delete tempNode;
		tempNode = NULL;
	}

	//��ɾ�ڵ��Ǻ����ڵ㣬���Ҳ�ɾ���ڵ�
	for (TempInquireResults *tempListNode = head; tempListNode->next;){
		if ((tempListNode->next->expressNumber != keyWord) && (tempListNode->next->expressAddress != keyWord) && (tempListNode->next->receiverName != keyWord) && (tempListNode->next->senderName != keyWord) && (tempListNode->next->receiverPhone != keyWord) && (tempListNode->next->senderPhone != keyWord) && (tempListNode->next->status != keyWord) && (tempListNode->next->courier != keyWord)){
			TempInquireResults *tempNode = NULL;
			tempNode = tempListNode->next;
			if (tempNode->next){												
				tempListNode->next = tempNode->next;		
			}else{																			//��ɾ�ڵ��Ѿ������һ���ڵ�
				tempListNode->next = NULL;
			}
			delete tempNode;
			tempNode = NULL;
			countExpress--;
		}else if(tempListNode->next){
			tempListNode = tempListNode->next;
		}
	}

	//��ʣһ���ڵ��Ҹýڵ���Ҫ��ɾ��
	if ((!head->next) && (head->expressNumber != keyWord) && (head->expressAddress != keyWord) && (head->receiverName != keyWord) && (head->senderName != keyWord) && (head->receiverPhone != keyWord) && (head->senderPhone != keyWord) && (head->status != keyWord) && (head->courier != keyWord)){															//headΪ���һ���ڵ�������ؼ��ʲ�ƥ��
		head = NULL;
	}

}

void TempInquireResults :: showList(TempInquireResults * head)
{

	TempInquireResults *tempHead = head;

	//��ӡ��ͷ
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << std::left << setw(12) << "�˵���" << setw(10) << "�ʼĵ�ַ" << setw(10) << "�ռ�������" << setw(10) << "�ļ�������" << setw(10) << "�ռ��˵绰" << setw(10) << "�ļ��˵绰" << setw(8) << "���״̬" << setw(10) << "���������" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	//��ӡ��񼰿����Ϣ
	while (tempHead){
		cout << std::left << setw(12) << tempHead->expressNumber << setw(10) << tempHead->expressAddress << setw(10) << tempHead->receiverName << setw(10) << tempHead->senderName << setw(10) << tempHead->receiverPhone << setw(10) << tempHead->senderPhone << setw(8) << tempHead->status << setw(10) << tempHead->courier << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		tempHead = tempHead->next;
	}

	cout << "\n";

}

void TempInquireResults::showUnSentExpress(TempInquireResults * head)
{

	TempInquireResults *tempHead = head;

	//��ӡ��ͷ
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << std::left << setw(12) << "�˵���" << setw(10) << "�ʼĵ�ַ" << setw(10) << "�ռ�������" << setw(10) << "�ļ�������" << setw(10) << "�ռ��˵绰" << setw(10) << "�ļ��˵绰" << setw(8) << "���״̬" << setw(10) << "���������" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	//��ӡ��񼰿����Ϣ
	while (tempHead){
		if (tempHead->status == "unsent"){
			cout << std::left << setw(12) << tempHead->expressNumber << setw(10) << tempHead->expressAddress << setw(10) << tempHead->receiverName << setw(10) << tempHead->senderName << setw(10) << tempHead->receiverPhone << setw(10) << tempHead->senderPhone << setw(8) << tempHead->status << setw(10) << tempHead->courier << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
		}
		tempHead = tempHead->next;
	}

}

#endif