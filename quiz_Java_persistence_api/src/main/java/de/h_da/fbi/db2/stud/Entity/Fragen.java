/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.h_da.fbi.db2.stud.Entity;

import java.util.ArrayList;
import javax.persistence.Embeddable;

/**
 *
 * @author arous
 */
@Embeddable
public class Fragen {
    
    private int id;
    private int answer;
    private ArrayList <String> allAnswers = new ArrayList<String>();

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @return the answer
     */
    public int getAnswer() {
        return answer;
    }

    /**
     * @return the allAnswers
     */
    public ArrayList <String> getAllAnswers() {
        return allAnswers;
    }
    
    
}
