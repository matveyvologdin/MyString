#include "MyString.h"

#pragma region Конструкторы_и_деструктор
//пустой конструктор
MyString::MyString()
{
	//инициализируем пустую строку объекта и обнуляем поля
	this->a_size = 0;
	this->a_capacity = 0;
	this->a_string = nullptr;
}

//основной конструктор
MyString::MyString(const char* str, int count):MyString()
{
	if (count > 0 && str != nullptr)
	{	
		//если введённое количество символов больше длины строки,\
		то копируется количество, равное длине строки
		if (count > strlen(str))
			count = strlen(str);
		
		//выделяем память под строку и инициализируем поля объекта
		this->a_string = new char[count + 1];
		this->a_size = count;
		this->a_capacity = count + 1;
		
		//копируем в строку нового объекта входную строку
		for (int i = 0; i < this->a_size; ++i)
			this->a_string[i] = str[i];
		this->a_string[this->a_size] = '\0';
	}
}


//конструктор объекта, делегируем основному конструктору
MyString::MyString(const char* str) :MyString(str, strlen(str)) {}


//конструктор объекта, делегируем основному конструктору
MyString::MyString(std::initializer_list<char> list) : MyString(std::string(list)) {}


//конструктор объекта, делегируем основному конструктору
MyString::MyString(std::string str) : MyString(str.c_str()) {}


//конструктор объекта, делегируем основному конструктору
MyString::MyString(int count, char c) :MyString(std::string(count, c)) {}


//конструктор объекта, делегируем основному конструктору
MyString::MyString(const MyString& str) : MyString(str.a_string) {}


//деструктор объекта
MyString::~MyString()
{//удаляем строку и присваиваем ей nullptr, чтобы избежать ошибок в памяти
	delete[] this->a_string;
	this->a_string = nullptr;
}
#pragma endregion

