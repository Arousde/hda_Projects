import { Injectable, EventEmitter } from '@angular/core';
import { HttpClient, HttpParams, HttpHeaders } from '@angular/common/http';
import { User } from '../models/user';

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {

  private user: User = new User();
  private registered$ = new EventEmitter<boolean>();

  constructor(private httpClient: HttpClient) { }

  /** Service Interface */

  requestUser(name?: string, pword?: string): User {
    return this.user;
  }

  get registered(): EventEmitter<boolean> {
    return this.registered$;
  }

  logOut(): boolean {
    this.registered$.emit(false);
    return false;
  }

  /** Http Requests */

  //login User
  getUser(name: string, pass: string): Promise<boolean> {
    return new Promise<boolean>((res, rej) => {
      // let ret = // Backend Access
      let ret = 1;
      if (ret > 0) {
        this.user.name = name;
        this.user.password = pass;
        this.user.idr = ret;
        res(true);
      }
      else {
        res(false);
      }
    });
  }


}
