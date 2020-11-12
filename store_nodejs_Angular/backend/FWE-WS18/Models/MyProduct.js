/** Package import**/
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

/** Setup Schema**/
const productSchema = new Schema({
    prodName: {
        type: String,
        required: true
    },
    category: {
        type:String,
        required: true
    },
    qty: {
        type : Number,
        required: true
    },
    material: {
        type : String,
        required: false
    },
    propreties: {
        type : String,
        required: false
    },
    color: {
        type : String,
        required: false
    },
    price: {
        type : Number,
        required: true
    },
    currency: {
        type : String,
        required: true
    },
    productionYear: {
        type : String,
        required: false
    },
    madeIn: {
        type : String,
        required: false
    },
    brand: {
        type : String,
        required: false
    },
    mass: {
        type : String,
        required: false
    },
    size: {
        type : String,
        required: false
    },
    rating: {
        type : String,
        required: false
    },
    support: {
        type : Boolean,
        required: false
    },
    warranty: {
        type : String,
        required: false
    },
    createdUpdated: {
        type : Date,
        default: Date.now()
    },
    purchased: {
        type : Number,
        default: 0
    },
    available: {
        type : Boolean,
        default: 'yes'
    },

})

module.exports = mongoose.model('product',productSchema);