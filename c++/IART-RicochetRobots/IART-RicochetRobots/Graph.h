/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits.h>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <utility>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	bool processing;
	int indegree;
	double dist;
	int set;

	pair<int,int> viewer_pos;
public:

	Vertex(T in);
	friend class Graph<T>;

	void addEdge(Vertex<T> *dest, double w);
	void addEdge(Vertex<T> *dest, double w, double f);
	bool removeEdgeTo(Vertex<T> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;
	vector<Edge<T> > getAdj() const;
	Vertex<T>* getPath() const;

	bool operator<(const Vertex<T> vertex);

	Vertex* path;

	void updateEdgeFlow(unsigned int index, float f);

	bool getVisited() const;
	void setVisited(bool vis);
	Vertex(T in, int x, int y);

};


template <class T>
struct vertex_greater_than {
    bool operator()(Vertex<T> * a, Vertex<T> * b) const {
        return a->getDist() > b->getDist();
    }
};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exercício 5
template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), processing(false), indegree(0), dist(0), viewer_pos(-1,-1) {
	path = NULL;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	edgeD.orig = this;
	adj.push_back(edgeD);
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, double f)
{
	Edge<T> edgeD(dest, w, f);
	edgeD.orig = this;
	adj.push_back(edgeD);
}


template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
vector<Edge<T> > Vertex<T>::getAdj() const {
	return this->adj;
}

template <class T>
Vertex<T>* Vertex<T>::getPath() const {
	return this->path;
}


template <class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template <class T>
void Vertex<T>::updateEdgeFlow(unsigned int index, float f)
{
	if (index >= adj.size())
		return;
	adj[index].flow = f;
}



/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * dest;
	Vertex<T> * orig;
	double weight;
	double flow;
public:
	Edge(Vertex<T> *d, double w, double f=0);
	double getFlow() const;
	double getWeight() const;
	Vertex<T> *getDest() const;
	bool operator<(const Edge<T> &other) const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, double f): dest(d), weight(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}

template <class T>
bool Edge<T>::operator<(const Edge<T> &other) const {
	return this->weight < other.weight;
}

template <class T>
struct edge_greater_than {
    bool operator()(Edge<T> a, Edge<T>  b) const {
        return a.getWeight() > b.getWeight();
    }
};



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path

	bool viewer_pos;
	int viewer_size;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w,double f=0);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	void bellmanFordShortestPath(const T &s);

	Graph<T> clone();
	void resetEdgeFlow();
	vector<Vertex<T>*> calculateFordFulkerson(T source);
	float calculateFordFulkerson(Vertex<T>* current, Vertex<T>* parent, float min, Graph<T>* gf, Graph<T>* gr, vector<Vertex<T>*> visited);

	int findVertex(T info) const;
	void print() const;
	void display() const;
	bool addVertex(const T &in, int x, int y);

	Graph(bool view);
	Graph(bool view, int size);

	void set_viewer_pos(bool view);
	void set_viewer_size(int size);

	void displaySolution(vector<T> vs) const;

	double getTotalWeight(vector<T> vs);

	void invertEdges();

};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}


template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, double f) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD,w,f);

	return true;
}


template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

template <class T>
bool Vertex<T>::getVisited() const {
	return visited;
}

template <class::T>
void Vertex<T>::setVisited(bool vis) {
	this->visited = vis;
}

template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false ){
	    	dfs(it->dest, res);
	    }
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}


template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfsVisit(*it);
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
	    if ( it->dest->visited == false ){
	    	dfsVisit(it->dest);
	    }
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vector com o resultado da ordenacao
	vector<T> res;

	//verificar se é um DAG
	if( getNumCycles() > 0 ) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while( !sources.empty() ) {
		q.push( sources.back() );
		sources.pop_back();
	}

	//processar fontes
	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if( v->adj[i].dest->indegree == 0) q.push( v->adj[i].dest );
		}
	}

	//testar se o procedimento foi bem sucedido
	if ( res.size() != vertexSet.size() ) {
		while( !res.empty() ) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}


template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){
	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<T> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}


template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if( w->dist == INT_INFINITY ) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s) {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if( w->dist > v->dist + v->adj[i].weight ) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template <class T>
void Graph<T>::resetEdgeFlow()
{
	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		for (unsigned int a = 0; a < vertexSet[i]->adj.size(); a++)
			vertexSet[i]->adj[a].flow = 0;
	}
}


