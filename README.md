# blackjack_academy

# Basic rules of (casino) blackjack

## Basic setup
All players compete against the dealer, trying to get their card total closer to 21 without going over.  All cards are their face value (2-10 on the number cards), JQK are 10, Ace can be 1 or 11 (whichever value is better for the hand).

If the player is dealt a "blackjack" (getting 21 on first two cards), the player gets a bonus (common bonuses are 3:2, 2:1, 6:5, 7:5).  The "shoe" is the "deck" of cards that is played with, but consists of one to as many as eight decks of cards (in theory there can be n number of decks, but in practice most casinos won't go past 8).  If the player wins without getting a blackjack they win the amount that they bet.  If the dealer's hand (last to be resolved) is higher than the player or the player busts (goes over 21), the house wins and the player loses their bet.

## Game flow
Bets are placed before any cards are dealt.  There is a minimum and a maximum bet size usually that depends on the table.

All players are initially dealt one card (player cards are always face up) from (dealer's) left to right face-up.  Then a card is dealt to the dealer face-down.  The dealer then deals the second card to each player. Then a card is dealt to the dealer face-up.

(Insurance rule) if the dealer's face-up card has value 10 or 11, the players can bet that the dealer has blackjack.  They can bet up to half their original bet.  If the dealer has blackjack they win 2 to 1.

The dealer hand is checked for blackjack.  If the dealer has blackjack the hand ends and bet win/losses are calculated.

When it is the player's turn there are 2 main options and 3 options that require preconditions:

Hit - dealer deals them another face up card adding to their total
Stay - the player ends their turn
Split (preconditions)- If the player is dealt two identical value cards (10, J, Q, K are all same), they may split and play both cards as new hands.  This can be done to start 3 hands, but no more.
Double down (preconditions)- This action is only allowed if the player's hand consists of two cards (splits can be doubled down on).  The player can bet more (up to their original amount) and recieves only one card (ie this action amounts to Bet, Hit, Stay)
Surrender - Player loses half their bet after looking at their initial two cards.  There are two varieties.  Early Surrender, where the player quits before the dealer checks for blackjack.  Late surrender is quitting after the dealer checks for blackjack.

# Win Loss Condition
Players that get a higher score than the dealer without busting win their hand.  Lesser score than the dealer results in a loss.  A tie is called a push and can be a player loss, win, or the return of the bet money.

## Dealer play
The dealer has a set algorithm they must use to play.  The dealer can only hit or stay.  The dealer must hit until they reach 17 or greater (ie if they have 16 or less).

## Shoe management
Start of a shoe, the dealer deals a card direct to discard (called the "burn" card, no one sees the value of this card).  Reshuffling rules vary by casino, but a common practice is to have a marker card (this is not a playing card, it's a blank card) about a deck and a half from the end of the end of the shoe.  When this marker card is encountered in the deal, the shoe will be entirely reshuffled at the end of the current round.

# Perfect play
Since the player plays directly against the dealer and the dealer has a set algorithm to follow, the probabilities of given events are very calculable.  Since the probabilities are calculable, the rules around "perfect play" can be figured out.  Here "perfect play" means that if there is no knowledge of face-down cards values.

NOTE: For the purposes of this project near perfect play will be the standard as house rules can alter the precise implementation of perfect play

## Sources on Perfect play
### Good series of charts and 30 phrases defining perfect play
https://www.blackjackapprenticeship.com/blackjack-strategy-charts/


#Basic Layout of Code

##Important objects

()()()  General Logic
         - All cards stay in same memory and pointers determine where each card is (player #, dealer, discard, shoe)
         - 

Game Object:
 - Rule variations values
   - shoe reshuffling value
   - blackjack payout
   - {}{} add more variants
 - Player Data (n players and a dealer)
 - Current player turn
 - Number of players in game
 - Dealer face-up card
 - Active player hand 
 
Player Data:
 - Player money
 - Current hand(s) [splits will result in multiple hands]
 - Player number (Player 1 will be the human player)

Dealer Data (Player 0):
  # inherit from player
 - Current hand
 - Dealer number

Virtual hand:
  - Current cards

Player hand:
  # Inherit from Virtual hand
  # Most values on this should be recalculated everytime a hand is dealt
 - Soft score, hard score (if aces are in the hand the hand has multiple values) (flag value)
 - Possible hand values (what all possible numerical hand values are, (ie aces))
 - Hand numerical value (maximum of the possible hand values)

Discard hand:
  # Inherit from Virtual hand

Shoe hand:
  # Inherit from Virtual hand

Legal Cards (Card):
  # On instantiation n number of 52 card sets should be generated
 - Card ID (a number that makes each card unique)
 - Card Suit
 - Card Rank (eg 2, 4, J, Q, A)

All Cards (AllCards):
  # On instantiation n number of 52 card sets should be generated
 - Card ID (a number that makes each card unique)
 - Card Suit
 - Card Rank (eg 2, 4, J, Q, A)


Player Logic:
  # On separate thread for each player
  # Governs what computer players will do
  # Should have access to the hand
  # Dealer logic pattern should be a type here
  



Plan for bots
  Start thread when bot player is made (this can allow for different bot logic to be added)
  Send player and dealer state info to bot thread via promise
  Use future to get player action and execute action
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
# Ruberic Notes

README (All Rubric Points REQUIRED)

CRITERIA
MEETS SPECIFICATIONS
A README with instructions is included with the project

The README is included with the project and has instructions for building/running the project.

If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions.

You can submit your writeup as markdown or pdf.

The README indicates which project is chosen.

The README describes the project you have built.

The README also indicates the file and class structure, along with the expected behavior or output of the program.

The README includes information about each rubric point addressed.

The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.

Compiling and Testing (All Rubric Points REQUIRED)

CRITERIA
MEETS SPECIFICATIONS
The submission must compile and run.

The project code must compile and run without errors.

We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform.

Loops, Functions, I/O

CRITERIA
MEETS SPECIFICATIONS
The project demonstrates an understanding of C++ functions and control structures.

A variety of control structures are used in the project.

The project code is clearly organized into functions.

The project reads data from a file and process the data, or the program writes data to a file.

The project reads data from an external file or writes data to a file as part of the necessary operation of the program.

The project accepts user input and processes the input.

The project accepts input from a user as part of the necessary operation of the program.

Object Oriented Programming

CRITERIA
MEETS SPECIFICATIONS
The project uses Object Oriented Programming techniques.

The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.

Classes use appropriate access specifiers for class members.

All class data members are explicitly specified as public, protected, or private.

Class constructors utilize member initialization lists.

All class members that are set to argument values are initialized through member initialization lists.

Classes abstract implementation details from their interfaces.

All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.

Classes encapsulate behavior.

Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.

Classes follow an appropriate inheritance hierarchy.

Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.

Overloaded functions allow the same function to operate on different parameters.

One function is overloaded with different signatures for the same function name.

Derived class functions override virtual base class functions.

One member function in an inherited class overrides a virtual base class member function.

Templates generalize functions in the project.

One function is declared with a template that allows it to accept a generic parameter.

Memory Management

CRITERIA
MEETS SPECIFICATIONS
The project makes use of references in function declarations.

At least two variables are defined as references, or two functions use pass-by-reference in the project code.

The project uses destructors appropriately.

At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.

The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.

The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.

The project follows the Rule of 5.

For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.

The project uses move semantics to move data, instead of copying it, where possible.

For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.

The project uses smart pointers instead of raw pointers.

The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.

Concurrency

CRITERIA
MEETS SPECIFICATIONS
The project uses multithreading.

The project uses multiple threads in the execution.

A promise and future is used in the project.

A promise and future is used to pass data from a worker thread to a parent thread in the project code.

A mutex or lock is used in the project.

A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.

A condition variable is used in the project.

A std::condition_variable is used in the project code to synchronize thread execution.
