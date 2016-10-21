import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class WelcomeApplet extends Applet implements ActionListener
{
	Label lblName;
	TextFild txtName;
	TextFild txtDisp;

	public void init()
	{
		lblName=new Label("please input your naem");
		txtName=new TextFild(8);
		txtDisp=new TextFild(20);
		add(lblName);
		add(txtName);
		add(txtDisp);
		txtName.addActionListener(this);
	}

	public void actionPerformed(ActionEvent e)
	{
		txtDisp.setText(txtName.getText()+"欢迎来到你的java世界");
	}

	public static void main(String args[])
	{
		Frame f=new Frame("欢迎");
		f.addWindowListener(new WindowAdaper()){
		public void windowClosing(WindowEvent evt)
		{
			System.exit(0);
		}
		}
		;
		WelcomeApplet a=new WelcomeApplet();
		a.init();
		f.add("Center",a);
		f.setSize(400,300);
		f.show();
		a.start();
	}
}