template <class T>
Graph<T> Graph<T>::clone()
{
	Graph<T> ret(this->viewer_size,this->viewer_pos);
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
		ret.addVertex(this->vertexSet[i]->info);

	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		vector<Edge<T> > edges = this->vertexSet[i]->adj;
		for (unsigned int a = 0; a < edges.size(); a++)
			ret.addEdge(this->vertexSet[i]->info, edges[a].dest->info, edges[a].weight, edges[a].flow);
	}

	return ret;
}

template <class T>
vector<Vertex<T>*> Graph<T>::calculateFordFulkerson(T source)
{
	Graph<T> gr = this->clone();
	Graph<T> gf = this->clone();
	gf.resetEdgeFlow();

	Vertex<T>* src = gr.getVertex(source);
	if (src==NULL) throw -1;

	while(true)
	{
		vector<Vertex<T>*> visited;
		visited.push_back(src);

		float res = this->calculateFordFulkerson(src, NULL, 99999, &gf, &gr, visited);
		if (res < 0)
		{
			//*** All paths were searched. Terminating!
			break;
		}
	}

	return gf.vertexSet;
}

template <class T>
float Graph<T>::calculateFordFulkerson(Vertex<T>* current, Vertex<T>* parent, float min, Graph<T>* gf, Graph<T>* gr, vector<Vertex<T>*> visited)
{
	//*** Currently in vertex current->info
	//*** Minimum value is min

	vector<Edge<T> > edges = current->adj;

	for (unsigned int i = 0; i < edges.size(); i++)
	{
		Edge<T> edg = edges[i];

		//*** Searching edge to vertex edg.dest->info

		Vertex<T>* dest = edges[i].dest;
		Vertex<T>* destInGraph = this->getVertex(edges[i].dest->info);

		bool beenVisited = false;
		for (unsigned int j = 0; j < visited.size(); j++)
		{
			if (dest->info == visited[j]->info)
			{
				//*** Detected that dest->info was already visited. Will now continue with the next one!
				beenVisited = true;
				break;
			}
		}

		if (beenVisited)
			continue;

		if (edg.flow < min)
		{
			min = edg.flow;
			//*** Minimum flow updated to: min
		}

		visited.push_back(dest);

		if (destInGraph->adj.size() == 0)
		{
			//*** Reached a destination: dest->info

			//Upon the return, update the edges with the min value
			float newValue = edg.flow - min;
			if (newValue == 0)
			{
				//*** Deleting edge from current->info to dest->info since the val is 0!
				gr->removeEdge(current->info, dest->info);
			}
			else
				current->updateEdgeFlow(i, edg.flow - min);


			//Check to see if this edge already exists
			bool exists = false;
			unsigned int k = 0;
			for (k = 0; k < dest->adj.size(); k++)
			{
				if (dest->adj[k].dest->info == current->info)
				{
					exists = true;
					break;
				}
			}

			if (!exists)
			{
				gr->addEdge(dest->info, current->info, edg.weight, min);
				//*** Edge from dest->info to current->info does not exist in Gr... Adding with min
			}
			else
			{
				dest->updateEdgeFlow(k, dest->adj[k].flow + min);
				//*** Edge from dest->info to current->info already exists in Gr... Updating to: dest->adj[k].flow + min
			}

			//Search for the correct edge on Gf since both graphs may be unsynchronized
			Vertex<T>* updatedVertex = gf->getVertex(current->info);
			for (k = 0; k < current->adj.size(); k++)
			{
				if (current->adj[k].dest->info == dest->info)
					break;
			}
			float oldValue = updatedVertex->adj[k].flow;

			updatedVertex->updateEdgeFlow(k, oldValue + min);
			Edge<T> updatedEdge = updatedVertex->adj[k];

			//*** Setting k new edge flow value to the final graph from updatedVertex->info to updatedEdge.dest->info with k flow value of updatedEdge.flow

			//****** Returning minimum value of : min
			return min;
		}
		else
		{
			//*** Will enter recursion with new current: dest->info
			float newmin = this->calculateFordFulkerson(dest, current, min, gf, gr, visited);

			//*** Returned from recursion where new current was: dest->info
			//*** New minimum value is: newmin

			if (newmin < 0)
			{
				//*** There are no more paths to the destination. Exiting with new minimum: newmin
				continue;
			}

			//Upon the return, update the edges with the min value
			float newValue = edg.flow - newmin;
			if (newValue == 0)
			{
				//*** Deleting edge from current->info to dest->info since the val is 0!
				gr->removeEdge(current->info, dest->info);
			}
			else
				current->updateEdgeFlow(i, edg.flow - newmin);

			//Check to see if this edge already exists
			bool exists = false;
			unsigned int k = 0;
			for (k = 0; k < dest->adj.size(); k++)
			{
				if (dest->adj[k].dest->info == current->info)
				{
					exists = true;
					break;
				}
			}

			if (!exists)
			{
				gr->addEdge(dest->info, current->info, edg.weight, newmin);
				//*** Edge from dest->info to current->info does not exist in Gr... Adding with newmin
			}
			else
			{
				float newValue = dest->adj[k].flow + newmin;
				dest->updateEdgeFlow(k, newValue);
				//*** Edge from dest->info to current->info already exists in Gr... Updating to: newValue
			}

			//Search for the correct edge on Gf since both graphs may be unsynchronized
			Vertex<T>* updatedVertex = gf->getVertex(current->info);
			for (k = 0; k < updatedVertex->adj.size(); k++)
			{
				if (updatedVertex->adj[k].dest->info == dest->info)
					break;
			}
			if (k < updatedVertex->adj.size())
			{
				float oldValue = updatedVertex->adj[k].flow;

				updatedVertex->updateEdgeFlow(k, oldValue + newmin);
				Edge<T> updatedEdge = updatedVertex->adj[k];

				//*** Setting k new edge flow value to the final graph from updatedVertex->info to updatedEdge.dest->info with k flow value of updatedEdge.flow
			}
			else {
				//*** Didn't find the edge on Gf. Probably this was a REVERSE EDGE created in Gr. Find corresponding in Gf...
				Vertex<T>* reverseVertex = gf->getVertex(dest->info);
				for (k = 0; k < reverseVertex->adj.size(); k++)
				{
					if (reverseVertex->adj[k].dest->info == current->info)
						break;
				}
				if (k < reverseVertex->adj.size())
				{
					float oldValue = reverseVertex->adj[k].flow;

					reverseVertex->updateEdgeFlow(k, oldValue - newmin);
					Edge<T> reverseEdge = reverseVertex->adj[k];

					//*** ADJUSTING edge flow value to the final graph from reverseVertex->info to reverseEdge.dest->info with k flow value of reverseEdge.flow
				}

			}

			//*** Returning new minimum value of newmin after recursion!
			return newmin;
		}

	}

	return -1;
}

