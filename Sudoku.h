#include <iostream>
using namespace std;
class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		int fillIn(int n,int k);
		bool more_answer();
		void changeNum(int n1,int n2);
		void changeRow(int r1,int r2);
		void changeCol(int c1,int c2);
		void rotate(int r);
		void flip(int f);
		void transform();
		void change();
		void printOut();
	private:
		int sudoku[9][9];
};
