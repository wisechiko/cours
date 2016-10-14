import java.io.*;
import java.net.*;

class ServiceThread1 extends Thread {
      public Socket socket_thread;
 
      public ServiceThread1 (Socket socket){
           this.socket_thread = socket;
           start();
      }

      public void run()
      {
	      try{
                      while(true)
		      {
			      PrintStream out = new PrintStream( socket_thread.getOutputStream() );
			      out.println( "Hello World!" );
		      }
		//      socket_thread.close();
	      }
	      catch (Exception e)
	      {}
      }

}
