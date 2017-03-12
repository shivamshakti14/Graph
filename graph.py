class Node:
	def __init__(self,data):
		self.data=data
		self.neighbour={}

	def add_neighbour(self,new_neighbour,weight=0):
		self.neighbour[new_neighbour] = weight

	def print_neighbour(self):
		for i in self.neighbour:
			print str(i)+','+str(self.neighbour[i])+' ||| ',

	def get_neighbour(self):
		return self.neighbour

	def get_neighbour_vertex(self):
		l=[]
		for i in self.neighbour:
			l.append(i)
		return l

class Directed_Graph:
	def __init__(self):
		self.vertex={}
		self.total_vertex=0

	def add_vertex(self,data):
		self.total_vertex+=1
		new_vertex = Node(data)
		self.vertex[data] = new_vertex

	def add_directed_edge(self,from_u,to_v,weight=0):
		if from_u not in self.vertex:
			self.add_vertex(from_u)
		if to_v not in self.vertex:
			self.add_vertex(to_v)
		self.vertex[from_u].add_neighbour(to_v,weight)

	def print_directed_graph(self):
		for i in self.vertex:
			print str(i)+" => ",
			self.vertex[i].print_neighbour();
			print ''

	def bfs_util(self,visited,queue,size):
		while size>0:
			u = queue.pop(0)
			size-=1
			print u,
			for i in self.vertex[u].get_neighbour_vertex():
				if visited[i]==0:
					queue.append(i)
					size+=1
					visited[i]=1
		return visited,queue,size
	def initialize_visited(self):
		visited={}
		for i in self.vertex:
			visited[i]=0
		return visited
		
	def bfs(self,source):
		visited = self.initialize_visited()
		queue = [source]
		size = 1
		visited[source]=1
		visited, queue, size = self.bfs_util(visited,queue,size)
		#if graph is disconnected
		for i in visited:
			if visited[i]==0:
				visited[i] = 1
				queue = [i]
				size=1
				visited, queue, size = self.bfs_util(visited,queue,size)
		print ''
	def dfs_util(self,source,visited):
		if visited[source]==0:
			print source,
			visited[source]=1
			for i in self.vertex[source].get_neighbour_vertex():
				visited = self.dfs_util(i,visited)
		return visited

	def dfs(self,source):
		visited=self.initialize_visited()
		visited[source]=1
		print source,
		for i in self.vertex[source].get_neighbour_vertex():
			visited = self.dfs_util(i,visited)
		for i in self.vertex:
			if visited[i]==0:
				visited = self.dfs_util(i,visited)
		print ''

G=Directed_Graph()
G.add_directed_edge(1,2,33)
G.add_directed_edge(1,5,543)
G.add_directed_edge(2,3,3564)
G.add_directed_edge(4,5,434)
G.print_directed_graph()
G.bfs(1)
G.dfs(1)