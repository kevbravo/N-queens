//Libraries we will use in our program this includes c++ stack
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>

//to avoid typing std when printing or asking for input
using namespace std;

//declare all of our functions
int** init(int** board, int size);

//these methods will not return a value
void displayBoard(int** board, int size);
void assign(int** board, int x, int y, int value);
void sort(int** board, stack<int> *r, stack<int> *c, int size);

bool conflict(int** board, int size);

int fill(int** board, int size);

bool conflict_row(int** board, int i, int size);
bool conflict_col(int** board, int j, int size);
bool conflict_diagN(int** board, int i, int j, int size);
bool conflict_diagP(int** board, int i, int j, int size);

//main will be responsible for calling our methods and prompting user to enter an integer
int main(){

	int size;

	cout << "enter an integer value for the number of queens" << endl;

	cin >> size;

//we initialize our chess board using a double pointer for a two dimensional array
	int** board = init(board, size);

//calling assign function to enter first queen
//	assign(board, 0, 0, 1);
	
//next we use two stacks to keep track of the queen position with rows and columns respectively
	stack<int> r;

	stack<int> c;
	
//calling sort method to begin queen sorting
	sort(board, &r, &c, size);

}

//initializing the board of type double pointer to an integer 2d array
int** init(int** board, int size){

//we store the first array pointer in board think of x and y planes this will be our row
	board = new int* [size];

//our for loop creates the matrix and fills it with zeros
	for(int i = 0; i < size; i++){
			
		board[i] = new int[size];
	
//iterate until all positions in the array are filled with zero	
		for(int j = 0; j < size; j++){

			board[i][j] = 0;
		}
	}

//since it is a value of type double pointer we return board
	return board;

}

void displayBoard(int** board, int size){

	for(int i = 0; i < size; i++){


		for(int j = 0; j < size; j++){

			if(board[j][i] == 1){

			cout << "Q" << "|";
		}

			else{
			
				cout << " " << "|";
			}
		}

		cout << endl;
	}
}

//this method will assign a one or zero corresponding with the location of the array index
void assign(int** board, int x, int y, int value){

	board[x][y] = value;
}

//our sort function takes in the stacks, board and size of board
void sort(int** board, stack<int> *r, stack<int> *c, int size){

//we start at the first position of the matrix	
	int x = 0; 
	int y = 0;
	
//push those positions onto both column and row stacks
	c->push(x);
	r->push(y); 
	
//we then call the assign function to change that position to make it hold one
	assign(board, x, y, 1);

	displayBoard(board, size);

	cout << endl;

//this while loop will keep going as long as there is a conflict or the board has not been filled with the maximum number of queens
	while(conflict(board, size) || fill(board, size) != size){

//checks if there is no conflict then proceeds to move to next row after top of stack and resets x to first column	
		if(!conflict(board, size)){

			y = r->top() + 1;
			x = 0;

//next we push those positions onto stacks			
			r->push(y);
			c->push(x);

//assign the x and y a value of one to represent queen
			assign(board, x, y, 1);
			displayBoard(board, size);
		}
	
//executes if there is a conflict and x has not reached the end of the column array	
		else if(conflict(board, size) && x < size - 1){
			
//changes the original value of the conflicting position back to zero		
			assign(board, x, y, 0);
	
//we then move to the next column after top of c stack and set y equal to the value at the top of r stack		
			y = r->top();
			x = c->top() + 1;

//we remove the positions stored on both stacks
			r->pop();
			c->pop();

//push new positions onto stack
			r->push(y);
			c->push(x);

//place queen on that position and display it
			assign(board, x, y, 1);
			displayBoard(board, size);
		}

//else checks if there is a conflict and x has reached the end of the column array
		else if(conflict(board, size) && x >= size - 1){
			
//this while loop will run as long as x is greater than or equal to the size of the board 
			while(x >= size - 1){

//changes conflict position to zero
				assign(board, x, y, 0);

//pops the values on both stacks which will decrement the position in the matrix to the last stored values				
				r->pop();
				c->pop();

//sets the new values of top to both x and y
				y = r->top();
				x = c->top();
			}

//changes the previous queen position to zero
			assign(board, x, y, 0);
	
//x becomes position to the right of top of column stack	
			y = r->top();
			x = c->top() + 1;

//sets that position to new queen position and displays the board
			assign(board, x, y, 1);
			displayBoard(board, size);

//pops the old values off the top of both the stacks
			r->pop();
			c->pop();

//pushes new queen position onto stacks
			r->push(y);
			c->push(x);

		}
		
//prints empty line for reading the output better
		cout << endl;
		
	}

}


