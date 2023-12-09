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

```

### Trial 2

``` bash

```

### Trial 3

``` bash

```


## Output (Success: GoFish)

### Trial 1

``` bash

```

### Trial 2

``` bash

```

### Trial 3

``` bash

```
