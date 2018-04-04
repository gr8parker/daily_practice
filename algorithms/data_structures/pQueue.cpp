#include <iostream>
#include <exception>
#include <utility>


class PriorityQueue
{
public:
    typedef using int uint;
    
    explicit PriorityQueue()
    explicit PriorityQueue(uint length);
    
    ~PriorityQueue();
    
    int tip();
    void insert(int item);
    bool isEmpty() const;
    void print() const;
    
    
private:
    uint leftChildIndex(uint index) const;
    uint rightChildIndex(uint index) const;
    uint parentIndex(uint index) const;
    
    void siftUp(uint index);
    void siftDown(uint index);
    
    void reallocMemory();
    
private:
    int* m_data;
    uint m_size;
    uint m_maxSize;
};


PriorityQueue::PriorityQueue()
    : m_size(0)
    , m_maxSize(4)
{
    m_data = new int[m_maxSize];
}

PriorityQueue::PriorityQueue(Priority::uint length)
: m_size(0)
, m_maxSize(length)
{
    m_data = new int[m_maxSize];
}

PriorityQueue::~PriorityQueue()
{
    delete[] data;
}

PriorityQueue::uint PriorityQueue::leftChildIndex(Priority::uint index) const
{
    return (2 * index + 1);
}

PriorityQueue::uint PriorityQueue::rightChildIndex(Priority::uint index) const
{
    return (2 * index + 2);
}

PriorityQueue::uint PriorityQueue::parentIndex(PriorityQueue::uint index) const
{
    return static_cast<int>((index - 1) / 2);
}

void PriorityQueue::siftUp(PriorityQueue::uint index)
{
    while (index > 0 && m_data[index] < m_data[parentIndex(index)])
    {
        swap(m_data(index), m_data[parentIndex(index)]);
        index = parentIndex(index);
    }
}


