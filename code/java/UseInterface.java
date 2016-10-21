/* 
* @Author: Administrator
* @Date:   2016-02-17 09:01:17
* @Last Modified by:   Administrator
* @Last Modified time: 2016-02-17 09:09:25
*/

public class UseInterface
 {
    public static void main(String[] args) 
    {
    	Computer p=new Computer();
    	System.out.println(p.ADDRESS+p.MAKER);
    	System.out.println("the price of the Computer:"+p.getPrice()*10+ " thousands");


    }
}

class Computer implements Product
{
	public int getPrice()
	{
		return 1;
	}
}