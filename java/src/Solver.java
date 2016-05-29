import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;

public class Solver {

	public static ArrayList<Board> bfs(Board b) {
		BoardNode root = new BoardNode(b);
		
		LinkedList<BoardNode> q = new LinkedList<BoardNode>();
		q.push(root);
		
		ArrayList<Board> visited = new ArrayList<Board>();
		visited.add(root.getState());
		
		while(!q.isEmpty()) {
			BoardNode curr = q.poll();
			
			//generate successors
			ArrayList<Board> children = curr.getState().createChildrenBoards();
			for(int i=0; i< children.size();i++) {
				BoardNode child = new BoardNode(children.get(i));
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
	
	public static void main(String[] args) {
		Board b = new Board(1);
		b.setCurrGoal(12);
		
		/*
		ArrayList<Board> res = bfs(b);
		
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
		}*/
	}

}
