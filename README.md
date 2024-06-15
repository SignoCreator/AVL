
# <span style="color:#F18F01">Laboratorio 10 ASD Progetto Individuale 23/24</span>

I social network (e.g., Facebook) sono piattaforme digitali progettate per connettere utenti in tutto il mondo, creando una
vasta rete di relazioni interpersonali. Al centro di queste piattaforme c’è l’aspetto di rete, che consente agli utenti di costruire
connessioni con amici, familiari, colleghi e persone che condividono interessi comuni.
Una delle caratteristiche distintive di molti social netowork è la possibilità di creare e partecipare a gruppi. Questi gruppi
fungono da comunità virtuali dove gli utenti possono discutere di argomenti specifici, condividere esperienze e collaborare su
progetti comuni. I gruppi possono essere pubblici, permettendo a chiunque di unirsi e partecipare, oppure privati, dove l’accesso
è limitato solo a membri approvati.


## <span style="color:#F18F01"> Compilazione ed esecuzione</span>
```bash
 g++ -std=c++14 network-test.cpp list-array.cpp network.cpp -o social
./social
```

## <span style="color:#F18F01"> Obiettivo</span>

L’obiettivo del laboratorio individuale è quello di implementare le funzionlità di base di un social network focalizzandosi in
particolare sulle funzionalità relative alla gestione degli utenti del social network e dei gruppi di utenti.
Quindi vi viene richiesto di sviluppare un programma in C++ che implementi le funzionlità di base di un social network come
descritto in seguito.

## <span style="color:#F18F01"> Implementazione</span>
Il main per interagire con il social network vi viene già fornito, voi dovrete quindi progettare e implementare il codice delle
funzioni presenti nel file network.cpp che troverete, assieme ad altri file, all’interno del file .zip scaricabile da Aulaweb nella
sezione relativa al laboratorio 10. Più in dettaglio le funzioni da implementare sono le seguenti dichiarate nel file network.h:


### <span style="color:#F18F01"> Note</span>
- Il social network è rappresentato da una struttura dati di tipo Network che contiene le informazioni sui membri del social e sui gruppi creati dagli utenti.
- Ogni <b style="color:#17779A">membro</b> del social network è identificato da un user_Login, che è una stringa di lunghezza variabile.
- Ogni <b style="color:#94524A">gruppo</b> del social network è identificato da un nome, che è una stringa di lunghezza variabile.
- Ogni <b style="color:#17779A">membro</b> del social network può essere amico di altri membri del social network e può essere membro di uno o più gruppi del social network.
- Ogni <b style="color:#94524A">gruppo</b> del social network ha un creatore, che è un membro del social network.




## <span style="color:#F18F01"> ANALISI</span>
- Per prima cosa ho definito le relazioni tra le entità del social network, ovvero i membri e i gruppi.
- Network è una struttura dati che contiene le informazioni sui membri del social e sui gruppi creati dagli utenti, possiamo pensarlo come un contenitore.

### <span style="color:#F18F01"> ENTITA'</span>
#### UTENTE
- Ogni utente del social network è identificato da un user_Login, che è una stringa di lunghezza variabile.
- La lunghezza del nome €[1,∞) 
- Ogni utente può avere amici(altri utenti)
- Ogni utente può essere membro di più gruppi del social network.
- Ogni utente può creare uno o più gruppi.

#### GRUPPO
- Ogni gruppo del social network è identificato da un nome, che è una stringa di lunghezza variabile.
- La lunghezza del nome €[1,∞)
- Ogni gruppo ha un creatore, che è un membro del social network.
- Ogni gruppo può avere uno o più membri.

### <span style="color:#F18F01"> RELAZIONI</span>
- 1 utente può avere 0 o più amici
- 1 utente può essere membro di 0 o più gruppi
- 1 gruppo può avere 1 o più membri
- 1 gruppo ha 1 creatore

### <span style="color:#F18F01"> STRUTTURE DATI</span>

#### SOCIAL NETWORK
- Network è una struttura dati che contiene le informazioni sui membri del social e sui gruppi creati dagli utenti.
- Quando il network ha 0 membri è vuoto. ( 0 membri -> 0 creatori -> 0 gruppi)

```cpp
struct st_Network{
    Users members;
    Groups groups;
};

struct userStruct{
    User_ID user_Login;
    Friendships friends;
};

struct groupStruct{
    User creator;
    Users members;
};
```
### <span style="color:#F18F01"> PERCHE' HO SCELTO AVL</span>

