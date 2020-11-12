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


describe('/GET exam', () => {
    // GET beer should return an empty array
    it('should GET all the exams and check if id in data.property ', (done) => {
      chai
        .request(server)
        .get('/exam')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idm');
          done();
        });
    });
  });

  describe('/GET exam <searching>', () => {
    // GET beer should return an empty array
    it('should GET all the exams that have solutions ', (done) => {
      chai
        .request(server)
        .get('/exam/full')
        .query({ "semester": "2",
        "prof": "testprof",
        "module": "testmodule",
        "amount": 5})
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idm');
          res.body.data[0].should.have.property('idn');
          res.body.data[0].should.have.property('idy');

          done();
        });
    });
  });
  
  describe('/GET exam <searching>', () => {
    // GET beer should return an empty array
    it('should GET all the exams ', (done) => {
      chai
        .request(server)
        .get('/exam/fullbetter')
        .query({ "semester": "2",
        "prof": "testprof",
        "module": "testmodule",
        "amount": 5})
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idm');
          done();
        });
    });
  });


  describe('/GET exam by id', () => {
    // GET beer should return an empty array
    it('should GET a exam by id ', (done) => {
      chai
        .request(server)
        .get('/exam/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data[0].should.have.property('dataex');
          done();
        });
    });
  });

  describe('/GET solutions by exam id ', () => {
    // GET beer should return an empty array
    it('should GET all the solutions related to a specific exam ', (done) => {
      chai
        .request(server)
        .get('/exam/solbyexam/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('dataso');
          done();
        });
    });
  });

  describe('/GET summary by exam id ', () => {
    // GET beer should return an empty array
    it('should GET all the summaries related to a specific exam  ', (done) => {
      chai
        .request(server)
        .get('/exam/sumbyexam/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('datasu');
          done();
        });
    });
  });

  describe('/POST exam', () => {
    // Functional test
    it('it should POST a correct solution', (done) => {
      /** Create solution  */
      const exam = {
            "dataex": "path/path/",
            "semester": "2",
            "prof": "prof",
            "CP": 2,
            "module": "module",
            "aid": 1,
            "notes": "Notes",
            "usrid": 1
 };
      chai.request(server)
        .post('/exam')
        .send(exam)
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

  describe('/DELETE exam/:id', () => {
    it('it should DELETE an exam by given id', (done) => {
        console.log("deleted id ")
        console.log(insertId);
      /** Save beer and test it */
        chai
          .request(server)
          .delete('/exam/' + insertId )
          .end((err, res) => {
         res.should.have.status(200);
            done();
          });
      });
    });

