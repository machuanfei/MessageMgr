// MH_Base.h
#ifndef __MH_Base_h__
#define __MH_Base_h__

// 消息处理者基类
class MH_Base
{
public:
	virtual ~MH_Base() {};
	virtual void operator()(const void* data, size_t len) = 0;
};

/// 全局或者静态函数
class MH_Function : public MH_Base
{
public:
	typedef void (Function1)(const void* data, size_t len);
public:
	MH_Function(Function1* func) : _func1(func) {}
	virtual void operator()( const void* data, size_t len)
	{
		_func1( data, len);
	}

private:
	union
	{
		Function1* _func1;
	};
};

#endif