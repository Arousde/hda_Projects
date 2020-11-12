require('dotenv').config();

const mysql = require('mysql')


// var connection ;
// async function connect(){
//     try{
//         connection  = await mysql.createConnection({
//             host: 'db',
//             port: 3306,
//             user: 'root',
//             password: 'qwertz',
//             database: 'examlandout',
//             insecureAuth: true
//         });
//         connection.connect();
    
//     }catch(error){
//         return new Error(error);
//     }
// }
// connect();


var dbpassword = process.env.elo_PASSWORD;
var dbuser = process.env.elo_USER;
var dbhost = process.env.elo_HOST;
var dbpassword = process.env.elo_PASSWORD;
var dbdatabase = process.env.eloDB_NAME;
dbpassword = dbpassword.replace(/\s/g, '');
dbuser = dbuser.replace(/\s/g, '');
dbhost = dbhost.replace(/\s/g, '');
dbdatabase = dbdatabase.replace(/\s/g, '');


try{
var connection  =  mysql.createConnection({
    
        host: dbhost,
        port: 3306,
        user: dbuser,
        password:dbpassword ,
        database: dbdatabase,
        insecureAuth: true
    },(res,error)=>{
        if(error){
            return new Error(error);
        }
    });
    connection.connect((res,error)=>{
        if(error){
            return new Error(error);
        }
    });

}catch(error){
     console.log(new Error(error));
 }



module.exports = connection;