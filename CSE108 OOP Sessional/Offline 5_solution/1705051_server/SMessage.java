/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg1705051_server;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;
import java.util.StringTokenizer;
import static pkg1705051_server.ClientHandler.a;

/**
 *
 * @author Rasman Swargo
 */
public class SMessage {
    String input, username, type, str;
    int a[];
    int login,ind,id,islogout=0;
    DataOutputStream dos;
    Socket s;

    public SMessage(String str, int[] a, int id, DataOutputStream dos, Socket s) {
        this.str = str;
        this.a = a;
        this.id = id;
        this.dos = dos;
        this.s = s;
    }

    public int getIslogout() {
        return islogout;
    }
    

    
    public void process() throws FileNotFoundException, IOException
    {
                                char cS=str.charAt(3);
                                String msg="";
                                StringTokenizer multiTokenizer;
                                multiTokenizer = new StringTokenizer(str, "#");
                                while (multiTokenizer.hasMoreTokens())
                                    {
                                        msg=multiTokenizer.nextToken();
                                    }
                                if(cS=='s')
                                {
                                    ind=0;
                                    String loggedusers="";
                                    File file = new File("show.txt");
                                    Scanner sc = new Scanner(file);
                                    
                                    while (sc.hasNextLine())
                                    {
                                        String str3=sc.nextLine();
                                        if(a[ind]==1)
                                        {
                                            loggedusers=loggedusers+str3+" ";
                                        }
                                        ind++;
                                        if(ind==6) break;
                                        //System.out.println(ind + " " + a[ind]);
                                    }
                                    dos.writeUTF(loggedusers);
                                    System.out.println(msg);
                                    dos.flush();
                                }
                                
                                else if(cS=='l')
                                {
                                    islogout=1;
                                    System.out.println(msg);
                                    a[id]=0;
                                    //loggedinClients.remove(username);
                                    //dos.writeUTF("Logged Out");
                                    //s.close();
                                    //break;
                                }
    }
    
}
