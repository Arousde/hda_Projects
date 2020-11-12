import { Component, OnInit } from '@angular/core';
import { Product } from '../../models/Product';
import { ProductServiveService} from '../../service/product-servive.service';
import { Router, ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-add-aproduct',
  templateUrl: './add-aproduct.component.html',
  styleUrls: ['./add-aproduct.component.scss']
})
export class AddAproductComponent implements OnInit {

  product: Product;
  title = ' ADD OR UPDATE A PRODUCT';

  /* for radio buttons to bool*/
  prdSupp: number;

  constructor(private prodservice: ProductServiveService , private router: Router,
              private route: ActivatedRoute) { }
  ngOnInit() {
    this.product = new Product();

  }

  checksupp() {
    if (this.prdSupp === 1) {
      this.product.support = true;
    } else { this.product.support = false; }
  }
  onTop() {
 scroll(0, 0);
  }

  onSave() {
    try {
      this.checksupp();
      this.prodservice.addAproduct(this.product).then(data => {
        this.router.navigate(['/product']);
      }, err => {
        console.log(err);
      });
    } catch (e) {
      throw e;
    }

  }
  onUpdate() {
    try {
      this.checksupp();
      this.prodservice.updateAproduct(this.product).then(data => {
        this.router.navigate(['/product']);
      });
    } catch (e) {
      throw e;
    }

  }
}
