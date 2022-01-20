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