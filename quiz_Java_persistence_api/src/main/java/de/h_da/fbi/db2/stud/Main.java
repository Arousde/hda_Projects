package de.h_da.fbi.db2.stud;

import de.h_da.fbi.db2.stud.Entity.Question;
import de.h_da.fbi.db2.stud.Entity.Category;
import de.h_da.fbi.db2.stud.Entity.Game;

import de.h_da.fbi.db2.tools.CsvDataReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;
import org.eclipse.persistence.config.PersistenceUnitProperties;

/**
 * Main Class.
 *
 * @version 0.1.1
 * @since 0.1.0
 * @author arous 
 */
public class Main {

    /**
     * Main Method and Entry-Point.
     *
     * @param lines
     */
    public static Game dateneinlesen(List<String[]> lines) {

        final Game s = new Game();

        List<Question> myFragen = new ArrayList<>();

        for (int i = 1; i < lines.size(); i++) {

            Category myKategory = new Category(lines.get(i)[7]);
            List<String> myanswers = new ArrayList<>();
            myanswers.add(lines.get(i)[2]);
            myanswers.add(lines.get(i)[3]);
            myanswers.add(lines.get(i)[4]);
            myanswers.add(lines.get(i)[5]);
            int loesung = Integer.parseInt(lines.get(i)[6]);
            int id = Integer.parseInt(lines.get(i)[0]);
            Question myFrage = new Question(id, loesung, lines.get(i)[1], myanswers, myKategory);

            myKategory.getcFragen().add(myFrage);

            if (!s.getKat().isEmpty()) {
                boolean redund = false;
                for (int k = 0; k < s.getKat().size(); k++) {

                    if (s.getKat().get(k).getName().equals(myKategory.getName())) {
                        s.getKat().get(k).getcFragen().add(myFrage);
                        redund = true;
                    }

                }

                if (redund == false) {
                    s.getKat().add(myKategory);
                }
            } else {
                s.getKat().add(myKategory);
            }

        }


        System.out.println(s.getKat().size() );

        return s;
    }

    

    public static void main(String[] args) {
//
//        Game s = new Game();
//        try {
//            //Read default csv
//            final List<String[]> defaultCsvLines = CsvDataReader.read();
//
//         //   s = dateneinlesen(defaultCsvLines);
//
//            //Read (if available) additional csv-files and default csv-file
//            List<String> availableFiles = CsvDataReader.getAvailableFiles();
//            for (String availableFile : availableFiles) {
//                final List<String[]> additionalCsvLines = CsvDataReader.read(availableFile);
//
//            }
//        } catch (URISyntaxException use) {
//            System.out.println(use);
//        } catch (IOException ioe) {
//            System.out.println(ioe);
//        }
//
                  Menu menu = new Menu();
                  menu.setVisible(true);
   }
}
