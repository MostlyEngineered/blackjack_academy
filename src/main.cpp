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


// Udacity code template

void modifyMessage(std::promise<std::string> && prms, std::string message)
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
    std::thread t(modifyMessage, std::move(prms), messageToThread);

        // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;
    
    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // thread barrier
    t.join();

    return 0;
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