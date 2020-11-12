const express = require('express');
const router = express.Router({mergeParams: true});

const fs = require('fs');
const Json2csvParser = require('json2csv').Parser;
const PDFDocument = require ('pdfkit');

const weather = require('weather-js');


const Productmodel = require('../Models/MyProduct');

/* GET users listing. */
router.get('/',userfunc);
router.get('/weather',weatherfunc);
router.get('/csv/:id',downloadAproduct);
router.get('/csv',downloadproducts);
router.get('/pdf',downloadAsPdf);


 function weatherfunc(req,res) {

        weather.find({search: 'San Francisco, CA', degreeType: 'F'}, function(err, result) {
            if(err) console.log(err);

            res.send(JSON.stringify(result, null, 2));
        });


}

function userfunc(req, res, next) {
    res.send('hello user');
}

async function downloadAsPdf(req,res){


    try {


        const Products = await Productmodel.find();


       const doc = new PDFDocument
        doc
            .text(Products, 100, 100);


        doc.pipe(fs.createWriteStream('data.pdf'));
        doc.end();


        res.send({
            status: 'OK',
            data: Products
        });
    }catch (e)
    {
        console.log(e);
        //res.status(500).send(e);

    }


}



async function downloadproducts(req,res){

    let filename = 'datas.csv';

    try {


        const Products = await Productmodel.find();

        const fields = ['createdUpdated', 'purchased', 'available',
            '_id', 'prodName', 'category','qty', 'material',
            'propreties', 'color', 'price','currency', 'productionYear',
            'madeIn', 'brand', 'mass','size', 'rating',
            'support','warranty','__v'];

        const json2csvParser = new Json2csvParser({ fields });
        const csv = json2csvParser.parse(Products);

   const ok = await fs.writeFile(filename, csv, (err) => {
            // not secceed
            if (err) throw err;

            // success case, the file was saved
            console.log('data saved!');

        });
        // i cant figure out why this not working and just send an empty file
       res.download(filename);
    }catch (e)
    {

        res.status(500).send(e);

    }



}



async function downloadAproduct(req,res){

    try {


    const Products = await Productmodel.findById(req.params.id);
        let filename = '/home/arous/WebstormProjects/FWE-WS18/data.csv';
        const fields = ['createdUpdated', 'purchased', 'available',
            '_id', 'prodName', 'category','qty', 'material',
            'propreties', 'color', 'price','currency', 'productionYear',
            'madeIn', 'brand', 'mass','size', 'rating',
            'support','warranty','__v'];

        const json2csvParser = new Json2csvParser({ fields });
        const csv = json2csvParser.parse(Products);

        fs.writeFile(filename, csv, (err) => {
            // not secceed
            if (err) throw err;

            // success case, the file was saved
            console.log('data saved!');

        });


        res.download(filename);
   }catch (e)
{
    console.log(e);
   //res.status(500).send(e);

}


}


module.exports = router;
