#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include "card_classes.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

// vector<char> suits{ 'C', 'D', 'H', 'S'};
// vector<char> ranks{ '2', '3', '4', '5', '6', 
//     '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

void Card::calculateHardValue(){
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

void Card::calculateRunningCountValue(){
    // These are the standard running count values
    // These are usually calculated from player standpoint by adding
    // These will be done by the count in the shoe in this code so they will be subtracted
    if (_hardValue <= 6){
        _runningCountValue = 1;
    } else if ((_hardValue >= 7) && (_hardValue <= 9)){
        _runningCountValue = 0;
    } else{
        _runningCountValue = -1;
    }
};

void Hand::calculateHandValue(){
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
        _isBust = true; // >21 is the bust condition
        _isFinished = true; // No actions available after bust
    }

    if ( (_handValue == 21) && (_handCards.size()==2)){
        //This is the blackjack condition 
        _isBlackjack = true; 
    } else {
        //player can hit past blackjack if they want, need to be able to revert condition to not blackjack
        _isBlackjack = false; 
    }

};


// void Hand::moveCardToHand(unique_ptr<Card> card){
//     // _handCards.emplace_back(std::move(card));
//     _handCards.push_back(std::move(card));
//     calculateHandValue();
//     updateHandSize();
// };

void Hand::printHand(){
    for (auto &c : _handCards){
        c->printCard();
    }
    cout << "Hand values: " << this->_handValue << " DD:" << this->_isDoubleDownable << 
    ",Sp:" << this->_isSplittable << ", Bu:" << this->_isBust << ", Fi:" << this->_isFinished;
};

void Hand::logHand(){
    for (auto &c : _handCards){
        c->printCard();
    }
    BOOST_LOG_TRIVIAL(debug) << "Hand values: " << this->_handValue << " DD:" << this->_isDoubleDownable << 
    ",Sp:" << this->_isSplittable << ", Bu:" << this->_isBust << ", Fi:" << this->_isFinished;
};

void Hand::updateHandSplittable(){ 
    //This should be called after handsize is updated
    //Splittable hands are hands of size 2 that are a pair (identical rank)
    if (_handCards.size() == 2){
        _isDoubleDownable = true; // double down only valid on initial cards 
        _isSurrenderable = true;  // surrender only valid on initial cards
        if (_handCards[0]->_cRank == _handCards[1]->_cRank){ // hand of 2 is pair
            _isSplittable = true;
        } else {
            _isSplittable = false;
        }
    } else { // hand not equal to 2 cards
        _isSplittable = false;
        _isDoubleDownable = false;
        _isSurrenderable = false;
    }
};


// Udacity code template

void test_modifyMessage(std::promise<std::string> && prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // simulate work
    std::string modifiedMessage = message + " has been modified"; 
    prms.set_value(modifiedMessage);
}

int test_main()
{
    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(test_modifyMessage, std::move(prms), messageToThread);

        // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;
    
    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}

void returnBotDecision(std::promise<std::string> && prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // simulate work
    std::string modifiedMessage = message + " has been modified"; 
    prms.set_value(modifiedMessage);
}

int calculateAllLogic()
{


    // start several logic threads lock and unlock each one


    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(test_modifyMessage, std::move(prms), messageToThread);

        // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;
    
    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}


// std::mutex g_lock;
 
// void func()
// {
//     g_lock.lock();
 
//     std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
//     std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
 
//     g_lock.unlock();
// }


