# Lab 0
## Group members 
- Ruoyao Wen (ruoyao@wustl.edu)
- Wanzhou Liu (l.wanzhou@wustl.edu)
- Zherui Zhou (zherui@wustl.edu)

---

## Design decisions
In function "print" of PinochleDeck and HoldEmDeck, we use an iterator to traverse the whole deck. When we push cards onto the deck, they are ordered in a circular manner, so when printing the deck, each time we print a card with "spade" suit, we also print an extra "Enter" , this makes the output more readable.

## Error observations

### Compile error/warning
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
#### Problems found:
- In Card_T.cpp, when implenmenting the shift operator, we coded the "=" operator as "==" by mistake.
- In PinochleDeck and HoldEmDeck, we forget to use the parameter "std::ostream &os". Instead, we directly output the content to std::cout.
#### After fix these bugs, the program doesn't trigger errors/warnings anymore

### Run error
We don't have run error.

## Output
### Trial 1
``` bash
Pinochle Deck:
9C 9D 9H 9S JC JD JH JS QC QD QH QS KC KD KH KS 10C 10D 10H 10S AC AD AH AS 9C 9D 9H 9S JC JD JH JS QC QD QH QS KC KD KH KS 10C 10D 10H 10S AC AD AH AS
Texas Hold'em Deck:
2C 2D 2H 2S 3C 3D 3H 3S 4C 4D 4H 4S 5C 5D 5H 5S 6C 6D 6H 6S 7C 7D 7H 7S 8C 8D 8H 8S 9C 9D 9H 9S 10C 10D 10H 10S JC JD JH JS QC QD QH QS KC KD KH KS AC AD AH AS
```
At first, wen didn't add any enter to the output. The bash output is less readable. We decided to add enters to every card with suit spade.
### Trial 2
``` bash
Pinochle Deck:
9C 9D 9H 9S
JC JD JH JS
QC QD QH QS
KC KD KH KS
10C 10D 10H 10S
AC AD AH AS
9C 9D 9H 9S
JC JD JH JS
QC QD QH QS
KC KD KH KS
10C 10D 10H 10S
AC AD AH AS

Texas Hold'em Deck:
2C 2D 2H 2S
3C 3D 3H 3S
4C 4D 4H 4S
5C 5D 5H 5S
6C 6D 6H 6S
7C 7D 7H 7S
8C 8D 8H 8S
9C 9D 9H 9S
10C 10D 10H 10S
JC JD JH JS
QC QD QH QS
KC KD KH KS
AC AD AH AS

```
This is the final version of our Lab0.
