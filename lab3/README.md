# Lab 3

## Group members

- Ruoyao Wen (ruoyao@wustl.edu)
- Wanzhou Liu (l.wanzhou@wustl.edu)
- Zherui Zhou (zherui@wustl.edu)

---

## Design decisions
### 8
We didn't add our own copy constructor because the default copy constructor used in this case is deep copy. So the default constructor already satisfied the requirement.

### 10
To assign names to each melds, we create a static member string array to assign corresponding name to each enum numbers. Same method to assign points.

### 13
To ensure melds found in a previous hand should not be carried over into the next one - the vector must be empty before each call to the evaluation function, we define the melds vector as a local variable, so that when entering each loop, the melds vector will be re-initialized.

### 14
Same method as 10, we created a static member string array.

### 16
To store name of each player in our nested class, we decide to simply store the name index as an unsigned int, which should be the cooresponding name's index in the name array, solving the reference conflict.

To compare the HandRank of Texas Hold'em, we apply a recursive manner, i.e., for two pairs, we firstly compare the first pair. If the first pair's rank is same, we simply delete the pair and reduce it to the pair case.

## Error observations

### Compile error/warning

We don't have any compile error.

### Run error

``` C++
// Combine the player's hand with the common board
            std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();
            std::vector< Card<HoldEmRank, Suit> > playerSet = playerState.playerHand.*setPtr;
            std::vector< Card<HoldEmRank, Suit> > boardSet = commonBoard.*setPtr;

// Combine the player's hand with the common board
playerSet.insert(playerSet.end(), boardSet.begin(), boardSet.end());
```

The combination did't work at first. Then we found that the variable was defined and only modified in the for loop scope. So we change to use pointer to change the value in the real playerState's cardSet.

``` C++
std::vector<Card<HoldEmRank, Suit> >* playerSetPtr = &(playerState.playerHand.*CardSet<HoldEmRank, Suit>::getSetPtr());
std::vector<Card<HoldEmRank, Suit> >* boardSetPtr = &(commonBoard.*CardSet<HoldEmRank, Suit>::getSetPtr());

playerSetPtr->insert(playerSetPtr->end(), boardSetPtr->begin(), boardSetPtr->end());
```

The run error has been solved.

## Output (Exceptions)

### Trial 1

``` bash
$ ./lab2
Usage: lab2 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
1
```

### Trial 2

``` bash
$ ./lab2 HoldEm
Usage: lab2 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
2
```

### Trial 3

``` bash
$ ./lab2 UnknownGame Tom
Usage: lab2 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
3
```

## Output (Success: Pinochle)

### Trial 1

``` bash
$ ./lab2 Pinochle Amy Bob Cendy David
Welcome to Pinochle!
Name: Amy
10D QS AC AD 9S KC
9C QH JS QC 9C 10H

No possible melds!

Name: Bob
AH QS KH AC JH QD
JC 10S 10C 9S JC JD

Possible melds:
pinochle 40

Name: Cendy
9D 9H AH KS 9H KD
KD QD 10C 10S QH KC

No possible melds!

Name: David
10H AS AD KH JS JH
QC 10D JD 9D KS AS

No possible melds!
```

### Trial 2

```bash
Do you want to end the game? (type yes to end):
d
Starting a new round...
Name: Amy
9H 9C QH JS KH AH
10H AC JC KC AD 9H

No possible melds!

Name: Bob
AS QS 10S QC KD QD
QH 9C KS KD 9D 9S

Possible melds:
sixtyqueens 60

Name: Cendy
AC KC 10D AD JD JH
KS QC JD 10D 10C JS

No possible melds!

Name: David
QS QD 9S 10H JC KH
AH 10S 9D JH 10C AS

No possible melds!
```

### Trial 3

```bash
Do you want to end the game? (type yes to end):
n
Starting a new round...
Name: Amy
10H 9D QC QS 10D AD
JS JC 9C KD QS QC

No possible melds!

Name: Bob
9C AC AH 10C AD QD
QD JD 10D 9S AS QH

Possible melds:
hundredaces 100

Name: Cendy
10S 10C JH KC KS 10H
AH 9D AC AS KH 9S

No possible melds!

Name: David
KH KD 9H KC JH 10S
JD 9H JS KS QH JC

Possible melds:
eightykings 80
fortyjacks 40
```

## Output (Success: HoldEm)

### Trial 1

``` bash
$ ./lab2 HoldEm Amy Bob Cendy David
Welcome to Texas Hold'Em!
Name: Amy
8S 3D


Name: Bob
7D 8C


Name: Cendy
AS 3S


Name: David
QC QD


BOARD (flop):
QH JH AD


Ranking of players and cards:
Player: David
Hand: AD QH QD QC JH

Rank: Three of a Kind


Player: Cendy
Hand: AS AD QH JH 3S

Rank: Pair


Player: Bob
Hand: AD QH JH 8C 7D

Rank: High Card


Player: Amy
Hand: AD QH JH 8S 3D

Rank: High Card


BOARD (turn):
QH JH AD JS
BOARD (river):
QH JH AD JS JC
```

### Trial 2

``` bash
Do you want to end the game? (type yes to end):
n
Starting a new round...
Name: Amy
AC 3D


Name: Bob
KS 6D


Name: Cendy
4H JH


Name: David
9D 2C


BOARD (flop):
AD 3C AS


Ranking of players and cards:
Player: Amy
Hand: AS AD AC 3D 3C

Rank: Full House


Player: Bob
Hand: AS AD KS 6D 3C

Rank: Pair


Player: Cendy
Hand: AS AD JH 4H 3C

Rank: Pair


Player: David
Hand: AS AD 9D 3C 2C

Rank: Pair


BOARD (turn):
AD 3C AS JC
BOARD (river):
AD 3C AS JC 8C
```

### Trial 3

``` bash
Do you want to end the game? (type yes to end):
d
Starting a new round...
Name: Amy
10S AH


Name: Bob
8H 2H


Name: Cendy
5S 7D


Name: David
QC 4C


BOARD (flop):
KH QH 6H


Ranking of players and cards:
Player: Bob
Hand: KH QH 8H 6H 2H

Rank: Flush


Player: David
Hand: KH QH QC 6H 4C

Rank: Pair


Player: Amy
Hand: AH KH QH 10S 6H

Rank: High Card


Player: Cendy
Hand: KH QH 7D 6H 5S

Rank: High Card


BOARD (turn):
KH QH 6H JS
BOARD (river):
KH QH 6H JS 9D
```

This is the final version of our Lab2.
