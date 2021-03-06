/*
	Fayyaadh Razak & Victor Martins

	rolePlayingGame.cpp

	Create an RPG that will show your knowledge of everything that you
	have learned so far in this class, which includes, but is not
	limited to:
		- Functional Decomposition
		- Looping
		- Conditional Statements

	Input: Main menu choice, Character choice, Weapon choice

	Processing:
		1. Display menu of choices 1-3 for player to choose from
		2. When player chooses "2" at the start menu, then begin the game
		3. Add to player's point total based on what character they choose
		4. Start a specific minigame based on what weapon the player chooses:
			- If they choose "1" or "2", then they can attack as many monsters as they want to,
			  and points will be accumulated based on what monsters they attack
			- If they choose "3", then they will have the chance to create a potion, and they
			  will gain or lose points based on whether or not they successfully made the potion
		5. Check points in "highscore.txt" and points that the current player accumulated. If
		   current player got the new highscore, then their info will replace the info in
		   "highscore.txt".

	Output: Highscore of the player to a file (if it is higher than current high score)
*/

// Header Files
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

// Function Prototypes
void menu();
void rules();
int characterSelect(int, int);
int Weapon(int weaponChoice, int attack, int random, int points, int sessionChoice);
void Restart(char keepPlaying, int& points, int& menuChoice);
void saveHighscore(string&, int&);
void readHighscore(int, string, string&, int&);

int main() {
	// Variable Declarations
	int points = 0, random = 0, menuChoice, raceChoice = 0, weaponChoice = 0, 
		highScore, sessionChoice = 0, attack = 0;
	char keepPlaying = 'W';
	string playerName, highScoreName;
	fstream myFile;

	// Seed random function to current time
	srand(time(NULL));

	do {
		// Display Menu
		menu();
		cin >> menuChoice;

		// Display Rules
		if (menuChoice == 1) {
			rules();
		}

		// Start Game
		else if (menuChoice == 2) {
			// Assign points based on character selection
			points = characterSelect(raceChoice, points);

			// Assign points based on weapon gameplay
			points = Weapon(weaponChoice, attack, random, points, sessionChoice);

			// Display player's final score
			cout << "\n\tYour final score is: " << points << endl;

			// See if the player got the highscore
			readHighscore(points, playerName, highScoreName, highScore);

			// Replay the game if the player wants to
			Restart(keepPlaying, points, menuChoice);
		}

		// Quit Game
		else if (menuChoice == 3) {
			cout << setw(58) << endl << "\tThanks for playing!" << endl << endl;
		}
		else
			cout << setw(82) <<"Error ... Invalid choice ... Try again ..." << endl;
	} while (menuChoice != 3);

	return 0;
}



/*
	void menu()

	Display main menu

	Return Value: None
*/
void menu() {
	cout << "\n" << setw(70) << "Welcome to RPG Adventures!" << endl
		<< "\n" << setw(74) << "Select from the following options:" << endl
		<< setw(63) << "1) See Rules" << endl
		<< setw(63) << "2) Play Game" << endl
		<< setw(58) << "3) Quit" << endl
		<< setw(61) << endl << "What do you choose?: ";

	return;
}

/*
	void rules()

	Displays the rules of the game

	Return Value: None
*/
void rules() {

	cout << endl << endl << setw(59) << "------------------------------------------------------------------------------------------------------------------------"
		<< setw(59) << "RULES" << endl
		<< setw(59) << "------------------------------------------------------------------------------------------------------------------------" << endl
		<< setw(77) << "First, you will pick your character: " << endl
		<< setw(59) << "1) Human" << endl
		<< setw(58) << "2) Ogre" << endl
		<< setw(57) << "3) Elf" << endl << endl;
	cout << setw(79) << "Next you will pick from three weapons: " << endl
		<< setw(59) << "\t1) Flame Thrower" << endl
		<< setw(59) << "\t2) Bow and Arrow" << endl
		<< setw(59) << "\t3) Magic Potion" << endl << endl;
	cout << setw(88) << "If you pick Flame Thrower or Bow and Arrow, then you will"
		<< setw(81) << endl << " be taken to a practice session to test your skills"
		<< setw(86) << endl << " on the battlefield, and you will obtain points based on"
		<< " how well you did." << endl << endl;
	cout << setw(70) << "If you pick Magic Potion, then you will"
		<< setw(58) << endl << " attempt to create a potion."
		<< setw(93) << endl << " You will gain or lose points based on how successful you were." << endl << endl;

	return;
}

