#pragma once
#include "Logger.h"

void method1();
void method2();
void method3();

class TestException
{
public:
	TestException();
	~TestException();

private:
	Logger m_logger1;
	Logger m_logger2;
};
