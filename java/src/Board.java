import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

enum Direction {N, E, S, W};

public class Board {
	private Robot[] robots= new Robot[4];
	/*
	 * Blue:
	 * 	Saturn - A
	 * 	Triangle - C
	 * 	Moon - D
	 * 	Star - E
	 * Green:
	 * 	Saturn - F
	 * 	Triangle - H
	 * 	Moon - I
	 * 	Star - J
	 * Red:
	 * 	Saturn - Q
	 * 	Triangle - S
	 * 	Moon - T
	 * 	Star - U
	 * Yellow:
	 * 	Saturn - V
	 * 	Triangle - W
	 * 	Moon - X
	 * 	Star - Z
	 */
	private int[][] targets = new int[16][2];
	private ArrayList<Wall> walls = new ArrayList<Wall>();
	
	private int currGoal;
	private ArrayList<Integer> doneGoals = new ArrayList<Integer>();
	
	public Board(int type) {
		switch(type) {
		case 1:
			robots[0] = new Robot(Color.B, 13, 6);
			robots[1] = new Robot(Color.G, 2, 5);
			robots[2] = new Robot(Color.R, 11, 7);
			robots[3] = new Robot(Color.Y, 0, 4);
			
			targets[0][0]=6; targets[0][1]=5;
			targets[1][0]=12; targets[1][1]=6;
			targets[2][0]=6; targets[2][1]=10;
			targets[3][0]=13; targets[3][1]=11;
			
			targets[4][0]=3; targets[4][1]=14;
			targets[5][0]=1; targets[5][1]=2;
			targets[6][0]=9; targets[6][1]=13;
			targets[7][0]=9; targets[7][1]=1;
			
			targets[8][0]=10; targets[8][1]=4;
			targets[9][0]=14; targets[9][1]=14;
			targets[10][0]=3; targets[10][1]=6;
			targets[11][0]=1; targets[11][1]=13;

			targets[12][0]=8; targets[12][1]=10;
			targets[13][0]=4; targets[13][1]=9;
			targets[14][0]=14; targets[14][1]=2;
			targets[15][0]=6; targets[15][1]=1;
			
			walls.add(new Wall(Orientation.V, 4, 0));
			walls.add(new Wall(Orientation.V, 10, 0));
			walls.add(new Wall(Orientation.V, 6, 1));
			walls.add(new Wall(Orientation.V, 8, 1));
			walls.add(new Wall(Orientation.V, 0, 2));
			walls.add(new Wall(Orientation.V, 14, 2));
			walls.add(new Wall(Orientation.V, 10, 4));
			walls.add(new Wall(Orientation.V, 6, 5));
			walls.add(new Wall(Orientation.V, 2, 6));
			walls.add(new Wall(Orientation.V, 11, 6));
			walls.add(new Wall(Orientation.V, 6, 7));
			walls.add(new Wall(Orientation.V, 8, 7));
			walls.add(new Wall(Orientation.V, 6, 8));
			walls.add(new Wall(Orientation.V, 8, 8));
			walls.add(new Wall(Orientation.V, 3, 9));
			walls.add(new Wall(Orientation.V, 5, 10));
			walls.add(new Wall(Orientation.V, 8, 10));
			walls.add(new Wall(Orientation.V, 12, 11));
			walls.add(new Wall(Orientation.V, 7, 12));
			walls.add(new Wall(Orientation.V, 1, 13));
			walls.add(new Wall(Orientation.V, 8, 13));
			walls.add(new Wall(Orientation.V, 3, 14));
			walls.add(new Wall(Orientation.V, 14, 14));
			walls.add(new Wall(Orientation.V, 4, 15));
			walls.add(new Wall(Orientation.V, 11, 15));
			
			walls.add(new Wall(Orientation.H, 0, 5));
			walls.add(new Wall(Orientation.H, 0, 10));
			walls.add(new Wall(Orientation.H, 1, 1));
			walls.add(new Wall(Orientation.H, 1, 12));
			walls.add(new Wall(Orientation.H, 3, 6));
			walls.add(new Wall(Orientation.H, 3, 14));
			walls.add(new Wall(Orientation.H, 4, 9));
			walls.add(new Wall(Orientation.H, 6, 1));
			walls.add(new Wall(Orientation.H, 6, 4));
			walls.add(new Wall(Orientation.H, 6, 9));
			walls.add(new Wall(Orientation.H, 7, 6));
			walls.add(new Wall(Orientation.H, 7, 8));
			walls.add(new Wall(Orientation.H, 7, 11));
			walls.add(new Wall(Orientation.H, 8, 6));
			walls.add(new Wall(Orientation.H, 8, 8));
			walls.add(new Wall(Orientation.H, 8, 10));
			walls.add(new Wall(Orientation.H, 9, 1));
			walls.add(new Wall(Orientation.H, 9, 13));
			walls.add(new Wall(Orientation.H, 10, 4));
			walls.add(new Wall(Orientation.H, 12, 5));
			walls.add(new Wall(Orientation.H, 13, 10));
			walls.add(new Wall(Orientation.H, 14, 1));
			walls.add(new Wall(Orientation.H, 14, 13));
			walls.add(new Wall(Orientation.H, 15, 4));
			walls.add(new Wall(Orientation.H, 15, 9));
			
			break;
		case 2:
			break;
		}
		this.setRandomCurrGoal();
	}
	public Board(Board b) {
		//robots
		for(int i=0;i<4;i++) {
			this.robots[i]= new Robot(b.robots[i]);
		}
		
		//targets
		for(int i=0;i<16;i++) {
			this.targets[i][0] = b.targets[i][0];
			this.targets[i][1] = b.targets[i][1];
		}
		
		//walls
		this.walls = (ArrayList<Wall>) b.walls.clone();
		
		//goal
		this.currGoal = b.currGoal;
		this.doneGoals = (ArrayList<Integer>) b.doneGoals.clone(); 
	}
	
