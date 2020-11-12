import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { MyFirstComponentComponent } from './Pages/my-first-component/my-first-component.component';
import {ProductComponent} from './Pages/product/product.component';
import {HomeComponent} from './Pages/home/home.component';
import {AddAproductComponent} from './Pages/add-aproduct/add-aproduct.component';
import { BuyAProductComponent} from './Pages/buy-a-product/buy-a-product.component';
import { DeleteAProductComponent } from './Pages/delete-a-product/delete-a-product.component';
import {DownloadAProductComponent} from './Pages/download-a-product/download-a-product.component';

const routes: Routes = [
  {
    path: '',
    redirectTo: 'Home',
    pathMatch: 'full',
  },
  {
    path: 'test',
    component: MyFirstComponentComponent
  },
  {
    path: 'product',
    component: ProductComponent
  },
  {
    path: 'Home',
    component: HomeComponent
  },
  {
    path: 'Addaprod',
    component: AddAproductComponent
  },
  {
    path: 'buyaprod',
    component: BuyAProductComponent
  },
  {
    path: 'delaprod',
    component: DeleteAProductComponent
  }, {
    path: 'downloadprd',
    component: DownloadAProductComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
