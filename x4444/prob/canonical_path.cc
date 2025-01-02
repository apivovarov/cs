#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Solution {
 public:
  std::string simplifyPath(const std::string& path) {
    if (path.size() < 2) return path;
    std::vector<std::string> st;
    {
      std::istringstream ss(path);
      std::string s;
      while (std::getline(ss, s, '/')) {
        if (s.empty() || s == ".") {
          // do nothing
        } else if (s == "..") {
          if (!st.empty()) st.pop_back();
        } else {
          st.push_back(s);
        }
      }
    }

    if (st.empty()) return "/";
    std::string res;
    for (const std::string& s : st) {
      res.push_back('/');
      res.append(s);
    }
    return res;
  }
};

void test(const std::string& s, const std::string& expected) {
  Solution sol;
  std::string res = sol.simplifyPath(s);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("/", "/");
  test("/foo", "/foo");
  test("/foo/", "/foo");
  test("/foo/..", "/");
  test("/foo/../bar/", "/bar");
  test("/foo/./bar/", "/foo/bar");
  test("/foo/./bar/../../buzz/", "/buzz");
  test("/foo/.../bar/", "/foo/.../bar");
  test("/../", "/");
  test("/foo//bar/", "/foo/bar");
  test("/foo///bar/", "/foo/bar");
}
