export class User {

    idr: number;
    name: string;
    password: string;

    constructor(name? : string, pass? : string, idr?: number) {
        if (idr)
            this.idr = idr;
        this.name = name;
        this.password = this.password;
    }

}