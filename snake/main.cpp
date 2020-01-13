#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <string>
//#include <cmath>
//#include <string>
using namespace std;
enum dir{Top=1,Down,Right,Left};
void shift_r(int arr[],int size)
{
    for(int i=size-2;i>=0;i--)
    {
        arr[i+1] =arr[i];
    }
}

struct map
{
    int width,height,fruity,fruitx;
};
struct snake
{
    int heady,headx,tail_n;
    int tailx[50],taily[50];
    dir direction;
};
struct player
{
    string name;
    int score;
    bool lose;
};
map map1; snake snake1; player player1;

void generate_fruit()
{
    srand(time(NULL));
    map1.fruitx= rand() % (map1.width -2) +1;
    map1.fruity= rand() % (map1.height -2) +1;

}
void setup()
{
    map1.width=40;
    map1.height=20;
    generate_fruit();
    snake1.headx= map1.width /2;
    snake1.heady= map1.height /2;
    snake1.tail_n= 0;
    player1.score= 0;
    player1.lose = false;


}
void draw()
{
    system("cls");
    for(int y=0;y<map1.height;y++)
    {
        for(int x=0;x<map1.width;x++)
        {
            if(y==snake1.heady && x==snake1.headx)cout<<"O";
            if(y==map1.fruity && x==map1.fruitx)cout<<"$";
            if(y==0 || y==map1.height-1)cout<<"*";
            else if(x==0 || x==map1.width-1)cout<<"*";
            else {
                bool printed=false;
                for(int z=0;z<snake1.tail_n;z++)
                {
                    if(snake1.tailx[z]==x && snake1.taily[z]==y)
                        {cout<<"o";
                        printed=true;
                        break;}
                }
                if(!printed)cout<<" ";

                }

        }
        cout<<endl;
    }
    cout<<"Player Name : "<<player1.name<<endl<<"Player Score :"<<player1.score<<endl;
}
void input()
{
    if(_kbhit())
    {
        char c = _getch();
        switch (c)
        {
            case 'w': snake1.direction=Top;
            break;
            case 's': snake1.direction=Down;
            break;
            case 'a': snake1.direction=Left;
            break;
            case 'd': snake1.direction=Right;
            break;

            case 'x': exit(0);

        }
    }
}
void move()
{
    shift_r(snake1.tailx,50);
        shift_r(snake1.taily,50);
        snake1.tailx[0]=snake1.headx;
        snake1.taily[0]=snake1.heady;
    switch(snake1.direction)
    {
        case Top: snake1.heady--; break;
        case Down: snake1.heady++; break;
        case Right: snake1.headx++; break;
        case Left: snake1.headx--; break;

    }
        if(snake1.heady>=map1.height || snake1.heady<=0 || snake1.headx>=map1.width || snake1.headx<=0)
            {player1.lose=true;
            //exit(0);
            }
        if(snake1.heady==map1.fruity && snake1.headx==map1.fruitx)
        {
            generate_fruit();
            player1.score +=5;
            snake1.tail_n++;
        }


}

int main()
{

    cout<<"Enter Player Name :";
    cin>>player1.name;

    setup();
    while(!player1.lose)
    {
      draw();
      input();
      move();
      Sleep(50);

    }
    system("pause");


    return 0;
}
