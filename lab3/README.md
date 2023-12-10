# Lab 3

## Group members

- Ruoyao Wen (ruoyao@wustl.edu)
- Wanzhou Liu (l.wanzhou@wustl.edu)
- Zherui Zhou (zherui@wustl.edu)

---

## Design decisions

### Different prompts according to different deck selection
GoFish can use three different kind of decks, and using different deck will cause some difference when player input the rank.

We construct a static string vector data member, so that different deck(assigned with different ID) will have different prompt.

### User input during GoFish game
We want to let user to input integer as rank ID and player ID. If user input non-integer value, a prompt should be shown and the cin should be cleared, ready to receive new input.

We use following code fragment to realize mentioned function:
``` C++
while (!(std::cin >> requestedRank)) {
    std::cout << "Integer required! Please enter again:";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

### ```collect_books```
Since 4-of-a-kind has ambiguity when a rank has more than 4 cards in a deck (such as Pinochie deck, for each rank there is 8 cards: 2 cards for each suit), we simply consider four card in one rank as 4-of-a-kind regradless of its suits. This is suitable for "4-of-a-kind" literal meaning and doesn't affect GoFish playing.

### ```turn```
- If a player has no cards in its hand and the deck is not empty, no matter what rank it request, one card will be drawed from the deck to its hand.
- If a player collect a book after drawing a card from the deck, the method will return ```true``` (This player can play a new turn).

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
$ ./lab3 GoFish
Usage: lab3 <Game> [<Deck>] <Players>
Game should be either Pinochle, HoldEm, or GoFish.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
GoFish needs 2-5 players.
$ echo $?
2
```

### Trial 2

``` bash
$ ./lab3 GoFish myDeck A1 B2
Must provide valid Deck for GoFish: HoldEm, Pinochle or Uno
$ echo $?
5
```

### Trial 3

``` bash
$ ./lab3 GoFish Uno A1 
Usage: lab3 <Game> [<Deck>] <Players>
Game should be either Pinochle, HoldEm, or GoFish.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
GoFish needs 2-5 players.
$ echo $?
2
```

### Trial 4

``` bash
$ ./lab3 GoFish Uno A1 B2 C3 D4 E5 F6
Usage: lab3 <Game> [<Deck>] <Players>
Game should be either Pinochle, HoldEm, or GoFish.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
GoFish needs 2-5 players.
$ echo $?
2
```


## Output (Success: GoFish)

