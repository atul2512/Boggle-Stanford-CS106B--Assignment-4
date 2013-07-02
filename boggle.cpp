/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 *Author:Atul Agrawal
 */
 
#include <cctype>
#include <iostream>
#include "simpio.h"
#include "gwindow.h"
#include "gboggle.h"
#include "grid.h"
#include "random.h"
#include "lexicon.h"
#include "set.h"
using namespace std;


const int kBoggleWindowWidth = 650;
const int kBoggleWindowHeight = 350;

const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

static void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

static bool responseIsAffirmative(const string& prompt) {
    while (true) {
        string answer = getLine(prompt);
        if (!answer.empty()) {
            switch (toupper(answer[0])) {
                case 'Y': return true;
                case 'N': return false;
            }
        }
        cout << "Please answer yes or no." << endl;
    }
}

void shuffleBoggle(Grid<string> &cube,Map<char,Set<poinT> > &map,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation,Grid<char> &face);
void initialiseBoggle(Grid<string> &cube);
void swap(int a,int b,int c,int d,Grid<string> &cube,Map<char,Set<poinT> > &map,Grid<char> &face);
bool check(string word,Lexicon &lex,Set<string> &correctAnswer,Map<poinT,Set<poinT> > &myNeighbour, Map<char,Set<poinT> > &getLocation);
int compareCoordinate(poinT a,poinT b);
bool checkIfBoggle(string soFar,string rest,Set<poinT> checked,poinT p,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation);
Map<poinT,Set<poinT> > mapNeighbour(int numRows,int numCols,Set<poinT> > &allPoint);
void startFindAllWords(Lexicon &lex,Set<string> correctAnswer,int numRows,int numCols,Grid<char> &face,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation);
void FindAllWords(string soFar,Set<sring> &word,Set<poinT> checked,Lexicon &lex,poinT p,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation,Grid<char> &face);

struct poinT{
  	int row;
		int column;
};

