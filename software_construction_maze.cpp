#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

class Node
{
public:
	Node();
	Node(string name);
	void setName(string name);
	string getNodeName();
	void attachNewNode(Node *newNode, int direction);
	Node* getAttachedNode(int direction);
	void attachSnakeLadderNode(Node *newNode);
	Node* getSnakeLadderNode();
private:
	string nodeName;
	Node* attachedNodes[4];
	Node* snakeLadderNode;
};
class Graph
{
public:
	Node *createGraph(string filename);
	string getEnd();
	bool isNode(string nodeName);
	Node* findNode(string nodeName);
	int rollDice();
private:
	string endNode;
	Node *nodes[100];
};
class Player
{
public:
	Player();
	Player(string username);
	Node *getCurrentPos();
	string getName();
	void setCurrentPos(Node *newNode);
	void setPath(string nodeName);
	string getPath();
private:
	string userName;
	Node* currentPos;
	string pathTaken;
};
class System
{
public:
	void displayMenu();
	bool playerPos(string nodename);
private:
	Player player1;
	Player player2;
	Player player3;
	Player player4;
	Graph graph;
}snakesAndLadders;

int main()
{
	snakesAndLadders.displayMenu();
	return 0;
}

//default constructor
Node::Node()
{

}
//overloaded constructor
Node::Node(string name)
{
	nodeName = name;
	for (int i = 0; i < 5; i++)
	{
		attachedNodes[i] = NULL;
	}
}
//set name of node to given string
void Node::setName(string name)
{
	nodeName = name;
}
//return nodeName
string Node::getNodeName()
{
	return nodeName;
}
//create a from this node to *newNode
void Node::attachNewNode(Node *newNode, int direction)
{
	attachedNodes[direction] = newNode;
}
//return node in given direction from this node
Node* Node::getAttachedNode(int direction)
{
	return attachedNodes[direction];
}
//attach new snake or ladder node from this to *newNode
void Node::attachSnakeLadderNode(Node *newNode)
{
	snakeLadderNode = newNode;
}
//return snake or ladder node from this node
Node *Node::getSnakeLadderNode()
{
	return snakeLadderNode;
}

/*creates the graph to be traversed through in the game and 
returns a pointer to the starting node*/
Node* Graph::createGraph(string filename)
{
	string start, finish, line, temp, temp2 , numOfNodes;
	Node *p1;
	int i;
	int index = 0;
	ifstream read;
	read.open(filename);
	getline(read, numOfNodes);

	getline(read, start);
	p1 = new Node(start);
	nodes[index] = p1;
	index++;
	getline(read, finish);
	endNode = finish;

	//fill my pointer data structure to be accessed
	while (!read.eof())
	{
		getline(read, line);
		temp = line.substr(0, 2);
		if (temp != p1->getNodeName())
		{
			Node *b1;
			b1 = new Node(temp);
			nodes[index] = b1;
			index++;
		}
	}
	read.close();

	//links correct nodes
	read.open(filename);
	getline(read, numOfNodes);
	getline(read, numOfNodes);
	getline(read, numOfNodes);
    while (getline(read, line))
	{
		temp = line.substr(0, 2);
		Node *b2;
		b2 = findNode(temp);
		
		i = line.find(" ", 0);
		temp2 = line.substr(i + 1, 1);
		if (temp2 != "*")
		{
			temp2 = line.substr(i + 1, 2);
			Node *p2;
			p2 = findNode(temp2);
			b2->attachNewNode(p2, 0);
		}

		i = line.find(" ", i + 1);
		temp2 = line.substr(i + 1, 1);
		if (temp2 != "*")
		{
			temp2 = line.substr(i + 1, 2);
			Node *p3;
			p3 = findNode(temp2);
			b2->attachNewNode(p3, 1);
		}

		i = line.find(" ", i + 1);
		temp2 = line.substr(i + 1, 1);
		if (temp2 != "*")
		{
			temp2 = line.substr(i + 1, 2);
			Node *p4;
			p4 = findNode(temp2);
			b2->attachNewNode(p4, 2);
		}

		i = line.find(" ", i + 1);
		temp2 = line.substr(i + 1, 1);
		if (temp2 != "*")
		{
			temp2 = line.substr(i + 1, 2);
			Node *p5;
			p5 = findNode(temp2);
			b2->attachNewNode(p5, 3);
		}

		i = line.find(" ", i + 1);
		temp2 = line.substr(i + 1, 1);
		if (temp2 != "*")
		{
			temp2 = line.substr(i + 1, 2);
			Node *p6;
			p6 = findNode(temp2);
			b2->attachSnakeLadderNode(p6);
		}
	}

	return p1;
}
//return name of end node
string Graph::getEnd()
{
	return endNode;
}
//checks whether node has been created
bool Graph::isNode(string nodeName)
{
	for (int i = 0; i < 100; i++)
	{
		if (nodes[i]->getNodeName() == nodeName)
		{
			return true;
		}
	}
	return false;
}
//finds specified pointer in data structure
Node* Graph::findNode(string nodeName)
{
		
	for (int i = 0; i < 100; i++)
	{
		
		if (nodes[i]->getNodeName().substr(0,2) == (nodeName))
		{
			return nodes[i];
		}

		/*else
		{
			cout << endl << "Node not found";
			//cout << endl << nodes[i]->getNodeName();
		}*/

	}
	return NULL;
}
//rool dice and return value 1-6
int Graph::rollDice()
{
	for (int counter = 0; counter < 2; counter++)
	{
		srand(time(0));
		for (int i = 0; i <6; i++)
		{
			//cout << rand() % 6 + 1 << endl;
			return rand() % 6 + 1;
		}
	}
	return 0;
}

