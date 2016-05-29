import java.util.ArrayList;

public class BoardNode {
	private Board state;
	private int cost=0;
	private int heurValue;
	private BoardNode parent = null;
	private ArrayList<BoardNode> children = new ArrayList<BoardNode>();
	
	public BoardNode(Board state) {
		this.state=state;
	}
	
	public Board getState() {
		return state;
	}
	public int getCost() {
		return cost;
	}
	public int getHeurValue() {
		return heurValue;
	}
	public int getTotalCost() {
		return cost+heurValue;
	}
	public BoardNode getParent() {
		return parent;
	}
	public ArrayList<BoardNode> getChildren() {
		return children;
	}
	public ArrayList<Board> getPathToRoot() {
		ArrayList<Board> ret = new ArrayList<Board>();

		BoardNode curr = this;
		while(curr.parent!=null) {
			ret.add(curr.state);
			curr = curr.parent;
		}
		
		return ret;
	}
	public void addChild(BoardNode child) {
		child.parent=this;
		child.cost=this.cost+1;
		this.children.add(child);
		
	}
}
