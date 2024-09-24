#include<bits/stdc++.h>
using namespace std;
int parent[1005];
int sz[1005];
void dsu_init(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
        sz[i] = 1;
    }
}
int dsu_find(int node)
{
    if (parent[node] == -1)
        return node;
    int leader = dsu_find(parent[node]);
    parent[node] = leader;
    return leader;
}
void dsu_union_by_size(int node1, int node2)
{
    int leaderA = dsu_find(node1);
    int leaderB = dsu_find(node2);
    if (sz[leaderA] > sz[leaderB])
    {
        parent[leaderB] = leaderA;
        sz[leaderA] += sz[leaderB];
    }
    else if (sz[leaderA] < sz[leaderB])
    {
        parent[leaderA] = leaderB;
        sz[leaderB] += sz[leaderA];
    }
    else
    {
        parent[leaderA] = leaderB;
        sz[leaderB] += sz[leaderA];
    }
}
int main()
{
    int n,e;
    cin>>n>>e;
    dsu_init(n);
    vector<pair<int,pair<int,int>>> edges;
    while(e--){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    sort(edges.begin(),edges.end());
        int totalCost = 0;
    for(auto &ed : edges){
        int w = ed.first;
        int u = ed.second.first;
        int v = ed.second.second;

        // cout<<u<<" "<<v<<" "<<w<<endl;
        int leaderU = dsu_find(u);
        int leaderV = dsu_find(v);
        if(leaderU == leaderV){
            continue;
        }else{
            dsu_union_by_size(u,v);
            totalCost += w;
        }
    }
    cout<<totalCost<<endl;
    return 0;
}