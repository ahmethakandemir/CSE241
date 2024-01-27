#include <iostream>
#include <vector>

template <typename T>
class VectorIterator {
public:
    // Constructor
    VectorIterator(const std::vector<T>& vec, size_t index = 0) : vectorRef(vec), currentIndex(index) {}

    // Dereference operator
    const T& operator*() const {
        return vectorRef[currentIndex];
    }

    // Prefix increment operator
    VectorIterator<T>& operator++() {
        ++currentIndex;
        return *this;
    }

    // Postfix increment operator
    VectorIterator<T> operator++(int) {
        VectorIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    // Equality operators
    bool operator==(const VectorIterator<T>& other) const {
        return currentIndex == other.currentIndex;
    }

    bool operator!=(const VectorIterator<T>& other) const {
        return !(*this == other);
    }

private:
    const std::vector<T>& vectorRef;
    size_t currentIndex;
};

int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    // Using the custom iterator
    VectorIterator<int> iterBegin(myVector);
    VectorIterator<int> iterEnd(myVector, myVector.size());

    VectorIterator<int> iterBegin2(myVector);
    VectorIterator<int> iterEnd2(myVector, myVector.size());
    

    
    std::cout << std::endl;
    VectorIterator<int> iter = iterBegin;
    for (; iter != iterEnd; ++iter) {
    
        std::cout << *iter << " ";
    }
    
    std::cout << std::endl;
    VectorIterator<int> iter2 = iterBegin2;
    for (; iter2 != iterEnd2; ++iter2) {
        std::cout << *iter2 << " ";
        std::cout << (iter == iter2);
        std::cout << std::endl;
    }
    std::cout << (iter == iter2) << std::endl;



    return 0;
}
