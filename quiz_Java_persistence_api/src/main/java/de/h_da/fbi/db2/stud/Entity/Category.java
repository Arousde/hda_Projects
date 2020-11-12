package de.h_da.fbi.db2.stud.Entity;

import java.util.ArrayList;
import java.util.List;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.OrderColumn;

@Entity
@NamedQueries({
@NamedQuery(name="Category.findAll",
query="select c from Category c"),
})
public class Category {

    public Category() {

    }
    public Category(String name) {
        this.category_id = name;

    }
    @Id
    private String category_id;
    //  Hier fuer bidirektionales OneToMany ohne weitere Tabelle    
   @OneToMany(mappedBy = "category")
   @OrderColumn(name = "reihenfolge")
    private List<Question> cFragen  = new ArrayList();

   @ManyToOne
   private Game game;
    

    public void setName(String name) {
        this.category_id = name;
    }

    public String getName() {
        return category_id;
    }

    public List<Question> getcFragen() {
        return cFragen;
    }

}
