#include "network.h"
#include <string>
#include "list-array.h"
#include "AVL/AVL.h"
using namespace std;
using namespace list;

using namespace AVL;

#define EMPTY_USR_LOG "" // This makes the code more readable
namespace network{

    struct st_Network;
    using User_ID = string; // if I want to change the type of User_ID, I just need to change it here
    using Group_ID = string; // if I want to change the type of Group_ID, I just need to change it here

    struct userStruct;
    struct groupStruct;
    using User = userStruct*;
    using Group = groupStruct*;
    typedef st_Network* Network;

    typedef AVLTree<User_ID, User> Users; // users are represented by an AVLTree
    typedef AVLTree<Group_ID, Group> Groups; // groups are represented by an AVLTree

    /**
     * @brief This struct represents a network
     */
    struct st_Network{
        Users members;
        Groups groups;
    };

    typedef AVLTree<User_ID, User> Friendships;

    /**
     * @brief This struct represents a user
     */
    struct userStruct{
        User_ID user_Login; // user_Login is the unique identifier of the user
        Friendships friends; // friends are represented by an AVLTree
    };

    /**
     * @brief This struct represents a group
     */
    struct groupStruct{
        User creator; // the creator of the group
        Users members; // the members of the group
    };


    /**********************************************************************/
    /*               Funzione ausiliaria                                  */
    /**********************************************************************/
   
    /**
     * @brief This function checks if a string is alphabetic, that is, if it contains only letters
     * 
     * @param s the string to check
     * @return true if the string is alphabetic, false otherwise
     */
    bool isAlphabetic(string s){ // 0(n)
        for(char c : s) {
            if (('a' > c || c > 'z') && ('A' > c || c > 'Z'))
                return false;
        }
        return true;
    }
    
    /**
     * @brief This function checks if two strings are equal
     * 
     * @param s1 the first string
     * @param s2 the second string
     * @return true if the strings are equal, false otherwise
     */
    bool areEqual(string s1, string s2){ // 0(1)
        return s1 == s2;
    }
    
    /**
     * @brief This function checks if a string is empty
     * 
     * @param s the string to check
     * @return true if the string is empty, false otherwise
     */
    bool isEmptyString(string s){ // 0(1)
        return s == EMPTY_USR_LOG;
    }
    
    /**
     * @brief This function checks if a node Found
     * 
     * @param node the node to check
     * @return true if the node Found, false otherwise
     */
    bool Found(AVLNode<User_ID, User> node){ // 0(1)
        return node != NOT_FOUND;
    }
    
    /**
     * @brief This function checks if a node was found in the AVLTree
     * 
     * @param node the node to check
     * @return true if the node was found, false otherwise
     */
    bool Found(AVLNode<Group_ID, Group> node){ // 0(1)
        return node != NOT_FOUND;
    }

    /**
     * @brief This function checks if a string is a valid ID
     *
     * @param id the string to check
     * @return true if the string is a valid ID, false otherwise
     */
    bool IDValidator(string id){ // 0(1)
        return !isEmptyString(id) && isAlphabetic(id);
    }
    /**********************************************************************/
    /*               Funzione da implementare                             */
    /**********************************************************************/


    /**
     * @brief This function creates an empty network
     *
     * @return an empty network
     */
    Network createEmptyNetwork(){ // 0(1)
        Network net = new st_Network;
        net->members = createAVLTree<User_ID, User>();
        net->groups = createAVLTree<Group_ID, Group>();
        return net;
    }

    /**
     * @brief This function checks if a network is empty
     *
     * @param net the network to check
     * @return true if the network is empty, false otherwise
     */
    bool isEmpty(const Network& net){ // 0(1)
        // #members = 0 -> #creatorOf = 0 && #memberOf = 0 && #friends = 0 -> #groups = 0 -> net = empty
        return isEmpty(net->members);
    }

    /**
     * @brief This function adds a member to the network
     *
     * @param usr_Log the user login of the member to add
     * @param net the network to add the member to
     * @return true if the member was added, false otherwise
     */
    bool addMember(string usr_Log, Network &net){ // 0(log(n))
        AVLNode<User_ID,User> node = search(net->members, usr_Log);
        if(!IDValidator(usr_Log) || Found(node))
            return false;
        User user = new userStruct;
        user->user_Login = usr_Log;
        user->friends = createAVLTree<User_ID, User>();
        net->members = insert(net->members, usr_Log, user);
        return true;
    }

    /**
     * @brief This function makes two members friends
     *
     * @param usr_Log1 the user login of the first member
     * @param usr_Log2 the user login of the second member
     * @param net the network to make the members friends in
     * @return true if the members became friends, false otherwise
     */
    bool becomeFriends(User_ID usr_Log1, User_ID usr_Log2, Network& net) {
        AVLNode<User_ID,User> user1 = search(net->members, usr_Log1);
        AVLNode<User_ID,User> user2 = search(net->members, usr_Log2);
        if (areEqual(usr_Log1,usr_Log2) || !Found(user1) || !Found(user2))
            return false;
        user1->value->friends = insert(user1->value->friends, usr_Log2, user2->value);
        user2->value->friends = insert(user2->value->friends, usr_Log1, user1->value);
        return true;
    }

