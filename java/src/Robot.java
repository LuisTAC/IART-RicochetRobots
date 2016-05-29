enum Color { B, G, R, Y };

public class Robot {
	private Color color;
	private int[] start = new int[2];
	private int[] coords = new int[2];
	
	public Robot(Color c, int x, int y) {
		this.color = c;
		this.start[0]=x;
		this.start[1]=y;
		this.coords[0]=x;
		this.coords[1]=y;
	}
	public Robot(Robot r) {
		this.color = r.color;
		this.start[0]=r.start[0];
		this.start[1]=r.start[1];
		this.coords[0]=r.coords[0];
		this.coords[1]=r.coords[1];
	}
	
	public Color getColor() {
		return color;
	}
	public int[] getStart() {
		return start;
	}
	public int[] getCoords() {
		return coords;
	}
	
	public void setCoords(int x, int y) {
		this.coords[0]=x;
		this.coords[1]=y;
	}
	
}