#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

int Event=0;
int score=0;
int XAxis=15;
int YAxis=7;
int speed=500;
float Dspeed=0.9;

int Over_page(){
    int i,j,k;
    string Over_text[13]={
        "",
        "@@@@@   @@@   @   @  @@@@@",
        "@      @   @  @@ @@  @",
        "@ @@@  @@@@@  @ @ @  @@@@@",
        "@   @  @   @  @   @  @",
        "@@@@@  @   @  @   @  @@@@@",
        "",
        "@@@@@  @   @  @@@@@  @@@@",
        "@   @  @   @  @      @   @",
        "@   @  @   @  @@@@@  @@@@",
        "@   @   @ @   @      @  @",
        "@@@@@    @    @@@@@  @   @",
        " Press enter to try again"
    };
    int keyboard=0;
    cout<<"\x1b[2J"<<flush;
    while(1){
        if(kbhit()){
            keyboard=getch();
            if(keyboard==13){
                return 2;
            }
            if(keyboard==27){
                return -1;
            }
        }
        cout<<"\x1b[H"<<flush;
        for(i=0;i<13;++i){
            cout<<Over_text[i];
            if(i==6){
                cout<<"        score:"<<score;
            }
            cout<<'\n';
        }
        cout<<flush;
    }
    return -1;
}

int Game_page(){
    
    int Level=1;
    char Map[YAxis][XAxis];
    char Footer[XAxis];
    int i,j,k;
    int keyboard=0;
    int prevK=0;
    int Direction=0;
    int prevTime=0;
    int curTime=0;
    bool pause=false;
    int fruit_x=-1, fruit_y=-1;
    bool found=false;
    bool addSnake=false;
    struct snake{
        int x=-1;
        int y=-1;
    };
    deque<snake> S;
    snake temp;
    for(i=0;i<3;++i){
        temp.x=XAxis/2;
        temp.y=YAxis/2+i;
        S.push_back(temp);
    }

    memset(Map,'.',sizeof(Map));
    memset(Footer,'_',sizeof(Footer));
    prevTime=curTime=clock();
    fruit_x=rand()%XAxis;
    while(fruit_x==XAxis/2) fruit_x=rand()%XAxis;
    fruit_y=rand()%YAxis;

    cout<<"\x1b[2J"<<flush;
    while(1){
        if(kbhit()){
            keyboard=getch();
            if(keyboard=='W'||keyboard=='w'){
                if(Direction!=2) Direction=0;
            }
            if(keyboard=='A'||keyboard=='a'){
                if(Direction!=1) Direction=3;
            }
            if(keyboard=='S'||keyboard=='s'){
                if(Direction!=0) Direction=2;
            }
            if(keyboard=='D'||keyboard=='d'){
                if(Direction!=3) Direction=1;
            }
            if(keyboard==' '){
                if(pause==true) pause=false;
                else pause=true;
            }
            if(keyboard==27){
                return -1;
            }
        }
        curTime=clock();
        if(curTime-prevTime>=speed && pause==false){
            prevTime=curTime;
            temp.x=S[0].x;
            temp.y=S[0].y;
            switch(Direction){
                case 0:
                    --temp.y;
                    if(temp.y==-1) temp.y=YAxis-1;
                    break;
                case 1:
                    ++temp.x;
                    if(temp.x==XAxis) temp.x=0;
                    break;
                case 2:
                    ++temp.y;
                    if(temp.y==YAxis) temp.y=0;
                    break;
                case 3:
                    --temp.x;
                    if(temp.x==-1) temp.x=XAxis-1;
                    break;
            }
            S.push_front(temp);
            if(addSnake==false){
                S.pop_back();
            }else{
                addSnake=false;
            }
        }

        for(i=1;i<S.size();++i){
            if(S[0].x==S[i].x && S[0].y==S[i].y){
                score=Level;
                return 3;
            }
        }
        
        if(fruit_x==(S[0].x) && fruit_y==(S[0].y)){
            addSnake=true;
            
            ++Level;
            speed*=Dspeed;
            found=false;
            while(found==false){
                fruit_x=rand()%XAxis;
                fruit_y=rand()%YAxis;
                found=true;
                for(snake x:S){
                    if(x.x==fruit_x){
                        found=false;
                        break;
                    }
                    if(x.y==fruit_y){
                        found=false;
                        break;
                    }
                }
            }
            
        }
        

        memset(Map,'.',sizeof(Map));
        for(i=0;i<S.size();++i){
            if(i==0) Map[S[i].y][S[i].x]='@';
            else Map[S[i].y][S[i].x]='#';
        }
        Map[fruit_y][fruit_x]='$';
        if(pause==true){
            Map[YAxis/2][XAxis/2-2]='P';
            Map[YAxis/2][XAxis/2-1]='A';
            Map[YAxis/2][XAxis/2]='U';
            Map[YAxis/2][XAxis/2+1]='S';
            Map[YAxis/2][XAxis/2+2]='E';
        }

        cout<<"\x1b[H"<<flush;

        cout<<'\n'<<"Level:"<<Level<<'\n';
        for(i=0;i<YAxis;++i){
            for(j=0;j<XAxis;++j){
                cout<<Map[i][j];
            }
            cout<<'\n';
        }
        if(keyboard==' ') cout<<"pause"<<Direction;
        else cout<<char(keyboard)<<Direction<<'\n';
        //cout<<char(keyboard)<<Direction<<'_'<<fruit_x<<'_'<<fruit_y<<'_'<<clock()<<flush;

        cout<<flush;
    }
    return -1;
}

