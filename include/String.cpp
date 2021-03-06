#ifndef STRING_CPP
#define STRING_CPP
#include<new>
#include<assert.h>
#include<iostream>
#include "String.h"

#define NO_FREE_MEM_ERR "Error: No free memory!"

unsigned int strLen(const char* str) {
	unsigned int res = 0;
	for (size_t i = 0; str[i]; i++)
	{
		res++;
	}

	return res;
}

unsigned int max(const int& first, const int& second) {
	return first >= second ? first : second;
}

unsigned int min(const int& first, const int& second) {
	return first >= second ? second : first;
}

short strCompare(const char* first, const char* second) {
	unsigned int firstLength = strLen(first);
	unsigned int secondLength = strLen(second);

	unsigned int minLength = min(firstLength, secondLength);
	for (size_t i = 0; i < minLength; i++)
	{
		if (first[i] < second[i]) {
			return -1;
		}
		else if (first[i] > second[i]) {
			return 1;
		}
	}

	if (firstLength == secondLength) {
		return 0;
	}

	return firstLength > secondLength ? 1 : -1;
}

void strCopy(const char* source, char* destination) {
	if (source == nullptr || destination == nullptr) {
		return;
	}

	unsigned int sourceLength = strLen(source);
	unsigned int destinationLength = strLen(destination);
	
	assert(destinationLength >= sourceLength);

	for (size_t i = 0; i < sourceLength; i++)
	{
		destination[i] = source[i];
	}

	destination[sourceLength] = '\0';
}

void strConcat(char* destination, const char* source) {
	unsigned int sourceLength = strLen(source);
	unsigned int destinationLength = strLen(destination);
	unsigned int sourceIndex = 0;

	for (size_t i = destinationLength; i < destinationLength + sourceLength; i++)
	{
		destination[i] = source[sourceIndex];
		sourceIndex++;
	}

	destination[destinationLength + sourceLength] = '\0';
}

String::String(const char* _str) : capacity(0), length(0), str(nullptr) {
	assert(_str != nullptr);

	this->length = strlen(_str);
	this->reserve(this->length);

	strCopy(_str, this->str);
}

String::String(const String& other) : capacity(0), length(0), str(nullptr) {
	if (this != &other) {
		this->copy(other);
	}
}

String::~String() {
	this->deleteInternals();
}

String& String::operator=(const String& other) {
	if (this != &other) {
		this->copy(other);
	}

	return *this;
}

String& String::operator+=(const String& other) {
	this->copy(*this + other);

	return *this;
}
String& String::operator+=(const char* str) {
	this->copy(*this + str);

	return *this;
}

String& String::operator+=(const char& character) {
	this->copy(*this + character);

	return *this;
}

String String::operator+(const String& other) {
	String result = *this;
	unsigned int strLength = strLen(other.str);

	if (strLength + result.length >= result.capacity) {
		result.reserve(max(strLength, result.length));
	}

	strConcat(result.str, this->str);
	strConcat(result.str, other.str);
	result.length += strLength;

	return result;
}
String String::operator+(const char* str) {
	String result = *this;
	unsigned int strLength = strLen(str);

	if (strLength + result.length >= result.capacity) {
		result.reserve(max(strLength, result.length));
	}

	strConcat(result.str, str);
	result.length += strLength;

	return result;
}
String String::operator+(const char& character) {
	String result = *this;

	if (result.length + 1 >= result.capacity) {
		result.reserve(max(1, result.length));
	}

	result.str[result.length] = character;
	result.length++;
	result.str[result.length] = '\0';

	return result;
}

bool String::operator==(const String& other) {
	return strCompare(this->str, other.str) == 0;
}
bool String::operator==(const char* str) {
	return strCompare(this->str, str) == 0;
}

bool String::operator!=(const char* str) {
	return !(*this == str);
}

bool String::operator!=(const String& other) {
	return !(*this == other);
}

bool String::operator>(const String& other) {
	return strCompare(this->str, other.str) == 1;
}
bool String::operator>(const char* str) {
	return strCompare(this->str, str) == 1;
}

bool String::operator<(const String& other) {
	return strCompare(this->str, other.str) == -1;
}

bool String::operator<(const char* str) {
	return strCompare(this->str, str) == -1;
}

bool String::operator>=(const char* str) {
	return strCompare(this->str, str) >= 0;
}
bool String::operator<=(const char* str) {
	return strCompare(this->str, str) <= 0;
}
bool String::operator>=(const String& other) {
	return strCompare(this->str, other.str) >= 0;
}
bool String::operator<=(const String& other) {
	return strCompare(this->str, other.str) <= 0;
}

std::ostream& operator<<(std::ostream& stream, const String& string) {
	stream.write(string.str, string.length);

	return stream;
}

char& String::operator[](const unsigned int& index) {
	assert(index >= 0 && index < this->length);

	return this->str[index];
}

const char& String::operator[](const unsigned int& index) const {
	assert(index >= 0 && index < this->length);

	return this->str[index];
}

int String::indexOf(const char* str) const{
	unsigned int strLength = strLen(str);

	for (size_t i = 0; i < this->length; i++)
	{
		if (i + strLength - 1 >= this->length) {
			return -1;
		}

		if (this->str[i] == str[0]) {
			for (size_t j = 1; j < strLength; j++)
			{
				if (this->str[i + j] != str[j]) {
					return -1;
				}
			}

			return i;
		}

	}

	return -1;
}

int String::indexOf(const char& character) const{
	for (size_t i = 0; i < this->length; i++)
	{
		if (this->str[i] == character) {
			return i;
		}
	}

	return -1;
}

int String::indexOf(const String& other) const{
	return this->indexOf(other.str);
}

String String::substring(const unsigned int& first, const unsigned int& length) {
	assert(length >= 0 && first >= 0 && length < this->length && first + length <= length);

	String res;

	for (size_t i = first; i < first + length; i++)
	{
		res += this->str[i];
	}

	return res;
}

Vector<String> String::split(const char& delimiter) {
	Vector<String> res;
	String currWord;

	for (size_t i = 0; i < this->length; i++)
	{
		if (this->str[i] == delimiter) {
			res.pushBack(currWord);
			currWord = "";
		}
		else {
			currWord += this->str[i];
		}
	}

	res.pushBack(currWord);

	return res;
}

unsigned int String::getLength() const {
	return this->length;
}
unsigned int String::getCapacity() const {
	return this->capacity;
}

const char* const String::getConstChar() const{
	return this->str;
}

void String::reserve(const unsigned int& capacity) {
	if (capacity == 0) {
		this->capacity = this->capacity * 2 + 1;
	}
	else {
		this->capacity += capacity * 2;
	}

	this->copy(*this);
}

void String::copy(const String& other) {
	this->capacity = other.capacity;
	this->length = other.length;

	char* newStr = new (std::nothrow) char[this->capacity];

	if (newStr == nullptr) {
		throw NO_FREE_MEM_ERR;
	}

	strCopy(other.str, newStr);

	this->deleteInternals();
	this->str = newStr;
}

void String::deleteInternals() {
	delete[] this->str;
}
#endif // !STRING_CPP
