#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
#include <iomanip>
#include <math.h>
using namespace std;



int main(int argc, char **argv)
{
    
    vector < vector<int> > col,row,temp,parentY,parentX;
    vector<int> reverseX,reverseY;
    if(argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        system("pause");
        exit(1);
    }
    
    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    if(!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }
    
    // parse the input file
    cout << "======================" << endl;
    cout << "        Parser        " << endl;
    cout << "======================" << endl;
    
    char buffer[100];
    int count = 0 ,now = 0;
    int grid = 0,capacity = 0,numnet = 0,tempX = 0,tempY = 0;
    for(int i = 0; i <=7 ;++i)
    {
        fin >> buffer;
        if(buffer[0]<=57&&buffer[0]>=48)
        {
            switch(count)
            {
                case 0 :
                    grid = atoi(buffer);
                    break;
                case 2 :
                    capacity = atoi(buffer);
                    break;
                case 3 :
                    numnet = atoi(buffer);
                    break;
            }
            ++count;
        }
        
    }
    
    
    col.resize(grid);
    for(int i=0; i < grid; ++i){
        col[i].resize(grid);
    }
    
    row.resize(grid);
    for(int i=0; i < grid; ++i){
        row[i].resize(grid);
    }
    temp.clear();
    temp.resize(grid+1);
    for(int t = 0; t <= grid ; ++t)
    {
        temp[t].resize(grid+1);
    }
    int Xs,Ys,Xt,Yd,counter;
    // open the output file
    fstream fout;
    fout.open(argv[2],fstream::out);
    if(!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
        exit(1);
    }
    
    for(int i = 0; i < numnet ; ++i)
    {
        fin >> buffer;
        now = atoi(buffer);
        fin >> buffer;
        Xs = atoi(buffer);
        fin >> buffer;
        Ys= atoi(buffer);
        fin >> buffer;
        Xt = atoi(buffer);
        fin >> buffer;
        Yd = atoi(buffer);
        counter =  abs(Xt-Xs)+abs(Yd-Ys);
        parentY.clear();
        parentX.clear();
        reverseY.clear();
        reverseX.clear();

        parentX.resize(grid);
        parentY.resize(grid);
        reverseX.resize(counter+1);
        reverseY.resize(counter+1);
        fout<<now<<" "<<counter<<endl;
        for(int h=0; h < grid; ++h)
        {
            parentX[h].resize(grid);
            parentY[h].resize(grid);
        }
        for(int a = 0; a < grid ; ++a)
        {
            for(int b = 0; b< grid;++b)
            {
                if(b == Xs && a == Ys)
                {
                    parentX[b][a]=Xs;
                    parentY[b][a]=Ys;
                }
                else
                {
                    parentX[b][a]=0;
                    parentY[b][a]=0;
                }
                
            }
        }
        for(int a = 0; a < grid ; ++a)
        {
            for(int b = 0; b< grid;++b)
            {
                if(a ==Xs && b ==Ys)
                {
                    temp[a][b] = 0;
                }
                else{
                    temp[a][b] = 1e9;
                }
                
            }
        }
        
        if (Xt >= Xs  && Yd >= Ys)
        {
            for(int i = Xs; i <= Xt ; ++i)
            {
                for(int j = Ys; j <= Yd;++j)
                {
                    if(i == Xt && j == Yd)
                    {
                        reverseX[0] = Xt;
                        reverseY[0] = Yd;
                        for(int k = 1; k <= counter ;++k)
                        {
                            tempX = Xt;
                            tempY = Yd;
                            reverseX[k] = parentX[Xt][Yd];
                            reverseY[k] = parentY[Xt][Yd];
                            Yd = parentY[tempX][tempY];
                            Xt = parentX[tempX][tempY];
                        }
                        
                    }
                    else if( j == Yd)
                    {
                        if( temp[i+1][j] > temp[i][j] + row[i][j] )
                        {
                            temp[i+1][j] = temp[i][j] + row[i][j];
                            parentX[i+1][j] = i;
                            parentY[i+1][j] = j;
                        }
                    }
                    else if ( i == Xt)
                    {
                        if( temp[i][j+1] > temp[i][j] + col[i][j] )
                        {
                            temp[i][j+1] = temp[i][j] + col[i][j];
                            
                            parentX[i][j+1] = i;
                            parentY[i][j+1] = j;
                        }
                    }
                    else
                    {
                        
                        if( temp[i+1][j] > temp[i][j] + row[i][j] )
                        {
                            temp[i+1][j] = temp[i][j] + row[i][j];
                            
                            parentX[i+1][j] = i;
                            parentY[i+1][j] = j;
                        }
                        if( temp[i][j+1] > temp[i][j] + col[i][j] )
                        {
                            temp[i][j+1] = temp[i][j] + col[i][j];
                            
                            parentX[i][j+1] = i;
                            parentY[i][j+1] = j;
                        }
                        
                    }
                    
                }
            }
            
        }
        else if (Xt >= Xs && Yd <= Ys)
        {
            for(int i = Xs; i <= Xt ; ++i)
            {
                for(int j = Ys; j>= Yd;--j)
                {
                    if(i == Xt && j == Yd)
                    {
                        
                        reverseX[0] = Xt;
                        reverseY[0] = Yd;
                        for(int k = 1; k <= counter ;++k)
                        {
                            tempX = Xt;
                            tempY = Yd;
                            reverseX[k] = parentX[Xt][Yd];
                            reverseY[k] = parentY[Xt][Yd];
                            Yd = parentY[tempX][tempY];
                            Xt = parentX[tempX][tempY];
                            
                            
                            
                        }
                        
                    }
                    else if( j == Yd)
                    {
                        if( temp[i+1][j] > temp[i][j] + row[i][j] )
                        {
                            temp[i+1][j] = temp[i][j] + row[i][j];
                            parentX[i+1][j] = i;
                            parentY[i+1][j] = j;
                        }
                    }
                    else if ( i == Xt)
                    {
                        if( temp[i][j-1] > temp[i][j] + col[i][j-1] )
                        {
                            temp[i][j-1] = temp[i][j] + col[i][j-1];
                            parentX[i][j-1] = i;
                            parentY[i][j-1] = j;
                        }
                    }
                    else
                    {
                        if( temp[i+1][j] > temp[i][j] + row[i][j] )
                        {
                            temp[i+1][j] = temp[i][j] + row[i][j];
                            
                            parentX[i+1][j] = i;
                            parentY[i+1][j] = j;
                        }
                        if( temp[i][j-1] > temp[i][j] + col[i][j-1] )
                        {
                            temp[i][j-1] = temp[i][j] + col[i][j-1];
                            
                            parentX[i][j-1] = i;
                            parentY[i][j-1] = j;
                        }
                        
                    }
                    
                }
            }
        }
        else if (Xt <= Xs && Yd >= Ys)
        {
            for(int i = Xs; i >= Xt ; --i)
            {
                for(int j = Ys; j<= Yd;++j)
                {
                    if(i == Xt && j == Yd)
                    {                       
                        reverseX[0] = Xt;
                        reverseY[0] = Yd;                       
                        for(int k = 1; k <= counter ;++k)
                        {
                            tempX = Xt;
                            tempY = Yd;
                            reverseX[k] = parentX[Xt][Yd];
                            reverseY[k] = parentY[Xt][Yd];
                            Yd = parentY[tempX][tempY];
                            Xt = parentX[tempX][tempY];    
                        }
                        
                    }
                    else if( j == Yd)
                    {
                        if( temp[i-1][j] > temp[i][j] + row[i-1][j] )
                        {
                            temp[i-1][j] = temp[i][j] + row[i-1][j];
                            
                            parentX[i-1][j] = i;
                            parentY[i-1][j] = j;
                        }	
                    }
                    else if ( i == Xt)
                    {
                        if( temp[i][j+1] > temp[i][j] + col[i][j] )
                        {
                            temp[i][j+1] = temp[i][j] + col[i][j];
                            
                            parentX[i][j+1] = i;
                            parentY[i][j+1] = j;
                        }
                    }
                    else 
                    {
                        
                        if( temp[i-1][j] > temp[i][j] + row[i-1][j] )
                        {
                            temp[i-1][j] = temp[i][j] + row[i-1][j];
                            
                            parentX[i-1][j] = i;
                            parentY[i-1][j] = j;
                        }	
                        if( temp[i][j+1] > temp[i][j] + col[i][j] )
                        {
                            temp[i][j+1] = temp[i][j] + col[i][j];
                            
                            parentX[i][j+1] = i;
                            parentY[i][j+1] = j;
                        }
                        
                    }
                    
                }
            }
        }
        else if (Xt <= Xs && Yd <= Ys)
        {
            for(int i = Xs; i >= Xt ; --i)
            {
                for(int j = Ys; j>= Yd;--j)
                {
                    if(i == Xt && j == Yd)
                    {
                        
                        reverseX[0] = Xt;
                        reverseY[0] = Yd;
                        for(int k = 1; k <= counter ;++k)
                        {
                            tempX = Xt;
                            tempY = Yd;
                            reverseX[k] = parentX[Xt][Yd];
                            reverseY[k] = parentY[Xt][Yd];
                            Yd = parentY[tempX][tempY];
                            Xt = parentX[tempX][tempY];
                            
                        }
                    }
                    else if( j == Yd)
                    {
                        if( temp[i-1][j] > temp[i][j] + row[i-1][j] )
                        {
                            temp[i-1][j] = temp[i][j] + row[i-1][j];
                            parentX[i-1][j] = i;
                            parentY[i-1][j] = j;
                        }	
                    }
                    else if ( i == Xt)
                    {
                        if( temp[i][j-1] > temp[i][j] + col[i][j-1] )
                        {
                            temp[i][j-1] = temp[i][j] + col[i][j-1];								
                            parentX[i][j-1] = i;
                            parentY[i][j-1] = j;
                        }
                    }
                    else 
                    {
                        
                        if( temp[i-1][j] > temp[i][j] + row[i-1][j] )
                        {
                            temp[i-1][j] = temp[i][j] + row[i-1][j];								
                            parentX[i-1][j] = i;
                            parentY[i-1][j] = j;
                        }
                        if( temp[i][j-1] > temp[i][j] + col[i][j-1] )
                        {
                            temp[i][j-1] = temp[i][j] + col[i][j-1];		
                            parentX[i][j-1] = i;
                            parentY[i][j-1] = j;
                        }
                        
                    }
                    
                }
            }
        }
        for( int p = counter; p>0;--p)
		{
            fout << reverseX[p] <<" "<<reverseY[p]<<" "<<reverseX[p-1] <<" "<<reverseY[p-1]<<endl;
        }        
        
        for(int e = 0; e < counter; ++e)
        {
            
            if( reverseX[e+1] > reverseX[e])
            {
            	if(row[reverseX[e]][reverseY[e]] >= capacity - 1)
            	row[reverseX[e]][reverseY[e]] = row[reverseX[e]][reverseY[e]] + 1e3;
            	else
                ++row[reverseX[e]][reverseY[e]];
            }
            else if (reverseX[e+1] < reverseX[e])
            {
            	if(row[reverseX[e]-1][reverseY[e]] >= capacity - 1)
            	row[reverseX[e]-1][reverseY[e]] = row[reverseX[e]-1][reverseY[e]] + 1e3;
            	else
                ++row[reverseX[e]-1][reverseY[e]];
            }
            else if (reverseY[e+1] > reverseY[e])
            {
            	if(col[reverseX[e]][reverseY[e]] >= capacity - 1)
            	col[reverseX[e]][reverseY[e]] = col[reverseX[e]][reverseY[e]] + 1e3;
            	else
                ++col[reverseX[e]][reverseY[e]];
            }
            else if( reverseY[e+1] < reverseY[e] )
            {
            	if(col[reverseX[e]][reverseY[e]-1] >= capacity - 1)
            	col[reverseX[e]][reverseY[e]-1] = col[reverseX[e]][reverseY[e]-1] + 1e3;
            	else
                ++col[reverseX[e]][reverseY[e]-1];
            }	
            
        }
        

        
        
    }


    
    
    
    
    
    
    
    system("pause");
//        return 0;
}


