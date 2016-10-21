package Company;
class Employee
{
	public String name;
	public int    salary;
    
    public String getSalary()
    {
    	String str;
    	str="name:"+name+"\nSalary"+salary;
    	return str;
    }
}

public class Manager extends Employee
{
	public String department;
	public String getSalary()
	{
		return super.getSalary()+"\nDepartment:"+department;
	}
}

