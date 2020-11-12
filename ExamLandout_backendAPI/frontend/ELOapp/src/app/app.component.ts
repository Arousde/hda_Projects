import { Component, OnInit } from '@angular/core';
import { AuthenticationService } from './services/authentication.service';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {

  title: string = 'ELOapp';
  registered: boolean = false;

  constructor(private authenticationService: AuthenticationService) { }

  ngOnInit() {
    this.authenticationService.registered.subscribe((bool) => {
      console.log(bool)
      if (bool)
        this.registered = true;
    });
  }


}
