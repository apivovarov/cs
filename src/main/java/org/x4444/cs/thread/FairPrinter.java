package org.x4444.cs.thread;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class FairPrinter {
  private final Lock lock = new ReentrantLock();
  private final Condition mon = lock.newCondition();

  private int thIdDone = 2;

  public void print(int[] a, int thId) throws InterruptedException {
    if (a == null) {
      return;
    }
    for (int v : a) {
      lock.lock();
      try {
        while (thIdDone == thId) {
          mon.await();
        }
        System.out.println(v);
        thIdDone = thId;
        mon.signalAll();
      } finally {
        lock.unlock();
      }
    }
  }

  public static void main(String[] args) {
    final FairPrinter b = new FairPrinter();

    Thread t1 = new Thread() {
      public void run() {
        try {
          b.print(new int[] { 1, 3, 5, 7, 9 }, 1);
        } catch (InterruptedException e) {
          return;
        }
      }
    };

    Thread t2 = new Thread() {
      public void run() {
        try {
          b.print(new int[] { 2, 4, 6, 8 }, 2);
        } catch (InterruptedException e) {
          return;
        }
      }
    };

    t1.start();
    t2.start();
  }
}