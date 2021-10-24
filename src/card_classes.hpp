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

        // unique_ptr<Card> card_ptr(new Card(s, r, _curID));
        // _cards.emplace_back(card_ptr);


        long _cardID;
        char _cRank;
        char _suit;
        bool _faceUp = false;
        bool _discarded = false;


    private:


};

// void UniquePointer()
// {
//     std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
//     *unique = 2; // assign a value
//     // delete is not neccessary
// }

class  AllCards{
private:

public:

    AllCards(int nDecks){
        // make shoe
        // cout << "making " << nDecks << " decks" << endl;
        for (int n=0;n < nDecks;++n){ 
            cout << n << endl;
            for (auto const& s : suits){
                for (auto const& r : ranks){ 
                    unique_ptr<Card> card(new Card(s, r, _curID));
                    _cards.emplace_back(std::move(card));
                    // _cards.emplace_back(Card(s, r, _curID));                    
                    _curID += 1;

                }
            }
    
        }        

    };

    void printAllCards(){
        for (auto & c : _cards){
            // *c.printCard();
        }
    };



    long _curID=0;
    std::vector<unique_ptr<Card>> _cards;
    // Hand _shoe;

};

    
class Hand{
    private:

    public:

    Hand(){};

    ~Hand(){};

    void printHand(){};

    void calculateHandValue(){};

    void dealCardToHand(Card c){
        unique_ptr<Card> c_ptr;
        _handCards.emplace_back();
    };

    vector<unique_ptr<Card>> _handCards;


};