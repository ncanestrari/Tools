
#pragma once

template<class T>
class Singleton {
private:
  Singleton() {}

  static T & __get__() {
    static T instance;
    return instance;
  }

public:
  Singleton(const Singleton &) = delete;
  Singleton & operator=(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton & operator=(Singleton &&) = delete;

  static T & get()    { return  __get__(); }
  static T * getptr() { return &__get__(); }
};