    /**
     * @brief This function checks if two members are friends
     *
     * @param usr_Log1 the user login of the first member
     * @param usr_Log2 the user login of the second member
     * @param net the network to check the friendship in
     * @return true if the members are friends, false otherwise
     */
    bool areFriends(string usr_Log1, string usr_Log2, const Network &net){
        AVLNode<User_ID,User> user1 = search(net->members, usr_Log1);
        AVLNode<User_ID,User> user2 = search(net->members, usr_Log2);
        if(areEqual(usr_Log1,usr_Log2) || !Found(user1) || !Found(user2)) // 0(log(n))
            return false;
        bool user1IsFriendWithUser2 = Found(search(user1->value->friends, usr_Log2)); // 0(log(m))
        bool user2IsFriendWithUser1 = Found(search(user2->value->friends, usr_Log1)); // 0(log(m))
        return user1IsFriendWithUser2 && user2IsFriendWithUser1;
    }

    /**
     * @brief This function creates a group in the network
     *
     * @param usr_Log the user login of the member to create the group
     * @param g_Name the name of the group to create
     * @param net the network to create the group in
     * @return true if the group was created, false otherwise
     */
    bool createGroup(string usr_Log, string g_Name, Network &net){ // 0(nlog(n))
        // check if the user exists
        AVLNode<User_ID,User> user = search(net->members, usr_Log);
        if(!Found(user))
            return false;
        // check if the group exists
        AVLNode<Group_ID,Group> groupExist = search(net->groups, g_Name);
        if(Found(groupExist) || !IDValidator(g_Name))
            return false;
        //create the group
        Group group = new groupStruct;
        group->creator = user->value;
        group->members = createAVLTree<User_ID, User>();
        //add friends of creator to the group
        auto iterateInFriends = [&group](const std::string& key, User& user) -> void{
            group->members = insert(group->members, key, user); // 0(log(n))
        };
        performAction(user->value->friends,iterateInFriends); // 0(n)
        // add the creator to the group
        group->members = insert(group->members, usr_Log, user->value);
        net->groups = insert(net->groups, g_Name, group);
        return true;
    }

    /**
     * @brief This function makes a member join a group
     *
     * @param usr_Log the user login of the member to join the group
     * @param g_Name the name of the group to join
     * @param net the network to join the group in
     * @return true if the member joined the group, false otherwise
     */
    bool joinGroup(string usr_Log, string g_Name, Network &net){ //0(log(n))
        AVLNode<User_ID,User> user = search(net->members, usr_Log);
        AVLNode<Group_ID,Group> group = search(net->groups, g_Name);
        if(!Found(user) || !Found(group)) // 0(log(n))
            return false;
        group->value->members = insert(group->value->members, usr_Log, user->value); // 0(log(n))
        return true;
    }

    /**
     * @brief This function deletes a member from the network
     *
     * @param usr_Log the user login of the member to delete
     * @param net the network to delete the member from
     * @return true if the member was deleted, false otherwise
     */
    bool deleteMember(string usr_Log, Network &net) { // 0(nlog(n))
        if (search(net->members, usr_Log) == NOT_FOUND) // 0(log(n))
            return false;
        // delete all groups created by the user
        list::List creatorOfList = creatorOf(usr_Log, net); // 0(nlog(n))
        for (int i = 0; i < creatorOfList.size; i++) // 0(nlog(n))
            deleteGroup(get(i, creatorOfList), net);
        // delete all friendships of the user
        list::List friendsList = friends(usr_Log, net); // 0(nlog(n))
        for (int i = 0; i < friendsList.size; i++) // 0(nlog(n))
            leaveFriendship(usr_Log, get(i, friendsList), net);
        // delete all groups the user is in
        list::List memberOfList = memberOf(usr_Log, net); // 0(nlog(n))
        for (int i = 0; i < memberOfList.size; i++)// 0(nlog(n))
            leaveGroup(usr_Log, get(i, memberOfList), net);
        // delete the user
        net->members = deleteNode(net->members, usr_Log); // 0(log(n))
        return true;
    }


    /**
     * @brief This function deletes a group from the network
     *
     * @param g_Name the name of the group to delete
     * @param net the network to delete the group from
     * @return true if the group was deleted, false otherwise
     */
    bool deleteGroup(string g_Name, Network &net) { // 0(log(n))
        AVLNode<Group_ID, Group> group = search(net->groups, g_Name);
        if (!Found(group))
            return false;
        net->groups = deleteNode(net->groups, g_Name);
        return true;
    }



