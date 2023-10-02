# Lab 1
## Group members 
- Ruoyao Wen (ruoyao@wustl.edu)
- Wanzhou Liu (l.wanzhou@wustl.edu)
- Zherui Zhou (zherui@wustl.edu)

---

## Design decisions


## Error observations


### Compile error/warning


#### Problems found:


#### After fix these bugs, the program doesn't trigger errors/warnings anymore.

### Run error
``` bash
$ ./lab1 HoldEm Amy Bob Cendy David
Welcome to Texas Hold'Em!
Name: Amy
3C KC 

Name: Bob
10D QH 

Name: Cendy
7S KS 

Name: David
AS QD 

BOARD (flop):
JD 7H 5H BOARD (turn):
JD 7H 5H 2D BOARD (river):
JD 7H 5H 2D KD
```

## Output (Exceptions)
### Trial 1
``` bash
$ ./lab1
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
1
```
### Trial 2
``` bash
$ ./lab1 HoldEm
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
2
```
### Trial 3
``` bash
$ ./lab1 UnknownGame Tom
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
3
```
### Trial 4
``` bash
$ ./lab1 Pinochle Amy Bob Cendy
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
2
```
### Trial 5
``` bash
$ ./lab1 Pinochle Amy Bob Cendy David Emily
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
2
```
### Trial 6
``` bash
$ ./lab1 HoldEm Amy
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
2
```
### Trial 7
``` bash
$ ./lab1 HoldEm Amy Bob Cendy David Emily Frank Green Hallen Ivan Jack
Usage: lab1 <Game> <Players>
Game should be either Pinochle or HoldEm.
Pinochle needs 4 players.
HoldEm needs 2-9 players.
$ echo $?
2
```
## Output (Success)
### Trial 1
``` bash
$ ./lab1 Pinochle Amy Bob Cendy David
Welcome to Pinochle!
Name: Amy
KS QH JC JS AD QS 
JC 10S JH KS 10D JS 

Name: Bob
QC 9S 9C JD AD 9H 
9D 9H KH JH 10C AC 

Name: Cendy
KC AH KD KD 10H QH 
AS 9C QD QS 10H QD 

Name: David
9S AC QC 9D 10S 10D 
KH JD AS KC 10C AH 

Do you want to end the game? (type yes to end): 
no
Starting a new round...
Name: Amy
QC JC KH KS AH QS 
QD KH KS JD 10S 10H 

Name: Bob
AS KC AH 9C JS QH 
AC JH JC 9D JH JD 

Name: Cendy
AS QS 9H 10C 9C 10C 
JS 9D QH KD QD 9H 

Name: David
QC KD 10D AD AC 10D 
9S 10H 10S KC 9S AD 

Do you want to end the game? (type yes to end): 
yes
Thanks for playing Pinochle!
$ echo $?
0
```
### Trial 2
``` bash
$ ./lab1 HoldEm Amy Bob Cendy David
Welcome to Texas Hold'Em!
Name: Amy
9S 10S 


Name: Bob
3D JD 


Name: Cendy
JS 10H 


Name: David
6C 6D 


BOARD (flop):
QS JH 9H 
BOARD (turn):
QS JH 9H 9C 
BOARD (river):
QS JH 9H 9C KC 

Do you want to end the game? (type yes to end): 
yes
Thanks for playing Texas Hold'Em!
$ echo $?
0
```
### Trial 3
``` bash
$ ./lab1 HoldEm Amy Bob Cendy David
Welcome to Texas Hold'Em!
Name: Amy
3H 5H 


Name: Bob
8C 4D 


Name: Cendy
10D 9D 


Name: David
JH 3C 


BOARD (flop):
6C 3S KS 
BOARD (turn):
6C 3S KS AD 
BOARD (river):
6C 3S KS AD 5D 

Do you want to end the game? (type yes to end): 
no
Starting a new round...
Name: Amy
3H 4S 


Name: Bob
7D QC 


Name: Cendy
7H AD 


Name: David
9S 5D 


BOARD (flop):
2C 7S 8D 
BOARD (turn):
2C 7S 8D 5S 
BOARD (river):
2C 7S 8D 5S 9C 

Do you want to end the game? (type yes to end): 
yes
Thanks for playing Texas Hold'Em!
$ echo $?
0
```