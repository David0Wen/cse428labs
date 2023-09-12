# Lab 0
## Group members 
- Ruoyao Wen (ruoyao@wustl.edu)
- Wanzhou Liu (l.wanzhou@wustl.edu)
- Zherui Zhou (zherui@wustl.edu)

---

## design decisions
In function "print" of PinochleDeck and HoldEmDeck, we use an iterator to traverse the whole deck. When we push cards onto the deck, they are ordered in a circular manner, so when printing the deck, each time we print a card with "spade" suit, we also print an extra "Enter" , this makes the output more readable.

##  error observations

### compile error
``` C++
./Card_T.cpp:13:11: error: use of undeclared identifier ‘myRank’
    os << myRank << mySuit;
          ^
./Card_T.cpp:13:21: error: use of undeclared identifier ‘mySuit’
    os << myRank << mySuit;
                    ^
./Card_T.cpp:11:59: warning: unused parameter ‘myCard’ [-Wunused-parameter]
std::ostream &operator<<(std::ostream &os, const Card<T> &myCard)
                                                          ^
PinochleDeck.cpp:43:10: warning: equality comparison result unused [-Wunused-comparison]
                myRank ==PinochleRank::jack;
                ~~~~~~~^~~~~~~~~~~~~~~~~~~~
PinochleDeck.cpp:43:10: note: use ‘=‘ to turn this equality comparison into an assignment
                myRank ==PinochleRank::jack;
                       ^~
                       =
PinochleDeck.cpp:47:10: warning: equality comparison result unused [-Wunused-comparison]
                myRank ==PinochleRank::queen;
                ~~~~~~~^~~~~~~~~~~~~~~~~~~~~
PinochleDeck.cpp:47:10: note: use ‘=‘ to turn this equality comparison into an assignment
                myRank ==PinochleRank::queen;
                       ^~
                       =
PinochleDeck.cpp:51:10: warning: equality comparison result unused [-Wunused-comparison]
                myRank ==PinochleRank::king;
                ~~~~~~~^~~~~~~~~~~~~~~~~~~~
PinochleDeck.cpp:51:10: note: use '=' to turn this equality comparison into an assignment
                myRank ==PinochleRank::king;
                       ^~
                       =
PinochleDeck.cpp:55:10: warning: equality comparison result unused [-Wunused-comparison]
                myRank ==PinochleRank::ten;
                ~~~~~~~^~~~~~~~~~~~~~~~~~~
PinochleDeck.cpp:55:10: note: use '=' to turn this equality comparison into an assignment
                myRank ==PinochleRank::ten;
                       ^~
                       =
PinochleDeck.cpp:59:10: warning: equality comparison result unused [-Wunused-comparison]
                myRank ==PinochleRank::ace;
                ~~~~~~~^~~~~~~~~~~~~~~~~~~
PinochleDeck.cpp:59:10: note: use '=' to turn this equality comparison into an assignment
                myRank ==PinochleRank::ace;
                       ^~
                       =
PinochleDeck.cpp:63:10: warning: equality comparison result unused [-Wunused-comparison]
                myRank ==PinochleRank::undefined;
                ~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~
PinochleDeck.cpp:63:10: note: use '=' to turn this equality comparison into an assignment
                myRank ==PinochleRank::undefined;
                       ^~
                       =
PinochleDeck.cpp:85:40: warning: unused parameter 'os' [-Wunused-parameter]
void PinochleDeck::print(std::ostream &os)
                                       ^
8 warnings and 2 errors generated.
```
In Card_T.cpp, when implenmenting the shift operator, we coded the "=" operator as "==" by mistake.


### run error
We don't have run error.
