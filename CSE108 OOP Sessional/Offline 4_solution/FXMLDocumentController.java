package wordfreq;

import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;

/**
 *
 * @author Rasman Swargo
 */
public class FXMLDocumentController implements Initializable {

    @FXML
    private TableView<words> wordfrequency;
    @FXML
    private TableColumn<words, String> word;
    @FXML
    private TableColumn<words, Integer> freq;
    
    ObservableList<words>list=FXCollections.observableArrayList();
    ObservableList<words>listold=FXCollections.observableArrayList();
    
    @FXML
    private Label fileload;

    @FXML
    private void filechooser(ActionEvent event) {
        list.clear();
        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new ExtensionFilter("TEXT files (*.txt)", "*.txt"));
        File file= fc.showOpenDialog(null);
        if(file!=null)
        {
            fileload.setText(file.getName() + " Loaded. Press Update to see Word Frequency.");
            try {
                Scanner sc = new Scanner(file);
                 while(sc.hasNext()){
                    String str=sc.nextLine();
                     //System.out.println(str);
                    StringTokenizer multiTokenizer;
                    multiTokenizer = new StringTokenizer(str, " ://.-,;?[]{}()!~`_+=\"*");
 
                        while (multiTokenizer.hasMoreTokens())
                        {
                            String s=multiTokenizer.nextToken();
                            s=s.toLowerCase();
                            int size=list.size();
                            int i;
                            for(i=0; i<size; i++){
                                String temporary=list.get(i).getWord();
                                if(s.equals(temporary)){
                                    list.get(i).increaseone();
                                    break;
                                }
                            }                      
                            if(i!=size) continue;
                            list.add(new words(s, 1));
                        }
                }
            } catch (FileNotFoundException ex) {
                Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            
            
        }
    }

    @FXML
    private void updatebtn(ActionEvent event) {
       
        listold.clear();
        int size=list.size();
        fileload.setText("Total Distinct Words: "+size);
        int i;
        for(i=0; i<size; i++){
        listold.add(list.get(i));
        }                       
        wordfrequency.setItems(listold);
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        word.setCellValueFactory(new PropertyValueFactory<words, String>("word"));
        freq.setCellValueFactory(new PropertyValueFactory<words, Integer>("count"));
    }    
    
}
