/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.h_da.fbi.db2.stud.Entity;

import java.util.ArrayList;
import javax.persistence.Embeddable;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.ManyToOne;
import javax.persistence.Id;

/**
 *
 * @author sonya
 */
@Embeddable
public class Frage {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    private int id;
    private int answer;
    private String frage;
    private ArrayList <String> allAnswers = new ArrayList<String>();
    private Kategory kategorie;
    
   
    public int getId() {
        return id;
    }

    public int getAnswer() {
        return answer;
    }

    public ArrayList <String> getAllAnswers() {
        return allAnswers;
    }

    @ManyToOne
    public Kategory getKategorie() {
        return kategorie;
    }
    
    
}
