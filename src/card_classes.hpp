#define DEALER_HIT_LIMIT 16
#define DEALER_PUSH_RESULT "tie"  // player win, loss, or tie
#define DEALER_HIT_SOFT_17 
#define BLACKJACK_MULTIPLE 2.0

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <algorithm>
#include <limits>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::weak_ptr;
using std::unique_ptr;


//Rule of 3
// destructor ~ClassName()
// copy constructor ClassName( const ClassName& )
// copy assignment operator   MyClass& MyClass::operator=( const MyClass& obj )

//Rule of 5
// move constructor ClassName( ClassName&& obj ) 
// move assignment operator ClassName& operator=(ClassName&& obj)

// Reference Code
// forward_list(forward_list&& other) :
//     root_(std::move(other.root_)),
//     leaf_(std::move(other.leaf_)),
//     count_(other.count_),
//     heap_(other.heap_)
//     {
//         // Do Nothing
//     }
    


class Card {
    public:

        // Card(const Card&) = delete;
        // Card(Card&&) = default;

        Card(char suit, char cRank, double cardID){
            // cout << "card created" << endl;
            _cardID = cardID;
            _suit = suit;
            _cRank = cRank;
            calculateHardValue();
            calculateRunningCountValue();
        };

        ~Card(){
            cout << "card destroyed, this shouldn't happen..." << endl;
            this->printCard();
            // delete this;
        };
        

        Card( const Card& ) ; // copy constructor 
        // Card& Card::operator=( const Card& obj ) ;// copy assignment operator   
        Card( Card&& obj ) ; // move constructor 
        // Card& operator=(Card&& obj) ; // move assignment operator 


        void calculateHardValue();
        void calculateRunningCountValue();
        void printCard()
            {
                cout << _cardID << ": " << _cRank << _suit << ", HV: " 
                    << _hardValue << ", RC: " << _runningCountValue 
                    << ", faceup: " << _isFaceUp << endl;
            };

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
    Hand(){};
    // Hand(const Hand&) = delete; 
    // Hand(const Hand&) = default; 
    // Hand(Hand&&) = default;

    // Hand(){
    //     cout << "Hand created" << endl;
    //     };

    //Destructor
    ~Hand(){
        cout << "Hand destroyed" << endl;
        };

    // move constructor 
    Hand(Hand&& other) :
        _handCards(std::move(other._handCards))
        {};

    // Hand( const Hand& ) {}; // copy constructor 
    // Hand& Hand::operator=( const Hand& obj ) {};// copy assignment operator   
    // Hand& operator=(Hand&& obj) {}; // move assignment operator 


    void printHand();
    void calculateHandValue();
    void updateHandSize(){
        _handSize = _handCards.size();
        updateHandSplittable();
        updatePossibleActions();
    };
    // void moveCardToHand(unique_ptr<Card> card);
    void moveCardToHand(unique_ptr<Card> card){
        // _handCards.emplace_back(std::move(card));
        _handCards.push_back(std::move(card));
        calculateHandValue();
        updateHandSize();
    };

    void dealIndexCardFromHandToHand(int i, Hand &toHand, bool isFaceUp){
        vector<unique_ptr<Card>>::iterator it;
        // _runningCount += _shoe._handCards[i]->_runningCountValue;
        this->_handCards[i]->_isFaceUp = isFaceUp;
        toHand.moveCardToHand(std::move(this->_handCards[i]));
        it = this->_handCards.begin() + i;
        this->_handCards.erase(it);
        this->updateHandSize();
        // _trueCountValue = ((float)_runningCount * 52.) / (float)_shoe._handSize;
    };

    void dealRandomCardFromHandToHand(Hand &toHand, bool isFaceUp){
        srand (time(NULL)); //randomize seed number
        int RandIndex = rand() % this->_handCards.size();
        dealIndexCardFromHandToHand(RandIndex, toHand, isFaceUp);
    };


    //member values
    // vector<char> actionsList = { 'H', 'S', 'P', 'D', 'R'}; //Possible actions are: Hit, Stay, Splittable, Doubledown, Surrender
    void updateHandSplittable();
    
    void updatePossibleActions(){
        
        if ((_isBust) || (_isFinished)){
            _possibleActions = {};
        } else{ //if hand not Bust
            _possibleActions = {'H', 'S'};

            if (_isSplittable){
                _possibleActions.emplace_back('P');
            }
            if (_isDoubleDownable){
                _possibleActions.emplace_back('D');
            }
            if (_isSurrenderable){
                _possibleActions.emplace_back('R');
            }        
        }
    }

    vector<char> suits{ 'C', 'D', 'H', 'S'};
    vector<char> ranks{ '2', '3', '4', '5', '6', 
        '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

    vector<char> _possibleActions;
    vector<unique_ptr<Card>> _handCards = {};
    int _handValue; //total value of one deck is 380
    int _handSize;
    int _curID = 0;
    bool _isBust = false; //initialize to false as blank hands are not bust
    bool _isSplittable = false; //initialize to false as blank hands are not splittable
    bool _isDoubleDownable = false; //initialize to false as blank hands are not able to double down
    bool _handDoubledDown = false; //only changes to true if player doubles down
    bool _isBlackjack = false;
    bool _isSurrenderable = false;
    bool _isFinished = false; // only changes to true when a stop condition is reached (Stay, Doubledown, Bust, Surrender)
    bool _isSurrendered = false;
    

};


class Shoe : public Hand {
    private:

    public:

    Shoe(int nDecks){
        
        
        for (int n=0;n < nDecks;++n){ 
            for (auto const& s : suits){
                for (auto const& r : ranks){                 
                    _handCards.emplace_back(std::make_unique<Card>(s, r, _curID));             
                    _curID += 1;
                }
            }
        }
        updateHandSize();
        cout << "Shoe created" << endl;        
    };
    ~Shoe(){cout << "Shoe destroyed" << endl;};

};

class  HouseCards {
    private:

    public:

        HouseCards(int nDecks) : _shoe(Shoe(nDecks))
        {
            _shoeResetCardCount = (int)(nDecks * 52 * _resetPercentage);
        };


        void discardCard(unique_ptr<Card> card){
            _discardPile.moveCardToHand(std::move(card));

        };

        void dealCardToShoe(unique_ptr<Card> card){
            _shoe.moveCardToHand(std::move(card));
        };

        void reshuffleCards()
        {
            // take take all discard cards and put back into shoe
            int discardSize = 0;
            
            discardSize = _discardPile._handCards.size();
            for (int c=0;c<discardSize;c++ )
            { 
                _discardPile.dealIndexCardFromHandToHand(0, _shoe, false);
                cout << "discarding card " << c << " of " << discardSize << "\n";
            }
            

        };


        void printRunningCount(){cout << "running_count: " << _runningCount << endl;};


        long _curID=0;
        Hand _shoe;
        Hand _discardPile;
        float _resetPercentage = 0.25; // how much of the shoe is left when reset triggers
        int _shoeResetCardCount;
        int _runningCount = 0; //Running count starts at 0
        float _trueCountValue = 0.0; //True count is running count divided by decks left

};

