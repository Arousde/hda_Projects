package sample;
import javafx.beans.property.*;
public class Home {
    final  private  SimpleStringProperty id = new SimpleStringProperty("");
    final private  SimpleStringProperty name = new SimpleStringProperty("");
    final private  SimpleStringProperty temperatur = new SimpleStringProperty("");
    final private  SimpleStringProperty luftfeuchtigkeit = new SimpleStringProperty("");
    final private  SimpleStringProperty fensterzustend = new SimpleStringProperty("");
    final private  SimpleStringProperty drehzahldesBadluefters = new SimpleStringProperty("");

   public Home(String id ,String name ,String temperatur ,String luftfeuchtigkeit ,String fensterzustend ,String drehzahldesBadluefters ) {

       setId(id);
       setName(name);
       setTemperatur(temperatur);
       setLuftfeuchtigkeit(luftfeuchtigkeit);
       setFensterzustend(fensterzustend);
       setDrehzahldesBadluefters(drehzahldesBadluefters);
   }

    public String getId() {
        return id.get();
    }

    public String getName() {
        return name.get();
    }

    public String getTemperatur() {
        return temperatur.get();
    }

    public String  getLuftfeuchtigkeit() {
        return luftfeuchtigkeit.get();
    }

    public String getFensterzustend() {
        return fensterzustend.get();
    }

    public String getDrehzahldesBadluefters() {
        return drehzahldesBadluefters.get();
    }
    public void setId(String Id) {
         this.id.set(Id);
    }

    public void setName(String prop) {
        this.name.set(prop);
    }

    public void setTemperatur(String prop) {
        this.temperatur.set(prop);
    }

    public void setLuftfeuchtigkeit(String prop) {
        this.luftfeuchtigkeit.set(prop);
    }

    public void setFensterzustend(String prop) {
        this.fensterzustend.set(prop);
    }

    public void setDrehzahldesBadluefters(String prop) {
        this.drehzahldesBadluefters.set(prop);
    }
}

