#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>


template <typename T>
class ClinicQueue {
private:
    T* buffer;          
    int maxCapacity;     
    int head;           
    int tail;            
    int currentSize;   

public:
   
    ClinicQueue(int cap = 100) {
        if (cap <= 0) throw std::runtime_error("Capacity must be greater than 0");
        maxCapacity = cap;
        buffer = new T[maxCapacity];
        head = 0;
        tail = 0;
        currentSize = 0;
    }

    
    ~ClinicQueue() {
        delete[] buffer;
    }

    
    ClinicQueue(const ClinicQueue& other) {
        maxCapacity = other.maxCapacity;
        head = other.head;
        tail = other.tail;
        currentSize = other.currentSize;
        buffer = new T[maxCapacity]; 
        for (int i = 0; i < maxCapacity; i++) {
            buffer[i] = other.buffer[i]; 
        }
    }

  
    ClinicQueue& operator=(const ClinicQueue& other) {
        if (this == &other) return *this;
        delete[] buffer;
        maxCapacity = other.maxCapacity;
        head = other.head;
        tail = other.tail;
        currentSize = other.currentSize;
        buffer = new T[maxCapacity];
        for (int i = 0; i < maxCapacity; i++) {
            buffer[i] = other.buffer[i];
        }
        return *this;
    }

    
    void enqueue(const T& item) {
        if (isFull()) {
            throw std::runtime_error("Queue is full! Cannot add patient.");
        }
        buffer[tail] = item;
        tail = (tail + 1) % maxCapacity; 
        currentSize++;
    }

    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty! Cannot remove patient.");
        }
        T item = buffer[head];
        head = (head + 1) % maxCapacity; 
        currentSize--;
        return item;
    }


    T peekFront() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        return buffer[head];
    }

    bool isEmpty() const { return currentSize == 0; }
    bool isFull() const { return currentSize == maxCapacity; }
    int size() const { return currentSize; }

    T getAt(int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::runtime_error("Index out of bounds");
        }
        return buffer[(head + index) % maxCapacity];
    }
};

#endif