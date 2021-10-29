#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <optional>
#include <vector>
// #include "../src/card_classes.hpp"
#include "../src/game_classes.hpp"

TEST(CardInstantiation, MakeDecks){
    HouseCards test_cards = HouseCards(2);
    EXPECT_EQ(test_cards._curID, 104);
    HouseCards test_cards2 = HouseCards(5);
    EXPECT_EQ(test_cards2._curID, 260);
    Hand testhand;
}

TEST(CardInstantiation, CheckCardValues){
    Card two = Card('H', '2', 0);
    Card five = Card('H', '5', 0);
    Card ten = Card('H', 'T', 0);
    Card jack = Card('H', 'J', 0);
    Card queen = Card('H', 'Q', 0);
    Card king = Card('H', 'K', 0);
    Card ace = Card('H', 'A', 0);

    EXPECT_EQ(two._hardValue, 2);
    EXPECT_EQ(five._hardValue, 5);
    EXPECT_EQ(ten._hardValue, 10);
    EXPECT_EQ(jack._hardValue, 10);
    EXPECT_EQ(queen._hardValue, 10);
    EXPECT_EQ(king._hardValue, 10);
    EXPECT_EQ(ace._hardValue, 11);
}


TEST(CardInstantiation, CheckHandValues){
    HouseCards test_cards = HouseCards(1);
    Hand hand1;
    Hand hand2;

    // Deal hand 1
    test_cards.dealIndexCardFromShoeToHand(1, hand1); // 3
    test_cards.dealIndexCardFromShoeToHand(3, hand1); // 6
    EXPECT_EQ(hand1._isBlackjack, false);
    test_cards.dealIndexCardFromShoeToHand(7, hand1); // J
    EXPECT_EQ(hand1._handValue, 19);
    EXPECT_EQ(hand1._isBlackjack, false);

    // Deal hand 2
    test_cards.dealIndexCardFromShoeToHand(8, hand2); // K
    test_cards.dealIndexCardFromShoeToHand(8, hand2); // A, Blackjack
    EXPECT_EQ(hand2._isBlackjack, true);
    EXPECT_EQ(hand2._handValue, 21);
    test_cards.dealIndexCardFromShoeToHand(20, hand2); // A -> use soft value
    EXPECT_EQ(hand2._handValue, 12);
    EXPECT_EQ(hand2._isBlackjack, false);
    test_cards.dealIndexCardFromShoeToHand(44, hand2); // K -> 22, bust
    EXPECT_EQ(hand2._handValue, 22);
    EXPECT_EQ(hand2._isBlackjack, false);
    test_cards.dealIndexCardFromShoeToHand(43, hand2); // Q -> bust +10 = bust
    EXPECT_EQ(hand2._handValue, 22);
    
}

TEST(CardInstantiation, DealAllRandomCards){
    HouseCards test_cards = HouseCards(1);
    Hand hand;

    for (int i=0;i<52;i++){
        test_cards.dealRandomCardFromShoeToHand(hand);  // Deal all cards
    }
    EXPECT_EQ(hand._handSize, 52);
    EXPECT_EQ(test_cards._shoe._handSize, 0);

}

TEST(CardInstantiation, CheckSplittableAndDoubleDownable){
    HouseCards test_cards = HouseCards(1);
    Hand hand1;
    Hand hand2;

    // deal hand 1
    test_cards.dealIndexCardFromShoeToHand(1, hand1); // 3C
    EXPECT_EQ(hand1._isSplittable, false);
    EXPECT_EQ(hand1._isDoubleDownable, false);
    EXPECT_EQ(test_cards._runningCount, 1);
    EXPECT_NEAR(test_cards._trueCountValue, 1.01960784314, .001);
    
    test_cards.dealIndexCardFromShoeToHand(13, hand1); // 3D
    EXPECT_EQ(hand1._isSplittable, true);
    EXPECT_EQ(hand1._isDoubleDownable, true);
    EXPECT_EQ(test_cards._runningCount, 2);    
    EXPECT_NEAR(test_cards._trueCountValue, 2.08, .001);
 

    test_cards.dealIndexCardFromShoeToHand(15, hand1); // 6D
    EXPECT_EQ(hand1._isSplittable, false);
    EXPECT_EQ(hand1._isDoubleDownable, false);
    EXPECT_EQ(test_cards._runningCount, 3);
    EXPECT_NEAR(test_cards._trueCountValue, 3.18367346939, .001);
    
    // deal hand 2
    test_cards.dealIndexCardFromShoeToHand(1, hand2); // 4C
    EXPECT_EQ(hand2._isSplittable, false);
    EXPECT_EQ(hand2._isDoubleDownable, false);
    EXPECT_EQ(test_cards._runningCount, 4);
    EXPECT_NEAR(test_cards._trueCountValue, 4.33333333333, .001);
    
    test_cards.dealIndexCardFromShoeToHand(40, hand2); // 7S
    EXPECT_EQ(hand2._isSplittable, false);
    EXPECT_EQ(hand2._isDoubleDownable, true);
    EXPECT_EQ(test_cards._runningCount, 4);
    EXPECT_NEAR(test_cards._trueCountValue, 4.42553191489, .001);
    
    test_cards.dealIndexCardFromShoeToHand(43, hand2); // JS
    EXPECT_EQ(hand2._isSplittable, false);
    EXPECT_EQ(hand2._isDoubleDownable, false);
    EXPECT_EQ(test_cards._runningCount, 3);
    EXPECT_NEAR(test_cards._trueCountValue, 3.39130434783, .001);
    
}



TEST(PlayerInstantiation, MakePlayer){
    Player player = Player('H', 1);
    
}


int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}