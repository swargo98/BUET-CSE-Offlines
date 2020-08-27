/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg1705051_server;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

class ClientHandler extends Thread 
{ 
	 
	final DataInputStream dis; 
	DataOutputStream dos; 
	final Socket s;
        int ind,id;
        int login=0;
        static int a[]= new int [6];
        String username="";
        String type="";
	static HashMap<String,ClientHandler> loggedinClients = new HashMap<>();

	// Constructor 
	public ClientHandler(Socket s, DataInputStream dis, DataOutputStream dos) 
	{ 
		this.s = s; 
		this.dis = dis; 
		this.dos = dos; 
	} 
        Socket getClient() {return s;}
        String getusername() {return username;}
        DataOutputStream getdos(){return dos;}
    
	@Override
	public void run() 
	{ 
		while (true) 
		{ 
                    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
                    String str="",str2="";
                        try {
                            str=dis.readUTF();
                            System.out.println("client says: "+str);
                            char c = str.charAt(1);
                            if(c=='L')
                            {
                                LMessage lmessage=new LMessage(str, login, dos);
                                lmessage.login();
                                username=lmessage.getUsername();
                                id=lmessage.getId();
                                if(id<6)
                                {
                                    a[id]=1;
                                    login=1;
                                }
                                loggedinClients.put(username, this);            
                            }
                            
                            else if(c=='S')
                            {
                                SMessage smessage= new SMessage(str,a,id, dos,s);
                                smessage.process();
                                if(smessage.getIslogout()==1)
                                {
                                     s.close();
                                     loggedinClients.remove(username);
                                     break;
                                }
                            }
                            
                            else if(c=='B')
                            {
                                String msg="";
                                StringTokenizer multiTokenizer;
                                multiTokenizer = new StringTokenizer(str, "#");
                                while (multiTokenizer.hasMoreTokens())
                                    {
                                        msg=multiTokenizer.nextToken();
                                    }
                                System.out.println(msg);
                                BMessage broadcast = new BMessage(msg, type, dos, username);
                                broadcast.Handle();
                            }
                            //str2=br.readLine();
                            //dout.writeUTF(str2);
                            dos.flush();
                        } catch (IOException ex) {
                            Logger.getLogger(ClientHandler.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    
                }
                     try
                    { 
                        //this.s.close();
                        this.dis.close(); 
                        this.dos.close(); 
              
                    }catch(IOException e){ 
                        e.printStackTrace(); 
                    } 
                   
                    //s.close();
                
	} 
} 