template <class T>
int Graph<T>::findVertex(T info) const {
	for (int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info==info) return i;
	}
	return -1;
}

template <class T>
void Graph<T>::print() const {
	for(int i=0;i<getNumVertex();i++)
	{
		cout<< "Vertex \"" << vertexSet[i]->info << "\"; Edges to:\n\t[";
		for(int j=0;j<vertexSet[i]->adj.size();j++)
		{
			cout << vertexSet[i]->adj[j].dest->info << "(" << vertexSet[i]->adj[j].weight<< ", " << vertexSet[i]->adj[j].flow <<")";
			if(j!=vertexSet[i]->adj.size()-1) cout << "; ";
		}
		cout<<"]\n";
	}
}

template <class T>
void Graph<T>::display() const {
	GraphViewer *gv = new GraphViewer(viewer_size, viewer_size, !viewer_pos);
	gv->createWindow(viewer_size, viewer_size);
	for(int i=0;i<getNumVertex();i++)
	{
		stringstream sstm;
		sstm << i << "." << vertexSet[i]->info;
		string label = sstm.str();
		if(vertexSet[i]->viewer_pos.first<0 || vertexSet[i]->viewer_pos.second<0 || !viewer_pos)
		{
			gv->addNode(i);
		}
		else
		{
			gv->addNode(i, vertexSet[i]->viewer_pos.first, vertexSet[i]->viewer_pos.second);
		}
		gv->setVertexLabel(i,label);
		gv->rearrange();
	}
	int id_counter=0;
	for(int i=0;i<getNumVertex();i++)
	{
		vector<Edge<T>  > edges = vertexSet[i]->adj;
		for(int j=0;j<edges.size();j++)
		{
			Vertex<T> * v=edges[j].dest;

			stringstream sstm;
			sstm <<"[" << edges[j].weight << "," << edges[j].flow << "]";
			string label = sstm.str();

			gv->addEdge(id_counter,i,findVertex(v->info),EdgeType::DIRECTED);
			gv->setEdgeLabel(id_counter,label);
			id_counter++;
			gv->rearrange();
		}
	}
	gv->rearrange();
}

