import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { DeleteAProductComponent } from './delete-a-product.component';

describe('DeleteAProductComponent', () => {
  let component: DeleteAProductComponent;
  let fixture: ComponentFixture<DeleteAProductComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ DeleteAProductComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(DeleteAProductComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
