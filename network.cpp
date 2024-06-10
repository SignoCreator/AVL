#include "network.h"
#include <string>
#include "list-array.h"
#include "AVL.h"
using namespace std;
using namespace list;

using namespace AVL;


namespace network{
#define EMPTY_USR_LOG ""
    struct st_Network;
    using User_ID = string;
    using Group_ID = string;

    struct userStruct;
    struct groupStruct;
    using User = userStruct*;
    using Group = groupStruct*;
    typedef st_Network* Network;


    typedef AVLTree<User_ID, User> Users;
    typedef AVLTree<Group_ID, Group> Groups;
    struct st_Network{
        Users members;
        Groups groups;
    };

    typedef AVLTree<User_ID, User> Friendships;
    struct userStruct{
        User_ID user_Login;
        Friendships friends;
    };

    struct groupStruct{
        User creator;
        Users members;
    };
    /**********************************************************************/
    /*               Funzione da implementare                             */
    /**********************************************************************/

    // NB: - ogni membro (utente del social network) e' contraddistinto univocamente
    //           da un user_Login rappresentato con una stringa
    //     - ogni gruppo (gruppo di utenti del social network) e' contraddistinto
    //           univocamente da un group_Name rappresentato con una stringa


    bool isAlphabetic(string s){ // 0(n)
        for(char c : s) {
            if (('a' > c || c > 'z') && ('A' > c || c > 'Z'))
                return false;
        }
        return true;
    }
    // Ritorna una network vuota
    Network createEmptyNetwork(){ // 0(1)
        Network net = new st_Network;
        net->members = createAVLTree<User_ID, User>();
        net->groups = createAVLTree<Group_ID, Group>();
        return net;
    }

    // Ritorna true se la network net e' vuota, false altrimenti
    bool isEmpty(const Network& net){ // 0(1)
        return isEmpty(net->members);
    }

    // Aggiunge un membro alla network net con user_Login = usr_Log
    // Se usr_Log e' gia presente ritorna false
    // Se usr_Log e' uguale a "" ritorno false
    // Se usr_Log non contiene solo caratteri alfabetici, ritorna false
    // Altrimenti ritorna true
    bool addMember(string usr_Log, Network &net){ // 0(log(n))
        if(usr_Log == EMPTY_USR_LOG || !isAlphabetic(usr_Log) || search(net->members, usr_Log) != NOT_FOUND)
            return false;
        User user = new userStruct;
        user->user_Login = usr_Log;
        user->friends = createAVLTree<User_ID, User>();
        net->members = insert(net->members, usr_Log, user);
        return true;
    }

    // Rende amici nella network net i membri con user_Login usr_Log1 e usr_Log2
    // Se usr_Log1 o usr_Log2 (o entrambi) non sono presenti in net, ritorna false
    // Se usr_Log1 e' uguale a usr_Log2, ritorna false
    // Altrimenti ritorna true (anche se sono gia amici)
    bool becomeFriends(string usr_Log1, string usr_Log2, Network &net){ // 0(log(n))
        if(usr_Log1 == usr_Log2 || search(net->members, usr_Log1) == NOT_FOUND || search(net->members, usr_Log2) == NOT_FOUND)
            return false;
        User user1 = search(net->members, usr_Log1)->value;
        User user2 = search(net->members, usr_Log2)->value;
        user1->friends = insert(user1->friends, usr_Log2, user2);
        user2->friends = insert(user2->friends, usr_Log1, user1);
        return true;
    }

    // Ritorna true se i membri con user_Login usr_Log1 e usr_Log2 nella network sono amici
    //   (chiaramente devono anche gia' essere presenti entrambi in net)
    // Altrimenti ritorna false
    bool areFriends(string usr_Log1, string usr_Log2, const Network &net){ // 0(log(n))
        if(usr_Log1 == usr_Log2 || search(net->members, usr_Log1) == NOT_FOUND || search(net->members, usr_Log2) == NOT_FOUND)
            return false;
        User user1 = search(net->members, usr_Log1)->value;
        User user2 = search(net->members, usr_Log2)->value;
        return search(user1->friends, usr_Log2) != NOT_FOUND && search(user2->friends, usr_Log1) != NOT_FOUND;
    }

