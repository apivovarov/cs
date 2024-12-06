#include <list>
#include <unordered_map>
#include <iostream>

template <typename Key, typename Value>
struct LruCache {
  struct Node {
    Value val;
    std::list<Key>::iterator it;
  };
  struct ConstRes {
    const Value* vPtr;
    ConstRes(Value* _vPtr) : vPtr(_vPtr) {}
    const Value& operator*() const { return *vPtr; }
    const Value* operator->() const { return vPtr; }
    bool operator==(const ConstRes& other) const { return vPtr == other.vPtr; }
    bool operator!=(const ConstRes& other) const { return vPtr != other.vPtr; }
  };
  ConstRes not_found() const { return ConstRes(nullptr); }
  std::list<Key> li;
  std::unordered_map<Key, Node> map;
  const size_t capacity;
  LruCache(size_t _capacity) : map(_capacity), capacity(_capacity) {}

  void add(const Key& key, const Value& val) {
    auto map_it = map.find(key);
    if (map_it != map.end()) {
      map_it->second.val = val;
      li.erase(map_it->second.it);
      map_it->second.it = li.insert(li.begin(), key);
      return;
    }
    if (map.size() == capacity) {
      pop();
    }
    auto it = li.insert(li.begin(), key);
    map.emplace(key, Node{val, it});
  }

  void pop() {
    if (map.empty()) return;
    Key key = li.back();
    li.pop_back();
    map.erase(key);
  }

  ConstRes get(const Key& key) {
    auto map_it = map.find(key);
    if (map_it == map.end()) {
      return not_found();
    }
    Node& n = map_it->second;
    li.erase(n.it);
    n.it = li.insert(li.begin(), key);
    return ConstRes(&(n.val));
  }

  void dump_li() const {
    for (auto v : li) {
      std::cout << v << ",";
    }
    std::cout << std::endl;
  }

  void dump_map() const {
    for (auto v : map) {
      std::cout << v.first << ":" << v.second.val << ", ";
    }
    std::cout << std::endl;
  }
};

int main() {
  LruCache<std::string, std::string> cache(3);
  cache.add("1", "One");
  cache.add("2", "Two");
  cache.add("3", "Three");
  cache.add("4", "Four");
  cache.add("2", "Two_2");

  cache.dump_li();
  cache.dump_map();

  std::vector<std::string> keys = {"2", "4", "1", "3"};
  for (auto k : keys) {
    auto res = cache.get(k);
    if (res != cache.not_found()) {
      std::cout << k << ":" << *res << std::endl;
    } else {
      std::cout << k << ": not found" << std::endl;
    }
  }
  cache.dump_li();
}
