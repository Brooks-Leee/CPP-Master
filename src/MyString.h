#pragma once
class MyString
{
public:
	MyString(const char* string = nullptr);
	MyString(const MyString& str);

	~MyString();

private:
	int len();
	void append();
	int find();
	MyString* split();

	int m_Strlen(const char* str);


	bool operator==(const MyString& mystr);
	MyString operator=(const MyString& mystr);

private:
	char* m_myString;
	int m_strLen;
};

