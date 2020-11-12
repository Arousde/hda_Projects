CREATE TABLE summary(
    idy int NOT NULL AUTO_INCREMENT,
    data VARCHAR(255) NOT NULL, 
    id_user INT NOT NULL, 
    id_exam INT NOT NULL,  
    created TIMESTAMP NOT NULL, 
    updated TIMESTAMP NOT NULL,
    PRIMARY KEY(idy), 
    FOREIGN KEY (id_user) REFERENCES user(idr), 
    FOREIGN KEY (id_exam) REFERENCES exam(idm)
    );

CREATE TABLE solution(
    idn int NOT NULL AUTO_INCREMENT,
    data VARCHAR(255) NOT NULL,
    id_user INT NOT NULL, 
    id_exam INT NOT NULL,  
    created TIMESTAMP NOT NULL, 
    updated TIMESTAMP NOT NULL,
    PRIMARY KEY(idn), 
    FOREIGN KEY (id_user) REFERENCES user(idr), 
    FOREIGN KEY (id_exam) REFERENCES exam(idm)
    );

CREATE TABLE exam(
    idm int NOT NULL AUTO_INCREMENT,
    data VARCHAR(255) NOT NULL,
    created TIMESTAMP NOT NULL, 
    updated TIMESTAMP NOT NULL,
    semester varchar(24) NOT NULL,
    id_modul INT NOT NULL, 
    prof VARCHAR(50) NOT NULL,
    aid INT,
    notes varchar(500),  
    PRIMARY KEY(idm), 
    FOREIGN KEY (id_modul) REFERENCES modul(idl)
    );

CREATE TABLE modul(
    idl int NOT NULL AUTO_INCREMENT,
    semster INT NOT NULL, 
    cp INT NOT NULL, 
    id_user INT,
    PRIMARY KEY(idl), 
    FOREIGN KEY (id_user) REFERENCES user(idr)
    );

CREATE TABLE user(
    idr int NOT NULL AUTO_INCREMENT,
    name varchar(30) NOT NULL, 
    password varchar(128) NOT NULL, 
    permissionlevel INT NOT NULL,
    id_modul INT, 
    PRIMARY KEY(ID), 
    FOREIGN KEY (id_modul) REFERENCES modul(idr)
    );

CREATE TABLE user_module(
    id_user int,
    id_modul int, 
    PRIMARY KEY(id_user),PRIMARY key(id_modul),
    FOREIGN KEY (id_user) REFERENCES user(idr),
    FOREIGN KEY (id_user) REFERENCES modul(idl)
    );
