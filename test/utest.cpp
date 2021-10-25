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

    // test_cards._shoe._handCards[1]->printCard();
    // test_cards._shoe._handCards[4]->printCard();
    // test_cards._shoe._handCards[9]->printCard();

    cout << "Start deal" << endl ;
    hand1.moveCardToHand(std::move(test_cards._shoe._handCards[1])); // 3
    hand1.moveCardToHand(std::move(test_cards._shoe._handCards[4])); // 6
    hand1.moveCardToHand(std::move(test_cards._shoe._handCards[9])); // J

    EXPECT_EQ(hand1._handValue, 19);
    
    hand2.moveCardToHand(std::move(test_cards._shoe._handCards[11]));
    hand2.moveCardToHand(std::move(test_cards._shoe._handCards[12])); //Blackjack
    hand2.moveCardToHand(std::move(test_cards._shoe._handCards[25])); //2nd ace makes this 12

    EXPECT_EQ(hand2._handValue, 12);

    cout << "End deal" << endl ;
}



int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}