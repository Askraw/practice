#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock, std::defer_lock

// unique lock的功能很丰富 有很多方法和属性 有点类似与 time mutex 和mutex的功能 整合到这个类里
std::mutex mtx;           // mutex for critical section

void print_star () {
  std::unique_lock<std::mutex> lck(mtx,std::defer_lock);
  // print '*' if successfully locked, 'x' otherwise: 
  if (lck.try_lock())
    std::cout << '*';
  else                    
    std::cout << 'x';
}

int main ()
{
  std::vector<std::thread> threads;
  for (int i=0; i<500; ++i)
    threads.emplace_back(print_star);

  for (auto& x: threads) x.join();

  return 0;
}