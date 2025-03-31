//PROJECT
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <windows.h>
using namespace std;
//functions 
void initialize_Board();
void display_Board();
void get_player_move();
void check();
void play_game();
//global varriables
int i,j;
int row1,col1,row2,col2;
vector<vector<char> > matrix;
vector<vector<bool> > revealed; //to track currently flipped cards
vector<vector<bool> > matched; //to track permanently flipped cards
vector<vector<char> > board;
//setup the game board
void initialize_Board()
{
	matrix.clear();
	//row1
	vector<char> row1;
	row1.push_back('A');
	row1.push_back('A');
	row1.push_back('B');
	row1.push_back('B');
	matrix.push_back(row1);
	//row2
	vector<char> row2;
	row2.push_back('C');
	row2.push_back('C');
	row2.push_back('D');
	row2.push_back('D');
	matrix.push_back(row2);
	//row3
	vector<char> row3;
	row3.push_back('E');
	row3.push_back('E');
	row3.push_back('F');
	row3.push_back('F');
	matrix.push_back(row3);
	//row4
	vector<char> row4;
	row4.push_back('G');
	row4.push_back('G');
	row4.push_back('H');
	row4.push_back('H');
	matrix.push_back(row4); 
	cout<<endl;
	
	//shuffle the vector
	
	//2d array will be put into 1d array
	vector<char> flat;
	for(i=0;i<matrix.size();++i)
	{
		for(j=0;j<matrix[i].size();++j)
		{
			flat.push_back(matrix[i][j]);
		}
	}
	
	//1d array shuffled:
	
	srand(static_cast<unsigned int>(time(0))); 
	/*this ensure that sequence is different everytime the program runs, takes unsigned int as argument
	time(0) ensure it changes squence each time and static_cast: converts time into unsigned int datatype*/
	for(i=0;i<flat.size();++i)
	{
		int random_index=i+rand()%(flat.size()-i); //random index calculated using rand() function
		swap(flat[i],flat[random_index]); //swapping of the current index with random calculated index
	}
	
	//1d array convereted and put back into 2d array after shuffling
	int k=0;
	for(i=0;i<matrix.size();++i)
	{
		for(j=0;j<matrix[i].size();++j)
		{
			matrix[i][j]=flat[k++];
		}
	}
	vector<bool> boolrow; //1d array to construct flipped as false for all elements initially
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			boolrow.push_back(false); //for 1st row all columns every element is set to false and so on for next rows
		}
		revealed.push_back(boolrow); // boolrow is filled to flipped row by row
		boolrow.clear(); //clear is used to use boolrow for next row iterations
	}
	
}
//display the board
void display_board(const vector<vector<char> > &matrix,const vector<vector<bool> > &revealed)
/*matrix passed as reference with const so as not to modify it and a bool 2d vector flipped 
so as to track cards are hidden or not*/
{
	
	for(i=0;i<matrix.size();++i)
	{
		for(j=0;j<matrix[i].size();++j)
		{
			if(revealed[i][j]) //if flipped true then reveal the card
			{
				cout<<" "<<matrix[i][j]<<" ";
			}
			else //otherwise no reveal of card
			{
				cout<<" # ";
			}
		}
		cout<<endl;
	}
}
//taking player input 
void get_player_move(int &row1,int &col1,int &row2,int &col2,const vector<vector<bool> > &matched)
{
	do{
	cout<<endl;
	cout<<"Enter the row and column for first card:";
	cin>>row1>>col1;
	if(row1<0 || row1>=4 || col1<0 || col1>=4)
	{
		cout<<"Out of range, Value entered for first card. Try Again!";
		continue;
	}
	if(matched[row1][col1])
	{
		cout<<endl<<"Card Already Matched. Choose a Different One!";
		continue;
	}
	break;
	}while(true);
	
	do{
	cout<<"Enter the row and column for the second card:";
	cin>>row2>>col2;
	if(row2<0 || row2>=4 || col2<0 || col2>=4)
	{
		cout<<"Out of range, Value entered for second card. Try Again!";
		continue;
	}
	if(matched[row2][col2])
	{
		cout<<endl<<"Card Already Matched. Choose a Different One!";
		continue;
	}
	if(row1==row2 && col1==col2)
	{
		cout<<"You have already picked this card,choose a different one!";
		continue;
	}
	cout<<endl;
	break;
	}while(true);
}
//checking the board and flipping the cards
void check(const vector<vector<char> > &board,const vector<vector<bool> > &matched)
{
	get_player_move(row1,col1,row2,col2,revealed);
	revealed[row1][col1]=true;
	cout<<"You have selected:"<<matrix[row1][col1]<<endl;
	revealed[row2][col2]=true;
	cout<<"You have selected:"<<matrix[row2][col2]<<endl;
	cout<<endl;
	display_board(matrix, revealed);
}
//play game
void play_game(const vector<vector<char> > &board)
{
	int size=4;
	int moves=0; //to track the number of moves taken
	int total_pairs=(size*size)/2;
	int matches=0; //to count the number of pairs matched
	
	int timeLimit = 300;  //to limit the time
	time_t startTime, currentTime;
    time(&startTime); //captures current time
    int remainingTime;
    cout<<endl<<"You have "<<timeLimit<<" seconds to complete the game!"<<endl;
    
	while(matches<total_pairs)
	{
		time(&currentTime);  // updates current time inside loop to know how much time has passed
        int elapsedTime=difftime(currentTime, startTime); //difference between current and start times
        remainingTime=timeLimit-elapsedTime;
        
        if (remainingTime <= 0) 
		{
        	cout<<endl<<"OOPS! Time's Up!";
        	if(matches)
        	{
            cout <<endl<<"You were able to Match: "<<matches<<" cards"<<endl;
        	}
            return;
        }
        
        int minutes = remainingTime / 60;  // to get the Get minutes
		int seconds = remainingTime % 60;  // to Get the remaining seconds
		cout <<endl<<"Time remaining: "<<minutes<<":"<<(seconds < 10 ? "0" : "")<<seconds<< endl;
		
		check(board,matched);
		if(matrix[row1][col1] == matrix[row2][col2])
		{
			cout<<endl<<"Its a Match"<<endl;
			matches++;
		}
		else
		{
			revealed[row1][col1]=false;
			revealed[row2][col2]=false;
		}
		cout<<endl<<"Moves taken:"<<++moves<<endl;
	}
	int r_minutes=(timeLimit-remainingTime)/60;
	int r_seconds=(timeLimit-remainingTime)%60;
	cout<<endl<<"CONGRATULATIONS!!!!";
	cout<<endl<<"YOU HAVE COMPLETED THE GAME IN "<<r_minutes<<":"<<r_seconds;
}
int main()
{
	cout<<" ____________________________________ "<<endl;
	cout<<"|                                    |"<<endl;
	cout<<"|   WELCOME TO CARD MATCHING GAME!   |"<<endl;
	cout<<"|____________________________________| "<<endl;
	Sleep(2000);
	system("cls");
	
	cout<<endl<<"HERE'S THE RULES OF THE GAME";
	cout<<endl<<endl;
	cout<<"1. A Shuffled 4x4 gride contaning pairs of cards will be displayed."<<endl;
	cout<<"2. Try to match cards by selecting two cards at a time."<<endl;
	cout<<"3. The matched cards, stay flipped, otherwise the cards flip upside down."<<endl;
	cout<<"4. A Move Counter will keep track of the attempts made."<<endl;
	cout<<"5. A Time limit of 5 minutes is there to make sure that game ends after that time."<<endl;
	cout<<"6. Or The game ends when all cards are matched."<<endl;
	cout<<endl<<"7. Press Enter to start the game...";
	cin.get(); //to have enter key as input
	
	system("cls");
	
	cout<<endl<<"* LET THE GAME BEGIN *"<<endl;
	initialize_Board();
	display_board(matrix, revealed);
	play_game(matrix);
	return 0;
	
}
