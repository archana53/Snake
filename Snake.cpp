#include<iostream>
#include<windows.h>
#include<conio.h>
#include <bits/stdc++.h>


/*  SNAKE GAME IMPLEMENTATION */

using namespace std;

int ii,jj,kk,iii;

void gotoxy(int x, int y) //goes to x,y location in the console
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Pixel{
	
	public:
	int x,y;
	
	Pixel(){
		;
	}
	void init(int x1,int y1){
		x = x1;
		y = y1;
	}	
	void show(int head){
		
		if(head == 0){
			gotoxy(x,y);
			std::cout << "O";
		}
		else if(head == 1){
			gotoxy(x,y);
			std::cout << '\xFE';
		}
		else if (head == 2){
			gotoxy(x,y);
			std::cout << '\xB2';
		}
		else {
			SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), 5);
			gotoxy(x,y);
			std :: cout << '\xC12';
		}
	}
	void hide(){
		gotoxy(x,y);
		std::cout << " ";
	}
	bool operator ==(Pixel p1);
};
bool Pixel :: operator ==(Pixel p1){
	if(x == p1.x && y == p1.y ){
		return true;
	}
	return false;
}
class Snake : public Pixel {
	
	int Score;
	int Length;	
	
	Pixel* ptr = new Pixel;
	
	std::vector <Pixel> Body;

	public :
	
	char CurrDir = (char) 77;
	int minutes=0 , seconds = 0, hours=0 ;
	long long int Time;
	
	Snake(int n) : Pixel() {		
		Score = 0;
		Length = n;
		for(ii = 0; ii < n;ii++){
			Body.push_back(*ptr);
			Body[ii].init(50-ii,10);
		}		
	}	
	//game controls
	void move(char);
	bool Eat(Pixel);
	void ShowSnake();
	bool GameOver();
	void Extend();
	void operator++();	
	
	//Saving options
	void AddScore(int);
	void AddLength(int);
	void AddToBody(Pixel*);
	int GetScore();
	int GetLength();
	vector <Pixel> GetBody();

	//Printing score and timer during game
	void PrintScore();	
	void PrintTimer(int );

};

void Snake::move(char dir ){
		CurrDir = dir;
		if(CurrDir == 72){
			Body[Body.size()-1].hide();
			for(jj = Body.size()-1; jj >0 ; jj--){
				Body[jj].x = Body[jj-1].x;
				Body[jj].y = Body[jj-1].y;
			}
			Body[0].y--;
			
			if(Body[0].y == 0){
				Body[0].y = 25;
			}
		}
		if(CurrDir == 75){
			Body[Body.size()-1].hide();
			for(jj = Body.size()-1; jj >0 ; jj--){
				Body[jj].x = Body[jj-1].x;
				Body[jj].y = Body[jj-1].y;
			}
			Body[0].x--;
			
			if(Body[0].x == 0){
				Body[0].x = 97;
			}
			
		}
		if(CurrDir == 80){
			Body[Body.size()-1].hide();
			for(jj = Body.size()-1; jj >0 ; jj--){
				Body[jj].x = Body[jj-1].x;
				Body[jj].y = Body[jj-1].y;
			}
			Body[0].y++;
			if(Body[0].y == 26){
				Body[0].y = 1;
			}
		}
		if(CurrDir== 77){
			Body[Body.size()-1].hide();
			for(jj = Body.size()-1; jj >0 ; jj--){
				Body[jj].x = Body[jj-1].x;
				Body[jj].y = Body[jj-1].y;
			}
			
			Body[0].x++;
			if(Body[0].x == 98){
				Body[0].x = 1;
			}
		}
	}
bool Snake::Eat(Pixel food){
		if(Body[0] == food){		
			(*this).Extend();
			return true;
		}
		return false;
	}
