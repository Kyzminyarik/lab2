// Copyright 2021 Your Name <your_email>

#include <Exploring.hpp>
#include <algorithm>
#include <iostream>

using namespace std;

Exploring::Exploring() {
  for (size_t i= 0.5 * size_cache[0]; i < 1.5 * size_cache[2]; i*=2)
    buf_size.push_back(i);
  buf_size.push_back(1.5 * size_cache[2]);
}
Exploring::~Exploring() {}

void Exploring::direct() {
  [[maybe_unused]] int k = 0;
  variant = "direct";
  if (!experiment_time.empty()) {
    experiment_time.clear();
  }
  for (const size_t& size : buf_size) {
    int* arr= new int[size /4];
    for (size_t i= 0; i < size /4; i += 16) {//пргрев кэша
      k = arr[i];
    }
    clock_t start= clock();
    for (size_t n= 0; n < iter; n++) { //чтение
      for (size_t j= 0; j < size /4; j += 16) {
        k = arr[j];
      }
    }
    clock_t end= clock();
    experiment_time.push_back(static_cast <double> (end-start) / CLOCKS_PER_SEC * iter);
    delete[] arr;
  }
}
void Exploring::reverse() {
  [[maybe_unused]] int k = 0;
  variant = "reverse";
  if (!experiment_time.empty()) {
    experiment_time.clear();
  }
    for (const size_t& size : buf_size) { //прогрев кеша
    int* arr= new int[size /4];
    for (int i= size /4; i >= 0; i -= 16) {//прогрев кеша
      k = arr[i];
    }
    clock_t start= clock();
    for (size_t n= 0; n < iter; n++) {
      for (size_t j= size /4; j > 0; j -= 16) {
        k = arr[j];
      }
    }
    clock_t end= clock();
    experiment_time.push_back(static_cast <double> (end - start) / CLOCKS_PER_SEC * iter);
    delete[] arr;
  }
}
void Exploring::random() {
  [[maybe_unused]] int k = 0;
  variant = "random";
  if (!experiment_time.empty()) {
    experiment_time.clear();
  }
  for (const size_t& i : buf_size) {
    std::vector<size_t> rand_values;
    int* arr= new int[i/4];
    for (size_t j= 0; j < i/4; j += 16) {//прогрев кеша
      k= arr[j];
      rand_values.push_back(j);
    }
    random_shuffle(rand_values.begin(), rand_values.end());
    clock_t start= clock();
    for (size_t n= 0; n < iter; n++) {
      for (const auto& ind: rand_values)
        k= arr[ind];
    }
    clock_t end= clock();
    experiment_time.push_back(static_cast <double> (end - start) / CLOCKS_PER_SEC * iter);
    delete[] arr;
  }
}
void Exploring::print(const Exploring& c, std::ostream& os) {
  os << "investigation:\n"
     << "\ttravel_order: " << c.variant << "\n"
     << "\texperiments:\n";
  for (size_t i= 0; i < c.buf_size.size(); ++i) {
    os << "\t- experiment: \n"
       << "\t\tnumber: " << i+1 << "\n"
       << "\t\tinput_data:\n"
       << "\t\t\tbuffer_size: " << c.buf_size[i] / 1024 << " Kb\n"
       << "\t\tresults:\n"
       << "\t\t\tduration: " << c.experiment_time[i] << " ms\n";
  }
}
void experiment(){
  Exploring my_cache;
  my_cache.direct();
  my_cache.print(my_cache, cout);
  my_cache.reverse();
  my_cache.print(my_cache, cout);
  my_cache.random();
  my_cache.print(my_cache, cout);
}