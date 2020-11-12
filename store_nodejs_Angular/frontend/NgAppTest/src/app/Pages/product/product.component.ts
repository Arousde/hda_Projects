import { Component, OnInit } from '@angular/core';
import {Product} from '../../models/Product';
import { ProductServiveService } from '../../service/product-servive.service';

@Component({
  selector: 'app-product',
  templateUrl: './product.component.html',
  styleUrls: ['./product.component.scss']
})
export class ProductComponent implements OnInit {
   title = 'List of products';
   products: Product[] = [ ];
  private displayedColumns3: string[] = [ 'prodName', 'currency', 'productionYear', 'madeIn', 'brand'];
  private displayedColumns2: string[] = [ 'prodName', 'material', 'propreties', 'color' , 'price' , 'available' ];
  private displayedColumns: string[] = ['_id', 'prodName', 'category', 'qty' , 'purchased'];

  constructor(private productService: ProductServiveService ) {

  }

  ngOnInit() {

    this.productService.getProducts().then((products) => {
      this.products = products;
    }, err => {
      console.log(err);
    });

  }

}
