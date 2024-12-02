#include <iostream>
#include <algorithm>
#include <array>

template <typename T>
void merge(T* dest, T* b, int bsz, T* c, int csz) {
  int i = 0;
  int bid = 0;
  int cid = 0;
  bool bdone = false;
  bool cdone = false;

  while (true) {
    if (!bdone && (cdone || b[bid] < c[cid])) {
      dest[i++] = b[bid++];
      bdone = bid >= bsz;
    } else if (!cdone) {
      dest[i++] = c[cid++];
      cdone = cid >= csz;
    } else {
      break;
    }
  }
}

template <typename T>
void _sort(T* a, int sz, T* tmp) {
  if (sz <= 1) return;
  // divide a in two parts
  T* b = a;
  int bsz = (sz + 1) / 2;
  T* c = a + bsz;
  int csz = sz - bsz;
  // sort both parts
  _sort(b, bsz, tmp);
  _sort(c, csz, tmp + bsz);
  // merge sorted parts into tmp buffer
  merge(tmp, b, bsz, c, csz);
  // copy sorted tmp array back to a
  std::copy(tmp, tmp + sz, a);
}

template <typename T>
void sort(T* a, int sz) {
  if (sz <= 0) return; // Handle edge case
  T* tmp = new T[sz];
  _sort(a, sz, tmp);
  delete[] tmp;
}

int main() {
  std::array<float, 17> a = {5.,  1., 8., 33.3, 3., 9.1, 4.,   1.,  -4.2,
                             -7., 7., 8., 5.5,  2., 6.,  18.3, 4.44};
  sort(a.data(), a.size());

  for (const auto& v : a) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
