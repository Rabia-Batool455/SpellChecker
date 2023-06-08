#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#RABIA BATOOL
using namespace std;

class treenode
{
public:
    treenode* l;
    treenode* r;
    string data;
    treenode* p;
};

class Spell
{
public:
    treenode* root;
    int total;
    
    int index = 0;
    list<string> sugglist; 

    Spell()
    {
        root = NULL;
        total = 0;
    }

    ////////// Inorder////
    // Left Root Right //

    void InorderTraverse(treenode* n = NULL)
    {
        if (root == NULL)
        {
            cout << "Tree is empty." << endl;
            return;
        }

        if (n == NULL)
        {
            n = root;
        }

        if (n->l != NULL)
        {
            InorderTraverse(n->l);
        }

        cout << n->data << " ";

        if (n->r != NULL)
        {
            InorderTraverse(n->r);
        }
    }

    ///insertion//

    void insert(string m)
    {
        treenode* a = new treenode();
        a->data = m;
        a->l = NULL;
        a->r = NULL;

        treenode* y = NULL;
        treenode* x = root;

        while (x != NULL)
        {
            y = x;
            if (x->data.compare(a->data) > 0)
                x = x->l;
            else
                x = x->r;
        }

        a->p = y;
        if (root == NULL)
            root = a;
        else if (y->data.compare(a->data) < 0)
            y->r = a;
        else
            y->l = a;
        total++;
    }

    //Seraching in tree

    bool search(string s)
    {
        treenode* t = root;
        int distance;

        while (t != NULL)
        {
            if (t->data.compare(s) == 0)
            {
               
                return true;
            }
            else if (t->data.compare(s) > 0)
            { //the value of the character of the first string is greater as compared to the second string input.
                t = t->l;
                if (t != NULL)
                {
                    distance = find_distance(t->data, s);
                    if (distance < 3)
                    {
                        sugglist.push_back(t->data);
                    }
                }
            }
            else
            {
                t = t->r;
                if (t != NULL)
                {
                    distance = find_distance(t->data, s);
                    if (distance < 3)
                    {
                        sugglist.push_back(t->data);
                    }
                }
            }
        }

        // Return false if the word is not found
        return false;
    }

    bool isCorrect(string word)
    {
        bool c = search(word);
        if (c == true)
        {
            cout << "Yippee Correct Word!!!!" << endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool ends_with(string main_str, string to_match)
    {
        if (main_str.size() < to_match.size())
        {
            return false;
        }
        return main_str.compare(main_str.size() - to_match.size(), to_match.size(), to_match) == 0;

}

void print_words(){
	list<string>::iterator it;
	if (sugglist.empty()==true){
		cout<<"No suggestions!!!! "<<endl;
	}else{
		cout<<"Suggestions are:!!!!! "<<endl;
	}
	
	for (it = sugglist.begin(); it != sugglist.end(); ++it) {
        cout << *it << " ";
    }
}

string rootWord(string word){
	transform(word.begin(),word.end(), word.begin(), ::tolower); //The transform() function in C++ sequentially applies an operation to the elements of an array(s) and then stores the result in another output array. 
	if (ends_with(word,"ing")){
		return string(word.begin(), word.end() - 3); //begin() function is a bidirectional iterator used to return an iterator pointing to the first element of the container. vector::end() function is a bidirectional iterator used to return an iterator pointing to the last element of the container.
	}else if (ends_with(word,"ies")){
		return string(word.begin(), word.end() - 3)+'y';
	}else if (ends_with(word,"es") || ends_with(word,"ed") || ends_with(word,"ly") ){
		return string(word.begin(), word.end() - 2);
	}else if (ends_with(word,"s")){
		return string(word.begin(), word.end() - 1);
	}else{
		return word;
	}
}

void write_in_correct(string word){
	ofstream correct("Right.txt", ios::app);
	if (!correct){
		cout<<"Ops !!!right words file not exist"<<endl;
	}else{
		correct<<word<<endl;
		cout<<"Yippee!!! Word written in File of Right Words"<<endl;
	}
	correct.close();
}

void write_in_incorrect(string word){
	ofstream incorrect("Ops!!! NotRight.txt", ios::app);
	if (!incorrect){
		cout<<"Ops!!! NotRight words file not exist"<<endl;
	}else{
		incorrect<<word<<endl;
		cout<<"Ops!!! Word written in File of NotRight Words"<<endl;
	}
	incorrect.close();
}

int find_distance(string a, string b){
	int distance = 0;
	int i = 0;
	int j = 0;
	while (i<a.length() && j<b.length()){
		if (a[i]==b[j]){
			i++;
			j++;
		}else{
			distance++;
			i++;
			j++;
		}
	}
	distance += max(b.length(), a.length()) - min(b.length(), a.length()); // add remaining characters in b to distance
	return distance;
}



  
};

int main(){
	            
            fstream file;
            Spell bst;
            file.open("Dict.txt", ios::in);
            if (!file){
            	cout<<"file does not exist!!!!!";
			}else{
				string line;
				while (getline(file, line)) {
    				int first_non_space = line.find_first_not_of(" \t\r\n"); 
    				int last_non_space = line.find_last_not_of(" \t\r\n");   
    				if (first_non_space == string::npos) {  
        			continue;
    				}
    				
    			string word = line.substr(first_non_space, last_non_space - first_non_space + 1);
    			bst.insert(word);
				}

			}
			

			string word;
			string* arr;
			cout<<"Hello EveryOne !!! Please Enter a word: "<<endl;
			cin>>word;
			
			if (bst.isCorrect(word)==true){
				bst.write_in_correct(word); //writing in file  RIGHT
			}else{
				cout<<"Oopsss !! Word not found"<<endl;
				string root = bst.rootWord(word);
				if (bst.isCorrect(root)){
					bst.write_in_correct(word);	 //writing in file RIGHT
				}else{
					cout<<"NotRight word!!!!!!!"<<endl;
					bst.write_in_incorrect(word); //writing in file NOTRIGHT
					bst.print_words();
					

				}
			}
			
	return 0;
}
