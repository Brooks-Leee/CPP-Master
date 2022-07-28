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
		m_strLen = m_Strlen(str);
		// alocate memory
		m_myString = new char[m_strLen + 1];
		while (*str != '\0')
		{
			*m_myString = *str;
			str++;
			m_myString++;
		}
		*m_myString = '\0';
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
		memcpy(m_myString, &str, str.m_strLen);
		
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
	else
	{
		return false;
	}
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
			memcpy(m_myString, &str, str.m_strLen);
			// memcpy() copy memory from the begin of &str until the bytes count 
			// so we need add \0 manunlly
			m_myString[m_strLen] = '\0';
			return m_myString;
		}
	}

}

MyString::~MyString()
{
	if (m_myString != nullptr)
	{
		//delete m_MyString;

	}
}

int MyString::m_Strlen(const char* str)
{
	int len = 0;
	while(*str != '\0')
	{
		len++;
		str++;
	}

	return len;
}

