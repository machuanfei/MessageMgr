// main.cpp
#include <iostream>
#include "MessageManager.h"

// ��������в���
// �������� ��ǰ���ǽ��չ�������Ϣ�Ѿ�����ͷ �Ͱ����������
// ��������Լ�����һ����ͷ ����Ӧ���������˷������N

MessageHeader head;

MessageManager msg;

// �������д�ص�����
void Test_Function(const void* data, size_t len)
{
	// �˴�������һ�£� ����������Ŀ����Ҫ�Լ��ϸ���
	int a = *((int*)data);
	std::cout << __FUNCTION__ << std::endl;
	std::cout << a << std::endl;
}

void Test_Function2(const void* data, size_t len)
{
	// �˴�������һ�£� ����������Ŀ����Ҫ�Լ��ϸ���
	int a = *((int*)data);
	std::cout << __FUNCTION__ << std::endl;
	std::cout << a << std::endl;
}

int main()
{
	// ������޸�1����2 ���������� Test_Function  ���� Test_Function2
	head.msgId = 2;
	// ��ʱ����
	head.msgKey = 1001;

	// ���� ��������û�����崦��
	int a = 10;

	// ����1 ע����Ϣ��
	msg.regMessageHandler(1, new MH_Function(&::Test_Function));
	msg.regMessageHandler(2, new MH_Function(&::Test_Function2));

	// ����3 ���ú����� һ���ǽ��յ���Ϣͳһ��һ���ط�ִ��
	msg.onMessage(head, &a, sizeof(a));
	system("pause");
	return 0;
}