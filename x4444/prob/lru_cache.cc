#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
  struct E {
    std::list<int>::iterator it;
    int v;
  };

  int cap;
  std::list<int> li;
  std::unordered_map<int, E> map;

 public:
  LRUCache(int capacity) : cap(capacity) { map.reserve(capacity); }

  int get(int key) {
    auto mit = map.find(key);
    if (mit == map.end()) return -1;
    if (mit->second.it != li.begin()) {
      li.erase(mit->second.it);
      li.push_front(key);
      mit->second.it = li.begin();
    }
    return mit->second.v;
  }

  void put(int key, int value) {
    auto mit = map.find(key);
    if (mit == map.end()) {
      if (map.size() == cap) {
        map.erase(li.back());
        li.pop_back();
      }
      li.push_front(key);
      map.emplace(key, E{li.begin(), value});
    } else {
      if (mit->second.it != li.begin()) {
        li.erase(mit->second.it);
        li.push_front(key);
        mit->second.it = li.begin();
      }
      mit->second.v = value;
    }
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

void test(int res, int exp) {
  if (res != exp) {
    std::cerr << "ERROR: res: " << res << ", exp: " << exp << std::endl;
  }
}

int main() {
  LRUCache lRUCache(2);
  lRUCache.put(1, 1);        // cache is {1=1}
  lRUCache.put(2, 2);        // cache is {1=1, 2=2}
  test(lRUCache.get(1), 1);  // return 1
  lRUCache.put(3, 3);        // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  test(lRUCache.get(2), -1);  // returns -1 (not found)
  lRUCache.put(4, 4);  // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  test(lRUCache.get(1), -1);  // return -1 (not found)
  test(lRUCache.get(3), 3);   // return 3
  test(lRUCache.get(4), 4);   // return 4
}
