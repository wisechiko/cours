import java.io.*;
public class ThreadExemple extends Thread {


	public static void main(String argv[]) {
        new ThreadExemple();
        }


	public ThreadExemple() {
		start();
		while(true)
			System.out.println("toto");
	}

	public void run(){
		while(true)
			System.out.println("tata");

	}

} 
