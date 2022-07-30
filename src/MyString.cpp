#include "MyString.h"
#include <iostream>


// Construct
MyString::MyString(const char* str)
{
	if (str == nullptr)
	{
		m_myString = new char[1];
		*m_myString = '\0';
		std::cout << "constructed an empty MyString u little silly" << std::endl;
	}
	else
	{
		m_strLen = m_calStrLen(str);
		// alocate memory
		m_myString = new char[m_strLen + 1];

		// 使用该方式会乱码，原因不知
		/*while (*str != '\0')
		{
			*m_myString = *str;
			str++;
			m_myString++;
		}*/

		for (int i = 0; i < m_strLen; i++)
		{
			m_myString[i] = *str;
			str++;
		}
		m_myString[m_strLen] = '\0';
	}
}

// Copy construct 
MyString::MyString(const MyString& str)
{
	if (this == &str)
	{
		return;
	}
	if (&str == nullptr)
	{
		m_myString = nullptr;
	}
	else
	{
		m_strLen = str.m_strLen;
		m_myString = new char[m_strLen + 1];
		memcpy(m_myString, str.m_myString, str.m_strLen);
		
		m_myString[m_strLen] = '\0';
	}
}



bool MyString::operator==(const MyString& str)
{
	
	if (this == &str)
	{
		return true;
	}
	if (str.m_strLen == this->m_strLen)
	{
		for (int i = 0; i < m_strLen; i++)
		{
			if (m_myString[i] != str.m_myString[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

MyString MyString::operator=(const MyString& str)
{
	// get the str address, guard self assignment
	if (this == &str)
	{
		return *this;
	}
	else
	{
		delete[] m_myString;
		if (&str == nullptr)
		{
			m_myString = nullptr;
		}
		else
		{
			// remenber update m_strLen
			m_strLen = str.m_strLen;
			m_myString = new char[m_strLen + 1];
			memcpy(m_myString, str.m_myString, str.m_strLen);
			// memcpy() copy memory from the begin of str.m_mystring until the bytes count 
			// so we need add \0 manunlly
			m_myString[m_strLen] = '\0';
		}
		return *this;
	}
}

MyString MyString::operator=(const char* str)
{
	delete[] m_myString;
	if (str == nullptr)
	{
		m_myString = new char[1];
		*m_myString = '\0';
	}
	else
	{
		m_strLen = m_calStrLen(str);
		m_myString = new char[m_strLen + 1];
		for (int i = 0; i < m_strLen; i++)
		{
			m_myString[i] = str[i];
		}
		m_myString[m_strLen] = '\0';
	}
	return *this;
}



MyString::~MyString()
{
	if (m_myString != nullptr)
	{
		delete[] m_myString;

	}
}

int MyString::len()
{
	return m_strLen;
}

void MyString::append(const char* str)
{
	if (str == nullptr)
	{
		return;
	}
	int len = m_calStrLen(str) + m_strLen;
	char* strTemp = new char[len + 1];
	// 重新开辟更大的内存空间
	
	for (int i = 0; i < m_strLen; i++)
	{
		strTemp[i] = m_myString[i];
	}
	for (int i = m_strLen; i < len; i++)
	{
		strTemp[i] = str[i - m_strLen];
	}
	strTemp[len] = '\0';

	delete[] m_myString;
	m_myString = strTemp;
	m_strLen = len;
}

int MyString::m_calStrLen(const char* str)
{
	int len = 0;
	while(*str != '\0')
	{
		len++;
		str++;
	}

	return len;
}

std::ostream& operator<<(std::ostream& out, const MyString& str)
{
	for (int i = 0; i < str.m_strLen; i++)
	{
		out << str.m_myString[i];
	}
	return out;
}
