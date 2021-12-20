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
            // cout << "card destroyed" << endl;
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

    vector<char> suits{ 'C', 'D', 'H', 'S'};
    vector<char> ranks{ '2', '3', '4', '5', '6', 
        '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

    vector<char> possibleActions;
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


class Player {
    private:

    public:
        Player(char playerType, int playerNumber, long long int playerMoney) {
            _playerType = playerType;
            _playerNumber = playerNumber;

            if (playerType == 'D'){
                _isDealer = true;
                _isHuman = false;
                _playerMoney = 50000000;
                cout << "initiate dealer money (" << _playerNumber << "), " << _playerMoney << "\n";
            } else if (playerType == 'C'){
                _isDealer = false;
                _isHuman = false;
                _playerMoney = playerMoney;
                cout << "initiate computer money (" << _playerNumber << "), " << _playerMoney << "\n";
            } else if (playerType == 'H'){
                _isDealer = false;
                _isHuman = true;
                _playerMoney = playerMoney;
                cout << "initiate player money (" << _playerNumber << "), " << _playerMoney << "\n";
            } else {
                cout << "Invalid Player type" << endl;
            }
            
        };

        Player(char playerType, int playerNumber){
            Player(playerType, playerNumber, 50000);
        };

        ~Player(){};

        Player(Player&& other) :
            _playerHands(std::move(other._playerHands)),
            _playerMoney(other._playerMoney),
            _playerNumber(other._playerNumber),
            _isDealer(other._isDealer),
            _isHuman(other._isHuman),
            _isFinished(other._isFinished)

            {};

        Player( const Player& ) = delete; // copy constructor 
        // Player& Player::operator=( const Player& obj ) {};// copy assignment operator   
        // Player& operator=(Player&& obj) {}; // move assignment operator 


        void makePlayerNewHand(){ 
            Hand hand;
            _playerHands.emplace_back(std::move(hand));
        };

        void dealCardToPlayerNewHand(HouseCards &houseCards, bool isFaceUp){  
            makePlayerNewHand();
            // houseCards.dealRandomCardFromShoeToHand(_playerHands.back(), isFaceUp);
               houseCards._shoe.dealRandomCardFromHandToHand(_playerHands.back(), isFaceUp);
        };

        void printPlayerData(){
            string playerTag;
            if (_isDealer){
                playerTag = " (D)";
            } else if (_isHuman) {
                playerTag = " (H)";
            } else if (_playerType == 'C') {
                playerTag = "";
            } else {
                playerTag = "";
            }

            cout << "Player " << _playerNumber << ":" << playerTag << endl;
            cout << "Money: " << _playerMoney << endl;
            // for (auto hand : _playerHands){
            for (int h=0;h<_playerHands.size();h++ ){
                cout << "Hand: " << (h+1) << " of " << _playerHands.size() << endl;    
                _playerHands[h].printHand();
                cout << endl;
            }
        }

        // vector<unique_ptr< Hand >> _playerHands; 
        // vector<unique_ptr< int >> _playerHands; //nope
        // unique_ptr< int > _playerHands; 
        vector<Hand> _playerHands; //splits can make a player have multiple hands
        // PlayerHands _playerHands;
        long long int _playerMoney; //how much money the player has
        int _playerNumber; //player number (this keeps track of player round resolution order)
        char _playerType; // 'H' Human, 'C' Computer, 'D' Dealer (no human dealers)
        bool _isDealer;
        bool _isHuman;
        bool _isFinished = false; //player is finished when all his current round hands are finished, when hands are cleaned up this should be reset back to false

};


class Game{
    // Dealer is last player, but is the dealer and not considered a "player".
    private:

    public:
        Game(int numPlayers, long long int initialPlayerMoney, int numDecks) :
            _houseCards(HouseCards(numDecks))
        
        {
            // Start with numHumanPlayers always 1
            _numPlayers = numPlayers;
            _initialPlayerMoney = initialPlayerMoney;
            _numDecks=numDecks;
            _numHumanPlayers = 1; //this is at least 1
            _numComputerPlayers = _numPlayers - 1; //this is 0 or more
            _numGamblers = _numHumanPlayers + _numComputerPlayers; //human players + computer players (is _numPlayers - 1)
             seatPlayers();
            
        };

        // void seatPlayers(){
        //     for (int p=0;p<_numPlayers+1;p++){
        //         // cout << "loop number: " << p << " of players: " << _numPlayers << "\n";
        //         if (p < _numPlayers){
        //             cout << "add H Player" << endl;
        //             _players.emplace_back(std::move(Player('H', p, _initialPlayerMoney)));
        //             _players[p]._playerNumber = p;  // save player number for convenience
        //             cout << "player num: " << p << "\n";
        //             cout << "player num: " << _players[p]._playerNumber << "\n";
        //         } else {
        //             //can shuffle players here prior to adding dealer
        //             cout << "add D Player" << endl;
        //             _players.emplace_back(std::move(Player('D', p, _initialCasinoInitialMoney)));
        //             _players[p]._playerNumber = p;  // save player number for convenience
        //             cout << "player num: " << p << "\n";
        //             cout << "player num: " << _players[p]._playerNumber << "\n";

        //         }
        //     }
        // };

        void seatPlayers(){
            int ii = 5;
            for (int p=0;p<_numHumanPlayers;p++){
                cout << "add H Player" << endl;
                _players.emplace_back(std::move(Player('H', ii, _initialPlayerMoney)));
                // _players[ii]._playerNumber = ii;  // save player number for convenience
                cout << "player num: " << ii << "\n";
                cout << "player num: " << _players[ii]._playerNumber << "\n";
                ii++;
                }
            
            for (int p=0;p<_numComputerPlayers;p++){
                cout << "add C Player" << endl;
                _players.emplace_back(std::move(Player('C', ii, _initialPlayerMoney)));
                // _players[ii]._playerNumber = ii;  // save player number for convenience
                cout << "player num: " << ii << "\n";
                cout << "player num: " << _players[ii]._playerNumber << "\n";
                ii++;
                }

            // Add dealer player
            
            cout << "add D Player" << endl;
            _players.emplace_back(std::move(Player('D', ii, _initialCasinoInitialMoney)));
            // _players[ii]._playerNumber = ii;  // save player number for convenience
            cout << "player num: " << ii << "\n";
            cout << "player num: " << _players[ii]._playerNumber << "\n";
        
        };

        // One constructor should be numHumanPlayers, numComputerPlayers

        // Game();

        // ~Game();

        void playRound(){

            dealInitialCards();

            printRoundStatus();


        };

        void dealInitialCards()
        {
            for (int p=0;p<_numPlayers+1;p++){
                // First card
                if (p < _numPlayers){
                    //Player card, player cards are always face up
                    // _houseCards._shoe.dealRandomCardFromHandToHand(_players[p]._playerHands[0], true);
                    _players[p].dealCardToPlayerNewHand(_houseCards, true);
                    cout << "dealing card to " << p << "\n";
                    cout << "dealing card to " << _players[p]._playerNumber << "\n";
                } else {
                    //Dealer card, first is face down
                    // _houseCards._shoe.dealRandomCardFromHandToHand(_players[p]._playerHands[0], false);
                    _players[p].dealCardToPlayerNewHand(_houseCards, false);
                    cout << "dealing card to " << p << "\n";
                    cout << "dealing card to " << _players[p]._playerNumber << "\n";

                }
            }

            for (int p=0;p<_numPlayers+1;p++){
                // Second card is always face up
                    _houseCards._shoe.dealRandomCardFromHandToHand(_players[p]._playerHands[0], true);
                }
            

        };


        void printRoundStatus(){
            //print all information relevant to round

            cout << "Round number: " << _roundNum << endl;
            // for (auto player : _players){
            //     player.printPlayerData();
            //     player
            // }

            for (int p=0;p<_numPlayers+1;p++){
                // Second card is always face up
                    cout << "Player " << p << endl;
                    _players[p].printPlayerData();
                }

        };



        // void addPlayer(char playerType, int playerNumber, long long int playerMoney){
        //     // Player addPlayer = Player(playerType, playerNumber, playerMoney);
        //     // _players.emplace_back(std::move(addPlayer));
        // }

        int _numHumanPlayers; //this is at least 1
        int _numComputerPlayers; //this is 0 or more
        int _numPlayers; //human players + computer players + dealer
        int _numGamblers; //human players + computer players (is _numPlayers - 1)
        
        int _roundNum = 1;

        long long int _initialPlayerMoney;
        long long int _initialCasinoInitialMoney;

        // GameRound _curRound;
        vector<Player> _players;
        int _numDecks;

        HouseCards _houseCards;

};



