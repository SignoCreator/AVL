//
// Created by signo on 09/06/2024.
//

#ifndef AVL_VECTOR_H
#define AVL_VECTOR_H

#ifndef STRING
#define STRING
using namespace std;
#include <string>
#endif




#define LOAD_FACTOR  0.25
template<typename V>
struct vectorStruct {
    V *vector;
    int size;
    int maxSize;
};

template<typename V>
using vector = vectorStruct<V>;

template<typename V>
vector<V> createEmptyVector(int maxSize);

template<typename V>
void clear(vector<V> &v);

template<typename V>
void addBack(V n, vector<V> &v);

template<typename V>
void addFront(V n, vector<V> &v);

template<typename V>
void add(int pos, V n, vector<V> &v);

template<typename V>
void removePos(int pos, vector<V> &v);

template<typename V>
V get(int pos, const vector<V> &v);

template<typename V>
int size(const vector<V> &v);

template<typename V>
bool isEmpty(const vector<V> &v);

template<typename V>
string toString(const vector<V> &v);

template<typename V>
void set(int pos, V n, vector<V> &v);

template<typename V>
void resize(vector<V> &v);

template<typename V>
void shiftRight(int pos, vector<V> &v);

template<typename V>
void shiftLeft(int pos, vector<V> &v);

template<typename V>
vector<V> createEmptyVector(int maxSize) {
    vector<V> v;
    v.vector = new V[maxSize];
    v.size = 0;
    v.maxSize = maxSize;
    return v;
}

template<typename V>
void clear(vector<V> &v) {
    delete[] v.vector;
    v.size = 0;
    v.maxSize = 0;
}

template<typename V>
void addBack(V n, vector<V> &v) {
    if (v.size == v.maxSize) {
        resize(v);
    }
    v.vector[v.size] = n;
    v.size++;
}

template<typename V>
void addFront(V n, vector<V> &v) {
    if (v.size == v.maxSize) {
        resize(v);
    }
    shiftRight(0, v);
    v.vector[0] = n;
    v.size++;
}

template<typename V>
void add(int pos, V n, vector<V> &v) {
    if (v.size == v.maxSize) {
        resize(v,2);
    }
    shiftRight(pos, v);
    v.vector[pos] = n;
    v.size++;
}

template<typename V>
void removePos(int pos, vector<V> &v) {
    //with resize
    if(v.size == v.maxSize * LOAD_FACTOR)
        resize(v,1/2);
    shiftLeft(pos, v);
    v.size--;
}

template<typename V>
V get(int pos, const vector<V> &v) {
    return v.vector[pos];
}

template<typename V>
int size(const vector<V> &v) {
    return v.size;
}

template<typename V>
bool isEmpty(const vector<V> &v) {
    return v.size == 0;
}

template<typename V>
string toString(const vector<V> &v) {
    string result = "";
    for (int i = 0; i < v.size; i++) {
        result += to_string(v.vector[i].value) + " ";
    }
    return result;
}

template<typename V>
void set(int pos, V n, vector<V> &v) {
    v.vector[pos] = n;
}

template<typename V>
void resize(vector<V> &v, int k) {
    vector<V> newV = createEmptyVector<V>(v.maxSize * k);
    for (int i = 0; i < v.size; i++) {
        newV.vector[i] = v.vector[i];
    }
    newV.size = v.size;
    clear(v);
    v = newV;
}

template<typename V>
void shiftRight(int pos, vector<V> &v) {
    for (int i = v.size; i > pos; i--) {
        v.vector[i] = v.vector[i - 1];
    }
}

template<typename V>
void shiftLeft(int pos, vector<V> &v) {
    for (int i = pos; i < v.size - 1; i++) {
        v.vector[i] = v.vector[i + 1];
    }
}

#endif //AVL_VECTOR_H
