import { Injectable } from '@angular/core';
// import * as fs from 'fs';
// import { writeFile, readFile } from 'fs';


@Injectable({
  providedIn: 'root'
})
export class FsService {

  private logErrFile = "./err.log";
  private logFailFile = "./fail.log";

  constructor() { }

  writeErrLog(str: string) {
    // writeFile(this.logErrFile, str, function (err) {
    //   if (err) {
    //     //Not final solution!!!
    //     console.log(err);
    //   }
    // });
    console.log(str);
  }

  writeFailLog(str: string) {
    // writeFile(this.logFailFile, str, function (err) {
    //   if (err) {
    //     //Not final solution!!!
    //     console.log(err);
    //   }
    // });
    console.log(str);
  }
  
}

