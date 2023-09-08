#include <iostream>
#include <string.h>

class MyString {
private:
	char* string_content;
	int	  string_length;
	int	  memory_capacity;

public:
	MyString(char c);
	MyString(const char* str);
	MyString(const MyString& str);
	~MyString();

	int length() const;
	int capacity();
	int find(int find_from, MyString& str) const;
	int find(int find_from, const char* str) const;
	int find(int find_from, char c) const;
	void print()	const;
	void println() const;
	void reserve(int size);
	char at(int i) const;

	MyString& assign(const MyString& str);
	MyString& assign(const char* str);
	MyString& erase(int loc, int num);
	MyString& MyString::insert(int loc, const MyString& str);
	MyString& MyString::insert(int loc, const char* str);
	MyString& MyString::insert(int loc, char c);
};


MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
}

MyString::MyString(const char* str) {
	string_length = strlen(str);
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++) string_content[i] = str[i];

}

MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	string_content = new char[string_length];
	for (int i = 0; i < string_length; i++) {
		string_content[i] = str.string_content[i];
	}
}

int MyString::length() const { return string_length; }


void MyString::print() const{
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
}
void MyString::println() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
	std::cout << std::endl;
}
MyString::~MyString() { delete[] string_content;  }

MyString& MyString::insert(int loc, const MyString& str) {
	if (loc < 0 || loc > string_length) return *this;

	if (string_length + str.string_length > memory_capacity) {

		if (memory_capacity * 2 > string_length + str.string_length)
			memory_capacity *= 2;
		else
			memory_capacity = string_length + str.string_length;

		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];

		// �ϴ� insert �Ǵ� �κ� ���������� ������ �����Ѵ�.
		int i;
		for (i = 0; i < loc; i++) {
			string_content[i] = prev_string_content[i];
		}

		// �׸��� ���ӿ� insert �Ǵ� ���ڿ��� �ִ´�.
		for (int j = 0; j != str.string_length; j++) {
			string_content[i + j] = str.string_content[j];
		}

		// ���� �ٽ� �� ���ڿ��� ������ �޺κ��� �����Ѵ�.
		for (; i < string_length; i++) {
			string_content[str.string_length + i] = prev_string_content[i];
		}

		delete[] prev_string_content;

		string_length = string_length + str.string_length;
		return *this;
	}

	// ���� �ʰ����� �ʴ� ��� ���� �����Ҵ��� �� �ʿ䰡 ���� �ȴ�.
	// ȿ�������� insert �ϱ� ����, �и��� �κ��� ���� �ڷ� �о������.

	for (int i = string_length - 1; i >= loc; i--) {
		// �ڷ� �б�. �� �� ������ ���ڿ� �����Ͱ� ������� �ʰ� ��
		string_content[i + str.string_length] = string_content[i];
	}
	// �׸��� insert �Ǵ� ���� �ٽ� ����ֱ�
	for (int i = 0; i < str.string_length; i++)
		string_content[i + loc] = str.string_content[i];

	string_length = string_length + str.string_length;
	return *this;
	
}

MyString& MyString::assign(const MyString& str) {
	if (str, string_length > memory_capacity) {
		delete[] string_content;

		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}
	for (int i = 0; i != str.string_length; i++) {
		string_content[i] = str.string_content[i];
	}

	string_length = str.string_length;

	return *this;
}

MyString& MyString::assign(const char* str) {
	int str_length = strlen(str);
	if (str_length > memory_capacity) {
		// �׷��� �ٽ� �Ҵ��� ����߸� �Ѵ�.
		delete[] string_content;

		string_content = new char[str_length];
		memory_capacity = str_length;
	}
	for (int i = 0; i != str_length; i++) {
		string_content[i] = str[i];
	}

	string_length = str_length;

	return *this;
}

int MyString::capacity() { return memory_capacity;  }

void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char *prev_string_content = string_content;
		//a�� �ִ��� b�� �ű��
		string_content = new char[size];
		//a�� ����� �ø���
		memory_capacity = size;
		//b������ �ٽ� a�� ����ִ´�
		for (int i = 0; i != string_length; i++) 
			string_content[i] = prev_string_content[i];
		//b�� �����Ѵ�
		delete[] prev_string_content;
	}	
}

char MyString::at(int i) const {
	if (i >= string_length || i < 0)
		return NULL;
	else
		return string_content[i];
}

MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);
	return insert(loc, temp);
}
MyString& MyString::insert(int loc, char c) {
	MyString temp(c);
	return insert(loc, temp);
}

MyString& MyString::erase(int loc, int num) {
	if (num < 0 || loc <  0 || loc > string_length) return *this;

	for (int i = loc + num; i < string_length; i++) {
		string_content[i - 1] = string_content[i];
	}
	string_length -= num;
	return *this;
}

int MyString::find(int find_from, MyString&str) const {
	int i, j;
	if (str.string_length == 0) return -1;
	//										ã�� �ܾ�
	for (i = find_from; i <= string_length - str.string_length; i++) {
		for (j = 0; j < str.string_length; j++) {
			if (string_content[i + j] != str.string_content[j]) break;
		}
		if (j == str.string_length) return i;
	}
	return -1;
}
int MyString::find(int find_from, const char* str) const {
	MyString temp(str);
	return find(find_from, temp);
}
int MyString::find(int find_from, char c) const {
	MyString temp(c);
	return find(find_from, temp);
}

void main()
{
	MyString str1("this is a very very long string");
	std::cout << "Location of first <very> in the string : " << str1.find(0, "very")
		<< std::endl;
	std::cout << "Location of second <very> in the string : "
		<< str1.find(str1.find(0, "very") + 1, "very") << std::endl;
	//MyString str1("very long string");
	//MyString str2("<some string inserted between>");
	//str1.reserve(30);

	//std::cout << "Capacity : " << str1.capacity() << std::endl;
	//std::cout << "String length : " << str1.length() << std::endl;
	//str1.println();

	//str1.insert(5, str2);
	//str1.println();

	//std::cout << "Capacity : " << str1.capacity() << std::endl;
	//std::cout << "String length : " << str1.length() << std::endl;
	//str1.println();
}