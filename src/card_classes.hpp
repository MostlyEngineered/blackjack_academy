#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::weak_ptr;
using std::unique_ptr;

//Rule of 3
// destructor
// copy constructor
// copy assignment operator

//Rule of 5
// move constructor
// move assignment operator

class Card {
    public:

        Card(char suit, char cRank, double cardID){
            // cout << "card created" << endl;
            _cardID = cardID;
            _suit = suit;
            _cRank = cRank;
            calculateHardValue();
            calculateRunningCountValue();
        };

        ~Card(){
            // cout << "card destroyed" << endl;
            // delete this;
        };
        
        void calculateHardValue();
        void calculateRunningCountValue();
        void printCard(){cout << _cardID << ": " << _cRank << _suit << endl;};

        long _cardID;
        char _cRank;
        char _suit;
        bool _faceUp = false;
        bool _discarded = false;
        bool _isAce = false;
        int _hardValue;
        int _runningCountValue;
    private:


};

class Hand{
    private:

    public:

    Hand(){
        // cout << "Hand created" << endl;
        };

    ~Hand(){
        // cout << "Hand destroyed" << endl;
        };

    void printHand();
    void calculateHandValue();
    void updateHandSize(){
        _handSize = _handCards.size();
    };
    void moveCardToHand(unique_ptr<Card> card);

    //member values
    int _handValue; //total value of one deck is 380
    bool _isBust;
    vector<unique_ptr<Card>> _handCards;
    int _handSize;

};

class  AllCards {
    private:

    public:
        AllCards(int nDecks){
            for (int n=0;n < nDecks;++n){ 
                for (auto const& s : suits){
                    for (auto const& r : ranks){                 
                        unique_ptr<Card> card = std::make_unique< Card>(s, r, _curID);                 
                        card->printCard();
                        dealCardToShoe(std::move(card));
                        _curID += 1;

                    }
                }
            }
            _shoe.updateHandSize();        
        };

        void discardCard(unique_ptr<Card> card){
            _discardPile.moveCardToHand(std::move(card));
        };

        void dealCardToShoe(unique_ptr<Card> card){
            _shoe.moveCardToHand(std::move(card));
        };

        void dealIndexCardFromShoeToHand(int i, Hand &hand){
            vector<unique_ptr<Card>>::iterator it;

            hand.moveCardToHand(std::move(_shoe._handCards[i]));
            it = _shoe._handCards.begin() + i;
            _shoe._handCards.erase(it);
        };

        void dealRandomCardFromShoeToHand(Hand &hand){
            // _shoe.updateHandSize(); // this is done after each modifying action
            int RandIndex = rand() % _shoe._handSize;
            
            dealIndexCardFromShoeToHand(RandIndex, hand);
            _shoe.updateHandSize();
            hand.updateHandSize();
            cout << "print hand" << endl;
            hand.printHand();
            // cout << "shoe size is " << _shoe._handSize << " after deal" << endl;
            // cout << "hand size is " << hand._handSize << " after deal" << endl;
            // cout << "rand index is " << RandIndex << " out of " << _shoe._handSize << " cards" << endl;

        };

        vector<char> suits{ 'C', 'D', 'H', 'S'};
        vector<char> ranks{ '2', '3', '4', '5', '6', 
            '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
        long _curID=0;
        Hand _shoe;
        Hand _discardPile;

};

class Player {
    private:

    public:
        Player(){};
        ~Player(){};

        Hand* makePlayerNewHand(){
            Hand* hand = new Hand ;
            _playerHands.emplace_back(hand);
            return hand;
        };

        void dealCardToPlayerNewHand(AllCards &houseCards){  
            //append new hand to _playerHands and deal a random card from the shoe to it
            Hand *hand;
            hand = makePlayerNewHand();
            houseCards.dealRandomCardFromShoeToHand(*hand);
            

        };

        vector<Hand*> _playerHands; //splits can make a player have multiple hands
        long long int _playerMoney; //how much money the player has
        int playerNumber; //player number (this keeps track of player round resolution order)

};
