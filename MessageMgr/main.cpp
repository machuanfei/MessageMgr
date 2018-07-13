// main.cpp
#include <iostream>
#include "MessageManager.h"

// 在这里进行测试
// 首先声明 大前提是接收过来的消息已经将包头 和包体解析开了
// 我这里就自己定义一个包头 正常应该是其他端发过来嘚

MessageHeader head;

MessageManager msg;

// 步骤二编写回调函数
void Test_Function(const void* data, size_t len)
{
	// 此处随便解析一下， 但是正规项目中需要自己严格处理
	int a = *((int*)data);
	std::cout << __FUNCTION__ << std::endl;
	std::cout << a << std::endl;
}

void Test_Function2(const void* data, size_t len)
{
	// 此处随便解析一下， 但是正规项目中需要自己严格处理
	int a = *((int*)data);
	std::cout << __FUNCTION__ << std::endl;
	std::cout << a << std::endl;
}

int main()
{
	// 你可以修改1或者2 来决定调用 Test_Function  还是 Test_Function2
	head.msgId = 2;
	// 暂时无用
	head.msgKey = 1001;

	// 包体 （包体我没做具体处理）
	int a = 10;

	// 步骤1 注册消息码
	msg.regMessageHandler(1, new MH_Function(&::Test_Function));
	msg.regMessageHandler(2, new MH_Function(&::Test_Function2));

	// 步骤3 调用函数， 一般是接收到消息统一在一个地方执行
	msg.onMessage(head, &a, sizeof(a));
	system("pause");
	return 0;
}