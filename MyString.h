#pragma once
#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <initializer_list>

class MyString {
public:
	MyString();
	MyString(const char* str);
	MyString(std::initializer_list<char> list);
	MyString(std::string str);
	MyString(const char* str, int count);
	MyString(int count, char c);
	MyString(const MyString& str);
	~MyString();
	const MyString& operator= (const char* str);
	const MyString& operator= (std::string str);
	const MyString& operator= (const char c);
	const MyString& operator=(const MyString& str);
	const MyString operator+ (const MyString& str);
	const MyString operator+ (const char* str);
	const MyString operator+ (std::string str);
	const MyString& operator+= (const char* str);
	const MyString& operator+= (std::string str);
	const char& operator[] (int index);
	bool operator>(const MyString& str);
	bool operator<(const MyString& str);
	bool operator>=(const MyString& str);
	bool operator<=(const MyString& str);
	bool operator==(const MyString& str);
	bool operator!=(const MyString& str);
	const char* c_str();
	const char* data();
	int length();
	int size();
	bool empty();
	size_t capacity();
	void shrink_to_fit();
	void clear();
	friend std::ostream& operator<< (std::ostream& out, const MyString& str);
	friend std::istream& operator>> (std::istream& in, MyString& str);
	void insert(int index, int count, char c);
	void insert(int index, const char* str);
	void insert(int index, const char* str, int count);
	void insert(int index, std::string str);
	void insert(int index, std::string str, int count);
	void erase(int index, int count);
	void append(int count, char c);
	void append(const char* str, int index, int count);
	void append(const char* str);
	void append(std::string str);
	void append(std::string str, int index, int count);
	void replace(int index, int count, const char* str);
	void replace(int index, int count, std::string str);
	MyString substr(int index);
	MyString substr(int index, int count);
	int find(const char* str);
	int find(const char* str, int index);
	int find(std::string str);
	int find(std::string str, int index);

private:
	char* a_string;
	int a_size;
	int a_capacity;
	int compare(const MyString&);
};

#endif //_MYSTRING_H_