void Snake::ShowSnake(){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,2);
		Body[0].show(0);
		for(ii = 1;ii < Body.size();ii++){
			if((abs(Body[ii].x - Body[ii-1].x) == 1 && (ii < (Body.size()-1) && abs(Body[ii+1].y - Body[ii].y) == 1 )) || (abs(Body[ii].y - Body[ii-1].y) == 1 && (ii < (Body.size()-1) && abs(Body[ii+1].x - Body[ii].x) == 1 ))){
					Body[ii].show(1);				
			}
			else if (abs(Body[ii].x - Body[ii-1].x) == 1)
			Body[ii].show(1);
			else 
			Body[ii].show(2);
			
		}
	}	
bool Snake::GameOver(){
	for(ii =1;ii < Body.size() ; ii++){
		if(Body[0] == Body[ii])
			return true;
	}
	return false;
}
void Snake::AddToBody(Pixel *p1){
	Body.push_back(*p1);
}
void Snake::AddScore(int x){
	Score = x;
}
void Snake::AddLength(int y){
	Length = y;
}
void Snake::Extend(){
		Length++;
		++(*this);
		Length++;
		++(*this);
		Length++;
		++(*this);
		Score = Score + 5;
}
int Snake::GetLength(){
	return Length;
}
int Snake::GetScore(){
	return Score;
}
void Snake::PrintScore(){
		SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(40,28);
		std::cout << "Score :" << Score;
}
vector <Pixel> Snake::GetBody(){
		return Body;
	}
void Snake::PrintTimer(int speed){
			SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), 12);
			if(Time%(1000/(110-speed*20))== 0){
			seconds++;
			if(seconds == 60){
				seconds = 0;
				minutes++;
			}
			if(minutes == 60){
				minutes = 0;
				hours++;		
			}
		gotoxy(70,28);
		std :: cout << "Time : ";
		gotoxy(78,28);
		if(hours < 10)
		cout << 0<<hours << ":";
		else cout << hours <<":";
		gotoxy(81,28);
		if(minutes < 10)
		cout << 0<<minutes << ":";
		else cout << minutes <<":";
		gotoxy(84,28);
		if(seconds < 10)
		cout << 0<<seconds;
		else cout << seconds;
		
		}
	}
void Snake::operator ++(){
	
	Body.push_back(*ptr);
	Body[Body.size()-1].x = Body[Body.size()-2].x;
	Body[Body.size()-1].y = Body[Body.size()-2].y ;
	Length++;
	
 }

class Food : public Pixel{	
	
	public :
		
	Food() : Pixel(){
		;	
	}
	void Generate(){
		srand(time(0));
		x =  (rand() % 97) +1;
		y = (rand() %25) + 1;
	}
};
void ShowBorder(){
	
	SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), 12);
	
	gotoxy(0,0);
	std::cout << '\xC9'; //upper left
	for( ii = 0; ii < 98 ;ii++){ //top boundary
		std::cout << '\xCD';
	}
	std::cout << '\xBB'; //upper right
	
	for( ii = 0; ii < 25 ;ii++){ //right boundary
		gotoxy(99,ii+1);
		std::cout << '\xBA';
	}
	gotoxy(0,0);
	for(ii= 0; ii < 25;ii++){ //left boundary
		gotoxy(0,ii+1);
		std::cout << '\xBA';
	}
	gotoxy(0,26);
	std:: cout << '\xC8'; //lower left
	for( ii = 0; ii < 98 ;ii++){ //bottom boundary
		std::cout << '\xCD';
	}
	std::cout << '\xBC'; //lower right
}
class HighScores{
	
	//temporary storage
	vector < std::pair<int, string> > Table ;
	
	public:
	
