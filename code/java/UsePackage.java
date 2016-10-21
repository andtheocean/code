/* 
* @Author: Administrator
* @Date:   2016-02-17 00:16:23
* @Last Modified by:   Administrator
* @Last Modified time: 2016-02-17 00:32:27
*/

//import Company.Manager;
import Company.Manager;

public class UsePackage
{
	public static void main(String[] args)
	{
		Manager m=new Manager();
		m.name="wangFei";
		m.salary=10000;
		m.department="business department";
		System.out.println(m.getSalary());
	}
}