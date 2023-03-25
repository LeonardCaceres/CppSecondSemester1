#pragma once
#include <iostream>

template <typename T>
class SharedPtr {
  T* ptr_;
  int* strong_counter_;

 public:
  SharedPtr() {
    ptr_ = nullptr;
    strong_counter_ = nullptr;
  }

  explicit SharedPtr(T* ptr) {
    ptr_ = ptr;
    strong_counter_ = new int(1);
  }

  SharedPtr(std::nullptr_t) {  // NOLINT
    ptr_ = nullptr;
    strong_counter_ = nullptr;
  }

  SharedPtr(const SharedPtr<T>& other) {
    if (other.ptr_ != nullptr) {
      *other.strong_counter_ += 1;
      strong_counter_ = other.strong_counter_;
      ptr_ = other.ptr_;
    } else {
      ptr_ = nullptr;
      strong_counter_ = nullptr;
    }
  }

  SharedPtr<T>& operator=(std::nullptr_t) {
    if (ptr_ != nullptr) {
      *strong_counter_ -= 1;
      if (*strong_counter_ == 0) {
        delete strong_counter_;
        delete ptr_;
      }
      ptr_ = nullptr;
      strong_counter_ = nullptr;
    }
    return *this;
  }

  SharedPtr<T>& operator=(const SharedPtr<T>& other) {
    if (this == &other) {
      return *this;
    }
    if (this->ptr_ == nullptr) {
      delete strong_counter_;
      delete ptr_;
      if (other.ptr_ != nullptr) {
        (*other.strong_counter_ += 1);
      }
      if (other.ptr_ != nullptr) {
        strong_counter_ = other.strong_counter_;
      } else {
        strong_counter_ = nullptr;
      }
      ptr_ = other.ptr_;
    } else {
      *strong_counter_ -= 1;
      if (*strong_counter_ == 0) {
        delete strong_counter_;
        delete ptr_;
      }
      if (other.ptr_ != nullptr) {
        (*other.strong_counter_ += 1);
        strong_counter_ = other.strong_counter_;
      } else {
        strong_counter_ = nullptr;
      }
      ptr_ = other.ptr_;
    }
    return *this;
  }

  SharedPtr(SharedPtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    if (other.ptr_ != nullptr) {
      strong_counter_ = other.strong_counter_;
    } else {
      strong_counter_ = nullptr;
    }
    other.ptr_ = nullptr;
    other.strong_counter_ = nullptr;
  }

  ~SharedPtr() {
    if (strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete strong_counter_;
        delete ptr_;
      } else {
        *strong_counter_ -= 1;
      }
    }
  }

  SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
    if (this == &other) {
      other.ptr_ = nullptr;
      other.strong_counter_ = nullptr;
      return *this;
    }
    if (this->ptr_ == nullptr) {
      delete strong_counter_;
      ptr_ = other.ptr_;
      if (other.ptr_ != nullptr) {
        strong_counter_ = other.strong_counter_;
      } else {
        strong_counter_ = nullptr;
      }
    } else {
      *strong_counter_ -= 1;
      if (*strong_counter_ == 0) {
        delete strong_counter_;
        delete ptr_;
      }
      ptr_ = other.ptr_;
      if (other.ptr_ != nullptr) {
        strong_counter_ = other.strong_counter_;
      } else {
        strong_counter_ = nullptr;
      }
    }
    other.ptr_ = nullptr;
    other.strong_counter_ = nullptr;
    return *this;
  }

  void Reset(T* ptr = nullptr) {
    if (strong_counter_ != nullptr) {
      *strong_counter_ -= 1;
      if (*strong_counter_ == 0) {
        delete strong_counter_;
        delete ptr_;
      }
      ptr_ = ptr;
      if (ptr == nullptr) {
        strong_counter_ = nullptr;
      } else {
        strong_counter_ = new int(1);
      }
    } else {
      ptr_ = ptr;
      if (ptr_ == nullptr) {
        strong_counter_ = new int(1);
      } else {
        strong_counter_ = nullptr;
      }
    }
  }

  void Swap(SharedPtr<T>& other) {
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->strong_counter_, other.strong_counter_);
  }

  T* Get() const {
    return ptr_;
  }

  int UseCount() const {
    if (ptr_ == nullptr) {
      return 0;
    }
    return *strong_counter_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};