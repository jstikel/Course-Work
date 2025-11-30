//Josh Stikeleather
//2/2/2025
//Project-1 Dice Game
//This is the dice game! Roll a dice and guess whether the number you rolled is higher or lower than the acutal price of a car, get lucky enough and you could win!
//All of this work is my own, I have not collaborated with anyone or AI to make this.
//Got info from the textbook, geeksforgeeks, and progamiz. I used Chat GPT/DeepSeek for errors.

//Initialzing all the required headers
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <array>
using namespace std;

//Initalizing all the prototypes
void playDiceGame(void);  //Runs the dicegame
void printLogo();  //Prints the dicegame logo and welcomes the user to the game
int rollDie(int, int);  //Returns a random number between 1-6, to simulate 'Rolling' a die
void printRules(string);  //Gets the name of the car that the user inputs, then gives the rules
int getPrice(int, int);  //This returns a random number between 20000 and 30000 that will be the price of the car, also validates the input numbers
void printCar(int, string);  //This prints a picture of the car, along with the year and model, which is chosen at random
void printBoard(int[], int[], int, bool); //Prints a picture of the board depending on given info
string getCar(void);  //This returns our randomly selected car from our list of GTA cars.
int roll_and_print_dice(int); //Prints which digit the game is on, then rolls the dice and prints the result of the dice, returns the value.
int compare_roll_price(int, char); //Compares the roll and the actual value at that spot and returns the results as either -1, 0, +1. 0 Indicates the roll was identical to the actual


int main(){

   unsigned seed; //This sets up a random and different seed every time the user plays.
   seed = time(0);
   srand(seed);

   bool playing = true;

   while (playing == true){
      playDiceGame(); //This runs the game as many times as the player wants to play
      cout<<"Would you like to play again (y/n): ";
      char y_or_n;
      cin>> y_or_n;
      y_or_n = toupper(y_or_n);
      if (y_or_n == 'Y'){
         playing = true;
      }
      else{
         playing = false;
      }
   }
   cout<<"Ending Dice Game..."<<endl;

return 0;
}

void playDiceGame(void){

   printLogo();

   string car_name = "";
   car_name = getCar();

   printRules(car_name);

   int rolls[5] = {0, 0, 0, 0, 0}; //Initalizaing all variables/arrays
   int guesses[5] = {0, 0, 0, 0, 0};
   bool final_stage = false;
   int current_price = getPrice(20000,30000); //Setting random price
   string str_price = to_string(current_price); //This is to compare the value of the rolled number and the actual number

   rolls[0] = 2;
   cout<<endl<<endl;
   cout<<"The first digit of the car is a 2"<<endl<<endl;

   printBoard(rolls, guesses, current_price, final_stage); //Prints the empty board with only a 2 showing in the first slot

   for (int i = 1; i < 5; i++){ //This is the main gameplay loop, it runs through all 4 rounds, prompting with higher or lower. All functions explained in prototypes
      rolls[i] = roll_and_print_dice(i + 1);
      printBoard(rolls, guesses, current_price, final_stage);
      guesses[i] = compare_roll_price(rolls[i], str_price.at(i));
   }

   final_stage = true; //This triggers the final stage of the game
   cout<<"------------ FINAL RESULT------------"<<endl<<endl;
   printBoard(rolls, guesses, current_price, final_stage);

}

void printLogo(){ //This prints out the dice game logo at the start of the game
cout << "  +-----+     +-----+     +-----+     +-----+"<< endl;
cout << " /     /|    /     /|    /     /|    /     /|"<<endl;
cout << "/     / |   /     / |   /     / |   /     / |"<<endl;
cout << "+-----+  |  +-----+  |  +-----+  |  +-----+  |"<<endl;
cout << "|  D  |  |  |  I  |  |  |  C  |  |  |  E  |  |"<<endl;
cout << "|     | /   |     | /   |     | /   |     | /"<<endl;
cout << "|  G  |/    |  A  |/    |  M  |/    |  E  |/"<<endl;
cout << "+-----+     +-----+     +-----+     +-----+"<<endl;
}