/*
	int characterSelect(int raceChoice, int points)

	Prompts user to select their character, then adds appropriate
	points to the player's score

	Return Value: Points after choosing character
*/
int characterSelect(int raceChoice, int points) {
	do {
		cout << "\n\tCHARACTER SELECTION" << endl
			<< "\t1) Human" << endl
			<< "\t2) Ogre" << endl
			<< "\t3) Elf" << endl
			<< "\tWhat do you choose?: ";
		cin >> raceChoice;

		// Assign points for Human
		if (raceChoice == 1) {
			points += 100;
		}

		// Assign points for Ogre
		else if (raceChoice == 2) {
			points += 200;
		}

		// Assign points for Elf
		else if (raceChoice == 3) {
			points += 300;
		}

		else
			cout << "\n\tError ... Invalid choice ... Try again ..." << endl << endl;
	} while (raceChoice != 1 && raceChoice != 2 && raceChoice != 3);

	return points;
}

/*
	int Weapon(int weaponChoice, int attack, int random, int points, int sessionChoice)

	Prompts user to choose their weapon and creates the gameplay for that weapon

	Return Value: Points after using chosen weapon
*/
int Weapon(int weaponChoice, int attack, int random, int points, int sessionChoice) {
	do {
		cout << "\n\tCHOOSE YOUR WEAPON" << endl
			<< "\t1) Flame Thrower" << endl
			<< "\t2) Bow and Arrow" << endl
			<< "\t3) Magic Potion" << endl
			<< "\tWhat do you choose?: ";
		cin >> weaponChoice;

		// Flame Thrower Practice Session
		if (weaponChoice == 1) {
			cout << "\n\tYOU HAVE ENTERED THE BLASTED LANDS" << endl;

			do {
				cout << "\tPRESS 1 TO EQUIP YOUR FLAMETHROWER: ";
				cin >> attack;

				if (attack != 1)
					cout << "\n\tInvalid input... Try again..." << endl << endl;
			} while (attack != 1);

			do {
				random = rand() % 4 + 1;

				cout << "\n\tYou aim your flamethrower..." << endl;

				if (random == 1) {
					cout << "\tYou burned the Infected Snail to a crisp!" << endl;
					points += 100;
				}
				else if (random == 2) {
					cout << "\tYou burned the Skeletal Archer to a crisp!" << endl;
					points += 200;
				}
				else if (random == 3) {
					cout << "\tYou burned the Vampire to a crisp!" << endl;
					points += 300;
				}
				else if (random == 4) {
					cout << "\tYou missed every target..." << endl;
					points += 0;
				}

				do {
					cout << "\n\tPress 1 to Attack again" << endl
						<< "\tPress 2 to End your session" << endl
						<< "\tWhat do you choose?: ";
					cin >> sessionChoice;

					if (sessionChoice != 1 && sessionChoice != 2)
						cout << "\n\tError... Invalid input... Try again..." << endl;
				} while (sessionChoice != 1 && sessionChoice != 2);

			} while (sessionChoice == 1 && sessionChoice != 2);
		}

		// Bow and Arrow Practice Session
		else if (weaponChoice == 2) {
			cout << "\n\tYOU HAVE ENTERED THE ARCHER FOREST..." << endl;

			do {
				cout << "\tPRESS 1 TO EQUIP BOW & ARROW(S): ";
				cin >> attack;

				if (attack != 1)
					cout << "\n\tInvalid input... Try again..." << endl << endl;
			} while (attack != 1);

			do {
				random = rand() % 4 + 1;

				cout << "\n\tYou aim your bow..." << endl;

				if (random == 1) {
					cout << "\tYou impaled the Infected Snail!" << endl;
					points += 100;
				}
				else if (random == 2) {
					cout << "\tYou impaled the Skeletal Archer!" << endl;
					points += 200;
				}
				else if (random == 3) {
					cout << "\tYou impaled the Vampire!" << endl;
					points += 300;
				}
				else if (random == 4) {
					cout << "\tYou missed every target..." << endl;
					points += 0;
				}

				do {
					cout << "\n\tPress 1 to Attack again" << endl
						<< "\tPress 2 to End your session" << endl
						<< "\tWhat do you choose?: ";
					cin >> sessionChoice;

					if (sessionChoice != 1 && sessionChoice != 2)
						cout << "\n\tError... Invalid input... Try again..." << endl;
				} while (sessionChoice != 1 && sessionChoice != 2);

			} while (sessionChoice == 1 && sessionChoice != 2);
		}

		// Try to create a potion
		else if (weaponChoice == 3) {
			cout << "\n\tYOU ENTER THE CRAFTING TAVERN" << endl;

			do {
				cout << "\tPRESS 1 TO START CRAFTING POTIONS: ";
				cin >> attack;

				if (attack != 1)
					cout << "\n\tInvalid input... Try again..." << endl << endl;
			} while (attack != 1);

			do {
				random = rand() % 2;

				cout << "\n\tYou begin mixing magical ingredients..." << endl;

				if (random == 1) {
					cout << "\n\tYou made the potion successfully!" << endl;
					points += 200;

					do {
						cout << "\n\tPress 1 to Craft again" << endl
							<< "\tPress 2 to End your session" << endl
							<< "\tWhat do you choose?: ";
						cin >> sessionChoice;

						if (sessionChoice != 1 && sessionChoice != 2)
							cout << "\tError... Invalid input... Try again..." << endl;
					} while (sessionChoice != 1 && sessionChoice != 2);
				}
				else {
					cout << "\n\tYou destroyed the Tavern..." << endl;
					points -= 100;

					do {
						cout << "\n\tPress 1 to Craft at another Tavern" << endl
							<< "\tPress 2 to End your session" << endl
							<< "\tWhat do you choose?: ";
						cin >> sessionChoice;

						if (sessionChoice != 1 && sessionChoice != 2)
							cout << "\n\tError... Invalid input... Try again..." << endl;
					} while (sessionChoice != 1 && sessionChoice != 2);
				}

			} while (sessionChoice == 1 && sessionChoice != 2);
		}

		else
			cout << "\n\tError ... Invalid choice ... Try again ..." << endl;

	} while (weaponChoice != 1 && weaponChoice != 2 && weaponChoice != 3);

	return points;
}

