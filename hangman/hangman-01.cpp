/* game loop với logic tối thiểu chỉ đủ chạy được chương trình */

#include <iostream>

using namespace std;

struct Hangman {
    string secretWord;
    string guessedWord;
    int badGuesses;

    void init() {
        secretWord = "hello"; //todo: random
        guessedWord = string(secretWord.length(), '_');
        badGuesses = 0;
    }

    void update(char input) {
        badGuesses++;
    }

    bool isOver() {
        return badGuesses >= 6;
    }
};

void render(const Hangman& game) {
    cout << "Bad guesses: " << game.badGuesses << endl;
    cout << "Guessed word: " << game.guessedWord << endl;
}

char get_input() {
    string input;
    cout << "Make a guess: ";
    cin >> input;
    return input[0];
}

int main(int argc, char ** argv) {
    Hangman game;
    game.init();

    render(game);
    do {
        char input = get_input();
        game.update(input);
        render(game);
    } while (!game.isOver());

    return 0;
}
