#include <bits/stdc++.h>
using namespace std;
const int maxn=50005;
const int maxm=500005;
const int inf=0x3f3f3f3f;
struct Node{
    int to,val,next;
}q[maxm<<1];
int head[maxn],cnt=0,dep[maxn],cur[maxn],vis[maxn];
int sp,ep,maxflow;
void init(){
    memset(head,-1,sizeof(head));
    cnt=2,maxflow=0;
}
void addedge(int from,int to,int val){
    q[cnt].to=to;
    q[cnt].val=val;
    q[cnt].next=head[from];
    head[from]=cnt++;
}
void add_edge(int from,int to,int val){
    addedge(from,to,val);
    addedge(to,from,0);
}
bool bfs(int n){
    for(int i=0;i<=n;i++){
        cur[i]=head[i],dep[i]=0x3f3f3f3f;
        vis[i]=0;
    }
    dep[sp]=0;
    queue<int>que;
    que.push(sp);
    while(!que.empty()){
        int x=que.front();
        que.pop();
        vis[x]=0;
        for(int i=head[x];i!=-1;i=q[i].next){
            int to=q[i].to;
            if(dep[to]>dep[x]+1&&q[i].val){
                dep[to]=dep[x]+1;
                if(!vis[to]){
                    que.push(to);
                    vis[to]=1;
                }
            }
        }
    }
    if(dep[ep]!=inf) return true;
    else return false;
}
int dfs(int x,int flow){
    int rlow=0;
    if(x==ep){
        maxflow+=flow;
        return flow;
    }
    int used=0;
    for(int i=cur[x];i!=-1;i=q[i].next){
        cur[x]=i;
        int to=q[i].to;
        if(q[i].val&&dep[to]==dep[x]+1){
            if(rlow=dfs(to,min(flow-used,q[i].val))){
                used+=rlow;
                q[i].val-=rlow;
                q[i^1].val+=rlow;
                if(used==flow) break;
            }
        }
    }
    return used;
}
int dinic(int n){
    while(bfs(n)){
        dfs(sp,inf);
    }
    return maxflow;
}
int main()
{
    int n,m;
    scanf("%d%d%d%d",&n,&m,&sp,&ep);
    register int i;
    int u,v,val;
    init();
    for(i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&val);
        add_edge(u,v,val);
    }
    printf("%d",dinic(n));
    return 0;
}
