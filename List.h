//
// Created by Saar Keynan on 25/02/2022.
//

#ifndef CPPBJ_LIST_H
#define CPPBJ_LIST_H
#include <cstdlib>
template <typename T>
class List {
    T *data;
public:
    List<T>::List() {
        data = nullptr;
        size = 0;
    }

    T List<T>::get(int index) {
        return data[index];
    }

    void List<T>::add(T item) {
        data = (T*)realloc(data, (++size) * sizeof(T));
        data[size - 1] = item;
    }

    void List<T>::remove(int index) {
        T temp = data[size-1];
        data[size-1] = data[index];
        data[index] = temp;
        data = (T*)realloc(data, --size * sizeof(T));
    }
    int size;
};


#endif //CPPBJ_LIST_H
