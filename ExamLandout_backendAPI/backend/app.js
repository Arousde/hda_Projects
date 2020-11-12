var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');



const router = require('./routes/router');

var app = express();


//For google chrome core
// app.use(function(req, res, next) {
//     res.header("Access-Control-Allow-Origin", "*");
//     res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
//     console.log("Access")

//     if(req.method === "OPTIONS") {
//         res.header("Acces-Control-Allow-Methods", "GET, PUT, POST, DELETE");
//         return res.status(200).json({});}

//     next();
// });
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

/* Routes */
app.use('/', router);


// catch 404 and forward to error handler
app.use(function(req, res, next) {
  res.status(404).send();  
  next(createError(404));

});


module.exports = app;
