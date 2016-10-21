package sa;
02
	 
03
	public class City {
04
	    int x;
05
	    int y;
06
	 
07
	    // 生成一个随机的城市
08
	    public City(){
09
	        this.x = (int)(Math.random()*200);
10
	        this.y = (int)(Math.random()*200);
11
	    }
12
	 
13
	    public City(int x, int y){
14
	        this.x = x;
15
	        this.y = y;
16
	    }
17
	 
18
	    public int getX(){
19
	        return this.x;
20
	    }
21
	 
22
	    public int getY(){
23
	        return this.y;
24
	    }
25
	 
26
	    // 计算两个城市之间的距离
27
	    public double distanceTo(City city){
28
	        int xDistance = Math.abs(getX() - city.getX());
29
	        int yDistance = Math.abs(getY() - city.getY());
30
	        double distance = Math.sqrt( (xDistance*xDistance) + (yDistance*yDistance) );
31
	 
32
	        return distance;
33
	    }
34
	 
35
	    @Override
36
	    public String toString(){
37
	        return getX()+", "+getY();
38
	    }
39
	}
