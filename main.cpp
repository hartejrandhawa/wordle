/*
 * This file contains the `main` function, which serves as the entry point
 * for the program. It sets up the Wt server application, handles the
 * application life cycle, and instantiates the WordleApplication class
 * to manage user interactions with the game.
 * 
 */

#include <Wt/WApplication.h>
#include "WordleApplication.h"

int main(int argc, char **argv)
{
  /*
   * The `Wt::WRun` function starts the server application and handles
   * all application life cycles. It takes `argc` and `argv` as parameters
   * and a lambda function as the third parameter. This lambda function
   * will be executed when a new user accesses the application.
   */
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {

    return std::make_unique<WordleApplication>(env); // Instantiate WordleApplication and handle user interactions
    
  });
}
