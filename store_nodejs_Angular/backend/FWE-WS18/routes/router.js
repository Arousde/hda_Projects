const indexRouter = require('./index');
const usersRouter = require('./users');
const Productsrouter = require('./Products');
const express = require('express');
const app = express();

app.use('/',indexRouter);
app.use('/users',usersRouter);
app.use('/Products',Productsrouter);

module.exports = app ;