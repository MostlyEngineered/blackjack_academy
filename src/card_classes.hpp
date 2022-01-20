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
#include <boost/log/trivial.hpp>

#include <boost/log/core.hpp> 
#include <boost/log/expressions.hpp> 
#include <boost/log/utility/setup/file.hpp>

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
        BOOST_LOG_TRIVIAL(debug) << "Hand destroyed";
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
            _possibleActions.emplace_back('Q');
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
        BOOST_LOG_TRIVIAL(debug) << "Shoe created";        
    };

    ~Shoe(){
        BOOST_LOG_TRIVIAL(debug) << "Shoe destroyed";
    };

};

class  HouseCards {
    private:

    public:

        HouseCards(int nDecks) : _shoe(Shoe(nDecks))
        {
            BOOST_LOG_TRIVIAL(debug) << "Multideck Shoe created";
        };


        void discardCard(unique_ptr<Card> card){
            _discardPile.moveCardToHand(std::move(card));
            card = nullptr;
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
                _isBot = false;
                _playerMoney = 50000000;
                BOOST_LOG_TRIVIAL(debug) << "initiate dealer money (" << _playerNumber << "), " << _playerMoney;

            } else if (playerType == 'C'){
                _isDealer = false;
                _isHuman = false;
                _isBot = true;
                _playerMoney = playerMoney;
                BOOST_LOG_TRIVIAL(debug) << "initiate computer money (" << _playerNumber << "), " << _playerMoney;                

            } else if (playerType == 'H'){
                _isDealer = false;
                _isHuman = true;
                _isBot = false;
                _playerMoney = playerMoney;
                BOOST_LOG_TRIVIAL(debug) << "initiate player money (" << _playerNumber << "), " << _playerMoney;

            } else {
                BOOST_LOG_TRIVIAL(debug) << "Invalid Player type";

            }
            
        };

        Player(char playerType, int playerNumber){
            Player(playerType, playerNumber, 50000);
        };

        ~Player(){};

        Player(Player&& other) :
            _playerHands(std::move(other._playerHands)),
            _playerType(other._playerType),
            _playerMoney(other._playerMoney),
            _playerNumber(other._playerNumber),
            _isDealer(other._isDealer),
            _isBot(other._isBot),
            _isHuman(other._isHuman),
            _isFinished(other._isFinished),
            _playerCurBet(other._playerCurBet)

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
            houseCards._shoe.dealRandomCardFromHandToHand(_playerHands.back(), isFaceUp);
        };

        void printPlayerData(){
            string playerTag;
            if (_isDealer){
                playerTag = " (D)";
            } else if (_isHuman) {
                playerTag = " (H)";
            } else if (_playerType == 'C') {
                playerTag = " (C)";
            } else {
                playerTag = "(invalid player tag)";
            }

            cout << "Player " << _playerNumber << ":" << playerTag << endl;
            cout << "Money: " << _playerMoney << endl;

            for (int h=0;h<_playerHands.size();h++ ){
                cout << "Hand: " << (h+1) << " of " << _playerHands.size() << endl;    
                _playerHands[h].printHand();
                cout << endl;
            }
        }

        void updateIsFinished()
        {
            bool isFinished = true;
            for (int h=0;h<_playerHands.size();h++ )
            {
                if (_playerHands[h]._isFinished == false) 
                {
                    isFinished = false;
                }
            }
            _isFinished = isFinished;
        }

        void playerLoses(int curBet)
        {
            BOOST_LOG_TRIVIAL(debug) <<"player loses " << curBet;
            _playerMoney -= curBet;
        };

        void playerLosesMultiple(int curBet, float multiplier)
        {
            BOOST_LOG_TRIVIAL(debug) << "player loses multiple " << curBet;
            _playerMoney -= ((float)curBet * multiplier);
        };

        void playerWins(int curBet)
        {
            BOOST_LOG_TRIVIAL(debug) << "player wins " << curBet;
            _playerMoney += curBet;
        };

        void playerWinsMultiple(int curBet, float multiplier)
        {
            BOOST_LOG_TRIVIAL(debug) << "player wins multiple " << curBet;
            _playerMoney += ((float)curBet * multiplier);
        };

        vector<Hand> _playerHands; //splits can make a player have multiple hands
        long long int _playerMoney; //how much money the player has
        int _playerNumber; //player number (this keeps track of player round resolution order)
        char _playerType; // 'H' Human, 'C' Computer, 'D' Dealer (no human dealers)
        bool _isDealer;
        bool _isHuman;
        bool _isBot;
        bool _isFinished = false; //player is finished when all his current round hands are finished, when hands are cleaned up this should be reset back to false
        int _playerCurBet;

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


        void seatPlayers(){
            int ii = 0;
            for (int p=0;p<_numHumanPlayers;p++){
                BOOST_LOG_TRIVIAL(debug) << "add H Player";
                _players.emplace_back(std::move(Player('H', ii, _initialPlayerMoney)));
                ii++;
                }
            
            for (int p=0;p<_numComputerPlayers;p++){
                BOOST_LOG_TRIVIAL(debug) << "add C Player";
                _players.emplace_back(std::move(Player('C', ii, _initialPlayerMoney)));
                ii++;
                }

            // Add dealer player
            BOOST_LOG_TRIVIAL(debug) << "add D Player";
            _players.emplace_back(std::move(Player('D', ii, _initialCasinoInitialMoney)));
        
        };


        void playRound(){

            BOOST_LOG_TRIVIAL(debug) << "play round";

            dealInitialCards();

            printRoundStatus();

            takeInitialBets();

            processPlayerTurns();

            if (_exit_flag)
            {
                return;
            }

            calculateTurnResults();

            discardCards();


        };

        void discardCards()
        {
        int i = 0;
        int handSize;
            for (int p=0;p<_numPlayers+1;p++)
            {
                for (int h=0;h<_players[p]._playerHands.size();h++ )
                { 
                    handSize = _players[p]._playerHands[h]._handCards.size();
                    i=0;
                    for (int c=0;c<handSize;c++ )
                    {

                        BOOST_LOG_TRIVIAL(debug) << "card " << i << " discarding";
                        i++;
                        _players[p]._playerHands[h].dealIndexCardFromHandToHand(0, _houseCards._discardPile, false);
                    }

                    
                }

                _players[p]._playerHands.clear();
                _players[p]._isFinished = false;

            }
            _roundNum += 1;
        };

        void calculateTurnResults()
        {
            int dealerScore =  _players[_players.size()-1]._playerHands[0]._handValue;

            BOOST_LOG_TRIVIAL(debug) << "calc turn result";
            BOOST_LOG_TRIVIAL(debug) << "dealer score: " << dealerScore;

            for (int p=0;p<_numPlayers;p++)
            {
                for (int h=0;h<_players[p]._playerHands.size();h++ )
                {
                    _players[p]._playerHands[h].printHand();
                    cout << "\n";
                    if (_players[p]._playerHands[h]._isBust) 
                    {
                        //Player is bust, loses
                        _players[p].playerLoses(_players[p]._playerCurBet);
                        //Adjust House
                        _players[_players.size()-1].playerWins(_players[p]._playerCurBet);

                    }
                    else if (_players[p]._playerHands[h]._isBlackjack) 
                    {
                        //Player is blackjack, use house rules
                        _players[p].playerWinsMultiple(_players[p]._playerCurBet, BLACKJACK_MULTIPLE);
                        //Adjust House
                        _players[_players.size()-1].playerLosesMultiple(_players[p]._playerCurBet, BLACKJACK_MULTIPLE);
                    }

                    else if (_players[p]._playerHands[h]._isSurrendered)
                    {
                        _players[p].playerLosesMultiple(_players[p]._playerCurBet, 0.5);
                        //Adjust House
                        _players[_players.size()-1].playerWinsMultiple(_players[p]._playerCurBet, BLACKJACK_MULTIPLE);
                    }

                    else if (_players[p]._playerHands[h]._handValue > dealerScore)
                    {
                        //Player wins, due to higher score and not bust (bust checked earlier)
                        _players[p].playerWins(_players[p]._playerCurBet);
                        //Adjust House
                        _players[_players.size()-1].playerLoses(_players[p]._playerCurBet);
                    } 
                    else if (_players[p]._playerHands[h]._handValue < dealerScore) 
                    {
                        //Player loses, due to lower score
                        _players[p].playerLoses(_players[p]._playerCurBet);
                        //Adjust House
                        _players[_players.size()-1].playerWins(_players[p]._playerCurBet);
                    } 
                    else if (_players[p]._playerHands[h]._handValue == dealerScore) 
                    {
                        //Player push
                        if (DEALER_PUSH_RESULT == "tie")
                        {
                            // Do nothing in tie push
                        } 
                        else if (DEALER_PUSH_RESULT == "win")
                        {
                            _players[p].playerWins(_players[p]._playerCurBet);
                            //Adjust House
                            _players[_players.size()-1].playerLoses(_players[p]._playerCurBet);
                        } 
                        else if (DEALER_PUSH_RESULT == "lose")
                        {
                            _players[p].playerLoses(_players[p]._playerCurBet);
                            //Adjust House
                            _players[_players.size()-1].playerWins(_players[p]._playerCurBet);
                        }
                        else
                        {
                            BOOST_LOG_TRIVIAL(error) << "Invalid Dealer rule on push";
                        }
                    }
                } //end hand loop
            } // end player loop
        };

        void takeInitialBets()
        {
            std::string line;
            int curBet;

            for (int p=0;p<_numPlayers;p++)
            //take all player bets
            {
                if (_players[p]._isHuman) {

                    cout << "Enter a bet for Player " << _players[p]._playerNumber << ":\n";
                    std::cin.clear();
                    while (std::getline(std::cin, line))
                    {
                        std::stringstream ss(line);
                        if (ss >> curBet)
                        {
                            if (ss.eof())
                            {   // Success
                                break;
                            }
                        }
                        std::cout << "Invalid entry, retry bet entry!" << endl;
                    }
                    std::cin.clear();
                    std::cout << "Bet: " << curBet << endl; 
                    _players[p]._playerCurBet = curBet;
 

                }  else if (_players[p]._isBot) {
                    // {}{}{} Add bot logic for gambling
                    _players[p]._playerCurBet = 30;

                } else {
                    cout << "invalid betting!\n";
                }



            }

        };

        void processPlayerTurns()
        // process all player turns
        {
            char curAction;
            int ii; //counter for active hand

            for (int p=0;p<_numPlayers+1;p++){
                //process all player turns
                    if (_players[p]._isHuman){
                        //Accept actions to process turn
                        while (_players[p]._isFinished == false)
                        {
                            ii = 0;
                            while (true) // this should have some logic to exit besides a break
                            {
                                cout << "Select action for Player " << _players[p]._playerNumber << ", Hand " << ii << "\n";
                                cout << "Possible actions [";
                                for (char action :  _players[p]._playerHands[ii]._possibleActions)
                                {
                                    cout << action << " ";
                                }
                                cout << "]\n";
                                
                                // {}{}{} adjust input to transform to capital letters and only first, then clear other character in stdin
                                std::cin.clear();
                                std::cin >> curAction;
                                std::cin.clear();
                                // curAction = TakeNCharactersFromInput(1)[0];
                                
                                if ( std::find(_players[p]._playerHands[ii]._possibleActions.begin(), 
                                     _players[p]._playerHands[ii]._possibleActions.end(), curAction) != 
                                     _players[p]._playerHands[ii]._possibleActions.end() )

                                {
                                    // cout << "valid action selected\n";
                                    BOOST_LOG_TRIVIAL(debug) << "valid action selected";
                                    BOOST_LOG_TRIVIAL(debug) << "Player " << p << ": action " << curAction;
                                    
                                    //Execute Valid command
                                    executePlayerAction(curAction, _players[p]._playerHands[ii], _houseCards);
                                    if (_exit_flag)
                                    {
                                        return;
                                    }
                                    // curAction
                                    printRoundStatus();


                                } else {
                                    BOOST_LOG_TRIVIAL(debug) << "invalid action selected";
                                    cout << "invalid action selected, retry command\n";
                                }

                                _players[p].updateIsFinished();
                                if (_players[p]._isFinished)
                                {
                                    break;
                                }

                            }
                        }
                        

                    } else if (_players[p]._isBot){
                        //Use bot logic to process turn
                        //start debug with always hit

                    } else if (_players[p]._isDealer){
                        //Use Dealer logic to process turn 

                        // DEALER_HIT_SOFT_17
                        if (_players[p]._playerHands[0]._handValue <= DEALER_HIT_LIMIT)                            
                        { 
                            // Dealer must hit on anything equal to or less than DEALER_HIT_LIMIT
                            executePlayerAction('H', _players[p]._playerHands[0], _houseCards);
                            BOOST_LOG_TRIVIAL(debug) << "valid action selected";
                            BOOST_LOG_TRIVIAL(debug) << "Player " << p << ": action " << curAction;
                        } else {
                            // Dealer must stay if greater than the DEALER_HIT_LIMIT
                            executePlayerAction('S', _players[p]._playerHands[0], _houseCards);
                            BOOST_LOG_TRIVIAL(debug) << "valid action selected";
                            BOOST_LOG_TRIVIAL(debug) << "Player " << p << ": action " << curAction;
                        }

                    } 
                }
        };

        void executePlayerAction(char action, Hand &hand, HouseCards &houseCards)
        {
            // 'H', 'S', 'P', 'D', 'R'
            //  Hit, Stay, Split, DoubleDown, Surrender
            // cout << "execute " << action << "\n";
            BOOST_LOG_TRIVIAL(debug) << "execute " << action;
            if (action == 'H') {
                // Hit
                cout << "Hit\n";
                houseCards._shoe.dealRandomCardFromHandToHand(hand, true);


            } else if (action == 'S') {
                // Stay
                cout << "Stay\n";
                hand._isFinished = true;

            } else if (action == 'P') {
                // Split

            } else if (action == 'D') {
                // Double Down

            } else if (action == 'R') {
                // Surrender
                cout << "Surrender\n";
                hand._isFinished = true;
                hand._isSurrendered = true;
            
            } 
            else if (action == 'Q') {
                // Quit
                cout << "Quit\n";
                this->_exit_flag = true;
            } 

            else {
                cout << "action not in list";
            }

        };

        void dealInitialCards()
        {
            for (int p=0;p<_numPlayers+1;p++){
                // First card
                if (p < _numPlayers){
                    //Player card, player cards are always face up
                    // _houseCards._shoe.dealRandomCardFromHandToHand(_players[p]._playerHands[0], true);
                    _players[p].dealCardToPlayerNewHand(_houseCards, true);
                } else {
                    //Dealer card, first is face down
                    // _houseCards._shoe.dealRandomCardFromHandToHand(_players[p]._playerHands[0], false);
                    _players[p].dealCardToPlayerNewHand(_houseCards, false);

                }
                BOOST_LOG_TRIVIAL(debug) << "deal initial card to Player " << p;
            }

            for (int p=0;p<_numPlayers+1;p++){
                // Second card is always face up
                    _houseCards._shoe.dealRandomCardFromHandToHand(_players[p]._playerHands[0], true);
                    BOOST_LOG_TRIVIAL(debug) << "deal second card to Player " << p;
                }
            

        };


        void printRoundStatus(){
            //print all information relevant to round

            cout << "Round number: " << _roundNum << endl;
            for (int p=0;p<_numPlayers+1;p++){

                    cout << "Player " << p << endl;
                    _players[p].printPlayerData();
                }

        };

        int _numHumanPlayers; //this is at least 1
        int _numComputerPlayers; //this is 0 or more
        int _numPlayers; //human players + computer players + dealer
        int _numGamblers; //human players + computer players (is _numPlayers - 1)
        
        int _roundNum = 1;

        long long int _initialPlayerMoney;
        long long int _initialCasinoInitialMoney;

        vector<Player> _players;
        int _numDecks;

        HouseCards _houseCards;
        bool _exit_flag = false;

};
