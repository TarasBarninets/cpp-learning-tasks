#include <iostream>
#include <gtest/gtest.h>
#include <MyString.h>

class MyStringTest : public ::testing::Test
{
protected:
	MyString object1 = "Example";
	MyString object2 = "Test";

	MyStringTest()
	{
#ifdef _DEBUG
		std::cout << __FUNCSIG__ << std::endl;
#endif
	}

	~MyStringTest()
	{
#ifdef _DEBUG
		std::cout << __FUNCSIG__ << std::endl;
#endif
	}

	virtual void SetUp() override
	{
#ifdef _DEBUG
		std::cout << __FUNCSIG__ << std::endl;
#endif
	}

	virtual void TearDown() override
	{
#ifdef _DEBUG
		std::cout << __FUNCSIG__ << std::endl;
#endif
	}
};

TEST_F(MyStringTest, TestOfDefaultConstructor)
{
	MyString object;
	EXPECT_EQ(object.c_str(), nullptr);
	EXPECT_EQ(object.length(), 0);
}

TEST_F(MyStringTest, TestOfParameterizedConstructor)
{
	MyString object("987654321");
	EXPECT_STREQ(object.c_str(), "987654321");
	EXPECT_EQ(object.length(), 10);
}

TEST_F(MyStringTest, TestOfCopyConstructor)
{
	object1 = "test string";
	EXPECT_STREQ(object1.c_str(), "test string");
	EXPECT_EQ(object1.length(), 12);
}

TEST_F(MyStringTest, TestOfAssignmentOperatorWithMyStringArg)
{
	object1 = object2;
	EXPECT_EQ(object1, object2);
}

TEST_F(MyStringTest, TestOfAssignmentOperatorWithConstCharArg)
{
	object1 = "test";
	EXPECT_STREQ(object1.c_str(), "test");
	EXPECT_STRNE(object1.c_str(), "test1");
}

TEST_F(MyStringTest, TestOfIndexOperator)
{
	EXPECT_EQ(object1[0], 'E');
	EXPECT_EQ(object2[3], 't');
}

TEST_F(MyStringTest, TestOfEqualityOperator)
{
	object1 = "Test";
	EXPECT_EQ(object1, object2);
}

TEST_F(MyStringTest, TestOfNotEqualityOperator)
{
	EXPECT_NE(object1, object2);
}

TEST_F(MyStringTest, TestOfPlusOperator)
{
	MyString object = object1 + object2;
	EXPECT_EQ(object, "ExampleTest");
}

TEST_F(MyStringTest, TestOfPlusAssignmentOperator)
{
	object2 += object1;
	EXPECT_STREQ(object2.c_str(), "TestExample");
}

TEST_F(MyStringTest, TestOfLength)
{
	EXPECT_EQ(object1.length(), 8);
	EXPECT_EQ(object2.length(), 5);
}

TEST_F(MyStringTest, TestOfEmpty)
{
	EXPECT_EQ(object1.empty(), false);
	MyString object;
	EXPECT_EQ(object.empty(), true);
}

TEST_F(MyStringTest, TestOfClear)
{
	object1.clear();
	EXPECT_EQ(object1.length(), 0);
	EXPECT_STREQ(object1.c_str(), "");
}

TEST_F(MyStringTest, TestOfFind)
{
	MyString str = "pl";
	EXPECT_EQ(object1.find(str), 4u);
	MyString object = object1 + object2;
	EXPECT_EQ(object.find(object2), 7);
}

TEST_F(MyStringTest, TestOfSwap)
{
	object1.swap(object2);
	EXPECT_EQ(object1, "Test");
	EXPECT_EQ(object2, "Example");
}

TEST_F(MyStringTest, TestOfC_str)
{
	MyString obj = {};
	EXPECT_EQ(obj.c_str(), nullptr);
}
