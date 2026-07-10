/*
 * This file defines the WordleApplication class, which inherits from Wt::WApplication
 * and manages the game logic and user interface. It declares member variables and
 * functions for handling user input, processing guesses, and displaying game outcomes.
 * 
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <fstream>
#include <string>

class WordleApplication : public Wt::WApplication
{
public:
  /*
   * Constructor for WordleApplication class.
   * Initializes the game interface and connects the input button to the guess processing logic.
   */
  WordleApplication(const Wt::WEnvironment& env);

private:

  Wt::WText     *prompt_;       // Widget for game instructions
  Wt::WLineEdit *guessInput_;   // Widget for user guesses
  Wt::WText     *invalidState_; // Widget for invalid input messages
  Wt::WText     *guessOutput_;  // Widget for displaying feedback
  Wt::WText     *exitLine1_;    // Widget for exit message line 1
  Wt::WText     *exitLine2_;    // Widget for exit message line 2

  void guessSubmitted(const std::string& guess, const std::string& word);   // Process user guesses
  void processGuess(const std::string& guess, const std::string& word);     // Update game interface
  std::string pickRandomWord(const std::string& filename);                  // Pick a random word
};
