#include<iostream>
#include<cstdio>
#include<ctime>
#include<fstream>
#include"Sudoku.h"
using namespace std;
	void Sudoku::giveQuestion(){
			int  map[9][9]={8,0,0,0,0,0,0,0,0,
				   			0,0,3,6,0,0,0,0,0,
				   			0,7,0,0,9,0,2,0,0,
				 			0,5,0,0,0,7,0,0,0,
							0,0,0,0,4,5,7,0,0,
						    0,0,0,1,0,0,0,3,0,
						    0,0,1,0,0,0,0,6,8,
				 		    0,0,8,5,0,0,0,1,0,
				  			0,9,0,0,0,0,4,0,0,}; 
			int temp[9][9]={0};
			int chance=time(NULL);//做不同轉製機率 
			for(int notuse=0;notuse<10;notuse++){//作轉製的迴圈 
				chance+=time(NULL);//讓機率不會都一樣 
				if(chance%10<=1){//往上平移3 
//					cout<<",1\n";//try
					for(int i=0;i<9;i++){//
						for(int j=0;j<9;j++){//
							temp[i][j]=map[(i+3)%9][j];
						}
					}
					for(int i=0;i<9;i++){
						for(int j=0;j<9;j++){
							map[i][j]=temp[i][j];
						}
					}
				}
				else if(chance%10<=3 && chance>1){//往左3 
//					cout<<",2\n";//try
					for(int i=0;i<9;i++){//
						for(int j=0;j<9;j++){//
							temp[j][i]=map[j][(i+3)%9];
						}
					}
					for(int i=0;i<9;i++){
						for(int j=0;j<9;j++){
							map[i][j]=temp[i][j];
						}
					}
				}
				else if(chance%10<=5 && chance>3){  //往右轉90度 
//					cout<<",3\n";//try 
					for(int i=0;i<9;i++){
						for(int j=0;j<9;j++){
							temp[i][j]=map[8-j][i];
						}
					} 
					for(int i=0;i<9;i++){
						for(int j=0;j<9;j++){
							map[i][j]=temp[i][j];
						}
					}
				}
				else if(chance%10<=7 && chance>5){
//					cout<<",4\n";//try 
					int flip=time(NULL)%2;
					if(flip==0){//往左翻 
//						cout<<"flip is 0"<<endl;//try
						for(int i=0;i<9;i++){
							for(int j=0;j<9;j++){
								temp[i][j]=map[i][8-j];
							}
						}
					}
					else if(flip==1){//往上翻 
//						cout<<"flip is 1"<<endl;//try
						for(int i=0;i<9;i++){
							for(int j=0;j<9;j++){
								temp[i][j]=map[8-i][j];
							}
						}						
					}
					for(int i=0;i<9;i++){
						for(int j=0;j<9;j++){
							map[i][j]=temp[i][j];
						}
					}
				}
				else if(chance%10<=9 && chance>7){//兩數字交換 
//					cout<<",5\n";//try 
					int a=0;
					int b=0;
					int add=0;
					while(a==b){
						add+=1;
						a=(time(NULL)*chance+add)%9+1;
						b=(chance+a-add)%9+1;
					}
//					cout<<"the a , b is"<<a<<","<<b<<endl;//try
					for(int i=0;i<9;i++){
						for(int j=0;j<9;j++){
							if(map[i][j]==a)map[i][j]=b;
							else if(map[i][j]==b)map[i][j]=a;
						}
					}
				} 
			}
			for(int i=0;i<9;i++){//印出 
				for(int j=0;j<9;j++){
					cout<<map[i][j]<<" ";
				}
				cout<<"\n";
			}		
	}
	void Sudoku::readIn(){
/*			int name;
			ifstream file("high.txt",ios::in);
			if(!file){
				cerr<<"Failed opening"<<endl;
			}
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					file>>name;
					map[i][j]=name;
				}
			}*/
/*			ifstream file("a.txt",ios::in);
			if(!file){
				cerr<<"Failed opening"<<endl;
			}*/
			int name;
			for(int i=0;i<9;i++){ 
				for(int j=0;j<9;j++){
//					file>>name;
					cin>>name;
					map[i][j]=name;
				}
			}
//			cout<<"in finish";//try 
	}
		int solve2(int map[9][9],int &countforanswer,int tmp[9][9]){	
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					int number[10]={0};//看那些數字不能填 
					if(map[i][j]==0){
						for(int k=0;k<9;k++){
							if(map[i][k]!=0){//看那一row有哪些數字了 
								number[map[i][k]]=1;
							}
							if(map[k][j]!=0){//看那一colume有哪些數字了 
								number[map[k][j]]=1;
							} 
						}
						if(i>=0 && i<=2 && j>=0 && j<=2){
//							cout<<"1,";//try
							for(int k=0;k<=2;k++){
								for(int l=0;l<=2;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}
						else if(i>=0 && i<=2 && j>=3 && j<=5){
//							cout<<"2,";//try
							for(int k=0;k<=2;k++){
								for(int l=3;l<=5;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}
						else if(i<=2 && j>=6 && j<=8){
//							cout<<"3,";//try
							for(int k=0;k<=2;k++){
								for(int l=6;l<=8;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}
						else if(i>=3 && i<=5 && j>=0 && j<=2){
//							cout<<"4,";//try
							for(int k=3;k<=5;k++){
								for(int l=0;l<=2;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}
						else if(i>=3 && i<=5 && j>=3 && j<=5){
//							cout<<"5,";//try
							for(int k=3;k<=5;k++){
								for(int l=3;l<=5;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}	
						else if(i>=3 && i<=5 && j>=6 && j<=8){
//							cout<<"6,";//try
							for(int k=3;k<=5;k++){
								for(int l=6;l<=8;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}	
						else if(i>=6 && i<=8 && j>=0 && j<=2){
//							cout<<"7,";//try
							for(int k=6;k<=8;k++){
								for(int l=0;l<=2;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}	
						else if(i>=6 && i<=8 && j>=3 && j<=5){
//							cout<<"8,";//try
							for(int k=6;k<=8;k++){
								for(int l=3;l<=5;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}
						else if(i>=6 && i<=8 && j>=6 && j<=8){
//							cout<<"9,";//try
							for(int k=6;k<=8;k++){
								for(int l=6;l<=8;l++){
									if(map[k][l]!=0){
										number[map[k][l]]=1;
									}
								}
							}
						}
						//在這run recursive	
						int sum=0;//算~如果1~9都有數字就return 
						int watch=0;
						int sumforreturn=0;
						for(int k=1;k<10;k++){
							sum+=number[k];
						}
						if(sum==9)return(-1);
						
						for(int k=1;k<10;k++){
							if(number[k]==0){
//								cout<<".";//try 
								map[i][j]=k;
								watch=solve2(map,countforanswer,tmp);
								if(watch==1)return(1); 
								sumforreturn+=watch;
							}
						}//cout<<"\n";//try	
						if(sumforreturn==(sum-9)){
							map[i][j]=0;
							return(-1);
						}																						
					} //if(map[i][j]==0)
				}//for(int j=0;j<9;j++)
			}//for(int i=0;i<9;i++)	
			if(countforanswer==0){
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						tmp[i][j]=map[i][j];
					}
				}
				countforanswer+=1;
				return(-1);						
			}
			if(countforanswer==1){
				countforanswer+=1;
				cout<<"2";
				return(1);//多解 
			}
		}
		void Sudoku::solve(){	
			int countforanswer=0;	
			int tmp[9][9]={0};	
			int howmany=0;
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					if(map[i][j]!=0){
						howmany+=1;
					}
				}
			}
			if(howmany<=9){
				int number[10]={0};
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						for(int k=0;k<9;k++){
							if(map[i][k]!=0){//看那一row有哪些數字了 
								if(number[map[i][k]]==0){
									number[map[i][k]]=1;
								}
								else if(number[map[i][k]]==1){
									cout<<"0";
									return;
								}
							}
							if(map[k][j]!=0){//看那一colume有哪些數字了 
								if(number[map[k][j]]==0){
									number[map[k][j]]=1;
								}
								else if(number[map[k][j]]==1){
									cout<<"0";
									return;
								}
							} 
						}
					}
				}
				cout<<"2";
				return;
			}
			solve2(map,countforanswer,tmp);	
//			cout<<"\n"<<countforanswer;	//try	
			if(countforanswer==0){
				cout<<"0";
			}
			if(countforanswer==1){
//				cout<<"\nfinish"<<"\n";//try
				cout<<"1";
				cout<<"\n";//最後印出 
				for(int i=0;i<9;i++){//try
					for(int j=0;j<9;j++){//try
						cout<<tmp[i][j]<<" ";//try
					}//try
					cout<<"\n";//try
				}//try
			}
		}
		void Sudoku::flip(int n){
			int temp[9][9]={0};
			if(n==0){//向上翻 
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						temp[i][j]=map[8-i][j];
					}
				}
			}
			else if(n==1){//向左翻 
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						temp[i][j]=map[i][8-j];
					}
				}
			}
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					map[i][j]=temp[i][j];
				}
			}
		}
		void Sudoku::rotate(int n){
//			cout<<"\n the rotate is "<<n<<"\n";//try
			int temp[9][9]={0};
			int number=n%4;
			for(int k=0;k<number;k++){
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						temp[i][j]=map[8-j][i];
					}
				}
			
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						map[i][j]=temp[i][j];
					}
				}
			}
		}
		void Sudoku::changeCol(int a,int b){
			int temp[9][9]={0};
			if((a==0 && b==1) || (a==1 && b==0)){
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						if(j>=0 && j<=2){
							temp[i][j]=map[i][j+3];
						}
						else if(j<=5 && j>=3){
							temp[i][j]=map[i][j-3];
						}
						else temp[i][j]=map[i][j];
					}
				}
			}
			else if((a==0 && b==2) || (a==2 && b==0)){
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						if(j>=0 && j<=2){
							temp[i][j]=map[i][j+6];
						}
						else if(j<=8 && j>=6){
							temp[i][j]=map[i][j-6];
						}
						else temp[i][j]=map[i][j];
					}
				}				
			}
			else if((a==1 && b==2) || (a==2 && b==1)){
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						if(j>=3 && j<=5){
							temp[i][j]=map[i][j+3];
						}
						else if(j<=8 && j>=6){
							temp[i][j]=map[i][j-3];
						}
						else temp[i][j]=map[i][j];
					}
				}				
			}
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					map[i][j]=temp[i][j];
				}
			}				
		}
		void Sudoku::changeRow(int a, int b){
			int temp[9][9]={0};
			if((a==0 && b==1) || (a==1 && b==0)){
//				cout<<"0,1";//try
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						if(i>=0 && i<=2){
							temp[i][j]=map[i+3][j];
						}
						else if(i<=5 && i>=3){
							temp[i][j]=map[i-3][j];
						}
						else temp[i][j]=map[i][j];
					}
				}
			}
			else if((a==0 && b==2) || (a==2 && b==0)){
//				cout<<"0,2";//try
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						if(i>=0 && i<=2){
							temp[i][j]=map[i+6][j];
						}
						else if(i<=8 && i>=6){
							temp[i][j]=map[i-6][j];
						}
						else temp[i][j]=map[i][j];
					}
				}				
			}
			else if((a==1 && b==2) || (a==2 && b==1)){
//				cout<<"1,2";//try
				for(int i=0;i<9;i++){
					for(int j=0;j<9;j++){
						if(i>=3 && i<=5){
							temp[i][j]=map[i+3][j];
						}
						else if(i<=8 && i>=6){
							temp[i][j]=map[i-3][j];
						}
						else temp[i][j]=map[i][j];
					}
				}				
			}
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					map[i][j]=temp[i][j];
				}
			}			
		}
		void Sudoku::changeNum(int a,int b){
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					if(map[i][j]==a)map[i][j]=b;
					else if(map[i][j]==b)map[i][j]=a;
				}
			}
		}
		void Sudoku::change(){
			int a=0,b=0;
			while(a==b){
				a=((time(NULL)%100)*(time(NULL)%100))%9+1;
				b=(time(NULL)+time(NULL))%9+1;
			}
//			cout<<"changenum is"<<a<<","<<b;//try
			changeNum(a,b);//-------------------------------------------------------
			a=0;b=0;
			while(a==b){
				a=((time(NULL)%100)*(time(NULL)%100))%3;
				b=(time(NULL)+time(NULL))%3;				
			}
//			cout<<"\nchangerow is"<<a<<","<<b;//try
			changeRow(a,b);//---------------------------------------------------------
			a=0;b=0;//cout<<a<<","<<b;//try
			while(a==b){
				a=((time(NULL)%100)*8)%3;
				b=(time(NULL)+a)%3;				
			}
//			cout<<"\nchange col is "<<a<<","<<b;//try	
			changeCol(a,b);//------------------------------------------------------
			a=time(NULL)%101;
//			cout<<"\nrotate is "<<a;//try
			rotate(a);//-----------------------------------------		
			b=time(NULL)%2;
//			cout<<"\nflip is "<<b;//try
			flip(b); //------------------------------------------ 
		}
		void Sudoku::transform(){
//			readIn();
			change();
			//printtout
			cout<<"\n";//try
			for(int i=0;i<9;i++){//try
				for(int j=0;j<9;j++){//try
					cout<<map[i][j]<<" ";//try
				}//try
				cout<<"\n";//try
			}//try

		}

/*	int main(){
		Sudoku ss;
//		ss.giveQuestion();
		ss.readIn();
		ss.solve();
//		ss.transform();
		return(0);
	}*/
