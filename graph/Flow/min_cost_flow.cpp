struct MinCostFlow{
	using C = ll;		// capacity
	using D = ll;		// cost (distance)
	const D inf = 1e18;	// max distance

	struct edge{
		int to;
		C cap;
		D cost;
		int rev;
		edge(int to_,C cap_, D cost_, int rev_):to(to_),cap(cap_),cost(cost_),rev(rev_){}
	};
	
	int N;
	VV<edge> G;
	V<D> h;
	V<D> dist;
	V<int> prevv,preve;
	MinCostFlow(int N_):N(N_){
		G.resize(N);
		h.resize(N);
		dist.resize(N);
		prevv.resize(N);
		preve.resize(N);
	}

	void add_edge(int from, int to, C cap, D cost){
		show(cap);
		show(cost);
		edge e1(to,cap,cost,(int)G[to].size());
		edge e2(from,0,-cost,(int)G[from].size());
		G[from].push_back(e1);
		G[to].push_back(e2);
	}
	D min_cost_flow(int s, int t, C f){
		D res = 0;
		h = V<D>(N);
		while(f > 0){
			using P = pair<D,int>;
			priority_queue< P,vector<P>,greater<P> > que;
			dist = V<D>(N,inf);
			dist[s] = 0;
			que.push(P(0,s));
			while(!que.empty()){
				P p = que.top();
				que.pop();
				int v = p.second;
				if(dist[v] < p.first) continue;
				for(int i=0;i<(int)G[v].size();i++){
					edge &e = G[v][i];
					if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
						dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
						prevv[e.to]=v;
						preve[e.to]=i;
						que.push(P(dist[e.to],e.to));
					}
				}
			}
			if(dist[t]==inf) return -1;
			rep(v,N) h[v]+=dist[v];
			C d = f;
			for(int v=t;v!=s;v=prevv[v]){
				chmin(d,G[prevv[v]][preve[v]].cap);
			}
			f -= d;
			res += d*h[t];
			for(int v=t;v!=s;v=prevv[v]){
				edge &e=G[prevv[v]][preve[v]];
				e.cap-=d;
				G[v][e.rev].cap+=d;
			}
		}
		return res;
	}
};
