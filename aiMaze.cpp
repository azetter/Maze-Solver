/*
* Andrea Zetter
* CSC 412
* Bryant Walley
* October 08, 2018
* Program: Create an agent that can process a maze. The maze will be a 10x10 grid.
*		   The grid will have a point of entry in the '0' column and a point of exit somewhere
*		   along the other three walls. THe entry will be designated with an 'E', and the
*		   exit with an 'X'. The agent must traverse the left wall to find the Entry and point
*		   and then must traverse the maze, following the path to exit. You will use a Breadth
*		   first (queue), and Depth First (stack) methods.
*/
#include<iostream>
#include <fstream>
#include <queue>
#include <stack>
#include<string>

using namespace std;

// 2Dimensional Array
char matrix[10][10] = {};

// Initialize Visited nodes to false
bool visited[10][10] = { false };

// Create Struct
struct node
{
	char data;
	int row;
	int col;

	vector<int> move;
};
// Vector to store the path
vector <int> path;

// A queue to hold nodes
queue <node> queueNode;

// Stack nodes
stack <node> stackNode;

// BFS prototype
void BFS();

// DFS prototype
void DFS();

int main()
{
	//Read in maze file
	ifstream mazeFile("maze.txt");
	string line;
	
	//Check if file not found
	if (!mazeFile.is_open())
	{
		cout << "No file found." << endl;
	}else
	{
		
		//Read in 10x10 grid
		for (char r = 0; r < 10; r++)
		{
			for (char c = 0; c < 10; c++)
			{
				mazeFile >> matrix[r][c];
			}

		}

		//Print layout
		cout << "                    Simple Maze \n" << endl;
		cout << "     0    1    2    3    4    5    6    7    8    9\n" << endl;

		//Print 2D array 
		for (int r = 0; r < 10; r++)
		{
			cout << "  " << r << "  " << matrix[r][0] << "  ";
			for (int c = 1; c < 10; c++)
			{
				cout << "  " << matrix[r][c] << "  ";
			}
			cout << "  \n" << endl;
		}
	}

	// Output message that we are now showing BFS
	cout << endl << "Breadth First Searh Path: " << endl;

	
	// Find path in maze using BFS
	 BFS();

	 // For loop to iterate matrix and reset visited back to false
	 // this way we can run DFS function
	 for (int r = 0; r < 10; r++)
	 {
		 for (int c = 0; c < 10; c++)
		 {
			 visited[r][c] = false;
		 }
	 }

	 // Output message that we are now showing DFS
	 cout << endl << "\nDepth First Searh Path: " << endl;

	 // Find path in maze using DFS
	 DFS();

	cin.get();
	cin.get();
	return 0;
}

// Breadth First Search Function
void BFS()
{
	// Create entry node
	node entry;

	// Row and Col variables
	int row = 0;
	int col = 0;

	// Find the 'E' in the column 0
	for (int i = 0; i < matrix[i][col]; i++)
	{
		//If E is found
		if (matrix[i][col] == 'E') 
		{
			// Then save E in the queue
			entry.data = matrix[i][col];
			entry.row = i;
			entry.col = col;
			entry.move.push_back(i * 10);
			visited[i][col] = true;
		}
	}

   // Push entry into the queue
	queueNode.push(entry);

	//Check the the queue is not empty
	while (!queueNode.empty())
	{
		// Create a new node current
		node current = queueNode.front();

		// Pop current position
		queueNode.pop();

		// Check if we reached goal state and return
		if (matrix[current.row][current.col] == 'X')
		{
			for (int i = 0; i < current.move.size(); i++)
			{
				// Call printPath to print our path taken
				cout << current.move[i] << " ";
			}
		}

		// Checking left, position - 1
		if (current.col - 1 > 0 && current.col - 1 < 10)
		{
			// If left is P or X & it has not been visited
			if ((matrix[current.row][current.col - 1] == 'P' || matrix[current.row][current.col - 1] == 'X') && !visited[current.row][current.col - 1])
			{
				// create temp node
				node temp;

				// Temp will be current position
				temp.row = current.row;
				temp.col = current.col - 1;

				//Save the temp position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// Push temp to queue
				queueNode.push(temp);

				// Check it has been visited
				visited[temp.row][temp.col] = true;
			}
		}

		// Checking up, position - 10
		if (current.row - 1 >= 0 && current.row - 1 < 10)
		{
			// If top is P or X and it hasn't been visited
			if ((matrix[current.row - 1][current.col] == 'P' || matrix[current.row - 1][current.col] == 'X') && !visited[current.row - 1][current.col])
			{
				// Create a new temp node
				node temp;

				// Let temp be current position
				temp.row = current.row - 1;
				temp.col = current.col;

				// Save the temp position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// Push temp to queue
				queueNode.push(temp);

				// Check it has been visited
				visited[temp.row][temp.col] = true;
			}
		}

		//Checking right, position + 1 !isNotVisited(pos + 1)
		if (current.col + 1 < 9 && current.col + 1 >= 0)
		{
			// If right position is P or X and it hasn't been visited
			if ((matrix[current.row][current.col + 1] == 'P' || matrix[current.row][current.col + 1] == 'X') && !visited[current.row][current.col + 1])
			{
				// Create a new temp node
				node temp;

				// Let temp be current position
				temp.row = current.row;
				temp.col = current.col + 1;

				//Save the temp position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// Push temp to queue
				queueNode.push(temp);

				// It has been visited so set to true
				visited[temp.row][temp.col] = true;
			}
		}

		// Checking down, position + 10
		if (current.row + 1 <= 9 && current.row + 1 >= 0)
		{
			// If right position is P or X and it hasn't been visited
			if ((matrix[current.row + 1][current.col] == 'P' || matrix[current.row + 1][current.col] == 'X') && !visited[current.row + 1][current.col])
			{
				// Let temp be current position
				node temp;
				//Set temp = current
				temp.row = current.row + 1;
				temp.col = current.col;

				//Save the current position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// & Push temp to queue
				queueNode.push(temp);

				// It has been visited so set to true
				visited[temp.row][temp.col] = true;
			}
		}
	}
	
}

