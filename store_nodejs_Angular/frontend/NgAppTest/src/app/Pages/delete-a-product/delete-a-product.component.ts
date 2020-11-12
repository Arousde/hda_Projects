import { Component, OnInit } from '@angular/core';
import {Product} from '../../models/Product';
import { ProductServiveService} from '../../service/product-servive.service';
import { Router, ActivatedRoute } from '@angular/router';
@Component({
  selector: 'app-delete-a-product',
  templateUrl: './delete-a-product.component.html',
  styleUrls: ['./delete-a-product.component.scss']
})
export class DeleteAProductComponent implements OnInit {

  title = 'Delete a  product';
  product: Product;
  __ID: string;
  constructor(private prodservice: ProductServiveService , private router: Router,
              private route: ActivatedRoute) { }

  ngOnInit() {
    this.product = new Product();
    this.__ID = '';
  }

  onDeleteclicked() {
    if (this.__ID === '') { console.log('id must be filled'); return ; }

   try {
     this.prodservice.deleteAproduct(this.__ID).then(prod => {
       this.router.navigate(['/product']);
     }, err => {
       console.error(err);
     });
   } catch (e) {
     console.log(e);
   }
  }
}
