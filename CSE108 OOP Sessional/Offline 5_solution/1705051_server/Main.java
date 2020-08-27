/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg1705051_server;

/**
 *
 * @author Rasman Swargo
 */
import java.net.*;  
import java.io.*;  
import java.util.Scanner;

public class Main {

    public static void main(String args[])throws IOException{  
        ServerSocket ss = new ServerSocket(5056); 
		
		
		while (true) 
		{ 
			Socket s = null; 
			
			try
			{ 
			
				s = ss.accept(); 				 
				DataInputStream dis = new DataInputStream(s.getInputStream()); 
				DataOutputStream dos = new DataOutputStream(s.getOutputStream());
				Thread t = new ClientHandler(s, dis, dos); 
				t.start(); 
				
			} 
			catch (Exception e){ 
				s.close(); 
				e.printStackTrace(); 
			} 
		}
          
}
}
