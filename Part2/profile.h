#pragma once

#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
  explicit LogDuration(const string& msg = "")
    : message(msg + ": ")
    , start(high_resolution_clock::now())
  {
  }

  ~LogDuration() {
    auto finish = high_resolution_clock::now();
    auto dur = finish - start;
    cerr << message
       << duration_cast<microseconds>(dur).count()
       << " microseconds" << endl;
  }
private:
  string message;
  high_resolution_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};
