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
router.get('/', getsummarydata);
router.post('/', postsummarydata);
router.delete('/:id', deletesummarydata);
router.get('/:id', getsumbyid);


function getsummarydata(req, res, next) {
  var query = db.query('SELECT * FROM summary', (error, solutions, fields) => {
    if (error) {
      res.status(500).send(error);
        return new Error(error);
    }

    res.send({
      status: 'OK',
      data: solutions
    })
  })

}

function postsummarydata(req, res, next) {

  try {
    var data = req.body;
    var sql = 
    "INSERT INTO summary (`datasu`, `created`, `id_user`,`id_exam` ) VALUES ('" + data['datasu'] + "','" + new Date().toISOString().slice(0, 19).replace('T', ' ')
    + "','" + data['id_user'] + "','" + data['id_exam'] + "')";
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
    console.log(e);
  }

}
function deletesummarydata(req, res, next) {

  var query = db.query('DELETE FROM summary WHERE idy = ?',req.params.id, (error, result, fields) => {
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

function getsumbyid(req, res, next) {
  
  var query = db.query(
    'SELECT * FROM summary WHERE idy = ?', req.params.id,
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
module.exports = router;