	void AddHighScore(string username, int score){
		ofstream myfile;
		//adding highscore to highscores file
 		myfile.open ("HighScore.txt",std::fstream::app);
  			myfile << username << " " << score << endl;
	}
	void ShowHighScore(){
		//printing top 15 highscores
		ifstream myfile ("HighScore.txt",std::fstream::in);
  		if (myfile.is_open())
  		{
  			string line, token,token1;
    		while ( getline (myfile,line) )
    	
   	 		{
      		 	stringstream ss(line);   
      		 
   				 while(ss >> token){
   				 	int y;
   				 	ss >> token1;
   			 		sscanf(token1.c_str(),"%d",&y);
					Table.push_back(make_pair(y,token));				
    			}
			}
		}
		
		//sorting bottom most elements in Table
		std::sort(Table.begin(),Table.end());
		
		system("cls");
		ShowBorder();
		
		//printing format
		gotoxy(19,2);		
		cout << "S.No";
		gotoxy(46,2);
		cout << "Name";
		gotoxy(74,2);
		cout << "Score";
		//printing data		
		int size = Table.size();
		for( ii = 1 ; ii < min(16,size) ;ii++){
			gotoxy(19,3+ii);
			cout << ii ;
			gotoxy(21 + (56-(Table[Table.size()-ii].second).size())/2,3+ii);
			cout << Table[Table.size()-ii].second ;
			gotoxy(75,3+ii);
			cout << Table[Table.size()-ii].first << endl;
		}
	}
};

class Game{
	
	char Username[100];
	string filename; 
	int score;
	string sec,min,hr,day,mon,yr;
 	tm *ts;	 //timestamp
 	
 	public : 
 	void GetUser(string x){
 		//Obtaining username
 		for(ii = 0; ii < x.length();ii++){
 			Username[ii] = x[ii];
		 }
	}
	
	void GetTime(){
		//Getting time of creation
		 time_t now = time(0);
   		 ts = localtime(&now);
	}	
	
	void AddGame(FILE* fptr){	
	vector <string> Temporary;
	string line;	
	
	//copying data from Savedgames
	
	ifstream myfile ("Savedgames.txt");
  	if (myfile.is_open())  	{
    	while ( getline (myfile,line) ){
			Temporary.push_back(line);
    	}   	
    myfile.close();
	}	
		//Clearing data and SavedGames and writing at the beginning
		FILE* fwriteptr = fopen("Savedgames.txt","w"); 
		
		 fprintf(fptr,"%s %d %d %d %d %d %d\n",Username,ts->tm_sec,ts->tm_min,ts->tm_hour,ts->tm_mday,ts->tm_mon,ts->tm_year);	
		 
		 int len = Temporary.size();	
		 
		 //Copying 15 most recent games into SavedGames
		 for(ii = 0; ii < std::min(14,len);ii++){
		 	fprintf(fptr,"%s\n",Temporary[ii].c_str());
		 }
		 //Deleting the remaining data
		 for(ii = 14 ; ii < len ;ii++){
		 	for(iii = 0; iii < Temporary[ii].length();iii++){
		 		if(Temporary[ii][iii] = ' '){
		 			Temporary[ii].erase(Temporary[ii].begin()+iii);
				 }
			 }
			 Temporary[ii].append("txt");
			 cout << Temporary[ii];
			 remove(Temporary[ii].c_str());
		 }
		 Temporary.clear();
	}
	
	string GetFileName(){
		//returning filename of the game that is stored
		for(ii = 0; Username[ii]!= '\0';ii++){
			filename.push_back(Username[ii]);
		}
		filename.append(to_string(ts->tm_sec));
		filename.append(to_string(ts->tm_min));
		filename.append(to_string(ts->tm_hour));
		filename.append(to_string(ts->tm_mday));
		filename.append(to_string(ts->tm_mon));
		filename.append(to_string(ts->tm_year));
		return filename;
	}
};


