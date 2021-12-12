// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_EXPLORING_HPP_
#define INCLUDE_EXPLORING_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const size_t iter= 1000;

class Exploring {
 private:
  string variant;
  vector <double> experiment_time;
  vector <size_t> buf_size;
  vector <size_t> size_cache = { 512 * 1024,      // L1
                              2*1024*1024,    // L2
                              12*1024*1024 };  // L3

 public:
  Exploring();
  ~Exploring();
  void direct();
  void reverse();
  void random();
  void print(const Exploring& c, ostream& os);
};
void experiment();

#endif // INCLUDE_EXPLORING_HPP_