	public Robot[] getRobots() {
		return robots;
	}
	public int[][] getTargets() {
		return targets;
	}
	public ArrayList<Wall> getWalls() {
		return walls;
	}
	public int getCurrGoal() {
		return currGoal;
	}
	public ArrayList<Integer> getDoneGoals() {
		return doneGoals;
	}
	public boolean checkFinished() {
		return Arrays.equals(targets[currGoal], robots[(currGoal + 1) / 4].getCoords());
	}
	
	public void setCurrGoal(int currGoal) {
		this.currGoal = currGoal;
	}
	public void setRandomCurrGoal() {
		Random rand = new Random();
		this.currGoal = rand.nextInt(16);
	}
	public void addDoneGoal(int goal) {
		this.doneGoals.add(goal);
	}
	public boolean moveRobot(Color clr, Direction dir) {
		int clrInd = clr.ordinal();
		int[] coordsRobot = {robots[clrInd].getCoords()[0],robots[clrInd].getCoords()[1]};
		int max = -1;
		int min = 16;
		switch (dir) {
		case N:
			if (coordsRobot[1] == 0) return false;
			for (int i = 0; i < walls.size(); i++) {
				Wall wall = walls.get(i);
				if (wall.getOrientation() == Orientation.H && wall.getCoords()[0] == coordsRobot[0] &&
					wall.getCoords()[1]<coordsRobot[1] && wall.getCoords()[1]>max)
						max = wall.getCoords()[1]+1;
			}
			for (int i = 0; i < 4; i++) {
				if (i == clrInd) continue;
				Robot robot2 = robots[i];
				if (robot2.getCoords()[0] == coordsRobot[0] && robot2.getCoords()[1]<coordsRobot[1] &&
					robot2.getCoords()[1]>max) max = robot2.getCoords()[1]+1;
			}
			if (max != robots[clrInd].getCoords()[1]) robots[clrInd].setCoords(coordsRobot[0], Math.max(max,0));
			return coordsRobot[1] != robots[clrInd].getCoords()[1];
		case E:
			if (coordsRobot[0] == 15) return false;
			for (int i = 0; i < walls.size(); i++) {
				Wall wall = walls.get(i);
				if (wall.getOrientation() == Orientation.V && wall.getCoords()[1] == coordsRobot[1] &&
					wall.getCoords()[0]>=coordsRobot[0] && wall.getCoords()[0]<min)
					min = wall.getCoords()[0];
			}
			for (int i = 0; i < 4; i++) {
				if (i == clrInd) continue;
				Robot robot2 = robots[i];
				if (robot2.getCoords()[1] == coordsRobot[1] && robot2.getCoords()[0]>coordsRobot[0] &&
					robot2.getCoords()[0]<min) min = robot2.getCoords()[0]-1;
			}
			if (min != robots[clrInd].getCoords()[0]) robots[clrInd].setCoords(Math.min(min,15), coordsRobot[1]);
			return coordsRobot[0] != robots[clrInd].getCoords()[0];
		case S:
			if (coordsRobot[1] == 15) return false;
			for (int i = 0; i < walls.size(); i++) {
				Wall wall = walls.get(i);
				if (wall.getOrientation() == Orientation.H && wall.getCoords()[0] == coordsRobot[0] &&
					wall.getCoords()[1]>=coordsRobot[1] && wall.getCoords()[1]<min)
					min = wall.getCoords()[1];
			}
			for (int i = 0; i < 4; i++) {
				if (i == clrInd) continue;
				Robot robot2 = robots[i];
				if (robot2.getCoords()[0] == coordsRobot[0] && robot2.getCoords()[1]>coordsRobot[1] &&
					robot2.getCoords()[1]<min) min = robot2.getCoords()[1]-1;
			}
			if (min != robots[clrInd].getCoords()[1]) robots[clrInd].setCoords(coordsRobot[0], Math.min(min,15));
			return coordsRobot[1] != robots[clrInd].getCoords()[1];
		case W:
			if (coordsRobot[0] == 0) return false;
			for (int i = 0; i < walls.size(); i++) {
				Wall wall = walls.get(i);
				if (wall.getOrientation() == Orientation.V && wall.getCoords()[1] == coordsRobot[1] &&
					wall.getCoords()[0]<coordsRobot[0] && wall.getCoords()[0]>max)
					max = wall.getCoords()[0]+1;
			}
			for (int i = 0; i < 4; i++) {
				if (i == clrInd) continue;
				Robot robot2 = robots[i];
				if (robot2.getCoords()[1] == coordsRobot[1] && robot2.getCoords()[0]<coordsRobot[0] &&
					robot2.getCoords()[0]>max) max = robot2.getCoords()[0]+1;
			}
			if (max != robots[clrInd].getCoords()[0]) robots[clrInd].setCoords(Math.max(max,0), coordsRobot[1]);
			return coordsRobot[0] != robots[clrInd].getCoords()[0];
		}
		return false;
	}
	
