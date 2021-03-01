#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>

#include <iostream>

#include <algorithm>

// microseconds
inline int64_t GetCurrentTimePointStamp() {
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

struct TimerTask {
  int64_t next_invoke_timestamp;  // 下一次运行的时间戳
  int64_t period;                 // 正值表示这是一个周期任务
  std::function<void()> task;     //类似C中的函数指针
};

// 重载 >
bool operator>(const TimerTask& task1, const TimerTask& task2) {
  return task1.next_invoke_timestamp > task2.next_invoke_timestamp;
};

class Timer {
 public:
  Timer(){};
  // 添加从当前时间戳延迟 x 秒后仅调用一次的任务，延迟时间不应小于0秒，调用完成后删除
  void AddTaskOneShot(int64_t current_timestamp, std::function<void()> task, float delay_seconds = 0) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    task_list_.push(
      TimerTask{
        .next_invoke_timestamp = current_timestamp + static_cast<int64_t>(delay_seconds * 1e6),
        .period = -1,
        .task = task,
      });
  };
  // 添加在周期 x 秒内调用的任务，永远是周期性的，x > 0；
  void AddTaskPeriod(int64_t current_timestamp, float period_seconds, std::function<void()> task, float delay_seconds = -1) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    task_list_.push(
      TimerTask{
        .next_invoke_timestamp = current_timestamp +
                               (delay_seconds >= 0 ? static_cast<int64_t>(delay_seconds * 1e6):
                                                     static_cast<int64_t>(period_seconds * 1e6)),
        .period = static_cast<int64_t>(period_seconds * 1e6),
        .task = task,
      });
  };
  void ClearAllTasks() {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    while (!task_list_.empty()) {
      task_list_.pop();
    }
  };
  void ExecuteOneTime(int64_t current_timestamp) {
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    while (!task_list_.empty() && task_list_.top().next_invoke_timestamp <= current_timestamp) {
      TimerTask task = task_list_.top();
      task.task();
      task_list_.pop();
      if (task.period > 0) {
        // 如果是周期性任务，重新push进入list
        task.next_invoke_timestamp += task.period;
        task_list_.push(task);
      }
    }
  }

 private:
  std::priority_queue<TimerTask, std::vector<TimerTask>, std::greater<TimerTask>> task_list_;
  // use recursive mutex to allow multiple times lock in same thread
  mutable std::recursive_mutex mutex_;
};

void test1() {
  std::cout << "Test1, TimeStamp：" << GetCurrentTimePointStamp() << "\n";
}

void test2() {
  std::cout << "Test2, TimeStamp：" << GetCurrentTimePointStamp() << "\n";
}

int main() {
  Timer timer_;
  int64_t time_stamp = GetCurrentTimePointStamp();
  timer_.AddTaskOneShot(time_stamp, test1);
  timer_.AddTaskPeriod(time_stamp, 0.1, test2);
  while (true) {
    time_stamp = GetCurrentTimePointStamp();
    timer_.ExecuteOneTime(time_stamp);
  }
  return 0;
}