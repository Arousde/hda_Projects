import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { AddAproductComponent } from './add-aproduct.component';

describe('AddAproductComponent', () => {
  let component: AddAproductComponent;
  let fixture: ComponentFixture<AddAproductComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AddAproductComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(AddAproductComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