int Title_page(){
    int i,j,k;
    string Title_text[13]={
        "",
        "@   @  @@@@@  @   @  @@@@   @   @",
        "@   @  @      @@  @  @   @  @   @",
        "@@@@@  @@@@@  @ @ @  @@@@    @@@",
        "@   @  @      @  @@  @  @     @",
        "@   @  @@@@@  @   @  @   @    @",
        "",
        "@@@@@  @   @   @@@   @   @  @@@@@",
        "@      @@  @  @   @  @  @   @",
        "@@@@@  @ @ @  @@@@@  @@@    @@@@@",
        "    @  @  @@  @   @  @  @   @",
        "@@@@@  @   @  @   @  @   @  @@@@@",
        "    press enter to start"
    };
    int keyboard=0;

    cout<<"\x1b[2J"<<flush;
    

    while(1){
        if(kbhit()){
            keyboard=getch();
            if(keyboard==13){
                return 4;
            }
            if(keyboard==27){
                return -1;
            }
        }
        cout<<"\x1b[H"<<flush;
        for(i=0;i<13;++i){
            cout<<Title_text[i]<<'\n';
        }
    }

    return -1;
}

int Mode_page(){
    int Mode=1;
    int i,j,k;
    string Mode_text[9]={
        "",
        "[@] Easy",
        "",
        "[_] Normal",
        "",
        "[_] Hard",
        "",
        "Select gamemode",
        ""
    };
    int keyboard=0;

    cout<<"\x1b[2J"<<flush;
    while(1){
        if(kbhit()){
            keyboard=getch();
            if(keyboard==13){
                switch(Mode){
                    case 1:
                        XAxis=15;
                        YAxis=7;
                        speed=700;
                        Dspeed=0.9;
                        break;
                    case 3:
                        XAxis=23;
                        YAxis=11;
                        speed=500;
                        Dspeed=0.8;
                        break;
                    case 5:
                        XAxis=31;
                        YAxis=17;
                        speed=400;
                        Dspeed=0.7;
                        break;
                }
                return 1;
            }
            if(keyboard==27){
                return -1;
            }
            if(keyboard=='W'||keyboard=='w'){
                Mode-=2;
                if(Mode==-1) Mode=5;
            }
            if(keyboard=='S'||keyboard=='s'){
                Mode+=2;
                if(Mode==7) Mode=1;
            }
        }
        for(i=1;i<7;i+=2){
            Mode_text[i][1]='_';
        }
        Mode_text[Mode][1]='@';
        cout<<"\x1b[H"<<flush;
        for(i=0;i<9;++i){
            cout<<Mode_text[i]<<'\n';
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(NULL));

    Event=2;
    while(1){
        switch(Event){
            case -1:
                exit(0);
                break;
            case 1:
                Event=Game_page();
                break;
            case 2:
                Event=Title_page();
                break;
            case 3:
                Event=Over_page();
                break;
            case 4:
                Event=Mode_page();
                break;
        }
    }

    return 0;
}