#include<iostream>
class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		void change();
	private:
		int map[9][9];
		int emp[9][9];
};
