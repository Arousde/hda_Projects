const Productmodel = require('../Models/MyProduct');
const express = require('express');
const router = express.Router({mergeParams: true});

/** express http methods Products listing**/
router.get('/',getProducts);
router.post('/',createAproduct);
router.get('/:id',getAproduct);
router.delete('/:id', deleteAproduct);
router.put('/:id',updateAproduct);




async function updateAproduct(req,res){

    try {

        const ProductId = req.params.id;
        const Product = await Productmodel.findOneAndUpdate({

            _id: ProductId
        }, {
            $set: req.body
        }, {
           new: true
        });

        res.send({
            status: 'OK',
            data: Product
        })

    }catch (e) {

        res.status(500).send(e);
    }

}


async function deleteAproduct(req,res){
    try {

        await Productmodel.findByIdAndRemove(req.params.id);
        res.status(204).send();

    }catch (e) {
     res.status(500).send(e);
    }
}


async function getAproduct(req,res){
    try {

        const Product = await Productmodel.findById(req.params.id);
        res.send({
            status: 'OK',
            data: Product
        });

    }catch (e) {
        res.status(500).send(e);

    }
}

async function createAproduct(req,res){


    try {
        const newProduct = Productmodel(req.body)
        const createdProduct = await newProduct.save();


    res.status(201).send({
        status:'Created',
        data:createdProduct
    });
    }
      catch (e) {
          res.status(500).send(e);

      }
}
async function getProducts(req,res,next) {
    try {
        const Product = await Productmodel.find();
        console.log(Product);
        res.send({
            status: 'OK',
            data: Product
        });
    }catch (e) {
        console.log(e);
    }
}

module.exports = router;