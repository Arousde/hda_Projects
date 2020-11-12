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


describe('/GET solution', () => {
    // GET beer should return an empty array
    it('should GET all the solutions and check if id in data.property ', (done) => {
      chai
        .request(server)
        .get('/solution')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data.should.be.a('array');
          res.body.data[0].should.have.property('idn');
          done();
        });
    });
  });

  describe('/GET solution by id', () => {
    // GET beer should return an empty array
    it('should GET a solutions by id ', (done) => {
      chai
        .request(server)
        .get('/solution/1')
        .end((err, res) => {
          res.should.have.status(200);
          res.body.should.include.key('data');
          res.body.data[0].should.have.property('dataso');
          done();
        });
    });
  });

  describe('/POST solution', () => {
    // Functional test
    it('it should POST a correct solution', (done) => {
      /** Create solution  */
      const solution = {
        "dataso": "path/path/",
        "id_user": 1, 
        "id_exam":1 };
      chai.request(server)
        .post('/solution')
        .send(solution)
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

  describe('/DELETE solution/:id', () => {
    it('it should DELETE a solution given the id', (done) => {
        console.log("delete id ")
        console.log(insertId);
      /** Save beer and test it */
        chai
          .request(server)
          .delete('/solution/' + insertId )
          .end((err, res) => {
         res.should.have.status(200);
            done();
          });
      });
    });

