import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';
import { Product} from '../models/Product';


@Injectable({
  providedIn: 'root'
})
export class ProductServiveService {

  baseUrl = 'http://localhost:3000/Products';
  userUrl = 'http://localhost:3000/users/csv';
  constructor(private httpClient: HttpClient) { }


  async getProducts() {
    const result = await this.httpClient.get<any>(this.baseUrl).toPromise();
    return result.data;
  }

  async getOneProduct(prodId: string) {
    const result = await this.httpClient.get<any>(`${this.baseUrl}/${prodId}`).toPromise();
    return result.data;
  }
  async addAproduct(product: Product) {
    const result = await this.httpClient.post<any>(this.baseUrl, product).toPromise();
  }

  async updateAproduct(product: Product) {
    const result = await this.httpClient.put<any>(`${this.baseUrl}/${product._id}`, product).toPromise();
    return result.data;
  }
  async deleteAproduct(__ID: string) {
    const result = await this.httpClient.delete(`${this.baseUrl}/${__ID}`).toPromise();
    return result;
  }
  async downloadAproduct(__ID: string) {
    const result = await this.httpClient.get(`${this.userUrl}/${__ID}`).toPromise();
    return result;
  }
}
