#ifndef AVL_TPP
#define AVL_TPP

#include "AVL.h"

namespace AVL{
    template<typename K, typename V>
    AVLNode<K, V> newNode(K key, V value) {
        AVLNode<K, V> node = new AVLNodeStruct<K, V>;
        node->key = key;
        node->value = value;
        node->left = EMPTY_TREE;
        node->right = EMPTY_TREE;
        node->height = 1;
        return node;
    }

    template<typename K, typename V>
    AVLNode<K,V> createAVLTree() {
        return EMPTY_TREE;
    }

    template<typename K, typename V>
    AVLNode<K, V> insert(AVLNode<K, V>& node, K key, V value) {
        if (isEmpty(node))
            return newNode<K, V>(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    template<typename K, typename V>
    AVLNode<K,V> leftRotate(AVLNode<K,V>& x) {
        AVLNode<K,V> y = x->right;
        AVLNode<K,V> T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    template<typename K, typename V>
    AVLNode<K,V> rightRotate(AVLNode<K,V>& y) {
        AVLNode<K,V> x = y->left;
        AVLNode<K,V> T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }
    template<typename K, typename V>
    AVLNode<K, V> search(AVLNode<K, V>& root, K key) {
        if (isEmpty(root) || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);
        return search(root->left, key);
    }

    template<typename K, typename V>
    void preOrder(const AVLNode<K, V>& root) {
        if (!isEmpty(root)) {
            std::cout << root->key << ":" << root->value << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    template<typename K, typename V>
    void inOrder(const AVLNode<K, V>& root) {
        if (!isEmpty(root)) {
            inOrder(root->left);
            std::cout << root->key << ":" << root->value << " ";
            inOrder(root->right);
        }
    }

    template<typename K, typename V>
    void postOrder(const AVLNode<K, V>& root) {
        if (!isEmpty(root)) {
            postOrder(root->left);
            postOrder(root->right);
            std::cout << root->key << ":" << root->value << " ";
        }
    }

    template<typename K, typename V>
    bool isEmpty(const AVLNode<K, V>& node) {
        return node == EMPTY_TREE;
    }

    template<typename K, typename V>
    int height(const AVLNode<K, V>& node) {
        return isEmpty(node) ? 0 : node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    template<typename K, typename V>
    int balanceFactor(const AVLNode<K,V>& node) {
        return isEmpty(node) ?
               0 :
               height(node->left) - height(node->right);
    }
    template<typename K, typename V>
    AVLNode<K, V> minValueNode(const AVLNode<K, V>& node) {
        AVLNode<K, V> current = node;
        while (!isEmpty(current->left))
            current = current->left;
        return current;
    }


    template<typename K, typename V>
    AVLNode<K, V> deleteNode(AVLNode<K, V>& root, K key) {

        if (isEmpty(root))
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (isEmpty(root->left) || isEmpty(root->right)) {
                AVLNode<K, V> temp = root->left ? root->left : root->right;
                if (isEmpty(temp)) {
                    temp = root;
                    root = EMPTY_TREE;
                }else
                    *root = *temp;
                delete temp;
            } else {
                AVLNode<K, V> temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (isEmpty(root))
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }


    template<typename K,typename V>
    void auxToList(AVLNode<K,V>& t,list::List& l){
        if (!isEmpty(t)) {
            auxToList(t->left, l);
            list::addBack(t->key, l);
            auxToList(t->right, l);
        }
    }
    template<typename K,typename V>
    list::List toList(AVLNode<K,V>& t) {
        list::List l = list::createEmpty();
        auxToList(t, l);
        return l;
    }
    template <typename Key, typename Value,typename Action>
    void performAction(AVLNode<Key, Value>& node, Action action) {
        if (!node) return;
        performAction(node->left, action);
        action(node->key, node->value);
        performAction(node->right, action);
    }
}

#endif //AVL_AVL_H