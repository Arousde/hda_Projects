package de.h_da.fbi.db2.stud.Entity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import javax.persistence.ElementCollection;
import javax.persistence.Embeddable;
import javax.persistence.Embedded;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.OrderColumn;
import javax.persistence.Temporal;

@Entity
public class Game {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int gId;

   @OneToMany(mappedBy = "game")
   @OrderColumn(name = "reihenfolge")
    private List<Category> allCategories = new ArrayList();

    private String gamerName;
    private int numberCat;

    
   @ElementCollection
    @OrderColumn(name = "genQuest")
   private  List<Integer> genQuestions = new ArrayList();
   
   @ElementCollection
    @OrderColumn(name = "result")
   private  List<Integer> result = new ArrayList();

    public Game() {

    }

    public List<Category> getKat() {
        return allCategories;
    }

    private static  Game gameinstance  = null;

    
    public static void setGame_instance(Game s) {
         gameinstance = s ;
    }
    
    public static Game getGame_instance() {
       return gameinstance ;
    }
}
