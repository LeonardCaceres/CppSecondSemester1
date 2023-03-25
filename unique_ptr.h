#pragma once
#include <iostream>

template <typename T>
class UniquePtr {
  T* ptr_;

 public:
  UniquePtr() {
    ptr_ = nullptr;
  }

  explicit UniquePtr(std::nullptr_t) {
    ptr_ = nullptr;
  }

  explicit UniquePtr(T* ptr) {
    ptr_ = ptr;
  }

  UniquePtr(const UniquePtr<T>& other) = delete;

  UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;

  UniquePtr(UniquePtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  UniquePtr<T>& operator=(std::nullptr_t) {
    this->ptr_ = nullptr;
    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  T* Get() const {
    return ptr_;
  }

  T* Release() {
    auto tmp = std::move(ptr_);
    ptr_ = nullptr;
    return tmp;
  }

  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void Swap(UniquePtr<T>& ptr) {
    UniquePtr<T> tmp = std::move(*this);
    *this = std::move(ptr);
    ptr = std::move(tmp);
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};