void ShowScoreCard(int speed){
	
	SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), 12);
	
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 22;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
	gotoxy(0,27);
	for(ii = 0; ii < 2 ;ii++){
		gotoxy(0,27+ii);
		std::cout << '\xBA';
	} 
	gotoxy(0,29);
	std::cout << '\xC8';
	
	for(ii =0; ii < 98;ii++){
		std::cout << '\xCD';
	}
	gotoxy(99,29);
	std:: cout << '\xBC';
	for(ii = 0; ii < 2 ;ii++){
		gotoxy(99,27+ii);
		std::cout << '\xBA';
	}
	gotoxy(10, 28);		
	cout << "Level : " << speed ;
}
void WelcomeScreen(){ //We have to setup a 100x100 snake screen

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);  
	
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
	ShowBorder();
	
	SetConsoleTextAttribute ( hConsole, 14);
	gotoxy(43,2);
	std::cout << "Snake Game in OOPS";
	
	gotoxy(40,3);
	std::cout << "Course Project : CS2810";
	gotoxy(33,4);
	std::cout << "Indian Institute of Technology,Madras";
	
	SetConsoleTextAttribute(hConsole, 12);  
	
	gotoxy(1,6);
	for( ii = 0; ii < 98 ;ii++){ //top boundary
		std::cout << '\xCD';
	}
	
	gotoxy(1,6);
	for( ii = 0; ii < 98 ;ii++){ //top boundary
		std::cout << '\xCD';
	}
	SetConsoleTextAttribute ( hConsole, 2);
	gotoxy(35,7);
	std::cout << "           /^\\/^\\";
	gotoxy(35,8);
	std::cout << "         _|__|  O|";
	gotoxy(35,9);
	std::cout << "\\/     /~     \\_/ \\";
	gotoxy(35,10);
	std::cout << " \\____|__________/  \\";
	gotoxy(35,11);
	std::cout << "        \\_______      \\";
	gotoxy(35,12);
	std::cout << "                `\\     \\                 \\";
	gotoxy(35,13);
	std::cout <<"                  |     |                  \\";
	
	gotoxy(35,14);
	std::cout <<"                 /      /                    \\";
	gotoxy(35,15);
	std::cout <<"                /     /                       \\";
	gotoxy(35,16);
	std::cout <<"              /      /                         \\ \\";
	gotoxy(35,17);
	std::cout <<"             /     /                            \\  \\";
	gotoxy(35,18);
	std::cout <<"           /     /             _----_            \\   \\";
	gotoxy(35,19);
	std::cout <<"          /     /           _-~      ~-_         |   |";
	gotoxy(35,20);
	std::cout <<"         (      (        _-~    _--_    ~-_     _/   |";
	gotoxy(35,21);
	std::cout <<"          \\      ~-____-~    _-~    ~-_    ~-_-~    /";
	
	gotoxy(35,22);
	std::cout <<"            ~-_           _-~          ~-_       _-~";
	gotoxy(35,23);
	std::cout <<"               ~--______-~                ~-___-~";
		
	SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(5,14);
	std::cout << "Select Mode to proceed :";
	gotoxy(7,16);
	std::cout << "1 : New game";
	gotoxy(7,17);
	std::cout << "2 : Load game";
	gotoxy(7,18);
	std::cout << "3 : Highscores";
	gotoxy(7,19);
		std::cout << "4 : Instructions and Controls";
	gotoxy(7,20);
	std::cout << "5 : Choose Level";
	
}
void RulesAndControls(){
	ShowBorder();
	
	gotoxy(40,2);
	std::cout << "RULES AND CONTROLS";
	
	for( ii = 1; ii < 98 ;ii++){ //top boundary
		gotoxy(ii,4);
		std::cout << '\xCD';
	}
	
	gotoxy(10,7);
	std::cout << "GOAL : To consume as many fruits as possible before the snake collides with itself";
	
	gotoxy(20,10);
	std::cout << '\xB2';
	std::cout << "Use 'up', 'left', 'down','right' arrow keys to";
	gotoxy(21,11);
	cout << " navigate the snake up , right , down and left";
	
	gotoxy(20,14);
	std::cout << '\xB2';
	std::cout << "Press 'p' to pause the game";
	
	gotoxy(20,17);
	std::cout << '\xB2';
	std::cout << "Press 's' to save the game";
	
	gotoxy(20,20);
	std::cout << '\xB2';
	std::cout << "Press 'esc' to exit";
	
	gotoxy(0,26);
}
string LevelList(){
	
	string response;	
	ShowBorder();	
	gotoxy(45,2);
	std::cout << "LEVEL LIST";
	
	for( ii = 1; ii < 98 ;ii++){ //top boundary
		gotoxy(ii,4);
		std::cout << '\xCD';
	}		
	gotoxy(10,7);
	std::cout << "Choose the number corresponding to the level you want to play in ";
	
	gotoxy(20,10);
	std::cout << '\xB2';
	std::cout << "1 : Very Easy";
	
	gotoxy(20,13);
	std::cout << '\xB2';
	std::cout << "2 : Easy";
	
	gotoxy(20,16);
	std::cout << '\xB2';
	std::cout << "3 : Medium";
	
	gotoxy(20,19);
	std::cout << '\xB2';
	std::cout << "4 : Difficult";
	
	gotoxy(20,22);
	cout << "Your choice : ";
	cin >> response;
	gotoxy(0,26);
	return response;
}
char GameOverScreen(int score){
	
	system("cls");
	ShowBorder();
	
	//setting text size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
		
	gotoxy(45,10);
	std :: cout <<  "You Died!!!";
	gotoxy(43,11);
	std::cout << "Your Score : " << score ;
	gotoxy(37,13);
	std::cout << "Press 'n' to start new game";
	gotoxy(37,13);
	std::cout << "Press 'y' to add to High Scores";
	gotoxy(40,15);	
	std::cout << "Press 'esc' to exit";
	
	char retvalue = getch();
}
vector <string> PrintSavedGames(){
	
  std::string line,token,filename;
  
  vector <string> FileNames;
  
  //Printing the format
  
  		system("cls");
  
  		ShowBorder();
  		gotoxy(21,3);
  		cout << "S.No ";
  		
  		gotoxy(35,3);
  		cout << " Name ";
  		
  		gotoxy(55,3);
  		cout << " Time ";
  		
  		gotoxy(72,3);
  		cout << "Date ";
  		ii =1;
  
  ifstream myfile ("Savedgames.txt");
  	if (myfile.is_open())
  	{ 		
    	while ( getline (myfile,line) )
    	
   	 	{
   	 		if(ii == 16)
   	 		break;
   	 		//printing saved games
			filename.clear();
			
			//S.no
			gotoxy(23,4+ii);
   	 		cout << ii;
   	 		
   	 		int day,mon,yr;
   	 		int tracker = 0; //iterator
   	 		
      		 stringstream ss(line);   
      		 
   			 while(ss >> token) {
   			 	filename.append(token);
				if(tracker == 0){
					gotoxy((18 + (20-token.length()/2)),4+ii);
					cout << token;
				}
				if(tracker == 1){
					gotoxy(61,4+ii);
					int temp = stoi(token);
					if(temp < 10)
					cout << 0 << temp ;
					else
					cout << temp ;
				}
				if(tracker == 2){
					gotoxy(58,4+ii);
					int temp = stoi(token);
					if(temp < 10)
					cout << 0 << temp << ":";
					else
					cout << temp << ":";
				}
				if(tracker == 3){
					gotoxy(55,4+ii);
					int temp = stoi(token);
					if(temp < 10)
					cout << 0 << temp << ":";
					else
					cout << temp << ":";
				}
				if(tracker == 4){
					gotoxy(70,4+ii);
					day = stoi(token);
					if(day < 10)
					cout << 0 << day << "/";
					else
					cout << day << "/";
				}
				if(tracker == 5){
					mon = stoi(token);
					gotoxy(73,4+ii);
					if(mon+1 < 10)
					cout << 0 << mon+1 << "/";
					else
					cout << mon+1 << "/";
				}
				if(tracker == 6){
					yr = stoi(token);
					gotoxy(76,4+ii);
					if(yr-100 < 10)
					cout << 0 << yr-100;
					else
					cout << yr-100 ;
				}
				tracker++;				
    		}
    		//cout << gptr->GetFileName();
    		ii++;
    		FileNames.push_back(filename);
    	}    	
    myfile.close();
	}
	return FileNames;
}
string TakeUsername(){
	
	//taking valid input
	
	TakeUsername:
	string username1;
	system("cls");
	ShowBorder();
	gotoxy(15,15);
	cout << "NOTE : Username cannot have special characters or spaces in between";	
	gotoxy(37,12);
	cout << "Enter your name : ";	
	username1.clear();
	char n = getch();
		//checking if valid input
		while(n != '\r' && n != ' ' && ((n >= 97 && n <= 122) || (n >=48 && n <=57) || (n >= 65 && n <= 90) || n == 95 || n == 8 || n == 127) ){
		
			if(n != 8 && n != 127){
			std::cout << n;
			username1.push_back(n);
			n = getch();
			}
			while(n == 8 || n == 127){
				try{ //backspace or delete
					if(username1.length() == 0){
						throw 0;
					}
					gotoxy(55+ (username1.length()-1),12 );
					std::cout << " ";
					gotoxy(55 + (username1.length()-1),12);
					username1.erase(username1.end()-1);
					n=getch();
				}
				catch(int x){
					goto TakeUsername;
				}
			}	
		}
			if(username1.length() > 0  && username1.length() < 26 && (n == '\r' || n== ' ')){
				username1.push_back('\0');
				system("cls");
				return username1; //checking if valid username and throwing if it is
			}
			else{
				system("cls");
				ShowBorder();
				gotoxy(30,12);
				cout << "Invalid Name. Please Enter valid name";
				Sleep(1500);
				goto TakeUsername;
			}
		
}

