import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { NavbarComponent } from './components/navbar/navbar.component';
import { ExamCardComponent } from './components/exam-card/exam-card.component';
import { PreviewTileComponent } from './components/preview-tile/preview-tile.component';
import { TileListComponent } from './components/tile-list/tile-list.component';
import { AuthenticationService } from './services/authentication.service';
import { LoginComponent } from './components/login/login.component';
import { CardListComponent } from './components/card-list/card-list.component';
import { FsService } from './services/fs.service';

@NgModule({
  declarations: [
    AppComponent,
    NavbarComponent,
    ExamCardComponent,
    PreviewTileComponent,
    TileListComponent,
    LoginComponent,
    CardListComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule
  ],
  providers: [AuthenticationService, FsService],
  bootstrap: [AppComponent]
})
export class AppModule { }