//player default constructor
Player::Player()
{

}
//player overloadded constructor
Player::Player(string username)
{
	userName = username;
}
//return true is player is at finish node
Node *Player::getCurrentPos()
{
	return currentPos;
}
//return player name
string Player::getName()
{
	return userName;
}
//sets currentPosition to specified node
void Player::setCurrentPos(Node *newNode)
{
	currentPos = newNode;
}
//keep up with path taken from player
void Player::setPath(string nodeName)
{
	pathTaken = pathTaken + " " + nodeName;
}
//return path taken
string Player::getPath()
{
	return pathTaken;
}

//interact with the players in the game
void System::displayMenu()
{
	//create a pointer and call createGraph to assign the starting node to this pointer
	Node *p1;
	Node *p2;
	Node *p3;
	Node *p4;
	int ctr = 1;
	string filename;
	cout << "Enter the filename: ";
	cin >> filename;
	p1 = graph.createGraph(filename);
	p2 = p1;
	p3 = p1;
	p4 = p1;

	cout << endl << "===============================================";
	cout << endl << "| Welcome to the Snakes and Ladders Maze game |";
	cout << endl << "===============================================";

	int numOfPlayers;
	string playerName;
	cout << endl << "Enter the number of players: ";
	cin >> numOfPlayers;

	for (int i = 1; i <= numOfPlayers; i++)
	{
		cout << "Enter the name of player #" << i << ": ";
		cin >> playerName;
		if (i == 1)
		{
			player1 = Player(playerName);
			player1.setPath(p1->getNodeName());
			player1.setCurrentPos(p1);
		}
		if (i == 2)
		{
			player2 = Player(playerName);
			player2.setPath(p2->getNodeName());
			player2.setCurrentPos(p2);
		}
		if (i == 3)
		{
			player3 = Player(playerName);
			player3.setPath(p3->getNodeName());
			player3.setCurrentPos(p3);
		}
		if (i == 4)
		{
			player4 = Player(playerName);
			player4.setPath(p4->getNodeName());
			player4.setCurrentPos(p4);
		}
	}
	do
	{
		string empty;
		cout << endl << "==================";
		cout << endl << "| " + player1.getName() + "'s turn |";
		cout << endl << "==================";

		cout << endl << "Hit enter to throw the dice:";
		int dice = graph.rollDice();
		cout << player1.getName() + "'s dice throw is " + to_string(dice) + "."  << endl  ;
		cout << player1.getName() + " can move to  " + to_string(dice) + " nodes." << endl  ;

		for (int i = 0; i < dice; i++)
		{
			if (player1.getCurrentPos()->getSnakeLadderNode() != NULL)
			{
				cout << "you have hit a snake/ladder node." << endl;
				player1.setPath(player1.getCurrentPos()->getSnakeLadderNode()->getNodeName());
				player1.setCurrentPos(player1.getCurrentPos()->getSnakeLadderNode());
				i--;
				if (player1.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
				{
					cout << endl << "congratulations, " + player1.getName() + " is the winnder! You have reached the destination point.";
					cout << endl << "Nodes visited: " + player1.getPath();
					exit(0);
				}
			}

			else
			{
				string directions = player1.getName() + " is currently on Node " + player1.getCurrentPos()->getNodeName() + ", you can go";
				if (player1.getCurrentPos()->getAttachedNode(0) != NULL)
				{
					directions = directions + " North ";
				}
				if (player1.getCurrentPos()->getAttachedNode(1) != NULL)
				{
					directions = directions + " East ";
				}
				if (player1.getCurrentPos()->getAttachedNode(2) != NULL)
				{
					directions = directions + " South ";
				}
				if (player1.getCurrentPos()->getAttachedNode(3) != NULL)
				{
					directions = directions + " West ";
				}

				directions = directions + ", which direction would you like to go?";
				cout << directions << endl;
				string answer;
				cin >> answer;

				if (answer == "N" || answer == "n" || answer == "North" || answer == "north")
				{
					player1.setPath(player1.getCurrentPos()->getAttachedNode(0)->getNodeName());
					player1.setCurrentPos(player1.getCurrentPos()->getAttachedNode(0));
					if (player1.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
					{
						cout << endl << "congratulations, " + player1.getName() + " is the winnder! You have reached the destination point.";
						cout << endl << "Nodes visited: " + player1.getPath();
						exit(0);
					}
				}
				if (answer == "E" || answer == "e" || answer == "East" || answer == "east")
				{
					player1.setPath(player1.getCurrentPos()->getAttachedNode(1)->getNodeName());
					player1.setCurrentPos(player1.getCurrentPos()->getAttachedNode(1));
					if (player1.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
					{
						cout << endl << "congratulations, " + player1.getName() + " is the winnder! You have reached the destination point.";
						cout << endl << "Nodes visited: " + player1.getPath();
						exit(0);
					}
				}
				if (answer == "S" || answer == "s" || answer == "South" || answer == "south")
				{
					player1.setPath(player1.getCurrentPos()->getAttachedNode(2)->getNodeName());
					player1.setCurrentPos(player1.getCurrentPos()->getAttachedNode(2));
					if (player1.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
					{
						cout << endl << "congratulations, " + player1.getName() + " is the winnder! You have reached the destination point.";
						cout << endl << "Nodes visited: " + player1.getPath();
						exit(0);
					}
				}
				if (answer == "W" || answer == "w" || answer == "West" || answer == "west")
				{
					player1.setPath(player1.getCurrentPos()->getAttachedNode(3)->getNodeName());
					player1.setCurrentPos(player1.getCurrentPos()->getAttachedNode(3));
					if (player1.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
					{
						cout << endl << "congratulations, " + player1.getName() + " is the winnder! You have reached the destination point.";
						cout << endl << "Nodes visited: " + player1.getPath();
						exit(0);
					}
				}
			}
		}
		if (ctr == numOfPlayers) ctr = 1;
		else ctr++;

		if (ctr == 2)
		{
			cout << endl << "=============";
			cout << endl << "| " + player2.getName() + "'s turn |";
			cout << endl << "=============";

			cout << "Hit enter to throw the dice.";
			int dice = graph.rollDice();
			cout << player2.getName() + "'s dice throw is " + to_string(dice) + "." << endl;
			cout << player2.getName() + " can move to  " + to_string(dice) + " nodes." << endl;

			for (int i = 0; i < dice; i++)
			{
				if (player2.getCurrentPos()->getSnakeLadderNode() != NULL)
				{
					cout << "you have hit a snake/ladder node." << endl;
					player2.setPath(player2.getCurrentPos()->getSnakeLadderNode()->getNodeName());
					player2.setCurrentPos(player2.getCurrentPos()->getSnakeLadderNode());
					i--;
					if (player2.getCurrentPos()->getNodeName().substr(0,2) == graph.getEnd().substr(0, 2))
					{
						cout << endl << "congratulations, " + player2.getName() + " is the winnder! You have reached the destination point.";
						cout << endl << "Nodes visited: " + player2.getPath();
						exit(0);
					}
				}

				else
				{
					string directions = player2.getName() + " is currently on Node " + player2.getCurrentPos()->getNodeName() + ", you can go";
					if (player2.getCurrentPos()->getAttachedNode(0) != NULL)
					{
						directions = directions + " North ";
					}
					if (player2.getCurrentPos()->getAttachedNode(1) != NULL)
					{
						directions = directions + " East ";
					}
					if (player2.getCurrentPos()->getAttachedNode(2) != NULL)
					{
						directions = directions + " South ";
					}
					if (player2.getCurrentPos()->getAttachedNode(3) != NULL)
					{
						directions = directions + " West ";
					}

					directions = directions + ", which direction would you like to go?";
					cout << directions << endl;
					string answer;
					cin >> answer;

					if (answer == "N" || answer == "n" || answer == "North" || answer == "north")
					{
						player2.setPath(player2.getCurrentPos()->getAttachedNode(0)->getNodeName());
						player2.setCurrentPos(player2.getCurrentPos()->getAttachedNode(0));
						if (player2.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
						{
							cout << endl << "congratulations, " + player2.getName() + " is the winnder! You have reached the destination point.";
							cout << endl << "Nodes visited: " + player2.getPath();
							exit(0);
						}
					}
					if (answer == "E" || answer == "e" || answer == "East" || answer == "east")
					{
						player2.setPath(player2.getCurrentPos()->getAttachedNode(1)->getNodeName());
						player2.setCurrentPos(player2.getCurrentPos()->getAttachedNode(1));
						if (player2.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
						{
							cout << endl << "congratulations, " + player2.getName() + " is the winnder! You have reached the destination point.";
							cout << endl << "Nodes visited: " + player2.getPath();
							exit(0);
						}
					}
					if (answer == "S" || answer == "s" || answer == "South" || answer == "south")
					{
						player2.setPath(player2.getCurrentPos()->getAttachedNode(2)->getNodeName());
						player2.setCurrentPos(player2.getCurrentPos()->getAttachedNode(2));
						if (player2.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
						{
							cout << endl << "congratulations, " + player2.getName() + " is the winnder! You have reached the destination point.";
							cout << endl << "Nodes visited: " + player2.getPath();
							exit(0);
						}
					}
					if (answer == "W" || answer == "w" || answer == "West" || answer == "west")
					{
						player2.setPath(player2.getCurrentPos()->getAttachedNode(3)->getNodeName());
						player2.setCurrentPos(player2.getCurrentPos()->getAttachedNode(3));
						if (player2.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
						{
							cout << endl << "congratulations, " + player2.getName() + " is the winnder! You have reached the destination point.";
							cout << endl << "Nodes visited: " + player2.getPath();
							exit(0);
						}
					}
				}
			}
			if (ctr == numOfPlayers) ctr = 1;
			else ctr++;

			if (ctr == 3)
			{
				cout << endl << "=============";
				cout << endl << "| " + player3.getName() + "'s turn |";
				cout << endl << "=============";

				cout << "Hit enter to throw the dice.";
				int dice = graph.rollDice();
				cout << player3.getName() + "'s dice throw is " + to_string(dice) + "." << endl;
				cout << player3.getName() + " can move to  " + to_string(dice) + " nodes." << endl;

				for (int i = 0; i < dice; i++)
				{
					if (player3.getCurrentPos()->getSnakeLadderNode() != NULL)
					{
						cout << "you have hit a snake/ladder node." << endl;
						player3.setPath(player3.getCurrentPos()->getSnakeLadderNode()->getNodeName());
						player3.setCurrentPos(player3.getCurrentPos()->getSnakeLadderNode());
						i--;
						if (player3.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
						{
							cout << endl << "congratulations, " + player3.getName() + " is the winnder! You have reached the destination point.";
							cout << endl << "Nodes visited: " + player3.getPath();
							exit(0);
						}
					}

					else
					{
						string directions = player3.getName() + " is currently on Node " + player3.getCurrentPos()->getNodeName() + ", you can go";
						if (player3.getCurrentPos()->getAttachedNode(0) != NULL)
						{
							directions = directions + " North ";
						}
						if (player3.getCurrentPos()->getAttachedNode(1) != NULL)
						{
							directions = directions + " East ";
						}
						if (player3.getCurrentPos()->getAttachedNode(2) != NULL)
						{
							directions = directions + " South ";
						}
						if (player3.getCurrentPos()->getAttachedNode(3) != NULL)
						{
							directions = directions + " West ";
						}

						directions = directions + ", which direction would you like to go?";
						cout << directions << endl;
						string answer;
						cin >> answer;

						if (answer == "N" || answer == "n" || answer == "North" || answer == "north")
						{
							player3.setPath(player3.getCurrentPos()->getAttachedNode(0)->getNodeName());
							player3.setCurrentPos(player3.getCurrentPos()->getAttachedNode(0));
							if (player3.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
							{
								cout << endl << "congratulations, " + player3.getName() + " is the winnder! You have reached the destination point.";
								cout << endl << "Nodes visited: " + player3.getPath();
								exit(0);
							}
						}
						if (answer == "E" || answer == "e" || answer == "East" || answer == "east")
						{
							player3.setPath(player3.getCurrentPos()->getAttachedNode(1)->getNodeName());
							player3.setCurrentPos(player3.getCurrentPos()->getAttachedNode(1));
							if (player3.getCurrentPos()->getNodeName() == graph.getEnd())
							{
								cout << endl << "congratulations, " + player3.getName() + " is the winnder! You have reached the destination point.";
								cout << endl << "Nodes visited: " + player3.getPath();
								exit(0);
							}
						}
						if (answer == "S" || answer == "s" || answer == "South" || answer == "south")
						{
							player3.setPath(player3.getCurrentPos()->getAttachedNode(2)->getNodeName());
							player3.setCurrentPos(player3.getCurrentPos()->getAttachedNode(2));
							if (player3.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
							{
								cout << endl << "congratulations, " + player3.getName() + " is the winnder! You have reached the destination point.";
								cout << endl << "Nodes visited: " + player3.getPath();
								exit(0);
							}
						}
						if (answer == "W" || answer == "w" || answer == "West" || answer == "west")
						{
							player3.setPath(player3.getCurrentPos()->getAttachedNode(3)->getNodeName());
							player3.setCurrentPos(player3.getCurrentPos()->getAttachedNode(3));
							if (player3.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
							{
								cout << endl << "congratulations, " + player3.getName() + " is the winnder! You have reached the destination point.";
								cout << endl << "Nodes visited: " + player3.getPath();
								exit(0);
							}
						}
					}
				}
				if (ctr == numOfPlayers) ctr = 1;
				else ctr++;

				if (ctr == 4)
				{
					cout << endl << "=============";
					cout << endl << "| " + player4.getName() + "'s turn |";
					cout << endl << "=============";

					cout << "Hit enter to throw the dice.";
					int dice = graph.rollDice();
					cout << player4.getName() + "'s dice throw is " + to_string(dice) + "." << endl;
					cout << player4.getName() + " can move to  " + to_string(dice) + " nodes." << endl;

					for (int i = 0; i < dice; i++)
					{
						if (player4.getCurrentPos()->getSnakeLadderNode() != NULL)
						{
							cout << "you have hit a snake/ladder node." << endl;
							player4.setPath(player4.getCurrentPos()->getSnakeLadderNode()->getNodeName());
							player4.setCurrentPos(player4.getCurrentPos()->getSnakeLadderNode());
							i--;
							if (player4.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
							{
								cout << endl << "congratulations, " + player4.getName() + " is the winnder! You have reached the destination point.";
								cout << endl << "Nodes visited: " + player4.getPath();
								exit(0);
							}
						}

						else
						{
							string directions = player4.getName() + " is currently on Node " + player4.getCurrentPos()->getNodeName() + ", you can go";
							if (player4.getCurrentPos()->getAttachedNode(0) != NULL)
							{
								directions = directions + " North ";
							}
							if (player4.getCurrentPos()->getAttachedNode(1) != NULL)
							{
								directions = directions + " East ";
							}
							if (player4.getCurrentPos()->getAttachedNode(2) != NULL)
							{
								directions = directions + " South ";
							}
							if (player4.getCurrentPos()->getAttachedNode(3) != NULL)
							{
								directions = directions + " West ";
							}

							directions = directions + ", which direction would you like to go?";
							cout << directions << endl;
							string answer;
							cin >> answer;

							if (answer == "N" || answer == "n" || answer == "North" || answer == "north")
							{
								player4.setPath(player4.getCurrentPos()->getAttachedNode(0)->getNodeName());
								player4.setCurrentPos(player4.getCurrentPos()->getAttachedNode(0));
								if (player4.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
								{
									cout << endl << "congratulations, " + player4.getName() + " is the winnder! You have reached the destination point.";
									cout << endl << "Nodes visited: " + player4.getPath();
									exit(0);
								}
							}
							if (answer == "E" || answer == "e" || answer == "East" || answer == "east")
							{
								player4.setPath(player4.getCurrentPos()->getAttachedNode(1)->getNodeName());
								player4.setCurrentPos(player4.getCurrentPos()->getAttachedNode(1));
								if (player4.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
								{
									cout << endl << "congratulations, " + player4.getName() + " is the winnder! You have reached the destination point.";
									cout << endl << "Nodes visited: " + player4.getPath();
									exit(0);
								}
							}
							if (answer == "S" || answer == "s" || answer == "South" || answer == "south")
							{
								player4.setPath(player4.getCurrentPos()->getAttachedNode(2)->getNodeName());
								player4.setCurrentPos(player4.getCurrentPos()->getAttachedNode(2));
								if (player4.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
								{
									cout << endl << "congratulations, " + player4.getName() + " is the winnder! You have reached the destination point.";
									cout << endl << "Nodes visited: " + player4.getPath();
									exit(0);
								}
							}
							if (answer == "W" || answer == "w" || answer == "West" || answer == "west")
							{
								player4.setPath(player4.getCurrentPos()->getAttachedNode(3)->getNodeName());
								player4.setCurrentPos(player4.getCurrentPos()->getAttachedNode(3));
								if (player4.getCurrentPos()->getNodeName().substr(0, 2) == graph.getEnd().substr(0, 2))
								{
									cout << endl << "congratulations, " + player4.getName() + " is the winnder! You have reached the destination point.";
									cout << endl << "Nodes visited: " + player4.getPath();
									exit(0);
								}
							}
						}
					}
					if (ctr == 4) ctr = 1;
				}
			}
		}
	} while (player1.getCurrentPos()->getNodeName() != graph.getEnd() || player2.getCurrentPos()->getNodeName() != graph.getEnd() || player3.getCurrentPos()->getNodeName() != graph.getEnd() || player4.getCurrentPos()->getNodeName() != graph.getEnd());
}
//checks if any player is at destination node
bool System::playerPos(string nodename)
{
	if (player1.getCurrentPos()->getNodeName() == nodename) return false;
	if (player2.getCurrentPos()->getNodeName() == nodename) return false;
	if (player3.getCurrentPos()->getNodeName() == nodename) return false;
	if (player4.getCurrentPos()->getNodeName() == nodename) return false;
	else return true;
}