#pragma region Операторы
//оператор присваивания
const MyString& MyString::operator=(const char* str)
{
	if (str != nullptr)
	{
		//если строка непустая, то полям объекта присваиваются новые значения,\
		входная строка копируется в строку объекта
		this->a_size = strlen(str);
		if (strlen(str) >= this->a_capacity)
		{
			//если размер присваиваемой строки больше выделенной памяти,\
			выделяем память большего размера
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
		//если входная строка пустая, инициализируем объект, как в конструкторе без аргументов
		delete[] this->a_string;
		this->a_size = 0;
		this->a_capacity = 0;
	}
	//возвращаем ссылку на текущий объект
	return *this;
}


//оператор присваивания
const MyString& MyString::operator=(std::string str)
{
	return this->operator=(str.c_str());
}


//оператор присваивания
const MyString& MyString::operator=(const char c)
{
	return this->operator=(std::string(c, 1).c_str());
}


//оператор присваивания
const MyString& MyString::operator=(const MyString& str)
{
	return this->operator=(str.a_string);
}


//оператор сложения(конкатенации)
const MyString MyString::operator+(const MyString& str)
{
	//создаём новый объект, который будет возвращаться оператором
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


//оператор сложения(конкатенации)
const MyString MyString::operator+(const char* str)
{
	return this->operator+(MyString(str));
}


//оператор сложения(конкатенации)
const MyString MyString::operator+(std::string str)
{
	return this->operator+(str.c_str());
}


//оператор сложения(конкатенации) и присваивания
const MyString& MyString::operator+=(const char* str)
{
	return this->operator=(this->operator+(str));
}


//оператор сложения(конкатенации) и присваивания
const MyString& MyString::operator+=(std::string str)
{
	return this->operator+=(str.c_str());
}


//оператор индексации
const char& MyString::operator[](int index)
{
	//если индекс больше или равен 0, то возвращаем символ по этому индексу
	if (index >= 0)
		return this->a_string[index];
	else
	{
		//иначе выбрасываем исключение out_of_range
		throw std::out_of_range("Invalid index!!!(operator[])\n");
	}
}


//оператор сравнения
bool MyString::operator>(const MyString& str)
{
	return this->compare(str) > 0;
}


//оператор сравнения
bool MyString::operator<(const MyString& str)
{
	return this->compare(str) < 0;
}


//оператор сравнения
bool MyString::operator>=(const MyString& str)
{
	return this->compare(str) >= 0;
}


//оператор сравнения
bool MyString::operator<=(const MyString& str)
{
	return this->compare(str) <= 0;
}


//оператор сравнения
bool MyString::operator==(const MyString& str)
{
	return this->compare(str) == 0;
}


//оператор сравнения
bool MyString::operator!=(const MyString& str)
{
	return this->compare(str) != 0;
}


//оператор вывода в поток вывода
std::ostream& operator<< (std::ostream& out, const MyString& str)
{
	if (str.a_string != nullptr)
		out << str.a_string;
	return out;
}


//оператор ввода из потока ввода
std::istream& operator>>(std::istream& in, MyString& str)
{
	delete[] str.a_string;
	str.a_size = 0;
	str.a_string = new char[str.a_size + 1];
	str.a_string[str.a_size] = '\0';

	char input;
	//пока не встретим символ переноса строки,\
	добавляем элемент из потока ввода в строку объекта
	while ((input = in.get()) != '\n')
	{
		if (str.a_size >= str.a_capacity)
		{	
			//если размер присваиваемой строки больше выделенной памяти,\
			выделяем память большего размера
			//сохраняем старое значение
			char* tmp = new char[str.a_size + 1];
			for (int i = 0; i < str.a_size; ++i)
				tmp[i] = str.a_string[i];
			tmp[str.a_size] = '\0';
			//выделяем память под новый размер
			delete[] str.a_string;
			str.a_size++;
			str.a_string = new char[str.a_size + 1];
			str.a_capacity = str.a_size + 1;
			//восстанавливаем значение
			for (int i = 0; i < str.a_size - 1; ++i)
				str.a_string[i] = tmp[i];
			delete[] tmp;
		}
		//добавляем введённый символ
		str.a_string[str.a_size - 1] = input;
		str.a_string[str.a_size] = '\0';
	}
	return in;
}


#pragma endregion

#pragma region Методы

//лексикографическое сравнение двух строк
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

//возвращает указатель на строку, заканчивающуюся нуль-терминированным символом
const char* MyString::c_str()
{
	return this->a_string;
}

//возвращает указатель на строку, не обязательно заканчивающуюся нуль-терминированным символом
const char* MyString::data()
{
	return this->a_string;
}

//возвращает длину строки
int MyString::length()
{
	return this->a_size;
}

//возвращает длину строки
int MyString::size()
{
	return this->a_size;
}

//если строка пустая - возвращает true, иначе - false
bool MyString::empty()
{
	return (this->a_size == 0);
}

//возвращает размер выделенной памяти для строки
size_t MyString::capacity()
{
	return this->a_capacity;
}

//уменьшает выделяемую память ровно под размер строки
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

//очищает строку
void MyString::clear()
{
	delete[] this->a_string;
	this->a_string = nullptr;
	this->a_size = 0;
}

//вставляет count символов 'с', начиная с 'index' индекса
void MyString::insert(int index, int count, char c)
{
	this->insert(index, std::string(count, c));
}

//вставляет строку 'str', начиная с 'index' индекса
void MyString::insert(int index, const char* str)
{
	this->insert(index, str, strlen(str));
}

//вставляет 'count' символов строки 'str', начиная с 'index' индекса
void MyString::insert(int index, const char* str, int count)
{
	if (index >= 0 && count > 0 && str != nullptr)
	{
		//если введённое количество символов больше длины строки,\
		то копируется количество, равное длине строки
		if (count > strlen(str))
			count = strlen(str);
		MyString tmp(this->a_string, index);
		tmp.operator+=(MyString(str, count).a_string);
		tmp.operator+=(this->a_string + index);
		if (this->a_size + count >= this->a_capacity)
		{
			//если размер присваиваемой строки больше выделенной памяти,\
			выделяем память большего размера
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

//вставляет строку 'str', начиная с 'index' индекса
void MyString::insert(int index, std::string str)
{
	this->insert(index, str.c_str(), str.size());
}

//вставляет 'count' символов строки 'str', начиная с 'index' индекса
void MyString::insert(int index, std::string str, int count)
{
	this->insert(index, str.c_str(), count);
}

//стирает 'count' символов, начиная с 'index' индекса
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

//добавляет 'count' символов 'c' в конец строки
void MyString::append(int count, char c)
{
	if (count > 0)
		this->operator+=(MyString(count, c).a_string);
}

//добавляет в конец строки 'count' символов, начиная с 'index' индекса строки 'str' 
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

//добавляет строку 'str' в конец строки
void MyString::append(const char* str)
{
	this->append(str, 0, strlen(str));
}

//добавляет строку 'str' в конец строки
void MyString::append(std::string str)
{
	this->append(str.c_str());
}

//добавляет в конец строки 'count' символов, начиная с 'index' индекса строки 'str'
void MyString::append(std::string str, int index, int count)
{
	this->append(str.c_str(), index, count);
}

//заменяет 'count' символов строки, начиная с 'index' индекса, на символы строки 'str'
void MyString::replace(int index, int count, const char* str)
{
	if (count > 0 && index >= 0 && str != nullptr)
	{
		MyString tmp(this->a_string, index);
		tmp.operator+=(str);
		tmp.operator+=(this->a_string + index + count);
		if (this->a_size - count + strlen(str) >= this->a_capacity)
		{
			//если размер присваиваемой строки больше выделенной памяти,\
			выделяем память большего размера
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

//заменяет 'count' символов строки, начиная с 'index' индекса строкой 'str'
void MyString::replace(int index, int count, std::string str)
{
	this->replace(index, count, str.c_str());
}

//возвращает подстроку, начиная с 'index' индекса
MyString MyString::substr(int index)
{
	return this->substr(index, this->a_size - index);
}

//возвращает подстроку длиной 'count', начиная с 'index' индекса
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

//возвращает индекс > 'index' вхождения строки 'str' в строку
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

//возвращает индекс первого вхождения строки 'str' в строку
int MyString::find(const char* str)
{
	return this->find(str, 0);
}

//возвращает индекс первого вхождения строки 'str' в строку
int MyString::find(std::string str)
{
	return this->find(str.c_str(), 0);
}

//возвращает индекс > 'index' вхождения строки 'str' в строку
int MyString::find(std::string str, int index)
{
	return this->find(str.c_str(), index);
}

#pragma endregion