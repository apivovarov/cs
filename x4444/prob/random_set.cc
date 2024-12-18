#include <iostream>
#include <unordered_set>
#include <list>
#include <cstdlib>
#include <ctime>

class RandomizedSet {
 public:
  std::unordered_set<int> ss;

  RandomizedSet() : ss(16) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
  }

  bool insert(int val) {
    auto res = ss.insert(val);
    return res.second;
  }

  bool remove(int val) {
    size_t res = ss.erase(val);
    return res;
  }

  int getRandom() {
    auto it = ss.begin();
    int n = std::rand() % ss.size();
    std::advance(it, n);
    return *it;
  }
};

class RandomizedSet2 {
  std::vector<std::list<int>> ss;

 public:
  inline int hh(int val) { return std::abs(val) % ss.size(); }
  int sz = 0;

  RandomizedSet2() : ss(1){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
  };

  bool contains(const std::list<int>& li, int val) {
    for (int v : li) {
      if (val == v) return true;
    }
    return false;
  }

  void grow() {
    int sz2 = ss.size() * 2;
    std::vector<std::list<int>> ss2(sz2);
    for (int n = 0; n < ss.size(); ++n) {
      for (int val : ss[n]) {
        ss2[std::abs(val) % sz2].push_front(val);
      }
    }
    ss = std::move(ss2);
  }

  bool insert(int val) {
    int id = hh(val);
    std::list<int>& li = ss[id];
    if (contains(li, val)) return false;
    if (sz == ss.size()) {
      grow();
      return insert(val);
    }
    li.push_front(val);
    ++sz;
    return true;
  }

  bool remove(int val) {
    int id = hh(val);
    std::list<int>& li = ss[id];
    auto it = li.begin();
    for (; it != li.end(); ++it) {
      if (*it == val) {
        li.erase(it);
        --sz;
        return true;
      }
    }
    return false;
  }

  int getRandom() {
    int n = std::rand() % ss.size();
    while (true) {
      const auto& li = ss[n++];
      if (!li.empty()) {
        n = std::rand() % li.size();
        auto it = li.begin();
        std::advance(it, n);
        return *it;
      }
      n %= ss.size();
    }
  }

  std::ostream& operator<<(std::ostream& os) {
    int n = 0;
    for (; n < ss.size(); ++n) {
      bool f = false;
      for (int v : ss[n]) {
        f = true;
        os << v << ",";
      }
      if (f) os << std::endl;
    }
    return os;
  }
};



