/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg1705051_client;

/**
 *
 * @author Rasman Swargo
 */

import java.net.*;  
import java.io.*;  
class MyClient{  
}  

public class Main {

    public static void main(String args[])throws Exception{  
        try (Socket s = new Socket("localhost",5056)) {
            DataInputStream din=new DataInputStream(s.getInputStream());
            try (DataOutputStream dout = new DataOutputStream(s.getOutputStream())) {
                BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
                String str="",str2="";
                while(true){
                    str=br.readLine();
                    char lout=str.charAt(3);
                    char cmd=str.charAt(1);
                    dout.writeUTF(str);
                    dout.flush();
                    if(lout=='l' && cmd=='S')
                    {
                        s.close();
                        break;
                    }
                    /*if(cmd=='C')
                    {
                        
                    }*/
                    str2=din.readUTF();
                    System.out.println("Server says: "+str2);
                }
            }
        }  
}
    
}
