#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include "../src/card_classes.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::weak_ptr;
using std::unique_ptr;


class Player {
    private:

    public:
        Player(char playerType, int playerNumber, long long int playerMoney){
            _playerType = playerType;
            _playerNumber = playerNumber;

            if (playerType == 'D'){
                _isDealer = true;
                _isHuman = false;
                _playerMoney = 50000000;
            } else if (playerType == 'C'){
                _isDealer = false;
                _isHuman = false;
                _playerMoney = playerMoney;
            } else if (playerType == 'H'){
                _isDealer = false;
                _isHuman = true;
                _playerMoney = playerMoney;
            } else {
                cout << "Invalid Player type" << endl;
            }
            
        };

        Player(char playerType, int playerNumber){
            Player(playerType, playerNumber, 50000);
        };

        ~Player(){};

        // void makePlayerNewHand(){
        //     // Hand* hand = new Hand ;
        //     std::shared_ptr<Hand> hand;
        //     // unique_ptr<Hand> hand;
        //     _playerHands.push_back(std::move(hand));
        //     // return hand;
        // };

        void makePlayerNewHand(){
            Hand hand;
            // std::shared_ptr<Hand> hand;
            // unique_ptr<Hand> hand;
            _playerHands.push_back(hand);
            // return hand;
        };

        void dealCardToPlayerNewHand(HouseCards &houseCards, bool isFaceUp){  
            //append new hand to _playerHands and deal a random card from the shoe to it
            // Hand *hand;
            makePlayerNewHand();
            houseCards.dealRandomCardFromShoeToHand(_playerHands.back(), isFaceUp);
            
        };

        void printPlayerData(){
            string playerTag;
            if (_isDealer){
                playerTag = " (D)";
            } else if (_isHuman) {
                playerTag = " (H)";
            } else {
                playerTag = "";
            }

            cout << "Player " << _playerNumber << ":" << playerTag << endl;
            cout << "Money: " << _playerMoney << endl;
            // for (auto hand : _playerHands){
            for (int h=0;h<_playerHands.size();h++ ){
                cout << "Hand: " << (h+1) << " of " << _playerHands.size() << endl;    
                _playerHands[h].printHand();
            }
        }

        vector<Hand> _playerHands; //splits can make a player have multiple hands
        long long int _playerMoney; //how much money the player has
        int _playerNumber; //player number (this keeps track of player round resolution order)
        char _playerType; // 'H' Human, 'C' Computer, 'D' Dealer (no human dealers)
        bool _isDealer;
        bool _isHuman;
        bool _isFinished = false; //player is finished when all his current round hands are finished, when hands are cleaned up this should be reset back to false

};


class GameRound{
    private:

    public:
        GameRound(){};
        
        void incrementPlayerTurn(){
            _curPlayerTurn += 1;
            if (_curPlayerTurn>_numPlayers){
                _curPlayerTurn = 0;
            }
        };

        void resolvePayouts(){
            // resolve payouts for the round after dealer has taken turn

        };

        int _numHumanPlayers; //this is at least 1
        int _numComputerPlayers; //this is 0 or more
        int _numPlayers; //human players + computer players + dealer
        int _numGamblers; //human players + computer players (is _numPlayers - 1)
        int _curPlayerTurn = 0; //initialize as first gambler turn (dealer is last player)
        int _roundFinished = false; //Change to true after dealer has finished


};


class Game{
    // Dealer is last player.
    

    private:

    public:
        Game(int numPlayers, long long int initialPlayerMoney, int numDecks){
            //add logic to disallow <=1 and other bad values {}{}{}{}
            // This Constructor will be a single human player vs dealer
            
            _numPlayers = numPlayers;
            _initialPlayerMoney = initialPlayerMoney;
            _numDecks=numDecks;
            _numHumanPlayers = 1; //this is at least 1
            _numComputerPlayers = 0; //this is 0 or more
            _numGamblers = _numHumanPlayers + _numComputerPlayers; //human players + computer players (is _numPlayers - 1)
            // _numPlayers = _numGamblers + 1; //human players + computer players + dealer

            std::unique_ptr<HouseCards> houseCards = std::make_unique<HouseCards>(_numDecks); 
            // _houseCards = std::move(houseCards);
            seatPlayers();
            
        };
        // Game();

        // ~Game();


        //vector.insert(begin(), 1, val) //ref for adding dealer
        void playRound(){

            dealInitialCards();
            printRoundStatus();


        };



        void printRoundStatus(){
            //print all information relevant to round

            cout << "Round number: " << _roundNum << endl;
            for (auto player : _players){
                player.printPlayerData();
            }

        };

        void seatPlayers(){
            //instantiate all players and add them to the appropriate seats
            for (int p=0;p<_numPlayers;p++){
                if (p < _numPlayers-1){
                    _players.push_back(Player('H', p, _initialPlayerMoney));
                } else {
                    //can shuffle players here prior to adding dealer
                    _players.push_back(Player('D', p, _initialPlayerMoney));
                }


            }
        };

        void dealInitialCards(){
            // deal all players one card (face up, starting at player 1), dealer gets one card face down
            // deal all players second card (face up, starting at player 1), dealer gets one card face up
            for (auto player : _players){
                //deal first card, face down to dealer, face up to players
                if (player._isDealer==true){
                    player.makePlayerNewHand();

                    // this->_houseCards->dealRandomCardFromShoeToHand(*(player._playerHands[0]));

                    // player.dealCardToPlayerNewHand((this->_houseCards->_shoe), false);

                } else{
                    player.makePlayerNewHand();
                    // player.dealCardToPlayerNewHand((this->_houseCards->_shoe), true);

                }
            }

            for (auto player : _players){
                //deal second card face up to all
                // player.dealCardToPlayerNewHand(*(this->_houseCards), true);
            }
        };

        int _numHumanPlayers; //this is at least 1
        int _numComputerPlayers; //this is 0 or more
        int _numPlayers; //human players + computer players + dealer
        int _numGamblers; //human players + computer players (is _numPlayers - 1)
        
        int _roundNum = 1;

        long long int _initialPlayerMoney;
        long long int _initialCasinoInitialMoney;

        GameRound _curRound;
        vector<Player> _players;
        int _numDecks;

        std::unique_ptr<HouseCards> _houseCards;
        // HouseCards _houseCards(_numDecks);

};