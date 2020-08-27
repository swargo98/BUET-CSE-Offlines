#include<iostream>
#include<cstring>

using namespace std;

class unit
{
protected:
    int range;
    int health;
    int damage;
    int cost;
    int stepsize;
    int return_coin;
    int position;
    int Round;
    char name[30];
    char shoot_type[30];
    char movement[30];
    int coin;
public:
    virtual void round(int k) {}
    virtual void cst_update(int k) {}
    virtual int getcost(){}
    virtual int getround(){}
    virtual int gethealth(){}
    virtual int getrange(){}
    virtual int getposition(){}
    virtual int getcoin(){}
    virtual char* getname(){}
    virtual char* getshoottype(){}
    virtual char* getmovement(){}
    virtual void decreaseround() {}
    virtual void increaseround() {}
};

class bowman: public unit
{
public:
    bowman(int k)
    {
        range=110;
        health=60;
        damage=10;
        cost=100;
        position=0;
        stepsize=0;
        return_coin=40;
        strcpy(shoot_type,"Basic Arrow");
        strcpy(movement,"Stationary");
        strcpy(name,"Bowman");
    }

    void round(int k)
    {
        health-=40;
        //if(health<=0) cost+=return_coin;
    }
    int getcost(){return cost;}
    int gethealth(){return health;}
    int getrange(){return range;}
    int getposition(){return position;}
    char* getname(){return name;}
    char* getshoottype(){return shoot_type;}
    char* getmovement(){return movement;}

};

class advanced_bowman: public unit
{
public:
    advanced_bowman(int k)
    {
        range=130;
        health=85;
        damage=15;
        cost=200;
        position=0;
        stepsize=0;
        return_coin=60;
        strcpy(shoot_type,"Canon");
        strcpy(movement,"Stationary");
        strcpy(name,"Advanced Bowman");
    }

    void round(int k)
    {
        health-=40;
        //if(health<=0) cost+=return_coin;
    }
    int getcost(){return cost;}
    int gethealth(){return health;}
    int getrange(){return range;}
    int getposition(){return position;}
    char* getname(){return name;}
    char* getshoottype(){return shoot_type;}
    char* getmovement(){return movement;}

};

class archer: public unit
{
public:
    archer(int k)
    {

        range=50;
        health=100;
        damage=25;
        cost=150;
        position=25;
        stepsize=25;
        return_coin=0;
        strcpy(shoot_type,"Advanced Arrow");
        strcpy(movement,"Running");
        strcpy(name,"Archer");

    }

    void round(int k)
    {
        health-=40;
        position+=25;
    }
    int getcost(){return cost;}
    int gethealth(){return health;}
    int getrange(){return range;}
    int getposition(){return position;}
    char* getname(){return name;}
    char* getshoottype(){return shoot_type;}
    char* getmovement(){return movement;}
};

class advanced_archer: public unit
{
public:
    advanced_archer(int k)
    {
        range=50;
        health=120;
        damage=50;
        cost=600;
        position=30;
        stepsize=30;
        return_coin=0;
        strcpy(shoot_type,"Improved Arrow");
        strcpy(movement,"Riding horse");
        strcpy(name,"Advanced Archer");
    }
    void round(int k)
    {
        health-=40;
        position+=30;
    }
    int gethealth(){return health;}
    int getcost(){return cost;}
    int getrange(){return range;}
    int getposition(){return position;}
    char* getname(){return name;}
    char* getshoottype(){return shoot_type;}
    char* getmovement(){return movement;}

};

class enemy_tower : public unit
{
public:
    enemy_tower(int k)
    {
        range=200;
        health=300;
        damage=40;
        cost=1100;
        coin=1600;
        stepsize=0;
        position=0;
        Round=1;
        return_coin=0;
        strcpy(shoot_type,"Fire Arrow");
        strcpy(movement,"Stationary");
        strcpy(name, "Enemy Tower");
    }

    void cst_update(int k)
    {
        if(k==1) coin-=150;
        else if(k==2) coin-=600;
        else if(k==3)
        {
            coin-=60;
            cout<<"Bowman Gave 40 coins while dying.\n";
        }
        else if(k==4)
        {
            coin-=140;
            cout<<"Bowman Gave 60 coins while dying.\n";

        }

    }

    void round(int k)
    {
        if(k==1)
        {
            health-=25;
        }

        else if(k==2)
        {
            health-=50;
        }
        else if(k==3)
        {
            health-=10;
        }
        else if(k==4)
        {
            health-=15;
        }

    }
    int gethealth(){return health;}
    int getrange(){return range;}
    int getposition(){return position;}
    char* getname(){return name;}
    char* getshoottype(){return shoot_type;}
    char* getmovement(){return movement;}
    int getcost(){return cost;}
    int getround(){return Round;}
    int getcoin(){return coin;}
    void decreaseround() {Round--;}
    void increaseround() {Round++;}


};


int main()
{
    unit *w;
    unit *v;
    v= new enemy_tower(0);
    int choice;
    while(1)
    {
        //int rnd=1;
        cout<<"Coin Remaining: "<<v->getcoin()<<endl;
        cout<<"Choose your option:"<<endl<<"1. Archer (Cost 150)"<<endl<<"2. Advanced Archer (Cost 600)"<<endl<<"3. Bowman (Cost 100)"<<endl<<"4. Advanced Bowman (Cost 200)"<<endl;

        cin>>choice;
        switch(choice)
        {
        case 1:
            w =  new archer(0);
            break;
        case 2:
            w = new advanced_archer(0);
            break;
        case 3:
            w =  new bowman(0);
            break;
        default :
            w = new advanced_bowman(0);
            break;
        }

        if(w->getcost()>v->getcoin())
        {
            cout<<"You Cannot afford them.\n";
            continue;
        }


        //cout<<"Round : "<<v->Round++<<endl;
        //cout<<w->name<<". Health: "<<w->health<<". "<<w->movement<<". Positioned at "<<w->position<<"."<<endl;
        //cout<<v->name<<". Health: "<<v->health<<". "<<v->name<<" is shooting "<<v->shoot_type<<".\n";

        while(1)
        {
            if(v->gethealth()<=0)
            {
                cout<<"Game Over!! You Won!!\n";
                return 0;
            }

            cout<<"Round : "<<v->getround()<<endl;
            v->increaseround();
            if(w->gethealth()>0)
            {

                cout<<w->getname()<<". Health: "<<w->gethealth()<<". "<<w->getmovement()<<". Positioned at "<<w->getposition()<<". ";
                if(w->getrange()>=(100-w->getposition()))
                {
                    cout<<w->getname()<<" is shooting "<<w->getshoottype()<<".\n";
                    v->round(choice);
                }
                else cout<<endl;
                cout<<v->getname()<<". Health: "<<v->gethealth()<<". ";
                if(v->gethealth()>0) cout<<v->getname()<<" is shooting "<<v->getshoottype()<<".\n";
                else cout<<endl;
                w->round(0);

            }
            else
            {
                cout<<w->getname()<<". Health: "<<w->gethealth()<<". Unit Died!!\n";
                v-> decreaseround();
                break;
            }

        }

        v -> cst_update(choice);
        if(v->getcoin()<100)
        {
            cout<<"Game over!! You are out of money.\n";
            return 0;
        }
    }

    return 0;
}


