/*
 * CircBuffer.hpp
 *
 *  Created on: 10 февр. 2021 г.
 *      Author: user
 */

#ifndef CIRCBUFFER_H_
#define CIRCBUFFER_H_

#include <stdio.h>
#include <array>
/*
 * Простой циклический буфер
 */
template<class T>
class CircBuffer {

    T *buffer;
    size_t sz;
    size_t head;
    size_t tail;
    bool isFull;

public:
    CircBuffer(size_t s) : sz(s),head{0}, tail{0}, isFull{false} {
    	 buffer = new T[sz];
    }

   inline void put(T item) {
        buffer[head] = item;
        head = (head + 1) % sz;
        if (isFull) {
            tail = (tail + 1) % sz;
        }
        isFull = head == tail;
    }

   inline T get() {
        T result = buffer[tail];
        tail = (tail + 1) % sz;
        isFull = false;
        return result;
    }

   inline bool is_empty() const {
        return tail == head;
    }

   inline size_t capacity() const {
        return sz;
    }

    size_t size() const {
        if (isFull)
            return sz;

        if (head >= tail)
            return head - tail;

        return sz + head - tail;
    }
    virtual ~CircBuffer(){delete []buffer;}
};

#endif /* CIRCBUFFER_H_ */
