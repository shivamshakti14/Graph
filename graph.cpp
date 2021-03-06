#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <deque>
using namespace std;
class Directed_Graph{
public:
	int vertex,edge;
	std::vector< list <pair < int,int> > > graph;
	std::vector<int> size_of_con_comp;
	int size;
	Directed_Graph(int nodes){
		size=0;
		vertex = nodes;
		graph.resize(vertex+1);
	}
	void add_edge(int u,int v,int weight){
		graph[u].push_back(make_pair(v,weight));
	}
	void print_graph(){
		int i;
		for(i=1;i<=vertex;i++){
			cout<<i<<"-> ";
			list <pair <int, int> >:: iterator itr=graph[i].begin();
			while(itr!=graph[i].end()){
				cout<<(itr)->first<<" "<<(itr)->second<<" ";
				itr++;
			}cout<<endl;
		}
	}
	void DFS_util(int source,vector<int >& visited){
		list< pair < int,int > >::iterator itr=graph[source].begin();
		cout<<source<<" ";
		visited[source]=1;
		size++;
		while(itr!=graph[source].end()){
			if(visited[itr->first]==0){
				DFS_util(itr->first,visited);
			}
			itr++;
		}
	}
	void DFS(int source){
		std::vector<int> visited(vertex+1);
		fill(visited.begin(), visited.end(),0);
		DFS_util(source,visited);
		for(int i=1;i<=vertex;i++){
			if(visited[i]==0){
				DFS_util(i,visited);
			}
		}
		cout<<endl;
	}

	void BFS(int source){
		std::vector<int> visited(vertex+1);
		fill(visited.begin(), visited.end(),0);
		std::deque <int> d;
		d.push_back(source);
		visited[source]=1;
		while(!d.empty()){
			int s=d.front();
			//visited[s]=1;
			cout<<s<<" ";
			d.pop_front();
			list <pair <int,int > >::iterator itr = graph[s].begin();
			while(itr!=graph[s].end()){
				if(visited[itr->first]==0){
					d.push_back(itr->first);
					visited[itr->first]=1;
				}
				itr++;
			}
		}
		// if graph is disconnected
		int i;
		for(i=1;i<=vertex;i++){
			if(visited[i]==0){
				d.push_back(i);
				visited[source]=1;
				while(!d.empty()){
					int s=d.front();
					//visited[s]=1;
					cout<<s<<" ";
					d.pop_front();
					list <pair <int,int > >::iterator itr = graph[s].begin();
					while(itr!=graph[s].end()){
						if(visited[itr->first]==0){
							d.push_back(itr->first);
							visited[itr->first]=1;
						}
						itr++;
					}
				}
			}
		}
		cout<<endl;
	}
	void connected_component(){
		int source =1;
		std::vector<int> visited(vertex+1);
		fill(visited.begin(), visited.end(),0);
		size=0;
		DFS_util(source,visited);
		size_of_con_comp.push_back(size);
		size=0;
		for(int i=1;i<=vertex;i++){
			if(visited[i]==0){
				DFS_util(i,visited);
				size_of_con_comp.push_back(size);
				size=0;
			}
		}
		cout<<"total diff conn component "<<size_of_con_comp.size()<<endl;
		for(int i=0;i<size_of_con_comp.size();i++){
			cout<<size_of_con_comp[i]<<" ";
		}cout<<endl;
	}
};

int main(){
	int vertex;
	cin>>vertex;
	Directed_Graph G(vertex);
	G.add_edge(1,2,333);
	G.add_edge(3,2,13);
	G.add_edge(2,3,433);
	G.add_edge(4,5,343);
	G.add_edge(6,7,343);
	G.add_edge(6,8,5435);
	G.print_graph();
	int source=2;
	G.BFS(source);
	G.DFS(source);
	G.connected_component(); // total connected connected and size of each
	return 0;
}