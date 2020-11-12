const indexRouter = require('./index');
const userRouter = require('./elouser');
const examRouter = require('./eloexam');
const solutionRouter = require('./elosolution');
const summaryRouter = require('./elosummary');


const express = require('express');
const app = express();

app.use('/',indexRouter);
app.use('/user',userRouter);
app.use('/exam',examRouter);
app.use('/solution',solutionRouter);
app.use('/summary',summaryRouter);




module.exports = app ;
