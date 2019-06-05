#include <bits/stdc++.h>
#define maxn 200005
using namespace std;
struct edge{
    int next,to;
}q[maxn];
int head[maxn],dfn[maxn],low[maxn],cnt,tot;
int vis[maxn],belong[maxn],index,belong_num[maxn],num_index;
int indegree[maxn],outdegree[maxn];
void add_edge(int from,int to){
    q[cnt].next=head[from];
    q[cnt].to=to;
    head[from]=cnt++;
}
void init(){//初始化
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(head,-1,sizeof(head));
    memset(low,0,sizeof(low));
    memset(belong_num,0,sizeof(belong_num));//在某个连通块中有多少个结点
    memset(indegree,0,sizeof(indegree));//新图的入度
    memset(outdegree,0,sizeof(outdegree));
    index=num_index=cnt=tot=0;
}
stack<int>st;
void tarjin(int x){//Tarjin的主体
    dfn[x]=low[x]=++tot;
    vis[x]=1;
    st.push(x);
    for(int i=head[x];i!=-1;i=q[i].next){
        edge e=q[i];
        if(!dfn[e.to]){
            tarjin(e.to);
            low[x]=min(low[e.to],low[x]);
        }
        else if(vis[e.to]==1){
            low[x]=min(low[x],dfn[e.to]);
        }
    }
    if(dfn[x]==low[x]){
        int v;
        index=index+1;
        do{
            v=st.top();
            st.pop();
            belong[v]=index;
            belong_num[index]++;
            vis[v]=0;
        }while(v!=x);
    }
}
void solve(int n,int m,int root){
    for(int i=1;i<=n;i++){//对图进行Tarjin
        if(!dfn[i]){
            tarjin(i);
        }
    }
    //如果连通分量只有一个，则直接输出0
    if(index==1){
        puts("0");
        return ;
    }
    indegree[belong[root]]=1;//确保初始点root所在的连通分量入度不为0
    
    for(int i=1;i<=n;i++){//重构图的过程
        for(int j=head[i];j!=-1;j=q[j].next){
            edge e=q[j];
            if(belong[i]==belong[e.to]) continue;
            indegree[belong[e.to]]++;
            outdegree[belong[i]]++;
        }
    }
    int cnt=0;//统计入度为0的点
    for(int i=1;i<=index;i++){
        if(indegree[i]==0){
            cnt++;
        }
    }
    cout<<cnt<<endl;
}