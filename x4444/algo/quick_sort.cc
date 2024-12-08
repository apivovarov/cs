#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int low, int high) {
  int piv_id = low + std::rand() % (high - low);
  std::swap(arr[piv_id], arr[high - 1]);
  int piv = arr[high - 1];
  int i = low - 1;
  for (int j = low; j < high - 1; ++j) {
    if (arr[j] < piv) {
      std::swap(arr[++i], arr[j]);
    }
  }
  std::swap(arr[++i], arr[high - 1]);
  return i;
}

void _qsort(std::vector<int>& arr, int low, int high) {
  int sz = high - low;
  if (sz < 2) return;
  int piv = partition(arr, low, high);
  _qsort(arr, low, piv);
  _qsort(arr, piv + 1, high);
}

void qsort(std::vector<int>& arr) {
  int low = 0;
  int high = arr.size();
  _qsort(arr, low, high);
}

int main2() {
  std::vector<int> a = {1, 5, 9,  4,  2,  10, 3, 1, 5,  9, 2, 9,
                        6, 2, 12, 11, 5,  2,  2, 9, 9,  4, 2, 1,
                        6, 7, 11, 10, 12, 8,  1, 0, -4, 1, 9};
  qsort(a);
  for (const auto& v : a) std::cout << v << ",";
  std::cout << std::endl;
  return 0;
}

int main() {
  std::vector<int> a;
  a.reserve(1024);
  int num;
  while (std::cin >> num) {
    a.push_back(num);
  }
  // std::vector<int> b = a;

  std::cerr << "size: " << a.size() << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  qsort(a);
  // std::sort(a.begin(), a.end());
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cerr << "Execution time: " << duration.count() << " micro sec"
            << std::endl;

  // std::sort(b.begin(), b.end());
  // std::cerr << std::boolalpha << (a == b);

  std::cout << "min/max: " << a.front() << ".." << a.back() << std::endl;

  // for (const auto & v : a)
  //   std::cout<< v << ",";
  // std::cout<<std::endl;
  return 0;
}
