/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.h_da.fbi.db2.stud.Entity;
import java.util.Collection;
import java.util.List;
import javax.persistence.ElementCollection;
import javax.persistence.Embeddable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.ManyToOne;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;
import javax.persistence.OrderColumn;

/**
 *
 * @author sonya
 */

@Entity

public class Question {

    public Question() {
    }
    
    @Id
    private int id;
    
    private int answer;
    private String question;
    
    
    @ElementCollection
    @OrderColumn(name = "answer")
    private List<String> allAnswers ;
    
    
    @ManyToOne
    private Category category;
   //@JoinColumn (name = "category_id" , referencedColumnName = "category_id" , nullable = false)
   
    

    public Question(int id, int answer, String quest, List<String> allAnswers, Category cat) {
        this.id = id;
        this.answer = answer;
        this.question = quest;
        this.allAnswers = allAnswers;
        this.category = cat;
    }
    
   
    
    public int getId() {
        return id;
    }

    public int getAnswer() {
        return answer;
    }

    public List<String> getAllAnswers() {
        return allAnswers;
    }

   
    public Category getKategorie() {
        return category;
    }

    /**
     * @return the frage
     */
    public String getFrage() {
        return question;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @param answer the answer to set
     */
    public void setAnswer(int answer) {
        this.answer = answer;
    }

    /**
     * @param question the question to set
     */
    public void setQuestion(String question) {
        this.question = question;
    }

    /**
     * @param allAnswers the allAnswers to set
     */
    public void setAllAnswers(List<String> allAnswers) {
        this.allAnswers = allAnswers;
    }

    /**
     * @param kategorie the kategorie to set
     */
    public void setKategorie(Category kategorie) {
        this.category = kategorie;
    }

   
    
    
}
