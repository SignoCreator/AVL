/*


 #include <iostream>
#include <string>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include "AVL.h"

// Funzione per generare una chiave casuale univoca
std::string generateRandomKey(int length, std::unordered_set<std::string>& generatedKeys) {
    std::string key;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

do {
key = "";
for (int i = 0; i < length; ++i) {
key += alphanum[rand() % (sizeof(alphanum) - 1)];
}
} while (generatedKeys.find(key) != generatedKeys.end());

generatedKeys.insert(key);
return key;
}

using namespace AVL;
int main() {
    srand(time(nullptr));

    const int N = 10; // Numero di chiavi da generare
    const int keyLength = 8; // Lunghezza delle chiavi

    std::unordered_set<std::string> generatedKeys;
    AVLNode<std::string, int> root = EMPTY_TREE;

    // Inserimento delle chiavi nell'albero
    for (int i = 0; i < N; ++i) {
        std::string key = generateRandomKey(keyLength, generatedKeys);
        int value = key.length();
        root = insert(root, key, value);
    }

    // Stampa in ordine
    std::cout << "Chiavi in ordine:\n";
    inOrder(root);
    std::cout << std::endl;

    // Eliminazione delle chiavi una ad una e verifica che l'albero sia vuoto
    while (!isEmpty(root)) {
        AVLNode<std::string, int> minNode = minValueNode(root);
        std::cout << "Eliminazione di " << minNode->key << std::endl;
        root = deleteNode(root, minNode->key);
    }

    if (isEmpty(root)) {
        std::cout << "L'albero è vuoto." << std::endl;
    } else {
        std::cout << "L'albero non è vuoto." << std::endl;
    }

    // PRENDO SOLO NOMI con iniziale minore di M

    list::List l = list::createEmpty();

    traverseIf(root, [](const std::string& key, int value) {
        return key[0] < 'm';
    }, [&l](const std::string& key, int value) {
        list::addBack(key, l);
    });

    cout<<list::toString(l);


    return 0;
}




#include "network.h"
#include <iostream>
#include "list-array.h"
using namespace std;
using namespace network;

int main() {
    // Create a new network
    Network net = createEmptyNetwork();

    // Add some members
    addMember("Alice", net);
    addMember("Bob", net);
    addMember("Charlie", net);

    // Create some groups
    createGroup("Alice", "Group1", net);
    createGroup("Bob", "Group2", net);

    // Add members to groups
    joinGroup("Bob", "Group1", net);
    joinGroup("Charlie", "Group1", net);
    joinGroup("Alice", "Group2", net);

    // Print out the members
    std::cout << "Members:\n";
    list::List memberList = members(net);
    cout<<list::toString(memberList);

    // Print out the groups
    std::cout << "\nGroups:\n";
    list::List groupList = groups(net);
    cout<<list::toString(groupList);


    //RIMUOVO UN MEMBRO
    deleteMember("Bob", net);
    // Print out the members
    std::cout << "Members:\n";
    memberList = members(net);
    cout<<list::toString(memberList);
    return 0;
}
 */