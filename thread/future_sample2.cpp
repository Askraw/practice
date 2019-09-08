// future example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

// a non-optimized way of checking for prime numbers:
bool is_prime (int x) {
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}

int main ()
{
  // call function asynchronously:
  std::future<bool> fut = std::async (is_prime,444444443); 

  // do something while waiting for function to set future:
  std::cout << "checking, please wait" << std::endl;
  std::chrono::milliseconds span (500);
//   while (fut.wait_for(span)==std::future_status::timeout)
//     std::cout << '!' << std::endl;
  if(fut.wait_for(span) == std::future_status::deferred) std::cout << "test success!\n";
  bool x = fut.get();     // retrieve return value

  std::cout << "\n444444443 " << (x?"is":"is not") << " prime.\n";

    std::promise<int> pro;

  std::future<int> f2 = pro.get_future();
  while (f2.wait_for(span)==std::future_status::timeout)
    std::cout << '!' << std::flush;
    pro.set_value(10);
    
    std::cout << f2.get() << std::endl;
  return 0;
}