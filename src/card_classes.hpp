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


vector<char> suits{ 'C', 'D', 'H', 'S'};
vector<char> ranks{ '2', '3', '4', '5', '6', 
        '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};



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
            cout << "card created" << endl;
            _cardID = cardID;
            _suit = suit;
            _cRank = cRank;
            calculateHardValue();
        };

        ~Card(){
            cout << "card destroyed" << endl;
            // delete this;
        };

        void calculateHardValue(){
            _hardValue  = ((int)(_cRank)) - 48;  // All numbers (besides 'T') will be 2-9
        
            if ((_hardValue==36) || (_hardValue==26) || (_hardValue==33) || (_hardValue==27)){
                _hardValue = (int)10;
            } else if (_hardValue==17){
                _hardValue = (int)11;  // Each ace will be recalculated if there is a bust on hand calculation
            }

            if (_cRank == 'A'){
                _isAce = true;
            }


        };

        void printCard(){
            cout << _cardID << ": " << _cRank << _suit << endl;
        };

        long _cardID;
        char _cRank;
        char _suit;
        bool _faceUp = false;
        bool _discarded = false;
        bool _isAce = false;
        int _hardValue;
    private:


};

class Hand{
    private:

    public:

    Hand(){cout << "Hand created" << endl;};

    ~Hand(    ){
        cout << "Hand destroyed" << endl;
    };

    void printHand(){
        for (auto &c : _handCards){
            c->printCard();
        }
    };

    void calculateHandValue(){
        int aceCount = 0;
        _handValue = 0;

        for (int c=0; c<_handCards.size(); c++){
            _handValue += _handCards[c]->_hardValue;
            if (_handCards[c]->_isAce){
                aceCount += 1;
            }
        }
            
        if (_handValue > 21){            
            for (int a=aceCount; a>0 ; a-- ){
                _handValue -= 10;  //decrement for each ace in the hand
                if (_handValue <= 21){ //check if decrement makes it below 21
                    break;
                }
            }
        }

        if (_handValue > 21){            
            _handValue = 22; // 22 will be standard bust value
        }
    };

    void moveCardToHand(unique_ptr<Card> card){
        _handCards.emplace_back(std::move(card));
        calculateHandValue();
    };


    int _handValue; //total value of one deck is 380
    bool _isBust;
    vector<unique_ptr<Card>> _handCards;

};

class  AllCards : public Hand {
    private:

    public:

        AllCards(int nDecks){
            for (int n=0;n < nDecks;++n){ 
                for (auto const& s : suits){
                    for (auto const& r : ranks){ 
                        // unique_ptr<Card> card(new Card(s, r, _curID));                 
                        unique_ptr<Card> card = std::make_unique< Card>(s, r, _curID);                 
                        card->printCard();
                        dealCardToShoe(std::move(card));
                        // card.get()->printCard();
                        // cout << card->_suit;
                        // cout << (card->_suit);
                        _curID += 1;

                    }
                }
            }        
        };

        void discardCard(unique_ptr<Card> card){
            _discardPile.moveCardToHand(std::move(card));
        };

        void dealCardToShoe(unique_ptr<Card> card){
            _shoe.moveCardToHand(std::move(card));
        };

        // void dealCardFromShoeToHand(unique_ptr<Card> card, Hand hand){
        //     hand.moveCardToHand(std::move(card));
        // };

        void dealIndexCardFromShoeToHand(int i, Hand hand){
            // hand.moveCardToHand(std::move(_shoe._handCards[i]));
            hand.moveCardToHand(std::move(_shoe._handCards[i]));
            // _shoe._handCards.erase(i);

            // std::move(_shoe._handCards).erase(i);  //need to resize so there are no holes
            // (_shoe._handCards).erase(i);  //need to resize so there are no holes


        };

        long _curID=0;
        Hand _shoe;
        Hand _discardPile;

};

    
