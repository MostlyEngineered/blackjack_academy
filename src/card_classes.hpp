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
            _cardID = cardID;
            _suit = suit;
            _cRank = cRank;
        };

        ~Card(){

        };

        void printCard(){
            cout << _cardID << ": " << _cRank << _suit << endl;
        };

        long _cardID;
        char _cRank;
        char _suit;
        bool _faceUp = false;
        bool _discarded = false;

    private:


};

class Hand{
    private:

    public:

    Hand(){};

    ~Hand(){};

    void printHand(){
        for (auto &c : _handCards){
            c->printCard();
        }
    };

    void calculateHandValue(){};

    void moveCardToHand(unique_ptr<Card> card){
        _handCards.emplace_back(std::move(card));
        
    };


    vector<unique_ptr<Card>> _handCards;
};

class  AllCards : public Hand {
private:

public:

    AllCards(int nDecks){
        for (int n=0;n < nDecks;++n){ 
            for (auto const& s : suits){
                for (auto const& r : ranks){ 
                    unique_ptr<Card> card(new Card(s, r, _curID));                 
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
        hand.moveCardToHand(std::move(_shoe._handCards[i]));
        // _shoe._handCards.erase(i);  //need to resize so there are no holes
    };

    long _curID=0;
    Hand _shoe;
    Hand _discardPile;

};

    
