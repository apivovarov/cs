#include <vector>
#include <iostream>

int partition(std::vector<int> & arr, int low, int high) {
  int piv = arr[high - 1];
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (arr[j] < piv) {
        std::swap(arr[++i], arr[j]);
    }
  }
  std::swap(arr[++i], arr[high-1]);
  return i;
}

int main() {
    std::vector<int> a = {1,5,4,2,3};
    int piv_id = partition(a, 0, a.size());

    std::cout<< piv_id << std::endl;
    for (const auto & v : a)
      std::cout<< v << ",";
    std::cout<<std::endl;
}
