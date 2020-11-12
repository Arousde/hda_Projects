/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.h_da.fbi.db2.stud.Entity;

import java.util.Collection;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.OneToMany;

/**
 *
 * @author arous
 */
@Entity
public class Kategory {
    
    @Id
    private String name;
    private Collection<Frage> cFragen;

    
    public String getName() {
        return name;
    }

    
    @OneToMany(mappedBy = "kategory")
    public Collection<Frage> getcFragen() {
        return cFragen;
    }
}