void printCar( int year = 2024, string car_name = ""){ //Prints out the car design and name/year of car won
cout << "     ______" <<endl;
cout << "    /|_||_\\`.__" <<endl;
cout << "   (   _    _ _\\"<<endl;
cout << "   =`-(_)--(_)-'"<<endl;
cout << "A brand new "<<year<<" " <<car_name<< "!!!"<<endl<<endl;
}

void printRules(string car_name){ //Simply states the rules of the game
cout << "Welcome to CPSC 1070 Dice Game!"<<endl<<endl;
cout << "You have a chance to win a" <<endl;
printCar(2024, car_name);
cout << "Here are the rules:\n";
cout << "  1. We will give you the first digit of the price of the car." << endl;
cout << "  2. The remaining digits are each a number between 1 and 6." << endl;
cout << "  3. For each digit, you will virtually roll a die. If the number matches the digit"<< endl;
cout << "     you get that number. Otherwise, you need to predict whether the actual digit" << endl;
cout << "     is higher or lower than the value you rolled." << endl;
cout << "  4. If you roll all the numbers and/or guess higher or lower correctly, you win!" << endl;
}

string getCar(void){ //This function simply returns a random car from a predetermined selection of cars.
   vector<string> cars{"Sabre Turbo", "Redwood Guantlet", "Buffalo S", "Buccaneer", "Pigalle", "Tornado", "Emperor", "Regina", "Radius",
       "Tailgater", "Panto", "Blista", "Burrito", "Rebel", "Rancher XL", "Prarie", "Exemplar", "Felon GT", "Windsor", "Oracle XS"};  
int random = rand() % 20;
return cars[random];
}

int rollDie(int low, int high){ //This returns a random number between a high and low value, prints an error if there is an incorrect input	
   if (low >= high){
      cout<<"Error incorrect order"<<endl;
   return 0;
   }
   else if (high <=0 || low <= 0){
      cout<<"Error: Negative number"<<endl;
   return 0;
   }
   else{
      int random = rand() % (high - low + 1) + low;
      return random;
   }
}

int getPrice(int low, int high){ //Works incredibly similarly to the rollDie function.
   if (high <=0 || low <= 0){
      cout<<"Error: Negative number"<<endl;
   return 0;
   }
   if (low >= high){
      cout<<"Error incorrect order"<<endl;
   return 0;
   }
   string price = "2";  //Insures that our first value is a 2

   for(int i = 0; i < 4; i++){ //This loop runs to insure that all following values are between 1 and 6
      int num = rand() % 6 + 1;
      price += to_string(num);
   }
   int num_price = stoi(price); //Converts our string of numbers into an int

   return num_price;
}

