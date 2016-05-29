import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;

public class Solver {

	public static ArrayList<Board> bfs(Board b) {
		BoardNode root = new BoardNode(b,0);
		
		LinkedList<BoardNode> q = new LinkedList<BoardNode>();
		q.push(root);
		
		ArrayList<Board> visited = new ArrayList<Board>();
		visited.add(root.getState());
		
		while(!q.isEmpty()) {
			BoardNode curr = q.poll();
			
			//generate successors
			ArrayList<Board> children = curr.getState().createChildrenBoards();
			for(int i=0; i< children.size();i++) {
				BoardNode child = new BoardNode(children.get(i),0);
				if(child.getState().checkFinished()) {
					curr.addChild(child);
					return child.getPathToRoot();
				}
				
				if(!visited.contains(child.getState())) {
					curr.addChild(child);
					visited.add(child.getState());
					q.add(child);
				}
			}
		}
		
		return new ArrayList<Board>();
	}
	
	public static ArrayList<Board> astar(Board b) {
		
		int[][] heurBoard = b.heuristicPreComp();
		int robotInd = (b.getCurrGoal() + 1) / 4;
		
		BoardNode root = new BoardNode(b,heurBoard[b.getRobots()[robotInd].getCoords()[1]][b.getRobots()[robotInd].getCoords()[0]]);
		ArrayList<BoardNode> openSet = new ArrayList<BoardNode>();
		openSet.add(root);
		
		ArrayList<BoardNode> closedSet = new ArrayList<BoardNode>();
		
		while(!openSet.isEmpty()) {
			openSet.sort(new Comparator<BoardNode>() {
			    public int compare(BoardNode o1, BoardNode o2) {
			        return o1.compareTo(o2);
			    }
			});
			
			BoardNode curr = openSet.get(0);
			openSet.remove(0);
			closedSet.add(curr);
			
			int cost=curr.getCost()+1;
			ArrayList<Board> children = curr.getState().createChildrenBoards();
			for(int i=0;i<children.size();i++) {
				BoardNode child = new BoardNode(children.get(i),
						heurBoard[children.get(i).getRobots()[robotInd].getCoords()[1]][children.get(i).getRobots()[robotInd].getCoords()[0]]);
				if(child.getState().checkFinished()) {
					curr.addChild(child);
					return child.getPathToRoot();
				}
				
				//search openSet
				int foundOpen = openSet.indexOf(child);
				if(foundOpen != -1 && cost < openSet.get(foundOpen).getCost())
					openSet.remove(child);
				
				//search closedSet
				int foundClosed = closedSet.indexOf(child);
				if(foundClosed != -1 && cost < closedSet.get(foundClosed).getCost())
					closedSet.remove(child);
				
				if(!openSet.contains(child) && !closedSet.contains(child)) {
					curr.addChild(child);
					openSet.add(child);
				}
			}
		}
		
		return new ArrayList<Board>();
	}
	
	public static void main(String[] args) {
		Board b = new Board(1);
		b.setCurrGoal(12);
		
		ArrayList<Board> res = astar(b);
		Collections.reverse(res);
		
		FileOutputStream out = null;
		try {
			out = new FileOutputStream("0.txt");
			out.write(b.toString().getBytes());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		for(int i=0; i<res.size(); i++) {
			try {
				out = new FileOutputStream((i+1)+".txt");
				out.write(res.get(i).toString().getBytes());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
