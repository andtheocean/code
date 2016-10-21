package sa;
02
	 
03
	import java.util.ArrayList;
04
	import java.util.Collections;
05
	 
06
	public class Tour{
07
	 
08
	    // 保持城市的列表
09
	    private ArrayList tour = new ArrayList<City>();
10
	    // 缓存距离
11
	    private int distance = 0;
12
	 
13
	    // 生成一个空的路径
14
	    public Tour(){
15
	        for (int i = 0; i < SimulatedAnnealing.allCitys.size(); i++) {
16
	            tour.add(null);
17
	        }
18
	    }
19
	 
20
	    // 复杂路径
21
	    public Tour(ArrayList tour){
22
	        this.tour = (ArrayList) tour.clone();
23
	    }
24
	 
25
	    public ArrayList getTour(){
26
	        return tour;
27
	    }
28
	 
29
	    // Creates a random individual
30
	    public void generateIndividual() {
31
	        // Loop through all our destination cities and add them to our tour
32
	        for (int cityIndex = 0; cityIndex < SimulatedAnnealing.allCitys.size(); cityIndex++) {
33
	          setCity(cityIndex, SimulatedAnnealing.allCitys.get(cityIndex));
34
	        }
35
	        // 随机的打乱
36
	        Collections.shuffle(tour);
37
	    }
38
	 
39
	    // 获取一个城市
40
	    public City getCity(int tourPosition) {
41
	        return (City)tour.get(tourPosition);
42
	    }
43
	 
44
	    public void setCity(int tourPosition, City city) {
45
	        tour.set(tourPosition, city);
46
	        // 重新计算距离
47
	        distance = 0;
48
	    }
49
	 
50
	    // 获得当前距离的 总花费
51
	    public int getDistance(){
52
	        if (distance == 0) {
53
	            int tourDistance = 0;
54
	            for (int cityIndex=0; cityIndex < tourSize(); cityIndex++) {
55
	                City fromCity = getCity(cityIndex);
56
	                City destinationCity;
57
	                if(cityIndex+1 < tourSize()){
58
	                    destinationCity = getCity(cityIndex+1);
59
	                }
60
	                else{
61
	                    destinationCity = getCity(0);
62
	                }
63
	                tourDistance += fromCity.distanceTo(destinationCity);
64
	            }
65
	            distance = tourDistance;
66
	        }
67
	        return distance;
68
	    }
69
	 
70
	    // 获得当前路径中城市的数量
71
	    public int tourSize() {
72
	        return tour.size();
73
	    }
74
	 
75
	    @Override
76
	    public String toString() {
77
	        String geneString = "|";
78
	        for (int i = 0; i < tourSize(); i++) {
79
	            geneString += getCity(i)+"|";
80
	        }
81
	        return geneString;
82
	    }
83
	}
