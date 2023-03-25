#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

#pragma once
#include <iostream>

class String {
 public:
  char* str_;
  int size_;
  int capacity_;
  String();
  String(const int& size, const char& symbol);
  String(const char* str);  // NOLINT
  String(const char* str, const int& size);
  ~String();
  String(const String& other);
  String& operator=(const String& other);
  char& operator[](const int& index);
  char operator[](const int& index) const;
  char& At(const int& index);
  char At(const int& index) const;
  char& Front();
  char Front() const;
  char& Back();
  char Back() const;
  const char* CStr() const;
  const char* Data() const;
  char* CStr();
  char* Data();
  bool Empty() const;
  int Size() const;
  int Length() const;
  int Capacity() const;
  void Clear();
  void Swap(String& other);
  void PopBack();
  void IncreaseSize();
  void IncreaseSize(const int& a);
  void PushBack(const char& a);
  String& operator+=(const String& other);
  String& operator+=(char symbol);
  String& operator+=(const char& symbol);
  void Resize(const int& new_size, const char& symbol);
  void Reserve(const int& new_capacity);
  void ShrinkToFit();
  friend bool operator==(const String& str1, const String& str2);
  friend bool operator!=(const String& str1, const String& str2);
  friend bool operator>(const String& str1, const String& str2);
  friend bool operator<(const String& str1, const String& str2);
  friend bool operator>=(const String& str1, const String& str2);
  friend bool operator<=(const String& str1, const String& str2);
  friend String operator+(const String& str1, const String& str2);
  friend std::ostream& operator<<(std::ostream& os, String str);
};
