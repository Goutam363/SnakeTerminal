//Hey! How are you?
#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
bool TeleMode=false;
int speed=50;
bool gameOver;
const int width=25;
const int height=25;
int x,y,fruitX,fruitY,score;
int tailX[(height-2)*(width-2)],tailY[(height-2)*(width-2)];
int nTail;
enum Direction{STOP=0,LEFT,RIGHT,UP,DOWN};
Direction dir;

void Setup()
{
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    if(fruitX==0)fruitX++;
    fruitY=rand()%height;
    if(fruitY==0)fruitY++;
    score=0;
    nTail=1;
}

void Draw()
{
    system("cls"); //"clear"
    for(int i=0;i<=height;i++)
    {
        for(int j=0;j<=width;j++)
        {
            if(i==0||i==height)
                cout<<'-';
            else if(j==0||j==width)
                cout<<'|';
            else if(i==y&&j==x)
                cout<<'0';
            else if(i==fruitY&&j==fruitX)
                cout<<'G';
            else
            {
                bool print=false;
                for(int k=0;k<nTail;k++)
                {
                    if(j==tailX[k]&&i==tailY[k])
                    {
                        cout<<'o';
                        print=true;
                    }
                }
                if(!print)
                    cout<<' ';
            }
        }
        cout<<endl;
    }
    cout<<"Score: "<<score<<endl;
}

void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                dir=LEFT;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'q':
                gameOver=true;
                break;
        }
    }
}

void Logic()
{
    int prevX=tailX[0],prevY=tailY[0];
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<nTail;i++)
    {
        int prev2X=tailX[i];
        int prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    if(TeleMode)
    {
        if(x<=0)
            x=width-1;
        else if(x>=width)
            x=1;
        if(y<=0)
            y=height-1;
        else if(y>=height)
            y=1;
    }
    else
        if(x<0||x>width||y<0||y>height)
        {
            gameOver=true;
            cout<<"Game Over!!!"<<endl;
        }

    for(int i=1;i<nTail;i++)
        if(x==tailX[i]&&y==tailY[i])
        {
            gameOver=true;
            cout<<"Game Over!!!"<<endl;
        }
    if(x==fruitX&&y==fruitY)
    {
        score+=10;
        fruitX=rand()%width;
        if(fruitX==0)fruitX++;
        fruitY=rand()%height;
        if(fruitY==0)fruitY++;
        nTail++;
    }
}

void About()
{
    system("cls");
    cout<<"Name: SNAKE TERMINAL"<<endl;
    cout<<"Version: 1.0.0"<<endl;
    cout<<"Release date: May 26, 2021"<<endl;
    cout<<"Creator: GOUTAM HALDER"<<endl;
    cout<<"https://www.goutam363.com"<<endl<<endl<<"\t";
    if(getchar())
        return;
}

void Display()
{
    system("cls");
    cout<<"---------------------------------------------------------*****************SNAKE TERMINAL*****************---------------------------------------------------------"<<endl<<endl<<endl;
    while(1)
    {
        cout<<endl<<"1.Play(A->Left | D->Right | W->Up | S->Down | Q->Quit)"<<endl<<"2.Teleportation-mode(default off)(0->off | 1->on)"<<endl<<"3.Set the game speed(default 50)(Increase->slow | Decrease->fast)"<<endl<<"4.About"<<endl<<"5.Quit"<<endl<<endl<<"\t";
        int ch;
        cin>>ch;
        switch (ch)
        {
            case 1:
                return;
                break;
            case 2:
                cout<<"Enter the mode: ";
                cin>>TeleMode;
                break;
            case 3:
                cout<<"Enter the speed: ";
                cin>>speed;
                break;
            case 4:
                About();
                break;
            case 5:
                exit(0);
                break;
            default:
                cout<<"Wrong input!!!"<<endl;
                break;
        }
    }
}

int main()
{
    while(1)
    {
        Display();
        while(1)
        {
            Setup();
            while(!gameOver)
            {
                Draw();
                Input();
                Logic();
                Sleep(speed);
            }
            char ch='n';
            cout<<"Play again?(y/n): ";
            cin>>ch;
            if(ch=='y'||ch=='Y')
                continue;
            else
                break;
        }
    }
    return 0;
}
