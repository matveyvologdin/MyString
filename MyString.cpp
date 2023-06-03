#include "MyString.h"

#pragma region ������������_�_����������
//������ �����������
MyString::MyString()
{
	//�������������� ������ ������ ������� � �������� ����
	this->a_size = 0;
	this->a_capacity = 0;
	this->a_string = nullptr;
}

//�������� �����������
MyString::MyString(const char* str, int count):MyString()
{
	if (count > 0 && str != nullptr)
	{	
		//���� �������� ���������� �������� ������ ����� ������,\
		�� ���������� ����������, ������ ����� ������
		if (count > strlen(str))
			count = strlen(str);
		
		//�������� ������ ��� ������ � �������������� ���� �������
		this->a_string = new char[count + 1];
		this->a_size = count;
		this->a_capacity = count + 1;
		
		//�������� � ������ ������ ������� ������� ������
		for (int i = 0; i < this->a_size; ++i)
			this->a_string[i] = str[i];
		this->a_string[this->a_size] = '\0';
	}
}


//����������� �������, ���������� ��������� ������������
MyString::MyString(const char* str) :MyString(str, strlen(str)) {}


//����������� �������, ���������� ��������� ������������
MyString::MyString(std::initializer_list<char> list) : MyString(std::string(list)) {}


//����������� �������, ���������� ��������� ������������
MyString::MyString(std::string str) : MyString(str.c_str()) {}


//����������� �������, ���������� ��������� ������������
MyString::MyString(int count, char c) :MyString(std::string(count, c)) {}


//����������� �������, ���������� ��������� ������������
MyString::MyString(const MyString& str) : MyString(str.a_string) {}


//���������� �������
MyString::~MyString()
{//������� ������ � ����������� �� nullptr, ����� �������� ������ � ������
	delete[] this->a_string;
	this->a_string = nullptr;
}
#pragma endregion

#pragma region ���������
//�������� ������������
const MyString& MyString::operator=(const char* str)
{
	if (str != nullptr)
	{
		//���� ������ ��������, �� ����� ������� ������������� ����� ��������,\
		������� ������ ���������� � ������ �������
		this->a_size = strlen(str);
		if (strlen(str) >= this->a_capacity)
		{
			//���� ������ ������������� ������ ������ ���������� ������,\
			�������� ������ �������� �������
			this->a_capacity = strlen(str) + 1;
			delete[] this->a_string;
			this->a_string = new char[this->a_size + 1];
		}
		for (int i = 0; i < this->a_size; ++i)
			this->a_string[i] = str[i];
		this->a_string[this->a_size] = '\0';
	}
	else
	{
		//���� ������� ������ ������, �������������� ������, ��� � ������������ ��� ����������
		delete[] this->a_string;
		this->a_size = 0;
		this->a_capacity = 0;
	}
	//���������� ������ �� ������� ������
	return *this;
}


//�������� ������������
const MyString& MyString::operator=(std::string str)
{
	return this->operator=(str.c_str());
}


//�������� ������������
const MyString& MyString::operator=(const char c)
{
	return this->operator=(std::string(c, 1).c_str());
}


//�������� ������������
const MyString& MyString::operator=(const MyString& str)
{
	return this->operator=(str.a_string);
}


//�������� ��������(������������)
const MyString MyString::operator+(const MyString& str)
{
	//������ ����� ������, ������� ����� ������������ ����������
	MyString newStr;
	newStr.a_size = this->a_size + str.a_size;
	newStr.a_capacity = newStr.a_size + 1;
	newStr.a_string = new char[newStr.a_size + 1];
	for (int i = 0; i < this->a_size; ++i)
		newStr.a_string[i] = this->a_string[i];
	for (int i = 0; i < str.a_size; ++i)
		newStr.a_string[i + this->a_size] = str.a_string[i];
	newStr.a_string[newStr.a_size] = '\0';
	return newStr;
}


//�������� ��������(������������)
const MyString MyString::operator+(const char* str)
{
	return this->operator+(MyString(str));
}


//�������� ��������(������������)
const MyString MyString::operator+(std::string str)
{
	return this->operator+(str.c_str());
}


//�������� ��������(������������) � ������������
const MyString& MyString::operator+=(const char* str)
{
	return this->operator=(this->operator+(str));
}


//�������� ��������(������������) � ������������
const MyString& MyString::operator+=(std::string str)
{
	return this->operator+=(str.c_str());
}


//�������� ����������
const char& MyString::operator[](int index)
{
	//���� ������ ������ ��� ����� 0, �� ���������� ������ �� ����� �������
	if (index >= 0)
		return this->a_string[index];
	else
	{
		//����� ����������� ���������� out_of_range
		throw std::out_of_range("Invalid index!!!(operator[])\n");
	}
}


