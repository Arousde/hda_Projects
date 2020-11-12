var express = require('express');
//var db = require('./model/db');
const db = require('../model/db');
const bodyParser = require('body-parser');

const router = express.Router({ mergeParams: true });
const cors = require('cors');

router.use(cors());

router.use(bodyParser.text());
router.use(bodyParser.urlencoded({ extended: true }));
router.use(bodyParser.json());
/* GET all user data. */
router.get('/', getuserdata);
router.get('/authentication', getuserbyNameAndPassword);
router.post('/', postuserdata);
router.delete('/:id', deleteuserdata);
/* new routes */
router.get('/solbyuser/:id', getsolbyuser);
router.get('/sumbyuser/:id', getsumbyuser);
router.get('/exambyuser/:id', getexambyuser);
router.get('/:id', getuserbyid);



function getuserdata(req, res, next) {
  var query = db.query('SELECT * FROM user', (error, users, fields) => {
    if (error) {
      res.status(500).send(error);
      return new Error(error);
    }
    res.send({
      status: 'OK',
      data: users
    })
  })

}

function postuserdata(req, res, next) {

  try {
    var data = req.body;
    var sql = "INSERT INTO user (`name`, `password`, `permissionlevel` ) VALUES ('" + data['name'] + "','" + data['password'] + "','" + data['permissionlevel'] + "')";
    var query = db.query(sql, (error, result) => {
      if (error) {
        res.status(500).send(error);
        return new Error(error);
      }
      res.send({
        status: result
      })
    })
  } catch (e) {
    res.status(500).send(e);
  }

}

function deleteuserdata(req, res, next) {

  var query = db.query('DELETE FROM user WHERE idr = ?',req.params.id, (error, result, fields) => {
    if (error) {
      res.status(500).send(error);
      return new Error(error);
    }

    res.send({
      status: 'DELETED ',
      data: result
    })
  })

}

function getsolbyuser(req, res, next) {
  
  var query = db.query(
    'SELECT s.idn , s.dataso FROM user u , solution s WHERE s.id_user = ?', req.params.id,
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

function getsumbyuser(req, res, next) {
  
  var query = db.query(
    'SELECT s.idy , s.datasu FROM user u , summary s WHERE s.id_user = ?', req.params.id,
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
function getexambyuser(req, res, next) {
  
  var query = db.query(
    'SELECT e.idm , e.dataex FROM user u , exam e WHERE e.usrid = ?', req.params.id,
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
function getuserbyid(req, res, next) {
  
  var query = db.query(
    'SELECT * FROM user WHERE idr = ?', req.params.id,
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

function getuserbyNameAndPassword(req, res, next) {
  var data = req.query;
  var sql = 
  "SELECT u.idr FROM user u WHERE u.name = '" + data['name'] + "' AND  u.password = '" + data['password'] + "'";
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
