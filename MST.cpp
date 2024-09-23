//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
	public:
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
    class Edge{
	    public:
	    int u,v,w;
	    Edge(int u,int v,int w){
	        this->u = u;
	        this->v = v;
	        this->w = w;
	    }
	};
    static bool cmp(Edge a, Edge b){
        return a.w <= b.w;
    }
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        dsu_init(V);
        vector<Edge> edgeList;
        for(int i=0;i<V;i++){
            for(auto child : adj[i]){
                int u = i;
                int v = child[0];
                int w = child[1];
                
                if(u < v)
                    edgeList.push_back(Edge(u,v,w));
            }
        }
        sort(edgeList.begin(), edgeList.end(),cmp);
        int totalCost = 0;
        int edgesUsed = 0;
        for(Edge ed : edgeList){
            int u = ed.u;
            int v = ed.v;
            int w = ed.w;

            int leaderU = dsu_find(u);
            int leaderV = dsu_find(v);
            cout<<u<<" "<<v<<" "<<w<<endl;
            if(leaderU == leaderV)
                continue;
            else{
                dsu_union_by_size(u,v);
                totalCost += w;
            }
        }
        return totalCost;
    }
};

//{ Driver Code Starts.


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        
        Solution obj;
    	cout << obj.spanningTree(V, adj) << "\n";
    }

    return 0;
}


// } Driver Code Ends