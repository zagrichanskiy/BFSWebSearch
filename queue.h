#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <QMutex>
#include <QWaitCondition>
#include <atomic>
#include <memory>

template<typename T>
class Queue
{
private:
	mutable QMutex mutex;
	std::queue<T *> queue;
	QWaitCondition condition;
	std::atomic_bool done;
public:
	Queue();

	void push(T *value);
	T *wait_and_pop();
	int size() const;
	bool empty() const;
	void release();
	void clear();
};

template<typename T>
Queue<T>::Queue()
	: done(false)
{}

template<typename T>
void Queue<T>::push(T *value)
{
	T *data  = value;
	QMutexLocker lk(&mutex);
	queue.push(data);
	condition.wakeOne();
}

template<typename T>
T *Queue<T>::wait_and_pop()
{
	mutex.lock();
	if (queue.empty()) {
		condition.wait(&mutex);
	}
	if (done) {
		mutex.unlock();
		return nullptr;
	}

	T *data = queue.front();
	queue.pop();
	mutex.unlock();
	return data;
}

template<typename T>
int Queue<T>::size() const
{
	QMutexLocker lk(&mutex);
	return queue.size();
}

template<typename T>
bool Queue<T>::empty() const
{
	QMutexLocker lk(&mutex);
	return queue.empty();
}

template<typename T>
void Queue<T>::release()
{
	done = true;
	condition.wakeAll();
}

template<typename T>
void Queue<T>::clear()
{
	QMutexLocker lk(&mutex);
	done = false;
	queue = std::queue<T *>();
}

#endif // QUEUE_H
