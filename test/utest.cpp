#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include "../src/card_classes.hpp"

TEST(CardInstantiation, MakeDecks){
    AllCards test_cards = AllCards(2);
    EXPECT_EQ(test_cards._curID, 104);
    AllCards test_cards2 = AllCards(5);
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
    AllCards test_cards = AllCards(1);
    Hand hand1;
    Hand hand2;

    test_cards.dealIndexCardFromShoeToHand(1, hand1); // 3
    test_cards.dealIndexCardFromShoeToHand(3, hand1); // 6
    test_cards.dealIndexCardFromShoeToHand(7, hand1); // J

    // Deal hand 1
    EXPECT_EQ(hand1._handValue, 19);
    test_cards.dealIndexCardFromShoeToHand(8, hand2); // K
    test_cards.dealIndexCardFromShoeToHand(8, hand2); // A, Blackjack

    // Deal hand 2
    EXPECT_EQ(hand2._handValue, 21);
    test_cards.dealIndexCardFromShoeToHand(20, hand2); // A -> use soft value
    EXPECT_EQ(hand2._handValue, 12);
    test_cards.dealIndexCardFromShoeToHand(44, hand2); // K -> 22, bust
    EXPECT_EQ(hand2._handValue, 22);
    test_cards.dealIndexCardFromShoeToHand(43, hand2); // Q -> bust +10 = bust
    EXPECT_EQ(hand2._handValue, 22);
    
}

TEST(CardInstantiation, DealAllRandomCards){
    AllCards test_cards = AllCards(1);
    Hand hand;

    for (int i=0;i<52;i++){
        test_cards.dealRandomCardFromShoeToHand(hand);  // Deal all cards
    }
    // cout << " print hand" << endl;
    // hand.printHand();
    // cout << " print shoe" << endl;
    // test_cards._shoe.printHand();
    
}

TEST(PlayerInstantiation, DealAllRandomCards){
    // Player test_player;
    
    // test_player.dealCardToPlayerNewHand();
    // test_player._playerHands[0].printHand();

}


int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}