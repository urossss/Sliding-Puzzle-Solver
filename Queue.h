#ifndef _QUEUE_H_
#define _QUEUE_H_

class Queue {
	struct QueueNode {
		void *ptr;
		QueueNode *next;
		QueueNode(void *p) {
			ptr = p;
			next = nullptr;
		}
	};
	QueueNode *front, *rear;
public:
	Queue() {
		front = rear = nullptr;
	}
	~Queue() {
		while (front) {
			QueueNode *old = front;
			front = front->next;
			delete old;
		}
		rear = nullptr;
	}
	bool empty() {
		return front == nullptr;
	}
	void insert(void *p) {
		rear = (!front ? front : rear->next) = new QueueNode(p);
	}
	void* remove() {
		if (front) {
			void *p = front->ptr;
			front = front->next;
			if (!front) {
				rear = nullptr;
			}
			return p;
		}
		return nullptr;
	}
};

#endif