int main() {
  RandomizedSet rs;
  std::vector<std::string> tasks = {"RandomizedSet","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","getRandom","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove","remove"};
  std::vector<std::vector<int>> args = {{},{1000000000},{1000000001},{1000000002},{1000000003},{1000000004},{1000000005},{1000000006},{1000000007},{1000000008},{1000000009},{1000000010},{1000000011},{1000000012},{1000000013},{1000000014},{1000000015},{1000000016},{1000000017},{1000000018},{1000000019},{1000000020},{1000000021},{1000000022},{1000000023},{1000000024},{1000000025},{1000000026},{1000000027},{1000000028},{1000000029},{1000000030},{1000000031},{1000000032},{1000000033},{1000000034},{1000000035},{1000000036},{1000000037},{1000000038},{1000000039},{1000000040},{1000000041},{1000000042},{1000000043},{1000000044},{1000000045},{1000000046},{1000000047},{1000000048},{1000000049},{1000000050},{1000000051},{1000000052},{1000000053},{1000000054},{1000000055},{1000000056},{1000000057},{1000000058},{1000000059},{1000000060},{1000000061},{1000000062},{1000000063},{1000000064},{1000000065},{1000000066},{1000000067},{1000000068},{1000000069},{1000000070},{1000000071},{1000000072},{1000000073},{1000000074},{1000000075},{1000000076},{1000000077},{1000000078},{1000000079},{1000000080},{1000000081},{1000000082},{1000000083},{1000000084},{1000000085},{1000000086},{1000000087},{1000000088},{1000000089},{1000000090},{1000000091},{1000000092},{1000000093},{1000000094},{1000000095},{1000000096},{1000000097},{1000000098},{1000000099},{-1000000000},{-1000000001},{-1000000002},{-1000000003},{-1000000004},{-1000000005},{-1000000006},{-1000000007},{-1000000008},{-1000000009},{-1000000010},{-1000000011},{-1000000012},{-1000000013},{-1000000014},{-1000000015},{-1000000016},{-1000000017},{-1000000018},{-1000000019},{-1000000020},{-1000000021},{-1000000022},{-1000000023},{-1000000024},{-1000000025},{-1000000026},{-1000000027},{-1000000028},{-1000000029},{-1000000030},{-1000000031},{-1000000032},{-1000000033},{-1000000034},{-1000000035},{-1000000036},{-1000000037},{-1000000038},{-1000000039},{-1000000040},{-1000000041},{-1000000042},{-1000000043},{-1000000044},{-1000000045},{-1000000046},{-1000000047},{-1000000048},{-1000000049},{-1000000050},{-1000000051},{-1000000052},{-1000000053},{-1000000054},{-1000000055},{-1000000056},{-1000000057},{-1000000058},{-1000000059},{-1000000060},{-1000000061},{-1000000062},{-1000000063},{-1000000064},{-1000000065},{-1000000066},{-1000000067},{-1000000068},{-1000000069},{-1000000070},{-1000000071},{-1000000072},{-1000000073},{-1000000074},{-1000000075},{-1000000076},{-1000000077},{-1000000078},{-1000000079},{-1000000080},{-1000000081},{-1000000082},{-1000000083},{-1000000084},{-1000000085},{-1000000086},{-1000000087},{-1000000088},{-1000000089},{-1000000090},{-1000000091},{-1000000092},{-1000000093},{-1000000094},{-1000000095},{-1000000096},{-1000000097},{-1000000098},{-1000000099},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{1000000000},{1000000001},{1000000002},{1000000003},{1000000004},{1000000005},{1000000006},{1000000007},{1000000008},{1000000009},{1000000010},{1000000011},{1000000012},{1000000013},{1000000014},{1000000015},{1000000016},{1000000017},{1000000018},{1000000019},{1000000020},{1000000021},{1000000022},{1000000023},{1000000024},{1000000025},{1000000026},{1000000027},{1000000028},{1000000029},{1000000030},{1000000031},{1000000032},{1000000033},{1000000034},{1000000035},{1000000036},{1000000037},{1000000038},{1000000039},{1000000040},{1000000041},{1000000042},{1000000043},{1000000044},{1000000045},{1000000046},{1000000047},{1000000048},{1000000049},{1000000050},{1000000051},{1000000052},{1000000053},{1000000054},{1000000055},{1000000056},{1000000057},{1000000058},{1000000059},{1000000060},{1000000061},{1000000062},{1000000063},{1000000064},{1000000065},{1000000066},{1000000067},{1000000068},{1000000069},{1000000070},{1000000071},{1000000072},{1000000073},{1000000074},{1000000075},{1000000076},{1000000077},{1000000078},{1000000079},{1000000080},{1000000081},{1000000082},{1000000083},{1000000084},{1000000085},{1000000086},{1000000087},{1000000088},{1000000089},{1000000090},{1000000091},{1000000092},{1000000093},{1000000094},{1000000095},{1000000096},{1000000097},{1000000098},{1000000099},{-1000000000},{-1000000001},{-1000000002},{-1000000003},{-1000000004},{-1000000005},{-1000000006},{-1000000007},{-1000000008},{-1000000009},{-1000000010},{-1000000011},{-1000000012},{-1000000013},{-1000000014},{-1000000015},{-1000000016},{-1000000017},{-1000000018},{-1000000019},{-1000000020},{-1000000021},{-1000000022},{-1000000023},{-1000000024},{-1000000025},{-1000000026},{-1000000027},{-1000000028},{-1000000029},{-1000000030},{-1000000031},{-1000000032},{-1000000033},{-1000000034},{-1000000035},{-1000000036},{-1000000037},{-1000000038},{-1000000039},{-1000000040},{-1000000041},{-1000000042},{-1000000043},{-1000000044},{-1000000045},{-1000000046},{-1000000047},{-1000000048},{-1000000049},{-1000000050},{-1000000051},{-1000000052},{-1000000053},{-1000000054},{-1000000055},{-1000000056},{-1000000057},{-1000000058},{-1000000059},{-1000000060},{-1000000061},{-1000000062},{-1000000063},{-1000000064},{-1000000065},{-1000000066},{-1000000067},{-1000000068},{-1000000069},{-1000000070},{-1000000071},{-1000000072},{-1000000073},{-1000000074},{-1000000075},{-1000000076},{-1000000077},{-1000000078},{-1000000079},{-1000000080},{-1000000081},{-1000000082},{-1000000083},{-1000000084},{-1000000085},{-1000000086},{-1000000087},{-1000000088},{-1000000089},{-1000000090},{-1000000091},{-1000000092},{-1000000093},{-1000000094},{-1000000095},{-1000000096},{-1000000097},{-1000000098},{-1000000099}};

//   for (int i =0; i < 130 ; ++i) {
//     if (tasks[i] == "insert") {
//        std::cout << "ins "<<  i <<":" << rs.insert(args[i][0]) << ",";
//     } else if (tasks[i] == "remove") {
//        std::cout << "rm " << i << ":" << rs.remove(args[i][0]) << ",";
//     } else if (tasks[i] == "getRandom") {
//        std::cout << "get "<< i << ":" << rs.getRandom() << ",";
//     }
//   }

   std::cout << rs.insert(1) << ",";
   std::cout << rs.insert(10) << ",";
   std::cout << rs.insert(20) << ",";
   std::cout << rs.insert(30) << ",";
   std::cout << std::endl;
   for (int i = 0 ; i < 100; ++i) {
     std::cout << rs.getRandom() << ",";
   }
   std::cout << std::endl;

//   std::cout << rs.insert(4) << ",";
//   std::cout << rs.insert(50000) << ",";
//   std::cout << rs.insert(4) << ",";
//   //std::cout << rs.remove(4) << ",";
//   //std::cout << rs.remove(60000) << ",";
//   std::cout << rs.insert(40004) << ",";
//   std::cout << rs.insert(80009) << ",";
//   std::cout << rs.insert(180006) << ",";
//   std::cout << rs.insert(110012) << ",";
//   std::cout << rs.insert(130004) << ",";
//   std::cout << rs.insert(170001) << ",";
//   std::cout << rs.insert(7) << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";

//   std::cout << std::endl;
//   rs<< std::cout;
//   std::cout << std::endl;
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
//   std::cout << rs.getRandom() << ",";
}
