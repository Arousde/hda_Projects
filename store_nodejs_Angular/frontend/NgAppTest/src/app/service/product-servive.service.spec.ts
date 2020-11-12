import { TestBed } from '@angular/core/testing';

import { ProductServiveService } from './product-servive.service';

describe('ProductServiveService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: ProductServiveService = TestBed.get(ProductServiveService);
    expect(service).toBeTruthy();
  });
});
