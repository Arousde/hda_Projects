var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', indexfunc);

function indexfunc(req, res, next) {
   res.send("hello world");
}

module.exports = router;
