#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"
using namespace std;
void Sudoku::giveQuestion(){
	int i;
	int Sudo[81]={0,0,0,0,0,0,6,8,0,0,0,0,0,7,3,0,0,9,3,0,9,0,0,0,0,4,5,4,9,0,0,0,0,0,0,0,8,0,3,0,5,0,9,0,2,0,0,0,0,0,0,0,3,6,9,6,0,0,0,0,3,0,8,7,0,0,6,8,0,0,0,0,0,2,8,0,0,0,0,0,0};
	for(i=0;i<81;i++){
		cout<<Sudo[i];
		if((i+1)%9==0)
			cout<<endl;
		else
			cout<<" ";
		}
}
void Sudoku::readIn(){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++)
			cin>>sudoku[i][j];
	}
}
void Sudoku::solve(){
	int i,j,k;
	if(more_answer())
		cout<<"2"<<endl;
	else{
		for(i=8;i>=0;i--){
			for(j=8;j>=0;j--){
				if(sudoku[i][j]==0)
					k=9*i+j;
			}
		}
		if(fillIn(0,k)==1){
			cout<<"1"<<endl;
			printOut();
		}
		else
			cout<<"0"<<endl;
	}
}
int Sudoku::fillIn(int n,int k){
	int i,j;
	int conflict,try_number;
	int row,col,block_row,block_col;
	if(n==81)
		return 1;
	row=n/9;
	col=n%9;
	block_row=row/3;
	block_col=col/3;
	if(sudoku[row][col]!=0)
		return fillIn(n+1,k);
	for(try_number=1;try_number<=9;try_number++){
		conflict=0;
		for(i=0;i<9&&!conflict;i++){
			if(((row!=i)&&(sudoku[i][col]==try_number))||((col!=i)&&(sudoku[row][i]==try_number)))
				conflict=1;
		}
		if(!conflict){
			for(i=0;i<3&&!conflict;i++){
				for(j=0;j<3&&!conflict;j++){
					if(sudoku[3*block_row+i][3*block_col+j]==try_number)
						conflict=1;
				}
			}
			if(!conflict){
				sudoku[row][col]=try_number;
				if(fillIn(n+1,k))
					return 1;
			}
		}
		if(conflict==1&&try_number==9&&n==k)
			return 0;
	}
	sudoku[row][col]=0;
	return 0;
}
bool Sudoku::more_answer(){
	int i,j;
	int count=0;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(sudoku[i][j]!=0)
				count++;
		}
	}
	if(count<17)
		return true;
	else
		return false;
}
void Sudoku::changeNum(int n1,int n2){
	int i,j,temp1,temp2;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(sudoku[i][j]==n1)
				temp1=j;
			if(sudoku[i][j]==n2)
				temp2=j;
		}
			sudoku[i][temp1]=n2;
			sudoku[i][temp2]=n1;
	}
}
void Sudoku::changeRow(int r1,int r2){
	int i,j,R1=3*r1,R2=3*r2;
	int temp[3][9];
	for(i=0;i<3;i++,R1++,R2++){
		for(j=0;j<9;j++){
			temp[i][j]=sudoku[R1][j];
			sudoku[R1][j]=sudoku[R2][j];
			sudoku[R2][j]=temp[i][j];
		}
	}
}
void Sudoku::changeCol(int c1,int c2){
	int i,j,C1=3*c1,C2=3*c2;
	int temp[9][3];
	for(j=0;j<3;j++,C1++,C2++){
		for(i=0;i<9;i++){
			temp[i][j]=sudoku[i][C1];
			sudoku[i][C1]=sudoku[i][C2];
			sudoku[i][C2]=temp[i][j];
		}
	}
}
void Sudoku::rotate(int r){
	int i,j,N=r%4;
	int temp[9][9];
	switch (N){
		case 1:
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					temp[i][j]=sudoku[i][j];
			}
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					sudoku[j][8-i]=temp[i][j];
			}
			break;
		case 2:
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					temp[i][j]=sudoku[i][j];
			}
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					sudoku[8-i][8-j]=temp[i][j];
			}
			break;
		case 3:
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					temp[i][j]=sudoku[i][j];
			}
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					sudoku[8-j][i]=temp[i][j];
			}
			break;
		default:
			return;
	}
}
void Sudoku::flip(int f){
	int i,j;
	int temp[9][9];
	if(f==0){
		for(i=0;i<9;i++){
			for(j=0;j<9;j++)
				temp[i][j]=sudoku[i][j];
		}
		for(i=0;i<9;i++){
			for(j=0;j<9;j++)
				sudoku[8-i][j]=temp[i][j];
		}
	}
	else{
		for(i=0;i<9;i++){
			for(j=0;j<9;j++)
				temp[i][j]=sudoku[i][j];
		}
		for(i=0;i<9;i++){
			for(j=0;j<9;j++)
				sudoku[i][8-j]=temp[i][j];
		}
	}
}
void Sudoku::transform(){
	readIn();
	change();
	printOut();
}
void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}
void Sudoku::printOut(){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			cout<<sudoku[i][j];
			if(j==8)
				cout<<endl;
			else
				cout<<" ";
		}
	}
}
