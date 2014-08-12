#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream> 
#include <iostream>
#include <map>
using namespace std; 
 
typedef pair<int,int> PI; 
typedef pair<PI,int> PPI; 
typedef vector<int> VI;
typedef vector<PI> VP;
#define mp make_pair
#define pb push_back
#define INF 1000000000

vector<VI> arr; //adjecency list
VI vis; //visited list
VI par; //parent list
vector<pair<string,int> > vmap;
map<pair<string,int>,int> person;
int getPerson(string s, int x){
    if(person.find(mp(s,x)) == person.end()){
        throw 1;
    }
    return person[mp(s,x)];
}
       
int dijkstra(int source, int destination){	 //returns the shortest path, returns -1 when not connected
    priority_queue<PPI, vector<PPI>, greater<PPI> > q;
    //queue<PPI> q;
    q.push(mp(mp(0,source),source)); 
    PPI temp; 
    while(!q.empty()){
		temp = q.top();
        //temp = q.front();
		
        q.pop();
		if(!vis[temp.second]){
			par[temp.second] = temp.first.second; 
			if(temp.second == destination) return temp.first.first; 
			vis[temp.second] = 1;
			for(int i=0;i<arr[temp.second].size();i++){
				q.push(mp(mp(temp.first.first + 1, temp.second), arr[temp.second][i]));
			}
		}
    }
    return -1; 
}
void shortestDistance(int a,int b){
    int x = dijkstra(a, b);
    if(x == -1)
	cout << "THE TWO PEOPLE ARE NOT CONNECTED" << endl;
    else 
	cout <<"THE SHORTEST DISTANCE BETWEEN THE TWO PEOPLE IS: " << x << endl; 
}
void shortestPath(int a,int b){
	int x = dijkstra(a, b);
	if(x == -1)
		cout << "THE TWO PEOPLE ARE NOT CONNECTED" << endl;
	else{
		cout <<"THE SHORTEST DISTANCE BETWEEN THE TWO PEOPLE IS: " << x << endl; 
		cout <<"THE PATH IS AS FOLLOWS: " << endl;
		x = b;
        cout << vmap[b].first << " " << vmap[b].second << endl;
		while(par[x] != x){
			x = par[x];
			cout << vmap[x].first << " " << vmap[x].second << endl;
		}
	}
}

vector<VI> dis; //distance grid for floyd warshall
vector<VI> cnt; //count grid for floyd warshall
void storeFW(int n){
	dis.resize(n);
	cnt.resize(n);
	for(int i=0;i<n;i++)dis[i].resize(n), cnt[i].resize(n);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)dis[i][j] = INF, cnt[i][j] = 0; 
	for(int i=0;i<n;i++)dis[i][i] = 0; 
	for(int i=0;i<n;i++){
		for(int j=0;j<arr[i].size();j++){
			dis[i][arr[i][j]] = 1;  
			cnt[i][arr[i][j]] =	1; 
		}
	}
	// DISTANCE GRID INITIALIZED, NOW THE MAIN ALGO
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);  // TRIANGLE INEQUALITY
				if(dis[i][j] > dis[i][k] + dis[k][j]){
					dis[i][j] = dis[i][k] + dis[k][j]; 
					cnt[i][j] = 1;
				}
				else if(dis[i][j] == dis[i][k] + dis[k][j] && k!=i && k!=j){
					cnt[i][j] ++;
				}
			}
		}
	}
	ofstream f("FW.txt"); 
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			f << dis[i][j] << " " << cnt[i][j] << " "; 
		}
	}
	f.close();
}
void floydWarshall(int n){
	ifstream f("FW.txt");
	int val; 
	dis.resize(n);
	cnt.resize(n);	
	for(int i=0;i<n;i++)dis[i].resize(n), cnt[i].resize(n);
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			f >> val;
			dis[i][j] = dis[j][i] = val;
			f >> val; 
			cnt[i][j] = cnt[j][i] = val;
		}
	}
	f.close();
}
float getImportance(int k,int n){
	int ans = 0;  
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(i!=k && j!=k && dis[i][j] == dis[i][k]  + dis[k][j]){
				ans += cnt[i][k]*cnt[k][j];
			} 
		}
	}
	return ans;
}
void importance(int k, int n){
	floydWarshall(n);
	int ans = getImportance(k, n);
	cout << "THE IMPORTANCE OF THE GIVEN PERSON IS : " << ans << endl; 
}
void shortestDistance(int n){
	floydWarshall(n); 
	int ans = 0; 
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ans = max(ans,dis[i][j]);
 		}
	}
	if(ans >= INF) cout << "THE GRAPH IS DISCONNECTED" << endl;
	else cout << "THE SHORTEST DISTANCE BETWEEN ANY TWO PEOPLE IN THE GRAPH IS: " << ans << endl;
}

