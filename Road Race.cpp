#include <iostream>     // Input Output
#include <conio.h>      // Keyboard Interrupt
#include <windows.h>    // Delay
#include <vector>       // Dynamic Array
#include <fstream>      // File Operation
#include <string>       // String Manipulation
#include <algorithm>    // Sorting

using namespace std;

// UI Purposes
void fullscreen();
void decoration();
void spaces(string str);
// Main Program
void intro();
void menu();
void leaderboard();
void input_leaderboard(string& name, int& score);
void credits();
void instruction();
void drawBorder();
void genEnemy();
void drawEnemy();
void eraseEnemy();
void resetEnemy();
void drawcar();
void erasecar();
int collision();
void gameover();
void updateScore();
void play();


// To Adjust Height and Width Output Position
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

// To center output (adding spaces before the output)
void spaces(int len = 39) {
    string str = "" ;
    int length = len - (str.length() / 4);
    for (int i = 0; i < length; i++) {
        cout << " ";
    }
}

// Decoration purpose (adding '=' multiple times)
void decoration() {
    spaces();
    for (int i = 0; i < 50; i++) {
        cout << "=";
    }
    cout << endl;
}

// To make the terminal become fullscreen
void fullscreen() {
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 25;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

const int e = 4;
int enemyY[e], enemyX[e], enemyFlag[e];
char car[4][4] = { ' ','_','_',' ', 
			       '[','-','-',']', 
			       ' ','0','0',' ',
			        '[','-','-',']' }; 
int carPos, score = 0; 

void drawBorder(){  
	for(int i=1; i<36; i++){
		for(int j=1; j<10; j++){
			gotoxy(36+j,i); cout<<"|";
			gotoxy(75+j,i); cout<<"|";
		}
		for(int j=1; j<3; j++){
			gotoxy(53+j,i); cout <<"|";
			gotoxy(65+j,i); cout <<"|";
		}
	} 
	for(int i=1; i<36; i++){
        gotoxy(30,i); cout<<"|";
		gotoxy(94,i); cout<<"|";
	}
}
void genEnemy(int ind){
	int random = rand()%3+1;
	if(random == 1) enemyX[ind] = 48;
	else if(random == 2)enemyX[ind] = 59;
	else enemyX[ind] = 70;  
}
void drawEnemy(int ind){
	if(enemyFlag[ind] == true){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"[--]";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" XX "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"[--]"; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" XX ";  
	} 
}
void eraseEnemy(int ind){
	if(enemyFlag[ind] == true){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+29); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+29); cout<<" ";
		}
	}
}
 
int collision(){
    for(int i = 0; i < e; i++)
    {
    	if(enemyY[i]+4 >= 29){
		if(enemyX[i] + 4 - carPos >= 0 && enemyX[i] + 4 - carPos < 9) return 1;
	}
    }
	return 0;
} 

void gameover(){
	system("cls");
	gotoxy(60,9); cout << "GAME OVER" << endl;
    gotoxy(0,10); decoration();
    gotoxy(40,11); cout << "SCORE\t\t: " << score << endl;
    gotoxy(0,15); decoration();
    string name;
    gotoxy(40,12); 
    cout << "INPUT YOUR NAME : ";
    cin >> name;
    
    gotoxy(40,14); cout << "Press any key to go back to menu" << endl;
	getch();

    ofstream outfile;
    outfile.open("leaderboard.txt", std::ofstream::ate| std::ofstream::app);
    outfile << name << " " << score;
    outfile.close();
}

void updateScore(){
	gotoxy(86, 15); cout << "Score: " << endl;
    gotoxy(86, 16); cout << score << endl;
}

void play(){
	carPos = 59;
	score = 0;
	enemyFlag[0] = 1;
    enemyY[0] = 1;
    for(int i = 1; i < e; i++){ 
        enemyFlag[i] = 0;
        enemyY[i] = 1;
    }
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
    for(int i = 0; i < e; i++){ 
        genEnemy(i);
    }
    gotoxy(16,15); cout << "PRESS ANY KEY";
    gotoxy(16,16); cout << "     TO START";
	_getch();
    gotoxy(16,15); cout << "             ";
    gotoxy(16,16); cout << "             ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if(ch=='a' || ch=='A') if(carPos > 52) carPos -= 11;
			if(ch=='d' || ch=='D') if(carPos < 68) carPos += 11;
			if(ch==27) break;
		} 
		drawCar();
        for(int i = 0; i < e; i++){ 
            drawEnemy(i);
        } 
		if(collision() == 1){
			gameover();
			return;
		} 
		Sleep(50);
		eraseCar(); 
        for(int i = 0; i < e; i++){ 
            eraseEnemy(i);
        } 
		
        for(int i = 0; i < e-1; i++){
            if(enemyY[i] == 12)
                if(enemyFlag[i+1] == 0) enemyFlag[i+1] = 1;
        }
		for(int i = 0; i < e; i++){
            if(enemyFlag[i] == 1) enemyY[i] += 1;
        }
        for(int i = 0; i < e; i++){
            if(enemyY[i] > 31){
			resetEnemy(i);
			score++;
			updateScore();
            }
        }
	}
}

// Instruction before playing into the game
void instruction(){
    system("cls");
    char ch;
    decoration();
    spaces(58);
    cout << "HOW TO PLAY" << endl;
    decoration();

    spaces(); cout << "-Avoid obstacles and Get the Highest Score" << endl;
    spaces(); cout << "-Press 'D' to go right" << endl;
    spaces(); cout << "-Press 'A' to go left" << endl;
    cout << endl;

    decoration();
    spaces(59);
    cout << "HAVE FUN!";
    ch = _getch();
}

