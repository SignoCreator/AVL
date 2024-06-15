#ifndef AVL_AVL_H
#define AVL_AVL_H

#include <iostream>
#include "../list-array.h"


namespace AVL {

    template<typename K, typename V>
    struct AVLNodeStruct {
        K key;
        V value;
        AVLNodeStruct<K, V> *left;
        AVLNodeStruct<K, V> *right;
        int height;
    };

    template<typename K, typename V>
    using AVLNode = AVLNodeStruct<K, V> *;

    template<typename K, typename V>
    using AVLTree = AVLNodeStruct<K, V> *;

    #define EMPTY_TREE nullptr
    #define NOT_FOUND nullptr


    template<typename K, typename V>
    int balanceFactor(const AVLNode<K, V>& node);

    template<typename K, typename V>
    AVLNode<K, V> deleteNode(AVLNode<K, V>& root, K key);

    template<typename K, typename V>
    void inOrder(const AVLNode<K, V>& root);

    template<typename K, typename V>
    AVLNode<K, V> insert(AVLNode<K, V>& node, K key, V value);

    template<typename K, typename V>
    bool isEmpty(const AVLNode<K, V>& node);

    template<typename K, typename V>
    int height(const AVLNode<K, V>& node);

    int max(int a, int b);

    template<typename K, typename V>
    AVLNode<K, V> createAVLTree();

    template<typename K, typename V>
    void postOrder(const AVLNode<K, V>& root);

    template<typename K, typename V>
    void preOrder(const AVLNode<K, V>& root);

    template<typename K, typename V>
    AVLNode<K, V> search(AVLNode<K, V>& root, K key);

    template<typename K, typename V>
    list::List toList(AVLNode<K,V>& t);

    //performAction
    template <typename Key, typename Value,typename Condition>
    void performAction(const AVLNode<Key, Value>& node, Condition condition);


}
#include "avl.tpp"
#endif //AVL_AVL_H
