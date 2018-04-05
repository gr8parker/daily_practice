#include <iostream>
#include <exception>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstdlib> // rand for tests
#include <ctime>
#include <vector>

class PriorityQueue
{
public:
    typedef unsigned int uint;
    
    explicit PriorityQueue();
    explicit PriorityQueue(uint length);
    
    ~PriorityQueue();
    
    int top();
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

PriorityQueue::PriorityQueue(PriorityQueue::uint length)
: m_size(0)
, m_maxSize(length)
{
    m_data = new int[m_maxSize];
}

PriorityQueue::~PriorityQueue()
{
    delete[] m_data;
}

PriorityQueue::uint PriorityQueue::leftChildIndex(PriorityQueue::uint index) const
{
    return (2 * index + 1);
}

PriorityQueue::uint PriorityQueue::rightChildIndex(PriorityQueue::uint index) const
{
    return (2 * index + 2);
}

PriorityQueue::uint PriorityQueue::parentIndex(PriorityQueue::uint index) const
{
    return static_cast<uint>((index - 1) / 2);
}

void PriorityQueue::siftUp(PriorityQueue::uint index)
{
    while (index > 0 && m_data[index] > m_data[parentIndex(index)])
    {
        std::swap(m_data[index], m_data[parentIndex(index)]);
        index = parentIndex(index);
    }
}

void PriorityQueue::siftDown(PriorityQueue::uint index)
{
    uint maxChildIndex = index;
    
    uint leftIndex = leftChildIndex(index);
    if (leftIndex < m_size && m_data[index] < m_data[leftIndex])
    {
        maxChildIndex = leftIndex;
    }
    
    uint rightIndex = rightChildIndex(index);
    if (rightIndex < m_size && m_data[maxChildIndex] < m_data[rightIndex])
    {
        maxChildIndex = rightIndex;
    }
    
    if (index != maxChildIndex)
    {
        std::swap(m_data[index], m_data[maxChildIndex]);
        siftDown(maxChildIndex);
    }
}

int PriorityQueue::top()
{
    int ret = m_data[0];
    m_data[0] = m_data[--m_size];
    siftDown(0);
    return ret;
}

void PriorityQueue::insert(int item)
{
    if (m_size >= m_maxSize)
        reallocMemory();
    m_data[m_size++] = item;
    siftUp(m_size - 1);
}

bool PriorityQueue::isEmpty() const
{
    return (this->m_size == 0);
}

void PriorityQueue::reallocMemory()
{
    m_maxSize *= 2;
    int *newData = new int[m_maxSize];
    for (int i = 0; i < m_size; ++i)
        newData[i] = m_data[i];
    
    delete [] m_data;
    m_data = newData;
}

void PriorityQueue::print() const
{
    for (int i = 0; i < m_size - 1; ++i)
        std::cout << m_data[i] << ", ";
    std::cout << m_data[m_size - 1] << std::endl;
}

void test()
{
    int n = 99999;
    PriorityQueue q;
    for(int i = 0; i < n; ++i)
        q.insert(i);
    while(!q.isEmpty())
    {
        if (q.top() != --n)
        {
            std::cout << "Error occured at n = " << n << std::endl;
            break;
        }
        
    }
    if (n == 0)
        std::cout << "Success" << std::endl;
}

void stressTest()
{
    int nTests = 100;
    int nElements = 100000;
    std::srand(unsigned(std::time(0)));
    for (int iTest = 0; iTest < nTests; ++iTest)
    {
        std::vector<int> v;
        PriorityQueue q;
        // fill
        for (int i = 0; i < nElements; ++i)
        {
            int val = std::rand();
            v.push_back(val);
            q.insert(val);
        }
        // test
        std::sort(v.begin(), v.end(), std::greater<int>());
        for (const auto& val : v)
        {
            if (val != q.top())
            {
                std::cout << "Test[" << iTest << "] Failed" << std::endl;

                return;
            }
        }
        
        if (!q.isEmpty())
        {
            std::cout << "Test[" << iTest << "] Failed" << std::endl;
            return;
        }
    }
    std::cout << nTests << " successfully passed. Congratulations!" << std::endl;
}

int main()
{
    stressTest();
}