//Search Member Information
struct Carisearch{
    string fullname;
    string firstname;
    string role;
    string nim;
    string major;
};

Carisearch role[6] = {{"Ahmad Mahat Madani","Mahat", "Programming","22/504920/PA/21727","Chemistry"},
                      {"Lutfi Wibowo", "Lutfi", "Documentary","22/504413/PA/21697","Elins"}, 
                      {"Maria Clareta Febriani","Reta", "Project Manager","22/505983/PA/21780","Computer Science"},
                      {"M. Hariish Hafiiz","Hariish", "Designer", "22/504651/PA/21712","Computer Science"},
                      {"Nicolas Dwi Hardjoleksono","Nicolas", "Programming","22/493899/PA/21225","Computer Science"},
                      {"Shaffa Dalih Zulihasmi","Shaffa", "Analyst","22/499499/PA/21540","Chemistry"}};
void Srole(){
    spaces(39); cout << "Insert A Nickname To Find Information" << endl;
    spaces(39); cout << "Name: ";
    string key;
    cin >> key;
    bool found = true;
    for(int i = 0; i < 6; i++){
        if(role[i].firstname == key){
            found = true;
            spaces(42); cout << "Name : " << role[i].fullname << endl;
            spaces(42); cout << "Role : " << role[i].role << endl;
            spaces(42); cout << "NIM  : " << role[i].nim << endl;
            spaces(42); cout << "Major: " << role[i].major << endl;
            break;
        }
        else found = false;
    }
    if(!found){
        spaces(42); cout << "Data is not found" << endl;
    }
    decoration(); spaces(42); cout << "PRESS ANY KEY TO RETURN TO MAIN MENU" << endl;
    _getch();
}

//Credits showing one by one
void credits () {
    string arr[7][100] = {
        {"---====ROAD RACE====---"},
        {"Ahmad Mahat Madani"}, {"Lutfi Wibowo"},
        {"Maria Clareta"}, {"Muhammad Hariish"},
        {"Nicolas Hardjoleksono"}, {"Shaffa Dalih"},
    };
    system("cls");
    decoration();
    for(int j=0;j<7;j++){
        j == 0 ? spaces(52) : spaces(42);
        for (int i= 0; i < 50; i++) {
            cout<< arr[j][i];
        }
        cout << endl;
        Sleep(100);
    }
    decoration();
    char Cchoice = _getch();
    if(Cchoice == '.') Srole();
}

//Intro
void intro() {
    string welcome = "WELCOME TO ROAD RACE";
    system("cls");
    gotoxy(0,8); decoration();        
    spaces(54); cout << welcome << endl;
    decoration();
    cout << endl;
    spaces(49);
    cout << "PRESS ANY KEY TO ENTER THE GAME" << endl;
    cout << endl;
    decoration();
    _getch();
    menu();
    Sleep(1000);
}

// Leaderboard mechanism
void leaderboard() {
    struct player {
        string name;
        int score;
        static bool comp(player& a, player& b) {
            return a.score > b.score;
        };
    };
    player* p;
    p = new player[10];

    ifstream infile;
    infile.open("leaderboard.txt");
    decoration();
    spaces(39); cout << "LEADERBOARD" << endl;
    decoration();
    // Check leaderboard.txt exist or not
    if (infile.fail()) {
        spaces(45); cout << "No scores are saved...yet." << endl;
        spaces(45); cout << "Please play the game first" << endl;
    }else{
        int i = 0;
        int count = 0;

        // Insert name and score to leaderboard.txt
        while (!infile.eof()) {
            infile >> p[i].name >> p[i].score;
            i++;
            count++;
        }
        infile.close();

        // Sorting descending
        sort(p, p + count, player::comp);

        // Showing the leaderboard
        spaces();
        cout << "NO.\tNAME\t\t\t\t  SCORE" << endl;
        decoration();
        for (int i = 0; i < count; i++) {
            spaces(); cout << i + 1 << ".\t" << p[i].name; 
            gotoxy(82,i+5); cout << p[i].score << endl;
        }
    }
}

// Main Menu
void menu() {
    string menu = "MAIN MENU";
    int distance = 30 - (menu.length() * 2);
    string str = "Thanks for playing, have a nice day!";
    string str2 = "PRESS ANY KEY TO RETURN TO MAIN MENU";
    int strLen = str.length();
    bool player;
    while (true) {
        system("cls"); gotoxy(0,8); decoration();
        gotoxy(42,9); cout << "MAIN MENU" << endl;
        decoration(); gotoxy(39,11); cout << "1. Start Game" << endl;
        gotoxy(39,12); cout << "2. Instructions" << endl;
        gotoxy(39,13); cout << "3. Leaderboard" << endl;
        gotoxy(71,11); cout << "4. Credits" << endl;
        gotoxy(71,12); cout << "5. Exit" << endl;
        gotoxy(0,14); decoration();
        char choice = _getch();
        if(choice == '1') play();
        else if(choice == '2') instruction();
        else if(choice == '3') {
            system("cls");
            leaderboard(); decoration(); spaces(45); cout << str2; 
            _getch();
        }
        else if(choice == '4') credits();
        else if(choice == '5') {
            spaces(45); cout << str << endl; decoration();
            while(true) {
                Sleep(500);
                if(_kbhit()) break;
            }
            break;
        }
        else continue;
    }
}

int main(int argc, char const* argv[])
{
    fullscreen();
    intro();
    return 0;
}