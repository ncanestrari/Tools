
#pragma once

#include <cstring>
#include <string>
#include <chrono>
#include "date.h"
#include <fmt/format.h>

#define NOW date::format("%Y-%m-%d_%H-%M-%S", std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now())) 

/**
 * Item must have a default constructor
 *                a default copy-constructor
 *                an std::string str() method
 */
template<class Item>
class WrapperItem {
protected:
  bool        m_active;
  std::string m_date;
  Item        m_item;
public:
  WrapperItem()
    : m_active(false)
    , m_date("")
    , m_item() {}

  WrapperItem(const Item & item)
    : m_active(true) 
    , m_date(NOW)
    , m_item(item) {}

  void print(FILE * file) {
    if (m_active)
      fmt::print(file, "{} - {}", m_date, m_item.str());
  }

  void print() {
    if (m_active) {
      FILE *file = fopen(fmt::format("incident_{}{}", m_date, Item::log_type()).c_str(), "w");
      fmt::print(file, "{}", m_item.str());
      fclose(file);
    }
  }

};

template<class Item, int N>
class CircularBufferNoPop {
public:
  CircularBufferNoPop() { clear(); }
  ~CircularBufferNoPop() {}

  void push(const Item & item) {
    m_data[advance()] = WrapperItem<Item>(item);
  }

  void flushOnOneFile() {
    FILE * file = fopen(fmt::format("incident_{}{}", NOW, Item::log_type()).c_str(), "w");
    int start = m_iter;
    do { m_data[advance()].print(file); } while (start != m_iter);
    clear();
    fclose(file);
  }

  void flushOnSeveralFiles() {
    int start = m_iter;
    do { m_data[advance()].print(); } while (start != m_iter);
    clear();
  }

  /* disable copy/move assignment operator and copy/move constructor */
  CircularBufferNoPop(const CircularBufferNoPop &) = delete;
  CircularBufferNoPop(CircularBufferNoPop &&) = delete;
  CircularBufferNoPop & operator = (const CircularBufferNoPop &) = delete;
  CircularBufferNoPop & operator = (CircularBufferNoPop &&) = delete;

protected:
  WrapperItem<Item> m_data[N];
  int               m_iter = -1;

  int advance() {
    m_iter = (m_iter + 1) % N;
    return m_iter;
  }

  void clear() {
    for (int i = 0; i < N; ++i)
      m_data[i] = WrapperItem<Item>();
  }
};

