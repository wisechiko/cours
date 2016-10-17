import java.io.*;
import java.net.*;



class ServiceThread extends Thread {
      public Socket socket_thread;
 
      public ServiceThread (Socket socket){
           this.socket_thread = socket;
           start();
      }

      public void run()
      {
	      try{
		      PrintStream out = new PrintStream( socket_thread.getOutputStream() );
		      out.println( "Hello World!" );
		      socket_thread.close();
	      }
	      catch (Exception e)
	      {}
      }

}

