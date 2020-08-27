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
import java.util.Scanner;
import java.util.StringTokenizer;
import static pkg1705051_server.ClientHandler.a;

/**
 *
 * @author Rasman Swargo
 */
public class LMessage {
    String input, username, type;
    int login,ind,id=6;
    DataOutputStream dos;

    public LMessage(String input, int login, DataOutputStream dos) {
        this.input = input;
        this.login = login;
        this.dos = dos;
        System.out.println("Hello");
    }

    public String getUsername() {
        return username;
    }

    public int getLogin() {
        return login;
    }

    public int getId() {
        return id;
    }
    
    
    public void login() throws FileNotFoundException, IOException
    {
        StringTokenizer multiTokenizer;
                                multiTokenizer = new StringTokenizer(input, "#");
                                for(int i=0; i<4; i++)
                                    {
                                        if(i<2) username=multiTokenizer.nextToken();
                                        else type=multiTokenizer.nextToken();
                                    }
                                System.out.println(username+type);
                                ind=0;
                                File file = new File("users.txt");
                                Scanner sc = new Scanner(file);
                                
                                while (sc.hasNextLine())
                                {
                                    if(login==1)
                                        {
                                            dos.writeUTF("You are already logged in");
                                            break;
                                        }
                                    String str3=sc.nextLine();
                                    if(str3.equals(input))
                                    { 
                                        dos.writeUTF("login successful");
                                        login=1;
                                        a[ind]=1;
                                        id=ind;
                                        break;
                                    }
                                    ind++;
                                }
                                if(ind==6)  dos.writeUTF("Wrong Username/Password/Type.");
    }
    
}
