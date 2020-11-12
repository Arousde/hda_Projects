export class Product {

  _id?: string;
  prodName: string;
  category: string;
  qty: number;
  material?: string;
  propreties?: string;
  color?: string;
  price: number;
  currency: string;
  productionYear?: string;
  madeIn?: string;
  brand?: string;
  mass?: string;
  size?: string;
  rating?: string;
  support?: boolean;
  createdUpdated?: Date;
  purchased?: number;
  available?: boolean;
  constructor(values: Object = {}) {
    Object.assign(this, values);
  }

}
