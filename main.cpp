#include<bits/stdc++.h>
using namespace std;


int n,p;
vector<int> obstacle,k;
vector<pair<int,int>> loc;
vector<string> s;





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////           DFS              ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////




//f is flag to know the rows column and diagonal to place queen

void depthfirst(vector<vector<string>> &v, vector<int> f, int row, int c){
    if(p==0){
        v.push_back(s);
        return;
    }
    if(row==n)
        return;
    if(p>n-row+k[row])
        return;
    for(int col=c;col<n;col++){
            
        if(v.size()==1)return;
        if(s[row][col]=='2'){
            f[row]=f[n+col] = f[n+n+row+col] = f[5*n-2+col-row] =1; 
            continue;
        }
        if(f[row] && f[n+col] && f[n+n+row+col] && f[5*n-2+col-row]){
            f[row]=f[n+col] = f[n+n+row+col] = f[5*n-2+col-row] =0;
            s[row][col]='1';
            p--;
                // for(int j=0;j<n;j++)
                //     cout<<s[j]<<"\n";
                // cout<<"\n";
            if(obstacle[row]==0)
                depthfirst(v,f,row+1,0);
            else{
                   
                if(col==n-1)
                    depthfirst(v,f,row+1,0);
                else 
                    depthfirst(v,f,row,col+1);
            }
                
            s[row][col]='0';
            p++;
            f[row]=f[n+col] = f[n+n+row+col] = f[5*n-2+col-row] =1;
        }
            
    }
        
    depthfirst(v,f,row+1,0);
}











///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////           SIMULATED ANNEALING              ////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////










double probability(){
    return random()%100;
}


// To check if a conflict is present in the probem

int check_conflict(vector<pair<int,int>> lo){
    int weight = 0;
    int i,j;
    for(i=0;i<lo.size();i++){
        int x1= lo[i].first , y1 = lo[i].second;
        for(j=i+1;j<lo.size();j++){ 
            
            int x2 = lo[j].first , y2 = lo[j].second;     
            if(x1 == x2){ 

                int mn=min(y1,y2);
                int mx=max(y1,y2);
                for(int ob=mn+1;ob<mx;ob++){
                    if(s[x1][ob]=='2'){
                        weight--;
                        break;
                    }
                }
                weight++;
            }
            if(y1 == y2){  
                int mn=min(x1,x2);
                int mx=max(x1,x2);
                for(int ob=mn+1;ob<mx;ob++){
                    if(s[ob][y1]=='2'){
                        weight--;
                        break;
                    }
                }
                weight++;
            }
            if(abs(x1-x2)==abs(y1-y2)){
                int mn1=min(x1,x2);
                int mn2=min(y1,y2);
                if((x1==mn1 && y1==mn2)||(x2==mn1 && y2==mn2)){
                    for(int ob=1;ob<abs(x1-x2);ob++){
                        if(s[mn1+ob][mn2+ob]=='2'){
                            weight--;
                            break;
                        }
                    }
                    weight++;
                }
                else{
                    for(int ob=1;ob<abs(x1-x2);ob++){
                        if(s[mn1+ob][mn2+(abs(x1-x2)-ob)]=='2'){
                            weight--;
                            break;
                        }
                    }
                    weight++;
                }
            }


        }
    }
    return weight;
}




// To check if repititions are present



bool check_rep(int x,int y){
    for(int i=0;i<loc.size();i++){
        if(x==loc[i].first && y==loc[i].second)
            return true;
    }
    if(s[x][y]=='2')return true;
    return false;
}




// To randomly put initial set of lizards in the garden


void gen_lizards(){
    srandom((unsigned int)time(NULL));
    int i;
    for(i=0;i<p;i++){
        bool rep=true;
        while(rep){
            int x=random()%n;
            int y = random()%n;
            if(!check_rep(x,y)){
                loc.push_back({x,y});
                rep=false;
            }
        }
    }
    //for(i=0;i<p;i++) cout<<loc[i].first<<" "<<loc[i].second<<"\n";
}




// main function for simulated annealing