- Ho scelto di utilizzare una struttura dati di tipo AVL-tree per memorizzare utenti, gruppi e relazioni tra utenti e gruppi.
- Questa scelta è stata fatta per garantire una complessità logaritmica per le operazioni di ricerca, inserimento e cancellazione.
- Risulta che alcuni inserimenti di network non siano logaritmici perché vengono richiesti ulteriori controlli.
- Inoltre gli AVL sono alberi ordinati, quindi mi permettono di avere i dati ordinati in base al user_Login e al nome del gruppo.
- L'ordine scelto in questo caso è lessicografico crescente.
### <span style="color:#F18F01"> Funzioni implemetate e complessità</span>

```cpp
 createEmptyNetwork ();
```
- crea una rete vuota.
- complessità O(1)
```cpp
bool isEmpty ( const Network & net );
```
- restituisce true se la rete è vuota, false altrimenti false.
- complessità O(1)
```cpp
bool addMember ( string usr_Log , Network &net );
```
- aggiunge un nuovo membro alla rete. Se il membro è già presente nella rete, la funzione restituisce false, altrimenti true.
- complessità O(log n)
```cpp
bool becomeFriends ( string usr_Log1 , string usr_Log2 , Network &net );
```
-  Rende amici nella network net i membri con user_Login usr_Log1 e usr_Log2
- complessità O(log n)
```cpp
bool areFriends ( string usr_Log1 , string usr_Log2 , const Network &net );
```
- restituisce true se usr_Log1 e usr_Log2 sono amici nella network net, false altrimenti.
- complessità O(log n)
```cpp
bool createGroup ( string usr_Log , string g_Name , Network &net );
```
- crea un nuovo gruppo nella network net. Se il gruppo è già presente nella network, la funzione restituisce false, altrimenti true.
- complessità O(nlog n)
```cpp
bool joinGroup ( string usr_Log , string g_Name , Network &net );
```
- aggiunge usr_Log al gruppo g_Name nella network net. Se usr_Log è già membro del gruppo, la funzione restituisce false, altrimenti true.
- complessità O(log n)
```cpp
bool deleteMember ( string usr_Log , Network &net );
```
- Cancella il membro con user_Login = usr_Log dal network net. Se il membro non è presente nella network, la funzione restituisce false, altrimenti true.
- complessità O(nlog n)
```cpp
bool deleteGroup ( string g_Name , Network &net );
```
- Cancella il gruppo con nome = g_Name dal network net. Se il gruppo non è presente nella network, la funzione restituisce false, altrimenti true.
- complessità O(log n)
```cpp
bool leaveFriendship ( string usr_Log1 , string usr_Log2 , Network &net );
```
- Cancella l’amicizia tra usr_Log1 e usr_Log2 nella network net. Se i due membri non sono amici, la funzione restituisce false, altrimenti true.
- complessità O(log n)
```cpp
bool leaveGroup ( string usr_Log , string g_Name , Network &net );
```
- Cancella usr_Log dal gruppo g_Name nella network net. Se usr_Log non è membro del gruppo, la funzione restituisce false, altrimenti true. Se usr_Log è il creatore del gruppo, il gruppo viene cancellato.
- complessità O(log n)
```cpp
list :: List members ( const Network & net );
```
- restituisce una lista di tutti i membri della network net.
- complessità O(n)
```cpp
list :: List groups ( const Network & net );
```
- restituisce una lista di tutti i gruppi della network net.
- complessità O(n)
```cpp
list :: List friends ( string usr_Log , const Network &net );
```
- restituisce una lista di tutti i membri amici di usr_Log nella network net.
- complessità O(n)
```cpp
list :: List memberOf ( string usr_Log , const Network &net );
```
- restituisce una lista di tutti i gruppi di cui usr_Log è membro nella network net.
- complessità O(nlog(n))
```cpp
list :: List creatorOf ( string usr_Log , const Network &net );
```
- restituisce una lista di tutti i gruppi creati da usr_Log nella network net.
- complessità O(n)
```cpp
bool makeMoreFriends ( string usr_Log , Network &net );
```
- Il membro usr_Log diventa amico con tutti i membri con i quali condivide un gruppo
- complessità O(n*m) dove n è il numero di gruppi e m è il numero di membri di ogni gruppo




### link utili
- [AVL tree](https://en.wikipedia.org/wiki/AVL-tree)
- [AVL geekforgeeks](https://www.geeksforgeeks.org/insertion-in-an-avl-tree/)
- [AVL cppreference](https://en.cppreference.com/w/cpp/container/set)
- [AVL michael sambol](https://youtu.be/DB1HFCEdLxA?si=dHZE1oydTCc3RDir)
- [AVL Back to Back SWE](https://youtu.be/vRwi_UcZGjU?si=a3S-EDeg_qbx2fJG)





