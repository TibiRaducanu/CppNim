#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
using namespace std;

void Afisare(int n, int v[]){
    int max=0;
    for(int i=1;i<=n;i++){
        if(v[i]>max) max=v[i];
    }
    for(int j=1;j<=max;j++) cout<<"- ";
    cout<<"\n";
    for(int i=1;i<=n;i++){
        printf("Line %d: ",i);
        for(int j=1;j<=v[i];j++) cout<<"O ";
        cout<<"\n";
    }
    for(int j=1;j<=max;j++) cout<<"- ";
    cout<<"\n\n";
}

int CheckFinish(int n, int v[]){
    int One=0, OneLine, NrLines=0;
    for(int i=1;i<=n;i++){
        if(v[i]==1) One=1, OneLine=i;
        if(v[i]) NrLines++;
    }

    if(NrLines==1 and One==0){
        int l;
        for(int i=1;i<=n;i++){
            if(v[i]){
                l=i;
                break;
            }
        }

        int val=v[l]-1;
        if(val==1) printf("Computer has picked 1 stone from line %d\n",l);
        else printf("Computer has picked %d stones from line %d\n",val,l);
        v[l]-=val;
        Afisare(n,v);
        cout<<"Computer has won!\n";
        return 1;
    }
    if(NrLines==2 and One==1){
        int l;
        for(int i=1;i<=n;i++){
            if(v[i]>1){
                l=i;
                break;
            }
        }

        printf("Computer has picked %d stones from line %d\n",v[l],l);
        v[l]=0;
        Afisare(n,v);
        cout<<"Computer has won!\n";
        return 1;
    }
    return 0;
}

int main()
{
    int v[100], n, t=0, s=1, Xor, max;
    cout<<"Welcome to the NIM game!\n\n\n";

    while(t<1 or t>5){
        cout<<"Select the dificulty of the game, choosing between 1, 2, 3, 4 or 5:\n\n";
        cout<<"1. Easy\n";
        cout<<"2. Medium\n";
        cout<<"3. Hard\n";
        cout<<"4. Insane\n";
        cout<<"5. Random\n\n\n";
        cout<<"Insert the number here: ";
        cin>>t;

        if(t<1 or t>5) cout<<"Please insert a value between 1 and 5.\n\n";
    }

    /// Initialize random seed:
    srand (time(NULL));

    if(t==1){
        n=3;
        v[1]=1; v[2]=3; v[3]=5;
    }
    if(t==2){
        n=4;
        v[1]=1; v[2]=3; v[3]=5;
        v[4]=8;
    }
    if(t==3){
        n=5;
        v[1]=1; v[2]=3; v[3]=5;
        v[4]=7; v[5]=9;
    }
    if(t==4){
        n=6;
        v[1]=1; v[2]=3; v[3]=5;
        v[4]=7; v[5]=9; v[6]=11;
    }
    if(t==5){
        n=rand()%4+3;
        for(int i=1;i<=n;i++) v[i]=rand()%8+1;
        sort(v+1, v+n+1);
    }

    cout<<"\nThe Game Has Started!\n\n";
    cout<<"Rules:\n";
    cout<<"1. You can pick at least one stone at every step\n";
    cout<<"2. You can pick stones from only one line\n";
    cout<<"3. The player that picks the last stone loses\n\n";
    Afisare(n,v);


    while(s){

        int line;
        cout<<"Insert line: ";
        cin>>line;
        while(line<1 or line>n or v[line]==0){
            cout<<"Insert a valid line: ";
            cin>>line;
        }

        int stones;
        cout<<"Insert the number of stones that you want to pick: ";
        cin>>stones;
        while(stones<=0 or stones>v[line]){
            cout<<"Insert a valid number of stones: ";
            cin>>stones;
        }

        v[line]-=stones;
        s=Xor=max=0;
        int pos, PickedLine=0, StonesNumber=0;
        for(int i=1;i<=n;i++){
            s+=v[i];
            Xor^=v[i];
            if(v[i]>max) max=v[i], pos=i;
        }

        Afisare(n,v);

        if(s==0){
            cout<<"Computer has won!\n";
            break;
        }
        if(s==1){
            cout<<"You have won, congratulations!\n";
            break;
        }

        /// Computer is thinking
        Sleep(1000);
        cout<<"Thinking..\n";
        Sleep(1500);
        /// Computer is thinking

        /// Finish him
        //if(CheckFinish(n,v)) break;
        /// Finish him

        if(Xor==0){
            PickedLine=pos;
            StonesNumber=1;
            s--;
            v[pos]--;
        }
        else{
            /*int Bit=0, nr=0, CheckXor=1;
            for(int i=0;i<10;i++){
                if(((1<<i) & Xor) Bit=i;
            }
            nr=Xor-2*(Xor-(1<<Bit));

            int l;

            for(int i=1;i<=n;i++){
                if( ( v[i] & (1<<Bit) ) == (1<<Bit) ){
                    l=i;
                    break;
                }
            }*/

            int OneLines=0;
            for(int i=1;i<=n;i++){
                if(v[i]==1) OneLines++;
            }
            //printf("%d\n",OneLines);

            int XorS=0;
            for(int i=1;i<=n;i++){
                if(v[i]==0) continue;
                XorS=Xor^v[i];
                if(s-v[i]==OneLines){
                    if(OneLines%2==0){
                        PickedLine=i;
                        StonesNumber=v[i]-1;
                        //cout<<"MARIN PAR!!!!!\n";
                    }
                    else{
                        PickedLine=i;
                        StonesNumber=v[i];
                        //cout<<"MARIN ImPAR!!!!!\n";
                    }
                    break;
                }
                if(v[i]>=XorS){
                    PickedLine=i;
                    StonesNumber=v[i]-XorS;
                    break;
                }
            }

            v[PickedLine]-=StonesNumber;
            s-=StonesNumber;
        }
        if(s==0){
            cout<<"You have won, congratulations!\n";
            break;
        }

        if(StonesNumber==1) printf("The computer has picked 1 stone from line %d\n\n",PickedLine);
        else printf("The computer has picked %d stones from line %d\n\n",StonesNumber,PickedLine);

        Afisare(n,v);
    }
    return 0;
}