//�������� ���������
bool MyString::operator>(const MyString& str)
{
	return this->compare(str) > 0;
}


//�������� ���������
bool MyString::operator<(const MyString& str)
{
	return this->compare(str) < 0;
}


//�������� ���������
bool MyString::operator>=(const MyString& str)
{
	return this->compare(str) >= 0;
}


//�������� ���������
bool MyString::operator<=(const MyString& str)
{
	return this->compare(str) <= 0;
}


//�������� ���������
bool MyString::operator==(const MyString& str)
{
	return this->compare(str) == 0;
}


//�������� ���������
bool MyString::operator!=(const MyString& str)
{
	return this->compare(str) != 0;
}


//�������� ������ � ����� ������
std::ostream& operator<< (std::ostream& out, const MyString& str)
{
	if (str.a_string != nullptr)
		out << str.a_string;
	return out;
}


//�������� ����� �� ������ �����
std::istream& operator>>(std::istream& in, MyString& str)
{
	delete[] str.a_string;
	str.a_size = 0;
	str.a_string = new char[str.a_size + 1];
	str.a_string[str.a_size] = '\0';

	char input;
	//���� �� �������� ������ �������� ������,\
	��������� ������� �� ������ ����� � ������ �������
	while ((input = in.get()) != '\n')
	{
		if (str.a_size >= str.a_capacity)
		{	
			//���� ������ ������������� ������ ������ ���������� ������,\
			�������� ������ �������� �������
			//��������� ������ ��������
			char* tmp = new char[str.a_size + 1];
			for (int i = 0; i < str.a_size; ++i)
				tmp[i] = str.a_string[i];
			tmp[str.a_size] = '\0';
			//�������� ������ ��� ����� ������
			delete[] str.a_string;
			str.a_size++;
			str.a_string = new char[str.a_size + 1];
			str.a_capacity = str.a_size + 1;
			//��������������� ��������
			for (int i = 0; i < str.a_size - 1; ++i)
				str.a_string[i] = tmp[i];
			delete[] tmp;
		}
		//��������� �������� ������
		str.a_string[str.a_size - 1] = input;
		str.a_string[str.a_size] = '\0';
	}
	return in;
}


#pragma endregion

#pragma region ������

//������������������ ��������� ���� �����
int MyString::compare(const MyString& str)
{
	char* tmp1 = this->a_string;
	char* tmp2 = str.a_string;
	for (; *tmp1 && *tmp2; ++tmp1, ++tmp2) {
		if (*tmp1 != *tmp2) {
			return *tmp1 < *tmp2 ? -1 : +1;
		}
	}
	if (*tmp1 != 0) return +1;
	if (*tmp2 != 0) return -1;
	return 0;
}

//���������� ��������� �� ������, ��������������� ����-��������������� ��������
const char* MyString::c_str()
{
	return this->a_string;
}

//���������� ��������� �� ������, �� ����������� ��������������� ����-��������������� ��������
const char* MyString::data()
{
	return this->a_string;
}

//���������� ����� ������
int MyString::length()
{
	return this->a_size;
}

//���������� ����� ������
int MyString::size()
{
	return this->a_size;
}

//���� ������ ������ - ���������� true, ����� - false
bool MyString::empty()
{
	return (this->a_size == 0);
}

//���������� ������ ���������� ������ ��� ������
size_t MyString::capacity()
{
	return this->a_capacity;
}

//��������� ���������� ������ ����� ��� ������ ������
void MyString::shrink_to_fit()
{
	char* tmp = new char[this->a_size];
	for (int i = 0; i < this->a_size; ++i)
		tmp[i] = this->a_string[i];
	delete[] this->a_string;
	this->a_string = new char[this->a_size + 1];
	this->a_capacity = this->a_size + 1;
	for (int i = 0; i < this->a_size; ++i)
		this->a_string[i] = tmp[i];
	this->a_string[this->a_size] = '\0';
	delete[] tmp;
}

//������� ������
void MyString::clear()
{
	delete[] this->a_string;
	this->a_string = nullptr;
	this->a_size = 0;
}

//��������� count �������� '�', ������� � 'index' �������
void MyString::insert(int index, int count, char c)
{
	this->insert(index, std::string(count, c));
}

//��������� ������ 'str', ������� � 'index' �������
void MyString::insert(int index, const char* str)
{
	this->insert(index, str, strlen(str));
}

