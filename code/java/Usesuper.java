/* 
* @Author: Administrator
* @Date:   2016-02-16 16:08:22
* @Last Modified by:   Administrator
* @Last Modified time: 2016-02-16 23:24:31
*/
public class Usesuper
{
	public static void main (String args[])
	{
		Manager m=new Manager();
		m.name="王飞";
		m.salary=10000;
		m.department="yewu";
		System.out.println(m.getSalary());
	}
}

class Employee
{
	public String name;
	public int salary;
	public String getSalary()
	{
		String str;
		str="name:"+name+"\nSalary:"+salary;
		return str;
	}
}

class Manager extends Employee
{
	public String department;

	public String getSalary()
	{
		return super.getSalary()+"\nDepartment:"+department;
	}
}