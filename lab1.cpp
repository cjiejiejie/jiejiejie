#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{	
	string text;
	vector<string> nums; 
	string filename;
	string keywords[33]={"auto", "break", "case", "char", "const", "continue",
		"default", "do", "double", "else", "enum", "extern", "float",
		"for", "foto", "if", "int", "long", "main", "register", "return", "short",
		"signed", "sizeof", "static", "struct", "switch", "typeof", "union",
		"unsigned", "void", "volatile", "while"};
	string ifelsekeywords[3]={"else if","if","else"};
	int keywordcount=0;	
	int switchcount=0;
	int casecount=0;
	int ifelsekeywordcount[3] = {0};
	vector<int> casenum;
	vector<string> ifelse; 
	int ifelsecount=0;
	int ifelseifcount=0;
	ifstream inFile;
	cout<<"Please enter the file name with suffix name(eg..cpp): ";
	cin>>filename;
	cout<<"Please choose the level(1,2,3,4): ";
	int level;
	cin>>level;
	inFile.open(filename.c_str());
	if(inFile.fail())
	{
		cout<<"The file was not successfully opend"<<endl;
		exit(1);
	}
	string buf;
	while (getline(inFile,buf))
	{
		int i = 0, j = 0;	
		while(i < int(buf.size()) && j < int(buf.size())) 
		{
			if (isalpha(buf[i])) 
			{
				if (!isalpha(buf[j] )) 
				{
					string s = buf.substr(i, j-i);
					nums.push_back(s);
					for (int k = 0; k < 33; k++) {
						if (s == keywords[k]) {
							keywordcount++;
						}
					}
					i = j+1;
					j = i;
				}
				else
					j++;
			}
			else
				{i++;j=i;}
		}
	}
	if(level>=1)
	cout<<"total number of keywords is: "<<keywordcount<<endl;
	if(level>1)
	{
		for(int i=0;i<int(nums.size());i++)
		{
			if(nums[i]=="switch")
			{
				switchcount+=1;
				//cout<<switchcount<<endl;
				for(int j=i+1;j<int(nums.size());j++)
				{
					//cout<<"nums[j] is now: "<<nums[j]<<endl;
					if (nums[j]=="case")
						casecount+=1;
						//cout<<"casecount is now: "<<casecount<<endl;}
					else if(nums[j]=="switch" )
					{
						i=j-1;
						casenum.push_back(casecount);
						casecount=0;
						break;
					}
					else if(j==int(nums.size()-1))
					{
						i=j;
						casenum.push_back(casecount);
						break;
					}
				}
			}
		} 
			cout<<"total number of switch is: "<<switchcount<<endl;
			cout<<"total number of case is: ";
			for(int i=0;i<int(casenum.size());i++)
			{
				cout<<casenum[i]<<"  ";
			}
			cout<<endl;
			inFile.close();
	}
	if(level>2)
		{
			inFile.open(filename.c_str());
			if(inFile.fail())
			{
				cout<<"The file was not successfully opend";
				exit(1);
			}
			while (getline(inFile,buf))
			{
				for(int i=0;i<3;i++)
				{
					if(int(buf.find(ifelsekeywords[i]))!=-1)
						ifelsekeywordcount[i]=1;
					else
						ifelsekeywordcount[i]=0;
				}	
				if(ifelsekeywordcount[1]==1 && ifelsekeywordcount[2]==1)
				{
					ifelsekeywordcount[0]=1;
					ifelsekeywordcount[1]=0;
					ifelsekeywordcount[2]=0;
				}	
				for(int i=0;i<3;i++)
				{
					if(ifelsekeywordcount[i]==1)
						ifelse.push_back(ifelsekeywords[i]);	
				}
			}
			for(int i=0;i<int(ifelse.size())-1;i++)
			{
				if(ifelse[i]=="if" && ifelse[i+1]=="else")
				{
					ifelsecount+=1;
				}
				if(ifelse[i]=="if" && ifelse[i+1]=="else")
				{
					ifelseifcount+=1;
				}	
			}
			if(level>2)
				cout<<"total number of if-else structure is: "<<ifelsecount<<endl;
			if(level>3)
				cout<<"total number of if-else if-else structure is: "<<ifelseifcount<<endl;
			//finish
		}
		return 0;
}

