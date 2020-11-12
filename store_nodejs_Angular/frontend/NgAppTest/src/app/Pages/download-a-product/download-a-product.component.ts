import { Component, OnInit } from '@angular/core';
import {Product} from '../../models/Product';
import { ProductServiveService} from '../../service/product-servive.service';
import { Router, ActivatedRoute } from '@angular/router';
@Component({
  selector: 'app-download-a-product',
  templateUrl: './download-a-product.component.html',
  styleUrls: ['./download-a-product.component.scss']
})
export class DownloadAProductComponent implements OnInit {
  title = 'Download a product';
  product: Product;
  __ID: string;
  constructor(private prodservice: ProductServiveService , private router: Router,
              private route: ActivatedRoute) { }

  ngOnInit() {
    this.__ID = '';
  }
  ondowneclicked() {
    if (this.__ID === '') { console.log('id must be filled'); return ; }
   try {
        this.prodservice.downloadAproduct(this.__ID).then(prod => {
          console.log('downloaded');
        }, err => {
          console.log(err);

        });
   } catch (e) {
   console.log(e);
   }
  }

  onalldowneclicked() {
  }
}
