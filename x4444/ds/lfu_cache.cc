#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

template <typename Key, typename Value>
struct LfuCache {
  struct MapNode {
    Value val;
    std::multimap<size_t, Key>::iterator it;
  };
  const size_t cap;
  std::multimap<size_t, Key> freq_map;
  std::unordered_map<Key, MapNode> map;
  LfuCache(size_t _cap) : cap(_cap), map(_cap) {}

  void update_freq_(std::unordered_map<Key, MapNode>::iterator& map_it) {
    auto key = map_it->first;
    auto freq_map_it = map_it->second.it;
    size_t freq = freq_map_it->first;
    freq_map.erase(freq_map_it);
    ++freq;
    map_it->second.it = freq_map.emplace(freq, key);
  }

  void add(Key key, Value val) {
    auto map_it = map.find(key);
    if (map_it != map.end()) {
      // update
      update_freq_(map_it);
      map_it->second.val = val;
      return;
    }
    if (map.size() == cap) {
      pop();
    }
    auto freq_map_it = freq_map.emplace(1, key);
    map.emplace(key, MapNode(val, freq_map_it));
  }

  void pop() {
    if (map.empty()) return;
    auto freq_map_it = freq_map.begin();
    map.erase(freq_map_it->second);
    freq_map.erase(freq_map_it);
  }

  const Value* get(const Key& key) {
    auto map_it = map.find(key);
    if (map_it == map.end()) {
      return nullptr;
    }
    update_freq_(map_it);
    return &map_it->second.val;
  }

  void dump_freq_map() const {
    for (auto v : freq_map) {
      std::cerr << v.second << ":" << v.first << ", ";
    }
    std::cerr << std::endl;
  }

  void dump_map() const {
    for (auto v : map) {
      std::cerr << v.first << ":" << v.second.val << ", ";
    }
    std::cerr << std::endl;
  }
};

int main() {
  LfuCache<std::string, std::string> cache(2);

  cache.add("k1", "One");
  cache.add("k4", "Four");
  cache.add("k2", "Two");
  cache.add("k3", "Three");
  cache.add("k2", "Two");
  cache.add("k3", "Three2");
  cache.dump_freq_map();
  cache.dump_map();

  for (int i = 0; i < 10; ++i) {
    for (auto k : {"k1", "k4", "k3"}) {
      const auto* v = cache.get(k);
      if (v) {
        std::cerr << "get(" << k << "): " << *v << std::endl;
      } else {
        std::cerr << "get(" << k << "): not found" << std::endl;
      }
    }
  }

  cache.dump_freq_map();
  cache.dump_map();

  std::cerr << "add(k9)" << std::endl;
  cache.add("k9", "Nine");
  cache.dump_freq_map();
  cache.dump_map();

  std::cerr << "pop()" << std::endl;
  cache.pop();
  cache.dump_freq_map();
  cache.dump_map();
}
