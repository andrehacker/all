#include <deque>
#include <mutex>
#include <functional>
#include <condition_variable>

template<class T>
class SafeQueue {

public:
	
	// Constructor, explicit
	explicit SafeQueue(std::size_t capacity) : capacity_(capacity) {}
	
	void push_front(T item) {
		// create/aquire lock first (on mutex)
		std::unique_lock<std::mutex> lock(mutex_);
		
		// Check condition variable:
		// - will wait if predicate is false (and free lock I guess?!)
		// - returns and re-aquires lock if someone calls notify on condition variable
		// ??bind??
		not_full_.wait(lock, std::bind(&SafeQueue<T>::is_not_full, this));
		
		// exclusive access
		container_.push_front(item);
		
		lock.unlock();
		not_empty_.notify_one();
	}
	
	void pop_back(T* pItem) {
		std::unique_lock<std::mutex> lock(mutex_);
		
		not_empty_.wait(lock, std::bind(&SafeQueue<T>::is_not_empty, this));
		
		*pItem = container_.back();
		container_.pop_back();
		
		lock.unlock();
		not_full_.notify_one();
	}
	
	int get_full_count() {
		return full_count_;
	}
	
	int get_empty_count() {
		return empty_count_;
	}
	
private:
	
	// Disable copy constructor
	SafeQueue(const SafeQueue&) = delete;
	// Disable assign operator
	SafeQueue& operator=(const SafeQueue&) = delete;
	
	std::deque<T> container_;
	const std::size_t capacity_;
	std::mutex mutex_;
	
	// debug
	int full_count_, empty_count_;
	
	// predicates for condition variables
	// TODO: removed const...
	bool is_not_empty() {
		if (container_.size() <= 0) {
			++empty_count_;
			return false;
		}
		return true;
	}
	bool is_not_full() {
		if (container_.size() >= capacity_) {
			++full_count_;
			return false;
		}
		return true;
	}
	
	// condition variables
	std::condition_variable not_empty_;
	std::condition_variable not_full_;
	
};
