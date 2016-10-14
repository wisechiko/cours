import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;


class HelloServer4 {
	public static void main(String argv[]) throws Exception
	{

		ServerSocket serversocket = new ServerSocket(1111);
                int i=0;
                while(i != 5)
                {
	               Socket socket = serversocket.accept();
                       ServiceThread service = new ServiceThread(socket);
                       i++;
                }
	}
}