void moreImportant(int k, int n){
	floydWarshall(n); 
	int base = getImportance(k, n);
	VI envy; 
	for(int i=0;i<arr[k].size();i++){
		if(getImportance(arr[k][i],n) > base) envy.pb(arr[k][i]); 
	}
	cout <<  "THERE ARE " << envy.size() << " FRIENDS MORE IMPORTANT THAN THE GIVEN PERSON" << endl; 
	if(envy.size()){
		cout <<"THE LIST OF THOSE FRIENDS IS: " << endl;
		for(int i=0;i<envy.size();i++){
			cout << vmap[envy[i]].first << " " << vmap[envy[i]].second << endl;
		} 
	}
}
int indices[25]; 
void cliqueSize(int k, int n){
	floydWarshall(n); 	
	int sz = arr[k].size();
    if(sz >= 25){
        cout << "THE PERSON IS TOO SOCIAL, CLIQUES ARE NOT HIS/HER STYLE\n";
	return;
    }
	int temp; 
	int i,idx;
	bool flg; 
	int ans = 0; 
	for(int mask = 0; mask < (1<<sz); mask ++){
		temp = mask; 
		i = 0; 
		idx = 0; 
		while(temp){
			flg = true; 
			for(int j=0;j<idx;j++){
				if(dis[arr[k][i]][indices[j]] != 1) flg = false; 
			}
			if(flg) indices[idx++] = arr[k][i];  
			i++;
			temp >>= 1;
		}
		ans = max(ans,idx);
	}
	cout << "CLIQUE SIZE OF THE GIVEN PERSON IS: " << ans+1 << endl;
}

void make_graph(int &n){
	ifstream f("vmap.txt");
	int a,b; 
	string s; 
	n = 0; 
	while(true){
		f >> a;
        if(f.eof())break;
        f>> s >> b;
		vmap.pb(mp(s,b));
		n ++;
		person[mp(s,b)] = a;
	}
	arr.resize(n);
	f.close(); 
	f.open("adj.txt");
	while(true){
		f >> a;
        if(f.eof())break;
        f >> b;
		arr[a].pb(b);
		arr[b].pb(a);
	}
	f.close(); 
}

int main(int argc, char* argv[]){
	int n;
    make_graph(n);
	vis.resize(n);
	par.resize(n);
	for(int i=0;i<n;i++)par[i] = i;
    try {
        if(argc > 1){
            if(strcmp(argv[1],"FW") == 0){
                cout << " ---- LOADING ------ \n";
                storeFW(n);
                cout << "DONE \n ";
            }else if(strcmp(argv[1],"CL") == 0){
                string s(argv[2]); 
                int st = getPerson(s,atoi(argv[3]));
                cliqueSize(st, n);
            }else if(strcmp(argv[1],"SD") == 0 && argc == 6){
                string s(argv[2]); 
                int st1 = getPerson(s,atoi(argv[3]));
                s = string(argv[4]); 
                int st2 = getPerson(s,atoi(argv[5]));
                shortestDistance(st1, st2); 
            }else if(strcmp(argv[1],"SP") == 0 && argc == 6){
                string s(argv[2]); 
                int st1 = getPerson(s,atoi(argv[3]));
                s = string(argv[4]); 
                int st2 = getPerson(s,atoi(argv[5]));
                shortestPath(st1, st2); 
            }else if(strcmp(argv[1],"SD") == 0){
                shortestDistance(n); 
            }else if(strcmp(argv[1],"I") == 0){
                string s(argv[2]); 
                int st1 = getPerson(s,atoi(argv[3]));
                importance(st1, n);
            }else if(strcmp(argv[1],"CI") == 0){
                string s(argv[2]); 
                int st1 = getPerson(s,atoi(argv[3]));
                moreImportant(st1, n);
            }
        }
    } catch(int x){
        cout <<"DATA NOT FOUND IN THE NETWORK" << endl;
    }
}
