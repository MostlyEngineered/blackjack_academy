#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::cout;

std::vector<char> suits{ 'C', 'D', 'H', 'S'};
std::vector<char> ranks{ '2', '3', '4', '5', '6', 
        '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};


class Card {

public:

    Card(char suit, char rank){

    };

    ~Card(){

    };

    double cardID;
    char rank;
    char suit;

private:


};

class  AllCards{
private:

public:

    AllCards(){

    };

    AllCards(int nDecks){
        curID = 0;
        

    };


    double curID;



};