#include <iostream>
#include <string>
#include <vector>

class Solution {
 public:
  std::vector<int> getSpaces(int n, int width) {
    int whole = width / n;
    int rem = width % n;
    std::vector<int> res;
    res.reserve(n);
    for (int i = 0; i < n; ++i) {
      int v = whole;
      if (rem > 0) {
        ++v;
        --rem;
      }
      res.push_back(v);
    }
    return res;
  }

  void print(std::vector<std::string>& res,
             const std::vector<std::string>& words, int b, int e, int width,
             int maxWidth) {
    if (b == e) {
      printLastLine(res, words, b, e, width, maxWidth);
      return;
    }
    int spacesN = e - b;
    int spacesW = maxWidth - (width - spacesN);
    std::vector<int> spMask = getSpaces(spacesN, spacesW);
    int i = 0;
    std::string line;
    line.reserve(maxWidth);
    while (b <= e) {
      if (!line.empty()) {
        for (int j = 0; j < spMask[i]; ++j) {
          line.push_back(' ');
        }
        ++i;
      }
      line.append(words[b]);
      ++b;
    }
    res.push_back(std::move(line));
  }

  void printLastLine(std::vector<std::string>& res,
                     const std::vector<std::string>& words, int b, int e,
                     int width, int maxWidth) {
    std::string line;
    line.reserve(maxWidth);
    while (b <= e) {
      if (!line.empty()) {
        line.push_back(' ');
      }
      line.append(words[b]);
      ++b;
    }
    while (width < maxWidth) {
      line.push_back(' ');
      ++width;
    }
    res.push_back(std::move(line));
  }

 public:
  std::vector<std::string> fullJustify(const std::vector<std::string>& words,
                                       int maxWidth) {
    int b = 0;
    int e = 0;
    std::vector<std::string> res;
    int width = words[b].size();

    while (true) {
      ++e;
      if (e == words.size()) {
        printLastLine(res, words, b, e - 1, width, maxWidth);
        break;
      }
      ++width;
      width += words[e].size();
      if (width > maxWidth) {
        width -= words[e].size();
        --width;
        --e;
        print(res, words, b, e, width, maxWidth);
        b = e + 1;
        e = e + 1;
        if (b == words.size()) break;
        width = words[b].size();
      }
    }
    return res;
  }
};

void test(const std::vector<std::string>& words, int maxWidth,
          const std::vector<std::string>& expected) {
  Solution sol;
  std::vector<std::string> res = sol.fullJustify(words, maxWidth);
  if (res != expected) {
    std::cerr << "ERROR: res: " << std::endl;
    for (const std::string& s : res) {
      std::cerr << "'" << s << "'" << std::endl;
    }
  }
}

int main() {
  // Solution sol;
  // for (auto s : sol.getSpaces(1,5)) {
  //   std::cerr << s << ",";
  // }
  // std::cerr<<std::endl;

  test({"Hello"}, 7, {"Hello  "});

  test({"Hello", "World"}, 11, {"Hello World"});
  test({"Hello", "World"}, 14, {"Hello World   "});
  test({"Hi", "Hello", "World"}, 14, {"Hi Hello World"});
  test({"Hi", "Hello", "World"}, 16, {"Hi Hello World  "});

  test({"Hi", "Hello", "World"}, 8, {"Hi Hello", "World   "});
  test({"Hi", "Hello", "World"}, 10, {"Hi   Hello", "World     "});
  test({"Hi", "Hi", "Hi", "Hello", "Hi", "Hi", "H", "Hello", "World"}, 15,
       {"Hi  Hi Hi Hello", "Hi  Hi  H Hello", "World          "});

  test({"This", "is", "an", "example", "of", "text", "justification."}, 16,
       {{"This    is    an"}, {"example  of text"}, {"justification.  "}});

  test({"What", "must", "be", "acknowledgment", "shall", "be"}, 16,
       {{"What   must   be"}, {"acknowledgment  "}, {"shall be        "}});

  test({"Science", "is", "what", "we", "understand", "well", "enough", "to",
        "explain", "to", "a", "computer.", "Art", "is", "everything", "else",
        "we", "do"},
       20,
       {{"Science  is  what we"},
        {"understand      well"},
        {"enough to explain to"},
        {"a  computer.  Art is"},
        {"everything  else  we"},
        {"do                  "}});
}
