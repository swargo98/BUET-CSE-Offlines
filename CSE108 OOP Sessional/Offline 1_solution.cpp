#include <iostream>
#include <cmath>
#include <sstream>
#include<cstdlib>
#include<cstdio>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3


string to_string(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        if(x<(GRIDSIZE-1)) x++;
        else cout<<"You cannot go out of the grid"<<endl;
    }

    void moveLeft()
    {
        if(x>0) x--;
        else cout<<"You cannot go out of the grid"<<endl;
    }

    void moveUp()
    {
        if(y<(GRIDSIZE-1))y++;
        else cout<<"You cannot go out of the grid"<<endl;
    }

    void moveDown()
    {
        if(y>0) y--;
        else cout<<"You cannot go out of the grid"<<endl;
    }

    bool isAdjacent(Position p)
    {
        if(p.x==this->x && (p.y+1==this->y || p.y-1==this->y)) return 1;
        if(p.y==this->y && (p.x+1==this->x || p.x-1==this->x)) return 1;
        return 0;
    }

    bool isSamePoint(Position p)
    {
        if(p.x==this->x && p.y==this->y ) return 1;
        return 0;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};


class WumpusWorld;

class Wumpus
{

    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
        int k=rand()%GRIDSIZE, l=rand()%GRIDSIZE;
        p=Position(k,l);
        killed=false;
    }

    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }

    friend WumpusWorld;

};


class Player
{

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player()
    {
        p=Position(0,0);
        total_shots=MAX_SHOTS;
        killed=false;
        direction=0;
    }

    void turnLeft()
    {
        direction=(direction+3)%4;
    }

    void turnRight()
    {
        direction=(direction+1)%4;
    }

    void moveForward()
    {
        if(direction==0) p.moveUp();
        else if(direction==1) p.moveRight();
        else if(direction==2) p.moveDown();
        else p.moveLeft();

    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }

    void kill()
    {
        killed = true;
    }

    string getPositionInfo()
    {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }

    string getDirectionInfo()
    {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }
    friend WumpusWorld;

};



class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Position gold_position;
    Position pit;
    bool ended;

public:

    WumpusWorld()
    {
        int k=rand()%GRIDSIZE, l=rand()%GRIDSIZE;
        gold_position=Position(k,l);
        int m=rand()%GRIDSIZE, n=rand()%GRIDSIZE;
        pit=Position(m,n);
    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        wumpus.p=Position(wumpus_x, wumpus_y);
        int k=rand()%GRIDSIZE, l=rand()%GRIDSIZE;
        gold_position=Position(k,l);
        int m=rand()%GRIDSIZE, n=rand()%GRIDSIZE;
        pit=Position(m,n);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        wumpus.p=Position(wumpus_x, wumpus_y);
        gold_position=Position(gold_x,gold_y);
        int m=rand()%GRIDSIZE, n=rand()%GRIDSIZE;
        pit=Position(m,n);

    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        wumpus.p=Position(wumpus_x, wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit=Position(pit_x,pit_y);
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
        if(player.total_shots==0) cout<<"No more shot left"<<endl;
        else
        {
            player.total_shots--;
            Position wmp=wumpus.getPosition();
            int wx=wmp.getX(), wy=wmp.getY();
            int px=player.p.getX(),py=player.p.getY(), pd=player.direction;
            if(pd==UP && px==wx && py<wy)
            {
                cout<<"WUMPUS KILLED"<<endl;
                wumpus.kill();
            }

            else if(pd==DOWN && px==wx && py>wy)
            {
                cout<<"WUMPUS KILLED"<<endl;
                wumpus.kill();
            }
            else if(pd==RIGHT && py==wy && px<wx)
            {
                cout<<"WUMPUS KILLED"<<endl;
                wumpus.kill();
            }
            else if(pd==LEFT && py==wy && px>wx)
            {
                cout<<"WUMPUS KILLED"<<endl;
                wumpus.kill();
            }
            else
            {
                cout<<"MISSED. Avilable Shots: "<<player.total_shots<<endl;
            }
        }

    }

    void showGameState()
    {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if (wumpus.killed==false && player.isAdjacent(wumpus.getPosition()))
        {
            cout << "stench!" << endl;
        }

        if (player.isAdjacent(pit))
        {
            cout << "Breeze!" << endl;
        }

        if (wumpus.killed==false && player.isSamePoint(wumpus.getPosition()))
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }
        if (player.isSamePoint(pit))
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }

        if (player.isSamePoint(gold_position))
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
    }

    bool isOver()
    {
        return ended;
    }

};


int main()
{
    // taking the six integers input from file
    int c,inp[6],cnt=0;
    //the six members in the array are the positions of wumpus,gold and pit respectively
    FILE *f;
    f=fopen("in.txt", "r");
    WumpusWorld w;
    while(!feof(f))
    {
        fscanf(f,"%d",&inp[cnt]);
        cnt++;
    }
    fclose(f);
    if(cnt==2) w=WumpusWorld(inp[0],inp[1]); //taking wumpus position as parameters
    else if(cnt==4) w=WumpusWorld(inp[0], inp[1], inp[2], inp[3]); //taking wumpus & gold position as parameters
    else if(cnt==6) w=WumpusWorld(inp[0], inp[1], inp[2], inp[3], inp[4], inp[5]); //taking wumpus & gold & pit position as parameters
    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}
