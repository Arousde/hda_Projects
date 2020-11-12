import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BuyAProductComponent } from './buy-a-product.component';

describe('BuyAProductComponent', () => {
  let component: BuyAProductComponent;
  let fixture: ComponentFixture<BuyAProductComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BuyAProductComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BuyAProductComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