void printBoard(int rolls[], int guesses[], int current_price, bool final_stage){
   string str_price = to_string(current_price);
   if (final_stage){ //This is the for loop for when you are at the final stage.
      cout<<"           ";
      for (int i = 0; i < 4; i++){ //This prints the numbers only if they are above the rolled value in that same spot.
         if (str_price.at(i+1) - '0' > rolls[i+1]){
            cout<<str_price.at(i+1);
         }
         else{
            cout<<" ";
         }
         if (i < 3){
            cout<<"    ";
         }
      }
      cout<<endl;
   }
   else{
      cout<<"           ?    ?    ?    ?"<<endl; //If it is not the final stage the output will always be this
   }

   cout<<"     _";
   for (int i = 0; i < 5; i++){ //This for loop is for the top layer of the board
      if (guesses[i] != 0 && guesses[i] == 1){
         cout<<"|";
      }   
      else{
         cout<<' ';
      }
      if (i < 4){
         cout<<"_  _";
      }
      else{
         cout<<"_";
      }
   }
   cout<<endl;
   cout<<" $  | "; //This for loop runs to display the dice rolls on the board
   for (int i = 0; i < 5; i++){
      if (rolls[i] != 0){
         cout<<rolls[i];
      }
      else{
         cout<<" ";
      }
      if (i < 4){
         cout<<" || ";
      }
      else{
         cout<<" |";
      }
   }

   cout<<endl;
   cout<<"     -";
   for (int i = 0; i < 5; i++){ //This for loop is for the bottom layer of the board
      if (guesses[i] != 0 && guesses[i] == -1){
         cout<<"|";
      }
      else{
         cout<<' ';
      }
      if (i < 4){
         cout<<"-  -";
      }
      else{
         cout<<"-";
      }
   }
   cout<<endl;
   if (final_stage){ //This only prints out the correct value if it is equal or below the rolled value
      cout<<"           ";
      for (int i = 0; i < 4; i++){
         if (str_price.at(i+1) - '0' <= rolls[i+1]){
            cout<<str_price.at(i+1);
         }
         else{
            cout<<" ";
         }
         if (i < 3){
            cout<<"    ";
         }
      }
      cout<<endl;
   }
   else{
   cout<<"           ?    ?    ?    ?"<<endl; //Whenever it is not the final stage outputs question marks.
   }

   if (final_stage){ //Checks to see if we're on the final stage of the game, if so, checks to see if the player won
      int win_count = 0;
      for (int i = 1; i < 5; i++){
         char actual_digit = str_price.at(i); //These two values are going to be used to compare our numbers.
         int rolled_digit = rolls[i];
   
         if (guesses[i] == 0){ //If the guess was correct
            if (rolled_digit == (actual_digit - '0')){
               win_count += 1;
            }
         }
         else if (guesses[i] == 1){ //If the guess was higher
            if (actual_digit > rolled_digit + '0'){
               win_count += 1;
            }
         }
         else if (guesses[i] == -1){ //If the guess was lower
            if (actual_digit < rolled_digit + '0'){
               win_count += 1;
            }
         }
      }
   
      if (win_count == 4){
         cout<<"Congratulations, you won a brand new car!"<<endl<<endl<<endl;
      }
      else{
         cout<<"Sorry, you did not win! Better luck next time!"<<endl<<endl<<endl;
      }
   }
}

int roll_and_print_dice(int digit){ //This function is simply used to clean up the playDiceGame function. 
   cout<<"------------ Digit # "<<digit<<"------------"<<endl<<endl;
   int roll = rollDie(1,6);
   cout<<"You rolled a "<<roll<<" for the next digit in the price of the car."<<endl<<endl;
   return roll;
}

int compare_roll_price(int current_roll, char price_point){
   if (current_roll == (price_point - '0')){ //Compares the roll to the original car value.
      cout<<"**Ding ding!** "<<current_roll<<" is the next digit of the car!"<<endl;
      return 0;
   }
   else if (current_roll == 1){ //If the roll is 1 and that digit is also not 1, the system will automatically return +1
      cout<<"The next number in the price of the car is not 1, so we know that the digit has to be higher!"<<endl;
      return 1;
   } 
   else if (current_roll == 6){ //If the roll is 6 and that digit is also not 6, the system will automatically return -1
      cout<<"The next number in the price of the car is not 6, so we know that the digit has to be lower!"<<endl;
      return -1;
   }
   else { //Runs if the roll is not a 1 or a 6 and is still not the same value as the actual digit.
      char h_or_l;
      cout << "Unfortunately, " << current_roll << " is not the next digit of the car." << endl;
      cout << "Do you think the next digit is higher or lower? (press h or l): ";
      while (true) { // Runs until the input is valid
         cin >> h_or_l;
         h_or_l = toupper(h_or_l); // Converts the users input to uppercase
         if (h_or_l == 'H') {
               return 1;
         } 
         else if (h_or_l == 'L') {
               return -1;
         } 
         else {
            cout << "You did not enter a 'h' or 'l'. Please retry: ";
         }
      }
   }
}  
