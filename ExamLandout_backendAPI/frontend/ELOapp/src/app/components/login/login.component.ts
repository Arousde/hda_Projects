import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { AuthenticationService } from '../../services/authentication.service';
import { FsService } from '../../services/fs.service';
import { User } from '../../models/user';


@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})

export class LoginComponent implements OnInit {

  private user: User = null;

  constructor(
    private authenticationService: AuthenticationService,
    private fsService: FsService,
    private router: Router
  ) { }

  ngOnInit() {
    this.user = new User("test", "test");

    /** 4 Debug */
    this.clickLogin();
  }

  clickLogin() {

    if (this.validate(this.user.name && this.user.password)) {

      let ret = this.authenticationService.getUser(this.user.name, this.user.password);
      ret.then((bool) => {
        if (bool) {
          this.router.navigate(['/cardList']);
          
        }
        else {
          this.fsService.writeFailLog("Failed login try");
        }
      }).catch((err) => {
        this.fsService.writeErrLog(err);
      });
    }

    else {
      this.fsService.writeFailLog("false credentials : " + new Date());
    }
  }

  validate(toVal: string): boolean {
    if (toVal === "name" || toVal === "password" || toVal === "") {
      return false;
    }
    return true;
  }

}
