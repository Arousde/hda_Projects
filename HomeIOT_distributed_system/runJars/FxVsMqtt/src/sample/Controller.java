package sample;

import javafx.fxml.FXML;
import javafx.scene.control.TableView;
import com.mongodb.*;
import java.net.UnknownHostException;
public class Controller {
    private MongoClient mongoClient ;
    private DB myMongoDb ;
    private DBCollection collection;
    private DBObject homeobj ;
    private Home home ;

    @FXML
    private TableView tab ;

    @FXML
    private void reload() {
        System.out.println("Clicked");
        //Home home = new Home("first","test","test","test","test","test");
        //tab.getItems().add(home);
        try {
            connect();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
           insertRows();
    }

    public void connect() throws UnknownHostException {
        this.mongoClient = new MongoClient(new MongoClientURI("mongodb://Arousde:sanymany1992@ds159782.mlab.com:59782/homezentrale"));
        System.out.println("connected");
        createDBandColections();
    }
    public void createDBandColections() {
        this.myMongoDb = this.mongoClient.getDB("homezentrale");
        this.collection = myMongoDb.getCollection("Home");
    }

    public void insertRows() {
        tab.getItems().clear();
        DBCursor cursor = this.collection.find();
        while (cursor.hasNext()) {
            DBObject obj = cursor.next();
            String id = (String) obj.get("_id");
            String name = (String) obj.get("Name");
            String temperature = String.valueOf(obj.get("Temperature")) ;
            String luftfeuchtigkeit = String.valueOf(obj.get("Luftfeuchtigkeit")) ;
            String drehzahldesBadluefters = String.valueOf(obj.get("DrehzahldesBadluefters")) ;
            String fensterzustend = (String) obj.get("Fensterzustend");
            Home home = new Home(id,name,temperature,luftfeuchtigkeit,drehzahldesBadluefters,fensterzustend);
            tab.getItems().add(home);

        }
    }
}
