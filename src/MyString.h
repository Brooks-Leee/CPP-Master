#pragma once
#include <iostream>

class MyString
{
public:
	MyString(const char* string = nullptr);
	MyString(const MyString& str);

	~MyString();

	int len();
	void append(const char* str);
	int find(const char* str);
	MyString sub(int begin, int end);
	MyString* split();

	int m_calStrLen(const char* str);


public:

	bool operator==(const MyString& str);
	MyString operator=(const MyString& str);
	MyString operator=(const char* str);
	friend std::ostream& operator<<(std::ostream& out, const MyString& str);

private:
	char* m_myString;
	int m_strLen;
};