    /**
     * @brief This function deletes a friendship between two members
     *
     * @param usr_Log1 the user login of the first member
     * @param usr_Log2 the user login of the second member
     * @param net the network to delete the friendship from
     * @return true if the friendship was deleted, false otherwise
     */
    bool leaveFriendship(string usr_Log1, string usr_Log2, Network &net){ // 0(log(n))
        AVLNode<User_ID,User> user1 = search(net->members, usr_Log1);
        AVLNode<User_ID,User> user2 = search(net->members, usr_Log2);
        if(areEqual(usr_Log1,usr_Log2) || !Found(user1) || !Found(user2))
            return false;
        user1->value->friends = deleteNode(user1->value->friends, usr_Log2);
        user2->value->friends = deleteNode(user2->value->friends, usr_Log1);
        return true;
    }

    /**
     * @brief This function deletes a member from a group
     *
     * @param usr_Log the user login of the member to delete from the group
     * @param g_Name the name of the group to delete the member from
     * @param net the network to delete the member from the group in
     * @return true if the member was deleted from the group, false otherwise
     */
    bool leaveGroup(string usr_Log, string g_Name, Network &net){ // 0(log(n))
        AVLNode<User_ID,User> user = search(net->members, usr_Log);
        AVLNode<Group_ID,Group> group = search(net->groups, g_Name);
        if(!Found(user) || !Found(group))
            return false;
        if(areEqual(group->value->creator->user_Login,usr_Log))
            return deleteGroup(g_Name, net);
        group->value->members = deleteNode(group->value->members, usr_Log);
        return true;
    }

    /**
     * @brief This function returns the members list of the network
     *
     * @param net the network to get the members from
     * @return the members list of the network
     */
    list::List members(const Network &net){ // 0(n)
        return toList(net->members);
    }

    /**
     * @brief This function returns the groups list of the network
     *
     * @param net the network to get the groups from
     * @return the groups list of the network
     */
    list::List groups(const Network &net){ // 0(n)
        return toList(net->groups);
    }

    /**
     * @brief This function returns the friends list of a member
     *
     * @param usr_Log the user login of the member to get the friends of
     * @param net the network to get the friends from
     * @return the friends list of the member
     */
    list::List friends(string usr_Log, const Network &net){ // 0(n)
        AVLNode<User_ID, User> user = search(net->members, usr_Log);
        if(isEmpty(user))
            return createEmpty();
        return toList(user->value->friends);
    }

    /**
     * @brief This function returns the member of list of a member
     *
     * @param usr_Log the user login of the member to get the member of list of
     * @param net the network to get the member of list from
     * @return the member of list of the member
     */
    list::List memberOf(string usr_Log, const Network &net){ // 0(nlogn)
        list::List l = list::createEmpty();
        auto iterateInGroups = [&l,usr_Log](const std::string& key, Group& group) -> void{
            AVLNode<User_ID, User> user = search(group->members, usr_Log);
            if(!isEmpty(user))
                list::addBack(key,l);
        };
        performAction(net->groups,iterateInGroups); // 0(n)
        return l;
    }

    /**
     * @brief This function returns the creator of list of a member
     *
     * @param usr_Log the user login of the member to get the creator of list of
     * @param net the network to get the creator of list from
     * @return the creator of list of the member
     */
    list::List creatorOf(string usr_Log, const Network &net){  // 0(n)
        list::List l = list::createEmpty();
        auto iterateInGroups = [&l,usr_Log](const std::string& key, Group& group) -> void{
            if(areEqual(group->creator->user_Login,usr_Log))
                list::addBack(key,l);
        };
        performAction(net->groups,iterateInGroups); // 0(n)
        return l;
    }

    /**
     * @brief This function makes a member friends with all the members of the groups he is in
     *
     * @param usr_Log the user login of the member to make friends with
     * @param net the network to make friends in
     * @return true if the member was found, false otherwise
     */
    bool makeMoreFriends(string usr_Log, Network &net) { // 0(n*m) where m is the number of members in the group and n is the number of groups
        // @brief This lambda function is used to iterate over the members of a group and make friends with them
        auto iterateInMembers = [&usr_Log, &net](const std::string& key, User& user) -> void{
            if(!areEqual(user->user_Login,usr_Log))
                becomeFriends(usr_Log, key, net);
        };
        // @brief This lambda function is used to iterate over the groups and make friends with the members of the groups
        auto iterateInGroups = [&usr_Log, &net, &iterateInMembers](const std::string& key, Group& group) -> void{
            AVLNode<User_ID, User> user = search(group->members, usr_Log);
            if(!isEmpty(user))
                performAction(group->members, iterateInMembers);
        };
        performAction(net->groups,iterateInGroups); // 0(n*m) where m is the number of members in the group and n is the number of groups
        AVLNode<User_ID,User> user = search(net->members, usr_Log);
        return Found(user);
    }
}

