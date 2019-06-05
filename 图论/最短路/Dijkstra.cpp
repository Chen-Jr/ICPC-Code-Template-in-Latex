const int INF=0x3f3f3f3f;
int head[maxn],cnt;
struct edge{
    int to,next;
    long long cost;
}q[maxn];
void add_edge(int from,int to,int cost){
    q[cnt].to=to;
    q[cnt].cost=cost;
    q[cnt].next=head[from];
    head[from]=cnt++;
}
typedef pair<int,int>P;
long long d[maxn];
int a[maxn],b[maxn],c[maxn];
void dijikstra(int s){
    memset(d,INF,sizeof(d));
    priority_queue<P,vector<P>,greater<P> >que;
    d[s]=0;
    que.push(P(0,1));
    while(!que.empty()){
        P p=que.top();
        que.pop();
        int x=p.second;
        //if(d[x]<p.first) continue;
        for(int i=head[x];i!=-1;i=q[i].next){
            edge id=q[i];
            if(d[id.to]>d[x]+id.cost){
                d[id.to]=d[x]+id.cost;
                que.push((P(d[id.to],id.to)));
            }
        }
    }
}