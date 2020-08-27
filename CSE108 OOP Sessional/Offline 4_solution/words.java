/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wordfreq;

/**
 *
 * @author Rasman Swargo
 */
public class words {
    private String word;
    private int count;

    public words(String word, int count) {
        this.word = word;
        this.count = count;
    }

    public String getWord() {
        return word;
    }

    public int getCount() {
        return count;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public void setCount(int count) {
        this.count = count;
    }
    
    public void increaseone()
    {
        count++;
    }
    
       
}

