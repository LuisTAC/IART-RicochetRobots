import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;

public class Solver {

	public static void main(String[] args) {
		Board b = new Board(1);
		b.setCurrGoal(12);
		
		ArrayList<Board> children = b.createChildrenBoards();
		
		BoardNode root = new BoardNode(b);
		for(int i=0;i<children.size();i++) {
			BoardNode child = new BoardNode(children.get(i));
			root.addChild(child);
		}
		
		FileOutputStream out = null;
		try {
			out = new FileOutputStream("0.txt");
			out.write(root.getState().toString().getBytes());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ArrayList<BoardNode> succs = root.getChildren();
		for(int i=0; i<succs.size(); i++) {
			try {
				out = new FileOutputStream((i+1)+".txt");
				out.write(succs.get(i).getState().toString().getBytes());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}

}
