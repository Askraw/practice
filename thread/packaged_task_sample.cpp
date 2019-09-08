#include <functional>
#include <future>
#include <iostream>

int main() {
  //! sleeps for one second and returns 1
  auto sleep = []() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 1;
  };

  //
  // Case 1: packaged_task
  //
  std::packaged_task<int()> task(sleep);
  auto f1 = task.get_future();
  auto start = std::chrono::high_resolution_clock::now();
  task();  // invoke the function
  auto stop = std::chrono::high_resolution_clock::now();

  // You have to wait until task returns. Since task calls sleep
  // you will have to wait at least 1 second.
  std::cout << "You can see this after "
            << std::chrono::duration<double>(stop - start).count()
            << " second\n";
  // However, f.get() will be available, since task has already finished.
  std::cout << f1.get() << std::endl;

  //
  // Case 2: async    人如其名 async 就是 get的是哈异步调用这个async绑定的func 而 task需要手动去invoke
  //
  auto f2 = std::async(std::launch::async, sleep);
  std::cout << "You can see this immediately!\n";

  // However, the value of the future will be available after sleep has finished
  // so f.get() can block up to 1 second.
  start = std::chrono::high_resolution_clock::now();
  auto result = f2.get();
  stop = std::chrono::high_resolution_clock::now();
  // you will have to wait at least 1 second.
  std::cout << "You can see " << result << " after "
            << std::chrono::duration<double>(stop - start).count()
            << " second\n";

  return 0;
}
