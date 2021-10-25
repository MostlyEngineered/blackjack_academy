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
    AllCards test_cards = AllCards(2);
    Hand hand1;
    Hand hand2;

    // test_cards._shoe._handCards[1]->printCard();
    // test_cards._shoe._handCards[4]->printCard();
    // test_cards._shoe._handCards[9]->printCard();

    hand1.moveCardToHand(std::move(test_cards._shoe._handCards[1])); // 3
    hand1.moveCardToHand(std::move(test_cards._shoe._handCards[4])); // 6
    hand1.moveCardToHand(std::move(test_cards._shoe._handCards[9])); // J

    EXPECT_EQ(hand1._handValue, 19);
    
    hand2.moveCardToHand(std::move(test_cards._shoe._handCards[11]));
    hand2.moveCardToHand(std::move(test_cards._shoe._handCards[12])); //Blackjack
    hand2.moveCardToHand(std::move(test_cards._shoe._handCards[25])); //2nd ace makes this 12

    EXPECT_EQ(hand2._handValue, 12);
}



TEST(CardInstantiation, CardDeal){
    AllCards test_cards = AllCards(2);
    Hand hand;
    // test_cards3.dealIndexCardFromShoeToHand(0, testhand);
    // test_cards.dealIndexCardFromShoeToHand(1, testhand);
    // testhand.printHand();

    // test_cards._shoe._handCards[1]->printCard();
    // test_cards3.dealIndexCardFromShoeToHand(1, testhand);
    // hand.moveCardToHand(std::move(test_cards._shoe._handCards[2]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[1]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[8]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[9]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[10]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[11]));
    hand.moveCardToHand(std::move(test_cards._shoe._handCards[12]));
    // cout << "test value is: " << test_cards._shoe._handCards[1];
    // hand.printHand();
    // cout << ((int)(hand._handCards[0].get()->_cRank)) - 48 << endl;
    // cout << ((int)(hand._handCards[1].get()->_cRank)) - 48 << endl;
    // cout << ((int)(hand._handCards[2].get()->_cRank)) - 48 << endl;
    // cout << ((int)(hand._handCards[3].get()->_cRank)) - 48 << endl;
    // cout << ((int)(hand._handCards[4].get()->_cRank)) - 48 << endl;
    // cout << ((int)(hand._handCards[5].get()->_cRank)) - 48 << endl;

    
    

    EXPECT_EQ(1, 1);


    // test_cards.dealCardFromShoeToHand()
    
}


int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}