``` bash
$ ./lab3 GoFish Pinochle A1 B2 C3 D4 E5
Player A1, ID: 1
Current hand:
QH 10H AS 9D AD

Current book:
No book collected.

Player B2, ID: 2
Current hand:
AS KS 9D 10H AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
AC JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
AH KH 9C 9H JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 1
Enter player ID to ask from: 2
Invalid Rank Number!
Enter card rank number to ask for: 0
Enter player ID to ask from: 6
Invalid Player ID!
Enter card rank number to ask for: 1
Enter player ID to ask from: 6
Invalid Rank Number!
Invalid Player ID!
Enter card rank number to ask for: 0
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H AS 9D AD 9D

Current book:
No book collected.

Player B2, ID: 2
Current hand:
AS KS 10H AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
AC JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
AH KH 9C 9H JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H AS 9D AD 9D 9C

Current book:
No book collected.

Player B2, ID: 2
Current hand:
AS KS 10H AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
AC JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
AH KH 9H JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H AS AD

Current book:
9D 9D 9C 9H

Player B2, ID: 2
Current hand:
AS KS 10H AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
AC JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
AH KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H AS AD AH

Current book:
9D 9D 9C 9H

Player B2, ID: 2
Current hand:
AS KS 10H AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
AC JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H

Current book:
9D 9D 9C 9H
AS AD AH AC

Player B2, ID: 2
Current hand:
AS KS 10H AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 2
Invalid Rank Number!
Enter card rank number to ask for: 4
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H 10H

Current book:
9D 9D 9C 9H
AS AD AH AC

Player B2, ID: 2
Current hand:
AS KS AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC 10D QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H 10H 10D

Current book:
9D 9D 9C 9H
AS AD AH AC

Player B2, ID: 2
Current hand:
AS KS AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC QS JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H 10H 10D QS

Current book:
9D 9D 9C 9H
AS AD AH AC

Player B2, ID: 2
Current hand:
AS KS AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
QH JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 5
Successfully Collected!

Player A1, ID: 1
Current hand:
QH 10H 10H 10D QS QH

Current book:
9D 9D 9C 9H
AS AD AH AC

Player B2, ID: 2
Current hand:
AS KS AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QS QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 5
Successfully Collected!

Player A1, ID: 1
Current hand:
10H 10H 10D

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 2
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
KH JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 3
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 3
Enter player ID to ask from: 5
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH JD

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 1
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
JC JD JD

Current book:
No book collected.

Player D4, ID: 4
Current hand:
JC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 1
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 5
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
KC

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player D4's turn. ID: 4

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 2
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
KC

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
KC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC

Current book:
No book collected.


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 1
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

End of Round 1
Player A1, ID: 1
Number of books collected: 3
Player B2, ID: 2
Number of books collected: 0
Player C3, ID: 3
Number of books collected: 1
Player D4, ID: 4
Number of books collected: 0
Player E5, ID: 5
Number of books collected: 0

Player A1, ID: 1
Current hand:
10H 10H 10D 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
KC

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
KC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 2
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
KC

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
KC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 2
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AS KS AH KH

Current book:
No book collected.

Player C3, ID: 3
Current hand:
KC

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
KC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 3
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AS KS AH KH KC

Current book:
No book collected.

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
KC

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for:
3
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AS AH

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 3
Enter player ID to ask from: 5
Invalid Rank Number!
Enter card rank number to ask for: 5
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AS AH QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AS AH QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
AH QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 5
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH 9S

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player D4's turn. ID: 4

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 5
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C QD

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH 9S

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH

Current book:
No book collected.


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 1
Successfully Collected!

Player A1, ID: 1
Current hand:
9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QD

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH 9S

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD

Current book:
No book collected.


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH 9S

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD

Current book:
No book collected.


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 2
Go Fish! Draw a card from the deck.

End of Round 2
Player A1, ID: 1
Number of books collected: 4
Player B2, ID: 2
Number of books collected: 1
Player C3, ID: 3
Number of books collected: 1
Player D4, ID: 4
Number of books collected: 0
Player E5, ID: 5
Number of books collected: 0

Player A1, ID: 1
Current hand:
9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH 9S

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD

Current book:
No book collected.


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 3
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD

Current book:
No book collected.


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QC

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD

Current book:
No book collected.


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 5
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QC

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH KD

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD

Current book:
No book collected.


Player D4's turn. ID: 4

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QC

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH KD

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S KS

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD

Current book:
No book collected.


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 3
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QC

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S KS

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC KH QD QD KD KD

Current book:
No book collected.


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 3
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:
QC

Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH QC QD QD

Current book:
KH KD KD KS


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 2
Enter player ID to ask from: 2
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S JS

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH

Current book:
KH KD KD KS
QC QD QD QC


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 1
Enter player ID to ask from: 1
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
JH JH JS

Current book:
KH KD KD KS
QC QD QD QC


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 1
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AD AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
AC

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AS AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
AC AD

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:
AH

Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
AC AD AS

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 5
Enter player ID to ask from: 3
Successfully Collected!

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9C 9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9H

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 1
Successfully Collected!

Player A1, ID: 1
Current hand:
9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9H 9C

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 1
Successfully Collected!

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9H 9C 9S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player E5's turn. ID: 5

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 1
Go Fish! Draw a card from the deck.

End of Round 3
Player A1, ID: 1
Number of books collected: 4
Player B2, ID: 2
Number of books collected: 1
Player C3, ID: 3
Number of books collected: 1
Player D4, ID: 4
Number of books collected: 0
Player E5, ID: 5
Number of books collected: 4

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9H 9C 9S 10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 5
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
9S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9H 9C 9S 10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 5
Successfully Collected!

Player A1, ID: 1
Current hand:
9S 9H

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9C 9S 10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 5
Successfully Collected!

Player A1, ID: 1
Current hand:
9S 9H 9C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
9S 10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 0
Enter player ID to ask from: 5
Successfully Collected!

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 4
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:
10C

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:
10S

Current book:
No book collected.

Player E5, ID: 5
Current hand:
10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 4
Successfully Collected!

Player A1, ID: 1
Current hand:
10C 10S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:
10S

Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 5
Successfully Collected!

Player A1, ID: 1
Current hand:
10C 10S 10S

Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 4
Go Fish! Draw a card from the deck.

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S
10C 10S 10S 10C

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player A1's turn. ID: 1

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 4
Go Fish and deck is empty! You're out.

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S
10C 10S 10S 10C

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player B2's turn. ID: 2

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 4
Go Fish and deck is empty! You're out.

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S
10C 10S 10S 10C

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player C3's turn. ID: 3

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 2
Invalid Player ID!
Enter card rank number to ask for: 4
Enter player ID to ask from: 1
Invalid Player ID!
Enter card rank number to ask for: 4
Enter player ID to ask from: 3
Invalid Player ID!
Enter card rank number to ask for: 4
Enter player ID to ask from: 4
Go Fish and deck is empty! You're out.

Player A1, ID: 1
Current hand:


Current book:
9D 9D 9C 9H
AS AD AH AC
QH QS QH QS
10H 10H 10D 10D
9S 9H 9C 9S
10C 10S 10S 10C

Player B2, ID: 2
Current hand:


Current book:
KS KH KC KC

Player C3, ID: 3
Current hand:


Current book:
JC JD JD JC

Player D4, ID: 4
Current hand:


Current book:
No book collected.

Player E5, ID: 5
Current hand:


Current book:
KH KD KD KS
QC QD QD QC
JH JH JS JS
AC AD AS AH


Player D4's turn. ID: 4

For Pinochle Deck, rank is 9, J, Q, K,
10, A; corresponding rank number is 0-5.

Enter card rank number to ask for: 4
Enter player ID to ask from: 5
Go Fish and deck is empty! You're out.

End of Round 4
Player A1, ID: 1
Number of books collected: 6
Player B2, ID: 2
Number of books collected: 1
Player C3, ID: 3
Number of books collected: 1
Player D4, ID: 4
Number of books collected: 0
Player E5, ID: 5
Number of books collected: 4

Game End! Players: A1 collected the most books!
$ echo $?
0
```