//��������� 'count' �������� ������ 'str', ������� � 'index' �������
void MyString::insert(int index, const char* str, int count)
{
	if (index >= 0 && count > 0 && str != nullptr)
	{
		//���� �������� ���������� �������� ������ ����� ������,\
		�� ���������� ����������, ������ ����� ������
		if (count > strlen(str))
			count = strlen(str);
		MyString tmp(this->a_string, index);
		tmp.operator+=(MyString(str, count).a_string);
		tmp.operator+=(this->a_string + index);
		if (this->a_size + count >= this->a_capacity)
		{
			//���� ������ ������������� ������ ������ ���������� ������,\
			�������� ������ �������� �������
			delete[] this->a_string;
			this->a_string = new char[this->a_size + count + 1];
			this->a_capacity = this->a_size + count + 1;
		}
		this->a_size += count;
		for (int i = 0; i < this->a_size; ++i)
			this->a_string[i] = tmp.a_string[i];
		this->a_string[this->a_size] = '\0';
	}
}

//��������� ������ 'str', ������� � 'index' �������
void MyString::insert(int index, std::string str)
{
	this->insert(index, str.c_str(), str.size());
}

//��������� 'count' �������� ������ 'str', ������� � 'index' �������
void MyString::insert(int index, std::string str, int count)
{
	this->insert(index, str.c_str(), count);
}

//������� 'count' ��������, ������� � 'index' �������
void MyString::erase(int index, int count)
{
	if (index >= 0 && count > 0)
	{
		if (count + index > this->a_size)
			count = this->a_size - index;
		this->a_size -= count;
		for (int i = index; i < this->a_size; ++i)
			this->a_string[i] = this->a_string[i + count];
		this->a_string[this->a_size] = '\0';
	}
}

//��������� 'count' �������� 'c' � ����� ������
void MyString::append(int count, char c)
{
	if (count > 0)
		this->operator+=(MyString(count, c).a_string);
}

//��������� � ����� ������ 'count' ��������, ������� � 'index' ������� ������ 'str' 
void MyString::append(const char* str, int index, int count)
{
	if (count > 0 && index >= 0 && str != nullptr)
	{
		if (count + index > strlen(str))
			count = strlen(str) - index;
		MyString tmp(str + index, count);
		this->operator+=(tmp.a_string);
	}
}

//��������� ������ 'str' � ����� ������
void MyString::append(const char* str)
{
	this->append(str, 0, strlen(str));
}

//��������� ������ 'str' � ����� ������
void MyString::append(std::string str)
{
	this->append(str.c_str());
}

//��������� � ����� ������ 'count' ��������, ������� � 'index' ������� ������ 'str'
void MyString::append(std::string str, int index, int count)
{
	this->append(str.c_str(), index, count);
}

//�������� 'count' �������� ������, ������� � 'index' �������, �� ������� ������ 'str'
void MyString::replace(int index, int count, const char* str)
{
	if (count > 0 && index >= 0 && str != nullptr)
	{
		MyString tmp(this->a_string, index);
		tmp.operator+=(str);
		tmp.operator+=(this->a_string + index + count);
		if (this->a_size - count + strlen(str) >= this->a_capacity)
		{
			//���� ������ ������������� ������ ������ ���������� ������,\
			�������� ������ �������� �������
			delete[] this->a_string;
			this->a_string = new char[this->a_size - count + strlen(str) + 1];
			this->a_capacity = this->a_size + strlen(str) - count + 1;
		}
		this->a_size = this->a_size - count + strlen(str);
		for (int i = 0; i < this->a_size; ++i)
			this->a_string[i] = tmp.a_string[i];
		this->a_string[this->a_size] = '\0';
	}
}

//�������� 'count' �������� ������, ������� � 'index' ������� ������� 'str'
void MyString::replace(int index, int count, std::string str)
{
	this->replace(index, count, str.c_str());
}

//���������� ���������, ������� � 'index' �������
MyString MyString::substr(int index)
{
	return this->substr(index, this->a_size - index);
}

//���������� ��������� ������ 'count', ������� � 'index' �������
MyString MyString::substr(int index, int count)
{
	if (index >= 0 && count > 0 && index + count <= this->a_size)
	{
		MyString tmp(this->a_string + index, count);
		return tmp;
	}
	else if (count <= 0)
		return nullptr;
	else
		throw std::out_of_range("Invalid index!!!(substr)\n");
}

//���������� ������ > 'index' ��������� ������ 'str' � ������
int MyString::find(const char* str, int index)
{
	if (str == nullptr || index < 0 || index > this->a_size)
		return -1;
	for (int i = index; i < this->a_size - strlen(str) + 1; ++i)
	{
		MyString tmp(this->a_string + i, strlen(str));
		if (tmp.compare(str) == 0)
			return i;
	}
	return -1;
}

//���������� ������ ������� ��������� ������ 'str' � ������
int MyString::find(const char* str)
{
	return this->find(str, 0);
}

//���������� ������ ������� ��������� ������ 'str' � ������
int MyString::find(std::string str)
{
	return this->find(str.c_str(), 0);
}

//���������� ������ > 'index' ��������� ������ 'str' � ������
int MyString::find(std::string str, int index)
{
	return this->find(str.c_str(), index);
}

#pragma endregion