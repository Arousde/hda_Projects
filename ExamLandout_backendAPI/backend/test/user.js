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


describe('/GET user', () => {
    // GET beer should return an empty array
    it('should GET all the users and check if id in data.property ', (done) => {
      chai
        .request(server)
        .get('/user')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idr');
          done();
        });
    });
  });

  describe('/GET user by id', () => {
    // GET beer should return an empty array
    it('should GET a user by id ', (done) => {
      chai
        .request(server)
        .get('/user/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data[0].should.have.property('name');
          done();
        });
    });
  });

  describe('/GET solutions by user id ', () => {
    // GET beer should return an empty array
    it('should GET all the solutions created by a specific user ', (done) => {
      chai
        .request(server)
        .get('/user/solbyuser/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('dataso');
          done();
        });
    });
  });

  describe('/GET summary by user id ', () => {
    // GET beer should return an empty array
    it('should GET all the summaries created by a specific user ', (done) => {
      chai
        .request(server)
        .get('/user/sumbyuser/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('datasu');
          done();
        });
    });
  });

  describe('/GET exams by user id ', () => {
    // GET beer should return an empty array
    it('should GET all the exams created by a specific user ', (done) => {
      chai
        .request(server)
        .get('/user/exambyuser/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('dataex');
          done();
        });
    });
  });

  describe('/GET user <authentication>', () => {
    // GET beer should return an empty array
    it('should GET a user by name & pwd ', (done) => {
      chai
        .request(server)
        .get('/user/authentication')
        .query({  "name": "usrtest",
                 "password": "pwd"})
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idr')
          done();
        });
    });
  });
  

  describe('/POST user', () => {
    // Functional test
    it('it should POST a correct user', (done) => {
      /** Create solution  */
      const user = {
        "name": "test",
        "password": "test",
        "permissionlevel": 1

 };
      chai.request(server)
        .post('/user')
        .send(user)
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

  describe('/DELETE user/:id', () => {
    it('it should DELETE a user by given id', (done) => {
        console.log("deleted id ")
        console.log(insertId);
      /** Save beer and test it */
        chai
          .request(server)
          .delete('/user/' + insertId )
          .end((err, res) => {
         res.should.have.status(200);
            done();
          });
      });
    });