// Depth First Search Function
void DFS()
{
	// Create entry node
	node entry;

	// Row and Col variables
	int row = 0;
	int col = 0;

	// Find the 'E' in the column 0
	for (int i = 0; i < matrix[i][col]; i++)
	{
		//If E is found
		if (matrix[i][col] == 'E')
		{
			// Then save E in the queue
			entry.data = matrix[i][col];
			entry.row = i;
			entry.col = col;
			entry.move.push_back(i * 10);
			visited[i][col] = true;
		}
	}

	// Push entry into the stack
	stackNode.push(entry);

	//Check the the stack is not empty
	while (!stackNode.empty())
	{
		// Create a new node current
		node current = stackNode.top();

		// Pop current position
		stackNode.pop();

		// Check if we reached goal state and return
		if (matrix[current.row][current.col] == 'X')
		{
			for (int i = 0; i < current.move.size(); i++)
			{
				// Call printPath to print our path taken
				cout << current.move[i] << " ";
			}
			
		}

		// Checking left, position - 1
		if (current.col - 1 > 0 && current.col - 1 < 10)//col > 0 current.col > 0
		{
			// If left is P or X & it has not been visited
			if ((matrix[current.row][current.col - 1] == 'P' || matrix[current.row][current.col - 1] == 'X') && !visited[current.row][current.col - 1])
			{
				// create temp node
				node temp;

				// Temp will be current position
				temp.row = current.row;
				temp.col = current.col - 1;

				//Save the temp position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// Push temp to stack
				stackNode.push(temp);

				// Check it has been visited
				visited[temp.row][temp.col] = true;
			}
		}

		// Checking up, position - 1
		if (current.row - 1 >= 0 && current.row - 1 < 10)
		{
			// If top is P or X and it hasn't been visited
			if ((matrix[current.row - 1][current.col] == 'P' || matrix[current.row - 1][current.col] == 'X') && !visited[current.row - 1][current.col])
			{
				// Create a new temp node
				node temp;

				// Let temp be current position
				temp.row = current.row - 1;
				temp.col = current.col;

				// Save the temp position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// Push temp to stack
				stackNode.push(temp);

				// Check it has been visited
				visited[temp.row][temp.col] = true;
			}
		}

		//Checking right, position + 1 !isNotVisited(pos + 1)
		if (current.col + 1 < 9 && current.col + 1 >= 0)
		{
			// If right position is P or X and it hasn't been visited
			if ((matrix[current.row][current.col + 1] == 'P' || matrix[current.row][current.col + 1] == 'X') && !visited[current.row][current.col + 1])
			{
				// Create a new temp node
				node temp;

				// Let temp be current position
				temp.row = current.row;
				temp.col = current.col + 1;

				//Save the temp position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// Push temp to stack
				stackNode.push(temp);

				// It has been visited so set to true
				visited[temp.row][temp.col] = true;
			}
		}

		// Checking down, position + 1
		if (current.row + 1 <= 9 && current.row + 1 >= 0)
		{
			// If right position is P or X and it hasn't been visited
			if ((matrix[current.row + 1][current.col] == 'P' || matrix[current.row + 1][current.col] == 'X') && !visited[current.row + 1][current.col])
			{
				// Let temp be current position
				node temp;
				//Set temp = current
				temp.row = current.row + 1;
				temp.col = current.col;

				//Save the current position into our move vector
				temp.move = current.move;
				temp.move.push_back(temp.row * 10 + temp.col);

				// & Push temp to stack
				stackNode.push(temp);

				// It has been visited so set to true
				visited[temp.row][temp.col] = true;
			}
		}
	}
}