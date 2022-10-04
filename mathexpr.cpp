/*
 * mathexpr.cpp
 *
 *  Created on: Mar 29, 2022
 *      Author: Jason Salazar
 */

#include<iostream>
#include<sstream>
#include<queue>
#include<vector>
#include<unordered_set>
#include<algorithm>

using namespace std;
//creates connection with parent, expression, and value
struct State {
explicit State(int value, const string &expression, State *parent) :
value {value}, expression(expression), parent {parent} {
}
int value;
string expression;
State *parent;
};

ostringstream oss;
//boolean check for integers only
bool check(string input){
	int size = input.length();
	int count = 0;
for(int i = 0; i < size; i++)
  if(isdigit(input[i]) != false)
		count ++;
return count == size?true : false;
}

string expression(int input) {
	//unordered set for unique values
	// queue for tree
	//vector for deletion
	unordered_set<int> seen_states;
	queue<State*> queue1;
	vector<State*> vector1;
	vector<State*> vector2;

	//root node
	State *s = new State(1,"1",nullptr);
	//enqueue
	queue1.push(s);
	//adding to set
	seen_states.insert(1);

	while (!queue1.empty()){
		State *current = queue1.front();
		queue1.pop();
		//division and multiplication
		int divide = current->value / 3;
		int multiply = current->value * 2;

		if(current->value == input) {
			while (current != nullptr){
				vector1.push_back(current);
				current = current->parent;
			}
			break;
		}
		if (seen_states.find(divide) == seen_states.end()) {
			State *t = new State (divide," / 3", current);
			queue1.push(t);
			seen_states.insert(divide);

			}
		if (seen_states.find(multiply) == seen_states.end()) {
			State *t = new State (multiply, " x 2", current);
			queue1.push(t);
			seen_states.insert(multiply);

		}
	}
for_each(vector1.rbegin(), vector1.rend(), [](State *element){
	oss << element->expression;
});


return oss.str();
}


int main (int argc, char *argv[]){
	if(argc != 2) {
		cout << "Usage: ./mathexpr <non-negative integer>";
	} else {
		if (check(argv[1])){
					int number = atoi(argv[1]);
					cout << expression(number) << endl;
					} else  cout << "Error: Argument '" << argv[1] << "' is not a non-negative integer.";
	}
	return 0;
}
