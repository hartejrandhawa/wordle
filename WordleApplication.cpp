/*
 * This file contains the implementation of the WordleApplication class, which
 * handles the main logic of the game. It uses Wt widgets to create a web-based
 * interface for the game, allowing users to input guesses and providing feedback
 * on their guesses.
 * 
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "WordleApplication.h"
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>  

int guessesMade = 0;    // number of guesses made counter

/*
 * Constructor for WordleApplication class.
 * Initializes the game interface and connects the input button to the guess processing logic.
 */
WordleApplication::WordleApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{
  setTitle("Wordle");                            // application title

  prompt_ = root()->addWidget(std::make_unique<Wt::WText>());
  prompt_->setText("Enter a guess, 5 letters maximum: ");       // displays prompt 

  guessInput_ = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow text input
  guessInput_->setFocus();                              // give focus

  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Submit"));   // create a button
  button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

  invalidState_ = root()->addWidget(std::make_unique<Wt::WText>());

  std::string word = pickRandomWord("wordlist.txt");      // runs function to recieve random word for user to guess


  button->clicked().connect([=] {           // when the button is pressed by user it will process its guess
      std::string guess = guessInput_->text().toUTF8();
      std::string uppercaseGuess = guess;
      std::transform(uppercaseGuess.begin(), uppercaseGuess.end(), uppercaseGuess.begin(), ::toupper);   // making guess to all uppercase

      guessSubmitted(uppercaseGuess, word);   // running function to process guesses input
  });
}

/*
 * Callback function for processing user guesses.
 * Checks the validity of the guess and updates the game interface accordingly.
 */
void WordleApplication::guessSubmitted(const std::string& guess, const std::string& word)
{
  invalidState_->setText(" ");
  if (guess.size() != 5) {                                                    // checking if guess is 5 letters only
      invalidState_->setText(" Invalid guess. Please enter a 5-letter word.");
      return;
  }

  root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line break
  guessOutput_ = root()->addWidget(std::make_unique<Wt::WText>()); // empty text

  processGuess(guess, word);    // running function to process guess to actual word
}

/*
 * Process the user's guess and update the game interface with the result.
 * Compares the guessed word with the target word, highlighting correct and incorrect letters.
 * Displays congratulatory or game over message if the game is won or lost, respectively.
 */
void WordleApplication::processGuess(const std::string& guess, const std::string& word)
{
    std::string resultText;
    // comparing the letters of the users guess to the wordle word and colouring it according to if it is in the word and in the right position
    for (size_t i = 0; i < guess.size(); ++i) {      
        if (guess[i] == word[i]) {
            resultText += "<span style='color: green;'>" + std::string(1, guess[i]) + "</span>";  // green indicating correct letters in the correct places 
        } else if (word.find(guess[i]) != std::string::npos) {
            resultText += "<span style='color: red;'>" + std::string(1, guess[i]) + "</span>";    // red letters indicating correct letters in incorrect places 
        } else {
            resultText += "<span style='color: grey;'>" + std::string(1, guess[i]) + "</span>";   // grey letters indicating incorrect letters
        }
    }
    
    // displayng the results of the users guess
    auto resultWidget = std::make_unique<Wt::WText>(resultText, Wt::TextFormat::UnsafeXHTML);
    root()->addWidget(std::move(resultWidget));

    // check if the game is won
    if (guess == word) {
      root()->addWidget(std::make_unique<Wt::WBreak>());
      root()->addWidget(std::make_unique<Wt::WBreak>());
      exitLine1_ = root()->addWidget(std::make_unique<Wt::WText>());
      exitLine1_->setText("Congratulations! You guessed the word: " + word + ".");    // display congratulatory message and stop the application

      root()->addWidget(std::make_unique<Wt::WBreak>());
      exitLine2_ = root()->addWidget(std::make_unique<Wt::WText>());
      exitLine2_->setText("Refresh the page to play again.");

      guessesMade = 0;    // restarting the guess counter 
      return; // stop the application here
    }

    guessesMade++;    // updating the counter as one more guess has been made

    // check if the maximum number of guesses (6) is reached
    if (guessesMade == 6){
      root()->addWidget(std::make_unique<Wt::WBreak>());      // display game over message and stop the application
      root()->addWidget(std::make_unique<Wt::WBreak>());
      exitLine1_ = root()->addWidget(std::make_unique<Wt::WText>());
      exitLine1_->setText("You are out of guesses, the word is " + word + ".");

      root()->addWidget(std::make_unique<Wt::WBreak>());
      exitLine2_ = root()->addWidget(std::make_unique<Wt::WText>());
      exitLine2_->setText("Game over. Refresh the page to play again.");

      guessesMade = 0;    // restarting the guess counter 
      return;   // stop the application here
    }

}

/*
 * Picks a random word from a given wordlist file.
 * Returns the randomly selected word.
 */
std::string WordleApplication::pickRandomWord(const std::string& filename) 
{
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;

    // opening the wordlist file
    if (file.is_open()) {
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    } else {
        std::cerr << "Error: Could not open the wordlist file." << std::endl;
        return "ERROR"; // return an error string if the file cannot be opened
    }

    std::srand(std::time(0));
    int randomIndex = std::rand() % words.size();

    // returning a random word from the wordlist file
    return words[randomIndex];
}
