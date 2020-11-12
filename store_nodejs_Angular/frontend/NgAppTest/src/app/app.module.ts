import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { MyFirstComponentComponent } from './Pages/my-first-component/my-first-component.component';
import { ProductComponent } from './Pages/product/product.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import {DragDropModule} from '@angular/cdk/drag-drop';
import {ScrollingModule} from '@angular/cdk/scrolling';
import {CdkTableModule} from '@angular/cdk/table';
import {CdkTreeModule} from '@angular/cdk/tree';

import {FlexLayoutModule} from '@angular/flex-layout';


import {
  MatAutocompleteModule,
  MatBadgeModule,
  MatBottomSheetModule,
  MatButtonModule,
  MatButtonToggleModule,
  MatCardModule,
  MatCheckboxModule,
  MatChipsModule,
  MatDatepickerModule,
  MatDialogModule,
  MatDividerModule,
  MatExpansionModule,
  MatGridListModule,
  MatIconModule,
  MatInputModule,
  MatListModule,
  MatMenuModule,
  MatNativeDateModule,
  MatPaginatorModule,
  MatProgressBarModule,
  MatProgressSpinnerModule,
  MatRadioModule,
  MatRippleModule,
  MatSelectModule,
  MatSidenavModule,
  MatSliderModule,
  MatSlideToggleModule,
  MatSnackBarModule,
  MatSortModule,
  MatStepperModule,
  MatTableModule,
  MatTabsModule,
  MatToolbarModule,
  MatTooltipModule,
  MatTreeModule,
} from '@angular/material';
import {HttpClient, HttpClientModule} from '@angular/common/http';
import { HomeComponent } from './Pages/home/home.component';
import { AddAproductComponent } from './Pages/add-aproduct/add-aproduct.component';
import { BuyAProductComponent } from './Pages/buy-a-product/buy-a-product.component';
import { MessageDialogeComponent } from './Pages/buy-a-product/buy-a-product.component';
import { DeleteAProductComponent } from './Pages/delete-a-product/delete-a-product.component';
import { DownloadAProductComponent } from './Pages/download-a-product/download-a-product.component';

@NgModule({
  declarations: [
    AppComponent,
    MyFirstComponentComponent,
    ProductComponent,
    HomeComponent,
    AddAproductComponent,
    BuyAProductComponent,
    MessageDialogeComponent,
    DeleteAProductComponent,
    DownloadAProductComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    BrowserAnimationsModule ,
    HttpClientModule,

    CdkTableModule,
    CdkTreeModule,
    DragDropModule,
    MatAutocompleteModule,
    MatBadgeModule,
    MatBottomSheetModule,
    MatButtonModule,
    MatButtonToggleModule,
    MatCardModule,
    MatCheckboxModule,
    MatChipsModule,
    MatStepperModule,
    MatDatepickerModule,
    MatDialogModule,
    MatDividerModule,
    MatExpansionModule,
    MatGridListModule,
    MatIconModule,
    MatInputModule,
    MatListModule,
    MatMenuModule,
    MatNativeDateModule,
    MatPaginatorModule,
    MatProgressBarModule,
    MatProgressSpinnerModule,
    MatRadioModule,
    MatRippleModule,
    MatSelectModule,
    MatSidenavModule,
    MatSliderModule,
    MatSlideToggleModule,
    MatSnackBarModule,
    MatSortModule,
    MatTableModule,
    MatTabsModule,
    MatToolbarModule,
    MatTooltipModule,
    MatTreeModule,
    ScrollingModule,
    FlexLayoutModule,
  ],
  entryComponents: [BuyAProductComponent, MessageDialogeComponent],
    // declarations: [BuyAProductComponent, MessageDialogeComponent],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