//this method will check if there is any sort of conflict with the position of the queen
bool conflict(int** board, int size){

//our for loop will iterate through the board to check rows, columns, and diagonal conflicts
	for (int i = 0; i < size; i++){

      		for (int j = 0 ; j < size ; j++ ){
	
//if there is a queen at that position on the board and there is a conflict on any of the methods tested it will return true 		
			if(board[i][j]== 1 && (conflict_row(board, i, size) ||
	 					conflict_col(board, j, size) || 
						conflict_diagN (board, i, j, size) || 
						conflict_diagP(board, i, j, size) ))
                
				return true;
          	 }
        }

//otherwise there is no conflict
	return false;
}

//specifically checks the row the queen is in to make sure there is no conflict
bool conflict_row(int** board, int r, int size){

//we use this integer to keep track of how many queens are in each row
	int a = 0;

//our for loop will iterate through each column to check if there is another queen
 	for (int j = 0; j < size; j++){

        	if (board[r][j] == 1)

//adds one each time we find a queen in the same row
            		 a++;
    	}

//if there is more than one queen there is a conflict with the row
	if(a >= 2){

		return true;

	}
        
//else there is no conflict
	return false;
}

//checks column of the queen
bool conflict_col(int** board, int c, int size){
	
//count how many queens are in the same column
	int a = 0;
 
//iterates each row to check for another queen
	for (int i = 0; i < size; i++){
        
//if there is a queen we add one to our counter
		if (board[i][c] == 1)
            
			a++;
   		}
    
//conflict if more than one queen per column
	if(a >= 2){

		return true;
	}

//no conflict if otherwise
	return false;
}

//method used to check negative diagonal to the queen 
bool conflict_diagN(int** board, int r, int c, int size){

//we store the positions of minus one from both x and y position of the queen to get the negative diagonal position from the queen
//example queen position = (1,1) diagonal = (0,0)
	int row = r - 1;
    	int col = c - 1;
    
//executes while row and column do not access outside of matrix to ensure all diagonals are checked
	while ((row > -1) && (col > -1)){
        
//if there is a queen in diagonally left to the initial queen there is a conflict
		if (board[row][col] == 1){
            
			return true;
        	}

//else we check the next diagonally up left position        
	row--;
        
	col--;
    	}
    
//this will check for the diagonal down right position
//example queen = (1,1) diagonal = (2,2)
	row = r + 1;
    	col = c + 1;
    
//while the row and column don't go past the size of the board
	while (!(row >= size) && !(col >= size)){
        
		if (board[row][col] == 1){
            		
			return true;
        	}

//checks all diagonal positions        
	row++;
        col++;

   	}
   
//no conflict 	
	return false;
}

//this one will check diagonally the opposite way
bool conflict_diagP(int** board, int r, int c, int size){

//up one and right one position from queen
	int row = r - 1;
    	int col = c + 1;

//keeps numbers within matrix range
    	while (row != -1 && col != size){

//if there exists another queen return conflict
		if (board[row][col] == 1)
            		return true;

//checks rest of positions        
		row--;
        
		col++;
	}

//same as before it this section checks the opposite way    
	row =r + 1;
    
	col =c - 1;
    
	while (row != size && col != -1){
        
		if (board[row][col] == 1)
            
			return true;
        
		row++;
        
		col--;
	}
    
//no conflict
	return false;
}

//our fill method will check how many times there is a queen in the board
int fill(int** board, int size){

//start with zero queens
	int a = 0;
    	
//iterate through whole board
	for (int r = 0; r < size; r++){
       
		for (int c = 0 ;c < size ;c++){
   
//counts how many times "1" appears which represents queens         
			if (board[r][c] == 1){
                
				a++;
            		}
        	} 
    	}

//returns number of queens    
	return a;
}