template <class T>
Vertex<T>::Vertex(T in, int x, int y): info(in), visited(false), viewer_pos(x,y){}

template <class T>
bool Graph<T>::addVertex(const T &in, int x, int y) {
	for(int i=0;i<getNumVertex();i++)
	{
		if(getVertexSet()[i]->info==in) return false;
	}
	vertexSet.push_back( new Vertex<T>(in,x,y) );
	return true;
}

template <class T>
Graph<T>::Graph(bool view): viewer_pos(view), viewer_size(600){}

template <class T>
Graph<T>::Graph(bool view, int size): viewer_pos(view), viewer_size(size){}

template <class T>
void Graph<T>::set_viewer_pos(bool view) {
	viewer_pos=view;
}

template <class T>
void Graph<T>::set_viewer_size(int size) {
	viewer_size=size;
}

template <class T>
void Graph<T>::displaySolution(vector<T> vs) const {
	GraphViewer *gv = new GraphViewer(viewer_size, viewer_size, !viewer_pos);
		gv->createWindow(viewer_size, viewer_size);
		for(int i=0;i<getNumVertex();i++)
		{
			stringstream sstm;
			sstm << i << "." << vertexSet[i]->info;
			string label = sstm.str();
			if(vertexSet[i]->viewer_pos.first<0 || vertexSet[i]->viewer_pos.second<0 || !viewer_pos)
			{
				gv->addNode(i);
				for(unsigned int j=0;j<vs.size();j++)
				{
					if(vs[j]==vertexSet[i]->info)
					{
						gv->setVertexColor(i,GREEN);
						break;
					}
				}

			}
			else
			{
				gv->addNode(i, vertexSet[i]->viewer_pos.first, vertexSet[i]->viewer_pos.second);
				for(unsigned int j=0;j<vs.size();j++)
				{
					if(vs[j]==vertexSet[i]->info)
					{
						gv->setVertexColor(i,GREEN);
						break;
					}
				}
			}
			gv->setVertexLabel(i,label);
			gv->rearrange();
		}
		int id_counter=0;
		for(int i=0;i<getNumVertex();i++)
		{
			vector<Edge<T>  > edges = vertexSet[i]->adj;
			for(int j=0;j<edges.size();j++)
			{
				Vertex<T> * v=edges[j].dest;

				stringstream sstm;
				sstm <<"[" << edges[j].weight << "," << edges[j].flow << "]";
				string label = sstm.str();

				gv->addEdge(id_counter,i,findVertex(v->info),EdgeType::DIRECTED);
				gv->setEdgeLabel(id_counter,label);
				id_counter++;
				gv->rearrange();
			}
		}
		gv->rearrange();
}

template <class T>
double Graph<T>::getTotalWeight(vector<T> vs) {
	double res=0;
	Vertex<T> * current = getVertex(vs[0]);
	for(int i=1;i<vs.size();i++)
	{
		bool found=false;
		for(int j=0;j<current->adj.size();j++)
		{
			if(current->adj[j].dest->info==vs[i])
			{
				found=true;
				res+=current->adj[j].weight;
				current=current->adj[j].dest;
				break;
			}
		}
		if(!found) return -1;
	}
	return res;
}

template <class T>
void Graph<T>::invertEdges() {
	vector<Edge<T> > edges;
	for(unsigned int i=0;i<getNumVertex();i++)
	{
		cout<<"vertexSet[" << i << "]: " << vertexSet[i]->info << " - " <<vertexSet[i]->adj.size() <<" edges\n";
		for(int j=0;j<vertexSet[i]->adj.size();j++)
		{
			cout<<"\tedge[" << i << "] to: " << vertexSet[i]->adj[j].dest->info << "\n";
			edges.push_back(vertexSet[i]->adj[j]);
			vertexSet[i]->removeEdgeTo(vertexSet[i]->adj[j].dest);
			j--;
		}
	}

	for(unsigned int i=0;i<edges.size();i++)
	{
		addEdge(edges[i].dest->info, edges[i].orig->info, edges[i].weight, edges[i].flow);
	}
}

#endif /* GRAPH_H_ */