int main() {
   
   int numRows=4;int numCols=4;Lexicon lex("EnglishWords.dat");
   GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
   initGBoggle(gw);
   welcome();
   if (responseIsAffirmative("Do you need instructions? ")) {
      giveInstructions();
   }
   Set<poinT> > allPoint(compareCoordinate);
   Map<poinT,Set<poinT> > myNeighbour(compareCoordinate)=mapNeighbour(numRows,numCols,allPoint);
   myNeighbour.put(getPoint(-1,-1),allPoint);
   Grid<string> cube(numRows,numCols);
   Grid<char> face(numRows,numCols);
   drawBoard(numRows,numCols);
   initialiseBoggle(cube);
   
   while(true){
   Map<char,Set<poinT> > getLocation;
   shuffleBoggle(cube,getLocation);
   Set<string> correctAnswer;
   while(true){
		string word=getLine;
		if(word==""){
			startFindAllWords(lex,correctAnswer,numRows,numCols,face,myNeighbour,getLocation);
			if (responseIsAffirmative("Do you want to play again? "))
				break;
			else exit(0);
		}
		if(check(s,lex,correctAnswer,myNeighbour,getLocation));
			//Update Board of user sid;
   }
   }
   return 0;
}
/*
*wrapper function
*/
bool check(string word,Lexicon &lex,Set<string> &correctAnswer,Map<poinT,Set<poinT> > &myNeighbour, Map<char,Set<poinT> > &getLocation){
	if(!(correctAnswer.contains(word)) && lex.contains(s))
		string soFar="",rest=word;
		Set<poinT> checked(compareCoordinate);
		Set<poinT> isNeighbour(compareCoordinate);
		if(checkIfBoggle(soFar,rest,checked,getPoint(-1,-1),myNeighbour,getLocation)){
			correctAnswer.add(s);
			return true
		}
		return false;
}
/*Checking words enter by user
*Since the program has to go through a lot of recursion,care is taken that the computation inside recursion to
*be minimal.The code can be made simpler if we check neighbours here instead of calculating it outside.
*But it wil then consume more time.
*/
bool checkIfBoggle(string soFar,string rest,Set<poinT> checked,poinT p,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation){
	{
		if(rest==""){
			//Highlight all checked points
			return true;
		}
			char c=rest[0];
			Set<poinT> set(compareCoordinate);
			set=getLocation.get(c);
			set*(myNeighbour.get(p));          //intersect the two sets
			if(set.isEmpty())return false;
			else set-checked;					//set A - Set B
			if(set.size()==0) return false;
			else
				foreach(poinT p in set)
					if(checkIfBoggle(soFar+rest[0],rest.substr(1),checked.add(p),p,myNeighbour,getLocation)) return true;
			return false;
	}

/*
 *Wraper function for finding words by computer
 */
void startFindAllWords(Lexicon &lex,Set<string> correctAnswer,int numRows,int numCols,Grid<char> &face,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation){
		Set<string> word;
		foreach(string s in correctAnswer)
			word.add(s);
		Set<poinT> checked(compareCoordinate);
		for (int row = 0; row < numRows; row++)
			for (int col = 0; col < numCols; col++)
				FindAllWords("",word,checked,lex,getPoinT(numRows,numCols),myNeighbour,getLocation,face);
	}

/*
 *Find all word which are possible to construct with a char(located at poinT p) as starting word
 */
void FindAllWords(string soFar,Set<sring> &word,Set<poinT> checked,Lexicon &lex,poinT p,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation,Grid<char> &face){
		foreach(poinT p in myNeighbour.get(p)){
			string testString=soFar+face.get(p.row,p.column);
			if(lex.contains(testString) && !(word.contains(testString))
				word.add(testString);
			if(lex.containsPrefix(testString))
				FindAllWords(testString,word,checked.add(p),lex,p,myNeighbour,getLocation,face);
		}
}

void shuffleBoggle(Grid<string> &cube,Map<char,Set<poinT> > &map,Map<poinT,Set<poinT> > &myNeighbour,Map<char,Set<poinT> > &getLocation,Grid<char> &face{
	int numRows=cube.numRows();
	int numCols=cube.numCols();	
	int count=0;
	for (int row = 0; row < numRows; row++)
		for (int col = 0; col < numCols; col++)
			swap(row,col,randomInteger(row,numRows-1),randomInteger(col,numCols-1),cube,map,face);
}

/*
 *Swap tro cell location and update face and add map  character to its all possible location
 */
void swap(int a,int b,int c,int d,Grid<string> &cube,Map<char,Set<poinT> > &map,Grid<char> &face){
	string temp;
	temp=cube.get(a,b);
	cube.set(a,b,cube.get(c,d));
	cube.set(c,d,temp);
	labelCube(a,b,face.get(a,b));
	labelCube(c,d,face.get(c,d));
	char c1=(cube.get(a,b))[randomInteger(0,5)];
	char c2=(cube.get(c,d))[randomInteger(0,5)];
	face.set(a,b,c1);
	face.set(c,d,c2);
	if(map.containsKey(c1))
		map[c1].add(getPoinT(a,b));
	else {
		Set<poinT> set1(compareCoordinate);
		set1.add(getPoinT(a,b));
		map.put(c1,set1);
	}
	if(map.containsKey(c2))
		map[c2].add(getPoinT(c,d));
	else {
		Set<poinT> set2(compareCoordinate);
		set2.add(getPoinT(c,d));
		map.put(c2,set2);
	}
}
/*
 *Compare two point
 */
int compareCoordinate(poinT a,poinT b){
	if((a.row<b.column)) return -1;
	if(a.row>a.column) return +1
	if((a.row==b.row)&&(a.column==b.column)) return 0;
	return -1;	
}
/*
*Calculate Neighbour given a point
*
*/
Set<poinT> getNeighbour(poinT coordinate,int Row,int Col){
	Col=Col-1;
	Row=Row-1;
	row=coordinate.row;
	col=coordinate.column;
	Set<pointT> set(compareCoordinate);
	if(row-1>=0) set.add(getPoinT(row-1,Col));
	if(col-1>=0) set.add(getPoinT(row,col-1));
	if(row+1<=Row)set.add(getPoinT(row+1,col));
	if(col+1<=Col) set.add(getPoinT(row,col+1));
	if(row-1>=0&&col-1>=0) set.add(getPoinT(row-1,col-1));
	if(row-1>=0&&col+1<=Row) set.add(getPoinT(row-1,col+1));
	if(row+1>=0&&col-1>=0) set.add(getPoinT(row+1,col-1));
	if(row+1>=0&&col+1<=Row) set.add(getPoinT(row+1,col+1));
	return set;
}
/*
 *Return poinT struct given row and column
 */
poinT getPoinT(int row,int col){
	poinT a;
	a.row=row;
	a.column=col;
}
/*
*Map all the points to its neighbour
*/
Map<poinT,Set<poinT> > mapNeighbour(int numRows,int numCols,Set<poinT> > &allPoint){
	Map<poinT,Set<poinT> > a(compareCoordinate);
	for (int row = 0; row < numRows; row++){
		for (int col = 0; col < numCols; col++){
			poinT point=getPoinT(row,col);
			allPoint.add(point);
			a.put(point,getNeighbour(point,int numRows,int numCols);
		}
	}
	return a;
}


