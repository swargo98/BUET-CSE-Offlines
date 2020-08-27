/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg1705051_server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Rasman Swargo
 */
public class BMessage {
    private String message,sender;
    private boolean admin=false;
    //final DataInputStream inp;
    DataOutputStream out;
    
    

    BMessage(String message, String type, DataOutputStream out, String sender) {
        this.message = message;
        if(type.equals("admin"))this.admin = true;
        this.out = out;
        this.sender = sender;
        System.out.println(admin + message);
    }

    void Handle() throws IOException {
        if(!admin){
            //System.out.println("admin na vag!");
            out.writeUTF("You Don't Have The Privilege To Broadcast!");
        }
        else{
            for(ClientHandler x:ClientHandler.loggedinClients.values()){
                //System.out.println("Khela Hobe");
                DataOutputStream dos=x.getdos();
                if (!x.getusername().equals(sender)) {
                    //System.out.println("Khela Hocche");
                    System.out.println(sender+": "+message);
                    dos.writeUTF(sender+": "+message);
                    
                    //System.out.println("Khela Hocche 2");
                    dos.flush();
                }
            }
            out.writeUTF("Message Successfully Sent!");
        }
    }

 
}