Snake LoadGame(){
	
	SelectSavedGame:
		
	system("cls");
	//prints and returns the filenames of saved games
	vector <string> x = PrintSavedGames();
	//choosing game to laod
	gotoxy(30,24) ;
	cout << "Choose Game Number : ";
	char num[5];
	gets(num);
	int sel = stoi(num);
	string filename = x[sel-1];
	string token,line,token1;
	filename.append(".txt");
	Snake* newSnake = new Snake(0);
	ii = 0;
	
	//reading contents of the file
	ifstream myfile (filename.c_str());
  	if (myfile.is_open())
  	{
    	while ( getline (myfile,line) ){	
    	stringstream ss(line);
    	 while(ss >> token){
    	 	if(ii ==0){
    	 		int score ; //taking score
    	 		sscanf(token.c_str(),"%d",&score);
    	 		newSnake->AddScore(score);
    	 		ii++;
			 }
			else if(ii == 1){
				int length;	//taking length
    	 		sscanf(token.c_str(),"%d",&length);
    	 		newSnake->AddLength(length);
    	 		ii++;
			}
			else if(ii == 2){
				int sec;	//taking seconds
    	 		sscanf(token.c_str(),"%d",&sec);
    	 		newSnake->seconds = sec;
    	 		ii++;
			}
			else if(ii == 3){
				int min;	//taking minutes
    	 		sscanf(token.c_str(),"%d",&min);
    	 		newSnake->minutes = min;
    	 		ii++;
			}
			else if(ii == 4){
				int hr;		//taking hours
    	 		sscanf(token.c_str(),"%d",&hr);
    	 		newSnake->hours = hr;
    	 		ii++;
			}
			else if(ii == 5){
				int dir;		//taking hours
    	 		sscanf(token.c_str(),"%d",&dir);
    	 		newSnake->CurrDir = dir;
    	 		ii++;
			}
			else{
				//taking body input
				ss >> token1;
				Pixel* p1 = new Pixel;
				int x ;
				int y ;
				sscanf(token.c_str(),"%d",&x);
				sscanf(token1.c_str(),"%d",&y);
				p1->init(x,y);
				newSnake->AddToBody(p1);
			}
    	 	
		 }
		 
   		}
	}
	else{
		system("cls");
		ShowBorder();
		gotoxy(35,12);
		cout << "ERROR : File could not be loaded";
		Sleep(2000);
		goto SelectSavedGame;
	}
    myfile.close();
    system("cls");
	return *newSnake;
}
char SaveGame(Snake s1){

	//taking username
	string GameName;
	
	GameName.clear();
	GameName = TakeUsername();
	
	//Adding game to savedgames
	FILE* fptr;
	fptr = fopen("Savedgames.txt","a+");
	Game* gptr = new Game;
	
	gptr->GetUser(GameName);
	gptr->GetTime();
	gptr->AddGame(fptr);
	
	string filename = gptr->GetFileName();
	filename.append(".txt");

	fclose(fptr);
	//Adding data to the game file
	FILE* gamefileptr;
	gamefileptr = fopen(filename.c_str(),"w");
	fprintf(gamefileptr,"%d\n%d\n%d\n%d\n%d\n%d\n",s1.GetScore(),s1.GetLength(),s1.seconds,s1.minutes,s1.hours,s1.CurrDir);
	
	vector <Pixel> copy = s1.GetBody();

	for(ii = 0; ii < copy.size() ;ii++)
		fprintf(gamefileptr,"%d %d\n",copy[ii].x,copy[ii].y);
		
	fclose(gamefileptr); 
	
	//taking response from user
	system("cls");
	gotoxy(47,13);
	cout << "Saved Successfully!";
	gotoxy(45,14);
	cout << "Press 'c' to continue";
	gotoxy(45,15);
	cout << "Press 'esc to exit";
	char ret = getch();
	return ret;
}