    // Aggiunge un nuovo gruppo di group_Name g_Name alla network net
    // Questo gruppo ha un unico creatore che e il membro con user_Login usr_Log
    // Tutti gli amici del creatore al momento della creazione diventano membri del gruppo
    // Se non c'e' un membro in net con user_Login usr_Log, ritorna false
    // Se g_Name esiste gia', ritorna false
    // Altrimenti ritorna true
    bool createGroup(string usr_Log, string g_Name, Network &net){ // 0(nlog(n))
        if(search(net->members, usr_Log) == NOT_FOUND || search(net->groups, g_Name) != NOT_FOUND)
            return false;
        Group group = new groupStruct;
        group->creator = search(net->members, usr_Log)->value;
        group->members = createAVLTree<User_ID, User>();
        User user = search(net->members, usr_Log)->value;
        group->members = insert(group->members, usr_Log, user);
        Union(group->members, user->friends); // 0(nlog(m))
        net->groups = insert(net->groups, g_Name, group);
        return true;
    }

    // Il membro con user_Login usr_Log, diventa membro del gruppo con group_Name = g_Name
    // Ritorna true se c'e' un membro usr_Log e un gruppo g_Name
    // Altrimenti ritorna false
    bool joinGroup(string usr_Log, string g_Name, Network &net){ //0(log(n))
        if(search(net->members, usr_Log) == NOT_FOUND || search(net->groups, g_Name) == NOT_FOUND) // 0(log(n))
            return false;
        Group group = search(net->groups, g_Name)->value; // 0(log(n))
        group->members = insert(group->members, usr_Log, search(net->members, usr_Log)->value); // 0(log(n))
        return true;
    }

    // Cancella il membro con user_Login = usr_Log dal network net
    // Cancella anche tutti i gruppi di cui questo membro e' il creatore
    // Ritorna true se tale membro esiste
    // Altrimenti ritorna false
    bool deleteMember(string usr_Log, Network &net) { // 0(nlog(n))
        if (search(net->members, usr_Log) == NOT_FOUND) // 0(log(n))
            return false;

        // Prendi una lista di gruppi di cui usr_Log è creatore
        list::List creatorOfList = creatorOf(usr_Log, net); // 0(nlog(n))
        for (int i = 0; i < creatorOfList.size; i++) { // 0(nlog(n))
            string groupName = get(i, creatorOfList);
            deleteGroup(groupName, net);
        }

        list::List friendsList = friends(usr_Log, net); // 0(nlog(n))
        for (int i = 0; i < friendsList.size; i++) { // 0(nlog(n))
            string friendName = get(i, friendsList);
            leaveFriendship(usr_Log, friendName, net);
        }
        list::List memberOfList = memberOf(usr_Log, net); // 0(nlog(n))
        for (int i = 0; i < memberOfList.size; i++) { // 0(nlog(n))
            string groupName = get(i, memberOfList);
            leaveGroup(usr_Log, groupName, net);
        }
        net->members = deleteNode(net->members, usr_Log); // 0(log(n))
        return true;
    }

    // Cancella il gruppo con group_Name = g_Name dal network net
    // Ritorna true se un tale gruppo esiste
    // Altrimenti ritorna false
    bool deleteGroup(string g_Name, Network &net) { // 0(log(n))
        if (search(net->groups, g_Name) == NOT_FOUND)
            return false;
        net->groups = deleteNode(net->groups, g_Name);
        return true;
    }



    // Cancella l'amicizia fra il membro usr_Log1 e il membro usr_Log2
    // Se non ci sono i membri usr_Log1 o usr_Log2, ritorna false
    // Se usr_Log1 e' uguale a usr_Log2, ritorna false
    // Altrimenti ritorna true (anche se non sono amici)
    bool leaveFriendship(string usr_Log1, string usr_Log2, Network &net){ // 0(log(n))
        if(usr_Log1 == usr_Log2 || search(net->members, usr_Log1) == NOT_FOUND || search(net->members, usr_Log2) == NOT_FOUND)
            return false;
        User user1 = search(net->members, usr_Log1)->value;
        User user2 = search(net->members, usr_Log2)->value;
        user1->friends = deleteNode(user1->friends, usr_Log2);
        user2->friends = deleteNode(user2->friends, usr_Log1);
        return true;
    }

