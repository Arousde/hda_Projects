import { Component, OnInit } from '@angular/core';

import { Product } from '../../models/Product';
import { ProductServiveService} from '../../service/product-servive.service';
import { Router, ActivatedRoute } from '@angular/router';
 // popup dialog for qty check msg
import {MatDialog} from '@angular/material';
import {forEach} from '@angular/router/src/utils/collection';

@Component({
  selector: 'app-buy-a-product',
  templateUrl: './buy-a-product.component.html',
  styleUrls: ['./buy-a-product.component.scss']
})
export class BuyAProductComponent implements OnInit {
  title = 'purchased products';
  product: Product;
  products: Product[] = [ ];
  purchasedprd: Product[] = [ ];
  __ID: string;
  qnty: number;
  prc: number;
  constructor(private prodservice: ProductServiveService , private router: Router,
              private route: ActivatedRoute , public dialoge: MatDialog  ) {
    this.product = new Product();
    this.title = this.title.toUpperCase();

  }

  prodsort() {
    for (const p of this.products) {
      if (p.purchased > 0) {
        this.purchasedprd.push(p);
      }
    }
  }
  ngOnInit() {
    this.qnty = 0 ;
    this.prc = 0 ;
    this.__ID = '';
    this.prodservice.getProducts().then(prds => {
       this.products = prds ;
       this.prodsort();
    }, err => {
         console.log(err);
    });
  }
  async getTheProd() {
   await this.prodservice.getOneProduct(this.__ID).then(prduct => {
     this.product = prduct;

   }, err => {
     this.dialoge.open( MessageDialogeComponent);
    });
   }
   // check the qty and calculate the price if product recieved if not popup
   calculateProdprc() {
    if (this.qnty === 0) {
      this.dialoge.open( MessageDialogeComponent);
    }  if (this.__ID === '') {
      this.dialoge.open( MessageDialogeComponent);
    } else {
      console.log(this.prc);
      console.log(this.qnty);
      console.log('prd' + this.product.price);
      this.prc = this.product.price * this.qnty ;
    }
   }
  async onprice() {
    try {
      // without then() the calculateProdprc can be executed before fetching the product
      this.getTheProd().then(prod => {
        this.calculateProdprc();
      });
    } catch (e) {
      console.log(e);
    }
  }
  onclear() {
    this.qnty = 0 ;
    this.prc = 0 ;
    this.__ID = '';
  }

  checkavailability() {
    if (this.product.qty > 0 && this.product.available === false) {
      // why not
      this.product.available = true ;
    }
    if (this.product.available) {
      if (this.product.qty <= 0) {
        this.product.available = false ;
        return false ;
      } else if (this.product.qty > 0) {
        if (this.product.qty - this.qnty <= 0 ) {
          this.product.purchased = this.product.purchased + this.product.qty;
          this.product.qty = 0 ;
          this.product.available = false ;
        } else {
          this.product.purchased =  this.product.purchased + this.qnty;
          this.product.qty = this.product.qty - this.qnty ;
        }
      }
       return true;
    }
    return false ;
  }
  onBuyclicked() {
    this.getTheProd().then(prod => {
      if (this.checkavailability()) {
          this.prodservice.updateAproduct(this.product).then( prd => {
          this.router.navigate(['/product']);
          }, err => {
          console.error(err);
          });
      } else {
        this.dialoge.open( MessageDialogeComponent);
      }
    },
      err => {
         console.log(err);
      });
  }
}

@Component({
  selector: 'app-message-dialoge',
  templateUrl: './message-dialoge.html',
  styleUrls: ['./buy-a-product.component.scss']
})
export class  MessageDialogeComponent {}

