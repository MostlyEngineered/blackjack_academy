#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include "../src/card_classes.hpp"

// TEST(CardInstantiation, MakeDecks){ // old test
//     HouseCards test_cards = HouseCards(2);
//     EXPECT_EQ(test_cards._curID, 104);
//     HouseCards test_cards2 = HouseCards(5);
//     EXPECT_EQ(test_cards2._curID, 260);
//     Hand testhand;
// }

// TEST(CardInstantiation, MakeDecks){ 
//     Shoe test_cards = Shoe(2);
//     EXPECT_EQ(test_cards._curID, 104);
//     Shoe test_cards2 = Shoe(5);
//     EXPECT_EQ(test_cards2._curID, 260);

// }


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
    // HouseCards test_cards = HouseCards(1);
    Shoe test_cards = Shoe(1);
    Hand hand1;
    Hand hand2;

    // Deal hand 1
    test_cards.dealIndexCardFromHandToHand(1, hand1, true); // 3
    test_cards.dealIndexCardFromHandToHand(3, hand1, true); // 6
    EXPECT_EQ(hand1._isBlackjack, false);
    test_cards.dealIndexCardFromHandToHand(7, hand1, true); // J
    EXPECT_EQ(hand1._handValue, 19);
    EXPECT_EQ(hand1._isBlackjack, false);

    // Deal hand 2
    test_cards.dealIndexCardFromHandToHand(8, hand2, true); // K
    test_cards.dealIndexCardFromHandToHand(8, hand2, true); // A, Blackjack
    EXPECT_EQ(hand2._isBlackjack, true);
    EXPECT_EQ(hand2._handValue, 21);
    test_cards.dealIndexCardFromHandToHand(20, hand2, true); // A -> use soft value
    EXPECT_EQ(hand2._handValue, 12);
    EXPECT_EQ(hand2._isBlackjack, false);
    test_cards.dealIndexCardFromHandToHand(44, hand2, true); // K -> 22, bust
    EXPECT_EQ(hand2._handValue, 22);
    EXPECT_EQ(hand2._isBlackjack, false);
    test_cards.dealIndexCardFromHandToHand(43, hand2, true); // Q -> bust +10 = bust
    EXPECT_EQ(hand2._handValue, 22);
    
}

TEST(CardInstantiation, DealAllRandomCards){
    Shoe test_cards = Shoe(1);
    Hand hand;

    for (int i=0;i<52;i++){
        test_cards.dealRandomCardFromHandToHand(hand, true);  // Deal all cards
    }
    EXPECT_EQ(hand._handSize, 52);
    EXPECT_EQ(test_cards._handSize, 0);
    

}

TEST(CardInstantiation, CheckSplittableAndDoubleDownable){
    Shoe test_cards = Shoe(1);
    Hand hand1;
    Hand hand2;

    // deal hand 1
    test_cards.dealIndexCardFromHandToHand(1, hand1, true); // 3C
    EXPECT_EQ(hand1._isSplittable, false);
    EXPECT_EQ(hand1._isDoubleDownable, false);
    // EXPECT_EQ(test_cards._runningCount, 1);
    // EXPECT_NEAR(test_cards._trueCountValue, 1.01960784314, .001);
    
    test_cards.dealIndexCardFromHandToHand(13, hand1, true); // 3D
    EXPECT_EQ(hand1._isSplittable, true);
    EXPECT_EQ(hand1._isDoubleDownable, true);
    // EXPECT_EQ(test_cards._runningCount, 2);    
    // EXPECT_NEAR(test_cards._trueCountValue, 2.08, .001);
 

    test_cards.dealIndexCardFromHandToHand(15, hand1, true); // 6D
    EXPECT_EQ(hand1._isSplittable, false);
    EXPECT_EQ(hand1._isDoubleDownable, false);
    // EXPECT_EQ(test_cards._runningCount, 3);
    // EXPECT_NEAR(test_cards._trueCountValue, 3.18367346939, .001);
    
    // deal hand 2
    test_cards.dealIndexCardFromHandToHand(1, hand2, true); // 4C
    EXPECT_EQ(hand2._isSplittable, false);
    EXPECT_EQ(hand2._isDoubleDownable, false);
    // EXPECT_EQ(test_cards._runningCount, 4);
    // EXPECT_NEAR(test_cards._trueCountValue, 4.33333333333, .001);
    
    test_cards.dealIndexCardFromHandToHand(40, hand2, true); // 7S
    EXPECT_EQ(hand2._isSplittable, false);
    EXPECT_EQ(hand2._isDoubleDownable, true);
    // EXPECT_EQ(test_cards._runningCount, 4);
    // EXPECT_NEAR(test_cards._trueCountValue, 4.42553191489, .001);
    
    test_cards.dealIndexCardFromHandToHand(43, hand2, true); // JS
    EXPECT_EQ(hand2._isSplittable, false);
    EXPECT_EQ(hand2._isDoubleDownable, false);
    // EXPECT_EQ(test_cards._runningCount, 3);
    // EXPECT_NEAR(test_cards._trueCountValue, 3.39130434783, .001);
    
}

TEST(CardInstantiation, MakePlayerHand){
    Player test_player = Player('H', 0, 50000);
    // Shoe test_cards = Shoe(1);
    // HouseCards test_house(1);

    test_player.makePlayerNewHand();

    // test_house.dealToHand(&(test_player._playerHands[0]));
    // test_house.dealToHand(test_player._playerHands[0]);
    // test_house._shoe.dealRandomCardFromHandToHand(test_player._playerHands[0], true);
    // test_cards.dealRandomCardFromHandToHand(test_player._playerHands[0], true);
    // test_player.printPlayerData();


}


int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}