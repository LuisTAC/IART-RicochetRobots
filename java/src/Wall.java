import java.util.Arrays;

enum Orientation { H, V };

public class Wall {
	private Orientation orientation;
	private int[] coords = new int[2];
	
	public Wall(Orientation or , int x, int y) {
		this.orientation = or ;
		this.coords[0]=x;
		this.coords[1]=y;
	}
	public Wall(Wall w) {
		orientation = w.orientation;
		coords[0]=w.coords[0];
		coords[1]=w.coords[1];
	}
	
	public Orientation getOrientation() {
		return orientation;
	}
	public int[] getCoords() {
		return coords;
	}
	
	public void setOrientation(Orientation or) {
		this.orientation=or;
	}
	public void setCoords(int x,int y) {
		this.coords[0]=x;
		this.coords[1]=y;
	}
	
	public boolean equals(Object obj) {
		if (!(obj instanceof Wall))
            return false;
        if (obj == this)
            return true;
        
        Wall rhs = (Wall)obj;
        if(this.orientation!=rhs.orientation) return false;
        
        if(!Arrays.equals(this.coords, rhs.coords)) return false;
        
        return true;
	}
	
}
