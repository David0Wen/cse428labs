# Lab 3

## Group members

- Ruoyao Wen (ruoyao@wustl.edu)
- Wanzhou Liu (l.wanzhou@wustl.edu)
- Zherui Zhou (zherui@wustl.edu)

---

## Design decisions
### 8


## Error observations

### Compile error/warning

#### 1
``` C++
In file included from GoFishGame_T.h:53,
                 from lab3.cpp:15:
GoFishGame_T.cpp: In instantiation of ‘void GoFishGame<S, R, D>::deal() [with S = Color; R = UnoRank; D = UnoDeck]’:
GoFishGame_T.h:49:18:   required from here
GoFishGame_T.cpp:179:24: error: no match for ‘operator>>’ (operand types are ‘UnoDeck’ and ‘CardSet<UnoRank, Color>*’)
                 myDeck >> &hand;
                 ~~~~~~~^~~~~~~~
In file included from CardSet_T.h:70,
                 from Deck_T.h:9,
                 from PinochleDeck.h:14,
                 from lab3.cpp:7:
CardSet_T.cpp:50:16: note: candidate: ‘CardSet<R, S>& CardSet<R, S>::operator>>(CardSet<R, S>&) [with R = UnoRank; S = Color]’
 CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &other) {
                ^~~~~~~~~~~~~
CardSet_T.cpp:50:16: note:   no known conversion for argument 1 from ‘CardSet<UnoRank, Color>*’ to ‘CardSet<UnoRank, Color>&’
In file included from GoFishGame_T.h:53,
                 from lab3.cpp:15:
GoFishGame_T.cpp: In instantiation of ‘void GoFishGame<S, R, D>::deal() [with S = Suit; R = PinochleRank; D = PinochleDeck]’:
GoFishGame_T.h:49:18:   required from here
GoFishGame_T.cpp:179:24: error: no match for ‘operator>>’ (operand types are ‘PinochleDeck’ and ‘CardSet<PinochleRank, Suit>*’)
                 myDeck >> &hand;
                 ~~~~~~~^~~~~~~~
In file included from CardSet_T.h:70,
                 from Deck_T.h:9,
                 from PinochleDeck.h:14,
                 from lab3.cpp:7:
CardSet_T.cpp:50:16: note: candidate: ‘CardSet<R, S>& CardSet<R, S>::operator>>(CardSet<R, S>&) [with R = PinochleRank; S = Suit]’
 CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &other) {
                ^~~~~~~~~~~~~
CardSet_T.cpp:50:16: note:   no known conversion for argument 1 from ‘CardSet<PinochleRank, Suit>*’ to ‘CardSet<PinochleRank, Suit>&’
In file included from GoFishGame_T.h:53,
                 from lab3.cpp:15:
GoFishGame_T.cpp: In instantiation of ‘void GoFishGame<S, R, D>::deal() [with S = Suit; R = HoldEmRank; D = HoldEmDeck]’:
GoFishGame_T.h:49:18:   required from here
GoFishGame_T.cpp:179:24: error: no match for ‘operator>>’ (operand types are ‘HoldEmDeck’ and ‘CardSet<HoldEmRank, Suit>*’)
                 myDeck >> &hand;
                 ~~~~~~~^~~~~~~~
In file included from CardSet_T.h:70,
                 from Deck_T.h:9,
                 from PinochleDeck.h:14,
                 from lab3.cpp:7:
CardSet_T.cpp:50:16: note: candidate: ‘CardSet<R, S>& CardSet<R, S>::operator>>(CardSet<R, S>&) [with R = HoldEmRank; S = Suit]’
 CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &other) {
                ^~~~~~~~~~~~~
CardSet_T.cpp:50:16: note:   no known conversion for argument 1 from ‘CardSet<HoldEmRank, Suit>*’ to ‘CardSet<HoldEmRank, Suit>&’
make: *** [lab3] Error 1
```
#### Solution
Modify ```myDeck >> &hand;``` to ```myDeck >> hand;```

#### 2
``` C++
In file included from GoFishGame_T.h:55,
                 from lab3.cpp:15:
GoFishGame_T.cpp: In instantiation of ‘bool GoFishGame<S, R, D>::turn(int) [with S = Color; R = UnoRank; D = UnoDeck]’:
GoFishGame_T.cpp:227:20:   required from ‘int GoFishGame<S, R, D>::play() [with S = Color; R = UnoRank; D = UnoDeck]’
GoFishGame_T.h:26:17:   required from here
GoFishGame_T.cpp:100:23: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<std::__cxx11::basic_string<char> >::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
     for (int i = 0; i < playerNames.size(); i++)
                     ~~^~~~~~~~~~~~~~~~~~~~
GoFishGame_T.cpp: In instantiation of ‘bool GoFishGame<S, R, D>::turn(int) [with S = Suit; R = PinochleRank; D = PinochleDeck]’:
GoFishGame_T.cpp:227:20:   required from ‘int GoFishGame<S, R, D>::play() [with S = Suit; R = PinochleRank; D = PinochleDeck]’
GoFishGame_T.h:26:17:   required from here
GoFishGame_T.cpp:100:23: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<std::__cxx11::basic_string<char> >::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
GoFishGame_T.cpp: In instantiation of ‘bool GoFishGame<S, R, D>::turn(int) [with S = Suit; R = HoldEmRank; D = HoldEmDeck]’:
GoFishGame_T.cpp:227:20:   required from ‘int GoFishGame<S, R, D>::play() [with S = Suit; R = HoldEmRank; D = HoldEmDeck]’
GoFishGame_T.h:26:17:   required from here
GoFishGame_T.cpp:100:23: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<std::__cxx11::basic_string<char> >::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
```

#### Solution
Modify ```for (int i = 0; i < playerNames.size(); i++)``` to ```for (size_t i = 0; i < playerNames.size(); i++)```

### Run error

We don't have any run errors.

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
