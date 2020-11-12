var express = require('express');
//var db = require('./model/db');
const db = require('../model/db');
const bodyParser = require('body-parser');
const cors = require('cors');

const router = express.Router({ mergeParams: true });

router.use(cors());
router.use(bodyParser.text());
router.use(bodyParser.urlencoded({ extended: true }));
router.use(bodyParser.json());
/* GET all exam data. */
router.get('/', getexamdata);
router.get('/full', getfullexam);
router.get('/fullbetter', getfullexambetter);
router.post('/', postexamdata);
router.delete('/:id', deleteexamdata);
/* new routes */
router.get('/solbyexam/:id', getsolbyexam);
router.get('/sumbyexam/:id', getsumbyexam);
router.get('/:id', getexambyid);




function getexamdata(req, res, next) {
  var query = db.query('SELECT * FROM exam', (error, users, fields) => {
    if (error) {
        res.status(500).send(error);  
        return new Error(error);
    }

    res.send({
      status: 'OK',
      data: users
    })
  });

  
}

function postexamdata(req, res, next) {
  
    var data = req.body;
    var sql = 
    "INSERT INTO exam (`dataex`, `created`, `semester`,`prof`,`CP`,`module`,`aid`,`notes`,`usrid` ) VALUES ('" + data['dataex'] + "','" + new Date().toISOString().slice(0, 19).replace('T', ' ')
    + "','" + data['semester'] + "','" + data['prof'] + "','" + data['CP'] + "','" + data['module'] + "','" + data['aid'] + "','" + data['notes'] + "','" + data['usrid'] + "')";
   try {
    var query = db.query(sql, (error, result) => {
      if (error) {
        res.status(500).send(error);  
        return new Error(error);
      }
      res.send({
        status: result
      })
    })
   }catch(error){
    res.status(500).send(error);

   }
    
}

function deleteexamdata(req, res, next) {

  var query = db.query('DELETE FROM exam WHERE idm = ?',req.params.id, (error, result, fields) => {
    if (error) {
      res.status(500).send(error);
      return new Error(error);
    }

    res.send({
      status: 'DELETED',
      data: result
    })
  })

}
function getsolbyexam(req, res, next) {
  
  var query = db.query(
    'SELECT s.idn , s.dataso FROM exam e , solution s WHERE s.id_exam = ?', req.params.id,
    (error, users, fields) => {
    if (error) {
        res.status(500).send(error);  
        return new Error(error);
    }

    res.send({
      status: 'OK',
      data: users
    })
  });

  
}

function getsumbyexam(req, res, next) {
  
  var query = db.query(
    'SELECT s.idy , s.datasu FROM exam e , summary s WHERE s.id_exam = ?', req.params.id,
    (error, users, fields) => {
    if (error) {
        res.status(500).send(error);  
        return new Error(error);
    }

    res.send({
      status: 'OK',
      data: users
    })
  });

  
}
function getexambyid(req, res, next) {
  
  var query = db.query(
    'SELECT * FROM exam WHERE idm = ?', req.params.id,
    (error, users, fields) => {
    if (error) {
        res.status(500).send(error);  
        return new Error(error);
    }

    res.send({
      status: 'OK',
      data: users
    })
  });
}

function getfullexam(req, res, next) {
  var data = req.query;
  var sql = 
  "SELECT e.idm , e.dataex, e.module ,e.prof , e.CP , e.aid , e.notes , e.semester ,s.idy , s.datasu , n.idn , n.dataso FROM exam e , summary s , solution n WHERE e.semester = '" + data['semester'] + "' AND e.prof = '" + data['prof'] + "' AND e.module = '" + data['module'] + "' AND s.id_exam = e.idm AND n.id_exam = e.idm order by e.created DESC LIMIT " + data['amount'] + " ";
 try {
  var query = db.query(sql, (error, exams, fields)=> {
    if (error) {
      res.status(500).send(error);  
      return new Error(error);
    }
    res.send({
      status: 'OK',
      data: exams
    })
  });
 }catch(error){
  res.status(500).send(error);

 }
}

function getfullexambetter(req, res, next) {
  var data = req.query;
  var sql = 
  "SELECT e.idm , e.dataex ,  e.module , e.prof , e.CP , e.aid , e.notes , e.semester FROM exam e  WHERE e.semester = '" + data['semester'] + "' AND e.prof = '" + data['prof'] + "' AND e.module = '" + data['module'] + "' order by e.created DESC LIMIT " + data['amount'] + " ";
 try {
  var query = db.query(sql, (error, exams, fields)=> {
    if (error) {
      res.status(500).send(error);  
      return new Error(error);
    }
    res.send({
      status: 'OK',
      data: exams
    })
  });
 }catch(error){
  res.status(500).send(error);

 }
}


module.exports = router;
