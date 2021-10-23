# blackjack_academy

# Basic rules of (casino) blackjack

## Basic setup
All players compete against the dealer, trying to get their card total closer to 21 without going over.  All cards are their face value (2-10 on the number cards), JQK are 10, Ace can be 1 or 11 (whichever value is better for the hand).

If the player is dealt a "blackjack" (getting 21 on first two cards), the player gets a bonus (common bonuses are 3:2, 2:1, 6:5, 7:5).  The "shoe" is the "deck" of cards that is played with, but consists of one to as many as eight decks of cards.  If the player wins without getting a blackjack they win the amount that they bet.  If the dealer's hand (last to be resolved) is higher than the player or the player busts (goes over 21), the house wins and the player loses their bet.

## Game flow
Bets are placed before any cards are dealt.  There is a minimum and a maximum bet size usually that depends on the table.

All players are initially dealt one card (player cards are always face up) from (dealer's) left to right face-up.  Then a card is dealt to the dealer face-down.  The dealer then deals the second card to each player. Then a card is dealt to the dealer face-up.

(Insurance rule) if the dealer's face-up card has value 10 or 11, the players can bet that the dealer has blackjack.  They can bet up to half their original bet.  If the dealer has blackjack they win 2 to 1.

When it is the player's turn there are 2 main options and 2 options that require preconditions:

Hit - dealer deals them another face up card adding to their total
Stay - the player ends their turn
Split (preconditions)- If the player is dealt two identical value cards (10, J, Q, K are all same), they may split and play both cards as new hands.  This can be done to start 3 hands, but no more.
Double down (preconditions)- This action is only allowed if the player's hand consists of two cards (splits can be doubled down on).  The player can bet more (up to their original amount) and recieves only one card (ie this action amounts to Bet, Hit, Stay)

## Dealer play
The dealer has a set algorithm they must use to play.  The dealer can only hit or stay.  The dealer must hit until they reach 17 or greater (ie if they have 16 or less).


## Shoe management
Start of a shoe, the dealer deals a card direct to discard (no one sees the value of this card)
