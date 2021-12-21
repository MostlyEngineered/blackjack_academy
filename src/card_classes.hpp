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

        };


        void discardCard(unique_ptr<Card> card){
            _discardPile.moveCardToHand(std::move(card));
            // card = nullptr;
        };

        void dealCardToShoe(unique_ptr<Card> card){
            _shoe.moveCardToHand(std::move(card));
        };


        void printRunningCount(){cout << "running_count: " << _runningCount << endl;};


        long _curID=0;
        Hand _shoe;
        Hand _discardPile;
        int _runningCount = 0; //Running count starts at 0
        float _trueCountValue = 0.0; //True count is running count divided by decks left

};


// class Player {
//     private:

//     public:
//         Player(char playerType, int playerNumber, long long int playerMoney) {
//             _playerType = playerType;
//             _playerNumber = playerNumber;

//             if (playerType == 'D'){
//                 _isDealer = true;
//                 _isHuman = false;
//                 _isBot = false;
//                 _playerMoney = 50000000;
//                 cout << "initiate dealer money (" << _playerNumber << "), " << _playerMoney << "\n";
//             } else if (playerType == 'C'){
//                 _isDealer = false;
//                 _isHuman = false;
//                 _isBot = true;
//                 _playerMoney = playerMoney;
//                 cout << "initiate computer money (" << _playerNumber << "), " << _playerMoney << "\n";
//             } else if (playerType == 'H'){
//                 _isDealer = false;
//                 _isHuman = true;
//                 _isBot = false;
//                 _playerMoney = playerMoney;
//                 cout << "initiate player money (" << _playerNumber << "), " << _playerMoney << "\n";
//             } else {
//                 cout << "Invalid Player type" << endl;
//             }
            
//         };

//         Player(char playerType, int playerNumber){
//             Player(playerType, playerNumber, 50000);
//         };

//         ~Player(){};

//         Player(Player&& other) :
//             _playerHands(std::move(other._playerHands)),
//             _playerType(other._playerType),
//             _playerMoney(other._playerMoney),
//             _playerNumber(other._playerNumber),
//             _isDealer(other._isDealer),
//             _isBot(other._isBot),
//             _isHuman(other._isHuman),
//             _isFinished(other._isFinished),
//             _playerCurBet(other._playerCurBet)

//             {};

//         Player( const Player& ) = delete; // copy constructor 
//         // Player& Player::operator=( const Player& obj ) {};// copy assignment operator   
//         // Player& operator=(Player&& obj) {}; // move assignment operator 


//         void makePlayerNewHand(){ 
//             Hand hand;
//             _playerHands.emplace_back(std::move(hand));
//         };

//         void dealCardToPlayerNewHand(HouseCards &houseCards, bool isFaceUp){  
//             makePlayerNewHand();
//             houseCards._shoe.dealRandomCardFromHandToHand(_playerHands.back(), isFaceUp);
//         };

//         void discardHands(HouseCards &houseCards){
//             for (int h=0;h<_playerHands.size();h++ )
//             { 
//                 for (int c=0;c<_playerHands[h]._handCards.size();c++ )
//                 { 
//                     _playerHands[h].dealIndexCardFromHandToHand(c, houseCards._discardPile, false);
               
//                 }
//             }
//             _playerHands.clear();
//             // _playerHands = {};
//         };

//         void printPlayerData(){
//             string playerTag;
//             if (_isDealer){
//                 playerTag = " (D)";
//             } else if (_isHuman) {
//                 playerTag = " (H)";
//             } else if (_playerType == 'C') {
//                 playerTag = " (C)";
//             } else {
//                 playerTag = "(invalid player tag)";
//             }

//             cout << "Player " << _playerNumber << ":" << playerTag << endl;
//             cout << "Money: " << _playerMoney << endl;

//             for (int h=0;h<_playerHands.size();h++ ){
//                 cout << "Hand: " << (h+1) << " of " << _playerHands.size() << endl;    
//                 _playerHands[h].printHand();
//                 cout << endl;
//             }
//         }

//         void updateIsFinished()
//         {
//             bool isFinished = true;
//             for (int h=0;h<_playerHands.size();h++ )
//             {
//                 if (_playerHands[h]._isFinished == false) 
//                 {
//                     isFinished = false;
//                 }
//             }
//             _isFinished = isFinished;
//         }

//         void playerLoses(int curBet)
//         {
//             _playerMoney -= curBet;
//         };

//         void playerLosesMultiple(int curBet, float multiplier)
//         {
//             _playerMoney -= ((float)curBet * multiplier);
//         };

//         void playerWins(int curBet)
//         {
//             _playerMoney += curBet;
//         };

//         void playerWinsMultiple(int curBet, float multiplier)
//         {
//             _playerMoney += ((float)curBet * multiplier);
//         };

//         vector<Hand> _playerHands; //splits can make a player have multiple hands
//         long long int _playerMoney; //how much money the player has
//         int _playerNumber; //player number (this keeps track of player round resolution order)
//         char _playerType; // 'H' Human, 'C' Computer, 'D' Dealer (no human dealers)
//         bool _isDealer;
//         bool _isHuman;
//         bool _isBot;
//         bool _isFinished = false; //player is finished when all his current round hands are finished, when hands are cleaned up this should be reset back to false
//         int _playerCurBet;

// };