int main(){
	//setting default direction
	char input = 72;
	
	//setting default speed
	int speed = 3;
	
	WelcomeScreen:		
	HighScores myHighScores;
	
	WelcomeScreen();
	
	//Taking choice from user
	char choice = getch();
	
	
	if(choice == '1'){ //Single Player Game
	
	SinglePlayerGame :
	
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		system("cls");
		
		//initialising game screen
		ShowBorder();	
		ShowScoreCard(speed);
		
		
		//initialising snake
		Snake mySnake(5);
		mySnake.PrintScore();
		mySnake.ShowSnake();
		
		//initialising food
		Food myFood;
		myFood.Generate();
		myFood.show(3);
		
		//initialising direction indicator of snake
		char dir = 77;
				
		getch();	//key to start game
					
		while(!mySnake.GameOver()){	
				
			mySnake.PrintTimer(speed);	
			mySnake.ShowSnake();
			Sleep(110 - 20*speed);
			mySnake.move(dir);		
			myFood.show(3);
			//check if food is eaten
			if(mySnake.Eat(myFood)){
				myFood.hide();
				myFood.Generate();
				myFood.show(3);
				mySnake.PrintScore();
			}			
			
			//check for input
			if(kbhit()){
				input = getch();	
			}
			//Exit the game
			if(input == 27){
				system("cls");
				goto WelcomeScreen;
			}
			//Pausing the game
			else if(input == 'p'){
					input = getch();
			}
			//Saving the game
			else if(input == 's'){
				char ext = SaveGame(mySnake);
				if (ext == 27){
					//exit after saving
					goto WelcomeScreen;
				}
				else {
					//continuing after saving
					input = dir; //resetting input
					
					system("cls");
					
					ShowBorder();
					ShowScoreCard(speed);
					gotoxy(10, 28);
					cout << "Level : " << speed ;
					
					myFood.Generate();
					myFood.show(3);
					
					mySnake.PrintScore();					
					continue;
				}
			}
			try{
				//checking for valid move and throwing if valid
				if((input == 72 && dir == 75) || (input == 80 && dir == 75) || (input == 75 && dir == 72) || (input == 77 && dir == 72) || (input == 72 && dir == 77) ||
				(input == 80 && dir == 77) || (input == 75 && dir == 80)  || (input == 77 && dir == 80)  ){
					throw input; 
				}
			}
			catch(char x){//changing dir
				dir = input;
			}
			mySnake.Time++;
		}		
		//choice after game ends
	 	char ch = (GameOverScreen(mySnake.GetScore()));
	 	string username2;
		switch(ch){
		case 'n' : //start new game
				   goto SinglePlayerGame;
				   break;
		case 'y' :  //add to highscore
				username2 = TakeUsername();				
				myHighScores.AddHighScore(username2, mySnake.GetScore());
				goto WelcomeScreen;
				break;
		default: 	//go to home screen	
			goto WelcomeScreen;
			break;
		}
	}
	if(choice == '2'){
							
		system("cls");
		
		//loading the snake
		Snake* mySnake = new Snake(0);
		*mySnake = LoadGame();
		char dir = mySnake->CurrDir;
		//checking if ready
				
		gotoxy(45,12);
		cout << "Press any key to start";
		getch();
		system("cls");
		//Initialising food
		Food myFood;
		myFood.Generate();
		myFood.show(3);
		input = dir;
		
		//Game Screen
		ShowBorder();
		ShowScoreCard(speed);
		mySnake->ShowSnake();
		mySnake->PrintScore();
		
		gotoxy(10, 28);	
		cout << "Level : " << speed ;
				
		while(!mySnake->GameOver()){	
			
			mySnake->PrintTimer(speed);	
			mySnake->ShowSnake();
			Sleep(110 - 20*speed);
			mySnake->move(dir);		
			myFood.show(3);
			
			if(mySnake->Eat(myFood)){
				myFood.hide();
				myFood.Generate();
				myFood.show(3);
				mySnake->PrintScore();
			}
			if(kbhit()){
				input = getch();	
			}
			if(input == 27){
				system("cls");
				goto WelcomeScreen;
			}
			else if(input == 'p'){
					input = getch();
			}
			else if(input == 's'){
				char ext = SaveGame(*mySnake);
				if (ext == 27){
					goto WelcomeScreen;
				}
				else {
					system("cls");
					ShowBorder();
					
					gotoxy(10, 28);
					cout << "Level : " << speed ;
					
					myFood.Generate();
					myFood.show(3);
					mySnake->PrintScore();
					ShowScoreCard(speed);
					input = dir;						
					continue;
				}
			}
			try{
				if((input == 72 && dir == 75) || (input == 80 && dir == 75) || (input == 75 && dir == 72) || (input == 77 && dir == 72) || (input == 72 && dir == 77) ||
				(input == 80 && dir == 77) || (input == 75 && dir == 80)  || (input == 77 && dir == 80)  ){
					throw input; 
				}
			}
			catch(char x){
				dir = input;
			}
			mySnake->Time++;
		}
		char ch = (GameOverScreen(mySnake->GetScore()));
	 	string username2;
		switch(ch){
		case 'n' : goto SinglePlayerGame;
				   break;
		case 'y' :  
				username2 = TakeUsername();				
				myHighScores.AddHighScore(username2, mySnake->GetScore());
				goto WelcomeScreen;
				break;
		default: 		
			goto WelcomeScreen;
			break;
		}
	}
	if(choice == '3'){
		myHighScores.ShowHighScore();
		gotoxy(70,25);
		cout << "Press any key to go back .. " ;
		char check = getch();
		system("cls");
		goto WelcomeScreen;
	}
	if (choice == '4'){
		system("cls");
		RulesAndControls();
		gotoxy(70,25);
		cout << "Press any key to go back .. " ;
		char check = getch();
		system("cls");
		goto WelcomeScreen;
	}
	if(choice == '5'){
		int tempspeed = speed;
		system("cls");
		string x = LevelList();
		speed = atoi(x.c_str());
		if(speed >4 || speed < 0)
		speed = tempspeed;
		system("cls");
		goto WelcomeScreen;
	}
}

	
