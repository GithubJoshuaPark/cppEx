#include <iostream>
#include "helloEx.h" // for printLine
#include "queue_data_structureEx.h"

// Queue 구조체를 사용하여 큐의 상태(데이터, front, rear)를 캡슐화합니다.
// 이렇게 하면 코드가 더 명확하고 관리하기 쉬워집니다.
// QUEUE_SIZE는 helloEx.h에 정의되어 있습니다.
// Queue 구조체는 helloEx.h에 정의되어 있습니다.

// 큐를 초기화하는 함수
void initializeQueue(Queue& q) {
    q.front = -1;
    q.rear = -1;
}

// 큐가 가득 찼는지 확인하는 함수
bool isFull(const Queue& q) {
    // rear의 다음 위치가 front와 같으면 큐가 가득 찬 것입니다.
    return (q.rear + 1) % QUEUE_SIZE == q.front;
}

// 큐가 비어있는지 확인하는 함수
bool isEmpty(const Queue& q) {
    return q.front == -1;
}

// 큐에 데이터를 추가하는 함수 (Enqueue)
void enqueue(Queue& q, int value) {
    if (isFull(q)) {
        std::cerr << "Queue overflow! Cannot enqueue " << value << ".\n";
        return;
    }
    if (isEmpty(q)) {
        q.front = 0; // 첫 번째 요소 추가
    }
    q.rear = (q.rear + 1) % QUEUE_SIZE;
    q.items[q.rear] = value;
    q.count++;
    std::cout << "Enqueued " << value << " to the queue.\n";
}

// 큐에서 데이터를 제거하는 함수 (Dequeue)
int dequeue(Queue& q) {
    if (isEmpty(q)) {
        std::cerr << "Queue underflow! Cannot dequeue from an empty queue.\n";
        return -1; // 오류를 나타내는 값
    }
    int dequeuedValue = q.items[q.front];
    if (q.front == q.rear) {
        // 큐에 마지막 남은 요소를 제거하면 큐는 비게 됩니다.
        initializeQueue(q);
    } else {
        q.front = (q.front + 1) % QUEUE_SIZE;
    }
    q.count--;
    std::cout << "Dequeued " << dequeuedValue << " from the queue.\n";
    return dequeuedValue;
}

void queue_data_structureEx(void) {
    printLine("Queue Data Structure Example");
    
    // Queue 구조체 인스턴스를 생성하고 초기화합니다.
    Queue myQueue;
    initializeQueue(myQueue);

    // Test the queue operations
    enqueue(myQueue, 10);
    enqueue(myQueue, 20);
    enqueue(myQueue, 30);
    enqueue(myQueue, 40);
    enqueue(myQueue, 50);
    enqueue(myQueue, 60); // 큐가 가득 차서 실패해야 함
    dequeue(myQueue);
    dequeue(myQueue);
    enqueue(myQueue, 60); // 이제 성공해야 함
    while (!isEmpty(myQueue)) {
        dequeue(myQueue);
    }
    dequeue(myQueue); // 비어있는 큐에서 dequeue 시도

    printLine("Queue Data Structure Example Completed");
}