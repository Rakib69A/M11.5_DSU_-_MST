#include<bits/stdc++.h>
using namespace std;
int parent[100005];
int sz[100005];
void dsu_init(int n){
    for(int i=1;i<=n;i++){
        parent[i] = -1;
        sz[i] = 1;
    }
}
int dsu_find(int node){
    if(parent[node] == -1)
        return node;
    int leader = dsu_find(parent[node]);
    parent[node] = leader;
    return leader;
}
void dsu_union_by_size(int node1, int node2){
    int leaderA = dsu_find(node1);
    int leaderB = dsu_find(node2);

    if(sz[leaderA] > sz[leaderB]){
        parent[leaderB] = leaderA;
        sz[leaderA] += sz[leaderB];
    }
    else if(sz[leaderB] > sz[leaderA]){
        parent[leaderA] = leaderB;
        sz[leaderB] += sz[leaderA];
    }
    else{
        parent[leaderA] = leaderB;
        sz[leaderB] += sz[leaderA];
    }
}
vector<int> adj[100005];
bool vis[100005];
void dfs(int src){
    vis[src] = true;
    for(int child : adj[src]){
        if(!vis[child]){
            dfs(child);
        }
    }
}
class Edge{
    public:
    long long a,b,c;
    Edge(long long a, long long b, long long c){
        this->a = a;
        this->b = b;
        this->c = c;
    }
};
bool cmp(Edge a, Edge b){
    return a.c < b.c;
}
int main()
{
    int n,e;
    cin>>n>>e;
    dsu_init(n);
    // vector<pair<int,pair<int,int>>> edgeList;
    vector<Edge> edgeList;
    while(e--){
        long long int  a,b,c;
        cin>>a>>b>>c;
        // edgeList.push_back({c,{a,b}});
        edgeList.push_back(Edge(a,b,c));
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(vis,false,sizeof(vis));
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i);
            cnt++;
        }
    }
    if(cnt>1){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    sort(edgeList.begin(),edgeList.end(),cmp);
    long long int totalCost = 0;
    for(Edge ed : edgeList){
        // int c = ed.first;
        // int a = ed.second.first;
        // int b = ed.second.second;

        int c = ed.c;
        int a = ed.a;
        int b = ed.b;

        int leaderA = dsu_find(a);
        int leaderB = dsu_find(b);

        if(leaderA == leaderB)
            continue;
        else{
            dsu_union_by_size(a,b);
            totalCost += c;
        }
    }
    cout<<totalCost<<endl;
    return 0;
}