    // Il membro con user_Login = usr_Log viene rimosso dal gruppo con group_Name = g_Name
    // Se il membro e' il creatore, il gruppo vienne cancellato
    // Se non c'e' in net un membro usr_Log o un gruppo g_Name ritorna false
    // Altrimenti ritorna true (anche se il membro usr_Log non e' membro del gruppo)
    bool leaveGroup(string usr_Log, string g_Name, Network &net){ // 0(log(n))
        if(search(net->members, usr_Log) == NOT_FOUND || search(net->groups, g_Name) == NOT_FOUND)
            return false;
        Group group = search(net->groups, g_Name)->value;
        if(group->creator->user_Login == usr_Log)
            return deleteGroup(g_Name, net);
        group->members = deleteNode(group->members, usr_Log);
        return true;
    }

    // Ritorna la lista in ordine alfabetico dei user_Login dei membri del network
    list::List members(const Network &net){ // 0(n)
        return toList(net->members);
    }

    // Ritorna la lista in ordine alfabetico dei group_Name dei gruppi del network
    list::List groups(const Network &net){ // 0(n)
        return toList(net->groups);
    }

    // Ritorna la lista dei user_Login degli amici del membro con user_Login = usr_Log
    //  in ordine alfabetico
    // Se non c'e membro con user_Login = usr_Log ritorna la lista vuota
    list::List friends(string usr_Log, const Network &net){ // 0(n)
        AVLNode<User_ID, User> node = search(net->members, usr_Log);
        if(isEmpty(node))
            return createEmpty();
        User user = node->value;
        return toList(user->friends);
    }

    // Ritorna la lista dei nomi dei gruppi di cui il membro usr_Log
    //   e' membro (in ordine alfabetico)
    // (NB: un membro e' anche membro di un gruppo di cui e' il creatore)
    // Se in net non c'e' membro usr_Log ritorna la lista vuota
    list::List memberOf(string usr_Log, const Network &net){ // 0(nlogn)
        list::List l = list::createEmpty();
        performActionOnCondition(net->groups,
                                 [usr_Log](const std::string& key, Group& group) -> bool {
                                     return search(group->members, usr_Log) != EMPTY_TREE;
                                 },
                                 [&l](const std::string& key, Group& group) -> void{
                                     list::addBack(key,l);
                                 }
        );
        return l;
    }

    // Ritorna la lista dei nomi dei gruppi di cui il membro usr_Log
    //  e' creatore in ordine alfabetico
    // Se non c'e' membro usr_Log ritorna la lista vuota
    list::List creatorOf(string usr_Log, const Network &net){  // 0(n)
        list::List l = list::createEmpty();
        performActionOnCondition(net->groups,
                                 [usr_Log](const std::string& key, Group& group) -> bool {
                                     return group->creator->user_Login == usr_Log;
                                 },
                                 [&l](const std::string& key, Group& group) -> void{
                                     list::addBack(key,l);
                                 }
        ); // 0(n)
        return l;
    }

    // Il membro usr_Log diventa amico con tutti i membri con i
    //   quali condivide un gruppo
    // Ritorna true se c'e un membro con user_Login = usr_Log
    // Altrimenti ritorna false
    bool makeMoreFriends(string usr_Log, Network &net) { // 0(n*m) where m is the number of members in the group and n is the number of groups
        performActionOnCondition(net->groups,
                                 [usr_Log](const std::string& key, Group& group) -> bool {
                                     return search(group->members, usr_Log) != EMPTY_TREE;
                                 },
                                 [&usr_Log, &net](const std::string& key, Group& group) -> void{
                                     list::List members = toList(group->members); // 0(n) n=members
                                     for(int i = 0; i < members.size; i++){
                                         if(get(i,members) != usr_Log)
                                             becomeFriends(usr_Log, get(i,members), net);
                                     }
                                 }
        );
        return search(net->members, usr_Log) != NOT_FOUND;
    }

}