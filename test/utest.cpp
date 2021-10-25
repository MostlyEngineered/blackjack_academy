#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
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


TEST(CardInstantiation, CardDeal){
    AllCards test_cards = AllCards(2);
    Hand hand;
    // test_cards3.dealIndexCardFromShoeToHand(0, testhand);
    // test_cards.dealIndexCardFromShoeToHand(1, testhand);
    // testhand.printHand();

    test_cards._shoe._handCards[1]->printCard();
    // test_cards3.dealIndexCardFromShoeToHand(1, testhand);
    // hand.moveCardToHand(std::move(test_cards._shoe._handCards[2]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[1]));
    // hand.moveCardToHand(std::move(test_cards._shoe._handCards[1]));
    hand.printHand();

    

    EXPECT_EQ(1, 1);


    // test_cards.dealCardFromShoeToHand()
    
}


int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}