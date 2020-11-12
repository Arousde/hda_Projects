import { Injectable } from '@angular/core';
import { HttpClient, HttpParams, HttpHeaders } from '@angular/common/http';
import { ExamCard } from '../models/examCard';
import { Exam } from '../models/exam';
import { Solution } from '../models/solution';
import { Summary } from '../models/summary';

@Injectable({
	providedIn: 'root'
})
export class BackendService {

	private backendURL: string = 'http://localhost:8080/exam';






	constructor(private httpClient: HttpClient, private http : HttpClient) {
	}

	 getCards_RelatedToUser(): Promise<ExamCard[]> {
		// const httpOptions = {
		// 	headers: new HttpHeaders({
		// 		'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
		// 	})
		// };
		console.log(`${this.backendURL}`);
		const exams = this.httpClient.get<any>(`${this.backendURL}`).toPromise();
		return exams;

		/** 4 Debug */
		// let examcard: ExamCard = {
		// 	exam: this.examdum, solution: this.soldum, summary: this.sumdum
		// };

		// let arr: ExamCard[] = [examcard,
		// 	{ exam: new Exam, solution: new Solution, summary: new Summary }];

		// return new Promise((res, rej) => {
		// 	res(arr);
		// })
	}

	getCards_AllFromSubject() {

	}










	examdum: Exam = {
		idm: 3,
		data: "test",
		created: new Date(),
		updated: new Date(),
		semester: "3",
		prof: "Test",
		CP: 3,
		module: "test",
		aid: 3,
		notes: "test",
		usrid: 3
	}
	sumdum: Summary = {
		idy: 1,
		data: "test",
		id_user: 1,
		id_exam: 1,
		created: new Date(),
		updated: new Date()
	}
	soldum: Solution = {
		idn: 2,
		data: "test",
		id_user: 2,
		id_exam: 2,
		created: new Date(),
		updated: new Date
	}

}