/*
	void Restart(char keepPlaying, int& points, int& menuChoice)

	Resets player's points to zero if they choose to restart the game.
	Otherwise, the game ends.

	Return Value: None
*/
void Restart(char keepPlaying, int& points, int& menuChoice) {
	do {
		cout << "\n\tWould you like to restart your adventure?" << endl
			<< "\t(Type Y for Yes or N for No): ";
		cin >> keepPlaying;

		if (keepPlaying == 'Y' || keepPlaying == 'y') {
			points = 0;
			system("cls"); // Clears the entire terminal output for the next game session
		}
		if (keepPlaying == 'N' || keepPlaying == 'n') {
			menuChoice = 3;
			cout << "\n\tThanks for playing!" << endl << endl;
		}
		else if (keepPlaying != 'Y' && keepPlaying != 'y' && keepPlaying != 'N' && keepPlaying != 'n')
			cout << "\n\tError ... Invalid choice ... Try again ..." << endl;
	} while (keepPlaying != 'Y' && keepPlaying != 'y' && keepPlaying != 'N' && keepPlaying != 'n');

	return;
}

/*
	void saveHighscore(string& name, int& highscore)

	Writes player's name and highscore to highscore.txt

	Return Value: None
*/
void saveHighscore(string& name, int& highscore) {
	fstream hFile;

	hFile.open("highscore.txt", ios::out);

	if (hFile) {
		cout << "\n\tPlease enter your name: ";

		cin.ignore();
		getline(cin, name);

		// Write to file
		hFile << name << endl << highscore;
	}
	else {
		cout << "Error ... Could not create/modify highscore.txt" << endl;
	}

	// Close file
	hFile.close();

	return;
}

/*
	void readHighscore(int highscore, string name, string& currentName, int& currentScore)

	Reads in score from highscore.txt, checks to see if player's score is higher than score
	in file, then replaces file score with current player's score. If player's score is higher, then
	the player's score will replace the score in the file and the player will be prompted for their name.
	If player's score is not higher, then a message will be displayed saying "You don't have the highscore :(".

	Return Value: None
*/
void readHighscore(int highscore, string name, string& currentName, int& currentScore) {
	fstream  hFile;
	if (hFile) {
		hFile.open("highscore.txt", ios::in);

		cout << "\n\tChecking Score....\n";

		if (!hFile) {
			cout << "\n\tNo file available... Creating file..." << endl;
			saveHighscore(name, highscore);
			cout << "\n-----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t" << name << ", your highscore is: " << highscore;
			cout << "\n\tSuccessfully saved your highscore";
			cout << "\n-----------------------------------------------------------------------------------------------------------------------" << endl;
		}
		else if (hFile)
			while (hFile >> currentName) {

				getline(hFile, currentName);

				hFile >> currentScore;

				if (currentScore <= highscore) {
					cout << "\n\tYou have the new highscore!" << endl;
					saveHighscore(name, highscore);
					cout << "\n------------------------------------------------------------------------------------------------------------------------";
					cout << "\n\tThe highest scoring player is " << name << " with " << highscore << " points." << endl;
					cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				}
				else
					cout << "\n\tYou don't have the highscore :(" << endl << endl;
			}
	}

	// Close file
	hFile.close();

	return;
}