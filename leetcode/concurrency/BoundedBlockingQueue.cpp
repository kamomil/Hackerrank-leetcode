#include <mutex>
#include <queue>
#include <condition_variable>


class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) {
        capacity_ = capacity;
    }

    void enqueue(int element) {
        {
            std::unique_lock<std::mutex> lk(m_);
            cv_.wait(lk, [this](){
                return q_.size() < capacity_;
            });
            q_.push(element);
        }
        cv_.notify_all();
    }

  int dequeue() {
        int e;
        {
            std::unique_lock<std::mutex> lk(m_);
            cv_.wait(lk, [this](){
                return q_.size() > 0;
            });
            e = q_.front();
            q_.pop();
        }
        cv_.notify_all();
        return e;
    }

    int size() {
        std::lock_guard<std::mutex> lk(m_);
        return q_.size();
    }
private:
  std::queue<int> q_;
  std::mutex m_;
  std::condition_variable cv_;
  int capacity_;
};

int main()
{
  return 0;
}
