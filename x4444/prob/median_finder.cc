#include <iostream>
#include <queue>
#include <cmath>

// 295. Find Median from Data Stream
class MedianFinder {
  // top is largest
  std::priority_queue<int> leftq;
  // top is smallest
  std::priority_queue<int, std::vector<int>, std::greater<int>> rightq;

 public:
  MedianFinder() {
    leftq.push(std::numeric_limits<int>::min());
    rightq.push(std::numeric_limits<int>::max());
  }

  void addNum(int num) {
    if (num < leftq.top())
      leftq.push(num);
    else
      rightq.push(num);
    int rsz = rightq.size();
    int lsz = leftq.size();
    // rebalance
    while (std::abs(rsz - lsz) > 1) {
      if (rsz > lsz) {
        leftq.push(rightq.top());
        rightq.pop();
      } else {
        rightq.push(leftq.top());
        leftq.pop();
      }
      rsz = rightq.size();
      lsz = leftq.size();
    }
  }

  double findMedian() {
    int rsz = rightq.size();
    int lsz = leftq.size();
    if (rsz == lsz) {
      return (leftq.top() + rightq.top()) / 2.0;
    } else if (rsz > lsz) {
      return rightq.top();
    } else {
      return leftq.top();
    }
  }
};

int main() {
  {
    MedianFinder mf;
    mf.addNum(2);
    mf.addNum(1);
    std::cerr << std::boolalpha << (mf.findMedian() == 1.5) << std::endl;
    mf.addNum(3);
    std::cerr << std::boolalpha << (mf.findMedian() == 2) << std::endl;
  }

  {
    MedianFinder mf;
    mf.addNum(20);
    mf.addNum(10);
    mf.addNum(40);
    mf.addNum(30);
    std::cerr << std::boolalpha << (mf.findMedian() == 25.0) << std::endl;
    mf.addNum(70);
    mf.addNum(60);
    mf.addNum(50);
    mf.addNum(80);
    mf.addNum(90);
    std::cerr << std::boolalpha << (mf.findMedian() == 50) << std::endl;
  }
}
