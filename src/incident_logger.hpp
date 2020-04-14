
#pragma once

#include "circular_buffer_nopop.hpp"

class LogRow {
protected:
  int         m_category;
  std::string m_what;
public:
  LogRow()
    : m_category(0)
    , m_what("") {}
  
  LogRow(int category, const std::string & what)
    : m_category(category)
    , m_what(what) {}
  
  static std::string log_type() {
    return ".log";
  }

  std::string str() {
    std::stringstream ss;
    ss << m_category << " - " << m_what << "\n";
    return ss.str();
  }
};

template <int N>
class IncidentLogger : protected CircularBufferNoPop<LogRow, N> {
private:
public:
  IncidentLogger() {}

  void push(int category, const std::string & what) {
    CircularBufferNoPop<LogRow, N>::push(LogRow(category, what));
  }

  void flush() {
    CircularBufferNoPop<LogRow, N>::flushOnOneFile();
  }
};


