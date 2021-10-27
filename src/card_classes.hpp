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
        void printCard(){cout << _cardID << ": " << _cRank << _suit << ", HV: " << _hardValue << ", RC: " << _runningCountValue << endl;};

        long _cardID;
        char _cRank;
        char _suit;
        bool _isFaceUp = false;
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
        updateHandSplittable();
        updatePossibleActions();
    };
    void moveCardToHand(unique_ptr<Card> card);
    void updateHandSplittable();
    
    void updatePossibleActions(){
        
        if ((_isBust) || (_isFinished)){
            possibleActions = {};
        } else{ //if hand not Bust
            possibleActions = {'H', 'S'};

            if (_isSplittable){
                possibleActions.emplace_back('P');
            }
            if (_isDoubleDownable){
                possibleActions.emplace_back('D');
            }
            if (_isSurrenderable){
                possibleActions.emplace_back('R');
            }        
        }


    }

    //member values
    // vector<char> actionsList = { 'H', 'S', 'P', 'D', 'R'}; //Possible actions are: Hit, Stay, Splittable, Doubledown, Surrender
    vector<char> possibleActions;
    vector<unique_ptr<Card>> _handCards;
    int _handValue; //total value of one deck is 380
    int _handSize;
    bool _isBust = false; //initialize to false as blank hands are not bust
    bool _isSplittable = false; //initialize to false as blank hands are not splittable
    bool _isDoubleDownable = false; //initialize to false as blank hands are not able to double down
    bool _handDoubledDown = false; //only changes to true if player doubles down
    bool _isBlackjack = false;
    bool _isSurrenderable = false;
    bool _isFinished = false; // only changes to true when a stop condition is reached (Stay, Doubledown, Bust, Surrender)
    

};

class  HouseCards {
    private:

    public:
        // HouseCards(){cout << "House Cards constructed" << endl;};
        // ~HouseCards(){cout << "House Cards destructed" << endl;};
        HouseCards(int nDecks){
            for (int n=0;n < nDecks;++n){ 
                for (auto const& s : suits){
                    for (auto const& r : ranks){                 
                        unique_ptr<Card> card = std::make_unique<Card>(s, r, _curID);                 
                        // card->printCard();
                        dealCardToShoe(std::move(card));
                        _curID += 1;

                    }
                }
            }
            _shoe.updateHandSize();     
            // cout << "House Cards constructed" << endl;   
        };

        void discardCard(unique_ptr<Card> card){
            _discardPile.moveCardToHand(std::move(card));
        };

        void dealCardToShoe(unique_ptr<Card> card){
            _shoe.moveCardToHand(std::move(card));
        };

        void dealIndexCardFromShoeToHand(int i, Hand &hand){
            dealIndexCardFromShoeToHand(i, hand, true);
        };

        void dealIndexCardFromShoeToHand(int i, Hand &hand, bool isFaceUp){
            vector<unique_ptr<Card>>::iterator it;
            _runningCount += _shoe._handCards[i]->_runningCountValue;
            _shoe._handCards[i]->_isFaceUp = isFaceUp;
            hand.moveCardToHand(std::move(_shoe._handCards[i]));
            it = _shoe._handCards.begin() + i;
            _shoe._handCards.erase(it);
            _shoe.updateHandSize();
            _trueCountValue = ((float)_runningCount * 52.) / (float)_shoe._handSize;
        };


        void dealRandomCardFromShoeToHand(Hand &hand, bool isFaceUp){

            int RandIndex = rand() % _shoe._handCards.size(); //_shoe._handSize is bad value
            dealIndexCardFromShoeToHand(RandIndex, hand);
            _shoe.updateHandSize();
            hand.updateHandSize();

        };

        void dealRandomCardFromShoeToHand(Hand &hand){
            dealRandomCardFromShoeToHand(hand, true);

        };

        void printRunningCount(){cout << "running_count: " << _runningCount << endl;};

        vector<char> suits{ 'C', 'D', 'H', 'S'};
        vector<char> ranks{ '2', '3', '4', '5', '6', 
            '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
        long _curID=0;
        Hand _shoe;
        Hand _discardPile;
        int _runningCount = 0; //Running count starts at 0
        float _trueCountValue = 0.0; //True count is running count divided by decks left

};

