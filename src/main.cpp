#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include "card_classes.hpp"
using std::cout;
#include <stdlib.h>

#include <thread>
#include <future>

#include <boost/log/core.hpp> 
#include <boost/log/trivial.hpp> 
#include <boost/log/expressions.hpp> 
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

 
void init_logging()
{
    logging::add_file_log(keywords::file_name = "sample.log");

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::debug
    );
}







int main(int, char*[]){
    init_logging();
    
    // BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    // BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    // BOOST_LOG_TRIVIAL(info) << "This is an informational severity message"; 
    // BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    // BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    // BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";

    Game myGame = Game(1, 500000, 1);
    // Game myGame;
    // Player player = Player('H', 1, 5);
    // Players players = Players(1, 500000);
    // Shoe *_test_shoe = new Shoe(1);
    // cout << "start game" << endl;
    while (true)
    {
        myGame.playRound();
        if (myGame._exit_flag)
        {
            break;
        }
        
    }
    // cout << "program works" << endl;
    return 0;
}