int simulated_annealing(){
    if(p==0)
        return 1;
    if(check_conflict(loc) == 0){
            return 1;
        }
    double temperature = 50000;
    double coeff = 0.99;
    int time;
    double dE;
    vector<pair<int,int>> suc(p);

    // Run for arround 2 minutes
    for(time=0;time<20000000;time++){  
        temperature *= coeff;
        int i;
        for(i=0;i<p;i++) suc[i] = loc[i];
        
        bool rep=true;
        while(rep){
            int x=random()%n;
            int y = random()%n;
            if(!check_rep(x,y)){
                suc[random()%p]={x,y};
                rep=false;
            }
        }
        
        dE = check_conflict(suc) - check_conflict(loc);

        // select bad successor with a certain randomness

        if(dE < 0 || probability() < 100*exp(-dE*1.0/temperature)){
            for(i=0;i<p;i++) loc[i] = suc[i];
        }
        if(check_conflict(loc) == 0){
            return 1;
        }
    }
    
    return 0;
}








///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////           BFS             ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////




// if goal is found store the result

void store(vector<pair<int,int>> fr){
    for(int i=0;i<fr.size();i++){
        loc.push_back({fr[i].first,fr[i].second});
    }
}

// Start bfs from each location whereever possible
// main bfs function

void breadth(int x, int y){
    //cout<<x<<" "<<y<<"\n";
    vector<pair<int,int>> l;
    l.push_back({x,y});
    queue< vector<pair<int,int>> > q;
    q.push(l);
    while(!q.empty()){
        vector<pair<int,int>> fr = q.front();
        q.pop();
        int psize= fr.size();
        //cout<<psize;
        int flag=0;
        for(int i=fr[psize-1].first ; i<n;i++){
            for(int j=0;j<n;j++){
                if(s[i][j]=='2')
                    continue;
                //cout<<i<<" "<<j<<"\n"; 
                fr.push_back({i,j});
                if(check_conflict(fr)==0){
                    flag=1;
                    q.push(fr);
                    fr.pop_back();
                }
                else{
                    fr.pop_back();
                }
            }
            if(p-psize>n-i+k[i])
            break;
        }
        
            
        if(p==fr.size()){
            store(fr);
            return;
        }
        fr.clear();
    }
}


// Choose the starting square and call the main bfs function - breadth()

 int bfs(){
    if(p==0)
        return 1;
    for(int i=0;i<n;i++){
        if(p>n-i+k[i])
            break;
        for(int j=0;j<n;j++){
            if(s[i][j]=='2')
                continue;
            if(loc.empty())
                breadth(i,j);
            
        }
    }
    if(loc.empty())
        return 0;
    else return 1;
}





/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////            MAIN              //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////




int main(){
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string algo;
    cin>>algo;

    
    cin>>n>>p;
    


    vector<vector<string>> v;
    s.resize(n);
    obstacle.resize(n);
    k.resize(n);
    int count=0;
    for(int i=0;i<n;i++){
        cin>>s[i];
        for(int j=0;j<s[i].length();j++){
            if(s[i][j]=='2'){
                count++;
                obstacle[i]++;
            }
        }
    }
    k[n-1]=obstacle[n-1];
    for(int j=n-2;j>=0;j--){
        k[j]=obstacle[j]+k[j+1];
    }

    if(count+n<p || (n*n-count)<p){
        cout<<"FAIL\n";
        return 0;
    }

    if(algo[0]=='D'){                                     // CALL DFS 
        vector<int> f(6*n-2,1);
        //cout<<"\n";
        depthfirst(v,f,0,0);
        if(v.size()==0)
            cout<<"FAIL\n";
        else{
            cout<<"OK\n";
            for(int i=0;i<v.size();i++){
                for(int j=0;j<n;j++)
                    cout<<v[i][j]<<"\n";
                    //cout<<"\n";
            }
        }
    }


    if(algo[0]=='B'){                                       // CALL BFS
        int bfs_obtained=bfs();
        int i;
        if(bfs_obtained){
            cout<<"OK\n";
            for(i=0;i<p;i++)
                s[loc[i].first][loc[i].second]='1';
            for(i=0;i<n;i++)
                cout<<s[i]<<"\n";
        }
        else
            cout<<"FAIL\n";

    }


    if(algo[0]=='S'){                                       // CALL Simulated Annealing
        gen_lizards();
        //check_conflict();
        int sa_obtained=simulated_annealing();
        int i;
        if(sa_obtained){
            cout<<"OK\n";
            for(i=0;i<p;i++)
                s[loc[i].first][loc[i].second]='1';
            for(i=0;i<n;i++)
                cout<<s[i]<<"\n";
        }
        else
            cout<<"FAIL\n";
    }


    return 0;
}