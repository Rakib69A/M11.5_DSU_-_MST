#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int parent[N];
int sz[N];
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
    int n, e;
    cin >> n >> e;

    dsu_init(n);
    vector<int> adj[n];
    while (e--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // bool cycle = false;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int child : adj[i])
    //     {
    //         if (child != i - 1)
    //         {
    // int leaderA = dsu_find(i);
    // int leaderB = dsu_find(child);
    // if (leaderA == leaderB)
    // {
    //     cycle = true;
    // }
    // else
    // {
    //     dsu_union_by_size(i, child);
    // }
    //         }
    //     }
    // }
    // if (cycle)
    //     cout << "Cycle found" << endl;
    // else cout<<"Cycle is not found"<<endl;
    vector<pair<int, int>> edgeList;
    for (int u = 0; u < n; u++)
    {
        for (int v : adj[u])
        {
            if (u < v)
            {
                edgeList.push_back({u, v});
            }
        }
    }
    cout << "Edge List" << endl;
    bool cycle = false;
    for (pair<int, int> ed : edgeList)
    {
        cout<<ed.first<<" "<<ed.second<<endl;
        int leaderA = dsu_find(ed.first);
        int leaderB = dsu_find(ed.second);
        if (leaderA == leaderB)
        {
            cycle = true;
        }
        else
        {
            dsu_union_by_size(ed.first, ed.second);
        }
    }
    if(cycle) cout<<"Cycle Detected"<<endl;
    else cout<<"Cycle is not detected"<<endl;
    return 0;
}