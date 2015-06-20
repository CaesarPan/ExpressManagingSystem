//
//
//Express.h
//�Կ����Ķ���
//
//
#include <fstream>
#include <string>                                                                                                                                                                                                                                                                                                                                                            +
using namespace std;

#ifndef EXPRESS_H
#define EXPRESS_H

class Express
{
public:	
	Express(){};
	Express(string num) :expressNumber(num), address(""), receiverName(""), senderName(""), receiverPhone(""), senderPhone(""), status(""), courier(""){};
	Express(string, string, string, string, string, string, string = "unsent", string = "none");
	string numberOfCurrentExpress(){ return expressNumber; }	
	string addressOfCurrentExpress(){ return address; }
	string receiverOfCurrentExpress(){ return receiverName; }
	string senderOfCurrentExpress(){ return senderName; }
	string receiverPhoneOfCurrentExpress(){ return receiverPhone; }
	string senderPhoneOfCurrentExpress(){ return senderPhone; }
	string statusOfCurrentExpress(){ return status; }
	string courierOfCurrentExpress(){ return courier; }
	int expressExists();															//����������Ƿ�ȷʵ���ڣ����ڷ���1�������ڷ���0
private:
	string expressNumber;
	string address;
	string receiverName;
	string senderName;
	string receiverPhone;
	string senderPhone;
	string status;
	string courier;

	friend ifstream & operator >> (ifstream &, Express &);							//��������ȡ�����
	friend ofstream & operator << (ofstream &, Express &);							//���������������
	friend class TempInquireResults;												//����TempInquireResults��ΪExpress�����Ԫ�࣬ʹ���ڶ��幹�캯��ʱ�ɷ���Express��������ݳ�Ա

};

Express :: Express(string num, string add, string rN, string sN, string rP, string sP, string stat, string cour) :expressNumber(num), address(add), receiverName(rN), senderName(sN), receiverPhone(rP), senderPhone(sP), status(stat), courier(cour){};

ifstream & operator >> (ifstream & get, Express & express)
{
	
	get >> express.expressNumber >> express.address >> express.receiverName >> express.senderName >> express.receiverPhone >> express.senderPhone>>express.status>>express.courier;
	return get;

}

ofstream & operator << (ofstream & write, Express & express)
{
	
	write << express.expressNumber << " " << express.address << " " << express.receiverName << " " << express.senderName << " " << express.receiverPhone << " " << express.senderPhone << " " << express.status<< " " << express.courier;
	return write;

}

int Express::expressExists()
{

	ifstream listExpress("../SupportingFiles/ExpressInfo.txt", ios::in);

	if (!listExpress){
		cerr << "�ļ��޷���" << endl;
		return 1;
	}

	int countExpressExists = 0;
	Express tempExpress;

	while (listExpress >> tempExpress){
		if (tempExpress.numberOfCurrentExpress() == expressNumber){
			countExpressExists++;
			return 1;
		}
	}

	if (!countExpressExists){
		return 0;
	}

	listExpress.close();

}

#endif