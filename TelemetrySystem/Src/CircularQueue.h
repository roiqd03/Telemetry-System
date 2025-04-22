#ifndef CBUFFER_H_INC
#define CBUFFER_H_INC

//El autor del código original del bufffer circular es Jerry Coffin https://stackoverflow.com/questions/63310723/circular-queue-using-stl-queue
//Se han hecho algunas modificaciones a su código

template <class T>
class circular_buffer {
    T* data;
    unsigned read_pos;
    unsigned write_pos;
    unsigned in_use;
    const unsigned capacity;
public:
    circular_buffer(unsigned size) :
        data((T*)operator new(size * sizeof(T))),
        read_pos(0),
        write_pos(0),
        in_use(0),
        capacity(size)
    {
    }

    void push(T const& t) {
        // ensure there's room in buffer:
        if (in_use == capacity)
            pop();

        // construct copy of object in-place into buffer
        new(&data[write_pos++]) T(t);
        // keep pointer in bounds.
        write_pos %= capacity;
        ++in_use;
    }

    // return oldest object in queue:
    T front() {
        return data[read_pos];
    }

    // remove oldest object from queue:
    void pop() {
        // destroy the object:
        data[read_pos++].~T();

        // keep pointer in bounds.
        read_pos %= capacity;
        --in_use;
    }

    bool full() {
        return in_use == capacity;
    }

    bool empty() {
        return in_use <= 0;
    }

    unsigned size() {
        return in_use;
    }

    ~circular_buffer() {
        // first destroy any content
        while (in_use != 0)
            pop();

        // then release the buffer.
        operator delete(data);
    }

};

#endif