	public ArrayList<Board>createChildrenBoards() {
		ArrayList<Board> res = new ArrayList<Board>();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Board b1 = new Board(this);
				if (b1.moveRobot(Color.values()[i], Direction.values()[j]))
				{
					res.add(b1);
				}
			}
		}
		return res;
	}
	
	public String toString() {
		//top line (walls)
		char[] top = new char[34];
		top[0] = (char)201;
		for (int i = 1; i < 32; i++)
			top[i] = (char)205;
		top[32]=(char)(187);
		top[33] = '\n';
		
		//bottom line (walls)
		char[] bottom = new char[34];
		bottom[0] = (char)200;
		for (int i = 1; i < 32; i++)
			bottom[i] = (char)205;
		bottom[32] = (char)188;
		bottom[33] = '\n';
		
		//left line (walls)
		char[] left = new char[31];
		for (int i = 0; i < 31; i++)
			left[i] = (char)186;
		
		//right line (walls)
		char[] right = new char[31];
		for (int i = 0; i < 31; i++)
			right[i] = (char)186;
		
		char[][] str = new char[31][31];
		for(int i=0;i<31;i++)
			Arrays.fill(str[i],' ');
		//grid (no-walls)
		for (int i = 1; i < 31; i += 2) {
			for (int j = 0; j < 31; j++) {
				if (j<13 || j>17 || i<13 || i>17) str[i][j] = (char)196;
			}
		}
		for (int i = 1; i < 31; i += 2) {
			for (int j = 0; j < 31; j++) {
				if (j<13 || j>17 || i<13 || i>17) str[j][i] = (char)179;
			}
		}
		for (int i = 1; i < 31; i += 2) {
			for (int j = 1; j < 31; j += 2) {
				if (j<13 || j>17 || i<13 || i>17) str[j][i] = (char)197;
			}
		}
		
		//center (walls)
		str[13][15] = (char)205;
		str[17][15] = (char)205;
		str[15][13] = (char)186;
		str[15][17] = (char)186;
		str[13][13] = (char)201;
		str[13][17] = (char)187;
		str[17][13] = (char)200;
		str[17][17] = (char)188;
		
		//walls
		for (int i = 0; i < walls.size(); i++) {
			Wall wall = walls.get(i);
			int x = wall.getCoords()[0];
			int y = wall.getCoords()[1];

			if (wall.getOrientation() == Orientation.V) {
				str[y * 2][x * 2 + 1] = (char)186;
				if (y == 0) top[x * 2 + 2] = (char)203;
				else if (y == 15) bottom[x * 2 + 2] = (char)202;
				else {
					if (str[y * 2 - 1][x * 2] == (char)205)
						str[y * 2 - 1][x * 2 + 1] = (char)187;
					else if (str[y * 2 - 1][x * 2 + 2] == (char)205)
						str[y * 2 - 1][x * 2 + 1] = (char)201;
					else if (str[y * 2 + 1][x * 2 + 2] == (char)205)
						str[y * 2 + 1][x * 2 + 1] = (char)200;
					else if (str[y * 2 + 1][x * 2] == (char)205)
						str[y * 2 + 1][x * 2 + 1] = (char)188;
				}
			}
			else if (wall.getOrientation() == Orientation.H) {
				str[y * 2 + 1][x * 2] = (char)205;
				if (x == 0) left[y * 2 + 1] = (char)204;
				else if (x == 15) right[y * 2 + 1] = (char)185;
				else {
					if (str[y * 2][x * 2 - 1] == (char)186)
						str[y * 2 + 1][x * 2 - 1] = (char)200;
					else if (str[y * 2][x * 2 + 1] == (char)186)
						str[y * 2 + 1][x * 2 + 1] = (char)188;
					else if (str[y * 2 + 2][x * 2 + 1] == (char)186)
						str[y * 2 + 1][x * 2 + 1] = (char)187;
					else if (str[y * 2 + 2][x * 2 - 1] == (char)186)
						str[y * 2 + 1][x * 2 - 1] = (char)201;
				}
			}
		}
		
		//targets
		char goals[] = { 'A','C','D','E' ,'F','H','I','J', 'Q','S','T','U', 'V','W','X','Z' };
		for (int i = 0; i < 16; i++) {
			int x = targets[i][0];
			int y = targets[i][1];
			str[y * 2][x * 2] = goals[i];
		}

		//goal
		str[15][15] = goals[currGoal];
		
		//robots
		for (int i = 0; i < 4; i++) {
			Robot robot = robots[i];
			int x = robot.getCoords()[0];
			int y = robot.getCoords()[1];
			char clr = '\0';
			switch (robot.getColor()) {
			case B:
				clr = 'B';
				break;
			case G:
				clr = 'G';
				break;
			case R:
				clr = 'R';
				break;
			case Y:
				clr = 'Y';
				break;
			}
			str[y*2][x*2] = clr;
		}
		
		//output
		String ret = "";
		for (int i = 0; i < 34; i++) {
			ret += top[i];
		}
		for (int i = 0; i < 31; i++) {
			ret += left[i];
			for (int j = 0; j < 31; j++) {
				ret += str[i][j];
			}
			ret += right[i];
			ret += "\n";
		}
		for (int i = 0; i < 34; i++) {
			ret += bottom[i];
		}
		return ret;
	}
	
}
