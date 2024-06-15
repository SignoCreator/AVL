#ifndef AVL_TPP
#define AVL_TPP

#include "AVL.h"

namespace AVL{

    /**
     * @brief This struct represents a node in the AVL tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     */
    template<typename K, typename V>
    struct AVLNodeStruct {
        K key;
        V value;
        AVLNode<K, V> left;
        AVLNode<K, V> right;
        int height;
    };

    /**
     * @brief This function creates a new node
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param key is the key of the node
     * @param value is the value of the node
     * @return a new node
     */
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

    /**
     * @brief This function creates an empty AVL tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @return an empty tree
     */
    template<typename K, typename V>
    AVLNode<K,V> createAVLTree() {
        return EMPTY_TREE;
    }

    /**
     * @brief This function inserts a node in the tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param node is the current node
     * @param key is the key of the node to be inserted
     * @param value is the value of the node to be inserted
     * @return the root of the tree
     */
    template<typename K, typename V>
    AVLNode<K, V> insert(AVLNode<K, V>& node, K key, V value) {
        // if the tree is empty, return a new node
        if (isEmpty(node))
            return newNode<K, V>(key, value);

        //if the key is less than the root, insert it in the left subtree
        if (key < node->key)
            node->left = insert(node->left, key, value);

        //if the key is greater than the root, insert it in the right subtree
        else if (key > node->key)
            node->right = insert(node->right, key, value);

        //if the key is equal to the root, update the value
        else
            return node;
        //update the height of the current node
        node->height = max(height(node->left), height(node->right)) + 1;
        //get the balance factor of the current node
        int balance = balanceFactor(node);


        // in order to rebalance the tree, we need to check if the node is unbalanced,
        //then we can apply the corresponding rotation to preserve the AVL property
        //if the node is unbalanced, there are 4 cases

        //this is the left left case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        //this is the right right case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        //this is the left right case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //this is the right left case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    /**
     * @brief This function performs a left rotation on the node
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param x is the node to be rotated
     * @return the new root of the tree
     */
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

    /**
     * @brief This function performs a right rotation on the node
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param y is the node to be rotated
     * @return the new root of the tree
     */
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

    /**
     * @brief This function searches for a node in the tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param root is the root of the tree
     * @param key is the key of the node to be searched
     * @return the node if found, otherwise return an empty tree
     */
    template<typename K, typename V>
    AVLNode<K, V> search(AVLNode<K, V>& root, K key) {
        if (isEmpty(root) || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);
        return search(root->left, key);
    }






    /**
     * @brief This function deletes a node from the tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param root is the root of the tree
     * @param key is the key of the node to be deleted
     * @return the root of the tree
     */
    template<typename K, typename V>
    AVLNode<K, V> remove(AVLNode<K, V>& root, K key) {
        //if the tree is empty, return an empty tree
        if (isEmpty(root))
            return root;
        //if the key is less than the root, delete it from the left subtree
        if (key < root->key)
            root->left = remove(root->left, key);
        //if the key is greater than the root, delete it from the right subtree
        else if (key > root->key)
            root->right = remove(root->right, key);
        //if the key is equal to the root, delete the root
        else {
            //if the node has one child or no child
            if (isEmpty(root->left) || isEmpty(root->right)) {
                AVLNode<K, V> temp;
                // if left child is empty, then the right child is the new root
                if(isEmpty(root->left))
                    temp = root->right;
                // if right child is empty, then the left child is the new root
                else
                    temp = root->left;
                //if the node has no child then it is the leaf node
                if (isEmpty(temp)) {
                    temp = root;
                    root = EMPTY_TREE;
                }else
                    *root = *temp;
                delete temp;
            } else {
                //if the node has two children, get the inorder successor
                AVLNode<K, V> temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = remove(root->right, temp->key);
            }
        }
        //if the tree has only one node, return it
        if (isEmpty(root))
            return root;
        //update the height of the current node
        root->height = max(height(root->left), height(root->right)) + 1;

        int balance = balanceFactor(root);

        // in order to rebalance the tree, we need to check if the node is unbalanced,
        //then we can apply the corresponding rotation to preserve the AVL property
        //if the node is unbalanced, there are 4 cases

        //this is the left left case
        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

        //this is the left right case
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //this is the right right case
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

        //this is the right left case
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }



    /**
     * @brief This function converts the tree to a list-array
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param t is the tree to be converted
     * @param l is the list-array
     */
    template<typename K,typename V>
    void auxToList(AVLNode<K,V>& t,list::List& l){
        if (!isEmpty(t)) {
            auxToList(t->left, l);
            list::addBack(t->key, l);
            auxToList(t->right, l);
        }
    }


    /**
     * @brief This function converts the tree to a list-array
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param t is the tree to be converted
     * @return a list-array
     */
    template<typename K,typename V>
    list::List toList(AVLNode<K,V>& t) {
        list::List l = list::createEmpty();
        auxToList(t, l);
        return l;
    }

    /**
     * @brief This function performs an action on each node of the tree
     * @tparam Key is the key of the node
     * @tparam Value is the value of the node
     * @tparam Action is the action to be performed on the node
     * @param node is the current node
     * @param action is the action to be performed
     */
    template <typename Key, typename Value,typename Action>
    void performAction(AVLNode<Key, Value>& node, Action action) {
        if (!node) return;
        performAction(node->left, action);
        action(node->key, node->value);
        performAction(node->right, action);
    }

    /**
    * @brief This function performs a pre-order traversal of the tree
    * @tparam K is the key of the node
    * @tparam V is the value of the node
    * @param root is the root of the tree
    */
    template<typename K, typename V>
    void preOrder(const AVLNode<K, V>& root) {
        if (!isEmpty(root)) {
            std::cout << root->key << ":" << root->value << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    /**
     * @brief This function performs an in-order traversal of the tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param root is the root of the tree
     */
    template<typename K, typename V>
    void inOrder(const AVLNode<K, V>& root) {
        if (!isEmpty(root)) {
            inOrder(root->left);
            std::cout << root->key << ":" << root->value << " ";
            inOrder(root->right);
        }
    }

    /**
     * @brief This function performs a post-order traversal of the tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param root is the root of the tree
     */
    template<typename K, typename V>
    void postOrder(const AVLNode<K, V>& root) {
        if (!isEmpty(root)) {
            postOrder(root->left);
            postOrder(root->right);
            std::cout << root->key << ":" << root->value << " ";
        }
    }
    /**
     * @brief This function checks if the tree is empty
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param node is the current node
     * @return true if the tree is empty, false otherwise
     */
    template<typename K, typename V>
    bool isEmpty(const AVLNode<K, V>& node) {
        return node == EMPTY_TREE;
    }
    /**
     * @brief This function returns the height of the node
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param node is the current node
     * @return the height of the node
     */
    template<typename K, typename V>
    int height(const AVLNode<K, V>& node) {
        return isEmpty(node) ? 0 : node->height;
    }


    /**
     * @brief This function returns the maximum of two integers
     * @param a is the first integer
     * @param b is the second integer
     * @return the maximum of the two integers
     */
    int max(int a, int b) {
        return (a > b) ? a : b;
    }


    /**
     * @brief This function returns the balance factor of the node
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param node is the current node
     * @return the balance factor of the node
     */
    template<typename K, typename V>
    int balanceFactor(const AVLNode<K,V>& node) {
        return isEmpty(node) ?
               0 :
               height(node->left) - height(node->right);
    }


    /**
     * @brief This function returns the node with the minimum value found in the tree
     * @tparam K is the key of the node
     * @tparam V is the value of the node
     * @param node is the current node
     * @return is the node with the minimum value found in the tree
     */
    template<typename K, typename V>
    AVLNode<K, V> minValueNode(const AVLNode<K, V>& node) {
        AVLNode<K, V> current = node;
        while (!isEmpty(current->left))
            current = current->left;
        return current;
    }
}

#endif //AVL_AVL_H