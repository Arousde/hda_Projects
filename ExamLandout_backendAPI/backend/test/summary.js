const chai = require('chai');
const chaiHttp = require('chai-http');
const should = chai.should();
const db = require('../model/db');

let jobj ;
let insertId ;

/** File imports */
const server = require('../server');

/** chai.js plugins */
chai.use(chaiHttp);


describe('/GET summary', () => {
    // GET beer should return an empty array
    it('should GET all the summary and check if id in data.property ', (done) => {
      chai
        .request(server)
        .get('/summary')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idy');
          done();
        });
    });
  });

  describe('/GET summary by id', () => {
    // GET beer should return an empty array
    it('should GET a solutions by id ', (done) => {
      chai
        .request(server)
        .get('/summary/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data[0].should.have.property('datasu');
          done();
        });
    });
  });

  describe('/POST summary', () => {
    // Functional test
    it('it should POST a correct summary', (done) => {
      /** Create solution  */
      const summary = {
        "dataso": "path/path/",
        "id_user": 1, 
        "id_exam":1 };
      chai.request(server)
        .post('/summary')
        .send(summary)
        .end((err, res) => {
          res.should.have.status(200);
          console.log("inserted id : ");
          var jobj = JSON.parse(res.text);
          console.log(jobj.status.insertId); 
          insertId = jobj.status.insertId;
          done();
        });
    });
  });

  describe('/DELETE summary/:id', () => {
    it('it should DELETE a solution given the id', (done) => {
        console.log("deleted id ")
        console.log(insertId);
      /** Save beer and test it */
        chai
          .request(server)
          .delete('/summary/' + insertId )
          .end((err, res) => {
         res.should.have.status(200);
            done();
          });
      });
    });

