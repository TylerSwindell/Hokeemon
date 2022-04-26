#pragma once

#include <iostream>

template <typename T>
class Vector {
private:
    size_t numOfEle;
    T* arr;

    
    // Bold White
    const static std::string B_W;         
    // Bold Teal
    const static std::string B_T;
    // Bold Red
    const static std::string B_R;
    // Reset Text
    const static std::string R_T;

    void resize(int ind);

public:
    Vector();
    
    size_t size();
    size_t index();
    T get(size_t index);

    void push(const T &element);
    void pop();
    void remove(size_t index);
    
    void print(bool newLine = false);
    
};
