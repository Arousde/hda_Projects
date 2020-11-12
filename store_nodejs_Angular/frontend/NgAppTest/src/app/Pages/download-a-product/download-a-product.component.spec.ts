import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { DownloadAProductComponent } from './download-a-product.component';

describe('DownloadAProductComponent', () => {
  let component: DownloadAProductComponent;
  let fixture: ComponentFixture<DownloadAProductComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ DownloadAProductComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(DownloadAProductComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
