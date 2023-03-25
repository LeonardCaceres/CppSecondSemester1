#include "cppstring.h"

String::String() {
  str_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

String::String(const int& size, const char& symbol) {
  if (size == 0) {
    str_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  } else {
    size_ = size;
    capacity_ = size * 2;
    str_ = new char[capacity_];
    for (int i = 0; i < size; ++i) {
      str_[i] = symbol;
    }
    str_[size_] = '\0';
  }
}

String::String(const char* str) {
  int size = 0;
  while (str[size] != '\0') {
    size++;
  }
  if (size != 0) {
    size_ = size;
    capacity_ = size * 2;
    str_ = new char[capacity_];
    for (int i = 0; i < size; ++i) {
      str_[i] = str[i];
    }
  } else {
    str_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}

String::String(const char* str, const int& size) {
  size_ = size;
  capacity_ = size * 2;
  str_ = new char[capacity_];
  for (int i = 0; i < size; ++i) {
    str_[i] = str[i];
  };
}

String::~String() {
  delete[] str_;
  str_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

String::String(const String& other) {
  if (other.str_ == nullptr) {
    str_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  } else {
    size_ = other.size_;
    capacity_ = other.capacity_;
    str_ = new char[capacity_];
    for (int i = 0; i < size_; ++i) {
      str_[i] = other.str_[i];
    }
    str_[size_] = '\0';
  }
}

String& String::operator=(const String& other) {
  if (*this == other) {
    return *this;
  }
  if (other.str_ == nullptr) {
    delete[] str_;
    str_ = nullptr;
    capacity_ = 0;
    size_ = 0;
  } else {
    delete[] str_;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->str_ = new char[capacity_];
    for (int i = 0; i < size_; ++i) {
      this->str_[i] = other.str_[i];
    }
    str_[size_] = '\0';
  }
  return *this;
}

char& String::At(const int& index) {
  if (str_ == nullptr) {
    throw StringOutOfRange{};
  } else {
    if (index >= size_ || index < 0) {
      throw StringOutOfRange{};
    }
  }
  return str_[index];
}

char String::At(const int& index) const {
  if (str_ == nullptr) {
    throw StringOutOfRange{};
  } else {
    if (index >= size_ || index < 0) {
      throw StringOutOfRange{};
    }
  }
  return str_[index];
}

char& String::operator[](const int& index) {
  return str_[index];
}

char String::operator[](const int& index) const {
  return str_[index];
}

char& String::Front() {
  return str_[0];
}

char String::Front() const {
  return str_[0];
}

char& String::Back() {
  return str_[size_ - 1];
}

char String::Back() const {
  return str_[size_ - 1];
}

const char* String::CStr() const {
  return str_;
}

const char* String::Data() const {
  return str_;
}

char* String::CStr() {
  return str_;
}

char* String::Data() {
  return str_;
}

bool String::Empty() const {
  return size_ == 0;
}

int String::Size() const {
  return size_;
}

int String::Length() const {
  return size_;
}

int String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  if (str_ != nullptr) {
    size_ = 0;
    str_[0] = '\0';
  }
}

void String::Swap(String& other) {
  String tmp = std::move(*this);
  *this = std::move(other);
  other = std::move(tmp);
}

void String::PopBack() {
  size_--;
}

void String::IncreaseSize() {
  if (size_ != 0) {
    capacity_ *= 2;
    auto new_char = new char[capacity_];
    for (int i = 0; i < size_; ++i) {
      new_char[i] = str_[i];
    }
    delete[] str_;
    str_ = std::move(new_char);
    /*str_ = new char[capacity_ + 1];
    for (int i = 0; i < size_ + 1; ++i) {
      str_[i] = new_char[i];
    }*/
  } else {
    capacity_ = 15;
    str_ = new char[capacity_];
  }
}

void String::IncreaseSize(const int& a) {
  capacity_ = a;
  auto new_char = new char[capacity_ + 1];
  for (int i = 0; i < size_; ++i) {
    new_char[i] = str_[i];
  }
  delete[] str_;
  str_ = nullptr;
  std::swap(str_, new_char);
  /*for (int i = 0; i < size_ + 1; ++i) {
    str_[i] = new_char[i];
  }*/
}

void String::PushBack(const char& a) {
  if ((size_ + 2) >= capacity_) {
    IncreaseSize();
  }
  str_[size_] = a;
  size_++;
}

/*String& String::operator+=(const String& other) {
  if (size_ == 0) {
    IncreaseSize(other.capacity_);
    for (int i = 0; i < other.size_; ++i) {
      str_[i] = other.str_[i];
    }
  } else {
    IncreaseSize(other.capacity_ + other.capacity_);
    for (int i = this->size_; i < (size_ + other.size_); ++i) {
      str_[i] = other.str_[i];
    }
  }
  return *this;
}*/

String& String::operator+=(const String& other) {
  if (this->str_ == nullptr && other.str_ == nullptr) {
    return *this;
  }
  if (other.str_ == nullptr) {
    return *this;
  }
  while (capacity_ < other.size_ + size_) {
    IncreaseSize();
  }
  for (int i = 0; i < other.size_; ++i) {
    str_[size_ + i] = other.str_[i];
  }
  size_ += other.size_;
  return *this;
}

String& String::operator+=(const char& symbol) {
  PushBack(symbol);
  return *this;
}

void String::Resize(const int& new_size, const char& symbol) {
  if (new_size < size_) {
    size_ = new_size;
  } else {
    while (new_size > 1 + capacity_) {
      IncreaseSize();
    }
    for (int i = 0; i < new_size - size_; ++i) {
      str_[size_ + i] = symbol;
    }
    size_ = new_size;
  }
}

void String::Reserve(const int& new_capacity) {
  if (capacity_ < new_capacity) {
    capacity_ = new_capacity;
    IncreaseSize(capacity_);
  }
}

void String::ShrinkToFit() {
  IncreaseSize(size_);
}

bool operator==(const String& str1, const String& str2) {
  bool is_one_nullptr = false;
  if (str2.str_ == nullptr && str1.str_ == nullptr) {
    is_one_nullptr = true;
  }
  if (str2.str_ == nullptr && str1.size_ == 0) {
    is_one_nullptr = true;
  }
  if (str1.str_ == nullptr && str2.size_ == 0) {
    is_one_nullptr = true;
  }
  if (is_one_nullptr) {
    return true;
  }
  if (str1.size_ != str2.size_) {
    return false;
  }
  for (int i = 0; i < str1.size_; ++i) {
    if (str1.str_[i] != str2.str_[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& str1, const String& str2) {
  return !(str1 == str2);
}

bool operator<(const String& str1, const String& str2) {
  if (str1.size_ == 0 && str2.size_ > 0) {
    return true;
  }
  if (str2.size_ == 0) {
    return false;
  }
  for (int i = 0; i < std::min(str1.size_, str2.size_); ++i) {
    if (str1.str_[i] > str2.str_[i]) {
      return false;
    }
    if (str1.str_[i] < str2.str_[i]) {
      return true;
    }
  }
  return str1.size_ < str2.size_;
}
bool operator>(const String& str1, const String& str2) {
  if (str1.size_ > 0 && str2.size_ == 0) {
    return true;
  }
  if (str1.size_ == 0) {
    return false;
  }
  for (int i = 0; i < std::min(str1.size_, str2.size_); ++i) {
    if (str1.str_[i] < str2.str_[i]) {
      return false;
    }
    if (str1.str_[i] > str2.str_[i]) {
      return true;
    }
  }
  return str1.size_ > str2.size_;
}

bool operator>=(const String& str1, const String& str2) {
  return !(str1 < str2);
}

bool operator<=(const String& str1, const String& str2) {
  return !(str1 > str2);
}

std::ostream& operator<<(std::ostream& os, String str) {
  str.PushBack('\0');
  if (str.size_ != 0) {
    os << str.str_;
  }
  return os;
}

String operator+(const String& str1, const String& str2) {
  String new_string(str1);
  new_string += str2;
  return new_string;
}